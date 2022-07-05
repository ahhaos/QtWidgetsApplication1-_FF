#pragma once

#include <QObject>
#include <QtCore/qobject.h>
#define Mode_default						0		//Ĭ�Ϸ���ģʽ��һ��Ϊ��ǰ�����ٶȡ��߶ȱ���
#define Mode_PositionFollow					1		//�»�ģʽ
#define Mode_PositionFollow_V				2		//Ŀ����Ƶ�ģʽ��������������ٶ�
#define Mode_ManualOperation				3		//���ݸ˷���ģʽ
#define Mode_Waypoint						4		//��·�����ģʽ
#define Mode_Waypoint_2						5		//��·�����ģʽ_2
#define Mode_ZhuoJianFangZhen				6		//�Ž�����ģʽ
//#define Mode_TargetSequence					6		//Ŀ������ģʽ
//#define Mode_ClassicSceneNavigation			7		//���ͳ�������ģʽ

#include "Control/CloseLoopModel.h"
#include "wgs_conversions.h"
//#include "Read_txt.h"
#include "pathGeneration.h"
//#include "trackGeneration.h"
#include "PID.h"


struct Mode_default_VxVyVxyz		//���ڴ洢�л���Ĭ�Ϸ���ģʽʱ�ĸ���������ٶ�
{
	double Vx;			//ԭʼ�����ٶ�
	double Vy;			//ԭʼ�����ٶ�
	double Vxyz;		//ԭʼ������
	double dZ;			//ԭʼ�߶�
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
	double Xtt; //����������
	double Ytt;
	double Ztt;

	double Xdd; //��������
	double Ydd;
	double Zdd;

	std::vector<std::vector<double>>::iterator  targetSequence_it;
	std::vector<double>::iterator target_it;

	
//
	void Update();
	
	double Command_VKH[3] = { 80,0,2800 };			//�洢Ӧ��ָ���ٶȡ����򡢸߶�
	double Command_XYZV[4] = { 5000,0,2800,80 };			//�洢Ŀ�����ꡢ�ٶ�
	double Command_Manual[4] = { 0,0,0,0 };				//�洢�ֶ�����ָ����������桢����桢����
	double Command_xiaHua[3] = { 70,-3.5/180*PI,0};				//�»�ָ��ٶȣ��Ƕȣ��Ž��߶�
	double* Command_XYZ;
	double YZError[2] = { 0,0 };
	double YZ_V[2] = { 0,0 };
	double ZhuoJianZongV = 50;
	double* getNextTrackNode(double X_now, double Y_now, double Z_now, double V, double X_next, double Y_next, double Z_next, long long int i);
	long long int i = 0;
	int m_landing_bool;
	unsigned int currentMode;
	double xiaHuaChi;										//�»�ģʽ��ʼʱ�ĺ���
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


