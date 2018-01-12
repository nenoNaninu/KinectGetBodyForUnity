#include"kinectAPI.h"
#include"ComPtr.h"

#define ERROR_CHECK( ret )  \
    if ( (ret) != S_OK ) {    \
        std::stringstream ss;	\
        ss << "failed " #ret " " << std::hex << ret << std::endl;			\
        throw std::runtime_error( ss.str().c_str() );			\
    }

void KinectAPI::initialize()
{
	ERROR_CHECK(GetDefaultKinectSensor(&kinectSensor));

	ERROR_CHECK(kinectSensor->Open());

	BOOLEAN isOpen = false;
	ERROR_CHECK(kinectSensor->get_IsOpen(&isOpen));

	if (!isOpen)
	{
		throw std::runtime_error("KinectSensor‚ªŠJ‚¯‚Ü‚¹‚ñ");
	}

	//DepthReader‚ÌŽæ“¾
	ComPtr<IDepthFrameSource> depthFrameSoure;
	ERROR_CHECK(kinectSensor->get_DepthFrameSource(&depthFrameSoure));
	ERROR_CHECK(depthFrameSoure->OpenReader(&depthFrameReader));

	ComPtr<IFrameDescription> depthFrameDiscription;
	ERROR_CHECK(depthFrameSoure->get_FrameDescription(&depthFrameDiscription));
	ERROR_CHECK(depthFrameDiscription->get_Width(&depthWidth));
	ERROR_CHECK(depthFrameDiscription->get_Height(&depthHight));

	depthBuffer.resize(depthWidth*depthHight);

	depthImage = cv::Mat(depthHight, depthWidth, CV_32FC1);

}

int KinectAPI::getHight()
{
	return depthHight;
}

int KinectAPI::getWidth()
{
	return depthWidth;
}

void KinectAPI::upDateImage()
{
	ComPtr<IDepthFrame> depthFrame;
	auto ret = depthFrameReader->AcquireLatestFrame(&depthFrame);

	if (ret != S_OK)
	{
		return;
	}

	//depthFrame->CopyFrameDataToArray(depthBuffer.size(), &depthBuffer[0]);
	ERROR_CHECK(depthFrame->CopyFrameDataToArray(depthBuffer.size(), &depthBuffer[0]));

	float* depthImagePtr = (float*)depthImage.data;

	for (int i = 0; i < depthImage.total(); i++)
	{
		depthImagePtr[i] = (float)depthBuffer[i];
	}
}

void KinectAPI::queryImage(cv::Mat& mat)
{
	depthImage.copyTo(mat);
}