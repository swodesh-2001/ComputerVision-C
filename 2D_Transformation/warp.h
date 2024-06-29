#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <math.h>

using namespace std;

cv::Point2f homogeneous_coordinate(float x, float y, float z) {
    float x_bar = x / z;
    float y_bar = y / z; 
    return cv::Point2f(x_bar,y_bar);
}


cv::Point2f forward_warp(cv::Mat transform_matrix, float x, float y) { 
    cv::Mat temp_matrix;
    transform_matrix.convertTo(temp_matrix, CV_32FC1);
    cv::Mat point_matrix;
    point_matrix.create(3, 1, CV_32FC1); 
    point_matrix.at<float>(0,0) = x;
    point_matrix.at<float>(1,0) = y;
    point_matrix.at<float>(2,0) = 1.;
    cv::Mat warped_point = temp_matrix * point_matrix ;  
    return homogeneous_coordinate(warped_point.at<float>(0, 0),warped_point.at<float>(1, 0),warped_point.at<float>(2, 0));
}

cv::Point2f backward_warp(cv::Mat transform_matrix, float x, float y) {
    cv::Mat inverse_matrix;
    cv::invert(transform_matrix, inverse_matrix);
    inverse_matrix.convertTo(inverse_matrix, CV_32FC1);
    cv::Mat point_matrix;
    point_matrix.create(3, 1, CV_32FC1); 
    point_matrix.at<float>(0,0) = x;
    point_matrix.at<float>(1,0) = y; 
    point_matrix.at<float>(2,0) = 1.; // 1 is for z
    cv::Mat warped_point = inverse_matrix * point_matrix; 
    return homogeneous_coordinate(warped_point.at<float>(0, 0), warped_point.at<float>(1, 0), warped_point.at<float>(2, 0));
}

int check(int x){
// this functions returns the same integer if it is positive else returns 0

    if(x < 0) {
        return 0;
    }
    else {
        return x;
    }
}



cv::Mat image_warp(cv::Mat source, cv::Mat transformation_matrix) {
    int height = source.rows, width = source.cols;
    vector<cv::Point2f> corner_points = {cv::Point2f(0, 0), cv::Point2f(width - 1, 0), cv::Point2f(0, height - 1), cv::Point2f(width - 1, height - 1)};
    vector<cv::Point2f> warped_corner_points;
    for (cv::Point2f point : corner_points) {
        cv::Point2f warped_point = forward_warp(transformation_matrix, point.x, point.y);
        warped_corner_points.push_back(warped_point);
    }

    //  finding the minimum rectangle that can bound the warped points. It gives us the size of our warped image
   cv::Rect bounding_rect = boundingRect(warped_corner_points);
   int tx = bounding_rect.x, ty = bounding_rect.y;
   cout << "  tx : " << tx << "  ty  " << ty << endl;
   int warped_width = bounding_rect.width + std::abs(tx), warped_height = bounding_rect.height + std::abs(ty);
   cout << "  width : " << warped_width << "  height :   " << warped_height << endl;
   cv::Mat warped_image(warped_height , warped_width, CV_8UC3, cv::Scalar(0, 0, 0));
   
  
   int point_x,point_y;
   int shift_x = check(tx),shift_y = check(ty);
   cv::Point2f point_xy;
    for (int i = 0; i < warped_width; i++) {
        for (int j = 0; j < warped_height; j++) {
            point_xy  = backward_warp(transformation_matrix, i + tx, j + ty);
            point_x = int(point_xy.x);
            point_y = int(point_xy.y);

            if (point_x >= 0 && point_x < width && point_y >= 0 && point_y < height) {
                  warped_image.at<cv::Vec3b>(j + shift_y, i + shift_x ) = source.at<cv::Vec3b>(point_y, point_x);   
            }
        }
    }

    return warped_image;

}
