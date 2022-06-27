#pragma once
//该文件目的是为了能够让UI QtWidgetsApplication1使用taskManger中的函数和clm_control中的数据

#include <windows.h>
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include "global.h"
#include "Control/CloseLoopModel.h"
#include "taskManagement.h"


extern  CCloseLoopModel* clm_control;	//在主cpp中main.cpp中声明和实例化，目的是为了能够在QtWidgetsApplication1.cpp等文件中中调用仿真数据、操作任务管理
extern  taskManagement* taskManager;

extern MMRESULT timer_id_simulation;
//extern MMRESULT timer_id_consoleOut;
//extern taskManagement* taskManager;
extern void WINAPI catchTimer_simulation(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2);
extern void netSend_slot();

//void WINAPI catchTimer_consoleOut(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2);

