#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;


void view_histogram(cv::Mat img , std::string type){
 // TAKES AN IMAGE DISPLAYS ITS HISTOGRAM

std::vector<cv::Scalar> plot_color;

if(type == "bgr"){
    plot_color.push_back(cv::Scalar(255,0,0));
    plot_color.push_back(cv::Scalar(0,255,0));
    plot_color.push_back(cv::Scalar(0,0,255));
    }

if(type == "cmy"){
    plot_color.push_back(cv::Scalar(255,255,255));
    plot_color.push_back(cv::Scalar(255,255,0));
    plot_color.push_back(cv::Scalar(0,255,255));
    }

if(type == "lab"){
    plot_color.push_back(cv::Scalar(255,255,255));
    plot_color.push_back(cv::Scalar(0,255,255));
    plot_color.push_back(cv::Scalar(255,255,0));
    }

vector<Mat> diff_channels;
 split( img, diff_channels );
 int histSize = 256;
 float range[] = { 0, 256 }; //the upper boundary is exclusive
 const float* histRange[] = { range };
 bool uniform = true, accumulate = false;
 Mat first_hist, second_hist, third_hist;
 calcHist( &diff_channels[0], 1, 0, Mat(), first_hist, 1, &histSize, histRange, uniform, accumulate );
 calcHist( &diff_channels[1], 1, 0, Mat(), second_hist, 1, &histSize, histRange, uniform, accumulate );
 calcHist( &diff_channels[2], 1, 0, Mat(), third_hist, 1, &histSize, histRange, uniform, accumulate );
 int hist_w = 512, hist_h = 400;
 int bin_w = cvRound( (double) hist_w/histSize );
 Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
 normalize(first_hist, first_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
 normalize(second_hist, second_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
 normalize(third_hist, third_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
 for( int i = 1; i < histSize; i++ )
 {
 line( histImage, Point( bin_w*(i-1), hist_h - cvRound(first_hist.at<float>(i-1)) ),
 Point( bin_w*(i), hist_h - cvRound(first_hist.at<float>(i)) ),
 plot_color[0], 2, 8, 0 );
 line( histImage, Point( bin_w*(i-1), hist_h - cvRound(second_hist.at<float>(i-1)) ),
 Point( bin_w*(i), hist_h - cvRound(second_hist.at<float>(i)) ),
 plot_color[1], 2, 8, 0 );
 line( histImage, Point( bin_w*(i-1), hist_h - cvRound(third_hist.at<float>(i-1)) ),
 Point( bin_w*(i), hist_h - cvRound(third_hist.at<float>(i)) ),
 plot_color[2], 2, 8, 0 );
 }
 imshow("Histogram", histImage );
}




void show_bgr_channels(cv::Mat img){
    // TAKES AN IMAGE AND SHOWS INDIVIDUAL CHANNEL ALONG WITH ITS HISTOGRAM

    Mat dif_channel[3];
    cv::split(img,dif_channel);
    imshow("All Channel",img);
	imshow("Blue Channel", dif_channel[0]);
    imshow("Green Channel", dif_channel[1]);
    imshow("Red Channel",dif_channel[2]);
    view_histogram(img,"bgr");
	waitKey(0);
    cv::destroyAllWindows();
}

void hsv_tracking(cv::Mat img){
     // TAKES AN IMAGE AND DOES HSV MASKING USING TRACKBAR
    int h_l = 0, s_l = 110, v_l = 153;
    int h_h = 19, s_h = 240, v_h = 255;

    int key_press = 0;
	Mat hsv_image;
	namedWindow("trackbar",WINDOW_NORMAL);
    resizeWindow("trackbar",{400,400});
    //h_l refer Hue lower threshold and h_h refer Hue higher threshold value
	// And here we have send these threshold value as a reference argument to the function because the trackbar value is updated here 
	createTrackbar("H_L", "trackbar", &h_l, 255);
	createTrackbar("S_L", "trackbar", &s_l, 255);
	createTrackbar("V_L", "trackbar", &v_l, 255);
	createTrackbar("H_H", "trackbar", &h_h, 255);
	createTrackbar("S_H", "trackbar", &s_h, 255);
	createTrackbar("V_H", "trackbar", &v_h, 255);
	while (true) {
		cvtColor(img, hsv_image, COLOR_BGR2HSV);
		inRange(hsv_image, Scalar(h_l, s_l , v_l), Scalar(h_h, s_h, v_h), hsv_image);
		imshow("Original Image", img);
		imshow("HSV Masked Image", hsv_image);
		key_press = cv::waitKey(1) & 0xFF ;
         if( key_press == 27){
              break;
             }
	}
    cv::destroyAllWindows();
}



void cmy_channels(cv::Mat img){
 // TAKES AN IMAGE AND SHOWS INDIVIDUAL CHANNEL ALONG WITH ITS HISTOGRAM IN CMY COLORSPACE
cv::Mat cmy;

vector<cv::Mat> dst;
    for(int i = 0 ; i < 4 ; i++) {
        dst.push_back(Mat(img.size(), CV_8UC1));
    }
     // Looping through each pixel
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            dst[0].at<uchar>(i, j) = 255 - img.at<Vec3b>(i, j)[2] ;  
            dst[1].at<uchar>(i, j) = 255 - img.at<Vec3b>(i, j)[1]   ; 
            dst[2].at<uchar>(i, j) = 255 - img.at<Vec3b>(i, j)[0]  ;
        }
    }
    cv::merge(dst,cmy);
    // Display results
    imshow("Original Image", img);
    imshow("c", dst[0]);
    imshow("m", dst[1]);
    imshow("y", dst[2]);
    view_histogram(cmy,"cmy");
    waitKey(0);
    cv::destroyAllWindows();

}


void lab_channels(cv::Mat img){
 // TAKES AN IMAGE AND SHOWS INDIVIDUAL CHANNEL ALONG WITH ITS HISTOGRAM IN LAB COLOR SPACE

    Mat lab_channel[3];
    Mat dst;
    cvtColor(img,dst,cv::COLOR_BGR2Lab);
    split(dst,lab_channel);
    // Display results
    imshow("Original Image", img);
    imshow("L", lab_channel[0]);
    imshow("a", lab_channel[1]);
    imshow("b", lab_channel[2]);
    view_histogram(dst,"lab");
    waitKey(0);
    cv::destroyAllWindows();

}
