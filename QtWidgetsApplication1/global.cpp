#include "global.h"
#include <QString>
//#include "ZHHK429_dll.h"
#include <vector>

//仿真周期(ms)
double data_time = 25;
//仿真时延(ms)
double data_timedelay = 0;

//带宽参数
double data_bandwidth_dWX = 0.3;
double data_bandwidth_dWY = 0.3;
double data_bandwidth_dWZ = 0.3;
double data_bandwidth_dWV = 1;
double data_bandwidth_dWKh = 0.8;
double data_bandwidth_dWGama = 1.2;
double data_bandwidth_dWAlpha = 2;
double data_bandwidth_dWBeta = 2;
double data_bandwidth_dWMu = 1.5;
double data_bandwidth_dWp = 10;
double data_bandwidth_dWq = 10;
double data_bandwidth_dWr = 10;

double data_model_dThrustMax = 1250000;
double data_model_dThrustMin = 10000;
double data_model_dKh_dMax = 0.2;
double data_model_dWGama_I = 0.05;
double data_model_dMu_dT = 4;
double data_model_dMu_dMax = 2.5;
double data_model_dGama_IMax = 3.1415926535897932384626 / 8;

//副翼偏角
double data_model_ddeltaa = 0;
//鸭翼舵偏角
double data_model_ddeltac = 0;
//方向舵偏角
double data_model_ddeltar = 0;
//推力矢量偏角
double data_model_ddeltay = 0;
//推力矢量偏角
double data_model_ddeltaz = 0;
//推力
double data_model_dThrust = 20000;

//PID参数
double data_PID_X_KP = 1;
double data_PID_X_KI = 0.2;
double data_PID_X_KD = 0;
double data_PID_X_KI_Limit = 10;

double data_PID_Y_KP = 1;
double data_PID_Y_KI = 0.5;
double data_PID_Y_KD = 0;
//double data_PID_Y_KD = 1;
double data_PID_Y_KI_Limit = 10;

double data_PID_Z_KP =1;
double data_PID_Z_KI = 0.2;
double data_PID_Z_KD = 0;
double data_PID_Z_KI_Limit = 10;

//环境参数
double data_model_dg = 9.8;
double data_model_dRho = 1.11164;

//飞机参数
//double data_model_dM = 15097.3927;
//double data_model_dS = 37.1612;
//double data_model_db = 11.4056;
//double data_model_dC_ = 3.5112;
//
//double data_model_da_max = 30;
//double data_model_dr_max = 30;
//double data_model_dc_max = 90;
//double data_model_dy_max = 30;
//double data_model_dz_max = 30;
//
//double data_model_dxT = 8.50;
//
////转动惯量
//double data_model_dIx = 31183.8131;
//double data_model_dIy = 205125.7669;
//double data_model_dIz =230414.4835;
//double data_model_dIxz = -4028.1315;

//飞机参数
double data_model_dM = 10617;
double data_model_dS = 57.7;
double data_model_db = 13.11;
double data_model_dC_ = 4.40;

double data_model_da_max = 30;
double data_model_dr_max = 30;
double data_model_dc_max = 90;
double data_model_dy_max = 30;
double data_model_dz_max = 30;

double data_model_dxT = 8.50;

//转动惯量
double data_model_dIx = 22682;
double data_model_dIy = 77095;
double data_model_dIz = 95561;
double data_model_dIxz = 1125;

double data_expect_speed = 70;


//理想飞机东向速度
double data_expect_VelEast = 66.667;
//理想船速
double data_expect_shipspeed = 11.111;

//飞机起始坐标
double data_origin_X = 0;
double data_origin_Y = 0;
double data_origin_Z = 400;
//飞机起始经纬高
double data_origin_L0 = 119.55;	//初始经度
double data_origin_B0 = 40;//初始维度
double data_origin_H0 = 400;

// 东北天坐标系原点在经纬高坐标系中的位置，及参考点
double lla_ref[3] = { data_origin_B0 ,data_origin_L0 ,0 };


//飞机的当前经纬高
double L= data_origin_L0;
double B= data_origin_B0;//纬度
double H= data_origin_H0;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//飞机起始速度
double data_origin_V = 66;			

//飞机起始姿态角
double data_origin_Alpha = 0.1483;
double data_origin_Gama = 0;
double data_origin_Chi = 0;
//double data_origin_Chi = 3.1415927/180*10;
double data_origin_Beta = 0;
double data_origin_Mu = 0;

//飞机起始角速度
double data_origin_p = 0;
double data_origin_q = 0;
double data_origin_r = 0;

double data_shiptail_u = 0;
double data_shiptail_v = 0;
double data_shiptail_w = 0;

double data_Wind_Vx = 1;			//风速X轴分量
double data_Wind_Vy = 2;			//风速Y轴分量
double data_Wind_Vz = 3;			//风速Z轴分量


double SimulationTime = 0;			//当前仿真时间


// Aerodynamic force coefficients of F/A-18
double CDa4 = 1.46, CDa3 = -5.73, CDa2 = 6.39, CDa1 = -0.19, CDa0 = -1.49;
double CD0 = 1.50;
double CDde3 = -3.856, CDde2 = 4.23, CDde1 = -0.27, CDde0 = 0.03;
double CLa3 = 1.16, CLa2 = -5.42, CLa1 = 5.67, CLa0 = -0.02;
double CLde3 = 2.18, CLde2 = -2.69, CLde1 = 0.4, CLde0 = 0.57;
double CYb2 = -0.19, CYb1 = 0.26, CYb0 = -0.73;
double CYda3 = -0.85, CYda2 = 1.53, CYda1 = -0.24, CYda0 = -0.16;
double CYdr3 = 0.93, CYdr2 = -1.69, CYdr1 = 0.4, CYdr0 = 0.2;

double Clb4 = -1.61, Clb3 = 2.38, Clb2 = -0.36, Clb1 = -0.41, Clb0 = -0.05;
double Clda3 = 0.19, Clda2 = -0.26, Clda1 = -0.05, Clda0 = 0.14;
double Cldr3 = -0.02, Cldr2 = 0.01, Cldr1 = 0.00, Cldr0 = 0.01;
double Clp1 = 0.23, Clp0 = -0.35;
double Clr2 = -1.08, Clr1 = 0.78, Clr0 = 0.19;

double Cma2 = -1.28, Cma1 = 0.51, Cma0 = -0.08;
double Cmde2 = 0.93, Cmde1 = -0.32, Cmde0 = -0.9;
double Cmq3 = 64.71, Cmq2 = -68.56, Cmq1 = 10.99, Cmq0 = -4.11;

double Cnb2 = -0.38, Cnb1 = 0.03, Cnb0 = 0.08;
double Cnda3 = 0.26, Cnda2 = -0.34, Cnda1 = 0.05, Cnda0 = 0.01;
double Cndr4 = 0.38, Cndr3 = -0.89, Cndr2 = 0.55, Cndr1 = -0.01, Cndr0 = -0.07;
double Cnp1 = -0.08, Cnp0 = 0.07;
double Cnr1 = -0.13, Cnr0 = -0.43;





double VXdd, VYdd, VZdd;//地心地固系的速度




std::vector<std::vector<double>> targetNode_L_B_H;

std::vector<std::vector<double>> targetNode_X_Y_Z;

std::vector<std::string> targetNode_Name;


// 串口名
std::string serialPortName;

// 串口频率
int serialBaudRate=460800;


// 手动操纵UDP接收端口
int leverUdpPort = 10001;




double leverPitchCommandProportion = 0.0001;
double leverYawCommandProportion = 0.0000001;
//int throttleUdpPort = 10001;

double arriveDistanceFlag = 1;
//HANDLE g_CardHandle;
//BOOL g_isRun = FALSE;

// 纵向和侧向矫正速度
double VY_MAXLimt = 1000;
double VZ_MAXLimt = 10;

// 偏差着舰UDP接收端口
int zhuoJianErrorUdpPort = 10033;


//// 着舰时x向速度 x向速度
double zhuoJianXV = 55;

// udp 发送目标IP和端口
std::string udpSendTargetIP = "127.0.0.1";
int udpSendTargetPort = 4001;

// 航路点追踪模式或者偏差着舰模式的航路点追踪速度
double follow_V = 66.6;

// 存储着舰刨面信息
std::vector<std::vector<double>> landingPlaningInfo;

// 理想着舰点的BLH
double shipPointBLH[3] = { 40.0, 119.7, 0 };

// 着舰引导模式
int zhuoJianMode = 0;		// 0 航路点模式，无偏差导引
							// 1 光电
							// 2 雷达
							// 3 卫星
							// 4 雷达光电融合