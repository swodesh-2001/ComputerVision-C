#include "warp.h"


void affine_transform(cv::Mat image , float parameters[]){
 
    double data[] = {
         parameters[0], parameters[1], parameters[2],
         parameters[3] , parameters[4], parameters[5],
        0, 0, 1
    };
    // creating trasnformation matrix
    cv::Mat transformation_matrix(3, 3, CV_64F, data);
    cv::Mat transformed_image;
    transformed_image = image_warp(image,transformation_matrix);
    cv::namedWindow("Affine transformed image",cv::WINDOW_NORMAL);
    cv::resizeWindow("Affine transformed image",{500,500});
    cv::imshow("Affine transformed image",transformed_image); 
    cv::waitKey(0);

}

void similarity_transform(cv::Mat image , float theta , float s , float tx, float ty){
 
   float angle = (theta * M_PI/180.); 
    double data[] = {
         s*cos(angle), -s * sin(angle), tx,
         s* sin(angle) , s * cos(angle), ty,
        0, 0, 1
    };
    // creating trasnformation matrix
    cv::Mat transformation_matrix(3, 3, CV_64F, data);
    cv::Mat transformed_image;
    transformed_image = image_warp(image,transformation_matrix);
    cv::namedWindow("Similarity transformed image",cv::WINDOW_NORMAL);
    cv::resizeWindow("Similarity transformed image",{500,500});
    cv::imshow("Similarity transformed image",transformed_image);
    cv::waitKey(0);

}

void euclidean_transform(cv::Mat image , float theta, float tx, float ty){
    double angle = (theta * M_PI/180.); 
    double data[] = {
         cos(angle), -sin(angle), tx,
         sin(angle) , cos(angle), ty,
        0, 0, 1
    };
    // creating trasnformation matrix
    cv::Mat transformation_matrix(3, 3, CV_64F, data);
    cv::Mat transformed_image;
    transformed_image = image_warp(image,transformation_matrix);
    cv::namedWindow("Eucliidean transformed image",cv::WINDOW_NORMAL);
    cv::resizeWindow("Eucliidean transformed image",{500,500});
    cv::imshow("Eucliidean transformed image",transformed_image);
 
    cv::waitKey(0);

}



void projective_transform(cv::Mat image , float parameters[]){
 
    double data[] = {
         parameters[0], parameters[1], parameters[2],
         parameters[3] , parameters[4], parameters[5],
         parameters[6] , parameters[7], parameters[8]
    };
    // creating trasnformation matrix
    cv::Mat transformation_matrix(3, 3, CV_64F, data);
    cv::Mat transformed_image;
    transformed_image = image_warp(image,transformation_matrix);
    cv::namedWindow("Projective transformed image",cv::WINDOW_NORMAL);
    cv::resizeWindow("Projective transformed image",{500,500});
    cv::imshow("Projective transformed image",transformed_image);
    cv::waitKey(0);

}

 