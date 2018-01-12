#include"libHeader.h"
#include<iostream>
#include"exportDll.h"
#include<opencv2\opencv.hpp>

int main() {

	void* stream = getStream();
	cv::Mat mat(5, 5, CV_8UC3, cv::Scalar(0, 0, 0));
	cv::imshow("mat", mat);

	char key = 0;
	
	while (key != 'q')
	{
		float positionX[25*6];
		float positionY[25*6];
		float positionZ[25*6];
		upDateStreamData(stream);
		getBodyJoint(stream, positionX, positionY, positionZ);
		//std::cout << positionX[0] << std::endl;
		key = cv::waitKey(1);
	
	}

	std::getchar();

	return 0;
}



//#include <Kinect.h>
//#include <iostream>

//void processBodies(const unsigned int &bodyCount, IBody **bodies);
//
//template<class Interface>
//static inline void safeRelease(Interface *&interfaceToRelease)
//{
//	if (interfaceToRelease != nullptr) {
//		interfaceToRelease->Release();
//		interfaceToRelease = nullptr;
//	}
//}

//int main(int argc, char *argv[])
//{
//	IKinectSensor *sensor = nullptr;
//	IBodyFrameReader *bodyFrameReader = nullptr;
//
//	//Get the default Kinect sensor
//	HRESULT hr = GetDefaultKinectSensor(&sensor);
//
//	//If the function succeeds, open the sensor
//	if (SUCCEEDED(hr)) {
//		hr = sensor->Open();
//
//		if (SUCCEEDED(hr)) {
//			//Get a body frame source from which we can get our body frame reader
//			IBodyFrameSource *bodyFrameSource = nullptr;
//			hr = sensor->get_BodyFrameSource(&bodyFrameSource);
//
//			if (SUCCEEDED(hr)) {
//				hr = bodyFrameSource->OpenReader(&bodyFrameReader);
//			}
//
//			//We're done with bodyFrameSource, so we'll release it
//			safeRelease(bodyFrameSource);
//		}
//	}
//
//	if (sensor == nullptr || FAILED(hr)) {
//		std::cerr << "Cannot find any sensors.\n";
//		return E_FAIL;
//	}
//
//	while (bodyFrameReader != nullptr) {
//		IBodyFrame *bodyFrame = nullptr;
//		hr = bodyFrameReader->AcquireLatestFrame(&bodyFrame);
//
//		if (SUCCEEDED(hr)) {
//			IBody *bodies[BODY_COUNT] = { 0 };
//			hr = bodyFrame->GetAndRefreshBodyData(_countof(bodies), bodies);
//
//			if (SUCCEEDED(hr)) {
//				processBodies(BODY_COUNT, bodies);
//				//After body processing is done, we're done with our bodies so release them.
//				for (unsigned int bodyIndex = 0; bodyIndex < _countof(bodies); bodyIndex++) {
//					safeRelease(bodies[bodyIndex]);
//				}
//
//				safeRelease(bodyFrame);
//			}
//		}
//		else if (sensor) {
//			BOOLEAN isSensorAvailable = false;
//			hr = sensor->get_IsAvailable(&isSensorAvailable);
//			if (SUCCEEDED(hr) && isSensorAvailable == false) {
//				std::cerr << "No available sensor is found.\n";
//			}
//		}
//		else {
//			std::cerr << "Trouble reading the body frame.\n";
//		}
//	}
//
//	return 0;
//}
//
//void processBodies(const unsigned int &bodyCount, IBody **bodies)
//{
//	for (unsigned int bodyIndex = 0; bodyIndex < bodyCount; bodyIndex++) {
//		IBody *body = bodies[bodyIndex];
//
//		//Get the tracking status for the body, if it's not tracked we'll skip it
//		BOOLEAN isTracked = false;
//		HRESULT hr = body->get_IsTracked(&isTracked);
//		if (FAILED(hr) || isTracked == false) {
//			continue;
//		}
//
//		//If we're here the body is tracked so lets get the joint properties for this skeleton
//		Joint joints[JointType_Count];
//		hr = body->GetJoints(_countof(joints), joints);
//		if (SUCCEEDED(hr)) {
//			//Let's print the head's position
//			const CameraSpacePoint &headPos = joints[JointType_Head].Position;
//			const CameraSpacePoint &leftHandPos = joints[JointType_HandLeft].Position;
//
//			//Let's check if the use has his hand up
//			if (leftHandPos.Y >= headPos.Y) {
//				std::cout << "LEFT HAND UP!!\n";
//			}
//
//			HandState leftHandState;
//			hr = body->get_HandLeftState(&leftHandState);
//			if (SUCCEEDED(hr)) {
//				if (leftHandState == HandState_Closed) {
//					std::cout << "CLOSED HAND\n";
//				}
//				else if (leftHandState == HandState_Open) {
//					std::cout << "OPEN HAND\n";
//				}
//				else if (leftHandState == HandState_Lasso) {
//					std::cout << "PEW PEW HANDS\n";
//				}
//				else if (leftHandState == HandState_NotTracked) {
//					std::cout << "HAND IS NOT TRACKED\n";
//				}
//				else if (leftHandState == HandState_Unknown) {
//					std::cout << "HANDS STATE IS UNKNOWN\n";
//				}
//			}
//		}
//	}
//}
