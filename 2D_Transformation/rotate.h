#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <math.h>

using namespace std;


cv::Point2f rotate_point(cv::Point2f point, float angle , float a , float b ){
    float x,y;
    x =  int( (point.x- a)* cos(angle) - (point.y- b)*sin(angle));
    y =  int( (point.x - a)* sin(angle) + (point.y- b)*cos(angle));
    return cv::Point2f(x,y);
}

cv::Point2f inverse_rotate_point(cv::Point2f point, float angle, float a, float b) {
  float x,y;
    x =  int( point.x * cos(angle) + point.y *sin(angle)  +  a  );
    y =  int(  point.x * sin(-angle) + point.y*cos(angle) + b );
    return cv::Point2f(x,y);
}

void rotate_image(cv::Mat image , float angle , float a , float b ){

// angle is in counter clockwise and in degree
// a,b represent the Center of Rotation

angle = (angle * M_PI/180.); // converting degree to radian
int height = image.size[0];
int width = image.size[1];
// for the image buffer i have created image sized equal to height and width of the rectangle that bounds the rotated image
vector<cv::Point2f> corner_points = {cv::Point2f(0, 0), cv::Point2f(width - 1, 0), cv::Point2f(0, height - 1), cv::Point2f(width - 1, height - 1)};
vector<cv::Point2f> rotated_corner_points;
for (cv::Point2f point : corner_points) {
    cv::Point2f rotated_corner_point = rotate_point( point, angle , a, b);
    rotated_corner_points.push_back(rotated_corner_point);
}

// finding the minimum rectangle that can bound the warped points. It gives us the size of our warped image
cv::Rect bounding_rect = boundingRect(rotated_corner_points );
int tx = bounding_rect.x, ty = bounding_rect.y;
std::cout << " tx : " << tx << " ty : " << ty << endl;
int rotated_width = bounding_rect.width, rotated_height = bounding_rect.height;
cv::Mat rotated_image(rotated_height, rotated_width, CV_8UC3, cv::Scalar(0, 0, 0));

cv::Point2f original_point;
int x,y ;
// (a,b) is the center of the rotation 
    for(int i = 0 ; i < rotated_width ; i++ ){
        for(int j = 0 ; j < rotated_height ; j++ ){
 
        original_point = inverse_rotate_point(cv::Point2f(i + tx ,j + ty ),angle,a,b);
        x = int(original_point.x) ; 
        y = int(original_point.y) ;
        if ( x >=0 && y>=0 && x <image.size[1] &&  y<image.size[0]){
        rotated_image.at<cv::Vec3b>(j, i) = image.at<cv::Vec3b>(y, x) ; 
        }
        }
    }

cv::namedWindow("rotated image",cv::WINDOW_NORMAL);
cv::resizeWindow("rotated image",{500,500});
cv::imshow("rotated image",rotated_image); 
cv::waitKey(0);
}

 