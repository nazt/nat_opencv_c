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

        cvCreateTrackbar("LowH", "Control", &iLowH, 179, NULL); //Hue (0 - 179)
        cvCreateTrackbar("HighH", "Control", &iHighH, 179, NULL);

        cvInRangeS(imgHSV, cvScalar(iLowH, iLowS, iLowV, 0), cvScalar(iHighH, iHighS, iHighV, 0), imgThresholded2); //Threshold the image


        // YELLOW

        // cvInRangeS(imgHSV, cvScalar(20, 100, 100, 0), cvScalar(30, 255, 255, 0), imgThresholded);

        
        printf ("imgHSV.width %d\n", imgHSV->width);


        if( !frame )
            break;

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

