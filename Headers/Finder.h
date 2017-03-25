/*
 * Finder.h
 *
 *  Created on: Mar 25, 2017
 *      Author: meghnasapre
 */

#ifndef HEADERS_FINDER_H_
#define HEADERS_FINDER_H_

#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"
#include "include/opencv2/xfeatures2d/nonfree.hpp"
#include "ImageHandler.h"

using namespace std;
using namespace cv;

class Finder
{
	/*! Constructor for Finder
	 *  @return: None - Initialize  mQuery, mScene, mDetector
	 * */
	Finder(ImageHandler query, ImageHandler scene);

public:
	/*! Accessor for mDescriptorMatches
	 * */
	vector<DMatch> GetDescriptorMatches();

	/*! Accessor for mHomography
	 * */
	Mat GetHomography();

	/*! Render output
	 * */
	void RenderOutput();

protected:
	/*! PerformDescriptorMatch()
	 *  @brief        : Retrieve Descriptors extracted from
	 *                  Query and scene. Perform desc match
	 *                  and populate mDescriptorMatches
	 *  @return       : Return success or failure
	 *
	 * */
	bool PerformDescriptorMatch();

	/*! CalculateKeyPointDist()
	 *	@in Desc : Descriptors extracted from Query
	 *	@brief	 : Calculate of max and min distances between
	 *	           keypoints for Query Descr.
	 *	           Populate mMaxKeyPointDist and mMinKeyPointDist
	 *  @return  : Return success or failure
	 *
	 * */
	bool CalculateKeyPointDist();

	/*! CalculateGoodMatches()
	 *	@brief	 : Narrow down interesting matches from Query Desc
	 *	           Populate mGoodMatches
	 *  @return  : Return success or failure
	 *
	 * */
	bool CalculateGoodMatches();


	/*! FindHomography()
	 *	@brief	 : Get KeyPoints from the good matches
	 *	           Use CV to find Homography. Populate mHomography
	 *  @return  : Return success or failure
	 *
	 * */
	bool FindHomography();

	/*! PerformPerspTransform()
	 *	@brief	 : Calculate corners from query to find object to be detected
	 *	           Use CV to do perspective transform. Populate mSceneCorners
	 *  @return  : Return success or failure
	 *
	 * */
	bool PerformPerspTransform();

private:
	Ptr<Feature2D>    mDetector;
	FlannBasedMatcher mFMatcher;
	vector<DMatch>    mDescriptorMatches;
	vector<DMatch>    mGoodMatches;
	ImageHandler      mQuery;
	ImageHandler      mScene;
	vector<Point2f>   mSceneCorners;
	Mat 			  mImageMatches;
	Mat 			  mHomography;
	double 			  mMaxKeyPointDist = 0;
	double            mMinKeyPointDist = 70;
};


#endif /* HEADERS_FINDER_H_ */
