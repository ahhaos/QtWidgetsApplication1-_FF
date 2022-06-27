// CloseLoopModel.h: interface for the CCloseLoopModel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLOSELOOPMODEL_H__8250A6F3_77B1_4199_B9D0_D621A0E1C978__INCLUDED_)
#define AFX_CLOSELOOPMODEL_H__8250A6F3_77B1_4199_B9D0_D621A0E1C978__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DIController.h"
#include "FlightSimulation.h"
#include "CLchazhi.h"

class CCloseLoopModel
{
public:
	CCLchazhi m_cl;
	CDIController m_ctler;  //控制器
	CFlightSimulation m_mdl;
	double m_ctl[10];
	double m_dT;
public:

	SFlightStatus m_fst;
	SControlVolumes m_cv;
public:
	void initState();
	void Input_Hc(double hc);
	void Input_Kc(double khc);
	void Input_Vc(double vc);
	void Input_Attitude(double dpsi, double dtheta, double dphi);
	void GetControlVolumes(double* pcv);
	void SetStaticParams(double* psp);
	void GetStaticParams(double* psp);
	void SetFlightStatus(double* pfst);
	void SetT(double dT);
	double GetT();
	void GetControlStatus(double* pfst);
	void GetFlightStatus(double* pfst);
	void Input_VKH(double vc, double khc, double hc);
	void Input_DVKG(double dvc, double dkhc, double dhc);

	void Input_XYZ(double xc, double yc, double zc);       //给定x,y,z
	void Input_XYZ_V(double xc, double yc, double zc,double V);       //给定x,y,z
	void Input_Manual(double aileron, double elevator, double rudder,double throttle);
	void Follow(double x, double y, double z, double m_ship_dH, double m_ship_p, double m_ship_q/*,double m_shiptail_Vx,double m_shiptail_Vy,double m_shiptail_Vz*/);
	int Update();
	int Update_Manual();
	int Update(double x, double y, double z, double m_ship_dH, double m_ship_p, double m_ship_q/*,double m_shiptail_Vx,double m_shiptail_Vy,double m_shiptail_Vz*/);

	void Level();
	CCloseLoopModel();
	virtual ~CCloseLoopModel();

private:
	//bool m_bfollow;
};

#endif // !defined(AFX_CLOSELOOPMODEL_H__8250A6F3_77B1_4199_B9D0_D621A0E1C978__INCLUDED_)












