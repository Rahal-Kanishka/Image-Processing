#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
		return -1;
	}

	Mat image;
	image = imread(argv[1], CV_LOAD_IMAGE_COLOR); // Read the file

	if (!image.data) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	else
	{
		cout << "image found" << std::endl;
	}

	Mat Grayimg = imread(argv[1],0);

	//getting the count of rows and coloumns of pixels of the given image
	int rows = Grayimg.rows;
	int coloumns = Grayimg.cols;

	cout << "rows: " << rows << " Cloumns: " <<coloumns << std::endl;
	int i;
	int y;
	int greylevel;

	//count the number of pixels for a 255 gray levels
	int pixelscount[256];

	//emptying the array
		for (int a = 0; a < 256; a++)
	{
		pixelscount[a] = 0;
	}

	for (i=0;i<rows;i++)
	{
		for (y=0;y<coloumns;y++) {

			greylevel = (int)Grayimg.at<uchar>(y, i);
			pixelscount[greylevel] += 1;

		}
	}

	//printing out the grayleve values
	for (size_t x = 0; x< 256; x++)
	{
		cout << x << ": "  << pixelscount[x] << std::endl;
	}


	namedWindow("Color Image", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Color Image", image); // Show our image inside it.

	namedWindow("Gray Image", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Gray Image", Grayimg); // Show our image inside it.

	waitKey(0); // Wait for a keystroke in the window
	return 0;
}