#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <ctime>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
	VideoCapture cap(0);

	if (!cap.isOpened()){
		return -1;
	}

	clock_t input_time;
	clock_t processing_time;
	clock_t output_time;

	clock_t input_counter = 0;
	clock_t processing_counter = 0;
	clock_t output_counter = 0;
	double counter = 0;

	Mat frame; //empty matrix for storing webcam frames
	clock_t time = clock();

	while (true)
	{
		//input
		input_time = clock();
		cap >> frame; //inserting the webcam frame inside frame matrix
		input_time = clock() - input_time;
		input_counter += input_time;

		processing_time = clock();

		Mat edges;
		cvtColor(frame, edges, COLOR_BGR2GRAY);
		Canny(edges, edges, 30, 60, 5);
		Mat sub;
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		subtract(frame, edges, sub);
		//imshow("Webcam", sub);

		//---ROTATING---
		double angle = 170;

		// getting the center coordinates of the image to create the 2D rotation matrix
		Point2f center( frame.cols / 2, frame.rows / 2);
		
		//getting the rotation matrix
		Mat rotation_matix = getRotationMatrix2D(center, angle, 1.3);
		Mat rotated_webcam;
		// rotating the sub using rotation matrix
		warpAffine(sub, rotated_webcam, rotation_matix, edges.size());

		processing_time = clock() - processing_time;
		processing_counter += processing_time;

		output_time = clock();
		imshow("Webcam", rotated_webcam);
		output_time = clock() - output_time;
		output_counter += output_time;

		counter++;

		if (waitKey(33) == 27)
			break;
	}
	time = clock() - time - counter * 33;

	double total_time = (((double)time / CLOCKS_PER_SEC));
	double FPS = counter / (((double)time / CLOCKS_PER_SEC));
	double res_input_time = ((double)input_counter / CLOCKS_PER_SEC);
	double res_processing_time = ((double)processing_counter / CLOCKS_PER_SEC);
	double res_output_time = ((double)output_counter / CLOCKS_PER_SEC);


	cout << "Total time: " << total_time << endl;
	cout << "Frame per second: " << FPS << endl;
	cout << "Percentage of total time for input: " 
		<< res_input_time / total_time * 100 << "%" << endl;
	cout << "Percentage of total time for processing : " 
		<< res_processing_time / total_time * 100 << "%" << endl;
	cout << "Percentage of total time for output: " 
		<< res_output_time / total_time * 100 << "%" << endl;

	return 0;
}
