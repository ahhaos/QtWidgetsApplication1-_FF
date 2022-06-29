#include "cav_l1.h"

/* The DEVICE ID is a 32-bit value that identifies the following:
*		bits 28-31 = Backplane Type (0 = Simulated, 1 = PCI)
*		bits 20-27 = Board Type (0x10 = SIM-A429, 0x11 = TEST-A429, 0x12 = PMC-A4293, 0x13 = PC104P-A429, 0x14 = PCI-A429)
*		bits 16-19 = Board Number (0 to 15)
*      bits 8-15 = Channel Type (0x10 = 1553, 0x20 = A429)
*		bits 0-7 = Reserved,Default Value 0x00
*
*/
#include "shiZhu429.h"
#include <QDebug>


cav429::cav429()
{
	isInit = false;

}
cav429::~cav429()
{
}

void cav429::init()
{
	
	// 初始化CAV_L1库
	printf("Initializing Driver and Memory Management . . . ");
	
	status = CAV_L1_A429_InitDefault(DEVID, 10);
	
	//CAV_L0_UINT32 CAV_L1_A429_InitDefault(CAV_L0_UINT32 devID,CAV_L0_UINT32 numIQEntries)
	//用于初始化 A429 设备并为其分配中断队列。参数devID：设备标识符（具体定义见 2.1）。numIQEntries：待分配的中断队列深度。
	if (status != CAV_SUCCESS) {
		printf("ERROR %d on CAV_L1_A429_InitDefault\n", status);
		return;
	}
	printf("Success.\n\n");

	// 检查IPCore以及CAV_L1库版本号
	printf("Checking IPCore and API versions . . . ");
	status = CAV_L1_GetVersionInfo(DEVID, &IPCoreVersion, &l0Version, &l1Version);
	//获取固件、Layer 0 API 和 Layer 1 API 的版本信息。
	//CAV_L0_UINT32 CAV_L1_GetVersionInfo(CAV_L0_UINT32 devID,CAV_L0_UINT16 *peVersion,CAV_L0_UINT32 *layer0ApiVersion,CAV_L0_UINT32 *layer1ApiVersion)	//devID：设备标识符（具体定义见 2.1）。peVersion：固件信息。peVersion：固件信息。layer1ApiVersion：L1 层 API 版本信息。
	if (status == CAV_SUCCESS) {
		printf("Success.\n");
		printf("   Hardware version = %d.%d\n", (IPCoreVersion & 0x000000F0) >> 4, (IPCoreVersion & 0x0000000F));
		printf("   IPCore version = %d.%d\n", (IPCoreVersion & 0x0000F000) >> 12, (IPCoreVersion & 0x00000F00) >> 8);
		printf("   L0 API version = %d.%d.%d.%d\n", (l0Version & 0xFF000000) >> 24,
			(l0Version & 0x00FF0000) >> 16, (l0Version & 0x0000FF00) >> 8, l0Version & 0x000000FF);
		printf("   L1 API version = %d.%d.%d.%d\n\n", (l1Version & 0xFF000000) >> 24,
			(l1Version & 0x00FF0000) >> 16, (l1Version & 0x0000FF00) >> 8, l1Version & 0x000000FF);
	}
	else {
		printf("FAILURE - Error = %d\n\n", status);
		return;
	}
	// 检查通道配置
	printf("Checking Channel Configuration . . . ");
	status = CAV_L1_A429_GetConfig(DEVID, &chanConfig);
	//获取 A429 设备通道个数。
	//CAV_L0_UINT32 CAV_L1_A429_GetConfig(CAV_L0_UINT32 devID,CAV_L0_UINT32 *pChanConfig)
	//devID：设备标识符（具体定义见 2.1）。pChanConfig：存放通道个数的存储单元地址。
	if (status == CAV_SUCCESS) {
		printf("Success.\n");
		if (chanConfig > 0xFF)
		{
			printf("   Available channels = %dT%dR\n\n", (chanConfig & 0x0000FF00) >> 8, chanConfig & 0x000000FF);

		}
		else
			printf("   Available channels = %d\n\n", chanConfig);

	}
	else {
		printf("FAILURE - Error = %d\n\n", status);
		return;
	}

	///Setup TX Channel  
	//结构体 CAV_L1_TX_BitDirection 定义了发送的 32bit 数据的发送顺序，
	//可以通过设置 highBitPriority 和 LabelReversal 属性来改变发送顺序。
	//
	tx_bitdirection.highBitPriority = 0;
	tx_bitdirection.LabelReversal = 0;
	printf("Initializing TX Channel %d . . . ", tx_channel);
	//发送通道初始化并进行相关配置。
	status = CAV_L1_A429_TX_Channel_Init(DEVID, tx_channel, 100000, 2, &tx_bitdirection);
	//CAV_L0_UINT32 CAV_L1_A429_TX_Channel_Init
	//(
	//	CAV_L0_UINT32 devID,		//devID：设备标识符（具体定义见 2.1）。
	//	CAV_L0_UINT32 TxChanNum,	//TxChanNum：发送通道号（0 - 33）。
	//	CAV_L0_UINT32 BitRateHz,	//BitRateHz：发送的波特率 500bp/s– 300000bp/s。
	//	CAV_L0_UINT32 numTXCB,		//numTXCB：该发送通道分配的发送控制块个数。
	//	CAV_L1_TX_BitDirection *BitDir	//BitDir：指向存放接收数据位序的指针（具体定义见 3.7.6）。	//									//注：结构体中两个变量都设为 0 时，和之前的板卡功能相同。	//									详细信息请参考：附 1 ARINC A429 总线信号顺序说明发送消息位序说明。
	//	)	//
	if (status != CAV_SUCCESS) {
		printf("ERROR %d on CAV_L1_A429_TX_Channel_Init\n", status);
		return;
	}
	else
	{
		printf("Success\n\n");
	}
	//发送非周期消息时使能通道的函数。
	//注：在非周期消息发送的情况下，此函数在发送通道初始化完成后就调用。
	printf("Enabling the TX Channel %d", tx_channel);
	CAV_L1_A429_TX_Channel_Enable(DEVID, tx_channel);
	if (status != CAV_SUCCESS) {
		printf("ERROR %d on CAV_L1_A429_TX_Channel_Open\n", status);
		return;
	}
	else
	{
		printf("Success\n\n");
	}
	
	isInit = true;
}

void cav429::close()
{

	// 非周期消息使能
	CAV_L1_A429_TX_Channel_Disable(DEVID, tx_channel);

	printf("Closing TX Channel %d . . . ", tx_channel);
	//关闭通道
	status = CAV_L1_A429_TX_Channel_Close(DEVID, tx_channel);
	if (status != CAV_SUCCESS) {
		printf("ERROR %d on CAV_L1_A429_TX_Channel_Close\n", status);
	}
	else
	{
		printf("Success\n\n");
	}
}

void cav429::sendData()
{

	memset(&data_constructure, 0, sizeof(data_constructure));
	memcpy(&(data_constructure.Data_block), &ARINC429_data, sizeof(ARINC429_data));
	data_constructure.Label_num = ARINC429_label;
	CAV_L1_A429_TX_Channel_SendLabel(DEVID, tx_channel, &data_constructure, &parity);
	//CAV_L1_A429_TX_Channel_SendData(DEVID, tx_channel,0x12345678,&parity);
	printf("Sending Label . . . ");
	//status = CAV_L1_A429_TX_Channel_SendData(DEVID, tx_channel, 0X12345678,&parity);
	if (status != CAV_SUCCESS) {
		printf("ERROR %d on CAV_L1_A429_TX_Channel_SendLabel\n", status);
	}
	else {
		printf("Success.\n");
	}
}

void cav429::sendSimData(simDataStruct_429 myData)
{
	if (!isInit)
	{
		printf("ERROR CAV_L1_A429 have not initialized yet\n");
		qDebug() << "running2";
		return;
	}

	UINT32 tmp;
	// 发送初始位置经度
	memset(&tmp, 0, sizeof(tmp));
	tmp=( myData.origin_Lon*origin_Lon_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = origin_Lon_Label;
	sendData();

	// 发送初始位置纬度
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.origin_Lat*origin_Lat_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = origin_Lat_Label;
	sendData();

	// 发送惯性气压高
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.inertial_Barometric_Altitude*inertial_Barometric_Altitude_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = inertial_Barometric_Altitude_Label;
	sendData();

	// 发送航向角
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.chi*chi_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = chi_Label;
	sendData();

	// 发送俯仰角
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.theta*theta_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = theta_Label;
	sendData();

	// 发送滚转角
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.phi*phi_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = phi_Label;
	sendData();

	// 发送北向加速度
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.acc_North*acc_North_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = acc_North_Label;
	sendData();

	// 发送天向加速度
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.acc_Up*acc_Up_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = acc_Up_Label;
	sendData();

	// 发送东向加速度
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.acc_East*acc_East_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = acc_East_Label;
	sendData();

	// 发送北向速度
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.vel_North*vel_North_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = vel_North_Label;
	sendData();

	// 发送天向速度
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.vel_Up*vel_Up_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = vel_Up_Label;
	sendData();

	// 发送东向速度
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.vel_East*vel_East_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = vel_East_Label;
	sendData();

	// 发送仿真控制字
	memset(&tmp, 0, sizeof(tmp));
	tmp = myData.simControlWord;
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = simControlWord_Label;
	sendData();

	// 发送当前日期
	memset(&tmp, 0, sizeof(tmp));
	tmp = myData.currYear;
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = currYear_Label;
	sendData();

	// 发送当前时间_高字
	memset(&tmp, 0, sizeof(tmp));
	tmp = myData.currTime_h;
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = currTime_h_Label;
	sendData();

	// 发送当前时间_低字
	memset(&tmp, 0, sizeof(tmp));
	tmp = myData.currTime_l;
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = currTime_l_Label;
	sendData();

	// 发送仿真系统故障字
	memset(&tmp, 0, sizeof(tmp));
	tmp = myData.sysSettingFaultWord;
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = sysSettingFaultWord_Labe;
	sendData();
}