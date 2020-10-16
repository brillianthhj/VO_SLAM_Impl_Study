#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

void AspectRatio(const cv::Mat& img, const vector<float> rgb_mean_) {
  cv::Mat tmp_img(img.size(), CV_32F, cv::Scalar(0));
  img.convertTo(tmp_img, CV_32F);

  unsigned int width = img.cols;
  unsigned int height = img.rows;
  unsigned int max_wh = width < height ? height : width;

  unsigned int horz_point = int((max_wh - width) / 2);
  unsigned int vert_point = int((max_wh - height) / 2);

  float red_val = 255*rgb_mean_[0];
  float green_val = 255*rgb_mean_[1];
  float blue_val= 255*rgb_mean_[2];

  cv::Mat pad_img(max_wh, max_wh, CV_32FC3, cv::Scalar(blue_val, green_val, red_val));
  cv::imwrite("./pad_out.png", pad_img);

  tmp_img.copyTo(pad_img(cv::Rect(horz_point, vert_point, width, height)));

  cv::imwrite("./test_out.png", pad_img);
  cout << 1 <<endl;
}

int main()
{
  auto img = cv::imread(string("./test.png"), IMREAD_COLOR);

  vector<float> mean_ = {
    0.8555805436725191,
    0.7655167685055777,
    0.8145115278227488
  };
  AspectRatio(img, mean_);
  cout << 1 <<endl;
}