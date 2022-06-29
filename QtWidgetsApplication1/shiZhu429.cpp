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
	
	// ��ʼ��CAV_L1��
	printf("Initializing Driver and Memory Management . . . ");
	
	status = CAV_L1_A429_InitDefault(DEVID, 10);
	
	//CAV_L0_UINT32 CAV_L1_A429_InitDefault(CAV_L0_UINT32 devID,CAV_L0_UINT32 numIQEntries)
	//���ڳ�ʼ�� A429 �豸��Ϊ������ж϶��С�����devID���豸��ʶ�������嶨��� 2.1����numIQEntries����������ж϶�����ȡ�
	if (status != CAV_SUCCESS) {
		printf("ERROR %d on CAV_L1_A429_InitDefault\n", status);
		return;
	}
	printf("Success.\n\n");

	// ���IPCore�Լ�CAV_L1��汾��
	printf("Checking IPCore and API versions . . . ");
	status = CAV_L1_GetVersionInfo(DEVID, &IPCoreVersion, &l0Version, &l1Version);
	//��ȡ�̼���Layer 0 API �� Layer 1 API �İ汾��Ϣ��
	//CAV_L0_UINT32 CAV_L1_GetVersionInfo(CAV_L0_UINT32 devID,CAV_L0_UINT16 *peVersion,CAV_L0_UINT32 *layer0ApiVersion,CAV_L0_UINT32 *layer1ApiVersion)	//devID���豸��ʶ�������嶨��� 2.1����peVersion���̼���Ϣ��peVersion���̼���Ϣ��layer1ApiVersion��L1 �� API �汾��Ϣ��
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
	// ���ͨ������
	printf("Checking Channel Configuration . . . ");
	status = CAV_L1_A429_GetConfig(DEVID, &chanConfig);
	//��ȡ A429 �豸ͨ��������
	//CAV_L0_UINT32 CAV_L1_A429_GetConfig(CAV_L0_UINT32 devID,CAV_L0_UINT32 *pChanConfig)
	//devID���豸��ʶ�������嶨��� 2.1����pChanConfig�����ͨ�������Ĵ洢��Ԫ��ַ��
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
	//�ṹ�� CAV_L1_TX_BitDirection �����˷��͵� 32bit ���ݵķ���˳��
	//����ͨ������ highBitPriority �� LabelReversal �������ı䷢��˳��
	//
	tx_bitdirection.highBitPriority = 0;
	tx_bitdirection.LabelReversal = 0;
	printf("Initializing TX Channel %d . . . ", tx_channel);
	//����ͨ����ʼ��������������á�
	status = CAV_L1_A429_TX_Channel_Init(DEVID, tx_channel, 100000, 2, &tx_bitdirection);
	//CAV_L0_UINT32 CAV_L1_A429_TX_Channel_Init
	//(
	//	CAV_L0_UINT32 devID,		//devID���豸��ʶ�������嶨��� 2.1����
	//	CAV_L0_UINT32 TxChanNum,	//TxChanNum������ͨ���ţ�0 - 33����
	//	CAV_L0_UINT32 BitRateHz,	//BitRateHz�����͵Ĳ����� 500bp/s�C 300000bp/s��
	//	CAV_L0_UINT32 numTXCB,		//numTXCB���÷���ͨ������ķ��Ϳ��ƿ������
	//	CAV_L1_TX_BitDirection *BitDir	//BitDir��ָ���Ž�������λ���ָ�루���嶨��� 3.7.6����	//									//ע���ṹ����������������Ϊ 0 ʱ����֮ǰ�İ忨������ͬ��	//									��ϸ��Ϣ��ο����� 1 ARINC A429 �����ź�˳��˵��������Ϣλ��˵����
	//	)	//
	if (status != CAV_SUCCESS) {
		printf("ERROR %d on CAV_L1_A429_TX_Channel_Init\n", status);
		return;
	}
	else
	{
		printf("Success\n\n");
	}
	//���ͷ�������Ϣʱʹ��ͨ���ĺ�����
	//ע���ڷ�������Ϣ���͵�����£��˺����ڷ���ͨ����ʼ����ɺ�͵��á�
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

	// ��������Ϣʹ��
	CAV_L1_A429_TX_Channel_Disable(DEVID, tx_channel);

	printf("Closing TX Channel %d . . . ", tx_channel);
	//�ر�ͨ��
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
	// ���ͳ�ʼλ�þ���
	memset(&tmp, 0, sizeof(tmp));
	tmp=( myData.origin_Lon*origin_Lon_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = origin_Lon_Label;
	sendData();

	// ���ͳ�ʼλ��γ��
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.origin_Lat*origin_Lat_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = origin_Lat_Label;
	sendData();

	// ���͹�����ѹ��
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.inertial_Barometric_Altitude*inertial_Barometric_Altitude_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = inertial_Barometric_Altitude_Label;
	sendData();

	// ���ͺ����
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.chi*chi_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = chi_Label;
	sendData();

	// ���͸�����
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.theta*theta_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = theta_Label;
	sendData();

	// ���͹�ת��
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.phi*phi_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = phi_Label;
	sendData();

	// ���ͱ�����ٶ�
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.acc_North*acc_North_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = acc_North_Label;
	sendData();

	// ����������ٶ�
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.acc_Up*acc_Up_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = acc_Up_Label;
	sendData();

	// ���Ͷ�����ٶ�
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.acc_East*acc_East_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = acc_East_Label;
	sendData();

	// ���ͱ����ٶ�
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.vel_North*vel_North_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = vel_North_Label;
	sendData();

	// ���������ٶ�
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.vel_Up*vel_Up_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = vel_Up_Label;
	sendData();

	// ���Ͷ����ٶ�
	memset(&tmp, 0, sizeof(tmp));
	tmp = (myData.vel_East*vel_East_1_LSB);
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = vel_East_Label;
	sendData();

	// ���ͷ��������
	memset(&tmp, 0, sizeof(tmp));
	tmp = myData.simControlWord;
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = simControlWord_Label;
	sendData();

	// ���͵�ǰ����
	memset(&tmp, 0, sizeof(tmp));
	tmp = myData.currYear;
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = currYear_Label;
	sendData();

	// ���͵�ǰʱ��_����
	memset(&tmp, 0, sizeof(tmp));
	tmp = myData.currTime_h;
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = currTime_h_Label;
	sendData();

	// ���͵�ǰʱ��_����
	memset(&tmp, 0, sizeof(tmp));
	tmp = myData.currTime_l;
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = currTime_l_Label;
	sendData();

	// ���ͷ���ϵͳ������
	memset(&tmp, 0, sizeof(tmp));
	tmp = myData.sysSettingFaultWord;
	memcpy(&ARINC429_data, &tmp, 4);
	ARINC429_label = sysSettingFaultWord_Labe;
	sendData();
}