#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <math.h>

using namespace std;
void scale_image(cv::Mat image , float sx , float sy ){
 
// Takes scaling factor for x and y direction then displays the output. The filled holes are choosen to nearest neighbour.


cv::Mat scaled_image; 
int height = image.size[0];
int width = image.size[1];  
scaled_image = cv::Mat::zeros(cv::Size(width * sx , height * sy),CV_8UC3);
std::vector<cv::Point>  unfilled_points,filled_points;
int x,y;
 
    for(int i = 0 ; i < int(height*sy) ; i++ ){
        for(int j = 0 ; j < int(width*sx) ; j++ ){
            
        x = int (float(i)/sx); 
        y = int (float(j)/sx); 

         if (x>=0 && y>=0 && x<image.size[0] &&  y<image.size[1]){
            scaled_image.at<cv::Vec3b>(int(i), int(j)) = image.at<cv::Vec3b>(x, y) ;  
         }
        }
    } 
cv::namedWindow("scaled image",cv::WINDOW_NORMAL);
cv::resizeWindow("scaled image",{500,500});
cv::imshow("scaled image",scaled_image);
cv::waitKey(0);
}