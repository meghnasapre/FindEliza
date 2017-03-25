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

	ImageHandler query(argv[1], 0.75);
	ImageHandler scene(argv[2]);

	Finder finder(&query, &scene);
	query.SetKeyPointsAndDescriptors(finder.GetDetector());
	vector<KeyPoint> kp = query.GetKeyPoints();
	cout << "Query KeyPoints size: " << kp.size() << endl;

	scene.SetKeyPointsAndDescriptors(finder.GetDetector());
	vector<KeyPoint> sp = scene.GetKeyPoints();
	cout << "Scene KeyPoints size: " << sp.size() << endl;

	vector<DMatch> desc = finder.GetDescriptorMatches();
	cout << "desc size: " << desc.size() << endl;
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




