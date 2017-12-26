#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;




Mat HSI(Mat image) {
	float red, green, blue, hue, saturation, intensity;
	Mat hsi_image(image.rows, image.cols, image.type());
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			blue = image.at<Vec3b>(i, j)[0];
			green = image.at<Vec3b>(i, j)[1];
			red = image.at<Vec3b>(i, j)[2];

			intensity = (blue + green + red) / 3;

			int min_val = 0;
			min_val = std::min(red, std::min(blue, green));

			saturation = 1 - 3 * (min_val / (blue + green + red));
			if (saturation < 0.00001)
			{
				saturation = 0;
			}
			else if (saturation > 0.99999) {
				saturation = 1;
			}

			if (saturation != 0)
			{
				hue = 0.5 * ((red - green) + (red - blue)) / sqrt(((red - green)*(red - green)) + ((red - blue)*(green - blue)));
				hue = acos(hue);

				if (blue <= green)
				{
					hue = hue;
				}
				else {
					hue = ((360 * 3.14159265) / 180.0) - hue;
				}
			}


			hsi_image.at<Vec3b>(i, j)[2] = intensity;

		}
	}
	return hsi_image;
}
void showoutput(string windowname, Mat image) {
	namedWindow(windowname, CV_WINDOW_AUTOSIZE);
	imshow(windowname, image);
	waitKey();
	cvDestroyAllWindows();
}
int main()
{
	Mat image;
	image = imread("basel3.bmp", CV_LOAD_IMAGE_COLOR);
	if (image.empty())
		cerr << "Error: Loading image" << endl;

	Mat image_hsi(image.rows, image.cols, image.type());
	
	image_hsi = HSI(image);
	namedWindow("HSI image", CV_WINDOW_AUTOSIZE);
	namedWindow("RGB image", CV_WINDOW_AUTOSIZE);
	imshow("HSI image", image_hsi);
	imshow("RGB image", image);
	waitKey();
	cvDestroyAllWindows();
	
	waitKey(0);
	return 0;
}
