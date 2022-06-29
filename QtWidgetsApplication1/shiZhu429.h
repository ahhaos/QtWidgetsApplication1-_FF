#pragma once
#include "cav_l1.h"

#define tx_channel  0  // TX channel number,0 - 33
//#define rx_channel  0  // RX channel number,0 - 33 
#define DEVID (CAV_PRODUCT_PMCA429 | CAV_DEVID_BOARDNUM_01 | CAV_DEVID_CHANNELTYPE_A429)
struct simDataStruct_429
{
	float origin_Lon=0;						//初始位置经度		（度）
	float origin_Lat=0;						//初始位置纬度		（度）
	float inertial_Barometric_Altitude=0;		//惯性气压高度		（米）
	float chi=0;								//航向角			（度）
	float theta=0;							//俯仰角			（度）
	float phi=0;								//滚转角			（度）
	float acc_North=0;						//北向加速度		（m/s^2）
	float acc_Up=0;							//天向加速度		（m/s^2）
	float acc_East=0;							//东向加速度		（m/s^2）
	float vel_North=0;						//北向速度			（km/h）
	float vel_Up=0;							//天向速度			（km/h）
	float vel_East=0;							//东向速度			（km/h）
	float simControlWord=0;					//仿真控制字
	unsigned int currYear=0;					//当前日期_年
	unsigned int currMonth=0;					//当前日期_月
	unsigned int currDay=0;					//当前日期_日
	unsigned int currTime_h=0;				//当前时间_高位
	unsigned int currTime_l=0;				//当前时间_低位
	unsigned int sysSettingFaultWord=0;		//系统仿真故障字

};

#pragma pack(1)
typedef struct
{
	UINT32 nCheck : 1;	//校验和
	UINT32 nState : 2;	//状态位
	UINT32 nData : 21;	//数据值
	UINT32 nLabel : 8;	//标导位
}ARINC429DATA_ST1;
#pragma pack()
using namespace std;

class cav429
{
public:
	bool isInit;
	CAV_L0_UINT32 status, l0Version, l1Version, chanConfig;
	CAV_L0_UINT32 IPCoreVersion;
	CAV_L1_Tx_Parity  parity;
	CAV_L1_TX_BitDirection tx_bitdirection;
	CAV_L1_RX_BitDirection rx_bitdirection;
	CAV_L1_DataStructure data_constructure;


	ARINC429DATA_ST1 ARINC429_data_strc;
	CAV_L0_UINT32 ARINC429_label;
	CAV_L0_UINT32 ARINC429_data;

	cav429();
	~cav429();
	void init();

	void sendData();

	void close();

	void sendSimData(simDataStruct_429 myData);

private:
	unsigned int origin_Lon_Label = 0311;
	unsigned int origin_Lat_Label = 0310;
	unsigned int inertial_Barometric_Altitude_Label = 0361;
	unsigned int chi_Label = 0314;
	unsigned int theta_Label = 0324;
	unsigned int phi_Label = 0325;
	unsigned int acc_North_Label = 0363;
	unsigned int acc_Up_Label = 0364;
	unsigned int acc_East_Label = 0362;
	unsigned int vel_North_Label = 0366;
	unsigned int vel_Up_Label = 0360;
	unsigned int vel_East_Label = 0367;
	unsigned int simControlWord_Label = 0300;
	unsigned int currYear_Label = 0372;
	unsigned int currMonth_Label = 0372;
	unsigned int currDay_Label = 0372;
	unsigned int currTime_h_Label = 0373;
	unsigned int currTime_l_Label = 0374;
	unsigned int sysSettingFaultWord_Labe = 0301;

	float origin_Lon_1_LSB = 5825.422;
	float origin_Lat_1_LSB = 5825.422;
	float inertial_Barometric_Altitude_1_LSB = 32;
	float chi_1_LSB = 5825.422;
	float theta_1_LSB = 5825.422;
	float phi_1_LSB = 5825.422;
	float acc_North_1_LSB = 8192;
	float acc_Up_1_LSB = 8192;
	float acc_East_1_LSB = 8192;
	float vel_North_1_LSB = 256;
	float vel_Up_1_LSB = 256;
	float vel_East_1_LSB = 256;
};



