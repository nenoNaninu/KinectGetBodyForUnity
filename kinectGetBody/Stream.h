#pragma once
#include"KinecBodyFrameAPI.h"
#include<opencv2\opencv.hpp>
#include<fstream>

//Ç±ÇÃíÜÇ≈
class Stream
{
private:
	cv::Mat homographyMat;
	std::vector<std::string> split(const std::string&,char);
public:
	Stream() {
		kinectBodyFreame = KinectBodyFrameAPI();
		kinectBodyFreame.initialize();
		homographyMat = cv::Mat(3, 3, CV_32FC1);

		std::ifstream ifs("homography.csv");

		//if (!ifs)
		//{
		//	float* matPtr = (float*)homographyMat.data;
		//	matPtr[0] = 1;
		//	matPtr[1] = 0;
		//	matPtr[2] = 0;

		//	matPtr[3] = 0;
		//	matPtr[4] = 1;
		//	matPtr[5] = 0;
		//	
		//	matPtr[6] = 0;
		//	matPtr[7] = 0;
		//	matPtr[8] = 1;
		//	return;
		//}

		std::string line;

		int i = 0;
		float* matPtr = (float*)homographyMat.data;
		while (std::getline(ifs, line))
		{
			std::vector<std::string> temp = split(line, ',');
			matPtr[i] = std::stod(temp[0]);
			matPtr[i + 1] = std::stod(temp[1]);
			matPtr[i + 2] = std::stod(temp[2]);
			i += 3;
			if (i == 9)
			{
				break;
			}
		}
	}

	~Stream(){
	}

	void update();

	//25joint*6êlï™ÇÃîzóÒ
	void getAlimetJointPosition(float[],float[],float[]);

	void getOriginalJointPosition(float[], float[], float[]);


	void getIsPlayer(int[]);

	void getJointType(int[]);

private:
	KinectBodyFrameAPI kinectBodyFreame;
};

