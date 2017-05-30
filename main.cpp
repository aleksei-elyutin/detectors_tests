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


void drawKeypointCircle (Mat& image,  vector<KeyPoint>& kps, Scalar color);

const string keys =
    "{help h usage ?  |      | print this message     } \
     {@path           |      | path to image          } \
     {@image1Name     |      | image  for processing  } \
     {@image2Name     |      | image  for processing  } \
     {@detector       |SURF  | detector name          }";

int main(int argc, char *argv[])
{
    /** Parsing input **/

  /** Objects creation **/
    cv::CommandLineParser parser(argc, argv, keys);
    if (!parser.check())
    {
        cout << "Invalid input. Type 'help', 'h', 'usage' or '?' to get help." << endl;
        parser.printErrors();
        return -1;
    }
    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }
    string inputPath = parser.get<string>("@path");
    string inputImage1 = parser.get<string>("@image1Name");
    string inputImage2 = parser.get<string>("@image2Name");
    string detectorName = parser.get<string>("@detector");

    string buffer = inputPath; buffer += inputImage1;
    Mat img1 = imread(buffer);
    buffer.clear();
    buffer = inputPath;  buffer += inputImage2;
    Mat img2 = imread(buffer);
    if( img1.empty() |  img1.empty() )
    {
        if( img1.empty()) cout << "Error loading image 1 \n" << endl;
        if( img2.empty()) cout << "Error loading image 2 \n" << endl;
        return -1;
    }


    namedWindow( "image1", WINDOW_AUTOSIZE);


    cout << "Try to init " << detectorName << endl;

    Ptr<Feature2D> detector_obj;
    if (detectorName == "SURF") /** SURF creation **/
        {
      //  detector_obj = SURF::create(); //defaults
            detector_obj = SURF::create(
                        2000, // hessianThreshold - порог гессиана
                        1, // nOctaves - число октав
                        3, // nOctaveLayers - число уровней внутри каждой октавы
                        false, // использовать расширенный дескриптор
                        true); // использовать вычисление ориентации
            cout << "SURF" << " - OK." << endl;
         }
    if (detectorName == "KAZE")  /** KAZE creation **/
        {
            detector_obj = KAZE::create(); //defaults
            cout << "KAZE" << " - OK." << endl;
        }
    if (detectorName == "AKAZE")  /** AKAZE creation **/
        {
            detector_obj = AKAZE::create(); //defaults
            cout << "AKAZE" << " - OK." << endl;
        }
    if (detectorName == "BRISK")  /** BRISK creation **/
        {
            detector_obj = BRISK::create(); //defaults
            cout << "BRISK" << " - OK." << endl;
        }
    if (detectorName == "FAST")  /** FAST creation **/
        {
            detector_obj = FastFeatureDetector::create(); //defaults
             cout << "FAST" << " - OK." << endl;
        }

    vector<KeyPoint> im1_kps, im2_kps, im1_kps_matched, im2_kps_matched;
    Mat im1_dsc, im2_dsc;

    double timestamp1, timestamp2;  //Временные метки ***
    timestamp1   = (double)getTickCount();
    detector_obj->detectAndCompute( img1, Mat(), im1_kps, im1_dsc);
    timestamp2 = (double)getTickCount();
    cout << "Time for detection and compution of frame 1: " << (timestamp2-timestamp1)/getTickFrequency() << endl;
    cout << "Number of features for image 1: " << im1_kps.size() << endl;
    timestamp1   = (double)getTickCount();
    detector_obj->detectAndCompute( img2, Mat(), im2_kps, im2_dsc);
    timestamp2 = (double)getTickCount();
    cout << "Time for detection and compution of frame 2: " << (timestamp2-timestamp1)/getTickFrequency() << endl;
    cout << "Number of features for image 2: " << im2_kps.size() << endl;

    Ptr<DescriptorMatcher> matcher;
    matcher = DescriptorMatcher::create("BruteForce");
    vector< vector< DMatch > > matches;
    matcher->knnMatch(im1_dsc, im2_dsc, matches, 1);

    cout << "Number of matched features: " << matches.size() << endl;

//     for( size_t i = 0; i < matches.size(); i++ )
//        {
//           //-- Get the keypoints from the good matches
//           im1_kps_matched.push_back( im1_kps[ matches[i].queryIdx ] );
//           //previous_frame_matched_points.push_back( previous_frame_keypoints[ matches[i].queryIdx ].pt );
//           //cout <<  matches[i].queryIdx << "     ";
//           im2_kps_matched.push_back( im2_kps[ matches[i].trainIdx ] );
//           //current_frame_matched_points.push_back( current_frame_keypoints[ matches[i].trainIdx ].pt );
//           //cout <<  matches[i].trainIdx << "     " << endl;
//        }
//    drawKeypointCircle(img1, im2_kps_matched, Scalar(0, 255 , 0));
    imshow( "image1", img1 );
    cvWaitKey(4000);
    //imshow( "image1", img2 );
    //cvWaitKey();
    return 0;
}
