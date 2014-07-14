#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <stdlib.h>


int element_shape = CV_SHAPE_ELLIPSE;
int max_iters = 5;
int open_close_pos = 0;
int erode_dilate_pos = 0;
IplConvKernel* element = 0;


IplImage *frame_gray, *frame_segmented;
IplImage *frame_small = NULL;

int threshold_min = 0;
int threshold_max = 255;

int main( int argc, char** argv )
{
    CvCapture* capture = 0;

    cvNamedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
    cvNamedWindow( "Frame", 1 ); 
    cvNamedWindow( "Segmented", 1 ); 
    cvNamedWindow( "Gray", CV_WINDOW_OPENGL ); 

    capture = cvCaptureFromCAM( argc == 2 ? argv[1][0] - '0' : 0 );

    if( !capture )
    {
        fprintf(stderr,"Could not initialize capturing...\n");
        fprintf(stderr,"Usage: %s <CAMERA_NUMBER>    , or \n       %s <VIDEO_FILE>\n",argv[0],argv[0]);
        return -1;
    }


    cvCreateTrackbar("Min", "Control", &threshold_min, 255, NULL); //Hue (0 - 179)
    cvCreateTrackbar("Max", "Control", &threshold_max, 255, NULL);

    while (1) {
        char key;

        IplImage* frame = cvQueryFrame( capture ); 
        frame_gray = cvCreateImage(cvSize(frame->width,frame->height), IPL_DEPTH_8U, 1) ;
        frame_segmented= cvCreateImage(cvSize(frame->width,frame->height), IPL_DEPTH_8U, 1) ; 

				//cvSmooth(frame, frame, CV_BILATERAL, 5, 5, 3, 3);
        cvCvtColor(frame, frame_gray, CV_BGR2GRAY); 
        cvThreshold(frame_gray, frame_segmented, threshold_min, threshold_max, CV_THRESH_BINARY);
				//cvAdaptiveThreshold(frame_gray, frame_segmented, threshold_max, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, 3, 5);

        //IplImage* imgThresholded = cvCreateImage(cvSize(imgHSV->width,imgHSV->height), IPL_DEPTH_8U, 1) ;

        int n = erode_dilate_pos - max_iters;
        int an = n > 0 ? n : -n;

        element = cvCreateStructuringElementEx( an*2+1, an*2+1, an, an, element_shape, 0 );
         cvErode(frame_segmented, frame_segmented,element, 2);
        cvDilate(frame_segmented, frame_segmented,element,5);

        //cvDilate(imgHSV,imgHSV,element,1);
        //cvErode(imgHSV,imgHSV,element, 1);

        //cvInRangeS(imgHSV, cvScalar(iLowH, iLowS, iLowV, 0), cvScalar(iHighH, iHighS, iHighV, 0), imgThresholded2); //Threshold the image

       // // Calculate the moments to estimate the position of the ball
       // CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
       // cvMoments(imgThresholded2, moments, 1);

       // // The actual moment values
       // double moment10 = cvGetSpatialMoment(moments, 1, 0);
       // double moment01 = cvGetSpatialMoment(moments, 0, 1);
       // double area = cvGetCentralMoment(moments, 0, 0);
       // printf("moment10 %f, moment01 %f, area %f\n", moment10, moment01, area); 
       // // Holding the last and current ball positions
       // static int posX = 0;
       // static int posY = 0;

       // int lastX = posX;
       // int lastY = posY;

       // posX = moment10/area;
       // posY = moment01/area;

       // // Print it out for debugging purposes
       // printf("position (%d,%d)\n", posX, posY);

        //if(lastX>0 && lastY>0 && posX>0 && posY>0)
        //{
        //    // Draw a yellow line from the previous point to the current point
        //    cvLine(imgHSV, cvPoint(posX, posY), cvPoint(lastX, lastY), cvScalar(0,255,255, 0), 5, 8, 0);
        //}
				printf("Min: %d, Max: %d\n", threshold_min, threshold_max);

        if( !frame )
            break;

        //IplImage *segmented_resized = cvCreateImage(cvSize(imgHSV->width/2,imgHSV->height/2), IPL_DEPTH_8U, 1);
        //IplImage *hsv_resized = cvCreateImage(cvSize(imgHSV->width/2,imgHSV->height/2), IPL_DEPTH_8U, 3);
        //cvResize(imgHSV, hsv_resized, 0);

        cvShowImage( "Segmented", frame_segmented);
        cvShowImage( "Frame", frame);
        cvShowImage( "Gray", frame_gray);
        //cvShowImage( "Segmented", segmented_resized);
        //cvShowImage( "HSV Image", hsv_resized);
        // cvShowImage( "2", imgThresholded2);
        key = (char) cvWaitKey(10);

        if( key == 27 || key == 'q' || key == 'Q' ) // 'ESC'
            break;      
    }

    cvReleaseCapture( &capture );
    cvDestroyWindow( "rect & circle" );
    return 0;
}

