#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <math.h>


using namespace std;

cv::Mat detect_edge(cv::Mat image , bool erode_dilate = false ){
// This function returns the edge detected image applied with gaussian smoothing 

cv::Mat temp_image;
cv::cvtColor(image,temp_image,cv::COLOR_BGR2GRAY);
cv::GaussianBlur(temp_image,temp_image,{5,5},1);
if(erode_dilate){
cv::Mat erode_kernel = cv::Mat::ones(10, 10, CV_8U);
cv::Mat dilate_kernel = cv::Mat::ones(2, 2, CV_8U);
// Erosion
cv::erode(temp_image, temp_image, erode_kernel);
// Dilation
cv::dilate(temp_image, temp_image, dilate_kernel);
}

cv::Canny(temp_image,temp_image,40,200);

return temp_image;

}
 
void run_edge_detection(std::string video_path, bool save_video = false){

    cv::VideoCapture cap(video_path);
    int width  = int(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height  = int(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    int fps = int(cap.get(cv::CAP_PROP_FPS));

    cv::VideoWriter writer;
    int codec = cv::VideoWriter::fourcc('M','J','P','G');
    std::string video_name = "eroded.avi" ;
    if (save_video) {
        writer.open(video_name,codec,fps, {width,height} , 1);
    }
    
    cv::Mat img, out_val,out_val2,output;
    cv::namedWindow("windows",cv::WINDOW_NORMAL);
    cv::resizeWindow("windows",500,500);
    cv::namedWindow("windows2",cv::WINDOW_NORMAL);
    cv::resizeWindow("windows2",500,500);
    cv::namedWindow("windows3",cv::WINDOW_NORMAL);
    cv::resizeWindow("windows3",500,500);
    int key_press = 0;

    while(true){
        if(!cap.read(img)){break;}
        cap.read(img);
        out_val = detect_edge(img);
        out_val2 = detect_edge(img,true);
        cv::imshow("windows", img);
        cv::imshow("windows2", out_val);
        cv::imshow("windows3", out_val2);
        cv::cvtColor(out_val2,output,cv::COLOR_GRAY2RGB); 
        if (save_video){
            writer.write(output);
        }
        
        key_press = cv::waitKey(1) & 0xFF ;
        if( key_press == 27){
            break;
        }
    }
    cv::destroyAllWindows();
    cap.release();
    if (save_video) {
        writer.release();
    }
}
