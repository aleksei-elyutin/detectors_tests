#include <iostream>
#include <iterator>
#include <string.h>

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/calib3d.hpp>


using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

    /** Functions protorypes */
void drawKeypointCircle ( // Отрисовка особых точек цветными кругами
                         Mat& image,
                         vector<KeyPoint>& kps,
                         Scalar color = Scalar(0, 0 , 255)
                        );
void drawMatchesLines ( // Отрисовка особых точек
                        Mat& image, //Изображение 1
                        vector<KeyPoint>& kps1, //Вектор особых точек изображения 1
                        vector<KeyPoint>& kps2, //Вектор особых точек изображения 2
                        Scalar kps1_color = Scalar(255, 0 , 0), //Цвет особых точек изображения 1
                        Scalar kps2_color = Scalar(0, 255 , 0), //Цвет особых точек изображения 2
                        Scalar lines_color = Scalar(0, 0 , 255) //Цвет соединительных линий
                        );
    /*************************/
const string keys =
    "{help h usage ?  |      | print this message      } \
     {@path           |      | path to image           } \
     {@image1Name     |      | image  for processing   } \
     {@image2Name     |      | image  for processing   } \
     {@detector       |SURF  | detector name           } \
     {distance        |      | detector name           } \
     {o output        |      | detector name           }";

int main(int argc, char *argv[])
{
    /** Parsing input **/  
    cv::CommandLineParser parser(argc, argv, keys);
    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    } //Отобразить информационное сообщение
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
        if( img1.empty()) if (parser.has("output")) cout << "Error loading image 1" << endl;
        if( img2.empty()) if (parser.has("output")) cout << "Error loading image 2" << endl;
        return -1;
    }
    else
    {
        if (parser.has("output")) cout << "Loaded " << inputImage1 << " as image 1" << endl;
        if (parser.has("output")) cout << "Loaded " << inputImage2 << " as image 2" << endl;
    }

    /** Objects creation **/
    if (parser.has("output")) namedWindow( "image1", WINDOW_AUTOSIZE); //Создание окна

    if (parser.has("output")) cout << "Try to init " << detectorName << "... "<< endl;
    Ptr<Feature2D> detector_obj;
    Ptr<DescriptorMatcher> matcher;
    matcher = DescriptorMatcher::create("BruteForce");
    double thresh;

    if ((detectorName == "SURF")  |
        (detectorName == "AKAZE") |
        (detectorName == "BRISK") |
        (detectorName == "ORB") |
        (detectorName == "SIFT")   )
    {
        if (detectorName == "SURF") /** SURF creation **/
            {
                thresh = 0.2;
                detector_obj = SURF::create(); //defaults
                /*detector_obj = SURF::create(
                            300, // hessianThreshold - порог гессиана
                            4, // nOctaves - число октав
                            3, // nOctaveLayers - число уровней внутри каждой октавы
                            false, // использовать расширенный дескриптор
                            true); // использовать вычисление ориентации*/
                if (parser.has("output")) cout << "SURF" << " - OK." << endl;
             }
        if (detectorName == "AKAZE")  /** AKAZE creation **/
            {
                thresh = 200;
                detector_obj = AKAZE::create(); //defaults
                if (parser.has("output")) cout << "AKAZE" << " - OK." << endl;
            }
        if (detectorName == "BRISK")  /** BRISK creation **/
            {
                thresh = 600;
                detector_obj = BRISK::create(); //defaults
                if (parser.has("output")) cout << "BRISK" << " - OK." << endl;
            }
        if (detectorName == "ORB")  /** FAST creation **/
            {
        thresh = 600;
                detector_obj = ORB::create(); //defaults
                 if (parser.has("output")) cout << "ORB" << " - OK." << endl;
            }
        if (detectorName == "SIFT")  /** FAST creation **/
            {
                 thresh = 600;
                detector_obj = SIFT::create(); //defaults
                 if (parser.has("output")) cout << "SIFT" << " - OK." << endl;
            }
    }
    else
    {
        cout << "Incorrect detector name." << endl;
        return -1;
    }

    vector<KeyPoint> im1_kps, im2_kps, im1_kps_matched, im2_kps_matched,
        im1_inliers, im2_inliers, im1_outliers, im2_outliers;


    Mat im1_dsc, im2_dsc, mask;

    vector < vector< DMatch > > matches;
    vector <DMatch> single_matches;
    vector <Point2f> im1_pts, im2_pts;


        /** Main pipeline **/


    double timestamp1, timestamp2;  //Временные метки ***
    timestamp1   = (double)getTickCount();
    detector_obj->detectAndCompute( img1, Mat(), im1_kps, im1_dsc);
    timestamp2 = (double)getTickCount();

        if (parser.has("output"))
        cout << "Time for detection and compution of frame 1: " << (timestamp2-timestamp1)/getTickFrequency() << endl;
    if (parser.has("output"))
        cout << "Number of features for image 1: " << im1_kps.size() << endl;

    //    timestamp1   = (double)getTickCount();
    detector_obj->detectAndCompute( img2, Mat(), im2_kps, im2_dsc);
   // timestamp2 = (double)getTickCount();

        if (parser.has("output"))
        cout << "Time for detection and compution of frame 2: " << (timestamp2-timestamp1)/getTickFrequency() << endl;
    if (parser.has("output"))
        cout << "Number of features for image 2: " << im2_kps.size() << endl;



        /** Matching **/
    matcher->knnMatch(im1_dsc, im2_dsc, matches,4);
    double distance_thresh = parser.get<double>("distance");;
   // matcher->radiusMatch(im1_dsc, im2_dsc, matches, thresh);
    size_t size = matches.size();
    for( size_t i = 0; i < size; i++ )
    {
        if (!matches[i].empty())
        {           
            vector <DMatch> multi_matches = matches[i];
            size_t size2 = multi_matches.size();
            double min_distance  = multi_matches.front().distance;
            int n = 0;
            for( size_t j = 0; j < size2; j++ )
            {
               if  (multi_matches[j].distance < min_distance) n = j;
            }
            DMatch tempDM = multi_matches[n];
            if  (tempDM.distance < distance_thresh)
            {
                single_matches.push_back(tempDM);
                im1_kps_matched.push_back( im1_kps[ tempDM.queryIdx ] );
                im2_kps_matched.push_back( im2_kps[ tempDM.trainIdx ] );
                im1_pts.push_back( im1_kps[ tempDM.queryIdx ].pt );
                im2_pts.push_back( im2_kps[ tempDM.trainIdx ].pt );
            }

        }

    }

         /** Selecting inliers with RANSAC **/
   // vector<int> mask;
    //Mat H = findHomography( im1_pts, im2_pts, RANSAC, 3,mask);
    Mat H = estimateAffinePartial2D(im1_pts, im2_pts, mask, RANSAC);

    timestamp2 = (double)getTickCount();
    //cout << "Mask:" << endl << mask << endl;

    size = mask.rows;

    for( int i = 0; i < mask.rows; i++ ) //Отделение inlier и outlier
    {
        DMatch tempDM = single_matches[i];
        if ( mask.at<int>(i,1) )
        {
            im1_inliers.push_back( im1_kps[ tempDM.queryIdx ] );
            im2_inliers.push_back( im2_kps[ tempDM.trainIdx ] );
        }
        else
        {
            im1_outliers.push_back( im1_kps[ tempDM.queryIdx ] );
            im2_outliers.push_back( im2_kps[ tempDM.trainIdx ] );
        }

    }


    double inlier_ratio = im1_inliers.size() * 1.0 /im1_kps_matched.size();

    if (parser.has("output"))
    {
        cout << "Matches: " << single_matches.size() << endl;
        cout << "Inliers: " <<  im1_inliers.size() << endl;
        cout << "Outliers: " << im1_outliers.size() << endl;
        cout << "Inliers ratio: " << inlier_ratio << endl;
        cout << "Affine matrix:" << endl << H << endl;

        Mat im_result;// = img1.clone();

        addWeighted(img1 , 0.5, img2, 0.5, 0.0, im_result);
        drawMatchesLines (im_result,im1_inliers,im2_inliers, Scalar(255, 255 , 0),
                                                             Scalar(255, 255 , 0),
                                                             Scalar(0, 255 , 0));
        drawMatchesLines (im_result,im1_outliers,im2_outliers, Scalar(0, 255 , 255),
                                                               Scalar(0 , 255 , 255),
                                                               Scalar(0, 0 , 255));
        imshow( "image1", im_result );
        cvWaitKey();
        //imshow( "image1", img2 );
        //cvWaitKey();
     }
     else
     {
       // cout << "detectorName \t inputImage2 \t im1_kps \t im2_kps \t matched \t inliers \t outliers \t ratio" << endl;
        //cout << detectorName << "\t";
        //cout << inputImage2 << "\t";
        cout << (timestamp2-timestamp1)/getTickFrequency() << ", ";
        cout << im2_kps.size() << ", ";
        cout << im1_kps_matched.size()  << ", ";
        cout << im1_inliers.size() << ", " ;
        cout << im1_outliers.size() << ", ";
        cout << inlier_ratio << endl;
        cout << format(H, Formatter::FMT_CSV   ) << endl;
     }
    return 0;
}
