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
ImageHandler::ImageHandler(const string filename, const double resize)
{
	/*! Read the image in Color */
	mImg = imread( filename, IMREAD_COLOR );
	/*! Convert to Grayscale and store in mGrayScaleImg */
	cvtColor(mImg, mGrayScaleImg, CV_RGB2GRAY );
	/*! resize GrayScale image for processing */
	resize(mGrayScaleImg, mGrayScaleImg, cv::Size(), resize, resize);
}

/*! GetKeyPoints()
 *  @return : Accessor for mKeyPoints
 * */
vector<KeyPoint> ImageHandler::GetKeyPoints()
{
	return this->mKeyPoints;
}

/*! GetDescriptors()
 *  @return : Accessor for mDescriptors
 * */
vector<KeyPoint> ImageHandler::GetDescriptors()
{
	return this->mDescriptors;
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
		detector->detectAndCompute( this->mGrayScaleImg, Mat(), this->mKeyPoints, this->mDescriptors );
	}
	catch(int e)
	{
		cout << "An exception occurred. Exception: " << e << '\n';
		return false;
	}
	return true;
}
