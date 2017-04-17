#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#define height 1200
#define width 1200

using namespace cv;
using namespace std;

Point2f pos2pix(const Point2f & pos);

int main()
{
	cout << "Built with OpenCV " << CV_VERSION << endl;
	Mat in = imread("/home/nicolas/Downloads/dynboard.png");
	
	Mat M( 3, 3, CV_32FC1 );
	Mat out( in.rows, in.cols, in.type() );

	Point2f	inPoints[4];
	Point2f	outPoints[4];
	
	inPoints[0] = pos2pix( Point2f( -1, -1 ) );
	inPoints[1] = pos2pix( Point2f( 2, -4 ) );
	inPoints[2] = pos2pix( Point2f( 1, 3 ) );
	inPoints[3] = pos2pix( Point2f( 2, 2 ) );
	outPoints[0] = Point2f( 1, 1 );
	outPoints[1] = Point2f( width, 1 );
	outPoints[2] = Point2f( 1, height );
	outPoints[3] = Point2f( width, height );
	M = getPerspectiveTransform( inPoints, outPoints );
	warpPerspective( in, out, M, out.size() );
	Mat end( in.rows/4, in.cols/4, in.type() );
	resize( out, end, Size( width/4, height/4 ) );
	waitKey(0);

	inPoints[0] = pos2pix( Point2f( 0.5, -2.5 ) );
	inPoints[1] = pos2pix( Point2f( 2, -1 ) );
	inPoints[2] = pos2pix( Point2f( 1.5, 2.5 ) );
	inPoints[3] = pos2pix( Point2f( 0, 1 ) );
	outPoints[0] = Point2f( width/2, 1 );
	outPoints[1] = Point2f( width, height/2 );
	outPoints[2] = Point2f( width/2, height );
	outPoints[3] = Point2f( 1, height/2 );

	M = getPerspectiveTransform( inPoints, outPoints );
	warpPerspective( in, out, M, out.size() );
	Mat end2( in.rows/4, in.cols/4, in.type() );
	resize( out, end2, Size( width/4, height/4 ) );
	imshow("Sample", end);
	imshow("Sample2", end2);
	waitKey(0);
 	return 0;
}

Point2f pos2pix(const Point2f & pos){
	float pixSize = 1.0/150.0f; // metres/pixel
	Point2f pix( width/2.0f + pos.x/pixSize, height/2.0f + pos.y/pixSize );		
	return pix;
}
