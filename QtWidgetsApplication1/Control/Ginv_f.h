// FastLoop.h: interface for the CFastLoop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FASTLOOP_H__CD5B3174_5A16_4914_8C84_44AD1E7D8351__INCLUDED_)
#define AFX_FASTLOOP_H__CD5B3174_5A16_4914_8C84_44AD1E7D8351__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CtlSystem.h"

class CGinv_f : public CCtlSystem
{
	//inputs
	double m_dp_d;
	double m_dq_d;
	double m_dr_d;
public:

	//	����12����״̬
	int FeedBack(double* pFB);                                                             //����û���ã���

	//	�����Ϊ�������ƫ��m_delta,m_ddeltaa,m_ddeltac,
	//	m_ddeltar,m_ddeltay,m_ddeltaz,������m_dThrustc;	
	int Output(double* pOutputs);
	int Input(double* pInputs);

	int SetCtlParams(double* pParams);                                                     //���ÿ�������������
	int Update();
	CGinv_f();
	CGinv_f(CGeneralModel Model);
	virtual ~CGinv_f();

};

#endif // !defined(AFX_FASTLOOP_H__CD5B3174_5A16_4914_8C84_44AD1E7D8351__INCLUDED_)












