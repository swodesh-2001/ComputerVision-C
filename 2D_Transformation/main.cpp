#include "rotate.h"
#include "scale.h"
#include "translate.h"
#include "transformation.h"

int main(int argc ,char* argv[]){
    if(argc < 2){
        std::cerr << "Provide valid image path" << std::endl;
    }
    cv::Mat translated_img,rotated_img,scaled_img,img;
    img = cv::imread(argv[1]); 
    cv::resize(img,img, {500,500});
    translate_image(img,500,500);
    scale_image(img,2,2);
    rotate_image(img , 45 , 50, 60);    
    float affine_param[6] = {3,0,100,0,1,100}; //parameter for affine transformation matrix
    affine_transform(img, affine_param);
    euclidean_transform(img , 45 , 200, 200);
    similarity_transform(img,-30,2,100,200);
    
    float projective_param[9] = {1,0,50,0,1,50,0.0001,0.001,1};
    projective_transform(img,projective_param);
    return 0;
}