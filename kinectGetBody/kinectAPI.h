#pragma once

#include<Kinect.h>
#include<vector>
#include<iostream>
#include<sstream>
#include<opencv2\core.hpp>

class KinectAPI
{

protected:

	IKinectSensor* kinectSensor = nullptr;
	IDepthFrameReader* depthFrameReader = nullptr;

	std::vector<UINT16> depthBuffer;

	cv::Mat depthImage;

	const char* DepthWindowName = "Depth Image";

	int depthWidth;
	int depthHight;

public:
	~KinectAPI() {
		if (kinectSensor != nullptr) {
			kinectSensor->Close();
			kinectSensor = nullptr;
		}
	}
	void initialize();

	void queryImage(cv::Mat& mat);

	void upDateImage();

	int getWidth();
	int getHight();

};