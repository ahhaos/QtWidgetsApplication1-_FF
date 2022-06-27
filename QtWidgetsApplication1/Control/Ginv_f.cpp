// FastLoop.cpp: implementation of the CFastLoop class.
//
//////////////////////////////////////////////////////////////////////


#include "Ginv_f.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGinv_f::CGinv_f()
{
	//inputs
	m_dp_d = 0;
	m_dq_d = 0;
	m_dr_d = 0;

}
CGinv_f::CGinv_f(CGeneralModel Model)
{
	m_dp_d = 0;
	m_dq_d = 0;
	m_dr_d = 0;
	CCtlSystem::CCtlSystem(Model);
}

CGinv_f::~CGinv_f()
{

}

/*******************************************************
函数名：int CGinv_f::Input(double *pInputs)
输入：pInputs；指针
功能：输入p,q,r给定
********************************************************/
int CGinv_f::Input(double* pInputs)//dp_d,dq_d,dr_dThrust
{
	m_dp_d = pInputs[0];
	m_dq_d = pInputs[1];
	m_dr_d = pInputs[2];
	m_dThrustc = pInputs[3];
	return 0;
}

/*******************************************************
函数名：int CGinv_f::Output(double *pOutputs)
输入：pInputs；指针
功能：输出控制量
********************************************************/
int CGinv_f::Output(double* pOutputs)
{
	pOutputs[0] = m_ddeltaa;
	pOutputs[1] = m_ddeltac;
	pOutputs[2] = m_ddeltar;
	pOutputs[3] = m_ddeltay;
	pOutputs[4] = m_ddeltaz;
	return 0;
}

/*******************************************************
函数名：int CGinv_f::Update()
输入：void
功能：根据逆回路方程，求解控制量
********************************************************/
int CGinv_f::Update()
{
	//对应fastinv.m
	m_pCL->ChenckAlpha(m_dAlpha, m_dAlpha);//检查alpha值
	double pic = 3.1415926535897932384626 / 180;

	double q_ = m_dRho * m_dV * m_dV / 2;//动压
	double l_ = q_ * m_dS * m_db * ((*m_pCL)(m_pCL->C_lbeta, m_dAlpha) * m_dBeta                 //有问题??
		+ (*m_pCL)(m_pCL->C_lp, m_dAlpha) * m_dp * m_db / 2 / m_dV
		+ (*m_pCL)(m_pCL->C_lr, m_dAlpha) * m_dr * m_db / 2 / m_dV);//(*m_pCL)(m_pCL->C_lp,m_dAlpha)小括号运算符重载
	double m_ = q_ * m_dS * m_dC_
		* ((*m_pCL)(m_pCL->C_mo, m_dAlpha) + (*m_pCL)(m_pCL->C_mq, m_dAlpha) * m_dq * m_dC_ / 2 / m_dV);
	double n_ = q_ * m_dS * m_db * ((*m_pCL)(m_pCL->C_nbeta, m_dAlpha) * m_dr * m_db / 2 / m_dV);

	double fpx = (m_dIz * l_ + m_dIxz * n_ + m_dIxz * (m_dIx - m_dIy + m_dIz) * m_dp * m_dq
		+ (m_dIz * (m_dIy - m_dIz) - m_dIxz * m_dIxz) * m_dq * m_dr) / (m_dIx * m_dIz - m_dIxz * m_dIxz);
	double fqx = (1 / m_dIy) * (m_ + (m_dIz - m_dIx) * m_dp * m_dr + m_dIxz * (m_dr * m_dr - m_dp * m_dp));
	double frx = (m_dIxz * l_ + m_dIx * n_ + (m_dIx * (m_dIx - m_dIy) + m_dIxz * m_dIxz) * m_dp * m_dq
		- m_dIxz * (m_dIx - m_dIy + m_dIz) * m_dq * m_dr) / (m_dIx * m_dIz - m_dIxz * m_dIxz);

	double dp_d = m_dp_d - fpx;
	double dq_d = m_dq_d - fqx;
	double dr_d = m_dr_d - frx;

	//控制舵面映射到滚转、俯仰、偏航加速度的系数矩阵
	double gp1 = q_ * m_dS * m_db * (m_dIz * (*m_pCL)(m_pCL->C_ldeltaa, m_dAlpha)
		+ m_dIxz * (*m_pCL)(m_pCL->C_ndeltaa, m_dAlpha)) / (m_dIx * m_dIz - m_dIxz * m_dIxz);
	double gp3 = q_ * m_dS * m_db * (m_dIz * (*m_pCL)(m_pCL->C_ldeltar, m_dAlpha)
		+ m_dIxz * (*m_pCL)(m_pCL->C_ndeltar, m_dAlpha)) / (m_dIx * m_dIz - m_dIxz * m_dIxz);
	double gp4 = -m_dIxz * m_dThrustc * m_dxT * pic / ((m_dIx * m_dIz - m_dIxz * m_dIxz));
	double gq2 = q_ * m_dS * m_dC_ * (*m_pCL)(m_pCL->C_mdeltac, m_dAlpha) / m_dIy;
	double gq5 = m_dThrustc * m_dxT * pic / m_dIy;
	double gr1 = q_ * m_dS * m_db * (m_dIxz * (*m_pCL)(m_pCL->C_ldeltaa, m_dAlpha)
		+ m_dIx * (*m_pCL)(m_pCL->C_ndeltaa, m_dAlpha)) / (m_dIx * m_dIz - m_dIxz * m_dIxz);
	double gr3 = q_ * m_dS * m_db * (m_dIxz * (*m_pCL)(m_pCL->C_ldeltar, m_dAlpha)
		+ m_dIx * (*m_pCL)(m_pCL->C_ndeltar, m_dAlpha)) / (m_dIx * m_dIz - m_dIxz * m_dIxz);
	double gr4 = -m_dIx * m_dThrustc * m_dxT * pic / (m_dIx * m_dIz - m_dIxz * m_dIxz);

	//广义逆矩阵求解过程
	double aa = gp1 * gp1 * m_da_max + gp3 * gp3 * m_dr_max + gp4 * gp4 * m_dy_max;	//  aa	0	bb
	double bb = gr1 * gp1 * m_da_max + gr3 * gp3 * m_dr_max + gr4 * gp4 * m_dy_max;	//  0	cc	0
	double cc = gq2 * gq2 * m_dc_max + gq5 * gq5 * m_dz_max;					//  bb	0	dd
	double dd = gr1 * gr1 * m_da_max + gr3 * gr3 * m_dr_max + gr4 * gr4 * m_dy_max;

	double w0 = aa * dd - bb * bb;
	double w1 = dd / w0;	//  w1	0	w3
	double w2 = 1 / cc;		//  0	w2	0
	double w3 = -bb / w0;	//  w3	0	w4
	double w4 = aa / w0;	//

	double dlta11 = gp1 * w1 + gr1 * w3;
	double dlta13 = gp1 * w3 + gr1 * w4;
	double dlta22 = gq2 * w2;
	double dlta31 = gp3 * w1 + gr3 * w3;
	double dlta33 = gp3 * w3 + gr3 * w4;
	double dlta41 = gp4 * w1 + gr4 * w3;
	double dlta43 = gp4 * w3 + gr4 * w4;
	double dlta52 = gq5 * w2;



	dlta11 = dlta11 * m_da_max;
	dlta13 = dlta13 * m_da_max;
	dlta22 = dlta22 * m_dc_max;
	dlta31 = dlta31 * m_dr_max;
	dlta33 = dlta33 * m_dr_max;
	dlta41 = dlta41 * m_dy_max;
	dlta43 = dlta43 * m_dy_max;
	dlta52 = dlta52 * m_dz_max;

	if (m_ddeltaa > m_da_max
		|| m_ddeltac > m_dc_max
		|| m_ddeltar > m_dr_max
		|| m_ddeltay > m_dy_max
		|| m_ddeltaz > m_dz_max
		)
		int pause = 1;

	m_ddeltaa = dlta11 * dp_d + dlta13 * dr_d;							//dlta11	0		dlta13
	m_ddeltac = dlta22 * dq_d;										//0			dlta22	0
	m_ddeltar = dlta31 * dp_d + dlta33 * dr_d;							//dlta31	0		dlta33
	m_ddeltay = dlta41 * dp_d + dlta43 * dr_d;							//dalt41	0		dlta43
	m_ddeltaz = dlta52 * dq_d;										//0			dlta52		0
	//END广义逆求解过程

/*	double check1 = m_ddeltaa * gp1 + m_ddeltar * gp3 + m_ddeltay * gp4;
	double check2 = m_ddeltac * gq2 + m_ddeltaz * gq5;
	double check3 = m_ddeltaa * gr1 + m_ddeltar * gr3 + m_ddeltay * gr4;*/

	m_ddeltac += (*m_pCL)(m_pCL->delta_c0, m_dAlpha); //加上鸭翼0位角;
	return 0;
}

int CGinv_f::SetCtlParams(double* pParams)
{
	return 0;
}

/*******************************************************
函数名：int CGinv_f::FeedBack(double *pFB)
输入：指向状态量类的指针
功能：反馈用，构成闭环
********************************************************/
int CGinv_f::FeedBack(double* pFB)
{
	SFlightStatus::operator =(*(SFlightStatus*)pFB);
	return 0;
}












