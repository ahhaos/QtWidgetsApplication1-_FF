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

	bool   m_bDelay;	//�����ͺ����

	double m_dErr;		//Iter�е�����ֵ���
	int	   m_iCount;	//Iter�е�����������

public:
	double Fun_Thrust(double alphac, double dV_d);
	int Output(double* dOutputs);
	int Input(double* dInputs);
	int Update();
	CGinv_vs();
	CGinv_vs(CGeneralModel Model);
	virtual ~CGinv_vs();

private:

	//��̬����һ������ֵ��ĺ���
	double Fun_Alphac(double alpha);

	//	ţ�ٵ��������Fun_Alphac����������������Alpha����
	//	��������Ч��Χʱ����������false����Ϊtrue��x0Ϊ��
	//	��ֵ���ɴ�����һ�����Ľ�����ӿ�������resultΪ
	//	����Ľ����
	bool Iter(double x0, double& result);

	//	��������������������ڼ��˷���״̬�£�ţ�ٵ�����
	//	�ڵ��������лᳬ��Alpha����Ч��Χ���ڴ������½���
	//	RecursiveHalving��Fun_Alphac������⣬���ڸ÷���
	//	Ч�ʽϵͣ����Բ�ֱ��ʹ�á�
	//	����aΪ�������ޣ�bΪ�������ޣ�resultΪ���������
	//	�ѵݹ���õ���ʽ���У�����ʧ�ܽ�����false������Ϊtrue��
	bool RecursiveHalving(double a, double b, double& result);

};

#endif // !defined(AFX_GINV_VS_H__6A074456_4391_4D58_AAF0_7FB7D683A80D__INCLUDED_)












