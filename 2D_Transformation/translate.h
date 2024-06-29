#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <math.h>

using namespace std;

int check_val(int x){
// this functions returns the same integer if it is positive else returns 0

    if(x < 0) {
        return 0;
    }
    else {
        return x;
    }
}




void translate_image(cv::Mat image , float tx , float ty ){
// Translates the image based on translating values.
cv::Mat translated_image; 
int height = image.size[0];
int width = image.size[1];  
translated_image = cv::Mat::zeros(cv::Size(width + std::abs(tx) , height + std::abs(ty)),CV_8UC3);

int x,y;
 
    for(int i = 0 ; i < (height + abs(ty)) ; i++ ){
        for(int j = 0 ; j < (width + abs(tx)) ; j++ ){
            
        x = i - check_val(tx); 
        y = j - check_val(ty);

         if (x>=0 && y>=0 && x<image.size[0] &&  y<image.size[1]){
            translated_image.at<cv::Vec3b>(i, j) = image.at<cv::Vec3b>(x, y) ; 
         }
        }
    }
cv::namedWindow("translated image",cv::WINDOW_NORMAL);
cv::resizeWindow("translated image",{500,500});
cv::imshow("translated image",translated_image); 

cv::namedWindow("Original image",cv::WINDOW_NORMAL);
cv::resizeWindow("Original image",{500,500});
cv::imshow("Original image",image); 


cv::waitKey(0);
}