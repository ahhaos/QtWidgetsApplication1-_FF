// DIController.h: interface for the CDIController class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DICONTROLLER_H__FFFF2C75_CA62_463A_A9E1_EE86740D174D__INCLUDED_)
#define AFX_DICONTROLLER_H__FFFF2C75_CA62_463A_A9E1_EE86740D174D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CtlSystem.h"
#include "Ginv_f.h"
#include "Ginv_s.h"
#include "Ginv_vs.h"
#include "CtlSystemHeader.h"

class CDIController : public CCtlSystem
{
	double		m_dInputs[4];	//ָ������
	CGinv_f		m_gf;
	CGinv_s		m_gs;
	CGinv_vs	m_gvs;

	double		m_dGama_I;		//Gama�������֣���������Gama��̬���
	double		m_dMu_d;		//���ڹ�ת���˲���4/(S+4);

	CPID		m_pidKh_d;
	double		m_doKh;
	CPID		m_pidGama_d;
	double		m_doGama;
	double		m_doV;

	double		m_doX;

	double		m_doY;

	double		m_doZ;

public:
	CPID		m_pidX_d;
	CPID		m_pidY_d;
	CPID		m_pidZ_d;

	//int m_speed_pattern;


	///////////////////////////////////////////////////////////////////////////
	SFlightStatus	m_pfstd;	//��ǰ�����õ�״̬΢�־���
	SFlightStatus	m_pfst;		//����Follow��x,y,zԤ��ĸ��ٺ�������Ҫ�ķ���״̬
	SFlightStatus	m_lpfst;	//������һ���ڵ�m_pfst,����΢��
//	Ship			m_ship;		//��β��,����������
//	Wind			m_wind;		//��������
	///////////////////////////////////////////////////////////////////////////
public:
	SFlightStatus m_fstd;	//��Ӧ΢��
	SFlightStatus m_fstc;	//ָ��
	int	m_iFollowCount;			//��ǰ�������ļ����������ڷ�ֹ΢�ֳ���;
	int	m_iInputMod;			//���뷽ʽ
	SControllerParams m_cp;
public:
	void Input_Attitude(double pInputs[], bool b4Inputs = false, bool bVelocity = false);
	double Gravity(double gmin);
	void SetT(double dT);
	int Follow(double x, double y, double z, double m_ship_dH, double m_ship_p, double m_ship_q/*,double m_shiptail_Vx,double m_shiptail_Vy,double m_shiptail_Vz*/);
	void SetStaticParams(SStaticParams sp);
	void SetCtlParams(SControllerParams cp);
	//int Update();
	int Update();
	int Update_XYZV();
	void SetCharaLine(CCharaLine* pCL);
	int FeedBack(SFlightStatus fst);
	int FeedBack(double* dFB);
	int Output(SControlVolumes& Outputs);
	int Output(double* pOutputs);
	int Input(double* pInputs);
	CDIController();
	CDIController(CGeneralModel Model);
	virtual ~CDIController();

	//��m_cp�����µĴ�����������޸�
	//void BandwidthSet(double*);
};

#endif // !defined(AFX_DICONTROLLER_H__FFFF2C75_CA62_463A_A9E1_EE86740D174D__INCLUDED_)













