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


int drawKeypointCircle (Mat& image, KeyPoint& Kpoint, Scalar color)
{
    Point2f point = Kpoint.pt;
    circle( image, point , 4, color , 1, 8, 0 );
    return 1;
}



int main(int argc, char *argv[])
{
    /** Parsing input **/
    const string keys =
        "{help h usage ?  |      | print this message     } \
         {@path           |      | path to image          } \
         {@image1Name     |1.bmp | image  for processing  } \
         {@image2Name     |2.bmp | image  for processing  } \
         {@detector       |SURF  | detector name          }";
  /** Objects creation **/
    cv::CommandLineParser parser(argc, argv, keys);
    if (parser.check())
    {
        cout << "Invalid input. Type 'help', 'h', 'usage' or '?' to get help." << endl;
        parser.printErrors();
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

    namedWindow( "image1", WINDOW_AUTOSIZE);


    cout << "Try to init " << detectorName << endl;

    Ptr<Feature2D> detector_obj;
    if (detectorName == "SURF") /** SURF creation **/
        {
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

    vector<KeyPoint> im1_kps, im2_kps;
    Mat im1_dsc, im2_dsc;
    detector_obj->detectAndCompute(
                        img1,
                        Mat(),
                        im1_kps,
                        im2_dsc);

    for (size_t i = 0; i<im1_kps.size(); i++ )
    {
        drawKeypointCircle(img1, im1_kps[i],  Scalar(0, 0 , 127));
           }
   // FlannBasedMatcher matcher; /** Flann based matcher **/


    imshow( "image1", img1 );
    cvWaitKey();
    imshow( "image1", img2 );
    cvWaitKey();
    return 0;
}
