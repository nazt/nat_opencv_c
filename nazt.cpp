#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <stdlib.h>


void help()
{
    printf("\nThis program demonstrates finding the minimum enclosing box or circle of a set\n"
        "of points using functions: minAreaRect() minEnclosingCircle().\n"
        "Random points are generated and then enclosed.\n"
        "Call:\n"
        "./minarea\n");
}



int main( int argc, char** argv )
{
    CvCapture* capture = 0;

    cvNamedWindow( "1", 1 ); 
    cvNamedWindow( "2", 2 ); 
    cvNamedWindow( "3", 3 ); 
    capture = cvCaptureFromCAM( argc == 2 ? argv[1][0] - '0' : 0 );
    IplImage *imgHSV;

    if( !capture )
    {
        fprintf(stderr,"Could not initialize capturing...\n");
        fprintf(stderr,"Usage: %s <CAMERA_NUMBER>    , or \n       %s <VIDEO_FILE>\n",argv[0],argv[0]);
        help();
        return -1;
    }

    while (1) {
        char key;
        IplImage* frame = cvQueryFrame( capture ); 
        imgHSV = cvCreateImage(cvSize(frame->width,frame->height), IPL_DEPTH_8U, 3) ;
        cvCvtColor(frame, imgHSV, CV_BGR2HSV);

        IplImage* imgThresholded = cvCreateImage(cvSize(imgHSV->width,imgHSV->height), IPL_DEPTH_8U, 1) ;
        IplImage* imgThresholded2 = cvCreateImage(cvSize(imgHSV->width,imgHSV->height), IPL_DEPTH_8U, 1) ;
        IplImage* tmp= cvCreateImage(cvSize(imgHSV->width,imgHSV->height), IPL_DEPTH_8U, 1) ;

 int iLowH = 0;
 int iHighH = 179;

  int iLowS = 0; 
 int iHighS = 255;

  int iLowV = 0;
 int iHighV = 255;
        inRange(imgHSV, cvScalar(iLowH, iLowS, iLowV, 0), cvScalar(iHighH, iHighS, iHighV, 0), imgThresholded); //Threshold the image
        // cvInRangeS(imgHSV, cvScalar(20, 100, 100, 0),       cvScalar(30, 255, 255, 0)          , imgThresholded);

        // cvInRangeS(imgHSV, cvScalar(0, iLowS, iLowV, 0), cvScalar(10, iHighS, iHighV, 0), imgThresholded); //Threshold the image
        // cvInRangeS(imgHSV, cvScalar(170, iLowS, iLowV, 0), cvScalar(180, iHighS, iHighV, 0), imgThresholded2); //Threshold the image

 // inRange(imgHSV, Scalar(0, sMin, vMin), Scalar(10, sMax, vMax), imgThresh);
// inRange(imgHSV, Scalar(170, sMin, vMin), Scalar(180, sMax, vMax), imgThresh1);

        // imgThresholded += imgThresholded2;
        cvXor(imgThresholded, imgThresholded2, imgThresholded, NULL);
        // cvAnd(tmp, imgThresholded, imgThresholded, NULL);


        
        printf ("imgHSV.width %d\n", imgHSV->width);

        
        //cvInRangeS(imgHSV, cvScalar(20, 100, 100, 0), cvScalar(30, 255, 255, 0), frame_threadsholed2);


        if( !frame )
            break;

        // IplImage* iplImg = cvQueryFrame( capture );
        // frame = iplImg;
        // cvShowImage( "1", frame);
        cvShowImage( "3", imgHSV);
        cvShowImage( "2", imgThresholded);
        key = (char) cvWaitKey(10);

        if( key == 27 || key == 'q' || key == 'Q' ) // 'ESC'
            break;      
    }

    cvReleaseCapture( &capture );
    cvDestroyWindow( "rect & circle" );
    return 0;
}

