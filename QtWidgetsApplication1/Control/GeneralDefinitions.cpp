#include "GeneralDefinitions.h"
#include "math.h"
#include "../global.h"
#include <cstring>
////////////////////////////////////////
//SStaticParams/////////////////////////
////////////////////////////////////////
SStaticParams::SStaticParams()
{
	SStaticParams(data_model_dg, data_model_dRho, data_model_dM, data_model_dS, data_model_db, data_model_dC_,
		data_model_da_max, data_model_dr_max, data_model_dc_max, data_model_dy_max, data_model_dz_max,
		data_model_dxT, data_model_dIx, data_model_dIy, data_model_dIz, data_model_dIxz);
}
SStaticParams::SStaticParams(double dg, double dRho, double dM, double dS, double db, double dC_,
	double da_max, double dr_max, double dc_max, double dy_max, double dz_max,
	double dxT, double dIx, double dIy, double dIz, double dIxz)
{
	m_dg = dg;
	m_dRho = dRho;

	m_dM = dM;
	m_dS = dS;
	m_db = db;
	m_dC_ = dC_;
	m_da_max = da_max;
	m_dr_max = dr_max;
	m_dc_max = dc_max;
	m_dy_max = dy_max;
	m_dz_max = dz_max;

	m_dxT = dxT;
	m_dIx = dIx;
	m_dIy = dIy;
	m_dIz = dIz;
	m_dIxz = dIxz;
}
SStaticParams SStaticParams::operator =(SStaticParams sp)
{
	m_dg = sp.m_dg;
	m_dRho = sp.m_dRho;

	m_dM = sp.m_dM;
	m_dS = sp.m_dS;
	m_db = sp.m_db;
	m_dC_ = sp.m_dC_;
	m_dxT = sp.m_dxT;
	m_da_max = sp.m_da_max;
	m_dr_max = sp.m_dr_max;
	m_dc_max = sp.m_dc_max;
	m_dy_max = sp.m_dy_max;
	m_dz_max = sp.m_dz_max;


	m_dIx = sp.m_dIx;
	m_dIy = sp.m_dIy;
	m_dIz = sp.m_dIz;
	m_dIxz = sp.m_dIxz;
	return *this;
}
/*//////////////////////////////////
//SVector/////////////////////////
//////////////////////////////////
SVector::SVector()
{
	m_dX=m_dY=m_dZ=0;
}
SVector::SVector(double dX,double dY,double dZ)
{
	m_dX=dX;
	m_dY=dY;
	m_dZ=dZ;
}
SVector SVector::operator=(SVector vec)
{
	m_dX=vec.m_dX;
	m_dY=vec.m_dY;
	m_dZ=vec.m_dZ;
	return *this;
}
SVector SVector::operator+(SVector vec)
{
	return SVector(	m_dX + vec.m_dX,
					m_dY + vec.m_dY,
					m_dZ + vec.m_dZ	);
}
SVector SVector::operator-(SVector vec)
{
	return SVector(	m_dX - vec.m_dX,
					m_dY - vec.m_dY,
					m_dZ - vec.m_dZ	);
}
SVector SVector::operator*(double k)
{
	return SVector(	m_dX * k,
					m_dY * k,
					m_dZ * k	);
}
//////////////////////////////////
//SFlightStatus///////////////////
//////////////////////////////////*/

att::att()
{
	//姿态角速率
	dtheta = 0;
	dphi = 0;
	dpsi = 0;
	//姿态角加速度
	ddtheta = 0;
	ddphi = 0;
	ddpsi = 0;
}
att::att(double adtheta, double adphi, double adpsi,
	double addtheta, double addphi, double addpsi)
{
	//姿态角速率
	dtheta = adtheta;
	dphi = adphi;
	dpsi = adpsi;
	//姿态角加速度
	ddtheta = addtheta;
	ddphi = addphi;
	ddpsi = addpsi;
}

Vel::Vel()
{
	Velx = 0;
	Vely = 0;
	Velz = 0;
}

Vel::Vel(double u, double v, double w)
{
	Velx = u;
	Vely = v;
	Velz = w;
}

comb::comb()
{
	m_comb_deltaX = 0;
	m_comb_deltaY = 0;
	m_comb_deltaZ = 0;
	m_comb_valid = 1;
}

comb::comb(double deltaX, double deltaY, double deltaZ, int valid)
{
	m_comb_deltaX = deltaX;
	m_comb_deltaY = deltaY;
	m_comb_deltaZ = deltaZ;
	m_comb_valid = valid;
}



//Wind::Wind()
//{
//	m_Wind_V = 0;			//风速合速度
//	m_Wind_anghor = 0;		//风速水平角
//	m_Wind_angver = 0;		//风速垂直角
//	m_Wind_Vx = 0;			//风速X轴分量
//	m_Wind_Vy = 0;			//风速Y轴分量
//	m_Wind_Vz = 0;			//风速Z轴分量
//}
//
//Wind::Wind(	double V, double anghor, double angver,
//			double Vx, double Vy, double Vz)
//{
//	m_Wind_V = V;			//风速合速度
//	m_Wind_anghor = anghor;	//风速水平角
//	m_Wind_angver = angver;	//风速垂直角
//	m_Wind_Vx = Vx;			//风速X轴分量
//	m_Wind_Vy = Vy;			//风速Y轴分量
//	m_Wind_Vz = Vz;			//风速Z轴分量
//}

SFlightStatus::SFlightStatus()
{
	m_dX = 0;
	m_dY = 0;
	m_dZ = 0;
	m_dV = 0;
	m_dChi = 0;
	m_dGama = 0;
	m_dAlpha = 0;
	m_dBeta = 0;
	m_dMu = 0;
	m_dp = 0;
	m_dq = 0;
	m_dr = 0;

	m_dtheta = 0;		//俯仰角
	m_dpsi = 0;			//偏航角
	m_dphi = 0;			//滚转角

	m_Vx = 0;			//x方向速度
	m_Vy = 0;			//y方向速度
	m_Vz = 0;			//z方向速度

	m_Accx = 0;			//x方向线加速度
	m_Accy = 0;			//y方向线加速度
	m_Accz = 0;			//z方向线加速度

	m_dVtheta = 0;
	m_dVphi = 0;
	m_dVpsi = 0;

	m_Accp = 0;			//滚转角加速度
	m_Accq = 0;			//俯仰角加速度
	m_Accr = 0;			//偏航角加速度
}
SFlightStatus::SFlightStatus(double dX, double dY, double dZ,
	double dV, double dKh, double dGama,
	double dAlpha, double dBeta, double dMu,
	double dp, double dq, double dr,
	double dtheta, double dpsi, double dphi,
	double dVtheta, double dVphi, double dVpsi,
	double Vx, double Vy, double Vz,
	double Accx, double Accy, double Accz,
	double Accp, double Accq, double Accr)
{
	m_dX = dX;
	m_dY = dY;
	m_dZ = dZ;
	m_dV = dV;
	m_dChi = dKh;
	m_dGama = dGama;
	m_dAlpha = dAlpha;
	m_dBeta = dBeta;
	m_dMu = dMu;
	m_dp = dp;
	m_dq = dq;
	m_dr = dr;
	m_dtheta = dtheta;
	m_dpsi = dpsi;
	m_dphi = dphi;
	m_dVtheta = dVtheta;
	m_dVphi = dVphi;
	m_dVpsi = dVpsi;
	m_Vx = Vx;
	m_Vy = Vy;
	m_Vz = Vz;
	m_Accx = Accx;
	m_Accy = Accy;
	m_Accz = Accz;
	m_Accp = Accp;
	m_Accq = Accq;
	m_Accr = Accr;
}
SFlightStatus SFlightStatus::operator =(SFlightStatus st)
{
	m_dX = st.m_dX;
	m_dY = st.m_dY;
	m_dZ = st.m_dZ;
	m_dV = st.m_dV;
	m_dChi = st.m_dChi;
	m_dGama = st.m_dGama;
	m_dAlpha = st.m_dAlpha;
	m_dBeta = st.m_dBeta;
	m_dMu = st.m_dMu;
	m_dp = st.m_dp;
	m_dq = st.m_dq;
	m_dr = st.m_dr;
	m_dtheta = st.m_dtheta;
	m_dpsi = st.m_dpsi;
	m_dphi = st.m_dphi;

	m_dVtheta = st.m_dVtheta;
	m_dVphi = st.m_dVphi;
	m_dVpsi = st.m_dVpsi;

	m_Vx = st.m_Vx;
	m_Vy = st.m_Vy;
	m_Vz = st.m_Vz;

	m_Accx = st.m_Accx;
	m_Accy = st.m_Accy;
	m_Accz = st.m_Accz;

	m_Accp = st.m_Accp;
	m_Accq = st.m_Accq;
	m_Accr = st.m_Accr;
	return *this;
}
SFlightStatus SFlightStatus::operator *(double k)
{
	return SFlightStatus(k * m_dX, k * m_dY, k * m_dZ,
		k * m_dV, k * m_dChi, k * m_dGama,
		k * m_dAlpha, k * m_dBeta, k * m_dMu,
		k * m_dp, k * m_dq, k * m_dr,
		k * m_dtheta, k * m_dpsi, k * m_dphi,
		k * m_dVtheta, k * m_dVpsi, k * m_dVphi,
		k * m_Vx, k * m_Vy, k * m_Vz,
		k * m_Accx, k * m_Accy, k * m_Accz,
		k * m_Accp, k * m_Accq, k * m_Accr);
}
SFlightStatus SFlightStatus::operator +(SFlightStatus fs)   //含姿态角
{
	return SFlightStatus(m_dX + fs.m_dX, m_dY + fs.m_dY, m_dZ + fs.m_dZ,
		m_dV + fs.m_dV, m_dChi + fs.m_dChi, m_dGama + fs.m_dGama,
		m_dAlpha + fs.m_dAlpha, m_dBeta + fs.m_dBeta, m_dMu + fs.m_dMu,
		m_dp + fs.m_dp, m_dq + fs.m_dq, m_dr + fs.m_dr,
		m_dtheta + fs.m_dtheta, m_dpsi + fs.m_dpsi, m_dphi + fs.m_dphi,
		m_dVtheta + fs.m_dVtheta, m_dVpsi + fs.m_dVpsi, m_dVphi + fs.m_dVphi,
		m_Vx + fs.m_Vx, m_Vy + fs.m_Vy, m_Vz + fs.m_Vz,
		m_Accx + fs.m_Accx, m_Accy + fs.m_Accy, m_Accz + fs.m_Accz,
		m_Accp + fs.m_Accp, m_Accq + fs.m_Accq, m_Accr + fs.m_Accr);
}
SFlightStatus SFlightStatus::operator -(SFlightStatus fs)
{
	return SFlightStatus(m_dX - fs.m_dX, m_dY - fs.m_dY, m_dZ - fs.m_dZ,
		m_dV - fs.m_dV, m_dChi - fs.m_dChi, m_dGama - fs.m_dGama,
		m_dAlpha - fs.m_dAlpha, m_dBeta - fs.m_dBeta, m_dMu - fs.m_dMu,
		m_dp - fs.m_dp, m_dq - fs.m_dq, m_dr - fs.m_dr,
		m_dtheta - fs.m_dtheta, m_dpsi - fs.m_dpsi, m_dphi - fs.m_dphi,
		m_dVtheta - fs.m_dVtheta, m_dVpsi - fs.m_dVpsi, m_dVphi - fs.m_dVphi,
		m_Vx - fs.m_Vx, m_Vy - fs.m_Vy, m_Vz - fs.m_Vz,
		m_Accx - fs.m_Accx, m_Accy - fs.m_Accy, m_Accz - fs.m_Accz,
		m_Accp - fs.m_Accp, m_Accq - fs.m_Accq, m_Accr - fs.m_Accr);
}
//////////////////////////////////
//SControlVolumes/////////////////
//////////////////////////////////
SControlVolumes::SControlVolumes()
{
	m_ddeltaa = data_model_ddeltaa;
	m_ddeltac = data_model_ddeltac;
	m_ddeltar = data_model_ddeltar;
	m_ddeltay = data_model_ddeltay;
	m_ddeltaz = data_model_ddeltaz;
	m_dThrustc = data_model_dThrust;
}
SControlVolumes::SControlVolumes(double ddeltaa, double ddeltac, double ddeltar, double ddeltay, double ddeltaz, double dThrustc)
{
	m_ddeltaa = ddeltaa;
	m_ddeltac = ddeltac;
	m_ddeltar = ddeltar;
	m_ddeltay = ddeltay;
	m_ddeltaz = ddeltaz;
	m_dThrustc = dThrustc;
}
SControlVolumes SControlVolumes::operator =(SControlVolumes cs)
{
	m_ddeltaa = cs.m_ddeltaa;
	m_ddeltac = cs.m_ddeltac;
	m_ddeltar = cs.m_ddeltar;
	m_ddeltay = cs.m_ddeltay;
	m_ddeltaz = cs.m_ddeltaz;
	m_dThrustc = cs.m_dThrustc;
	return *this;
}
SControlVolumes SControlVolumes::operator +(SControlVolumes cs)
{
	return SControlVolumes(m_ddeltaa + cs.m_ddeltaa,
		m_ddeltac + cs.m_ddeltac,
		m_ddeltar + cs.m_ddeltar,
		m_ddeltay + cs.m_ddeltay,
		m_ddeltaz + cs.m_ddeltaz,
		m_dThrustc + cs.m_dThrustc);
}

SControlVolumes SControlVolumes::operator -(SControlVolumes cs)
{
	return SControlVolumes(m_ddeltaa - cs.m_ddeltaa,
		m_ddeltac - cs.m_ddeltac,
		m_ddeltar - cs.m_ddeltar,
		m_ddeltay - cs.m_ddeltay,
		m_ddeltaz - cs.m_ddeltaz,
		m_dThrustc - cs.m_dThrustc);
}
//////////////////////////////////
//CCharaLine//////////////////////
//////////////////////////////////
CCharaLine::CCharaLine() : C_L(0),
C_D(1),
C_ldeltaa(2),
C_ldeltac(3),
C_ldeltar(4),
C_lp(5),
C_lr(6),
C_lbeta(7),
C_mo(8),
C_mdeltac(9),
C_mq(10),
C_ndeltaa(11),
C_ndeltar(12),
C_np(13),
C_nr(14),
C_nbeta(15),
C_ydeltaa(16),
C_ydeltar(17),
C_ybeta(18),
delta_c0(19)
{
}
double CCharaLine::operator()(int iSelect, double x)
{
	return 0.0;
}
bool CCharaLine::ChenckAlpha(double alpha, double& AvailableAlpha)
{
	return true;
}
//////////////////////////////////
//CGeneralModel///////////////////
//////////////////////////////////
CGeneralModel::CGeneralModel()
{
	m_pCL = 0;
	m_dT = 0;
}
CGeneralModel::CGeneralModel(SStaticParams Static, SFlightStatus Status,
	SControlVolumes Control, CCharaLine* pCL, double dT)
{
	SStaticParams::operator =(Static);
	SFlightStatus::operator =(Status);
	SControlVolumes::operator=(Control);
	m_pCL = pCL;
	m_dT = dT;
}
CGeneralModel CGeneralModel::operator =(CGeneralModel Model)
{
	SStaticParams::operator =(Model);
	SFlightStatus::operator =(Model);
	SControlVolumes::operator=(Model);
	m_dT = Model.m_dT;		//仿真周期
	m_pCL = Model.m_pCL;	//一个指向特性线对象的指针

	return *this;
}
void CGeneralModel::SetCharaLine(CCharaLine* pCL)
{
	m_pCL = pCL;
}



void CGeneralModel::SetStaticParams(SStaticParams sp)
{
	SStaticParams::operator =(sp);
}

void CGeneralModel::SetFlightStatus(SFlightStatus fs)
{
	SFlightStatus::operator =(fs);
}

void CGeneralModel::SetControlVolumes(SControlVolumes cv)
{
	SControlVolumes::operator =(cv);
}

void CGeneralModel::GetControlVolumes(SControlVolumes& cv)
{
	cv = *this;
}

void CGeneralModel::GetFlightStatus(SFlightStatus& fs)
{
	fs = *this;
}

void CGeneralModel::GetStaticParams(SStaticParams& sp)
{
	sp = *this;
}

void CGeneralModel::SetT(double dT)
{
	m_dT = dT;
}

//DEL SFlightStatus SFlightStatus::GetFloatStatus()
//DEL {
//DEL 	SFlightStatus fs((float)(m_dX/KSCAlE),
//DEL 	(float)(m_dY/KSCAlE),
//DEL 	-(float)m_dZ/KSCAlE,
//DEL 	(float)m_dV,
//DEL 	m_dKh,
//DEL 	m_dGama,
//DEL 	m_dAlpha,
//DEL 	m_dBeta,
//DEL 	m_dMu,
//DEL 	m_dp,
//DEL 	m_dq,
//DEL 	m_dr);
//DEL 	return  fs;
//DEL }
SFlightStatusHL::SFlightStatusHL()
{
	m_dX = 0.0;		//地面坐标系X坐标(m)
	m_dY = 0.0;		//地面坐标系Y坐标(m)
	m_dZ = 0.0;		//地面坐标系Z坐标(m)
	m_dbu = 0.0;		//X方向速度(b:机身坐标系,m/s)
	m_dbv = 0.0;		//Y方向速度(b:机身坐标系,m/s)
	m_dbw = 0.0;		//Z方向速度(b:机身坐标系,m/s)
	m_dphi = 0.0;		//滚转角(rad)
	m_dtheta = 0.0;	//俯仰角(rad)
	m_dpsi = 0.0;		//偏航角(rad)
	m_dp = 0.0;		//滚转角(rad/s)
	m_dq = 0.0;		//俯仰角(rad/s)
	m_dr = 0.0;		//偏航角(rad/s)
}
SFlightStatusHL::SFlightStatusHL(double dX, double dY, double dZ,
	double dbu, double dbv, double dbw,
	double dtheta, double dpsi, double dphi,
	double dp, double dq, double dr)
{
	m_dX = dX;
	m_dY = dY;
	m_dZ = dZ;
	m_dbu = dbu;
	m_dbv = dbv;
	m_dbw = dbw;
	m_dpsi = dpsi;
	m_dtheta = dtheta;
	m_dphi = dphi;
	m_dp = dp;
	m_dq = dq;
	m_dr = dr;
}
SFlightStatusHL SFlightStatusHL::operator=(SFlightStatusHL state)
{
	memcpy(this, &state, sizeof(SFlightStatusHL));
	return *this;
}
SFlightStatusHL SFlightStatusHL::operator*(double k)
{
	return SFlightStatusHL(m_dX * k, m_dY * k, m_dZ * k,
		m_dbu * k, m_dbv * k, m_dbw * k,
		m_dphi * k, m_dtheta * k, m_dpsi * k,
		m_dp * k, m_dq * k, m_dr * k);
}

void SFlightStatusHL::InitStatus()
{
	m_dX = 0.0;		//地面坐标系X坐标(m)
	m_dY = 0.0;		//地面坐标系Y坐标(m)
	m_dZ = 0.0;		//地面坐标系Z坐标(m)
	m_dbu = 0.0;		//X方向速度(b:机身坐标系,m/s)
	m_dbv = 0.0;		//Y方向速度(b:机身坐标系,m/s)
	m_dbw = 0.0;		//Z方向速度(b:机身坐标系,m/s)
	m_dphi = 0.0;		//滚转角(rad)
	m_dtheta = 0.0;	//俯仰角(rad)
	m_dpsi = 0.0;		//偏航角(rad)
	m_dp = 0.0;		//滚转角(rad/s)
	m_dq = 0.0;		//俯仰角(rad/s)
	m_dr = 0.0;		//偏航角(rad/s)
}

void SFlightStatus::InitStatus()
{
	m_dX = 0;
	m_dY = 0;
	m_dZ = 0;
	m_dV = 0;
	m_dChi = 0;
	m_dGama = 0;
	m_dAlpha = 0;
	m_dBeta = 0;
	m_dMu = 0;
	m_dp = 0;
	m_dq = 0;
	m_dr = 0;
}

//////////////////////////////////
//SFlightAttitude/////////////////
//////////////////////////////////
SFlightAttitude::SFlightAttitude() :m_dPsi(0), m_dTheta(0), m_dPhi(0) {}
SFlightAttitude::SFlightAttitude(double dPsi, double dTheta, double dPhi) : m_dPsi(dPsi), m_dTheta(dTheta), m_dPhi(dPhi) {}
SFlightAttitude::SFlightAttitude(const double mT[3][3])
{
	mT2Angle(mT);
}
void SFlightAttitude::Angle2mT(double mT[3][3])
{
	mT[0][0] = cos(m_dTheta) * cos(m_dPsi);
	mT[0][1] = cos(m_dTheta) * sin(m_dPsi);
	mT[0][2] = -sin(m_dTheta);
	mT[1][0] = cos(m_dPsi) * sin(m_dTheta) * sin(m_dPhi) - cos(m_dPhi) * sin(m_dPsi);
	mT[1][1] = cos(m_dPsi) * cos(m_dPhi) + sin(m_dTheta) * sin(m_dPsi) * sin(m_dPhi);
	mT[1][2] = cos(m_dTheta) * sin(m_dPhi);
	mT[2][0] = sin(m_dPsi) * sin(m_dPhi) + cos(m_dPsi) * cos(m_dPhi) * sin(m_dTheta);
	mT[2][1] = cos(m_dPhi) * sin(m_dTheta) * sin(m_dPsi) - cos(m_dPsi) * sin(m_dPhi);
	mT[2][2] = cos(m_dTheta) * cos(m_dPhi);
}
void SFlightAttitude::mT2Angle(const double mT[3][3])
{
	double psi, theta, phi, cm, sm, sk, ck;
	theta = asin(-mT[0][2]);
	if (fabs(cos(theta)) < 1e-4) //检验theta是否为90度，若是则phi-psi为定值，取psi=0
	{
		psi = 0;
		sm = mT[1][0];
		cm = mT[2][0];
		phi = asin(sm);
		if (cm < 0)
			if (phi >= 0)
				phi = PI - phi;
			else
				phi = -PI - phi;
		m_dPsi = psi;
		m_dTheta = theta;
		m_dPhi = phi;
		return;
	}
	sk = mT[0][1] / cos(theta);
	ck = mT[0][0] / cos(theta);
	psi = asin(sk);
	if (ck < 0)
		if (psi >= 0)
			psi = PI - psi;
		else
			psi = -PI - psi;
	sm = mT[1][2] / cos(theta);
	cm = mT[2][2] / cos(theta);
	phi = asin(sm);
	if (cm < 0)
		if (phi >= 0)
			phi = PI - phi;
		else
			phi = -PI - phi;
	m_dPsi = psi;
	m_dTheta = theta;
	m_dPhi = phi;
}
SFlightAttitude SFlightAttitude::operator =(SFlightAttitude fat)
{
	m_dPsi = fat.m_dPsi;
	m_dTheta = fat.m_dTheta;
	m_dPhi = fat.m_dPhi;
	return *this;
}
SFlightAttitude SFlightAttitude::operator =(SFlightStatus fst)
{
	SFlightAttitude fat1(fst.m_dChi, fst.m_dGama, fst.m_dMu);
	SFlightAttitude fat2(-fst.m_dBeta, fst.m_dAlpha, 0.0);
	(*this) = fat1 + fat2;
	return *this;
}
SFlightAttitude SFlightAttitude::operator-(SFlightAttitude fat)
{
	double mT1[3][3];
	double mT2[3][3];
	double mT[3][3];
	Angle2mT(mT1);
	fat.Angle2mT(mT2);

	//mT1*mT2的逆
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			mT[i][j] = mT1[i][0] * mT2[j][0] + mT1[i][1] * mT2[j][1] + mT1[i][2] * mT2[j][2];

	fat.mT2Angle(mT);
	return fat;
}
SFlightAttitude SFlightAttitude::operator+(SFlightAttitude fat)
{
	double mT1[3][3];
	double mT2[3][3];
	double mT[3][3];
	Angle2mT(mT1);
	fat.Angle2mT(mT2);

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			mT[i][j] = mT2[i][0] * mT1[0][j] + mT2[i][1] * mT1[1][j] + mT2[i][2] * mT1[2][j];

	fat.mT2Angle(mT);
	return fat;
}
//////////////////////////////////
//SLimitations////////////////////
//////////////////////////////////
SRestrictions::SRestrictions()
{
	int n = sizeof(SRestrictions) / sizeof(double);
	for (int i = 0; i < n; i++)
		(&m_dH_Max)[i] = -1.0;

}
SRestrictions::SRestrictions(double dH_Max, double dH_Min,
	double dThrust_Max, double dThrust_Min,
	double dV_Max, double dV_Min,
	double dRadius_Min, double dGama_Max,
	double dGN_Max, double dBeta_Max,
	double dp_Max, double dq_Max, double dr_Max
)
{
	m_dH_Max = dH_Max;
	m_dH_Min = dH_Min;
	m_dThrust_Max = dThrust_Max;
	m_dThrust_Min = dThrust_Min;
	m_dV_Max = dV_Max;
	m_dV_Min = dV_Min;
	m_dRadius_Min = dRadius_Min;
	m_dGamma_Max = dGama_Max;
	m_dNG_Max = dGN_Max;
	m_dBeta_Max = dBeta_Max;
	//	m_dAlpha_Max=dAlpha_Max;
	m_dp_Max = dp_Max;
	m_dq_Max = dq_Max;
	m_dr_Max = dr_Max;
}
SRestrictions SRestrictions::operator=(SRestrictions rt)
{
	memcpy(this, &rt, sizeof(SRestrictions));
	return rt;
}

void SFlightStatus::ForMatWing()
{
	m_dGama = 0;
	m_dAlpha = 0;
	m_dBeta = 0;
	m_dMu = 0;
	m_dp = 0;
	m_dq = 0;
	m_dr = 0;
}

void SFlightStatusHL::ForMatWingHL()
{
	m_dphi = 0.0;		//滚转角(rad)
	m_dtheta = 0.0;	//俯仰角(rad)
	m_dpsi = 0.0;		//偏航角(rad)
	m_dp = 0.0;		//滚转角(rad/s)
	m_dq = 0.0;		//俯仰角(rad/s)
	m_dr = 0.0;		//偏航角(rad/s)
}
