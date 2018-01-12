#pragma once
#include"kinectAPI.h"
#include"ComPtr.h"
#include<array>

class KinectBodyFrameAPI :public KinectAPI{
protected:
	 ComPtr<IBodyFrameReader> bodyReader;
	 IBody* bodyPtrArray[BODY_COUNT] = {};
	 BOOLEAN isTrackedArray[6] = {};
	 Joint jointArray[6][25];

public:
	void initialize();
	void upDate();
	void getIsPlayer(int[]);
	void getBodyJointData(Joint[6][25]);
	void getJointType(int[6][25]);
};