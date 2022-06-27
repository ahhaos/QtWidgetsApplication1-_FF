

// FlightSimulation.h: interface for the CFlightSimulation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLIGHTSIMULATION_H__12D72E35_F7DA_4CDC_B2F4_55DBCE324E59__INCLUDED_)
#define AFX_FLIGHTSIMULATION_H__12D72E35_F7DA_4CDC_B2F4_55DBCE324E59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GeneralDefinitions.h"

class CFlightSimulation : public CGeneralModel
{
	//CGeneralModel�Ĺ������������Ե���CGeneralModel���protect��public�ĳ�Ա�����ͳ�Ա������
	//����Լ���Ҫ�ĳ�Ա�����ͳ�Ա������
public:
	int StateDifferential(SFlightStatus& Status_d);
	int Update();//����
//	int Input(SControlVolumes cs);
	CFlightSimulation();
	virtual ~CFlightSimulation();
	att m_att;
	att l_att;
	Vel l_vel;
};

#endif // !defined(AFX_FLIGHTSIMULATION_H__12D72E35_F7DA_4CDC_B2F4_55DBCE324E59__INCLUDED_)



