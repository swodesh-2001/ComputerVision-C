#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <math.h>


using namespace std;

cv::Mat detect_edge(cv::Mat image ){
// This function returns the edge detected image applied with gaussian smoothing 

cv::Mat temp_image;
cv::cvtColor(image,temp_image,cv::COLOR_BGR2GRAY);
cv::GaussianBlur(temp_image,temp_image,{5,5},1);
cv::Canny(temp_image,temp_image,50,250);

cv::Mat kernel = cv::Mat::ones(1, 1, CV_8U);
// Erosion
cv::erode(temp_image, temp_image, kernel);
// Dilation
cv::dilate(temp_image, temp_image, kernel);
return temp_image;

}

cv::Mat roi_image(cv::Mat image){
/* 
Returns the mask image with size equal to original image but with polygon filled with white and other is bla
ROI are ( 700,450) , (900,450) , (450,720) , (1280,720) 
*/

cv::Mat black_image;
black_image = cv::Mat::zeros(cv::Size(image.cols,image.rows),CV_8UC1);
// CV_8UC1 means 8 bit unsigned interger and 1 means 1 channel

std::vector<cv::Point> roi_points ;
roi_points.push_back(cv::Point(800,300));
roi_points.push_back(cv::Point(400,720));
roi_points.push_back(cv::Point(1280,720));
cv::fillConvexPoly(black_image , roi_points , {255} ); // if we use fillPoly we have to put the roi_point inside another array.
return black_image;

}



int find_x(float slope, float intercept , float y) {
    return int((y - intercept)/slope) ;
}



cv::Mat average_line(cv::Mat image , std::vector<cv::Vec4i> lines_list){

int height = image.size[0];
int width = image.size[1];
std::vector<float[2]> right_value,left_value,poly_list;
cv::Mat temp_image = image.clone();
if (!lines_list.empty()){
    float right_slope_avg = 0 ,right_intercept_avg = 0,left_slope_avg = 0,left_intercept_avg = 0 ;
    int right_count = 0, left_count = 0;
    for (int i = 0; i < lines_list.size(); i++ ){
        int x1,y1,x2,y2;  
        x1 = lines_list[i][0];
        y1 = lines_list[i][1];
        x2 = lines_list[i][2];
        y2 = lines_list[i][3];

        float slope,intercept;
        if ( (x2 - x1) == 0 ) {slope = 1 ; cout << "slope zero" << endl;}
        else { slope = (y2-y1)/float(x2-x1); }
        
        intercept = y1 - slope * x1;

        if(slope > 0){
            right_slope_avg += slope;
            right_intercept_avg += intercept;    
            right_count ++;    
        }
        else {
            left_slope_avg += slope;
            left_intercept_avg += intercept;
            left_count ++;
        }
    }

    right_slope_avg = right_slope_avg/right_count;
    left_slope_avg = left_slope_avg/left_count;
    right_intercept_avg = right_intercept_avg/right_count;
    left_intercept_avg = left_intercept_avg/left_count;

    // for creating a rectangle polyfill in the image, we will set the poly height to be from 450 to image height
    cv::Point right_start,right_end,left_start,left_end;
    right_end = {find_x(right_slope_avg,right_intercept_avg,450),450};
    right_start = {find_x(right_slope_avg,right_intercept_avg,float(height)),height};
    left_end = {find_x(left_slope_avg,left_intercept_avg,450),450};
    left_start = {find_x(left_slope_avg,left_intercept_avg,float(height)),height};

    std::vector<cv::Point> poly_points = {left_start,left_end,right_end,right_start} ;
    cv::fillConvexPoly( temp_image, poly_points , cv::Scalar(0,255,255) );
    cv::circle(temp_image,right_end,20,cv::Scalar(255,0,0),10);
    cv::circle(temp_image,right_start,20,cv::Scalar(0,0,255),10);
    cv::circle(temp_image,left_end,20,cv::Scalar(255,255,0),10);
    cv::circle(temp_image,left_start,20,cv::Scalar(255,0,255),10);


    return temp_image;
}

else{
    return image;
}

}

cv::Mat detect_lane(cv::Mat input){
    std::vector<cv::Vec4i> lines_list;  //cv::Vec4i is a vector of 4 integer, (x1,y1,x2,y2)
    cv::Mat canny_img,roi_img,merged_img, line_img;
    canny_img = detect_edge(input);
    roi_img = roi_image(input);
    cv::bitwise_and(roi_img,canny_img,merged_img);
    cv::imshow("windows2", merged_img);
    cv::HoughLinesP(merged_img,lines_list, 2 , M_PI/180 , 100 , 20 , 5);
    line_img = average_line(input,lines_list);
    return line_img;

}


void run_lane_detection(std::string video_path){

    cv::VideoCapture cap(video_path);
    int width  = int(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height  = int(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    int fps = int(cap.get(cv::CAP_PROP_FPS));

    cv::Mat img, out_val;
    cv::namedWindow("windows",cv::WINDOW_NORMAL);
    cv::resizeWindow("windows",300,300);
    cv::namedWindow("windows2",cv::WINDOW_NORMAL);
    cv::resizeWindow("windows2",300,300);
    int key_press = 0;

    // cv::VideoWriter writer;
    // int codec = cv::VideoWriter::fourcc('M','J','P','G');
    // std::string video_name = "../lane_output.avi" ;
    // writer.open(video_name,codec,fps, {width,height} , 1);


    while(true){

    cap.read(img);
    out_val = detect_lane(img);
	cv::imshow("windows", out_val);
   // writer.write(out_val);
    key_press = cv::waitKey(1) & 0xFF ;
    if( key_press == 27){
        break;
    }
    }
    cv::destroyAllWindows();
    cap.release();
}