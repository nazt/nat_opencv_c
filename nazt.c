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
    IplImage* img = cvCreateImage( cvSize( 500, 500 ), 8, 3 );
    cvNamedWindow( "rect & circle", 1 ); 

    capture = cvCaptureFromCAM( argc == 2 ? argv[1][0] - '0' : 0 );
    if( !capture )
    {
        fprintf(stderr,"Could not initialize capturing...\n");
        fprintf(stderr,"Usage: %s <CAMERA_NUMBER>    , or \n       %s <VIDEO_FILE>\n",argv[0],argv[0]);
        help();
        return -1;
    }

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
        img = frame;
        CvMat hsv;
        // CvScalar hsv_l(110,150,150); 
        // CvScalar hsv_h(130,255,255); 
        cvCvtColor(frame,img,CV_BGR2HSV);


        if( !frame )
            break;

        // IplImage* iplImg = cvQueryFrame( capture );
        // frame = iplImg;
        cvShowImage( "rect & circle", frame );
        key = (char) cvWaitKey(10);

        if( key == 27 || key == 'q' || key == 'Q' ) // 'ESC'
            break;      
    }

    cvReleaseCapture( &capture );
    cvDestroyWindow( "rect & circle" );
    return 0;
}

