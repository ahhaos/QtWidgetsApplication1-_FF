// Ginv_vs.cpp: implementation of the CGinv_vs class.
//
//////////////////////////////////////////////////////////////////////


#include "Ginv_vs.h"
#include <math.h>
#include <QDebug>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGinv_vs::CGinv_vs()
{
	m_dErr = 1e-6;
	m_dAlphac = 0.5;
	m_iCount = 3000;
}
CGinv_vs::CGinv_vs(CGeneralModel Model)
{
	m_dErr = 1e-6;
	m_dAlphac = 0.5;
	CCtlSystem::CCtlSystem(Model);
}

CGinv_vs::~CGinv_vs()
{

}

/*******************************************************
函数名：int CGinv_vs::Update()
输入：void
功能：根据逆方程，求解alpha，beta，mu给定
********************************************************/
int CGinv_vs::Update()
{
	int iError = 0;
	double q_ = 0.5 * m_dRho * m_dV * m_dV;//动压
	double Vz_d = m_dV * m_dKh_d * cos(m_dGama);
	double Vy_d = m_dV * m_dGama_d + m_dg * cos(m_dGama);
	if (Vy_d > 0)
	{
		m_dMuc = atan(Vz_d / Vy_d);
		m_bDelay = false;
	}
	else if (Vy_d < 0/*q_*m_dS*(*m_pCL)(m_pCL->C_L,-0.001)*/)
	{
		m_dMuc = atan(Vz_d / Vy_d);
		m_dMuc += (Vz_d < 0 ? -PI : PI);
		m_bDelay = true;
	}
	else
	{
		Vz_d = 0;//mark
		if (m_bDelay)
		{
			m_dMuc = atan(Vz_d / Vy_d);
			m_dMuc += (Vz_d < 0 ? -PI : PI);
		}
		else
		{
			m_dMuc = atan(Vz_d / Vy_d);
		}
	}

	m_dBetac = 0;
	if (Iter(m_dAlphac, m_dAlphac) == false)
		if (RecursiveHalving(-3.4910000e-001, 1.5707963, m_dAlphac) == false)
		{
			if (RecursiveHalving(1.5707964, 1.7453000e+000, m_dAlphac) == false)
				iError = CTL_ERROR_ALPHAC_INVALID;
		}
	m_dThrustc = (m_dM * m_dV_d + q_ * m_dS * (*m_pCL)(m_pCL->C_D, m_dAlpha) + m_dM * m_dg * sin(m_dGama)) / cos(m_dAlpha);
	//Tc=(M*V_d + q_*S*interp1(al,C_D_al,alphac) + M*g*sin(gama)) / cos(alphac);
	return iError;
}

/*******************************************************
函数名：int CGinv_vs::Input(double *pInputs)
输入：指针
功能：输入v,,kh,gama给定
********************************************************/
int CGinv_vs::Input(double* dInputs)
{
	m_dV_d = dInputs[0];
	m_dKh_d = dInputs[1];
	m_dGama_d = dInputs[2];
	return 0;
}

/*******************************************************
函数名：int CGinv_s::Output(double *pOutputs)
输入：指针
功能：输出alpha，beta,mu,给定
********************************************************/
int CGinv_vs::Output(double* dOutputs)
{
	dOutputs[0] = m_dAlphac;
	dOutputs[1] = m_dBetac;
	dOutputs[2] = m_dMuc;
	dOutputs[3] = m_dThrustc;
	return 0;
}

/*******************************************************
函数名：bool CGinv_vs::Iter(double x0,double &result)
输入：x0：求解精度;result:结果
输出：能否求解
功能：牛顿迭代法求alpha
********************************************************/
bool CGinv_vs::Iter(double x0, double& result)
{
	int count(m_iCount);
	double x1 = x0;
	x0 = x0 - 0.5 * 3.1415926535897932384626 / 180;
	double x2;

	bool bavailable = m_pCL->ChenckAlpha(x0, x0);
	if (bavailable && fabs(x1 - x0) >= m_dErr)
	{
		while (count--)
		{
			x2 = x1 - (Fun_Alphac(x1) / (Fun_Alphac(x1) - Fun_Alphac(x0))) * (x1 - x0);
			bavailable = m_pCL->ChenckAlpha(x2, x2);
			x0 = x1;
			x1 = x2;
			if (fabs(x1 - x0) <= m_dErr)
			{
				result = x1;
				return bavailable;
			}
		}
	}
	return false;
}

double CGinv_vs::Fun_Alphac(double alpha)
{
	double q_ = 0.5 * m_dRho * m_dV * m_dV;
	/*	double result=((m_dM*m_dV_d + q_*m_dS*(*m_pCL)(m_pCL->C_D,alpha)) * sin(alpha)
			+ m_dM*m_dg*cos(m_dGama+alpha)) * cos(m_dMuc)
			+ m_dM*m_dV*cos(alpha)*(cos(m_dGama)*sin(m_dMuc)*m_dKh_d + cos(m_dMuc)*m_dGama_d)
			- q_*m_dS*(*m_pCL)(m_pCL->C_L,alpha);
		return result;*/
		/*	return (m_dM*m_dV_d + q_*m_dS*(*m_pCL)(m_pCL->C_D,alpha) + m_dM*m_dg*sin(m_dGama) ) *tan(alpha)
				+ q_*m_dS*(*m_pCL)(m_pCL->C_L,alpha) - m_dM*m_dV*cos(m_dGama)*sin(m_dMuc)*m_dKh_d
				-m_dM*m_dV*cos(m_dMuc)*m_dGama_d - m_dM*m_dg*cos(m_dGama)*cos(m_dMuc);*/
	return (m_dM * m_dV_d + q_ * m_dS * (*m_pCL)(m_pCL->C_D, alpha) + m_dM * m_dg * sin(m_dGama)) * tan(alpha)
		+ q_ * m_dS * (*m_pCL)(m_pCL->C_L, alpha) - m_dM * m_dV * cos(m_dGama) * sin(m_dMu) * m_dKh_d
		- m_dM * m_dV * cos(m_dMu) * m_dGama_d - m_dM * m_dg * cos(m_dGama) * cos(m_dMu);
	/*	y = ( M*V_d + q_*S* interp1(al,C_L_al,x) + M*g*sin(gama) ) * tan(x)...
		+q_*S*interp1(al,C_L_al,x) - M*V*cos(gama)*sin(muc)*kh_d...
		-M*V*cos(muc)*gama_d - M*g*cos(gama)*cos(muc);*/
}

bool CGinv_vs::RecursiveHalving(double a, double b, double& result)
{
	if (b < a) return false;
	double fa = Fun_Alphac(a);
	double fb = Fun_Alphac(b);
	if (fa * fb > 0)
	{
		if (b - a < 1E-3 || b - a < m_dErr)
			return false;
		else
		{
			double c = (a + b) / 2;
			if (RecursiveHalving(a, c, result))
				return true;
			return RecursiveHalving(c, b, result);
		}
	}
	if (b - a < m_dErr)
	{
		result = (a + b) / 2;
		return true;
	}
	double c = (a + b) / 2;
	double fc = Fun_Alphac(c);
	if (fa * fc < 0)
		return RecursiveHalving(a, c, result);
	return RecursiveHalving(c, b, result);
}

//求推力公式
//alphac    迎角
//dV_d       V导数
/*******************************************************
函数名：double CGinv_vs::Fun_Thrust(double alphac,double dV_d)
输入：alphac    迎角;dV_d       V导数
输出：推力
功能：求推力
********************************************************/
double CGinv_vs::Fun_Thrust(double alphac, double dV_d)
{

	return (m_dM * dV_d + 0.5 * m_dRho * m_dV * m_dV * m_dS * (*m_pCL)(m_pCL->C_D, alphac)
		+ m_dM * m_dg * sin(m_dGama)) / cos(alphac);
}












