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

	//	反馈12飞行状态
	int FeedBack(double* pFB);                                                             //反馈没有用？？

	//	输出量为五个舵面偏角m_delta,m_ddeltaa,m_ddeltac,
	//	m_ddeltar,m_ddeltay,m_ddeltaz,和推力m_dThrustc;	
	int Output(double* pOutputs);
	int Input(double* pInputs);

	int SetCtlParams(double* pParams);                                                     //设置控制器参数？？
	int Update();
	CGinv_f();
	CGinv_f(CGeneralModel Model);
	virtual ~CGinv_f();

};

#endif // !defined(AFX_FASTLOOP_H__CD5B3174_5A16_4914_8C84_44AD1E7D8351__INCLUDED_)












