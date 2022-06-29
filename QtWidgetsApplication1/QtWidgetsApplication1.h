#pragma once



#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"

#include <QTimer>
#include <QtCharts>

#include <QChartView>

#include <QSplineSeries>
#include "dialog_initsetting.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "serialPort.h"
#include <QObject>
#include <QUdpSocket>
#include "wgs_conversions.h"
#include "shiZhu429.h"


#define ch_rx               0x00 // 接收通道
#define ch_tx               0x00 // 发送通道
#define tx_DataLength       0x10 // 取值1~256



//#include <>

class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = Q_NULLPTR);
	

	QTimer* flushMappingTimer;
	QTimer* consoleOutTimer;
	QTimer* serialPortOutTimer;
	QTimer* cav429OutTimer;

	QTimer* udpSendTimer;
	QUdpSocket *leverUdpSocket;
	QUdpSocket *zhuoJianErrorUdpSocket;

	QUdpSocket *sendUdpDataSocket;

	QChart* mChart_Z;
	QLineSeries* lineSeries_Z_true;
	QLineSeries* lineSeries_Z_expect;
	QChartView* chartView_Z;
	QLineSeries* lineSeries_landingPlaning;


	QChart* mChart_XY;
	QLineSeries* lineSeries_XY_true;
	QLineSeries* lineSeries_XY_expect;
	QChartView* chartView_XY;


	QLineSeries* lineSeries_beta_true;
	QLineSeries* lineSeries_alpha_true;
	QLineSeries* lineSeries_theta_true;
	QLineSeries* lineSeries_phi_true;
	QLineSeries* lineSeries_psi_true;
	
	QChart* mChart_theta;
	QChartView* chartView_theta;


	QChart* mChart_V;
	QChartView* chartView_V;
	QLineSeries* lineSeries_Vx;
	QLineSeries* lineSeries_Vy;
	QLineSeries* lineSeries_Vz;




	serialport* port;
	WgsConversions* wgs_enuConversion_APP;



	struct UDPDateStruct
	{
		unsigned short UsPackHead;
		unsigned char UcAin[8];
		unsigned short UsPackTail;

	};


	cav429* myCAV429;



private:
    Ui::QtWidgetsApplication1Class ui;
	Dialog_initsetting* Dialog_initsetting_ui;

	void UiInitialization();


	//void treeView_Init();
public slots:

	void stateInitSlot();

	void flushMappingFunction();
	void Start_Suspend_slot();
	void consoleOut_slot();
	void serialSend_slot();

	void udpReceive();

	void udpReceiveZhuoJianError();

	void udpSendDAta();

	void ModelChanged(int);
	void On_doubleSpinBox_Command_VKH_V_ValueChanged(double arg);
	void On_doubleSpinBox_Command_VKH_K_ValueChanged(double arg);
	void On_doubleSpinBox_Command_VKH_H_ValueChanged(double arg);
	void On_doubleSpinBox_Command_XYZV_X_ValueChanged(double arg);
	void On_doubleSpinBox_Command_XYZV_Y_ValueChanged(double arg);
	void On_doubleSpinBox_Command_XYZV_Z_ValueChanged(double arg);
	void On_doubleSpinBox_Command_XYZV_V_ValueChanged(double arg);
	void On_doubleSpinBox_Command_XYZV_Error_ValueChanged(double arg);


	void On_doubleSpinBox_Command_dV_ValueChanged(double arg);
	void On_doubleSpinBox_Command_dK_ValueChanged(double arg);
	void On_doubleSpinBox_Command_dH_ValueChanged(double arg);
	void doubleSpinBox_Command_xiaHua_V(double arg);
	void doubleSpinBox_Command_xiaHua_angle(double arg);
	void doubleSpinBox_Command_xiaHua_H(double arg);

	void On_initsetting_triggerd();


	void On_checkBox_selectAlpha_stateChanged(int arg);
	void On_checkBox_selectBeta_stateChanged(int arg);
	void On_checkBox_selectTheta_stateChanged(int arg);
	void On_checkBox_selectPhi_stateChanged(int arg);
	void On_checkBox_selectPsi_stateChanged(int arg);
	void On_checkBox_checkBox_true_H_stateChanged(int arg);
	void On_checkBox_checkBox_expect_H_stateChanged(int arg);
	void On_checkBox_checkBox_Vx_stateChanged(int arg);
	void On_checkBox_checkBox_Vy_stateChanged(int arg);
	void On_checkBox_checkBox_Vz_stateChanged(int arg);


	void ReceiveTaskManger_ModeChanged(unsigned int mode);
	void ReceiveTaskManger_targetArrived(int arg);
	void InitTargetsList();


	void drawExpect_Z_slot();

	void On_trigered_QAction(QAction*);

	void On_checkBox_isSerialPortSend_StateChange(int arg);
	void On_checkBox_is429Send_StateChange(int arg);

	void On_doubleSpinBox_Command_zhuoJianYV_Limit_valueChanged(double arg);

	void On_doubleSpinBox_Command_zhuoJianZV_Limit_valueChanged(double arg);

	void On_doubleSpinBox_Command_zhuoJianXV_valueChanged(double arg);

	void drawLandingPlaning();

	void use429SendSimData();

signals:
	void test();

};
