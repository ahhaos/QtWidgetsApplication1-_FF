// Ginv_vs.h: interface for the CGinv_vs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GINV_VS_H__6A074456_4391_4D58_AAF0_7FB7D683A80D__INCLUDED_)
#define AFX_GINV_VS_H__6A074456_4391_4D58_AAF0_7FB7D683A80D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CtlSystem.h"
#include "CtlSystemHeader.h"

class CGinv_vs : public CCtlSystem
{
	//inputs
	double m_dV_d;
	double m_dKh_d;
	double m_dGama_d;
	//outputs
	double m_dAlphac;
	double m_dBetac;
	double m_dMuc;
	//double m_dThrustc;

	bool   m_bDelay;	//用于滞后控制

	double m_dErr;		//Iter中迭代终值误差
	int	   m_iCount;	//Iter中迭代次数上限

public:
	double Fun_Thrust(double alphac, double dV_d);
	int Output(double* dOutputs);
	int Input(double* dInputs);
	int Update();
	CGinv_vs();
	CGinv_vs(CGeneralModel Model);
	virtual ~CGinv_vs();

private:

	//动态逆中一个求数值解的函数
	double Fun_Alphac(double alpha);

	//	牛顿迭代法求解Fun_Alphac，超出迭代次数和Alpha超出
	//	特性线有效范围时结束并返回false否则为true。x0为迭
	//	初值，可代入上一次求解的结果来加快收敛，result为
	//	计算的结果。
	bool Iter(double x0, double& result);

	//	减半递推搜索法。由于在极端飞行状态下，牛顿迭代法
	//	在迭代过程中会超出Alpha的有效范围，在此条件下将调
	//	RecursiveHalving对Fun_Alphac进行求解，由于该方法
	//	效率较低，所以不直接使用。
	//	参数a为区间下限，b为区间上限，result为搜索结果，
	//	已递归调用的形式进行，搜索失败将返回false，否则为true。
	bool RecursiveHalving(double a, double b, double& result);

};

#endif // !defined(AFX_GINV_VS_H__6A074456_4391_4D58_AAF0_7FB7D683A80D__INCLUDED_)












