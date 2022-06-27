#include <vector>
//#include <QString>

//带宽参数
extern double data_bandwidth_dWX;
extern double data_bandwidth_dWY;
extern double data_bandwidth_dWZ;
extern double data_bandwidth_dWV;
extern double data_bandwidth_dWKh;
extern double data_bandwidth_dWGama;
extern double data_bandwidth_dWAlpha;
extern double data_bandwidth_dWBeta;
extern double data_bandwidth_dWMu;
extern double data_bandwidth_dWp;
extern double data_bandwidth_dWq;
extern double data_bandwidth_dWr;

//最大推力
extern double data_model_dThrustMax;
//最小推力
extern double data_model_dThrustMin;
//最大转转向速度
extern double data_model_dKh_dMax;
//???
extern double data_model_dWGama_I;
//Mu导数传递函数时间常数
extern double data_model_dMu_dT;
//Mu导数幅限
extern double data_model_dMu_dMax;
//积分饱和
extern double data_model_dGama_IMax;

//副翼偏角
extern double data_model_ddeltaa;
//鸭翼舵偏角
extern double data_model_ddeltac;
//方向舵偏角
extern double data_model_ddeltar;
//推力矢量偏角
extern double data_model_ddeltay;
//推力矢量偏角
extern double data_model_ddeltaz;
//推力
extern double data_model_dThrust;

//XYZ方向PID参数以及积分参数限制
extern double data_PID_X_KP;
extern double data_PID_X_KI;
extern double data_PID_X_KD;
extern double data_PID_X_KI_Limit;

extern double data_PID_Y_KP;
extern double data_PID_Y_KI;
extern double data_PID_Y_KD;
extern double data_PID_Y_KI_Limit;

extern double data_PID_Z_KP;
extern double data_PID_Z_KI;
extern double data_PID_Z_KD;
extern double data_PID_Z_KI_Limit;

//飞机起始坐标
extern double data_origin_X;
extern double data_origin_Y;
extern double data_origin_Z;
//飞机起始经纬高
extern double data_origin_L0;
extern double data_origin_B0;
extern double data_origin_H0;
//飞机的当前经纬高
extern double L;
extern double B;//纬度
extern double H;


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//飞机起始速度
extern double data_origin_V;

//飞机起始姿态角
extern double data_origin_Alpha;
extern double data_origin_Gama;
extern double data_origin_Chi;
extern double data_origin_Beta;
extern double data_origin_Mu;

//飞机起始角速度
extern double data_origin_p;
extern double data_origin_q;
extern double data_origin_r;


//环境参数
//重力加速度g
extern double data_model_dg;
//大气密度
extern double data_model_dRho;

//飞机参数
//飞机质量
extern double data_model_dM;
//机翼面积
extern double data_model_dS;
//机翼展长
extern double data_model_db;
//平均空气动力弦
extern double data_model_dC_;
//发动机喷管距质心距离
extern double data_model_dxT;
//副翼舵最大
extern double data_model_da_max;
//方向舵最大
extern double data_model_dr_max;
//鸭翼舵最大
extern double data_model_dc_max;
//推力矢量舵最大
extern double data_model_dy_max;
//推力矢量舵最大
extern double data_model_dz_max;

//转动惯量
extern double data_model_dIx;
extern double data_model_dIy;
extern double data_model_dIz;
extern double data_model_dIxz;

//期望的恒定飞机速度
extern double data_expect_speed;

//理想飞机东向速度
extern double data_expect_VelEast;
//理想船速
extern double data_expect_shipspeed;


//仿真周期(ms)
extern double data_time;
//仿真时延(ms)
extern double data_timedelay;

//输入接口

	//偏差值信息

extern double data_diff_output_ID;		//发送节点ID
extern double data_diff_input_ID;		//接收节点ID
extern double data_diff_timestamp;		//时间戳
extern double data_diff_timedelay;		//时延
extern double data_diff_info_ID;		//消息ID
extern double data_diff_vertical;		//纵向偏差
extern double data_diff_Horizontal;		//横向偏差

//时间同步块

extern double data_time_output_ID;		//发送节点ID
extern double data_time_input_ID;		//接收节点ID
extern double data_time_timestamp;		//时间戳
extern double data_time_info_ID;		//消息ID

//状态管理数据块

extern double data_state_output_ID;		//发送节点ID
extern double data_state_input_ID;		//接收节点ID
extern double data_state_timestamp;		//时间戳
extern double data_state_info_ID;		//消息ID
extern double data_state_state;			//运行状态

extern double data_shiptail_u;		//舰尾流X轴分量
extern double data_shiptail_v;		//舰尾流Y轴分量
extern double data_shiptail_w;		//舰尾流Z轴分量

extern double data_Wind_Vx;			//风速X轴分量
extern double data_Wind_Vy;			//风速Y轴分量
extern double data_Wind_Vz;			//风速Z轴分量


extern	double SimulationTime;					//用于计算仿真运行时间


												//接收到的偏差值
extern double X_c;
extern double Y_c;
extern double Z_c;

// Aerodynamic force coefficients of F/A-18
extern double CDa4, CDa3 , CDa2 , CDa1 , CDa0 ;
extern double CD0;
extern double CDde3, CDde2 , CDde1 , CDde0 ;
extern double CLa3 , CLa2 , CLa1 , CLa0 ;
extern double CLde3 , CLde2 , CLde1 , CLde0 ;
extern double CYb2 , CYb1 , CYb0 ;
extern double CYda3 , CYda2 , CYda1 , CYda0 ;
extern double CYdr3 , CYdr2 , CYdr1 , CYdr0 ;

extern double Clb4 , Clb3 , Clb2 , Clb1 , Clb0 ;
extern double Clda3 , Clda2 , Clda1 , Clda0 ;
extern double Cldr3 , Cldr2, Cldr1 , Cldr0 ;
extern double Clp1 , Clp0 ;
extern double Clr2 , Clr1 , Clr0 ;

extern double Cma2 , Cma1 , Cma0 ;
extern double Cmde2 , Cmde1 , Cmde0 ;
extern double Cmq3 , Cmq2 , Cmq1 , Cmq0 ;

extern double Cnb2 , Cnb1 , Cnb0 ;
extern double Cnda3 , Cnda2 , Cnda1 , Cnda0 ;
extern double Cndr4 , Cndr3 , Cndr2 , Cndr1 , Cndr0 ;
extern double Cnp1 , Cnp0;
extern double Cnr1 , Cnr0 ;


extern int netSendTime;

//extern QYTopicSender* pstSender

extern double VXdd, VYdd, VZdd;//地心地固系的速度

extern int netID;
extern char netTopic[];


extern double target_1[] ;
extern double target_2[] ;


extern std::vector<std::vector<double>> targetNode_L_B_H;


extern std::vector<std::vector<double>> targetNode_X_Y_Z;

extern std::vector<std::string> targetNode_Name;

extern std::string serialPortName;

extern int serialBaudRate;

extern int leverUdpPort;
extern double leverPitchCommandProportion;
extern double leverYawCommandProportion;

extern double arriveDistanceFlag;
//extern HANDLE g_CardHandle;
//extern BOOL g_isRun

extern double VY_MAXLimt;
extern double VZ_MAXLimt;

extern bool isSerialPortSend ;

// 偏差着舰UDP接收端口
extern int zhuoJianErrorUdpPort;

// 着舰时x向速度
extern double zhuoJianXV;

extern std::string udpSendTargetIP;
extern int udpSendTargetPort;

