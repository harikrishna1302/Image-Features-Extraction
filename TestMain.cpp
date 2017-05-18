#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<sstream>
#include<cmath>

using namespace cv;
using namespace std;
using namespace boost::filesystem;

void LBP(Mat image, int i, int j, vector<int> &neighbourvalues) {
	if ((i >= 1) && (j >= 1) && (i < image.rows - 1) && (j < image.cols - 1))
	{
		neighbourvalues.push_back(image.at<uchar>(i - 1, j));
		neighbourvalues.push_back(image.at<uchar>(i - 1, j + 1));
		neighbourvalues.push_back(image.at<uchar>(i, j + 1));
		neighbourvalues.push_back(image.at<uchar>(i + 1, j + 1));
		neighbourvalues.push_back(image.at<uchar>(i + 1, j));
		neighbourvalues.push_back(image.at<uchar>(i + 1, j - 1));
		neighbourvalues.push_back(image.at<uchar>(i, j - 1));
		neighbourvalues.push_back(image.at<uchar>(i - 1, j - 1));
	}
	else if ((i == 0) && (j >= 1) && (j < image.cols - 1))
	{
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(image.at<uchar>(i, j + 1));
		neighbourvalues.push_back(image.at<uchar>(i + 1, j + 1));
		neighbourvalues.push_back(image.at<uchar>(i + 1, j));
		neighbourvalues.push_back(image.at<uchar>(i + 1, j - 1));
		neighbourvalues.push_back(image.at<uchar>(i, j - 1));
		neighbourvalues.push_back(0);
	}
	else if ((j == 0) && (i >= 1) && (i < image.rows - 1))
	{
		neighbourvalues.push_back(image.at<uchar>(i - 1, j));
		neighbourvalues.push_back(image.at<uchar>(i - 1, j + 1));
		neighbourvalues.push_back(image.at<uchar>(i, j + 1));
		neighbourvalues.push_back(image.at<uchar>(i + 1, j + 1));
		neighbourvalues.push_back(image.at<uchar>(i + 1, j));
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
	}
	else if ((i == image.rows - 1) && (j >= 1) && (j < image.cols - 1))
	{
		neighbourvalues.push_back(image.at<uchar>(i - 1, j));
		neighbourvalues.push_back(image.at<uchar>(i - 1, j + 1));
		neighbourvalues.push_back(image.at<uchar>(i, j + 1));
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(image.at<uchar>(i, j - 1));
		neighbourvalues.push_back(image.at<uchar>(i - 1, j - 1));
	}
	else if ((j == image.cols - 1) && (i >= 1) && (i < image.rows - 1)) {
		neighbourvalues.push_back(image.at<uchar>(i - 1, j));
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(image.at<uchar>(i + 1, j));
		neighbourvalues.push_back(image.at<uchar>(i + 1, j - 1));
		neighbourvalues.push_back(image.at<uchar>(i, j - 1));
		neighbourvalues.push_back(image.at<uchar>(i - 1, j - 1));
	}
	else if ((i == 0) && (j == 0))
	{
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(image.at<uchar>(i, j + 1));
		neighbourvalues.push_back(image.at<uchar>(i + 1, j + 1));
		neighbourvalues.push_back(image.at<uchar>(i + 1, j));
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
	}
	else if ((i == image.rows - 1) && (j == 0)) {
		neighbourvalues.push_back(image.at<uchar>(i - 1, j));
		neighbourvalues.push_back(image.at<uchar>(i - 1, j + 1));
		neighbourvalues.push_back(image.at<uchar>(i, j + 1));
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
	}
	else if ((j == image.cols - 1) && (i == 0)) {

		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(image.at<uchar>(i + 1, j));
		neighbourvalues.push_back(image.at<uchar>(i + 1, j - 1));
		neighbourvalues.push_back(image.at<uchar>(i, j - 1));
		neighbourvalues.push_back(0);
	}
	else if ((i == image.rows - 1) && (j == image.cols - 1)) {
		neighbourvalues.push_back(image.at<uchar>(i - 1, j));
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(0);
		neighbourvalues.push_back(image.at<uchar>(i, j - 1));
		neighbourvalues.push_back(image.at<uchar>(i - 1, j - 1));
	}
}


int Transition(vector<int> neighbourvalues) {
	int cnt = 0;
	for (int i = 0; i < neighbourvalues.size(); i++) {
		if (i == neighbourvalues.size() - 1) {
			if (neighbourvalues[i] != neighbourvalues[0])
			cnt++;
		}
	 else if (neighbourvalues[i] != neighbourvalues[i + 1])
			cnt++;	 
	}
	return cnt;
}

int main(int argc, char **argv) {

	path p(argv[1]);
	string outputpath(argv[2]);
	std::ofstream outputFile(outputpath);
	string histogramFile = outputpath + "/" + "HISTOGRAMS.txt";
	outputFile.open(histogramFile);
	outputFile.precision(6);
	outputFile.close();
	

	vector<string>imagenames;
	string extn;
	directory_iterator end_itr;
	for (directory_iterator itr(p); itr != end_itr; ++itr) {
		string imname = itr->path().filename().string();
		extn = itr->path().extension().string();
		imagenames.push_back(imname);
	}
	std::sort(imagenames.begin(), imagenames.end());

	for (size_t n = 0; n < imagenames.size(); n++) {
		string inputpath(argv[1]);
		string inputimage = inputpath + "/" + imagenames[n];
		if (extn == ".png" || extn == ".PNG") {
			Mat image = imread(inputimage, IMREAD_GRAYSCALE);
			if (!image.data) {
				cout << "ERROR: Could not open or find the image!" << endl;

				return -1;
			}

			Mat LBPimage = Mat::zeros(cv::Size(image.cols, image.rows), CV_8UC1);
			for (int i = 0; i < image.rows; i++) {
				for (int j = 0; j < image.cols; j++) {
					vector<int>neighbourvalues;
					LBP(image, i, j, neighbourvalues);
					int ones = 0;
					for (int k = 0; k < neighbourvalues.size(); k++) {
						if (neighbourvalues[k] > image.at<uchar>(i, j)) {
							neighbourvalues[k] = 1;
							ones++;
						}
						else
							neighbourvalues[k] = 0;
					}
					int T= Transition(neighbourvalues);
					if (T <= 2)
						LBPimage.at<uchar>(i, j) = ones;
					else
						LBPimage.at<uchar>(i, j) = 9;
				}
			}
			
	     	double bins[10];
			for (int i = 0; i < 10; i++)
				bins[i] = 0;
			
			for (int i = 0; i < LBPimage.rows; i++) {
				for (int j = 0; j < LBPimage.cols; j++) {
					bins[LBPimage.at<uchar>(i, j)] = bins[LBPimage.at<uchar>(i, j)] + 1;
				}
			}
			

			std::ofstream outputFile(histogramFile, ios::app);
			int N = LBPimage.rows*LBPimage.cols;
			outputFile << imagenames[n] << " ";
			for (int i = 0; i < 10; i++)
			outputFile << bins[i] / N << " ";
			if(n!=imagenames.size()-1)    // for avoiding empty line in Histogram.txt
			outputFile << endl;		

		}
	}
	outputFile.close();

	std::ifstream readFile(histogramFile);
	vector<vector<string>> array;
	string line;
	while (getline(readFile, line))     
	{
		array.push_back(vector<string>());
		istringstream ss(line);
		string value;
		while (ss >> value)
		{
			array.back().push_back(value);
		}
	}

	std::ofstream distanceOutputFile(outputpath);
	distanceOutputFile.precision(6);
	string distanceFile = outputpath + "/" + "DISTANCES.txt";
	distanceOutputFile.open(distanceFile);

	for (int i = 0; i < imagenames.size(); i++) {
		distanceOutputFile << imagenames[i] << " ";
		double distance = 0;
		for (int j = 1; j < 11; j++)
		{
			distance = distance + abs(stod(array[1][j]) - stod(array[i][j]));
		}
		distanceOutputFile << distance << endl;
		cout << "distance " << imagenames[i] << " " << distance << endl;
	}
	distanceOutputFile.close();
	return 0;
}