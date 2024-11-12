#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;

int main() 
{

   string image_path = samples::findFile("cat white.jpg");
   Mat img = imread(image_path, IMREAD_COLOR);

   if ( img.empty())
   {
      cout << "Cannot find file: " << image_path << endl;
      return 1;
   }
   
   float gamma = 10; // gamma < 1 => image brighter

   Mat lookUpTable(1, 256, CV_8U);

   uchar *p = lookUpTable.ptr();
   for ( int i = 0; i < 256; ++i )
      p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);

   Mat res = img.clone();
   LUT(img, lookUpTable, res);

   imshow("My image", img);
   imshow("My gamma image", res);

   int k = waitKey(0); // Wait for a keystroke in the window

   return 0;
}