#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/utils/logger.hpp>

#include <iostream>

using namespace std;
using namespace cv;

const string ASCII_CHARS = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,^ `'. ";

static string pixel_to_ascii(int intensity)
{
   string s = string(1, ASCII_CHARS[intensity * ASCII_CHARS.length() / 256]);
   return s;
}

int main() 
{
   cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);
   string image_path = samples::findFile("L.jpg");
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

   int width = 115, height = 65;
   Mat grey, resized;
   string ascii;
   cvtColor(img, grey, COLOR_BGR2GRAY);
   resize(grey, resized, Size(width, height), 0, 0, INTER_AREA);

   for ( int y = 0; y < height; y++ )
   {
      for ( int x = 0; x < width; x++ )
      {
         ascii += pixel_to_ascii(resized.at<uchar>(Point(x, y)));
      }
      ascii += "\n";
   }
   system("Color 04"); // https://www.geeksforgeeks.org/how-to-print-colored-text-in-c/
   //imshow("My image", img);
   //imshow("My grey image", grey);
   //imshow("My resized image", resized);
   //imshow("My gamma image", res);
   cout << ascii;
   int k = waitKey(0); // Wait for a keystroke in the window

   return 0;
}