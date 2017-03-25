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

	ImageHandler query(argv[1], 0.5);
	ImageHandler scene(argv[2]);

	Finder finder(query, scene);

	Ptr<Feature2D> detector = SIFT::create();
	query.SetKeyPointsAndDescriptors(detector);
	scene.SetKeyPointsAndDescriptors(detector);

	finder.GetDescriptorMatches();
	finder.GetHomography();
	finder.RenderOutput();

    waitKey(0);
    return 0;
}

/*! @function readme */
void readme()
{
	cout << " Usage: ./FindEliza <query> <scene>" << endl;
}




