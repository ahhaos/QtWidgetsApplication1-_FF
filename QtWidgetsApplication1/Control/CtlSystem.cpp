// CtlSystem.cpp: implementation of the CCtlSystem class.
//
//////////////////////////////////////////////////////////////////////

#include "CtlSystem.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCtlSystem::CCtlSystem()
{

}
CCtlSystem::CCtlSystem(CGeneralModel Model)
{
	CGeneralModel::operator =(Model);
}

CCtlSystem::~CCtlSystem()
{

}

int CCtlSystem::Input(double* dInputs)
{
	return 0;
}

int CCtlSystem::Output(double* dOutputs)
{
	return 0;
}

int CCtlSystem::Update()
{
	return 0;
}

/*******************************************************
函数名：int CCtlSystem::FeedBack(double *pFB)
输入：反馈的飞机状态
功能：设置飞机的实际状态
********************************************************/
int CCtlSystem::FeedBack(double* pFB)
{
	SFlightStatus::operator =(*(SFlightStatus*)pFB);
	return 0;
}

int CCtlSystem::SetCtlParams(double* pParams)
{
	return 0;
}
