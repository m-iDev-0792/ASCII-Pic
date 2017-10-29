//
//  main.cpp
//  ASCII-Pic
//
//  Created by 何振邦 on 2017/10/29.
//  Copyright © 2017年 何振邦. All rights reserved.
//

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;
void resize(Mat &imagesrc,int wsize=80){
    float fScale=(float)wsize/imagesrc.cols;
    Size dsize = Size((int)imagesrc.cols*fScale, (int)imagesrc.rows*fScale);
    Mat imagedst = Mat(dsize, CV_8UC1);
    resize(imagesrc, imagedst, dsize);
    imagesrc=imagedst;
}
int main(int argc, const char * argv[]) {
    string pix[]={" ",".","^","-","+","V","A","@"};
    string path;
    cout<<"enter a image filepath to covert:";
    cin>>path;
    Mat img=imread(path.c_str());
    if(img.empty()){
        cout<<"ERROR:image did not loaded!!!"<<endl;
        return 1;
    }
    resize(img);
    Mat grayImg;
    if (img.channels()==3) {
        cvtColor(img, grayImg, CV_RGB2GRAY);
    }else if (img.channels()==4){
        cvtColor(img, grayImg, CV_RGBA2GRAY);
    }else if (img.channels()==1){
        grayImg=img.clone();
    }else{
        cout<<"ERROR:unsupported image format!!!"<<endl;
        return 2;
    }
    
    const int imgHeight=grayImg.rows;
    const int imgWidth=grayImg.cols;


    for(int j=0;j<imgHeight;++j){
        for(int i=0;i<imgWidth;++i){
            int pixel=(grayImg.at<uchar>(j,i))/32;
            cout<<pix[pixel];
        }
        cout<<endl;
    }
    return 0;
}
