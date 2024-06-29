#include "func.h" 
 
int main(int argc ,char* argv[]){
    if(argc < 2){
        std::cerr << "Provide valid image path" << std::endl;
    }

cv::Mat image;
image = cv::imread(argv[1],cv::IMREAD_COLOR);  
show_image(image);
return 0;
}
 