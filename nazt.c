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

 int iLowH = 170;
 int iHighH = 179;

  int iLowS = 150; 
 int iHighS = 255;

  int iLowV = 60;
 int iHighV = 255;

IplConvKernel* element = 0;
int element_shape = CV_SHAPE_ELLIPSE;
int max_iters = 5;
int open_close_pos = 0;
int erode_dilate_pos = 0;



int main( int argc, char** argv )
{
    CvCapture* capture = 0;
    IplImage* img =     cvCreateImage( cvSize( 500, 500 ), IPL_DEPTH_8U, 3 );
    IplImage* img_hsv = cvCreateImage( cvSize( 500, 500 ), IPL_DEPTH_8U, 3 );
    IplImage* img_dst = cvCreateImage( cvSize( 500, 500 ), IPL_DEPTH_8U, 3 );
    IplImage* img_tmp = cvCreateImage( cvSize( 500, 500 ), IPL_DEPTH_8U, 3 );
    IplImage* hsv_frame = cvCreateImage( cvSize( 500, 500 ), IPL_DEPTH_8U, 3 );

    cvNamedWindow( "rect & circle", 1 ); 
    cvNamedWindow( "rect & circle", 2 ); 
    cvNamedWindow( "rect & circle", 3 ); 

    capture = cvCaptureFromCAM( argc == 2 ? argv[1][0] - '0' : 0 );
    if( !capture )
    {
        fprintf(stderr,"Could not initialize capturing...\n");
        fprintf(stderr,"Usage: %s <CAMERA_NUMBER>    , or \n       %s <VIDEO_FILE>\n",argv[0],argv[0]);
        help();
        return -1;
    }
       //int hl = 100, hu = 115, sl = 95, su = 135, vl = 115, vu = 200;
        int hl = 5, hu = 75, sl = 40, su = 245, vl = 105, vu = 175;
        

    while (1) {
        char key;
        // int i, count = rand()%100 + 1;
        // CvPoint pt0, pt;
        // CvBox2D box;
        // CvPoint2D32f box_vtx[4];
        // CvPoint2D32f center;
        // CvPoint icenter;
        // float radius;  

        // CvPoint* points = (CvPoint*)malloc( count * sizeof(points[0]));
        // CvMat pointMat = cvMat( 1, count, CV_32SC2, points );

        // for( i = 0; i < count; i++ )
        // {
        //     pt0.x = rand() % (img->width/2) + img->width/4;
        //     pt0.y = rand() % (img->height/2) + img->height/4;
        //     points[i] = pt0;
        // } 
        IplImage* frame = 0;

        frame = cvQueryFrame( capture );
        hsv_frame = cvCreateImage(cvSize(frame->width,frame->height), IPL_DEPTH_8U, 3) ;
        // IplImage *temp= cvCreateImage(cvSize(frame->width,frame->height), IPL_DEPTH_8U, 1) ;
        // img_hsv = frame;
        // ต้อง assign img_hsv ให้เป็น frame ด้วย
        // cvResize(frame, img_hsv, CV_INTER_LINEAR);
        // cvResize(frame, img_dst, CV_INTER_LINEAR);
        // cvResize(frame, hsv_frame, CV_INTER_LINEAR);
        // cvCvtColor(hsv_frame, hsv_frame, CV_RGB2HSV);
        cvCvtColor(hsv_frame, hsv_frame, CV_BGR2HSV);

        CvScalar hsv_min = cvScalar(150, 84, 130, 0);
        CvScalar hsv_max = cvScalar(358, 256, 255, 0);
        hsv_min = cvScalar(hl, sl, vl, 0);
        hsv_max = cvScalar(hu, su, vu, 0);
        // CvScalar hsv_min = cvScalar(hl, sl, vl, 0);
        // CvScalar hsv_max = cvScalar(hu, su, vu, 0);

        // cvCvtColor(frame, hsv_frame, CV_RGB2GRAY);


        // IplImage* frame_threadsholed = cvCreateImage(cvSize(hsv_frame->width,hsv_frame->height), IPL_DEPTH_8U, 1) ;
        IplImage* frame_threadsholed2 = cvCreateImage(cvSize(hsv_frame->width,hsv_frame->height), IPL_DEPTH_8U, 1) ;
        
// cvThreshold(const CvArr* src, CvArr* dst, double threshold, double max_value, int threshold_type)   
        printf ("hsv_frame.width %d\n", hsv_frame->width);
        printf ("img_hsv.width %d\n", img_hsv->width);

        // cvThreshold(hsv_frame, hsv_frame, 0, 255, CV_THRESH_BINARY_INV + CV_THRESH_OTSU);
        // cvMorphologyEx(const CvArr* src, CvArr* dst, CvArr* temp, IplConvKernel* element, int operation, int iterations=1 )
        // cvMorphologyEx(hsv_frame, hsv_frame, temp, NULL, CV_MOP_BLACKHAT, 6 );

        // cvCvtColor(img_hsv, img_dst,CV_BGR2HSV);
        // cvThreshold(const CvArr* src, CvArr* dst, double threshold, double max_value, int threshold_type)


        // int rotation = 128 - 255; // 255 = red
        // cvAddS(hsv_frame, cvScalar(rotation, 0, 0, 0), hsv_frame, 0);

        // cvInRangeS(hsv_frame, cvScalar(0, 10, 255, 0), cvScalar(0, 100, 255, 0), frame_threadsholed);
        // cvInRangeS(hsv_frame, cvScalar(0, 135, 135, 0), cvScalar(20, 255, 255, 0), frame_threadsholed);
        // cvInRangeS(hsv_frame, cvScalar(159, 135, 135, 0), cvScalar(179, 255, 255, 0), frame_threadsholed2);
        // cvInRangeS(hsv_frame, cvScalar(20, 100, 100, 0), cvScalar(30, 255, 255, 0), frame_threadsholed2);
        // cvInRangeS(hsv_frame, cvScalar(iLowH, iLowS, iLowV, 0), cvScalar(iHighH, iHighS, iHighV, 0), frame_threadsholed2);

        // cvInRangeS(hsv_frame, hsv_min, hsv_max, frame_threadsholed2);
        cvErode(hsv_frame,hsv_frame,element, 1);
        cvDilate(hsv_frame,hsv_frame,element,1);

        cvDilate(hsv_frame,hsv_frame,element,1);
        cvErode(hsv_frame,hsv_frame,element, 1);
        
        cvInRangeS(hsv_frame, cvScalar(20, 100, 100, 0), cvScalar(30, 255, 255, 0), frame_threadsholed2);

        int n = erode_dilate_pos - max_iters;
        int an = n > 0 ? n : -n;

        element = cvCreateStructuringElementEx( an*2+1, an*2+1, an, an, element_shape, 0 );


        // cvErode(frame_threadsholed2, frame_threadsholed2, getStructuringElement(MORPH_ELLIPSE, cvSize(5, 5)), 1);
        // cvDilate(frame_threadsholed2, frame_threadsholed2, getStructuringElement(CV_SHAPE_ELLIPSE, cvSize(5, 5)) ); 


        // cvSmooth( frame_threadsholed2, frame_threadsholed2, CV_GAUSSIAN, 9, 9, 0, 0);
        // cvErode()
        
        // cvErode(const CvArr* src, CvArr* dst, IplConvKernel* element=NULL, int iterations=1)
        // cvCreateStructuringElementEx
        // cvInRange(, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

        // gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

        // cvOr(frame_threadsholed, frame_threadsholed2, frame_threadsholed, 0);

        // cvInRangeS(src, cvScalar(100, 135, 135), cvScalar(140, 255, 255), threshold);

        if( !frame )
            break;

        // IplImage* iplImg = cvQueryFrame( capture );
        // frame = iplImg;
        cvShowImage( "1", frame);
        cvShowImage( "3", hsv_frame);
        cvShowImage( "2", frame_threadsholed2);
        key = (char) cvWaitKey(10);

        if( key == 27 || key == 'q' || key == 'Q' ) // 'ESC'
            break;      
    }

    cvReleaseCapture( &capture );
    cvDestroyWindow( "rect & circle" );
    return 0;
}

