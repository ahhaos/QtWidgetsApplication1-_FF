#if !defined GENERA_DEFINITIONS
#define GENERA_DEFINITIONS

#pragma once
#ifndef PI
#define PI 3.1415926535897932384626
#endif

#ifndef KSCAlE
#define KSCAlE 1000
#endif

//卫导姿态角相关量
struct att
{
	//姿态角速率
	double dtheta;
	double dphi;
	double dpsi;
	//姿态角加速度
	double ddtheta;
	double ddphi;
	double ddpsi;
	att();
	att(double adtheta, double adphi, double adpsi,
		double addtheta, double addphi, double addpsi);
};

struct Vel
{
	double Velx;
	double Vely;
	double Velz;
	Vel();
	Vel(double u, double v, double w);
};

struct comb
{
	double m_comb_deltaX;
	double m_comb_deltaY;		//横侧向偏差
	double m_comb_deltaZ;		//纵向偏差
	int m_comb_valid;
	comb();
	comb(double deltaX, double deltaY, double deltaZ, int valid);
};





struct SStaticParams	//静态参数
{
	//环境参数
	double m_dg;	//重力加速度g
	double m_dRho;	//大气密度

	//飞机参数
	double m_dM;	//飞机质量
	double m_dS;	//机翼面积
	double m_db;	//机翼展长
	double m_dC_;	//平均空气动力弦
	double m_dxT;	//发动机喷管距质心距离
	double m_da_max;//副翼舵最大
	double m_dr_max;//方向舵最大
	double m_dc_max;//鸭翼舵最大
	double m_dy_max;//推力矢量舵最大
	double m_dz_max;//推力矢量舵最大
	//转动惯量
	double m_dIx;
	double m_dIy;
	double m_dIz;
	double m_dIxz;
	SStaticParams();
	SStaticParams(double dg, double dRho, double dM, double dS, double db, double dC_,
		double m_da_max, double m_dr_max, double m_dc_max, double m_dy_max, double m_dz_max,
		double m_dxT, double dIx, double dIy, double dIz, double dIxz);
	SStaticParams operator=(SStaticParams params);
};


struct SFlightStatus	//飞行状态
{
	//
 //	int drawspeed;

	double m_dX;		//地面坐标系X坐标
	double m_dY;		//地面坐标系Y坐标
	double m_dZ;		//地面坐标系Z坐标
	double m_dV;		//航迹速度
	double m_dChi;		//航迹方位角
	double m_dGama;		//航迹俯仰角
	double m_dAlpha;	//迎角
	double m_dBeta;		//侧滑角
	double m_dMu;		//滚转角
	double m_dp;		//滚转角速度
	double m_dq;		//俯仰角速度
	double m_dr;		//偏航角速度

	double m_dtheta;     //俯仰角
	double m_dpsi;      //偏航角
	double m_dphi;       //滚转角

	double m_dVtheta;
	double m_dVphi;
	double m_dVpsi;

	double m_Vx;         //x方向速度
	double m_Vy;         //y方向速度
	double m_Vz;         //z方向速度

	double m_Accx;		//x方向线加速度
	double m_Accy;		//y方向线加速度
	double m_Accz;		//z方向线加速度

	double m_Accp;		//滚转角加速度
	double m_Accq;		//俯仰角加速度
	double m_Accr;		//偏航角加速度

	SFlightStatus();
	SFlightStatus(double dX, double dY, double dZ,
		double dV, double dKh, double dGama,
		double dAlpha, double dBeta, double dMu,
		double dp, double dq, double dr,
		double m_dtheta, double m_dpsi, double m_dphi,
		double m_dVtheta, double m_dVphi, double m_dVpsi,
		double Vx, double Vy, double Vz,
		double Accx, double Accy, double Accz,
		double Accp, double Accq, double Accr);
	SFlightStatus operator=(SFlightStatus state);
	SFlightStatus operator*(double k);
	SFlightStatus operator+(SFlightStatus state);
	SFlightStatus operator-(SFlightStatus state);
public:
	void ForMatWing();
	void InitStatus();

};

struct SFlightStatusHL
{
	double m_dX;		//地面坐标系X坐标(m)
	double m_dY;		//地面坐标系Y坐标(m)
	double m_dZ;		//地面坐标系Z坐标(m)
	double m_dbu;		//X方向速度(b:机身坐标系,m/s)
	double m_dbv;		//Y方向速度(b:机身坐标系,m/s)
	double m_dbw;		//Z方向速度(b:机身坐标系,m/s)
	double m_dpsi;		//偏航角(rad)
	double m_dtheta;	//俯仰角(rad)
	double m_dphi;		//滚转角(rad)
	double m_dp;		//滚转角(rad/s)
	double m_dq;		//俯仰角(rad/s)
	double m_dr;		//偏航角(rad/s)
	SFlightStatusHL();
	SFlightStatusHL(double dX, double dY, double dZ,
		double dbu, double dbv, double dbw,
		double dtheta, double dpsi, double dphi,
		double dp, double dq, double dr);
	SFlightStatusHL operator=(SFlightStatusHL state);
	SFlightStatusHL operator*(double k);
	SFlightStatusHL operator+(SFlightStatusHL state);
	SFlightStatusHL operator-(SFlightStatusHL state);
public:
	void ForMatWingHL();
	void InitStatus();
};


struct SControlVolumes	//控制量
{
	//5个控制舵面偏差
	double m_ddeltaa;	//副翼偏角
	double m_ddeltac;	//鸭翼舵偏角
	double m_ddeltar;	//方向舵偏角
	double m_ddeltay;	//推力矢量偏角
	double m_ddeltaz;	//推力矢量偏角
	//推力
	double m_dThrustc;

	SControlVolumes();
	SControlVolumes(double dac, double dcc, double drc, double dyc, double dzc, double dThrustc);
	SControlVolumes operator=(SControlVolumes cs);
	SControlVolumes operator+(SControlVolumes cs);
	SControlVolumes operator-(SControlVolumes cs);
	SControlVolumes operator*(double k);
};

class CCharaLine
{
public:
	//以下变量用于保存特性先编号
	const int C_L;			//00升力系数
	const int C_D;			//01阻力系数
	const int C_ldeltaa;	//02副翼	引起的滚转力矩系数
	const int C_ldeltac;	//03鸭翼舵 引起的滚转力矩系数
	const int C_ldeltar;	//04方向舵 引起的滚转力矩系数
	const int C_lp;			//05滚转角 引起的滚转力矩系数
	const int C_lr;			//06偏航角 引起的滚转力矩系数
	const int C_lbeta;		//07侧滑角 引起的滚转力矩系数
	const int C_mo;			//08零升力矩系数
	const int C_mdeltac;	//09鸭翼舵 引起的俯仰力矩系数
	const int C_mq;			//10俯仰角速度 引起的俯仰力矩系数
	const int C_ndeltaa;	//11副翼 引起的偏航力矩系数
	const int C_ndeltar;	//12方向舵 引起的偏航力矩系数
	const int C_np;			//13滚转角 引起的偏航力矩系数
	const int C_nr;			//14偏航角 引起的偏航力矩系数
	const int C_nbeta;		//15侧滑角 引起的偏航力矩系数
	const int C_ydeltaa;	//16副翼 引起的侧力系数
	const int C_ydeltar;	//17方向舵 引起的侧力系数
	const int C_ybeta;		//18侧滑角 引起的侧力系数
	const int delta_c0;		//19鸭翼偏差的零位角
	CCharaLine();
	virtual double operator()(int iSelect,	//特性线编号
		double x		//alpha值
		);	//特性线读取函数
	virtual bool ChenckAlpha(double alpha,	//待检查的alpha值
		double& AvailableAlpha//返回有效的alpha值
	);	//输入的alpha角有效性检查，
		//若alpha值超出有效范围，则返回false
};


struct SFlightAttitude
{
	double m_dPsi;
	double m_dTheta;
	double m_dPhi;
	SFlightAttitude();
	SFlightAttitude(double dPsi, double dTheta, double dPhi);
	SFlightAttitude(const double mT[3][3]);
	void mT2Angle(const double mT[3][3]);			//变换矩阵到角度
	void Angle2mT(double mT[3][3]);					//角度到变换矩阵
	SFlightAttitude operator=(SFlightAttitude fat);
	SFlightAttitude operator=(SFlightStatus fst);	//飞行状态到姿态角	
	SFlightAttitude operator+(SFlightAttitude fat);	//坐标变换相加
	SFlightAttitude operator-(SFlightAttitude fat);	//坐标变换相减
};


struct SRestrictions
{
	double m_dH_Max;		//最大升限(20000m)
	double m_dH_Min;		//最小安全飞行高度
	double m_dThrust_Max;	//最大推力
	double m_dThrust_Min;	//最小推力
	double m_dV_Max;		//最大安全飞行速度
	double m_dV_Min;		//最小安全飞行速度
	double m_dRadius_Min;	//最小转弯半径
	double m_dGamma_Max;	//正负最大航迹倾角
	double m_dNG_Max;		//最大过载加速度
	double m_dBeta_Max;		//最大侧滑角

	double m_dp_Max;		//正负最滚转角速度
	double m_dq_Max;		//正负最俯仰角速度
	double m_dr_Max;		//正负最偏航角速度
	SRestrictions();
	SRestrictions(double dH_Max, double dH_Min,
		double dThrust_Max, double dThrust_Min,
		double dV_Max, double dV_Min,
		double dRadius_Min, double dGama_Max,
		double dG_Max, double dBeta_Max,
		double dp_Max, double dq_Max, double dr_Max
	);
	SRestrictions operator=(SRestrictions rt);
};



class CGeneralModel :
	public SStaticParams,
	public SFlightStatus,
	public SControlVolumes
{
protected:
	double		m_dT;	//仿真周期
	CCharaLine* m_pCL;	//特性线指针
public:
	void GetStaticParams(SStaticParams& sp);	//获取静态参数
	void GetFlightStatus(SFlightStatus& fs);	//获取飞行状态
	void GetControlVolumes(SControlVolumes& cv);	//获取控制量
	void SetStaticParams(SStaticParams sp);		//设置飞行参数
	void SetFlightStatus(SFlightStatus fs);		//设置飞行状态
	void SetControlVolumes(SControlVolumes cv);	//设置控制量
	CGeneralModel();
	CGeneralModel(SStaticParams Static, SFlightStatus Status,
		SControlVolumes Control, CCharaLine* pCL, double dT);
	CGeneralModel operator =(CGeneralModel Model);//赋值运算
	void SetCharaLine(CCharaLine* pCL);	//设置特性线
	void SetT(double dT);	//设置仿真周期
};
#endif