/*
 * Finder.cpp
 *
 *  Created on: Mar 25, 2017
 *      Author: meghnasapre
 */

#include "../Headers/Finder.h"

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

/*! Constructor for Finder
	 *  @return: None - Initialize  mQuery, mScene, mDetector
	 * */
Finder::Finder(ImageHandler *query, ImageHandler *scene):mQuery(query),mScene(scene)
{
    mMaxKeyPointDist = 0;
    mMinKeyPointDist = 70;
	mDetector = SIFT::create();
}

/*! Accessor for Feature Detector
 * */
Ptr<Feature2D> Finder::GetDetector()
{
	return mDetector;
}


/*! PerformDescriptorMatch()
 *  @brief        : Retrieve Descriptors extracted from
 *                  Query and scene. Perform desc match
 *                  and populate mDescriptorMatches
 *  @return       : Return success or failure
 *
 * */
bool Finder::PerformDescriptorMatch()
{
	vector<KeyPoint> kp =  mQuery->GetKeyPoints();
	try
	{
		mFMatcher.match( mQuery->GetDescriptors(), mScene->GetDescriptors(), mDescriptorMatches);
		return true;
	}
	catch(int e)
	{
		cout << "An exception occurred. Exception: " << e << '\n';
		return false;
	}
	return false;
}

/*! CalculateKeyPointDist()
	 *	@in Desc : Descriptors extracted from Query
	 *	@brief	 : Calculate of max and min distances between
	 *	           keypoints for Query Descr.
	 *	           Populate mMaxKeyPointDist and mMinKeyPointDist
	 *  @return  : Return success or failure
	 *
	 * */
bool Finder::CalculateKeyPointDist()
{
	if(mDescriptorMatches.size() < 1)
	{
		return false;
	}

	for( int i = 0; i < (mQuery->GetDescriptors()).rows; i++ )
	 {
		  double dist = mDescriptorMatches[i].distance;
		  if( dist < mMinKeyPointDist ) mMinKeyPointDist = dist;
		  if( dist > mMaxKeyPointDist ) mMaxKeyPointDist = dist;
	  }
	  return true;
}

/*! CalculateGoodMatches()
 *	@brief	 : Narrow down interesting matches from Query Desc
 *	           Populate mGoodMatches
 *  @return  : Return success or failure
 *
 * */
bool Finder::CalculateGoodMatches()
{
	 if(mDescriptorMatches.size() < 1)
	 {
		 return false;
	 }

	 for( int i = 0; i < (mQuery->GetDescriptors()).rows; i++ )
	  {
		 if( mDescriptorMatches[i].distance < 3*mMinKeyPointDist )
		 {
			  mGoodMatches.push_back( mDescriptorMatches[i]);
		 }
	  }
	return true;
}

/*! FindHomography()
 *	@brief	 : Get KeyPoints from the good matches
 *	           Use CV to find Homography. Populate mHomography
 *  @return  : Return success or failure
 *
 * */
bool Finder::FindHomography()
{
	vector<KeyPoint> QueryKeyPoints = mQuery->GetKeyPoints();
	vector<KeyPoint> SceneKeyPoints = mScene->GetKeyPoints();
	if(mGoodMatches.size() < 1 || QueryKeyPoints.size() < 1 || SceneKeyPoints.size() < 1)
	{
		return false;
	}
	 std::vector<Point2f> obj;
	 std::vector<Point2f> scene;
	 for( size_t i = 0; i < mGoodMatches.size(); i++ )
	 {
		 obj.push_back(QueryKeyPoints[mGoodMatches[i].queryIdx ].pt );
		 scene.push_back(SceneKeyPoints[mGoodMatches[i].trainIdx ].pt );
	  }

	mHomography = findHomography( obj, scene, RANSAC );
	return true;
}

/*! PerformPerspTransform()
 *	@brief	 : Calculate corners from query to find object to be detected
 *	           Use CV to do perspective transform. Populate mHomography
 *  @return  : Return success or failure
 *
 * */
bool Finder::PerformPerspTransform()
{
	 Mat Query = mQuery->GetImg();
	 std::vector<Point2f> QueryCorners(4);
	 QueryCorners[0] = cvPoint(0,0); QueryCorners[1] = cvPoint( Query.cols, 0 );
	 QueryCorners[2] = cvPoint( Query.cols, Query.rows ); QueryCorners[3] = cvPoint( 0, Query.rows );

    perspectiveTransform( QueryCorners, mSceneCorners, mHomography);
	return true;
}

/*! Accessor for mDescriptorMatches
 * */
vector<DMatch> Finder::GetDescriptorMatches()
{
	if(mDescriptorMatches.size() < 1)
	{
		PerformDescriptorMatch();
	}
	return mDescriptorMatches;
}

/*! Draw Matches. Populate mImageMatches
 * */
bool Finder::DrawMatches()
{
	try
	{
		Mat ImageMatches;

		drawMatches(mQuery->GetImg(), mQuery->GetKeyPoints(), mScene->GetImg(), mScene->GetKeyPoints(),
			   mGoodMatches, ImageMatches, Scalar::all(255), Scalar::all(255),
			   std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

		ImageMatches.copyTo(mImageMatches);

		return true;
	}
	catch(int e)
	{
		cout << "An exception occurred. Exception: " << e << '\n';
		return false;
	}
	return false;
}
/*! Accessor for mHomography
 * */
Mat Finder::GetHomography()
{
	if(mHomography.empty())
	{
		CalculateGoodMatches();
		FindHomography();
	}
	return mHomography;
}

/*! Render output
 * */
void Finder::RenderOutput()
{
	 Mat Query = mQuery->GetImg();

	 DrawMatches();
	 PerformPerspTransform();

	 if(Query.empty() || mImageMatches.empty() || mSceneCorners.size() < 1)
	 {
		 cout << "Rendering is broken: Please check structures" << endl;
		 exit(0);
	 }

	 {
	  //-- Draw lines between the corners (the mapped object in the scene - image_2 )
	  line( mImageMatches, mSceneCorners[0] + Point2f( Query.cols, 0), mSceneCorners[1] + Point2f( Query.cols, 0), Scalar(0, 0, 255), 4 );
	  line( mImageMatches, mSceneCorners[1] + Point2f( Query.cols, 0), mSceneCorners[2] + Point2f( Query.cols, 0), Scalar(0, 0, 255), 4 );
	  line( mImageMatches, mSceneCorners[2] + Point2f( Query.cols, 0), mSceneCorners[3] + Point2f( Query.cols, 0), Scalar(0, 0, 255), 4 );
	  line( mImageMatches, mSceneCorners[3] + Point2f( Query.cols, 0), mSceneCorners[0] + Point2f( Query.cols, 0), Scalar(0, 0, 255), 4 );
	 }

	  //-- Show detected matches
	  std::string windowName = "Find Eliza";
	  namedWindow(windowName , WINDOW_NORMAL );
	  imshow( windowName, mImageMatches );
}


