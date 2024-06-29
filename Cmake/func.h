#include <opencv2/highgui.hpp>
#include <iostream>

int show_image(cv::Mat image){
     if(! image.data)
        {
            std::cout<<"No image file present" << std::endl;
            return 0;
        }    
        
    cv::namedWindow("image", cv::WINDOW_NORMAL);
    cv::resizeWindow("image",100,20);
    cv::imshow("image", image);
    cv::waitKey(0);
    return 1;
}