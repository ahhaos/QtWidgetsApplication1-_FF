// FlightSimulation.cpp: implementation of the CFlightSimulation class.
//
//////////////////////////////////////////////////////////////////////


#include "FlightSimulation.h"
#include <math.h>
#include "../global.h"
#include <QDebug>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFlightSimulation::CFlightSimulation()
{
	//	FILE *fp=fopen("debug.txt","w");
}

CFlightSimulation::~CFlightSimulation()
{

}

/*int CFlightSimulation::Input(SControlVolumes cs)
{
	SControlVolumes::operator =(cs);
	return 0;
}*/

int CFlightSimulation::Update()
{
	//这里添加代码，参考fcnModel.m
	//前缀delta和推力的参数在m_Control里面
	//特性线使用方法,如fcnModel.m中读取升力系数interp1(al,C_L_al,alpha)
	//在这里表示成(*m_pCL)(m_pCL->C_L_al, alpha)

	/*if(m_dZ <= 0.1)
	{
		ForMatWing();
		m_Vy = 0;
		m_Vz = 0;
		m_Vx = m_dV * cos(m_dGama) * cos(m_dChi);
		m_dV = sqrt(m_Vx*m_Vx);
	}*/
	//if (m_dZ >= 0.1)			//解决飞机的东北天坐标系不能为负的情况
	if (true)
	{
		SFlightStatus fs_d;
		att m_att;
		att l_att;

		l_att.dtheta = m_att.dtheta;
		l_att.dphi = m_att.dphi;
		l_att.dpsi = m_att.dpsi;

		StateDifferential(fs_d);//求状态微分
		fs_d = (SFlightStatus::operator+(fs_d * m_dT));//积分
		SFlightStatus::operator=(fs_d);//将结果赋到SFlightStatus
		//if(m_dZ <= 0.1){ForMatWing();}

		//求x,y,z方向速度
		m_Vx = m_dV * cos(m_dGama) * cos(m_dChi);
		m_Vy = m_dV * cos(m_dGama) * sin(m_dChi);
		m_Vz = m_dV * sin(m_dGama);
		



		//m_dV = sqrt(m_Vx* m_Vx + m_Vy * m_Vy + m_Vz* m_Vz);
		//m_dGama = asin(m_Vz / m_dV);
		//m_dChi = atan(m_Vy / m_Vx);


		//三个欧拉角速率
		m_att.dtheta = m_dq * cos(m_dphi) - m_dr * sin(m_dphi);						//pitch
		m_att.dphi = m_dp + tan(m_dtheta) * (m_dq * sin(m_dphi) + m_dr * cos(m_dphi));	//roll
		m_att.dpsi = (m_dq * sin(m_dphi) + m_dr * cos(m_dphi)) / cos(m_dtheta);			//yaw
		m_dVtheta = m_att.dtheta;//m_dtheta为俯仰角速率
		m_dVphi = m_att.dphi; //m_dphi为滚转角速率
		m_dVpsi = m_att.dpsi; //m_dpsi为偏航角速率

		//求角加速度
		m_att.ddtheta = (m_att.dtheta - l_att.dtheta) / data_time;
		m_att.ddphi = (m_att.dphi - l_att.dphi) / data_time;
		m_att.ddpsi = (m_att.dpsi - l_att.dpsi) / data_time;
		m_Accq = m_att.ddtheta;
		m_Accp = m_att.ddphi;
		m_Accr = m_att.ddpsi;

		if (m_dMu > PI)
			m_dMu -= ((int)(m_dMu / (PI * 2) + 0.5)) * PI * 2;
		else if (m_dMu < -PI)
			m_dMu -= ((int)(m_dMu / (PI * 2) - 0.5)) * PI * 2;

		if (m_dChi > PI)
			m_dChi -= ((int)(m_dChi / (PI * 2) + 0.5)) * PI * 2;
		else if (m_dChi < -PI)
			m_dChi -= ((int)(m_dChi / (PI * 2) - 0.5)) * PI * 2;

		int count = 1000;
		while (count--)
		{
			if (m_dGama > PI / 2)
			{
				if (m_dChi > 0) m_dChi -= PI;
				else if (m_dChi < 0) m_dChi += PI;
				if (m_dMu > 0) m_dMu -= PI;
				else if (m_dMu < 0) m_dMu += PI;
				m_dGama = PI - m_dGama;
				continue;
			}
			if (m_dGama < -PI / 2)
			{
				if (m_dChi > 0) m_dChi -= PI;
				else if (m_dChi < 0) m_dChi += PI;
				if (m_dMu > 0) m_dMu -= PI;
				else if (m_dMu < 0) m_dMu += PI;
				m_dGama = -PI - m_dGama;
				continue;
			}
			break;
		}
		if (m_dV < 0.1)
			m_dV = 0.01;
		return 0;
	}
	else
	{
		m_Vx -= 1.5;
		m_Vy = 0;
		m_Vz = 0;

		m_dV = sqrt(m_Vx * m_Vx);

		m_dX += m_dV / (1000 / data_time);
		m_dY = 0;
		m_dZ = 0;

		m_dChi = 0;
		m_dGama = 0;

		m_dAlpha = 0;
		m_dBeta = 0;
		m_dMu = 0;

		m_dp = 0;
		m_dq = 0;
		m_dr = 0;
		return 0;
	}

	//StateDifferential(fs_d);//求状态微分
	//fs_d=(SFlightStatus::operator+(fs_d*m_dT));//积分
	//SFlightStatus::operator=(fs_d);//将结果赋到SFlightStatus
	////if(m_dZ <= 0.1){ForMatWing();}
	////求x,y,z方向速度
	//m_Vx = m_dV * cos(m_dGama) * cos(m_dChi);
	//m_Vy = m_dV * cos(m_dGama) * sin(m_dChi);
	//m_Vz = m_dV * sin(m_dGama);

	//if(m_dMu>PI)
	//	m_dMu -= ((int)(m_dMu/(PI*2)+0.5))*PI * 2;
	//else if(m_dMu<-PI)
	//	m_dMu -= ((int)(m_dMu/(PI*2)-0.5))*PI * 2;

	//if(m_dChi>PI)
	//	m_dChi -= ((int)(m_dChi/(PI*2 )+0.5))*PI * 2;
	//else if(m_dChi<-PI)
	//	m_dChi -= ((int)(m_dChi/(PI*2 )-0.5))*PI * 2;

	//int count=1000;
	//while(count--)
	//{
	//	if(m_dGama > PI/2)
	//	{
	//		if(m_dChi>0) m_dChi-=PI;
	//		else if(m_dChi<0) m_dChi+=PI;
	//		if(m_dMu>0) m_dMu-=PI;
	//		else if(m_dMu<0) m_dMu+=PI;
	//		m_dGama = PI-m_dGama;
	//		continue;
	//	}
	//	if(m_dGama < -PI/2)
	//	{
	//		if(m_dChi>0) m_dChi-=PI;
	//		else if(m_dChi<0) m_dChi+=PI;
	//		if(m_dMu>0) m_dMu-=PI;
	//		else if(m_dMu<0) m_dMu+=PI;
	//		m_dGama = -PI-m_dGama;
	//		continue;
	//	}
	//	break;
	//}
	//if(m_dV<0.1) 
	//	m_dV=0.1;
	//return 0;
}

//含姿态角
int CFlightSimulation::StateDifferential(SFlightStatus& Status_d)
{
	/*if(m_dY <= 0.1)
		ForMatWing();*/
	double q_;
	double l, m, n;//滚转力矩、俯仰力矩、偏航力矩
	double L, D, Y;//升力、阻力、侧力

	double pic = PI / 180;
	double Tx = m_dThrustc;
	double Ty = m_dThrustc * m_ddeltay * pic;
	double Tz = m_dThrustc * m_ddeltaz * pic;
	double mT = m_dxT * Tz;
	double nT = -m_dxT * Ty;

	double temp_Vx = (data_shiptail_u + data_Wind_Vx) * (data_time / 1000);
	double temp_Vy = (data_shiptail_v + data_Wind_Vy) * (data_time / 1000);
	double temp_Vz = (data_shiptail_w + data_Wind_Vz) * (data_time / 1000);//  / (data_time / 1000);

	//m_dV = sqrt(m_Vx * m_Vx + m_Vy * m_Vy + m_Vz * m_Vz);
	//m_dGama = asin(m_Vz / m_dV);
	//m_dChi = atan(m_Vy / m_Vx);


	q_ = 0.5 * m_dRho * m_dV * m_dV;

	//求滚转力矩
	l = q_ * m_dS * m_db * ((*m_pCL)(m_pCL->C_lbeta, m_dAlpha) * m_dBeta +
		(*m_pCL)(m_pCL->C_lp, m_dAlpha) * m_dp * m_db / (2 * m_dV) +
		(*m_pCL)(m_pCL->C_lr, m_dAlpha) * m_dr * m_db / (2 * m_dV) +//mark
		(*m_pCL)(m_pCL->C_ldeltaa, m_dAlpha) * m_ddeltaa +
		(*m_pCL)(m_pCL->C_ldeltar, m_dAlpha) * m_ddeltar);


	//求俯仰力矩
/*	m=q_*m_dS*(m_dC_/*该项是什么//)((*m_pCL)(m_pCL->C_mo, m_dAlpha)+
		(-3)*m_dq*m_dC_/(2*m_dV)+(*m_pCL)(m_pCL->C_mdeltac, m_dAlpha)*
		(m_ddeltac-(*m_pCL)(m_pCL->delta_c0, m_dAlpha))+
		(*m_pCL)(m_pCL->C_mo, m_dAlpha)*(m_dAlpha-Alpha0));*///mark
	m = q_ * m_dS * m_dC_ * ((*m_pCL)(m_pCL->C_mo, m_dAlpha)
		- 3 * m_dq * m_dC_ / (2 * m_dV) + (*m_pCL)(m_pCL->C_mdeltac, m_dAlpha)
		* (m_ddeltac - (*m_pCL)(m_pCL->delta_c0, m_dAlpha)));

	//求偏航力矩
	n = q_ * m_dS * m_db * ((*m_pCL)(m_pCL->C_nbeta, m_dAlpha) * m_dBeta +
		(*m_pCL)(m_pCL->C_np, m_dAlpha) * m_dp * m_db / (2 * m_dV) +
		(*m_pCL)(m_pCL->C_nr, m_dAlpha) * m_dr * m_db / (2 * m_dV) +
		(*m_pCL)(m_pCL->C_ndeltaa, m_dAlpha) * m_ddeltaa +
		(*m_pCL)(m_pCL->C_ndeltar, m_dAlpha) * m_ddeltar);

	//求升力
	L = q_ * m_dS * ((*m_pCL)(m_pCL->C_L, m_dAlpha) +
		(*m_pCL)(m_pCL->C_ldeltac, m_dAlpha) * (m_ddeltac -
			(*m_pCL)(m_pCL->delta_c0, m_dAlpha)));
	double c_l = ((*m_pCL)(m_pCL->C_L, m_dAlpha) +
		(*m_pCL)(m_pCL->C_ldeltac, m_dAlpha) * (m_ddeltac -
			(*m_pCL)(m_pCL->delta_c0, m_dAlpha)));

	//求阻力
	D = q_ * m_dS * (*m_pCL)(m_pCL->C_D, m_dAlpha);
	//qDebug() << "D" << D;
	//求侧力
	Y = q_ * m_dS * ((-1) * m_dBeta + (*m_pCL)(m_pCL->C_ydeltar, m_dAlpha) * m_ddeltar);

	//6自由度12状态飞机方程
	Status_d.m_dX = m_dV * cos(m_dGama) * cos(m_dChi);

	Status_d.m_dY = m_dV * cos(m_dGama) * sin(m_dChi);

	Status_d.m_dZ = -m_dV * sin(m_dGama);

	//
	double temp = sqrt(temp_Vx * temp_Vx + temp_Vy * temp_Vy + temp_Vz * temp_Vz);//v

	//Status_d.m_dV = (1.0 / m_dM) * (-D + Y * sin(m_dBeta) - m_dM * m_dg * sin(m_dGama) +
	//	Tx * cos(m_dBeta) * cos(m_dAlpha) + Ty * sin(m_dBeta) + Tz * cos(m_dBeta) * sin(m_dAlpha)) +
	//	(temp_Vx + temp_Vy + temp_Vz) / temp;// *(data_time / 1000);// +0.04330127018922193233818615853765;// 0.2165063509461;

	Status_d.m_dV = (1.0 / m_dM) * (-D + Y * sin(m_dBeta) - m_dM * m_dg * sin(m_dGama) +
		Tx * cos(m_dBeta) * cos(m_dAlpha) + Ty * sin(m_dBeta) + Tz * cos(m_dBeta) * sin(m_dAlpha)) - temp_Vx;

	//Status_d.m_dChi = (1.0 / (m_dM * m_dV * cos(m_dGama))) *
	//	(L * sin(m_dMu) + Y * cos(m_dMu) * cos(m_dBeta) +
	//		Tz * (sin(m_dMu) * sin(m_dAlpha) - cos(m_dMu) * cos(m_dBeta) * cos(m_dAlpha))//;//mark
	//		+ Ty * cos(m_dMu) * cos(m_dBeta)
	//		- Tx * (cos(m_dMu) * sin(m_dBeta) * sin(m_dAlpha) + sin(m_dMu) * cos(m_dAlpha))) +
	//		(temp_Vx - temp_Vy) / (temp_Vx * temp_Vx + temp_Vy * temp_Vy) * (data_time / 1000);// *(data_time / 1000); //+0.0125;//` 3.1415926535897932384626 / 4;

	Status_d.m_dChi = (1.0 / (m_dM * m_dV * cos(m_dGama))) *
		(L * sin(m_dMu) + Y * cos(m_dMu) * cos(m_dBeta) +
			Tz * (sin(m_dMu) * sin(m_dAlpha) - cos(m_dMu) * cos(m_dBeta) * cos(m_dAlpha))//;//mark
			+ Ty * cos(m_dMu) * cos(m_dBeta)
			- Tx * (cos(m_dMu) * sin(m_dBeta) * sin(m_dAlpha) + sin(m_dMu) * cos(m_dAlpha)));

	/*	Status_d.m_dGama =(1.0/(m_dM*m_dV))*(L-m_dM*m_dg *cos(m_dGama)+
			T*(cos(m_dMu)*sin(m_dAlpha)+sin(m_dMu)*sin(m_dBeta)*cos(m_dAlpha)));*/
			//Status_d.m_dGama = (1.0 / (m_dM * m_dV)) * (L * cos(m_dMu) - Y * sin(m_dMu) * cos(m_dBeta) - m_dM * m_dg * cos(m_dGama)
			//	+ Tx * (sin(m_dMu) * sin(m_dBeta) * cos(m_dAlpha) + cos(m_dMu) * sin(m_dAlpha))
			//	- Ty * sin(m_dMu) * cos(m_dBeta)
			//	+ Tz * (sin(m_dMu) * sin(m_dBeta) * sin(m_dAlpha) - cos(m_dMu) * cos(m_dAlpha))) +
			//	(temp - temp_Vz) / sqrt(temp * temp * temp * temp - temp_Vz * temp_Vz * temp * temp) * (data_time / 1000);// *(data_time / 1000);// +0.03061862178478972622746605093382;// 0.6154797087;

	Status_d.m_dGama = (1.0 / (m_dM * m_dV)) * (L * cos(m_dMu) - Y * sin(m_dMu) * cos(m_dBeta) - m_dM * m_dg * cos(m_dGama)
		+ Tx * (sin(m_dMu) * sin(m_dBeta) * cos(m_dAlpha) + cos(m_dMu) * sin(m_dAlpha))
		- Ty * sin(m_dMu) * cos(m_dBeta)
		+ Tz * (sin(m_dMu) * sin(m_dBeta) * sin(m_dAlpha) - cos(m_dMu) * cos(m_dAlpha)));

	Status_d.m_dAlpha = m_dq - tan(m_dBeta) * (cos(m_dAlpha) * m_dp +
		sin(m_dAlpha) * m_dr) + (-L + m_dM * m_dg * cos(m_dGama) *
			cos(m_dMu) - Tx * sin(m_dAlpha)) / (m_dM * m_dV * cos(m_dBeta)) - temp_Vz / m_dV;

	Status_d.m_dBeta = -m_dr * cos(m_dAlpha) + m_dp * sin(m_dAlpha) +
		(Y * cos(m_dBeta) + m_dM * m_dg * cos(m_dGama) * sin(m_dMu) -
			Tx * sin(m_dBeta) * cos(m_dAlpha)) / (m_dM * m_dV) - temp_Vy / m_dV;

	/*	Status_d.m_dMu=(cos(m_dAlpha)*m_dp+sin(m_dAlpha)*m_dr)/cos(m_dBeta)+
			L*(tan(m_dGama)*sin(m_dMu)+tan(m_dBeta))/(m_dM*m_dV)-
			m_dg*cos(m_dGama)*cos(m_dMu)*tan(m_dBeta)/m_dV+
			T*sin(m_dAlpha)*(tan(m_dGama)*sin(m_dMu)+tan(m_dBeta))/(m_dM*Status_d.m_dV)-
			T*cos(m_dAlpha)*(tan(m_dGama)*cos(m_dMu)*sin(m_dBeta))/(m_dM*Status_d.m_dV);*/
	Status_d.m_dMu = (cos(m_dAlpha) * m_dp + sin(m_dAlpha) * m_dr) / cos(m_dBeta)
		- m_dg / m_dV * cos(m_dGama) * cos(m_dMu) * tan(m_dBeta)
		+ 1.0 / m_dM / m_dV * (L * (tan(m_dGama) * sin(m_dMu) + tan(m_dBeta))
			+ (Y + Ty) * tan(m_dGama) * cos(m_dMu) * cos(m_dBeta)
			+ (Tx * sin(m_dAlpha) - Tz * cos(m_dAlpha)) * (tan(m_dGama) * sin(m_dMu) + tan(m_dBeta))
			- (Tx * cos(m_dAlpha) + Tz * sin(m_dAlpha)) * tan(m_dGama) * cos(m_dMu) * sin(m_dBeta));

	Status_d.m_dp = (m_dIz * l + m_dIxz * (n + nT) + m_dIxz * (m_dIx - m_dIy + m_dIz) * m_dp * m_dq +
		(m_dIz * (m_dIy - m_dIz) - m_dIxz * m_dIxz) * m_dq * m_dr) / (m_dIx * m_dIz - m_dIxz * m_dIxz);

	Status_d.m_dq = (1.0 / m_dIy) * (m + mT + (m_dIz - m_dIx) * m_dp * m_dr + m_dIxz * (m_dr * m_dr - m_dp * m_dp));

	Status_d.m_dr = (m_dIxz * l + m_dIx * (n + nT) + (m_dIx * (m_dIx - m_dIy) + m_dIxz * m_dIxz) * m_dp * m_dq -
		m_dIxz * (m_dIx - m_dIy + m_dIz) * m_dq * m_dr) / (m_dIx * m_dIz - m_dIxz * m_dIxz);


	/*Status_d.m_dtheta = Status_d.m_dq * cos(Status_d.m_dphi) - Status_d.m_dr * sin(Status_d.m_dphi);
	Status_d.m_dphi = Status_d.m_dp + tan(Status_d.m_dtheta)*(Status_d.m_dq * sin(Status_d.m_dphi) + Status_d.m_dr * cos(Status_d.m_dphi));
	Status_d.m_dpsi = (Status_d.m_dq * sin(Status_d.m_dphi) + Status_d.m_dr * cos(Status_d.m_dphi))/cos(Status_d.m_dtheta);*/

	//phi_dot     = p_body+tan(theta)*(q_body*sin(phi)+r_body*cos(phi));
	//theta_dot   = q_body*cos(phi)-r_body*sin(phi);
	//psi_dot     = (q_body*sin(phi)+r_body*cos(phi))/cos(theta);
	//姿态角求解

	//Status_d.m_dpsi = (m_dr)/cos(0.18);			//yaw
	return 0;
}
