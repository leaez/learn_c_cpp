#ifndef __CoreData_H_
#define __CoreData_H_

#include "CoreStructures.h"
#include "eyeCanData.h"
#include "GlobalConst.h"
#include "FaceDetectionData.h"

class CORE_API CoreData{
public:

	// This Must Always be the first data member!!!!
	int m_nXmlDataVersion;

	bool m_bMirrorOutput;

	bool m_bDynamicCropping;
	bool m_bFaceDetection;
	bool m_bUserAnalysis;
	bool m_bDisableFaceDetectionOnTracking;
	bool m_bEyeCan;
	bool m_bEyeSign;
	bool m_bEyeDepth;
	bool m_bDevelEngine;
	bool m_bEyeSnip;
	
	bool m_bDetectLowLight;
	int m_nLowLightFrequency;
	int m_nSnrThreshold;

	bool m_bVideoConverter;
	int m_nConvertedHeight;
	int m_nConvertedWidth;

	int m_nMaxUsers;
	DeveloperRunMode m_eDeveloperRunMode;

	static const int m_nCurrentDataVersion=1;
	
	CoreData();
	void Reset();

	~CoreData();
};
//CoreData::m_nCurrentDataVersion = 1;

#endif //__CoreData_H_
