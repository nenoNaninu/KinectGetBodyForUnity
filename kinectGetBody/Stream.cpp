#include"Stream.h"

void Stream::getAlimetJointPosition(float argJointX[], float argJointY[], float argJointZ[])
{
	Joint joint[6][25];
	kinectBodyFreame.getBodyJointData(joint);
	cv::Mat mat(3, 1, CV_32FC1);
	float* matPtr = (float*)mat.data;

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 25; ++j)
		{
			matPtr[0] = -1 * joint[i][j].Position.X;
			matPtr[1] = joint[i][j].Position.Z;
			matPtr[2] = 1;

			cv::Mat posi(3, 1, CV_32FC1);
			posi = homographyMat*mat;
			float* alimentePosi = (float*)posi.data;

			argJointX[i * 25 + j] = alimentePosi[0];
			argJointY[i * 25 + j] = joint[i][j].Position.Y;
			argJointZ[i * 25 + j] = alimentePosi[1];
		}
	}
}

void Stream::getOriginalJointPosition(float argPositionX[], float argPositionY[], float argPositionZ[])
{
	Joint joint[6][25];
	kinectBodyFreame.getBodyJointData(joint);

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			argPositionX[i * 25 + j] = joint[i][j].Position.X;
			argPositionY[i * 25 + j] = joint[i][j].Position.Y;
			argPositionZ[i * 25 + j] = joint[i][j].Position.Z;
		}
	}
}

void Stream::getIsPlayer(int isPlayer[])
{
	kinectBodyFreame.getIsPlayer(isPlayer);
}

void Stream::update()
{
	kinectBodyFreame.upDate();
}

void Stream::getJointType(int argJointType[])
{
	int jointTypeArray[6][25];
	kinectBodyFreame.getJointType(jointTypeArray);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			argJointType[j + i * 25] = jointTypeArray[i][j];
		}
	}
}

std::vector<std::string> Stream::split(const std::string& line, char delimiter)
{
	std::istringstream stream(line);
	std::string filed;
	std::vector<std::string> result;
	while (std::getline(stream, filed, delimiter))
	{
		result.push_back(filed);
	}
	return result;
}