/*
 * Query.h
 *
 *  Created on: Mar 25, 2017
 *      Author: meghnasapre
 */

#ifndef HEADERS_QUERY_H_
#define HEADERS_QUERY_H_



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

class QueryImg{
	/*! Constructor for Query Img */
	QueryImg(string filename, double resize=1.0);

	uchar* getQueryImgData();

private:
	Mat mQueryImg;
	Mat mQueryKeyPoints;
	Mat mQueryDescriptors;

};

#endif /* HDR_QUERY_H_ */


#endif /* HEADERS_QUERY_H_ */
