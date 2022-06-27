// CtlSystem.h: interface for the CCtlSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTLSYSTEM_H__20F0FC7F_6CD5_47B7_80F6_7D5EA3A834F7__INCLUDED_)
#define AFX_CTLSYSTEM_H__20F0FC7F_6CD5_47B7_80F6_7D5EA3A834F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GeneralDefinitions.h"

class CCtlSystem : public CGeneralModel  //控制器基本模型，不直接使用，用来派生出其他控制器类。
{
public:

	//设置控制参数
	virtual int SetCtlParams(double* pParams);

	//控制对象的反馈信息
	virtual int FeedBack(double* pFB);

	//刷新函数,根据输入和反馈得到输出
	virtual int Update();

	//控制器输出，将输出数据赋值到pOutputs所指向的内存空间
	virtual int Output(double* pOutputs);

	//控制器输入，用来获得pInputs所指向的输入数据
	virtual int Input(double* pInputs);
	CCtlSystem();
	CCtlSystem(CGeneralModel Model);
	virtual ~CCtlSystem();
};

#endif // !defined(AFX_CTLSYSTEM_H__20F0FC7F_6CD5_47B7_80F6_7D5EA3A834F7__INCLUDED_)
