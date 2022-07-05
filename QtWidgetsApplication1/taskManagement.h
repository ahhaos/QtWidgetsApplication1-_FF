#pragma once

#include <QObject>
#include <QtCore/qobject.h>
#define Mode_default						0		//默认飞行模式，一般为当前航向、速度、高度保持
#define Mode_PositionFollow					1		//下滑模式
#define Mode_PositionFollow_V				2		//目标点制导模式，单独输入飞行速度
#define Mode_ManualOperation				3		//操纵杆仿真模式
#define Mode_Waypoint						4		//航路点仿真模式
#define Mode_Waypoint_2						5		//航路点仿真模式_2
#define Mode_ZhuoJianFangZhen				6		//着舰仿真模式
//#define Mode_TargetSequence					6		//目标序列模式
//#define Mode_ClassicSceneNavigation			7		//典型场景导航模式

#include "Control/CloseLoopModel.h"
#include "wgs_conversions.h"
//#include "Read_txt.h"
#include "pathGeneration.h"
//#include "trackGeneration.h"
#include "PID.h"


struct Mode_default_VxVyVxyz		//用于存储切换到默认飞行模式时的各个方向的速度
{
	double Vx;			//原始东向速度
	double Vy;			//原始北向速度
	double Vxyz;		//原始航迹速
	double dZ;			//原始高度
};

class taskManagement:public QObject
{
	Q_OBJECT
public:
	taskManagement(CCloseLoopModel* clm_control);
	~taskManagement();
	CCloseLoopModel* clm_control_task;
	//trackGeneration* trackGenerator;
	pathGeneration* pathGenerator;
	pathGeneration* pathGenerator_2;
	int haveArrivedNodeNumber;
	Pid_control* PID_Chi;
	Pid_control* PID_H;
	//---------------------------------------
	WgsConversions* wgs_enuConversion;
	//CRead_txt* txt_transmit;
	double Xtt; //东北天坐标
	double Ytt;
	double Ztt;

	double Xdd; //地心坐标
	double Ydd;
	double Zdd;

	std::vector<std::vector<double>>::iterator  targetSequence_it;
	std::vector<double>::iterator target_it;

	
//
	void Update();
	
	double Command_VKH[3] = { 80,0,2800 };			//存储应飞指令速度、航向、高度
	double Command_XYZV[4] = { 5000,0,2800,80 };			//存储目标坐标、速度
	double Command_Manual[4] = { 0,0,0,0 };				//存储手动操作指令，副翼、升降舵、方向舵、油门
	double Command_xiaHua[3] = { 70,-3.5/180*PI,0};				//下滑指令，速度，角度，着舰高度
	double* Command_XYZ;
	double YZError[2] = { 0,0 };
	double YZ_V[2] = { 0,0 };
	double ZhuoJianZongV = 50;
	double* getNextTrackNode(double X_now, double Y_now, double Z_now, double V, double X_next, double Y_next, double Z_next, long long int i);
	long long int i = 0;
	int m_landing_bool;
	unsigned int currentMode;
	double xiaHuaChi;										//下滑模式开始时的航向
	double baseChi_deg = 0;
	//int XVofset;
	//int YVofset;
protected:
	
	//Mode_default_VxVyVxyz defaultStatus;
public slots :
	void currentModeSet(unsigned int mode);

private:
	signals:
		void ModeChanged(unsigned int mode);
		void targetArrived(int arg);
		void drawExpect_Z();
		void serialSendSignal();
		void drawLandingPlaning();
};


