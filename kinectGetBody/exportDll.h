#pragma once
#ifdef _DLL_API_CALL_
#define _UNITY_API_ __declspec(dllexport)
#else 
#define _UNITY_API_ __declspec(dllimport)
#endif


extern "C" {
	_UNITY_API_ void* getStream();
	_UNITY_API_ void getAlimentBodyJoint(void*, float[], float[], float[]);
	_UNITY_API_ void releaseStream(void*);
	_UNITY_API_ void getIsPlayer(void*, int[]);
	_UNITY_API_ void upDateStreamData(void*);
	_UNITY_API_ void getJointType(void*, int[]);
	_UNITY_API_ void getOriginalBodyJoint(void*, float[], float[],float[]);
}