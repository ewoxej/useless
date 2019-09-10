//perspective transformation with openCV
//you have to pass image path as CL argument, mark object boundaries and get its perspective transformation
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

std::vector<cv::Point2f> points;
cv::Mat image;
cv::Mat otherImg;
cv::Mat original;

void fourPointTransform( cv::Mat img )
{   
   otherImg = img.clone();
   std::vector<cv::Point2f> result
   { 
      cv::Point2f( 0,0 ),
      cv::Point2f( img.size().width - 1 ,0 ),
      cv::Point2f( img.size().width - 1 ,img.size().height - 1 ),
      cv::Point2f( 0,img.size().height - 1 ),

   };

   cv::Mat transformMat = cv::getPerspectiveTransform( points, result );
   cv::warpPerspective( original, otherImg, transformMat, img.size() );
   cv::namedWindow( "newWindow", 0 );
   cv::imshow( "newWindow", otherImg );
   image = original.clone();
}

void mouseClickCallback( int event, int x, int y, int flags, void *userdata )
{
   switch( event )
   {
   case cv::EVENT_LBUTTONDOWN:

      cv::drawMarker( image, cv::Point( x, y ), cv::Scalar( 255, 0, 150, 0 ), 0, 10,10 );
      points.push_back( cv::Point( x, y ) );
      cv::imshow( "window", image );
      if( points.size() == 4 )
      {
         fourPointTransform( image );
         points.clear();
      }
      break;
   }
}
int main( int argc, char** argv )
{
   cv::namedWindow( "window", 0 );
   image = cv::imread( argv[1] );
   original = image.clone();
   cv::setMouseCallback( "window", mouseClickCallback );
   cv::imshow( "window", image );
   cvWaitKey( 0 );
}