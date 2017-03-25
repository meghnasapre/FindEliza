/*
 * Query.h
 *
 *  Created on: Mar 25, 2017
 *      Author: meghnasapre
 */

#ifndef HEADERS_IMAGEHANDLER_H_
#define HEADERS_IMAGEHANDLER_H_



/*
 * Query.h
 *
 *  Created on: Mar 25, 2017
 *      Author: meghnasapre
 */

#ifndef HDR_QUERY_H_
#define HDR_QUERY_H_

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

class ImageHandler
{
	/*! Constructor for mImg
	 *  @in filename          : Filepath and name to location
	 *  @in(optional) resize  : cv resize to scale image, defaults to no resize
	 *  @return               : None - Convert to Grayscale for processing
	 *  						Initialize mQueryImg and mGrayScaleImg
	 * */
	ImageHandler(const string filename, const double resize=1.0);

public:
	/*! GetImg()
	 *  @return : Accessor for mImg and mGrayScaleImg
	 * */
	Mat GetImg(bool GrayScale=false);

	/*! GetKeyPoints()
	 *  @return : Accessor for mKeyPoints
	 * */
	vector<KeyPoint> GetKeyPoints();

	/*! GetDescriptors()
	 *  @return : Accessor for mDescriptors
	 * */
	Mat GetDescriptors();

protected:
	/*! SetKeyPointsAndDescriptors()
	 *	@in detector : Pass in pointer to detector (SURF/SIFT etc.)
	 *	               to detect keypoints and extract descriptors
	 *  @return      : Set mKeyPoints and mDescriptors
	 * */
	bool SetKeyPointsAndDescriptors(Ptr<Feature2D> detector);

private:
	Mat mImg, mGrayScaleImg;
	vector<KeyPoint> mKeyPoints;
	Mat mDescriptors;

};

#endif /* HEADERS_IMAGEHANDLER_H_ */


#endif /* HEADERS_IMAGEHANDLER_H_ */
