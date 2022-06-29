#include "QtWidgetsApplication1.h"
#include "ui_QtWidgetsApplication1.h"
#include <windows.h>
#include "global.h"
#include "UIBridgeHeader.h"
#include <algorithm>

#define ch_rx               0x00 // 接收通道
#define ch_tx               0x00 // 发送通道
#define tx_DataLength       0x10 // 取值1~256

#pragma execution_character_set("utf-8") //解决中文乱码

#define CANCLE_YDDS	//取消nYDDS输出
#define CANCLE_LBHACCMAP	//取消经纬高以及加速度的绘图

QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
	: QMainWindow(parent)
{

	ui.setupUi(this);

	
	Dialog_initsetting_ui = new Dialog_initsetting(this);
	Dialog_initsetting_ui->show();
	// 初始化信号与槽连结
	connect(Dialog_initsetting_ui, SIGNAL(stateInit()), this, SLOT(stateInitSlot()));

	flushMappingTimer = new QTimer();
	connect(flushMappingTimer, SIGNAL(timeout()), this, SLOT(flushMappingFunction()));
	//启动时默认仿真状态为暂停

	consoleOutTimer = new QTimer();
	connect(consoleOutTimer, SIGNAL(timeout()), this, SLOT(consoleOut_slot()));

	cav429OutTimer = new QTimer();
	connect(cav429OutTimer, SIGNAL(timeout()), this, SLOT(use429SendSimData()));


	connect(taskManager, SIGNAL(ModeChanged(unsigned int)), this, SLOT(ReceiveTaskManger_ModeChanged(unsigned int)));
	connect(taskManager, SIGNAL(targetArrived(int)), this, SLOT(ReceiveTaskManger_targetArrived(int)));

	connect(ui.action_initsetting, SIGNAL(triggered()), this, SLOT(On_initsetting_triggerd()));


	connect(taskManager, SIGNAL(drawExpect_Z()), this, SLOT(drawExpect_Z_slot()));


	serialPortOutTimer = new QTimer();
	connect(serialPortOutTimer, SIGNAL(timeout()), this, SLOT(serialSend_slot()));



	//操纵杆UDP
	leverUdpSocket = new QUdpSocket;
	leverUdpSocket->bind(QHostAddress("0.0.0.0"), leverUdpPort);
	connect(leverUdpSocket, SIGNAL(readyRead()), this, SLOT(udpReceive()));


	//着舰偏差UDP
	zhuoJianErrorUdpSocket = new QUdpSocket;
	zhuoJianErrorUdpSocket->bind(QHostAddress("0.0.0.0"), zhuoJianErrorUdpPort);
	connect(zhuoJianErrorUdpSocket, SIGNAL(readyRead()), this, SLOT(udpReceiveZhuoJianError()));

	// 发送飞行仿真数据
	sendUdpDataSocket = new QUdpSocket;
	udpSendTimer = new QTimer();
	connect(udpSendTimer, SIGNAL(timeout()), this, SLOT(udpSendDAta()));

	connect(taskManager, SIGNAL(drawLandingPlaning()), this, SLOT(drawLandingPlaning()));






	////////////////Z的实际与期望曲线绘图
	lineSeries_Z_true = new QLineSeries();  //创建折线系列
	lineSeries_Z_expect = new QLineSeries();  //创建折线系列
	chartView_Z = new QChartView(this);		//创建图表显示
	mChart_Z = new QChart();					//创建图标
	lineSeries_Z_true->setName("实际Z");         //设置折线系列名称
	lineSeries_Z_expect->setName("期望Z");         //设置折线系列名称

	mChart_Z->addSeries(lineSeries_Z_true);          //向图表中添加系列
	mChart_Z->addSeries(lineSeries_Z_expect);          //向图表中添加系列

	// 刨面折线
	lineSeries_landingPlaning = new QLineSeries;
	lineSeries_landingPlaning->setName("着舰刨面");
	mChart_Z->addSeries(lineSeries_landingPlaning);
	//lineSeries_landingPlaning->setPen(QPen(QBrush(Qt::red), 2, Qt::DotLine));

	mChart_Z->createDefaultAxes();            //创建默认的坐标，必须在addSeries之后调用
	mChart_Z->axisX()->setMin(0);
	mChart_Z->axisY()->setMax(300);
	mChart_Z->axisX()->setTitleText("着舰点距离");
	mChart_Z->axisY()->setTitleText("(米）");
	mChart_Z->setTheme(QChart::ChartThemeDark);//设置图标主题
	mChart_Z->setTitle("");               //设置图标名称
	lineSeries_Z_expect->setPen(QPen(QBrush(Qt::red), 2, Qt::DotLine));
	//mChart->legend()->hide();                 //隐藏图例，也就是不显示系列名称了
	chartView_Z->setChart(mChart_Z);                //向chartView中添加图标
	chartView_Z->resize(QSize(500, 300));          //重新设置chartView的大小
	chartView_Z->setRenderHints(QPainter::Antialiasing);  //消除边缘，看起来平滑一些
	chartView_Z->setChart(mChart_Z);                //向chartView中添加图标
	ui.horizontalLayout_Line_Z->addWidget(chartView_Z);//把chartView放到水平布局中（在ui中拖一个水平布局）



	
	//lineSeries_landingPlaning->setPen(QPen(QBrush(Qt::blue), 2, Qt::DotLine));

													   //////////////////XY的实际与期望曲线绘图
	lineSeries_XY_true = new QLineSeries();  //创建折线系列
	lineSeries_XY_expect = new QLineSeries();  //创建折线系列
	chartView_XY = new QChartView(this);		//创建图表显示
	mChart_XY = new QChart();					//创建图标
	lineSeries_XY_true->setName("实际XY");         //设置折线系列名称
	lineSeries_XY_expect->setName("期望XY");         //设置折线系列名称
	mChart_XY->addSeries(lineSeries_XY_true);          //向图表中添加系列
	mChart_XY->addSeries(lineSeries_XY_expect);          //向图表中添加系列
	mChart_XY->createDefaultAxes();            //创建默认的坐标，必须在addSeries之后调用
	mChart_XY->axisX()->setMin(0);
	mChart_XY->axisY()->setMax(300);
	mChart_XY->axisX()->setTitleText("X(米)");
	mChart_XY->axisY()->setTitleText("Y(米)");
	mChart_XY->setTheme(QChart::ChartThemeDark);//设置图标主题
	mChart_XY->setTitle("");               //设置图标名称
										   //mChart->legend()->hide();                 //隐藏图例，也就是不显示系列名称了
	chartView_XY->setChart(mChart_XY);                //向chartView中添加图标
	chartView_XY->resize(QSize(500, 300));          //重新设置chartView的大小
	chartView_XY->setRenderHints(QPainter::Antialiasing);  //消除边缘，看起来平滑一些
	chartView_XY->setChart(mChart_XY);                //向chartView中添加图标
	ui.horizontalLayout_Line_XY->addWidget(chartView_XY);//把chartView放到水平布局中（在ui中拖一个水平布局）






	lineSeries_alpha_true = new QLineSeries();//创建折线系列
	chartView_theta = new QChartView(this);//创建图表显示
	mChart_theta = new QChart();//创建图表

	lineSeries_alpha_true->setName("Alpha");
	mChart_theta->addSeries(lineSeries_alpha_true);
	lineSeries_alpha_true->setVisible(false);

	lineSeries_beta_true = new QLineSeries();//创建折线系列
	lineSeries_beta_true->setName("Beta");
	mChart_theta->addSeries(lineSeries_beta_true);
	lineSeries_beta_true->setVisible(false);


	lineSeries_theta_true = new QLineSeries();//创建折线系列
	lineSeries_theta_true->setName("Theta");
	mChart_theta->addSeries(lineSeries_theta_true);
	lineSeries_theta_true->setVisible(false);

	lineSeries_phi_true = new QLineSeries();//创建折线系列
	lineSeries_phi_true->setName("Phi");
	mChart_theta->addSeries(lineSeries_phi_true);
	lineSeries_phi_true->setVisible(false);


	lineSeries_psi_true = new QLineSeries();//创建折线系列
	lineSeries_psi_true->setName("Psi");
	mChart_theta->addSeries(lineSeries_psi_true);
	//lineSeries_psi_true->hide();
	lineSeries_psi_true->setVisible(false);




	mChart_theta->createDefaultAxes();
	mChart_theta->axisX()->setMin(0);
	mChart_theta->axisX()->setTitleText("时间(秒)");
	mChart_theta->axisY()->setTitleText("度");
	mChart_theta->axisY()->setMin(-30);
	mChart_theta->axisY()->setMax(30);
	mChart_theta->setTheme(QChart::ChartThemeDark);//设置图标主题
	mChart_theta->setTitle("");               //设置图标名称

	chartView_theta->setChart(mChart_theta);                //向chartView中添加图标
	chartView_theta->resize(QSize(500, 300));          //重新设置chartView的大小
	chartView_theta->setRenderHints(QPainter::Antialiasing);  //消除边缘，看起来平滑一些
	chartView_theta->setChart(mChart_theta);                //向chartView中添加图标


	ui.horizontalLayout_Line_theta->addWidget(chartView_theta);//把chartView放到水平布局中（在ui中拖一个水平布局）
															   //ui.horizontalLayout_Line_theta->addWidget(chartView_theta);//把chartView放到水平布局中（在ui中拖一个水平布局）

															   ///////////////////////////
	lineSeries_Vx = new QLineSeries();  //创建折线系列
	lineSeries_Vy = new QLineSeries();  //创建折线系列
	lineSeries_Vz = new QLineSeries();  //创建折线系列
	chartView_V = new QChartView(this);		//创建图表显示
	mChart_V = new QChart();					//创建图标
	lineSeries_Vx->setName("Vx");         //设置折线系列名称
	lineSeries_Vy->setName("Vy");         //设置折线系列名称
	lineSeries_Vz->setName("Vz");         //设置折线系列名称
	mChart_V->addSeries(lineSeries_Vx);          //向图表中添加系列
	mChart_V->addSeries(lineSeries_Vy);          //向图表中添加系列
	mChart_V->addSeries(lineSeries_Vz);          //向图表中添加系列
	mChart_V->createDefaultAxes();            //创建默认的坐标，必须在addSeries之后调用
	mChart_V->axisX()->setTitleText("时间(秒)");
	mChart_V->axisY()->setTitleText("m/s");
	mChart_V->setTheme(QChart::ChartThemeDark);//设置图标主题
	mChart_V->setTitle("");               //设置图标名称
										  //lineSeries_Vx->setPen(QPen(QBrush(Qt::red), 2, Qt::DotLine));
										  //mChart->legend()->hide();                 //隐藏图例，也就是不显示系列名称了
	chartView_V->setChart(mChart_V);                //向chartView中添加图标
	chartView_V->resize(QSize(500, 300));          //重新设置chartView的大小
	chartView_V->setRenderHints(QPainter::Antialiasing);  //消除边缘，看起来平滑一些
	chartView_V->setChart(mChart_V);                //向chartView中添加图标
	ui.horizontalLayout_Line_V->addWidget(chartView_V);//把chartView放到水平布局中（在ui中拖一个水平布局）

	lineSeries_Vx->setVisible(false);
	lineSeries_Vy->setVisible(false);
	lineSeries_Vz->setVisible(false);
	//////////////////////















	ui.checkBox_selcetAlpha->setChecked(true);
	ui.checkBox_selcetBeta->setChecked(true);
	ui.checkBox_true_H->setChecked(true);
	ui.checkBox_expect_H->setChecked(true);
	ui.checkBox_Vx->setChecked(true);
	ui.checkBox_Vy->setChecked(true);
	ui.checkBox_Vz->setChecked(true);


#ifdef CANCLE_LBHACCMAP


#endif // CANCLE_LBHACCMAP


	port = new serialport();

	UiInitialization();				//初始化UI

									//qDebug() << "ZHHK429test()";
									//ZHHK429test();
									// 隐藏非默认模式所使用的输入控件
	ui.label_target->hide();
	ui.label_XYZV_X->hide();
	ui.label_XYZV_Y->hide();
	ui.label_XYZV_Z->hide();
	ui.label_XYZV_V->hide();
	ui.label_XYZV_Error->hide();
	ui.doubleSpinBox_Command_XYZV_X->hide();
	ui.doubleSpinBox_Command_XYZV_Y->hide();
	ui.doubleSpinBox_Command_XYZV_Z->hide();
	ui.doubleSpinBox_Command_XYZV_V->hide();
	ui.doubleSpinBox_Command_XYZV_Error->hide();

	ui.label_xiaHua->hide();
	ui.label_xiaHua_2->hide();
	ui.label_xiaHua_3->hide();
	ui.doubleSpinBox_Command_xiaHua_V->hide();
	ui.doubleSpinBox_Command_xiaHua_angle->hide();
	ui.doubleSpinBox_Command_xiaHua_H->hide();

	ui.label_zhuoJian_XV->hide();
	ui.label_zhuoJian_YV_Limit->hide();
	ui.label_zhuoJian_ZV_Limit->hide();
	ui.doubleSpinBox_Command_zhuoJianXV->hide();
	ui.doubleSpinBox_Command_zhuoJianYV_Limit->hide();
	ui.doubleSpinBox_Command_zhuoJianZV_Limit->hide();
	//ui.textBrowser_note->hide();

	ui.doubleSpinBox_Command_zhuoJianXV->setValue(zhuoJianXV);
	ui.doubleSpinBox_Command_zhuoJianYV_Limit->setValue(VY_MAXLimt);
	ui.doubleSpinBox_Command_zhuoJianZV_Limit->setValue(VZ_MAXLimt);


	wgs_enuConversion_APP = new WgsConversions;

	myCAV429 = new cav429;
}

void QtWidgetsApplication1::stateInitSlot()			//初始化仿真状态
{

	// 初始化串口
	if (!port->getportstate())
	{
		try
		{
			QString portName = QString::fromStdString(serialPortName);


			port->portInit(portName, serialBaudRate);
			//串口读取频率，单位ms
		}
		catch (...) {
			/////////////////////////////串口打开失败
		}
		////---------------------要在此初始化串口

	}


	// 设置完初始状态后更新UI
	taskManager->clm_control_task->initState();

	// 设置初始的默认仿真模式
	taskManager->currentModeSet(Mode_default);
	UiInitialization();
}
void WINAPI catchTimer_netSend(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2)
{


}

void QtWidgetsApplication1::UiInitialization()
{
	ui.doubleSpinBox_Command_VKH_V->setValue(taskManager->Command_VKH[0]);
	ui.doubleSpinBox_Command_VKH_K->setValue(taskManager->Command_VKH[1] * 180 / 3.1415926535);
	ui.doubleSpinBox_Command_VKH_H->setValue(taskManager->Command_VKH[2]);
	ui.doubleSpinBox_Command_XYZV_X->setValue(taskManager->Command_XYZV[0]);
	ui.doubleSpinBox_Command_XYZV_Y->setValue(taskManager->Command_XYZV[1]);
	ui.doubleSpinBox_Command_XYZV_Z->setValue(taskManager->Command_XYZV[2]);
	ui.doubleSpinBox_Command_XYZV_V->setValue(taskManager->Command_XYZV[3]);




}


void QtWidgetsApplication1::flushMappingFunction()
{
	//Z坐标动态添加数据
	//lineSeries_X_true->append(QPointF(i, qrand() % 300) );
	//double Distance = sqrt(pow(clm_control->m_fst.m_dX - data_origin_X, 2) + pow(clm_control->m_fst.m_dY - data_origin_Y, 2));
	static int cnt = 0;
	if (cnt >= 5)
	{
		double shipEnu[3];
		wgs_enuConversion_APP->lla2enu(shipEnu, shipPointBLH, lla_ref);
		double Distance = sqrt(pow(clm_control->m_fst.m_dX - shipEnu[0], 2) + pow(clm_control->m_fst.m_dY - shipEnu[1], 2));
		lineSeries_Z_true->append(QPointF(Distance, clm_control->m_fst.m_dZ));	//向折线系列添加数据
		ui.lcdNumber_Distance->display(QString("%1").arg(Distance, 6, 'f', 1));
		cnt = 0;
	}
	cnt++;

																			//lineSeries_Z_expect->append(QPointF(SimulationTime, Z_c));						//向折线系列添加数据
	if (lineSeries_Z_true->points().size() > 400)									//只保存400个数据
	{
		lineSeries_Z_true->remove(0);
		//lineSeries_Z_expect->remove(0);
	}
	//mChart_Z->axisX()->setMin(Distance - 100);										//设置纵坐标轴跟随数据变化
	//mChart_Z->axisX()->setMax(Distance + 100);
	//mChart_Z->axisX()->setRange(-1000, 100);
	//mChart_Z->axisY()->setMin(clm_control->m_fst.m_dZ - 100);
	//mChart_Z->axisY()->setMax(clm_control->m_fst.m_dZ + 100);


	////XY坐标动态添加数据
	////lineSeries_X_true->append(QPointF(i, qrand() % 300) );
	lineSeries_XY_true->append(QPointF(clm_control->m_fst.m_dX, clm_control->m_fst.m_dY));	//向折线系列添加数据
#ifndef CANCLE_LBHACCMAP
	lineSeries_XY_expect->append(QPointF(X_c, Y_c));						//向折线系列添加数据
#endif
	if (lineSeries_XY_true->points().size() > 400)									//只保存400个数据
	{
		lineSeries_XY_true->remove(0);
#ifndef CANCLE_LBHACCMAP
		lineSeries_XY_expect->remove(0);
#endif
	}

	mChart_XY->axisX()->setMin(clm_control->m_fst.m_dX - 200);										//设置纵坐标轴跟随数据变化
	mChart_XY->axisX()->setMax(clm_control->m_fst.m_dX + 200);
	mChart_XY->axisY()->setMin(clm_control->m_fst.m_dY - 200);
	mChart_XY->axisY()->setMax(clm_control->m_fst.m_dY + 200);




	//姿态角绘图动态添加数据
	lineSeries_alpha_true->append(QPointF(SimulationTime, clm_control->m_fst.m_dAlpha * 180 / PI));
	//qDebug() <<"#"<< clm_control->m_fst.m_dVtheta;
	if (lineSeries_alpha_true->points().size() > 400)									//只保存400个数据
	{
		lineSeries_alpha_true->remove(0);
		//lineSeries_XY_expect->remove(0);
	}

	lineSeries_beta_true->append(QPointF(SimulationTime, clm_control->m_fst.m_dBeta * 180 / PI));
	//qDebug() <<"#"<< clm_control->m_fst.m_dVtheta;
	if (lineSeries_beta_true->points().size() > 400)									//只保存400个数据
	{
		lineSeries_beta_true->remove(0);
		//lineSeries_XY_expect->remove(0);
	}



	lineSeries_theta_true->append(QPointF(SimulationTime, (clm_control->m_fst.m_dGama + clm_control->m_fst.m_dAlpha) * 180 / PI));
	//qDebug() <<"#"<< clm_control->m_fst.m_dVtheta;
	if (lineSeries_theta_true->points().size() > 400)									//只保存400个数据
	{
		lineSeries_theta_true->remove(0);
		//lineSeries_XY_expect->remove(0);
	}

	lineSeries_phi_true->append(QPointF(SimulationTime, (clm_control->m_fst.m_dMu) * 180 / PI));
	//qDebug() <<"#"<< clm_control->m_fst.m_dVtheta;
	if (lineSeries_phi_true->points().size() > 400)									//只保存400个数据
	{
		lineSeries_phi_true->remove(0);
		//lineSeries_XY_expect->remove(0);
	}

	lineSeries_psi_true->append(QPointF(SimulationTime, (clm_control->m_fst.m_dChi - clm_control->m_fst.m_dBeta) * 180 / PI));
	//qDebug() <<"#"<< clm_control->m_fst.m_dVtheta;
	if (lineSeries_psi_true->points().size() > 400)									//只保存4000个数据
	{
		lineSeries_psi_true->remove(0);
		//lineSeries_XY_expect->remove(0);
	}

	mChart_theta->axisX()->setMin(SimulationTime - 20);										//设置纵坐标轴跟随数据变化
	mChart_theta->axisX()->setMax(SimulationTime);

	double Vx = taskManager->clm_control_task->m_fst.m_Vx;
	double Vy = taskManager->clm_control_task->m_fst.m_Vy;
	double Vz = taskManager->clm_control_task->m_fst.m_Vz;

	lineSeries_Vx->append(QPointF(SimulationTime, Vx));
	lineSeries_Vy->append(QPointF(SimulationTime, Vy));
	lineSeries_Vz->append(QPointF(SimulationTime, Vz));
	//qDebug() <<"#"<< clm_control->m_fst.m_dVtheta;
	if (lineSeries_Vx->points().size() > 400)									//只保存4000个数据
	{
		lineSeries_Vx->remove(0);
		lineSeries_Vy->remove(0);
		lineSeries_Vz->remove(0);
		//lineSeries_XY_expect->remove(0);
	}


	mChart_V->axisY()->setMin(min(min(Vx, Vy), Vz) - 5);										//设置纵坐标轴跟随数据变化
	mChart_V->axisY()->setMax(max(max(Vx, Vy), Vz) + 5);
	mChart_V->axisX()->setMin(SimulationTime - 5);										//设置纵坐标轴跟随数据变化
	mChart_V->axisX()->setMax(SimulationTime);
	//mChart_V->createDefaultAxes();

	ui.lcdNumber_LBH_L->display(QString("%1").arg(L, 3, 'f', 5));
	ui.lcdNumber_LBH_B->display(QString("%1").arg(B, 3, 'f', 5));
	ui.lcdNumber_LBH_H->display(QString("%1").arg(H, 6, 'f', 1));
	//ui.lcdNumber_LBH_H->display(H);

}


//仿真启动和暂停
void QtWidgetsApplication1::Start_Suspend_slot()
{
	//qDebug() << "test" << timer_id_simulation << ";";// << timer_id_consoleOut;


	if (timer_id_simulation)
	{
		//要取消的计时器事件的标识符。设置计时器事件时，timeSetEvent函数返回此标识符。
		//如果指定的计时器事件不存在，则返回TimeRyNoRebug，如果成功或MySySerRyValpPARM则成功。
		//删除定时器事件   
		timeKillEvent(timer_id_simulation);
		//清除定时器分辨率   
		timeEndPeriod(1);
		timer_id_simulation = 0;
	}
	else
	{
		//设置定时器分辨率，1ms   
		//timeBeginPeriod(1);   
		//产生间隔data_time+data_timedelay毫秒，周期执行的定时器事件；启动定时器   
		//设置定时器
		timer_id_simulation = timeSetEvent(data_time + data_timedelay, 1, (LPTIMECALLBACK)catchTimer_simulation, DWORD(1), TIME_PERIODIC);
		//timer_id_simulation = timeSetEvent(data_time + data_timedelay, 1, (LPTIMECALLBACK)catchTimer_netSend, DWORD(1), TIME_PERIODIC);
		//timer_id2 = timeSetEvent(500, 1, (LPTIMECALLBACK)catchTimer2, DWORD(1), TIME_PERIODIC);
	}


	if (flushMappingTimer->isActive())
	{
		flushMappingTimer->stop();
	}
	else
	{
		flushMappingTimer->start(50);
	}

	if (consoleOutTimer->isActive())
	{
		consoleOutTimer->stop();
	}
	else
	{
		consoleOutTimer->start(500);
	}


}


void QtWidgetsApplication1::consoleOut_slot()
{
	ui.lcdNumber_SimulationTime->display(int(SimulationTime));

	QString str;
	switch (taskManager->currentMode)
	{
	case Mode_default:
		str = "Mode_default";
		break;
	case Mode_PositionFollow:
		str = "Mode_PositionFollow";
		break;
	case Mode_PositionFollow_V:
		str = "Mode_PositionFollow_V";
		break;
	case Mode_ManualOperation:
		str = "Mode_ManualOperation";
		break;
	case Mode_Waypoint:
		str = "Mode_Waypoint";
		break;
	case Mode_Waypoint_2:
		str = "Mode_Waypoint_2";
		break;
	case Mode_ZhuoJianFangZhen:
		str = "着舰仿真";
		break;

	default:
		break;
	}
	ui.textBrowser_ModeDisplay->setText(str);
}


void QtWidgetsApplication1::serialSend_slot()
{
	static serialport::serialportDataStruct sendData;


	sendData.week = SimulationTime / 604800;
	sendData.second = (int(SimulationTime * 1000000) % (604800 * 1000000));

	sendData.L = L * 100000000;
	sendData.B = B * 100000000;

	sendData.H = H * 1000;
	sendData.Veast = clm_control->m_fst.m_dX * 1000;
	sendData.Vnorth = clm_control->m_fst.m_dY * 1000;
	sendData.Vland = -clm_control->m_fst.m_dZ * 1000;
	double rho_dt = -5.256 / 44300 * 101.325*pow(1 - H / 44300, 4.256);
	sendData.theta = (clm_control->m_fst.m_dGama + clm_control->m_fst.m_dAlpha) * 1000;//theta
	sendData.psi = (clm_control->m_fst.m_dChi - clm_control->m_fst.m_dBeta) * 1000;
	sendData.phi = clm_control->m_fst.m_dMu * 1000;  //phi
	sendData.accX = clm_control->m_fst.m_Accx * 1000;
	sendData.accY = clm_control->m_fst.m_Accy * 1000;
	sendData.accZ = clm_control->m_fst.m_Accz * 1000;

	sendData.angleAccX = clm_control->m_fst.m_Accp * 1000;
	sendData.angleAccY = clm_control->m_fst.m_Accq * 1000;
	sendData.angleAccZ = clm_control->m_fst.m_Accr * 1000;

	port->sendSerialportData(sendData);



	static QFile myfile("227_1.txt");
	static bool flag = true;
	if (flag)
	{
		myfile.open(QFile::WriteOnly | QFile::Truncate);
		QTextStream out(&myfile);

		out << "second" << " " << "X" << " " << "Y" << " " << "Z"
			<< " " << "Vx" << " " << "Vy" << " " << "Vz"
			<< " " << "phi" << " " << "theta" << " " << "psi"
			<< " " << "alpha" << "\r\n";
		myfile.close();
		flag = false;
	}
	if (myfile.open(QFile::WriteOnly | QIODevice::Append))
	{
		QTextStream out(&myfile);
		out << SimulationTime << " " << clm_control->m_fst.m_dX << " " << clm_control->m_fst.m_dY << " " << clm_control->m_fst.m_dZ << " "
			<< clm_control->m_fst.m_Vx << " " << clm_control->m_fst.m_Vy << " " << clm_control->m_fst.m_Vz << " "
			<< clm_control->m_fst.m_dMu << " " << clm_control->m_fst.m_dGama + clm_control->m_fst.m_dAlpha << " " << clm_control->m_fst.m_dChi - clm_control->m_fst.m_dBeta
			<< " " << clm_control->m_fst.m_dAlpha << "\r\n";
		myfile.close();
	}


}



void QtWidgetsApplication1::ModelChanged(int arg)
{
	qDebug() << arg;
	taskManager->currentModeSet(arg);
	if (arg == 4)
	{
		InitTargetsList();
	}
	if (arg == 1)
	{
		ui.doubleSpinBox_Command_xiaHua_V->setValue(taskManager->clm_control_task->m_fst.m_dV);
	}


}

void QtWidgetsApplication1::ReceiveTaskManger_targetArrived(int arg)
{
	qDebug() << arg << "---";
	QStandardItemModel* ItemModel = new QStandardItemModel(this);
	int i = 0;
	vector<std::string>::iterator it;
	for (it = targetNode_Name.begin(); it != targetNode_Name.end(); it++)
	{
		QStandardItem *item;
		if (i <= arg)
		{
			item = new QStandardItem(QString::fromStdString(*it) + "___Arived");
		}
		else
		{
			item = new QStandardItem(QString::fromStdString(*it));
		}
		i++;

		ItemModel->appendRow(item);
	}
	ui.listView_targets->setModel(ItemModel);
}


void QtWidgetsApplication1::On_doubleSpinBox_Command_VKH_V_ValueChanged(double arg)
{
	taskManager->Command_VKH[0] = arg;

}
void QtWidgetsApplication1::On_doubleSpinBox_Command_VKH_K_ValueChanged(double arg)
{
	double tmp = arg;
	qDebug() << tmp << "debug";
	if (arg > 180)
	{
		//qDebug() << "1";
		arg -= 360;
		ui.doubleSpinBox_Command_VKH_K->setValue(arg);
	}
	else if (arg < -180)
	{
		//qDebug() << "2";
		arg += 360;
		ui.doubleSpinBox_Command_VKH_K->setValue(arg);
	}
	taskManager->Command_VKH[1] = arg *3.1415926535 / 180;

}
void QtWidgetsApplication1::On_doubleSpinBox_Command_VKH_H_ValueChanged(double arg)
{
	taskManager->Command_VKH[2] = arg;

}
void QtWidgetsApplication1::On_doubleSpinBox_Command_XYZV_X_ValueChanged(double arg)
{
	taskManager->Command_XYZV[0] = arg;

}
void QtWidgetsApplication1::On_doubleSpinBox_Command_XYZV_Y_ValueChanged(double arg)
{
	taskManager->Command_XYZV[1] = arg;
}
void QtWidgetsApplication1::On_doubleSpinBox_Command_XYZV_Z_ValueChanged(double arg)
{
	taskManager->Command_XYZV[2] = arg;
}
void QtWidgetsApplication1::On_doubleSpinBox_Command_XYZV_V_ValueChanged(double arg)
{
	taskManager->Command_XYZV[3] = arg;
}

void QtWidgetsApplication1::On_doubleSpinBox_Command_XYZV_Error_ValueChanged(double arg)
{
	arriveDistanceFlag = arg;
}


void QtWidgetsApplication1::On_doubleSpinBox_Command_dV_ValueChanged(double arg)
{
	taskManager->Command_Manual[0] = arg;
}
void QtWidgetsApplication1::On_doubleSpinBox_Command_dK_ValueChanged(double arg)
{
	taskManager->Command_Manual[1] = arg / 180 * PI;
}
void QtWidgetsApplication1::On_doubleSpinBox_Command_dH_ValueChanged(double arg)
{
	taskManager->Command_Manual[2] = arg / 100;
}

void QtWidgetsApplication1::doubleSpinBox_Command_xiaHua_V(double arg)
{
	//qDebug() << "VChange";
	taskManager->Command_xiaHua[0] = arg;
	//taskManager->Command_Manual[2] = arg /100;
}
void QtWidgetsApplication1::doubleSpinBox_Command_xiaHua_angle(double arg)
{
	taskManager->Command_xiaHua[1] = arg / 180 * PI;
	//qDebug() << "angleChange";
	//taskManager->Command_Manual[2] = arg / 100;
}
void QtWidgetsApplication1::doubleSpinBox_Command_xiaHua_H(double arg)
{
	//qDebug() << "HChange";
	taskManager->Command_xiaHua[2] = arg;
	//taskManager->Command_Manual[2] = arg / 100;
}



void QtWidgetsApplication1::ReceiveTaskManger_ModeChanged(unsigned int mode)
{

	ui.comboBox_ModeSelect->setCurrentIndex(mode);
	if (mode == 0)
	{
		ui.label_VKH_V->setVisible(true);
		ui.label_VKH_K->setVisible(true);
		ui.label_VKH_H->setVisible(true);
		ui.doubleSpinBox_Command_VKH_V->setVisible(true);
		ui.doubleSpinBox_Command_VKH_K->setVisible(true);
		ui.doubleSpinBox_Command_VKH_H->setVisible(true);


		ui.label_target->hide();
		ui.label_XYZV_X->hide();
		ui.label_XYZV_Y->hide();
		ui.label_XYZV_Z->hide();
		ui.label_XYZV_V->hide();
		ui.label_XYZV_Error->hide();
		ui.doubleSpinBox_Command_XYZV_X->hide();
		ui.doubleSpinBox_Command_XYZV_Y->hide();
		ui.doubleSpinBox_Command_XYZV_Z->hide();
		ui.doubleSpinBox_Command_XYZV_V->hide();
		ui.doubleSpinBox_Command_XYZV_Error->hide();



		ui.label_xiaHua->hide();
		ui.label_xiaHua_2->hide();
		ui.label_xiaHua_3->hide();
		ui.doubleSpinBox_Command_xiaHua_V->hide();
		ui.doubleSpinBox_Command_xiaHua_angle->hide();
		ui.doubleSpinBox_Command_xiaHua_H->hide();

		ui.label_zhuoJian_XV->hide();
		ui.label_zhuoJian_YV_Limit->hide();
		ui.label_zhuoJian_ZV_Limit->hide();
		ui.doubleSpinBox_Command_zhuoJianXV->hide();
		ui.doubleSpinBox_Command_zhuoJianYV_Limit->hide();
		ui.doubleSpinBox_Command_zhuoJianZV_Limit->hide();
		//ui.textBrowser_note->hide();

	}
	else if (mode == 1)
	{
		ui.label_VKH_V->hide();
		ui.label_VKH_K->hide();
		ui.label_VKH_H->hide();
		ui.doubleSpinBox_Command_VKH_V->hide();
		ui.doubleSpinBox_Command_VKH_K->hide();
		ui.doubleSpinBox_Command_VKH_H->hide();

		ui.label_target->hide();
		ui.label_XYZV_X->hide();
		ui.label_XYZV_Y->hide();
		ui.label_XYZV_Z->hide();
		ui.label_XYZV_V->hide();
		ui.label_XYZV_Error->hide();
		ui.doubleSpinBox_Command_XYZV_X->hide();
		ui.doubleSpinBox_Command_XYZV_Y->hide();
		ui.doubleSpinBox_Command_XYZV_Z->hide();
		ui.doubleSpinBox_Command_XYZV_V->hide();
		ui.doubleSpinBox_Command_XYZV_Error->hide();

		ui.label_xiaHua->setVisible(true);
		ui.label_xiaHua_2->setVisible(true);
		ui.label_xiaHua_3->setVisible(true);
		ui.doubleSpinBox_Command_xiaHua_V->setVisible(true);
		ui.doubleSpinBox_Command_xiaHua_angle->setVisible(true);
		ui.doubleSpinBox_Command_xiaHua_H->setVisible(true);

		ui.label_zhuoJian_XV->hide();
		ui.label_zhuoJian_YV_Limit->hide();
		ui.label_zhuoJian_ZV_Limit->hide();
		ui.doubleSpinBox_Command_zhuoJianXV->hide();
		ui.doubleSpinBox_Command_zhuoJianYV_Limit->hide();
		ui.doubleSpinBox_Command_zhuoJianZV_Limit->hide();
		//ui.textBrowser_note->hide();

	}
	else if (mode == 2)
	{
		ui.label_VKH_V->hide();
		ui.label_VKH_K->hide();
		ui.label_VKH_H->hide();
		ui.doubleSpinBox_Command_VKH_V->hide();
		ui.doubleSpinBox_Command_VKH_K->hide();
		ui.doubleSpinBox_Command_VKH_H->hide();


		ui.label_target->setVisible(true);
		ui.label_XYZV_X->setVisible(true);
		ui.label_XYZV_Y->setVisible(true);
		ui.label_XYZV_Z->setVisible(true);
		ui.label_XYZV_V->setVisible(true);
		ui.label_XYZV_Error->setVisible(true);
		ui.doubleSpinBox_Command_XYZV_X->setVisible(true);
		ui.doubleSpinBox_Command_XYZV_Y->setVisible(true);
		ui.doubleSpinBox_Command_XYZV_Z->setVisible(true);
		ui.doubleSpinBox_Command_XYZV_V->setVisible(true);
		ui.doubleSpinBox_Command_XYZV_Error->setVisible(true);

		ui.label_xiaHua->hide();
		ui.label_xiaHua_2->hide();
		ui.label_xiaHua_3->hide();
		ui.doubleSpinBox_Command_xiaHua_V->hide();
		ui.doubleSpinBox_Command_xiaHua_angle->hide();
		ui.doubleSpinBox_Command_xiaHua_H->hide();

		ui.label_zhuoJian_XV->hide();
		ui.label_zhuoJian_YV_Limit->hide();
		ui.label_zhuoJian_ZV_Limit->hide();
		ui.doubleSpinBox_Command_zhuoJianXV->hide();
		ui.doubleSpinBox_Command_zhuoJianYV_Limit->hide();
		ui.doubleSpinBox_Command_zhuoJianZV_Limit->hide();
		//ui.textBrowser_note->hide();

	}

	else if (mode == 6)
	{
		ui.label_VKH_V->hide();
		ui.label_VKH_K->hide();
		ui.label_VKH_H->hide();
		ui.doubleSpinBox_Command_VKH_V->hide();
		ui.doubleSpinBox_Command_VKH_K->hide();
		ui.doubleSpinBox_Command_VKH_H->hide();


		ui.label_target->hide();
		ui.label_XYZV_X->hide();
		ui.label_XYZV_Y->hide();
		ui.label_XYZV_Z->hide();
		ui.label_XYZV_V->hide();
		ui.label_XYZV_Error->hide();
		ui.doubleSpinBox_Command_XYZV_X->hide();
		ui.doubleSpinBox_Command_XYZV_Y->hide();
		ui.doubleSpinBox_Command_XYZV_Z->hide();
		ui.doubleSpinBox_Command_XYZV_V->hide();
		ui.doubleSpinBox_Command_XYZV_Error->hide();

		ui.label_xiaHua->hide();
		ui.label_xiaHua_2->hide();
		ui.label_xiaHua_3->hide();
		ui.doubleSpinBox_Command_xiaHua_V->hide();
		ui.doubleSpinBox_Command_xiaHua_angle->hide();
		ui.doubleSpinBox_Command_xiaHua_H->hide();

		ui.label_zhuoJian_XV->setVisible(true);
		ui.label_zhuoJian_YV_Limit->setVisible(true);
		ui.label_zhuoJian_ZV_Limit->setVisible(true);
		ui.doubleSpinBox_Command_zhuoJianXV->setVisible(true);
		ui.doubleSpinBox_Command_zhuoJianYV_Limit->setVisible(true);
		ui.doubleSpinBox_Command_zhuoJianZV_Limit->setVisible(true);

		//ui.textBrowser_note->setVisible(true);

	}
	else
	{
		ui.label_VKH_V->hide();
		ui.label_VKH_K->hide();
		ui.label_VKH_H->hide();

		ui.doubleSpinBox_Command_VKH_V->hide();
		ui.doubleSpinBox_Command_VKH_K->hide();
		ui.doubleSpinBox_Command_VKH_H->hide();


		ui.label_target->hide();
		ui.label_XYZV_X->hide();
		ui.label_XYZV_Y->hide();
		ui.label_XYZV_Z->hide();
		ui.label_XYZV_V->hide();
		ui.label_XYZV_Error->hide();
		ui.doubleSpinBox_Command_XYZV_X->hide();
		ui.doubleSpinBox_Command_XYZV_Y->hide();
		ui.doubleSpinBox_Command_XYZV_Z->hide();
		ui.doubleSpinBox_Command_XYZV_V->hide();
		ui.doubleSpinBox_Command_XYZV_Error->hide();

		ui.label_zhuoJian_XV->hide();
		ui.label_zhuoJian_YV_Limit->hide();
		ui.label_zhuoJian_ZV_Limit->hide();
		ui.doubleSpinBox_Command_zhuoJianXV->hide();
		ui.doubleSpinBox_Command_zhuoJianYV_Limit->hide();
		ui.doubleSpinBox_Command_zhuoJianZV_Limit->hide();
		//ui.textBrowser_note->hide();

	}
	if (mode == 6)
	{
		udpSendTimer->start(25);
	}
	else
	{
		udpSendTimer->stop();
	}
	qDebug() << "change:" << mode;
}

void QtWidgetsApplication1::On_initsetting_triggerd()
{
	//

	qDebug() << "---!!!___";
	
}

void QtWidgetsApplication1::On_checkBox_selectAlpha_stateChanged(int arg)
{
	lineSeries_alpha_true->setVisible(bool(arg));
}
void QtWidgetsApplication1::On_checkBox_selectBeta_stateChanged(int arg)
{
	lineSeries_beta_true->setVisible(bool(arg));
}
void QtWidgetsApplication1::On_checkBox_selectTheta_stateChanged(int arg)
{
	lineSeries_theta_true->setVisible(bool(arg));
}
void QtWidgetsApplication1::On_checkBox_selectPhi_stateChanged(int arg)
{
	lineSeries_phi_true->setVisible(bool(arg));
}
void QtWidgetsApplication1::On_checkBox_selectPsi_stateChanged(int arg)
{
	lineSeries_psi_true->setVisible(bool(arg));
}

void QtWidgetsApplication1::On_checkBox_checkBox_true_H_stateChanged(int arg)
{
	lineSeries_Z_true->setVisible(bool(arg));
}
void QtWidgetsApplication1::On_checkBox_checkBox_expect_H_stateChanged(int arg)
{
	lineSeries_Z_expect->setVisible(bool(arg));
}

void QtWidgetsApplication1::On_checkBox_checkBox_Vx_stateChanged(int arg)
{
	lineSeries_Vx->setVisible(bool(arg));
}

void QtWidgetsApplication1::On_checkBox_checkBox_Vy_stateChanged(int arg)
{
	//qDebug() << "yyy";
	lineSeries_Vy->setVisible(bool(arg));
}

void QtWidgetsApplication1::On_checkBox_checkBox_Vz_stateChanged(int arg)
{
	//qDebug() << "zzzz";
	lineSeries_Vz->setVisible(bool(arg));
}



void QtWidgetsApplication1::InitTargetsList()
{
	QStandardItemModel* ItemModel = new QStandardItemModel(this);

	vector<std::string>::iterator it;
	for (it = targetNode_Name.begin(); it != targetNode_Name.end(); it++)
	{
		QStandardItem *item = new QStandardItem(QString::fromStdString(*it));
		ItemModel->appendRow(item);
	}
	ui.listView_targets->setModel(ItemModel);

}

void QtWidgetsApplication1::drawExpect_Z_slot()
{
	double X_expect, Y_expect, Z_expect;
	double Distance;
	//double falseTime=0;
	int flag = taskManager->pathGenerator_2->getNode(X_expect, Y_expect, Z_expect);
	while (flag != -2)
	{
		Distance = sqrt(pow(X_expect - data_origin_X, 2) + pow(Y_expect - data_origin_Y, 2));
		lineSeries_Z_expect->append(QPointF(Distance, Z_expect));						//向折线系列添加数据
		flag = taskManager->pathGenerator_2->getNode(X_expect, Y_expect, Z_expect);
	}
}

void QtWidgetsApplication1::udpReceive()
{
	int pitch_command;
	int yaw_command;

	int pitchDeadZone = 10;
	int yawDeadZone = 10;
	int pitchBias = (3095 + 1) / 2;
	int yawBias = (3095 + 1) / 2;

	UDPDateStruct receiveDate;
	while (leverUdpSocket->hasPendingDatagrams())
	{
		leverUdpSocket->readDatagram((char*)&receiveDate, sizeof(receiveDate));
		qDebug() << "read";
	}

	if (true)
	{
		pitch_command = 0;
		yaw_command = 1548;
		pitch_command -= pitchBias;
		yaw_command -= yawBias;
		if (abs(pitch_command) < pitchDeadZone) pitch_command = 0;
		if (abs(yaw_command) < yawDeadZone) yaw_command = 0;

	}

	taskManager->Command_Manual[1] += double(leverYawCommandProportion*yaw_command);
	taskManager->Command_Manual[2] += double(leverPitchCommandProportion*pitch_command);
	//Command_Manual[0]速度
	//Command_Manual[1]航向
	//Command_Manual[2]高度
}

void QtWidgetsApplication1::udpReceiveZhuoJianError()
{

	struct zhuoJianUDPDateStruct
	{
		int mode;
		double Z0Error;
		double Y0Error;	//雷达
		double Z1Error;
		double Y1Error;	//光电
	};
	//qDebug() << sizeof(zhuoJianUDPDateStruct);
	zhuoJianUDPDateStruct receiveDate;

	static int cnt = 0;
	while (zhuoJianErrorUdpSocket->hasPendingDatagrams())
	{
		zhuoJianErrorUdpSocket->readDatagram((char*)&receiveDate, sizeof(receiveDate));
		//qDebug() << "read";
	}

	if (receiveDate.mode == 1)	// 光电
	{
		taskManager->YZError[0] = -receiveDate.Y1Error;
		taskManager->YZError[1] = -receiveDate.Z1Error;
	}
	else if (receiveDate.mode == 2)	//雷达
	{
		taskManager->YZError[0] = -receiveDate.Y0Error;
		taskManager->YZError[1] = -receiveDate.Z0Error;
	}
	else if (receiveDate.mode == 3)	//卫星
	{
		taskManager->YZError[0] = -receiveDate.Y0Error;
		taskManager->YZError[1] = -receiveDate.Z0Error;
	}
	else if (receiveDate.mode == 4)	//雷达光电
	{
		if (abs(receiveDate.Z1Error) <= 0.001&&abs(receiveDate.Y1Error) <= 0.001)
		{
			taskManager->YZError[0] = -receiveDate.Y0Error;
			taskManager->YZError[1] = -receiveDate.Z0Error;
		}
		else
		{
			taskManager->YZError[0] = -receiveDate.Y1Error;
			taskManager->YZError[1] = -receiveDate.Z1Error;
		}

	}
	if (receiveDate.mode!=zhuoJianMode)
	{
		zhuoJianMode = receiveDate.mode;
		QString modeStr;
		switch (zhuoJianMode)
		{
		case 1:
			modeStr = "光电";
			break;
		case 2:
			modeStr = "雷达";
			break;
		case 3:
			modeStr = "卫星";
			break;
		case 4:
			modeStr = "雷达光电融合";
			break;
		default:
			break;
		}
		ui.textBrowser_zhuoJianMode->setText(modeStr);
	}
	if (cnt > 40)
	{
		qDebug() << "receiveDate.Y0Error:" << receiveDate.Y0Error << "receiveDate.Z0Error:" << receiveDate.Z0Error;
		qDebug() << "receiveDate.Y1Error:" << receiveDate.Y1Error << "receiveDate.Z1Error:" << receiveDate.Z1Error;
		qDebug() << "YError:" << taskManager->YZError[0] << "ZError:" << taskManager->YZError[1];
		cnt = 0;
	}
	cnt++;
	
}

void QtWidgetsApplication1::udpSendDAta()
{
	struct UdpData
	{
		//包长 180
		int   head = 0x55AA55AA; //包头				*55AA55AA
		float velAttackAngle = 0;           //真迎角表决值
		float ChPressure = 0;               //场压
		float pressure = 0;                 //气压Pt pa
		float staticPressure = 0;           //静压   pa
		float dynamicPressure = 0;          //动压   pa
		float barometricAltitude = 0;       //气压高度Hp
		float barometricAmendAltitude = 0;  //气压修正高度Hbc
		float VcAltitude = 0;               //校正空速度Vc  km/h
		float UpDownAltitude = 0;           //升降速度 
		float mach = 0;                     //马赫数 
		float airspeed = 0;                 //真空速 km/h
		float allTemperature = 0;           //总温Tt
		float staticTemperature = 0;        //静温Ts
		float STGMA = 0;                    //大气密度比
		float back1 = 0;                    //预留
		float back2 = 0;                    //预留
		float back3 = 0;                    //预留
		float back4 = 0;                    //预留
		float back5 = 0;                    //预留
		float notAmendBarometric = 0;       //未修正气压   pa
		float notAmendDynamicPressure = 0;  //未修正动压   pa
		float notAmendStaticPressure = 0;   //未修正静压   pa
		float notAmendMach = 0;             //未修正马赫数
		float velAttackAngleValue = 0;      //表决后真迎角
											//后加入
		float latitude = B, longitude = L;      //经纬度  °		*								
		float radioAltitude = H;            // 无线电高度  m	*
											//姿态
		float roll = clm_control->m_fst.m_dMu, pitch = (clm_control->m_fst.m_dGama + clm_control->m_fst.m_dAlpha) * 180 / PI, yaw = (clm_control->m_fst.m_dChi - clm_control->m_fst.m_dBeta) * 180 / PI;         // 横滚 俯仰 偏航  °	*
		float angVelX = 0, angVelY = 0, angVelZ = 0; // 三向角速度(palstance)  °/s
		float courseAngle = yaw;              // 航向角  °
		float sideslipAngle = taskManager->clm_control_task->m_fst.m_dBeta;            // 侧滑角   °
																					   //速度
		float velX = taskManager->clm_control_task->m_fst.m_Vx*3.6, velY = taskManager->clm_control_task->m_fst.m_Vy*3.6, velZ = (taskManager->clm_control_task->m_fst.m_Vz)*3.6;     // 三向速度(velocity)  东北天 km/h		*注意坐标系
		float accX = 0, accY = 0, accZ = 0;     // 三向加速度(acceleration) 东北天  m/s^2	*
		float groundSpeed = 0;          // 地速
		float overload = 0;             // 过载  g
		float airflowVelocity = 0;      // 气流速度
	};//飞仿数据
	UdpData *sendData = new UdpData;

	QByteArray str;
	str.clear();
	str.append((char*)sendData, sizeof(UdpData));
	sendUdpDataSocket->writeDatagram(str, QHostAddress(QString::fromStdString(udpSendTargetIP)), udpSendTargetPort);

	// 本地UDP测试
	struct  testUDP
	{
		double Dz=taskManager->clm_control_task->m_fst.m_dZ;
		double Dx = taskManager->clm_control_task->m_fst.m_dY;
	};
	testUDP *sendData1 = new testUDP;
	QByteArray str1;
	str1.clear();
	str1.append((char*)sendData1, sizeof(testUDP));
	sendUdpDataSocket->writeDatagram(str1, QHostAddress(QString::fromStdString("127.0.0.1")), 4001);
}

void QtWidgetsApplication1::On_trigered_QAction(QAction* action)
{
	//qDebug() << action;
	if (action->toolTip() == "ZHHK429Init_action")
	{
		qDebug() << "ZHHK429Init_action";
		myCAV429->init();
	}

}

void QtWidgetsApplication1::On_checkBox_isSerialPortSend_StateChange(int arg) {
	if (arg)
	{
		serialPortOutTimer->start(100);
	}
	else
	{
		serialPortOutTimer->stop();
	}
}

void QtWidgetsApplication1::On_checkBox_is429Send_StateChange(int arg) {
	if (arg)
	{
		cav429OutTimer->start(100);
		
	}
	else
	{
		cav429OutTimer->stop();
	}
}


void QtWidgetsApplication1::On_doubleSpinBox_Command_zhuoJianYV_Limit_valueChanged(double arg)
{
	VY_MAXLimt = arg;
}
void QtWidgetsApplication1::On_doubleSpinBox_Command_zhuoJianZV_Limit_valueChanged(double arg)
{
	VZ_MAXLimt = arg;
}

void QtWidgetsApplication1::On_doubleSpinBox_Command_zhuoJianXV_valueChanged(double arg)
{
	zhuoJianXV = arg;
}

void QtWidgetsApplication1::drawLandingPlaning()
{
	qDebug() << "draw";
	double maxY = 0;
	double minY = 0;
	double minX = 0;
	double maxX = 0;
	for (auto obj:landingPlaningInfo)
	{
		maxX = max(maxX, obj[0]);
		maxY = max(maxY, obj[1]);
		lineSeries_landingPlaning->append(QPointF(obj[0], obj[1]));	//向折线系列添加数据
		qDebug() << obj[0] << obj[1];
	}
	//for (auto obj : landingPlaningInfo)
	//{
	//	lineSeries_landingPlaning->append(QPointF(obj[0], obj[1]));	//向折线系列添加数据
	//	qDebug() << obj[0] << obj[1];
	//}
	//lineSeries_landingPlaning->append(QPointF(0, 0));
	//lineSeries_landingPlaning->append(QPointF(100, 0));
	//lineSeries_landingPlaning->append(QPointF(101, 100));
	qDebug()<<"X:" << minX << maxX;
	mChart_Z->axisX()->setRange(minX, maxX);
	mChart_Z->axisY()->setRange(minY, maxY);
	
}


void  QtWidgetsApplication1::use429SendSimData()
{
	simDataStruct_429 myData;
	static int cnt = 0;
	static double lastVx = clm_control->m_fst.m_Vx;
	static double lastVy = clm_control->m_fst.m_Vy;
	static double lastVz = clm_control->m_fst.m_Vz;
	if (cnt <1)
	{
		cnt++;
		return;
	}
	double Vx,Vy,Vz;
	Vx = clm_control->m_fst.m_Vx;
	Vy = clm_control->m_fst.m_Vy;
	Vz = clm_control->m_fst.m_Vz;
	myData.origin_Lon = data_origin_L0;
	myData.origin_Lat = data_origin_B0;
	myData.inertial_Barometric_Altitude = data_origin_H0;
	myData.chi = taskManager->clm_control_task->m_fst.m_dChi * 180 / PI;
	myData.theta = (clm_control->m_fst.m_dGama + clm_control->m_fst.m_dAlpha) * 180 / PI;
	myData.phi = clm_control->m_fst.m_dMu;
	myData.acc_East = Vx - lastVx;
	myData.acc_North = Vy - lastVy;
	myData.acc_Up = Vz - lastVz;
	myData.vel_North = Vy;
	myData.vel_East = Vx;
	myData.vel_Up = Vz;
	myCAV429->sendSimData(myData);
}



