/****************************************************************************
 *
 * MODULE:             eyesight handle - Kc
 *
 * COMPONENT:          eyesight node to plant robot ros
 *
 * REVISION:           $Revision: 01 $
 *
 * DATED:              $Date: 2016-07-01 15:13:17 +0100  $
 *
 * AUTHOR:             PCT
 *
 ****************************************************************************
 *
 * Copyright panchangtao@gmail.com B.V. 2015. All rights reserved
 *
 ***************************************************************************/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <cv.h>
#include <signal.h>
#include <sstream>
/* Core Includes */
#include "Ctrl.h"
#include "CoreStructures.h"
#include "eyeSightOutput.h"
#include "eyeSignOutput.h"
#include "EngineFactory.h"
#include "ImageFormats.h"

using namespace std;
using namespace cv;
/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/
static void vQuitSignalHandler (int sig);
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define UI_GREEN(x)     "\e[32;1m"x"\e[0m"
#define UI_YELLOW(x)    "\e[33;1m"x"\e[0m"
#define UI_BLUE(x)      "\e[34;1m"x"\e[0m"
#define UI_PURPLE(x)    "\e[35;1m"x"\e[0m"

#define DBG_vPrintf(a,b,ARGS...)  do {  if (a) {printf(UI_BLUE	(b), ## ARGS);} } while(0)
#define INF_vPrintf(a,b,ARGS...)  do {  if (a) {printf(UI_YELLOW(b), ## ARGS);} } while(0)
#define NOT_vPrintf(a,b,ARGS...)  do {  if (a) {printf(UI_GREEN	(b), ## ARGS);} } while(0)
#define WAR_vPrintf(a,b,ARGS...)  do {  if (a) {printf(UI_PURPLE(b), ## ARGS);} } while(0)

#define FACE_DBG 1
#define GESTURE_DBG 1
/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/
static int cv_window = 0;

static const int iScreenWidth = 1920;
static const int iScreenHeight = 1080;
static const int iCameraWidth = 640;
static const int iCameraHeight = 480;
static const int iCameraSamplingRate = 30;
static cv::Mat resultM;//Picture

//Gesture
static VideoConfig oVideoConfig;
static const int iProductId = 1049;
static Ctrl *oEngine;
static eyeSightOutput *oEyeSightOutput;
//Face
static VideoConfig oFDVideoConfig;
static const int iFDProductId = 1061;
static Ctrl *oFDEngine;
static eyeSightOutput *oFDEyeSightOutput;
//motion
ros::Publisher pubM4;
/****************************************************************************/
/***        Local Functions                                               ***/
/****************************************************************************/
void M4_Publisher(String pMsg)
{
    ROS_INFO("M4 Publisher");

    if(ros::ok()){
        std_msgs::String msg;
        msg.data = pMsg.data();
        pubM4.publish(msg);
    }
}

void es_startEngine() {
    /* Initialize hand-tracking engine */
    if (oEngine != NULL) {
        eyeSight::destroyEngine(oEngine);
    }
    oVideoConfig.bFlip = false;
    oVideoConfig.nWidth = iCameraWidth;
    oVideoConfig.nHeight = iCameraHeight;
    oVideoConfig.tVideoFormat = KYUV422_YUYV;
    //oVideoConfig.tVideoFormat = CV_BGR2YUV_I420;
    oVideoConfig.nFps = iCameraSamplingRate;
    oVideoConfig.bMirror = false;
    oVideoConfig.nRotateByTheta = 0;

    static ConfigManager *pCfg = new ConfigManager(0, NULL);
    pCfg->setProduct(iProductId);
    pCfg->m_pEyeSignData->m_sMappingData.m_nDstWidth = iScreenWidth;
    pCfg->m_pEyeSignData->m_sMappingData.m_nDstHeight = iScreenHeight;
    //all feature enabled
    pCfg->m_pEyeSignData->m_bDetectUpperHand = true;
    pCfg->m_pEyeSignData->m_bDetectHand = true;
    pCfg->m_pEyeSignData->m_bDetectFist = true;
    pCfg->m_pEyeSignData->m_bDetectLowerFinger = true;
    pCfg->m_pEyeSignData->m_bDetectFinger = true;
    pCfg->m_pEyeSignData->m_bDetectThumbsUp = true;
    pCfg->m_pEyeSignData->m_bDetectMuteSign = true;
    pCfg->m_pEyeSignData->m_bDetectPartialMuteSign = true;
    pCfg->m_pEyeSignData->m_bDetectTentSign = true;
    pCfg->m_pEyeSignData->m_bDetectVictorySign = true;
    pCfg->m_pEyeSignData->m_bDetectPhoneSign = true;
    pCfg->m_pEyeSignData->m_bFingerClick = true;
    pCfg->m_pEyeSignData->m_bFingerDnd = true;
    pCfg->m_pEyeSignData->m_bPalmClick = true;
    pCfg->m_pEyeSignData->m_bPalmDnd = true;
    pCfg->m_pEyeSignData->m_bAngleResetAfterTransition = true;
    pCfg->m_pEyeSignData->m_bAllowWave = true;
    pCfg->m_pEyeSignData->m_bWaveResetOnTileEvent = true;
    /*  edited from eyeSignData.h */
    oEngine = eyeSight::createEngineByConfig(oVideoConfig, pCfg);
    if(oEngine == NULL){
        ROS_ERROR("Init oEngine Failed");
    }else{
        ROS_INFO("Success Init oEngine");
    }

    /* Initialize face-detection engine */
    if (oFDEngine != NULL) {
        eyeSight::destroyEngine(oFDEngine);
    }
    oFDVideoConfig.bFlip = false;
    oFDVideoConfig.nWidth = iCameraWidth;
    oFDVideoConfig.nHeight = iCameraHeight;
    oFDVideoConfig.tVideoFormat = KYUV422_YUYV;
    oFDVideoConfig.nFps = iCameraSamplingRate;
    oFDVideoConfig.bMirror = true;
    oFDVideoConfig.nRotateByTheta = 0;
    static ConfigManager *FDpCfg = new ConfigManager(0, NULL);
    FDpCfg->setProduct(iFDProductId);
    //FDpCfg->setFaceDetection(true,5);
    FDpCfg->m_pUserAnalysisConfig->m_bLandmarkDetector=true;
    FDpCfg->m_pUserAnalysisConfig->m_bLandmarkLocalization=true;
    FDpCfg->m_pUserAnalysisConfig->m_bUpperBodyProcess=true;
    FDpCfg->m_pUserAnalysisConfig->m_bExpression=true;

    //FDpCfg->m_pUserAnalysisConfig->m_bHeadPoseLM=true;
    //FDpCfg->m_pUserAnalysisConfig->m_bAttributesLM=true;
    //FDpCfg->m_pUserAnalysisConfig->m_bDummyLandmarksDetector=true;

    FDpCfg->m_pUserAnalysisConfig->m_bRecognizePerson=true;
    //FDpCfg->m_pUserAnalysisConfig->m_bDummyLandmarksDetector=true;
    //FDpCfg->m_pUserAnalysisConfig->m_bDummyLandmarksDetector=true;


    oFDEngine = eyeSight::createEngineByConfig(oFDVideoConfig, FDpCfg);
    //oFDEngine = eyeSight::createEngine(oFDVideoConfig, iFDProductId, NULL);
}

int es_stopEngine() {
    if (oEngine != NULL) {
        eyeSight::destroyEngine(oEngine);
        oEngine = NULL;
    }
    if (oFDEngine != NULL) {
        eyeSight::destroyEngine(oFDEngine);
        oFDEngine = NULL;
    }
    return 0;
}

const char *es_getEngineVersion() {

    if (oEngine != NULL) {
        static char sVersion[256] = { 0 };

        if (oEngine != NULL) {
            strncpy(sVersion, oEngine->GetCoreVersion(false), 255);
        } else {
            strcpy(sVersion, "Engine is not created.");
        }
        return sVersion;
    } else {
        return "ERROR. Engine is not created!";
    }
}

const char *es_getFDEngineVersion() {
    if (oFDEngine != NULL) {
        static char sVersion[256] = { 0 };

        if (oFDEngine != NULL) {
            strncpy(sVersion, oFDEngine->GetCoreVersion(false), 255);
        } else {
            strcpy(sVersion, "Engine is not created.");
        }
        return sVersion;
    } else {
        return "ERROR. FD Engine is not created!";
    }
}

void processFDFrame(unsigned char * oData) {
    if (oFDEngine != NULL) {
        oFDEyeSightOutput = oFDEngine->processFrame((unsigned char *) oData, -1);

        if (oFDEyeSightOutput != NULL) {
            //ROS_INFO("Success Handle Face");
            if ((oFDEyeSightOutput->m_pFaceDetectionOutput != NULL)) {
                FaceDataStruct *oFaceStruct =
                        oFDEyeSightOutput->m_pFaceDetectionOutput->m_pFacesData;
                if ((oFaceStruct != NULL) && (oFDEyeSightOutput->m_pFaceDetectionOutput->m_nNumOfFaces > 0)) {
                    for (int i = 0; i < oFDEyeSightOutput->m_pFaceDetectionOutput->m_nNumOfFaces; ++i) {
                        DBG_vPrintf(FACE_DBG, "\nFaces[%d]:, Gender:", i+1);
                        if (oFaceStruct[i].bIsValid) {
                            /* Print gender: Male/Female/Unknown */
                            if (oFaceStruct[i].nPersonGender == 0) {
                                DBG_vPrintf(FACE_DBG, "M, ");
                            } else if (oFaceStruct[i].nPersonGender == 1) {
                                DBG_vPrintf(FACE_DBG, "F, ");
                            } else {
                                DBG_vPrintf(FACE_DBG, "?, ");
                            }
                            DBG_vPrintf(FACE_DBG, "Age:%d, ", oFaceStruct[i].nPersonAge);
                            DBG_vPrintf(FACE_DBG, "LeftEyeOpenProb:%d, ", oFaceStruct[i].nLeftEyeOpenProb);
                            DBG_vPrintf(FACE_DBG, "RightEyeOpenProb:%d, ", oFaceStruct[i].nRightEyeOpenProb);
                            /* Expression Detection*/
                            if(oFaceStruct[i].eExpression>0){
                                DBG_vPrintf(FACE_DBG, "Expression:smile");
                                M4_Publisher("smile");
                            }
                            if(oFaceStruct[i].eExpression==0){
                                DBG_vPrintf(FACE_DBG, "Expression:neutral");
                                M4_Publisher("neutral");
                            }

                            if(cv_window){
                                /* Facial Landmarks Detection */
                                if(oFaceStruct[i].nFacialLandmarksValid>0){
                                    //printf("Facial Landmarks : %d \n\t",oFaceStruct[i].m_nNumOfLandmarks);
                                    for(int jj = 0;jj<oFaceStruct[i].m_nNumOfLandmarks;jj++){
                                        //printf("No.%d = %d,%d",jj,oFaceStruct[i].m_nFacialLandmarksX[jj],oFaceStruct[i].m_nFacialLandmarksY[jj]);
                                        cv::Point a = cv::Point(iCameraWidth - oFaceStruct[i].m_nFacialLandmarksX[jj], oFaceStruct[i].m_nFacialLandmarksY[jj]);
                                        cv::Point b = cv::Point(iCameraWidth - oFaceStruct[i].m_nFacialLandmarksX[jj] + 1, oFaceStruct[i].m_nFacialLandmarksY[jj] + 1);
                                        rectangle(resultM, a, b, cv::Scalar(255,0,0), 3);
                                    }
                                }
                                /*Facial Area*/
                                cv::Point f_x = cv::Point(iCameraWidth - oFaceStruct[i].nCenterX - oFaceStruct[i].nWidth/2, oFaceStruct[i].nCenterY - oFaceStruct[i].nHeight/2);
                                cv::Point f_y = cv::Point(iCameraWidth - oFaceStruct[i].nCenterX + oFaceStruct[i].nWidth/2+1, oFaceStruct[i].nCenterY + oFaceStruct[i].nHeight/2+1);
                                rectangle(resultM, f_x, f_y, cv::Scalar(255,0,0), 3);

                                /*Upper Body Detection*/
                                double cx = oFaceStruct[i].sUpperBody[0];
                                double cy = oFaceStruct[i].sUpperBody[1];
                                double W = oFaceStruct[i].sUpperBody[2];
                                double H = oFaceStruct[i].sUpperBody[3];

                                cv::Point a = cv::Point(cx - W / 2.0, cy - H / 2.0);
                                cv::Point b = cv::Point(cx + W / 2.0, cy + H / 2.0);
                                //cv::Point b = cv::Point(oFaceStruct[i].sUpperBody[0] + oFaceStruct[i].sUpperBody[2], oFaceStruct[i].sUpperBody[1] + oFaceStruct[i].sUpperBody[3]);
                                if(cx!=-1){
                                    rectangle(resultM, a, b, cv::Scalar(0,0,255), 10);
                                }
                                try {
                                    if(!resultM.empty()){
                                        imshow("view", resultM);
                                    }
                                }catch (cv::Exception &ex){
                                    ROS_ERROR("%s", ex.what());
                                }
                            }

                        }
                    }
                }
            }
        }else{
            ROS_ERROR("oFDEyeSightOutput is NULL");
        }
    }
}

void processFrame(unsigned char * oData) {
    int iMouseType;
    int iMouseX;
    int iMouseY;

    if(NULL == oData){
        ROS_ERROR("invaild pointer");
        return;
    }
    if (oEngine != NULL) {
        oEyeSightOutput = oEngine->processFrame((unsigned char *) oData, -1);

        if (oEyeSightOutput != NULL) {
            //ROS_INFO("Success Handle Gesture");
            if (oEyeSightOutput->m_pEyeSignOutput[0] != NULL) {
                eyeSignInfo *pDetectedHand = &oEyeSightOutput->m_pEyeSignOutput[0]->m_pEyeSignInfo[0];
                iMouseType = pDetectedHand->m_sOutputPoint.eType;
                iMouseX = pDetectedHand->m_sOutputPoint.nXmap;
                iMouseY = pDetectedHand->m_sOutputPoint.nYmap;
                if (iMouseType > 0) {
                    NOT_vPrintf(GESTURE_DBG, "\nGesture: Type=%d, X=%d, Y=%d",
                           iMouseType, iMouseX, iMouseY);
                }else{
                    //ROS_ERROR("iMouseType < 0");
                }
            }else{
                ROS_ERROR("oEyeSightOutput->m_pEyeSignOutput[0] is NULL");
            }
        }else{
            ROS_ERROR("oEyeSightOutput is NULL");
        }
    }else{
        ROS_ERROR("Eyesight Engine is not ready\n");
    }
}

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    try{
        cv::Mat srcImg = cv_bridge::toCvShare(msg, "rgb8")->image;

        Mat yuvImg;
        cvtColor(srcImg, yuvImg, CV_BGR2YUV);//YUYV444 CV_BGR2YUV CV_YUV2BGR_YUYV

        vector<Mat> mv;
        Mat imageY(srcImg.rows,srcImg.cols,1);
        Mat imageU(srcImg.rows,srcImg.cols,1);
        Mat imageV(srcImg.rows,srcImg.cols,1);
        split(yuvImg, (vector<Mat>&)mv);
        imageY = mv[0].clone();
        imageU = mv[1].clone();
        imageV = mv[2].clone();
        //ROS_INFO("Y Channels:%d, HW:[%d %d]", imageY.channels(), imageY.rows, imageY.cols);
        //ROS_INFO("Y:[%d]",imageY.ptr<uchar>(0)[0]);
        //ROS_INFO("U:[%d]",imageU.ptr<uchar>(0)[0]);
        //ROS_INFO("V:[%d]",imageV.ptr<uchar>(0)[0]);

        int buflen = srcImg.rows * srcImg.cols * srcImg.channels() * 2 / 3;
        unsigned char *dest = new unsigned char[buflen];
        memset(dest, 0, buflen);
        int j = 0;
        int flag = 0;
        for (int i = 0; i < buflen; i = i + 2) {
            dest[i] = imageY.ptr<uchar>(0)[j];
            if(flag == 0){
                dest[i+1] = imageU.ptr<uchar>(0)[j];
                //dest[i+2] = imageV.ptr<uchar>(0)[j+1];
                flag = 1;
            } else{
                flag = 0;
                dest[i+1] = imageV.ptr<uchar>(0)[j];
                //dest[i+2] = imageU.ptr<uchar>(0)[j+1];
            }
            j++;
        }
        if(cv_window){
            Mat srcM(iCameraHeight, iCameraWidth, CV_8UC2, (unsigned char*)dest);
            cv::cvtColor(srcM, resultM, CV_YUV2BGR_YUYV);
            if(!resultM.empty()) {
                imshow("view", resultM);//CV
            }
        }

        processFrame(dest);
        processFDFrame(dest);
        delete[] dest;
    }catch (cv_bridge::Exception& e){
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

int main(int argc, char **argv)
{
    printf("eyesight node start...\n");

    signal(SIGTERM, vQuitSignalHandler);/* Install signal handlers */
    signal(SIGINT,  vQuitSignalHandler);
    es_startEngine();
    printf("Eyesight Version: %s \n", es_getEngineVersion());

    ros::init(argc, argv, "eyesight_node");

    ros::NodeHandle nodeM4;
    pubM4 = nodeM4.advertise<std_msgs::String>("M4Motion", 10);

    ros::NodeHandle n_camera;
    n_camera.param("/cv_window", cv_window, 0);
    if(cv_window){
        NOT_vPrintf(1, "cv_window:%d\n", cv_window);
        if(cv_window){
            namedWindow("view");//CV
            startWindowThread();//CV
        }
    }else{
        WAR_vPrintf(1, "Can't Get Param\n");
    }
    image_transport::ImageTransport it(n_camera);
    image_transport::Subscriber sub_camera = it.subscribe("camera/image", 1, imageCallback);

    ros::Rate loop_rate(10);
    ros::spin();
    es_stopEngine();
    if(cv_window)
        destroyWindow("view");//CV

    return 0;
}

static void vQuitSignalHandler (int sig)
{
    printf("Exit...\n");
    es_stopEngine();
    return;
}

