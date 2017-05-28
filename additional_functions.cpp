#include <iostream>
#include <iterator>
#include <string.h>

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>


using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;


void drawKeypointCircle (Mat& image,  vector<KeyPoint>& kps, Scalar color)
{
    for (size_t i = 0; i < kps.size(); i++ )
    {
        Point2f point = kps[i].pt;
        circle( image, point , 4, color , 1, 8, 0 );
    }

}

