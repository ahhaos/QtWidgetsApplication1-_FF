#include <vector>
//#include <QString>

//�������
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

//�������
extern double data_model_dThrustMax;
//��С����
extern double data_model_dThrustMin;
//���תת���ٶ�
extern double data_model_dKh_dMax;
//???
extern double data_model_dWGama_I;
//Mu�������ݺ���ʱ�䳣��
extern double data_model_dMu_dT;
//Mu��������
extern double data_model_dMu_dMax;
//���ֱ���
extern double data_model_dGama_IMax;

//����ƫ��
extern double data_model_ddeltaa;
//Ѽ���ƫ��
extern double data_model_ddeltac;
//�����ƫ��
extern double data_model_ddeltar;
//����ʸ��ƫ��
extern double data_model_ddeltay;
//����ʸ��ƫ��
extern double data_model_ddeltaz;
//����
extern double data_model_dThrust;

//XYZ����PID�����Լ����ֲ�������
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

//�ɻ���ʼ����
extern double data_origin_X;
extern double data_origin_Y;
extern double data_origin_Z;
//�ɻ���ʼ��γ��
extern double data_origin_L0;
extern double data_origin_B0;
extern double data_origin_H0;
//�ɻ��ĵ�ǰ��γ��
extern double L;
extern double B;//γ��
extern double H;


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//�ɻ���ʼ�ٶ�
extern double data_origin_V;

//�ɻ���ʼ��̬��
extern double data_origin_Alpha;
extern double data_origin_Gama;
extern double data_origin_Chi;
extern double data_origin_Beta;
extern double data_origin_Mu;

//�ɻ���ʼ���ٶ�
extern double data_origin_p;
extern double data_origin_q;
extern double data_origin_r;


//��������
//�������ٶ�g
extern double data_model_dg;
//�����ܶ�
extern double data_model_dRho;

//�ɻ�����
//�ɻ�����
extern double data_model_dM;
//�������
extern double data_model_dS;
//����չ��
extern double data_model_db;
//ƽ������������
extern double data_model_dC_;
//��������ܾ����ľ���
extern double data_model_dxT;
//��������
extern double data_model_da_max;
//��������
extern double data_model_dr_max;
//Ѽ������
extern double data_model_dc_max;
//����ʸ�������
extern double data_model_dy_max;
//����ʸ�������
extern double data_model_dz_max;

//ת������
extern double data_model_dIx;
extern double data_model_dIy;
extern double data_model_dIz;
extern double data_model_dIxz;

//�����ĺ㶨�ɻ��ٶ�
extern double data_expect_speed;

//����ɻ������ٶ�
extern double data_expect_VelEast;
//���봬��
extern double data_expect_shipspeed;


//��������(ms)
extern double data_time;
//����ʱ��(ms)
extern double data_timedelay;

//����ӿ�

	//ƫ��ֵ��Ϣ

extern double data_diff_output_ID;		//���ͽڵ�ID
extern double data_diff_input_ID;		//���սڵ�ID
extern double data_diff_timestamp;		//ʱ���
extern double data_diff_timedelay;		//ʱ��
extern double data_diff_info_ID;		//��ϢID
extern double data_diff_vertical;		//����ƫ��
extern double data_diff_Horizontal;		//����ƫ��

//ʱ��ͬ����

extern double data_time_output_ID;		//���ͽڵ�ID
extern double data_time_input_ID;		//���սڵ�ID
extern double data_time_timestamp;		//ʱ���
extern double data_time_info_ID;		//��ϢID

//״̬�������ݿ�

extern double data_state_output_ID;		//���ͽڵ�ID
extern double data_state_input_ID;		//���սڵ�ID
extern double data_state_timestamp;		//ʱ���
extern double data_state_info_ID;		//��ϢID
extern double data_state_state;			//����״̬

extern double data_shiptail_u;		//��β��X�����
extern double data_shiptail_v;		//��β��Y�����
extern double data_shiptail_w;		//��β��Z�����

extern double data_Wind_Vx;			//����X�����
extern double data_Wind_Vy;			//����Y�����
extern double data_Wind_Vz;			//����Z�����


extern	double SimulationTime;					//���ڼ����������ʱ��


												//���յ���ƫ��ֵ
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

extern double VXdd, VYdd, VZdd;//���ĵع�ϵ���ٶ�

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

// ƫ���Ž�UDP���ն˿�
extern int zhuoJianErrorUdpPort;

// �Ž�ʱx���ٶ�
extern double zhuoJianXV;

extern std::string udpSendTargetIP;
extern int udpSendTargetPort;

