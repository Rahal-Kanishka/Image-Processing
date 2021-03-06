#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//function declaration
Mat drawHistrogram(Mat Grayimg);
Mat HistrogramEqualisation(int a, int b, int c, int d, int l, Mat grayimage);

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

	Mat Grayimg = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	
	//getting the count of rows and coloumns of pixels of the given image
	int rows = Grayimg.rows;
	int coloumns = Grayimg.cols;

	cout << "rows: " << rows << " Cloumns: " <<coloumns << std::endl;

	int i;
	int y;
	
	//getting the histrogram as a image
	Mat histro = drawHistrogram(Grayimg);

	Mat equalized = HistrogramEqualisation(12,97,20,180,255,Grayimg);
	
	// display histogram 
	namedWindow("Intensity Histogram", CV_WINDOW_AUTOSIZE);
	imshow("Intensity Histogram", histro);

	namedWindow("Color Image", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Color Image", image); // Show our Colorimage inside it.

	namedWindow("Gray Image", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Gray Image", Grayimg); // Show our grayimage inside it.s
	
	namedWindow("Equalized Image", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Equalized Image", equalized); // Show our equalized image inside it.
	
	namedWindow("Equalized histrogram", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Equalized histrogram", drawHistrogram(equalized)); // Show our equalized histrogram inside it.

	waitKey(0); // Wait for a keystroke in the window
	return 0;
}

Mat drawHistrogram(Mat Grayimg)
{
	int rows = Grayimg.rows;
	int coloumns = Grayimg.cols;
	int greylevel;

	//count the number of pixels for a 255 gray levels
	int pixelscount[256];

	//emptying the array
	for (int a = 0; a < 256; a++)
	{
		pixelscount[a] = 0;
	}

	for (int x = 0;x<rows;x++)
	{
		for (int y = 0;y<coloumns;y++) {

			greylevel = (int)Grayimg.at<uchar>(x, y);
			pixelscount[greylevel] += 1;

		}
	}
		
	//printing out the grayleve values
	for (int x = 0; x< 256; x++)
	{
		cout << x << ": " << pixelscount[x] << std::endl;
	}

	// definig histrogram width and height
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / 256);

	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));

	// find the maximum intensity element from histogram
	int max = pixelscount[0];
	for (int i = 1; i < 256; i++) {
		if (max < pixelscount[i]) {
			max = pixelscount[i];
		}
	}

	//normalize the histogram between 0 and histImage.rows(400)  
	for (int i = 0; i < 255; i++) {
		pixelscount[i] = ((double)pixelscount[i] / max)*histImage.rows;
	}

	// draw the intensity line for histogram  
	for (int i = 0; i < 255; i++) {

		line(histImage, Point(bin_w*(i), hist_h),
			Point(bin_w*(i), hist_h - pixelscount[i]),
			Scalar(0, 0, 0), 1, 8, 0);
	}

	return histImage;
}


Mat HistrogramEqualisation(int a,int b,int c,int d,int l,Mat grayimage)
 {
	Mat equalizedimge		; 
	equalizedimge = grayimage.clone();
	int greylevel;
	double alpha = (double)c / a;
	double Beta = (double)(d-c) / (b-a);
	double Gamma = (double)(l - d) / (l - b);
		
	//count the number of pixels for a 255 gray levels
	int pixelscount[256];

	//emptying the array
	for (int a = 0; a < 256; a++)
	{
		pixelscount[a] = 0;
	}

	for (int x = 0;x<grayimage.rows;x++)
	{
		for (int y = 0;y<grayimage.cols;y++) {

			greylevel = (int)grayimage.at<uchar>(x, y);
			pixelscount[greylevel] += 1;

		}
	}
		
	//equalising the image

	for (int x = 0;x<grayimage.rows;x++)
	{
		for (int y = 0;y<grayimage.cols;y++) {

			greylevel = (int)grayimage.at<uchar>(x, y);
						
				if (0 < greylevel <= a) {

					equalizedimge.at<uchar>(x, y) = alpha*greylevel;
				}
				else if (a <= greylevel<b)
				{
					equalizedimge.at<uchar>(x, y) = Beta*(greylevel - a) + c;
				}
				else if (b <= greylevel <l)
				{
					equalizedimge.at<uchar>(x, y) = Gamma*(greylevel - b) + d;
				}
		
		}
	}
	

	return equalizedimge;
}