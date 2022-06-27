// CtlSystem.h: interface for the CCtlSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTLSYSTEM_H__20F0FC7F_6CD5_47B7_80F6_7D5EA3A834F7__INCLUDED_)
#define AFX_CTLSYSTEM_H__20F0FC7F_6CD5_47B7_80F6_7D5EA3A834F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GeneralDefinitions.h"

class CCtlSystem : public CGeneralModel  //����������ģ�ͣ���ֱ��ʹ�ã����������������������ࡣ
{
public:

	//���ÿ��Ʋ���
	virtual int SetCtlParams(double* pParams);

	//���ƶ���ķ�����Ϣ
	virtual int FeedBack(double* pFB);

	//ˢ�º���,��������ͷ����õ����
	virtual int Update();

	//�������������������ݸ�ֵ��pOutputs��ָ����ڴ�ռ�
	virtual int Output(double* pOutputs);

	//���������룬�������pInputs��ָ�����������
	virtual int Input(double* pInputs);
	CCtlSystem();
	CCtlSystem(CGeneralModel Model);
	virtual ~CCtlSystem();
};

#endif // !defined(AFX_CTLSYSTEM_H__20F0FC7F_6CD5_47B7_80F6_7D5EA3A834F7__INCLUDED_)
