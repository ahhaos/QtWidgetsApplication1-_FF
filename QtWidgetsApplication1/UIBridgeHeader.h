#pragma once
//���ļ�Ŀ����Ϊ���ܹ���UI QtWidgetsApplication1ʹ��taskManger�еĺ�����clm_control�е�����

#include <windows.h>
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include "global.h"
#include "Control/CloseLoopModel.h"
#include "taskManagement.h"


extern  CCloseLoopModel* clm_control;	//����cpp��main.cpp��������ʵ������Ŀ����Ϊ���ܹ���QtWidgetsApplication1.cpp���ļ����е��÷������ݡ������������
extern  taskManagement* taskManager;

extern MMRESULT timer_id_simulation;
//extern MMRESULT timer_id_consoleOut;
//extern taskManagement* taskManager;
extern void WINAPI catchTimer_simulation(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2);
extern void netSend_slot();

//void WINAPI catchTimer_consoleOut(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2);

