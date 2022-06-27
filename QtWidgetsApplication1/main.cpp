

#include <QtWidgets/QApplication>

#include <QDebug>

#include "QtWidgetsApplication1.h"


#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>

#include "Control/GeneralDefinitions.h"
#include "global.h"
#include "Control/CloseLoopModel.h"
#include "taskManagement.h"
#include "ui_dialog_initsetting.h"

#pragma comment(lib, "winmm.lib")





using namespace std;



MMRESULT timer_id_simulation;


//MMRESULT timer_id_consoleOut;
CCloseLoopModel* clm_control = new CCloseLoopModel;
taskManagement* taskManager = new taskManagement(clm_control);


//轨迹生成变量，轨迹起点为飞行器起点
double X_c = clm_control->m_fst.m_dX;
double Y_c = clm_control->m_fst.m_dY;
double Z_c = clm_control->m_fst.m_dZ;


int main(int argc, char *argv[])
{





	//QYTopicSender* pstSender = new QYTopicSender("yy", NULL);


	//A ss;
	//memset(&ss.head, '!', sizeof(ss.head));
	//ss.a = inputarg;
	//ss.b = 1;

	//int serial = 0;

	//while (TRUE)
	//{
	//	ss.serial = serial++;
	//	//  pstSender->sendData((const char*)&ss,sizeof(ss));
	//	Sleep(1000);
	//}
	//getchar();
	//return 0;




	//timer_id_simulation = timeSetEvent(data_time + data_timedelay, 1, (LPTIMECALLBACK)catchTimer_simulation, DWORD(1), TIME_PERIODIC);
	timer_id_simulation = 0;	//启动时默认仿真状态为暂停
								//timer_id_consoleOut = timeSetEvent(500, 1, (LPTIMECALLBACK)catchTimer_consoleOut, DWORD(1), TIME_PERIODIC);
	QApplication a(argc, argv);





	////启动动画
	//QSplashScreen *splash = new QSplashScreen;
	////splash->setPixmap(QPixmap("C:\\Users\\P53\\Desktop\\601\\QtWidgetsApplication1\\QtWidgetsApplication1\\picture\\NUAA.jpg"));
	//splash->setPixmap(QPixmap(":/startflush/picture/NUAA.jpg"));
	//splash->show();
	////让对话框延迟一段时间显示
	//for (int i = 0; i < 1000; i++)
	//{
	//	splash->repaint();
	//}
	////------启动动画


	QtWidgetsApplication1 w;


	w.show();



	////清除启动动画
	////将窗口移动到屏幕的中央
	//w.move((QApplication::desktop()->width() - w.width()) / 4, (QApplication::desktop()->height() - w.height()) / 2);
	//splash->finish(&w);
	//delete splash;
	////------清除启动动画


	return a.exec();
}











//
void WINAPI catchTimer_simulation(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2);













void WINAPI catchTimer_simulation(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2)
{
	taskManager->Update();

}