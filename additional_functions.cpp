#include <iostream>
#include <iterator>
#include <string.h>
#include <cmath>

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>


using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;


void drawKeypointCircle ( // Отрисовка особых точек цветными кругами
                         Mat& image,
                         vector<KeyPoint>& kps,
                         Scalar color
                        )
{
    for (size_t i = 0; i < kps.size(); i++ )
    {
        Point2f point = kps[i].pt;
        circle( image, point , 4, color , 1, 8, 0 );
    }

}

void drawKeypointsXmarks(
                            Mat& image,
                            vector<KeyPoint>& kps,
                            Scalar color
                           )
{
    for (size_t i = 0; i < kps.size(); i++ )
    {
        Point2f point = kps[i].pt;

        drawMarker	(image, point, color, MARKER_CROSS, 4, 1, 8 );
        //MARKER_TILTED_CROSS
    }
}

void drawMatchesLines ( // Отрисовка особых точек
                        Mat& image, //Изображение 1
                        vector<KeyPoint>& kps1, //Вектор особых точек изображения 1
                        vector<KeyPoint>& kps2, //Вектор особых точек изображения 2
                        Scalar kps1_color, //Цвет особых точек изображения 1
                        Scalar kps2_color, //Цвет особых точек изображения 2
                        Scalar lines_color //Цвет соединительных линий
                        )
{
    for (size_t i = 0; i < kps1.size(); i++ )
    {
        Point2f point1 = kps1[i].pt; Point2f point2 = kps2[i].pt;
       // circle( image, point1 , 4, kps1_color , 1, 8, 0 );
       // circle( image, point2 , 4, kps2_color , 1, 8, 0 );
       // drawMarker	(image, point2, kps2_color, MARKER_CROSS, 6, 1, 8 );
      //  line(image,point1,point2,lines_color,1,8,0);
        arrowedLine(image,point1,point2,lines_color,1,8,0);
    }

}


