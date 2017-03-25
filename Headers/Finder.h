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

using namespace std;
using namespace cv;

class Finder
{
	/*! Constructor for Finder
	 *   @return: None - Initialize mDetector
	 * */
	Finder();

public:
	/*! Accessor for mDescriptorMatches
	 * */
	bool GetDescriptorMatches();

protected:
	/*! PerformDescriptorMatch()
	 *	@in QueryDesc : Descriptors extracted from Query
	 *	@in SceneDesc : Descriptors extracted from Scene
	 *  @brief        : Perform desc match and populate
	 *                  mDescriptorMatches
	 *  @return       : Return success or failure
	 *
	 * */
	bool PerformDescriptorMatch(Mat QueryDesc, Mat SceneDesc);

	/*! CalculateKeyPointDist()
	 *	@in Desc : Descriptors extracted from Query
	 *	@brief	 : Calculate of max and min distances between
	 *	           keypoints. Populate mMaxKeyPointDist and
	 *             mMinKeyPointDist
	 *  @return  : Return success or failure
	 *
	 * */
	bool CalculateKeyPointDist(Mat Desc);

private:
	Ptr<Feature2D>    mDetector;
	FlannBasedMatcher mFMatcher;
	vector<DMatch>    mDescriptorMatches;
	double 			  mMaxKeyPointDist = 0;
	double            mMinKeyPointDist = 70;
};


#endif /* HEADERS_FINDER_H_ */
