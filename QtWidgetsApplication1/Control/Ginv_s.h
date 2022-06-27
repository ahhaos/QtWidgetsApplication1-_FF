// SlowLoop.h: interface for the CGinv_s class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SLOWLOOP_H__2D27949C_C6A0_42CC_87E6_3F15CA696E80__INCLUDED_)
#define AFX_SLOWLOOP_H__2D27949C_C6A0_42CC_87E6_3F15CA696E80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CtlSystem.h"

class CGinv_s : public CCtlSystem
{
	//inputs
	double m_dAlpha_d;
	double m_dBeta_d;
	double m_dMu_d;
	//outputs
	double m_dpc;
	double m_dqc;
	double m_drc;
public:
	int Update();
	int SetCtlParams(double* pParams);
	int Output(double* pOutputs);
	int Input(double* pInputs);
	CGinv_s();
	CGinv_s(CGeneralModel Model);
	virtual ~CGinv_s();

};

#endif // !defined(AFX_SLOWLOOP_H__2D27949C_C6A0_42CC_87E6_3F15CA696E80__INCLUDED_)
























