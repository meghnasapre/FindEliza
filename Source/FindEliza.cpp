/*
 * FindEliza.cpp
 *
 *  Created on: Mar 25, 2017
 *      Author: meghnasapre
 */

#include "../Headers/ImageHandler.h"
#include "../Headers/Finder.h"

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

void readme();

/*! @function main */
int main( int argc, char** argv )
{
	 if( argc != 3 )
	 {
		 readme();
		 return -1;
	 }

	 /*! Input Query Image */
	ImageHandler query(argv[1], 0.8);
	/*! Input Scene */
	ImageHandler scene(argv[2]);

	/*! Initialize the finder */
	Finder finder(&query, &scene);

	/*! Use Feature Detector initialized by finder
	 * to get KeyPoints and Descriptors
	 */
	query.SetKeyPointsAndDescriptors(finder.GetDetector());
	scene.SetKeyPointsAndDescriptors(finder.GetDetector());

	/*! Perform Description Matching
	 * */
	finder.GetDescriptorMatches();

	/*! Calculate Good Matches
	 *  and get Homography
	 * */
	finder.GetHomography();

	/*! Apply Perspective Transform
	 *  Draw and Render Matches
	 * */
	finder.RenderOutput();

    waitKey(0);
    return 0;
}

/*! @function readme */
void readme()
{
	cout << " Usage: ./FindEliza <query> <scene>" << endl;
}




