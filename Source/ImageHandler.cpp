/*
 * ImageHandler.cpp
 *
 *  Created on: Mar 25, 2017
 *      Author: meghnasapre
 */

#include "../Headers/ImageHandler.h"

using namespace std;
using namespace cv;

/*! Constructor for mImg
 *  @in filename          : Filepath and name to location
 *  @in(optional) resize  : cv resize to scale image, defaults to no resize
 *  @return               : Convert to Grayscale for processing.
 *  						Initialize mQueryImg and mGrayScaleImg.
 * */
ImageHandler::ImageHandler(const string filename, double resizeVal)
{
	/*! Read the image in Color */
	mImg = imread( filename, IMREAD_COLOR );
	if(!mImg.data)
	{
		 cout << " --(!) Error reading images " << endl;
		 return;
	}
	/*! Convert to Grayscale and store in mGrayScaleImg */
	cvtColor(mImg, mGrayScaleImg, CV_RGB2GRAY );
	/*! resize GrayScale image for processing */
	resize(mGrayScaleImg, mGrayScaleImg, cv::Size(), resizeVal, resizeVal);
}

/*! GetImg()
 *  @return : Accessor for mImg and mGrayScaleImg
 * */
Mat ImageHandler::GetImg(bool GrayScale)
{
	if(GrayScale)
	{
		return mGrayScaleImg;
	}
	return mImg;
}

/*! GetKeyPoints()
 *  @return : Accessor for mKeyPoints
 * */
vector<KeyPoint> ImageHandler::GetKeyPoints()
{
	return mKeyPoints;
}

/*! GetDescriptors()
 *  @return : Accessor for mDescriptors
 * */
Mat ImageHandler::GetDescriptors()
{
	return mDescriptors;
}

/*! SetKeyPointsAndDescriptors()
 *	@in detector : Pass in pointer to detector (SURF/SIFT etc.)
 *	               to detect keypoints and extract descriptors
 *  @return      : Set mKeyPoints and mDescriptors
 * */
bool ImageHandler::SetKeyPointsAndDescriptors(Ptr<Feature2D> detector)
{
	if(detector == nullptr)
	{
		return false;
	}
	try
	{
		detector->detectAndCompute( mGrayScaleImg, Mat(), mKeyPoints, mDescriptors );
		return true;
	}
	catch(int e)
	{
		cout << "An exception occurred. Exception: " << e << '\n';
		return false;
	}
	return false;
}
