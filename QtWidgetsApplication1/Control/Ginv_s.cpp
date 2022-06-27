// SlowLoop.cpp: implementation of the CGinv_s class.
//
//////////////////////////////////////////////////////////////////////


#include "Ginv_s.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGinv_s::CGinv_s()
{

}
CGinv_s::CGinv_s(CGeneralModel Model)
{
	CCtlSystem::CCtlSystem(Model);
}

CGinv_s::~CGinv_s()
{

}

/*******************************************************
��������int CGinv_s::Input(double *pInputs)
���룺ָ��
���ܣ�����alpha,beta,mu,thrust����
********************************************************/
int CGinv_s::Input(double* pInputs)
{
	m_dAlpha_d = pInputs[0];
	m_dBeta_d = pInputs[1];
	m_dMu_d = pInputs[2];
	m_dThrustc = pInputs[3];
	return 0;
}

/*******************************************************
��������int CGinv_s::Output(double *pOutputs)
���룺ָ��
���ܣ����P��q,r,����
********************************************************/
int CGinv_s::Output(double* pOutputs)
{
	pOutputs[0] = m_dpc;
	pOutputs[1] = m_dqc;
	pOutputs[2] = m_drc;
	return 0;
}

int CGinv_s::SetCtlParams(double* pParams)
{
	return 0;
}

/*******************************************************
��������int CGinv_s::Update()
���룺void
���ܣ������淽�̣����p.q.r����
********************************************************/
int CGinv_s::Update()
{
	//��Ӧslowinv.m
	if (m_pCL->ChenckAlpha(m_dAlpha, m_dAlpha) == false)
		int pause = 1;
	double pic = 3.1415926535897932384626 / 180;
	double q_ = m_dRho * m_dV * m_dV / 2;//��ѹ
	double Tx = m_dThrustc;//������X���ϵķ���

	double falpha = (1 / (m_dM * m_dV * cos(m_dBeta)))
		* (-q_ * m_dS * (*m_pCL)(m_pCL->C_L, m_dAlpha) + m_dM * m_dg * cos(m_dMu) - Tx * sin(m_dAlpha));

	double fbeta = (1 / m_dM / m_dV) * (q_ * m_dS * (*m_pCL)(m_pCL->C_ybeta, m_dAlpha)
		* m_dBeta * cos(m_dBeta) + m_dM * m_dg * cos(m_dGama) * sin(m_dMu) - Tx * sin(m_dBeta) * cos(m_dAlpha));

	double fmu = (1 / (m_dM * m_dV)) * (q_ * m_dS * (*m_pCL)(m_pCL->C_L, m_dAlpha) * (tan(m_dBeta) + tan(m_dGama) * sin(m_dMu)))
		+ (1 / (m_dM * m_dV)) * (q_ * m_dS * (*m_pCL)(m_pCL->C_ybeta, m_dAlpha) * m_dBeta * tan(m_dGama) * cos(m_dMu) * cos(m_dBeta))
		- (m_dg / m_dV) * cos(m_dGama) * cos(m_dMu) * tan(m_dBeta)
		+ (Tx / (m_dM * m_dV)) * (tan(m_dGama) * (sin(m_dMu) * sin(m_dAlpha)
			- cos(m_dMu) * sin(m_dBeta) * cos(m_dAlpha)) + tan(m_dBeta) * sin(m_dAlpha));

	double sa = -tan(m_dBeta) * cos(m_dAlpha);	//P41 5.3.5			sa	 1	 se
	double sb = sin(m_dAlpha);				//					sb	 0	 sf
	double sc = cos(m_dAlpha) / cos(m_dBeta);	//					sc	 0	 sg
	double se = -tan(m_dBeta) * sin(m_dAlpha);
	double sf = -cos(m_dAlpha);
	double sg = sin(m_dAlpha) / cos(m_dBeta);

	double pg00 = sb * sg - sc * sf;
	double pg11 = 0;
	double pg12 = sg / pg00;
	double pg13 = -sf / pg00;
	double pg21 = 1;
	double pg22 = (sc * se - sa * sg) / pg00;
	double pg23 = (sa * sf - se * sb) / pg00;
	double pg31 = 0;
	double pg32 = -sc / pg00;
	double pg33 = sb / pg00;

	m_dpc = pg11 * (m_dAlpha_d - falpha) + pg12 * (m_dBeta_d - fbeta) + pg13 * (m_dMu_d - fmu);
	m_dqc = pg21 * (m_dAlpha_d - falpha) + pg22 * (m_dBeta_d - fbeta) + pg23 * (m_dMu_d - fmu);
	m_drc = pg31 * (m_dAlpha_d - falpha) + pg32 * (m_dBeta_d - fbeta) + pg33 * (m_dMu_d - fmu);
	return 0;
}
























