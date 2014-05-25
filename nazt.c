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
    IplImage *frame_small = NULL;

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

        // IplImage* channelRed = cvCreateImage(cvGetSize(frame), 8, 1);
        // IplImage* channelGreen = cvCreateImage(cvGetSize(frame), 8, 1);
        // IplImage* channelBlue = cvCreateImage(cvGetSize(frame), 8, 1);

        // cvSplit(frame, channelBlue, channelGreen, channelRed, NULL);

        // cvAdd(channelBlue, channelGreen, channelGreen, NULL);
        // cvSub(channelRed, channelGreen, channelRed, NULL);
        // cvThreshold(channelRed, channelRed, 20, 255, CV_THRESH_BINARY);

        cvCvtColor(frame, imgHSV, CV_BGR2HSV);

        IplImage* imgThresholded = cvCreateImage(cvSize(imgHSV->width,imgHSV->height), IPL_DEPTH_8U, 1) ;
        IplImage* imgThresholded2 = cvCreateImage(cvSize(imgHSV->width,imgHSV->height), IPL_DEPTH_8U, 1) ;
        // IplImage* tmp= cvCreateImage(cvSize(imgHSV->width,imgHSV->height), IPL_DEPTH_8U, 1) ;

        int iLowH = 170;
        int iLowS = 150; 
        int iLowV = 50;

        int iHighH = 179;
        int iHighS = 255;
        int iHighV = 255;

        // cvResize(frame, )

         // cvInRangeS(frame, CV_RGB(155, 0, 0), CV_RGB(255, 130, 130), imgThresholded);
        // cvInRangeS(imgHSV, cvScalar(0,20, 100, 100, 0),       cvScalar(30, 255, 255, 0)          , imgThresholded);

 // int hl = 5, hu = 75, sl = 40, su = 245, vl = 105, vu = 175;

        // Detect a red ball
        // CvScalar hsv_min = cvScalar(hl, sl, vl, 0);
        // CvScalar hsv_max = cvScalar(hu, su, vu, 0);
        // cvInRangeS(imgHSV,   cvScalar(0, iLowS, iLowV, 0), cvScalar(10, iHighS, iHighV, 0), imgThresholded); //Threshold the image
        // cvInRangeS(imgHSV, cvScalar(iLowH, iLowS, iLowV, 0), cvScalar(iHighH, iHighS, iHighV, 0), imgThresholded); //Threshold the image
        // cvInRangeS(imgHSV, cvScalar(170, iLowS, iLowV, 0), cvScalar(180, iHighS, iHighV, 0), imgThresholded2); //Threshold the image
        // cvInRangeS(imgHSV, hsv_min, hsv_max, imgThresholded2); //Threshold the image
         cvCreateTrackbar("LowH", "Control", &iLowH, 179, NULL); //Hue (0 - 179)
         cvCreateTrackbar("HighH", "Control", &iHighH, 179, NULL);

        cvInRangeS(imgHSV, cvScalar(iLowH, iLowS, iLowV, 0), cvScalar(iHighH, iHighS, iHighV, 0), imgThresholded2); //Threshold the image


        // YELLOW

        // cvInRangeS(imgHSV, cvScalar(20, 100, 100, 0), cvScalar(30, 255, 255, 0), imgThresholded);


 // inRange(imgHSV, Scalar(0, sMin, vMin), Scalar(10, sMax, vMax), imgThresh);
// inRange(imgHSV, Scalar(170, sMin, vMin), Scalar(180, sMax, vMax), imgThresh1);

        // imgThresholded += imgThresholded2;
        // cvSum(imgThresholded, imgThresholded2, imgThresholded);
        // cvAnd(tmp, imgThresholded, imgThresholded, NULL);


        
        printf ("imgHSV.width %d\n", imgHSV->width);

        
        //cvInRangeS(imgHSV, cvScalar(20, 100, 100, 0), cvScalar(30, 255, 255, 0), frame_threadsholed2);


        if( !frame )
            break;

        // IplImage* iplImg = cvQueryFrame( capture );
        // frame = iplImg;
        // cvShowImage( "1", frame);
        cvShowImage( "2", frame);
        // cvShowImage( "1", channelRed);
        cvShowImage( "3", imgThresholded2);
        // cvShowImage( "2", imgThresholded2);
        key = (char) cvWaitKey(10);

        if( key == 27 || key == 'q' || key == 'Q' ) // 'ESC'
            break;      
    }

    cvReleaseCapture( &capture );
    cvDestroyWindow( "rect & circle" );
    return 0;
}

