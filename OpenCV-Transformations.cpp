#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cmath>

#define PI 3.14159265 //used to convert radians to degrees

using namespace cv;
using namespace std;


Mat scale(Mat image, int transMat[3][3])
{
	Mat newImage = Mat::zeros(image.rows * 2, image.cols * 2, CV_8UC3); //new image matrix

	//loop through pixel rows and columns
	for (int x = 0; x < image.rows; x++)
	{
		for (int y = 0; y < image.cols ; y++)
		{
			Vec3b pixelLocation = image.at<Vec3b>(x, y);

			//set new x and y values
			int xLocation = x * transMat[0][0] + y * transMat[1][0] + transMat[1][2];
			int yLocation = x * transMat[0][1] + y * transMat[1][1] + transMat[0][2];

			//do not display pixels that are out of bounds
			if (xLocation >= 0 && yLocation >= 0)
			{
				newImage.at<Vec3b>(xLocation, yLocation) = pixelLocation;
			}
		}
	}

	return newImage;
}


Mat rotate(Mat image, float transMat[3][3])
{
	Mat newImage = Mat::zeros(image.rows * 2, image.cols * 2, CV_8UC3); //new image matrix

	//loop through pixel rows and columns
	for (int x = 0; x < image.rows; x++)
	{
		for (int y = 0; y < image.cols; y++)
		{
			Vec3b pixelLocation = image.at<Vec3b>(x, y);

			//set new x and y values
			int xLocation = x * transMat[0][0] + y * transMat[1][0] + transMat[1][2];
			int yLocation = x * transMat[0][1] + y * transMat[1][1] + transMat[0][2];

			//do not display pixels that are out of bounds
			if (xLocation >= 0 && yLocation >= 0)
			{
				newImage.at<Vec3b>(xLocation, yLocation) = pixelLocation;
			}
		}
	}

	return newImage;
}


Mat translate(Mat image, int transMat[3][3])
{
	Mat newImage = Mat::zeros(image.rows * 2, image.cols * 2, CV_8UC3); //new image matrix

	//loop through pixel rows and columns
	for (int x = 0; x < image.rows; x++)
	{
		for (int y = 0; y < image.cols; y++)
		{
			Vec3b pixelLocation = image.at<Vec3b>(x, y);

			//set new x and y values
			int xLocation = x * transMat[0][0] + y * transMat[1][0] + transMat[1][2];
			int yLocation = x * transMat[0][1] + y * transMat[1][1] + transMat[0][2];

			//do not display pixels that are out of bounds
			if (xLocation >= 0 && yLocation >= 0)
			{
				newImage.at<Vec3b>(xLocation, yLocation) = pixelLocation;
			}
		}
	}

	return newImage;
}


int main()
{
	//read original image
	Mat image1 = imread("lenna.jpg");
	if (image1.empty())
	{
		cout << "Image could not be found." << endl;
		exit(EXIT_FAILURE);
	}

	//doubling image scale and show rescaled image
	int doubleSizeMatrix[3][3] = { {2,0,0},{0,2,0},{0,0,1} };
	Mat doubleSizeImage = scale(image1, doubleSizeMatrix);
	imshow("Original Image", image1);
	imshow("Double Size Image", doubleSizeImage);
	waitKey(0);

	//rotate image by 45 degrees and show rotated image
	float rotateMatrix[3][3] = { {cosf(45 * PI / 180),-sinf(45 * PI / 180),0},{sinf(45 * PI / 180),cosf(45 * PI / 180),0},{0,0,1} };
	Mat rotateImage = rotate(image1, rotateMatrix);
	imshow("Rotated Image", rotateImage);
	waitKey(0);

	//translate x by 100 and y by 50 and show translated image
	int translateMatrix[3][3] = { {1,0,100},{0,1,50},{0,0,1} };
	Mat translateImage = translate(image1, translateMatrix);
	imshow("Translated Image", translateImage);
	waitKey(0);

	//translate and then rotate image
	Mat tranRot = rotate(translateImage, rotateMatrix);
	imshow("Translated and then Rotated Image", tranRot);
	waitKey(0);

	//rotate and then translate image
	Mat rotTran = translate(rotateImage, translateMatrix);
	imshow("Rotated and then Translated Image", rotTran);
	waitKey(0);

}
