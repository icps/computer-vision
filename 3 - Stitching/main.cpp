#include <QCoreApplication>

#include <stdio.h>
#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/stitching/stitcher.hpp"

using namespace cv;
using namespace std;

vector<Mat> imgs;


/** @function main */
int main( )
{
    // Load the images
     Mat image1 = imread("/home/isadora/Imagens/ic1.jpg");
     Mat image2 = imread("/home/isadora/Imagens/ic2.jpg");
     Mat image3 = imread("/home/isadora/Imagens/ic3.jpg");
     Mat image4 = imread("/home/isadora/Imagens/ic4.jpg");

     // Juntar ic1 e ic2
     imgs.push_back(image1);
     imgs.push_back(image2);

     Mat P1;
     Stitcher stitcher = Stitcher::createDefault();
     Stitcher::Status status1 = stitcher.stitch(imgs, P1);

     namedWindow("Teste", WINDOW_NORMAL);
     imshow("Teste", P1);
     imwrite( "/home/isadora/Imagens/stitch-ic1_ic2.jpg", P1);

     //Juntar ic3 e ic4
     imgs.pop_back();
     imgs.pop_back();

     imgs.push_back(image3);
     imgs.push_back(image4);

     Mat P2;
     status1 = stitcher.stitch(imgs, P2);

     namedWindow("Teste1", WINDOW_NORMAL);
     imshow("Teste1", P2);
     imwrite( "/home/isadora/Imagens/stitch-ic3_ic4.jpg", P2);

     //Juntar P1 e P2
     imgs.pop_back();
     imgs.pop_back();

     imgs.push_back(P1);
     imgs.push_back(P2);

     Mat P1P2;
     status1 = stitcher.stitch(imgs, P1P2);

     namedWindow("Teste2", WINDOW_NORMAL);
     imshow("Teste2", P1P2);
     imwrite( "/home/isadora/Imagens/stitch-P1_P2.jpg", P1P2);

     //Cumulativo
     // P1 + ic3
     imgs.pop_back();
     imgs.pop_back();

     imgs.push_back(P1);
     imgs.push_back(image3);

     Mat finalP;
     status1 = stitcher.stitch(imgs, finalP);

     // P1 + ic3 + ic4
     imgs.pop_back();
     imgs.pop_back();

     imgs.push_back(finalP);
     imgs.push_back(image4);

     Mat cumuP;
     status1 = stitcher.stitch(imgs, cumuP);

     namedWindow("Teste3", WINDOW_NORMAL);
     imshow("Teste3", cumuP);
     imwrite( "/home/isadora/Imagens/cumulative-stitch.jpg", cumuP);

     waitKey(0);
     return 0;
 }




