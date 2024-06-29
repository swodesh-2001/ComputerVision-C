#include "color_func.h"

int main(int argc ,char* argv[]){
    if(argc < 2){
        std::cerr << "Provide valid image path" << std::endl;
    }
    Mat img1 = imread(argv[1]);
    resize(img1,img1 , {550,300});
    show_bgr_channels(img1);
    hsv_tracking(img1);
    cmy_channels(img1);
    lab_channels(img1);
    return 0;
}
