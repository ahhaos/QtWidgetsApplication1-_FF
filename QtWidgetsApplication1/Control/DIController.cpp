// DIController.cpp: implementation of the CDIController class.
//
//////////////////////////////////////////////////////////////////////

#include "DIController.h"
#include <math.h>
#include "..\global.h"
#include <QDebug>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDIController::CDIController()
{
	m_dGama_I = 0;
	m_dMu_d = 0;
	//m_iInputMod = CTL_HERBST_INPUT_VKH;//默认vkh
	m_iInputMod = CTL_HERBST_INPUT_XYZ;
	m_iFollowCount = 4;
	m_doKh = 0;
	m_doGama = 0;
	//m_speed_pattern=1;
	//m_doV=100;
	//m_doX=0;
	//m_doY=0;
	//m_doZ=0;

	//x的pid参数
	m_pidX_d.m_dK[0] = data_PID_X_KP;
	m_pidX_d.m_dK[1] = data_PID_X_KI;
	m_pidX_d.m_dK[2] = data_PID_X_KD;
	m_pidX_d.m_dILimit = data_PID_X_KI_Limit;

	m_pidY_d.m_dK[0] = data_PID_Y_KP;
	m_pidY_d.m_dK[1] = data_PID_Y_KI;
	m_pidY_d.m_dK[2] = data_PID_Y_KD;
	m_pidY_d.m_dILimit = data_PID_Y_KI_Limit;

	m_pidZ_d.m_dK[0] = data_PID_Z_KP;
	m_pidZ_d.m_dK[1] = data_PID_Z_KI;
	m_pidZ_d.m_dK[2] = data_PID_Z_KD;
	m_pidZ_d.m_dILimit = data_PID_Z_KI_Limit;

	//Kh_d
	m_pidKh_d.m_dK[0] = 50;//PID控制
	m_pidKh_d.m_dK[1] = 5;
	m_pidKh_d.m_dILimit = 10;
}

CDIController::CDIController(CGeneralModel Model) : m_gf(Model), m_gs(Model), m_gvs(Model)
{
	m_dGama_I = 0.16628573674823224;
	m_dMu_d = 0;
	CCtlSystem::CCtlSystem(Model);
}

CDIController::~CDIController()
{

}

/*******************************************************
函数名：int CDIController::Input(double *pInputs)
输入：指针
功能：输入x,y,z给定
********************************************************/
int CDIController::Input(double* pInputs)
{
	//m_iFollowCount = 4;
	m_dInputs[0] = pInputs[0];
	m_dInputs[1] = pInputs[1];
	m_dInputs[2] = pInputs[2];
	m_dInputs[3] = pInputs[3];
	return 0;
}

//？？？？
void CDIController::Input_Attitude(double pInputs[], bool b4Inputs/*=false*/, bool bVelocity/*=false*/)
{
	double psi = pInputs[0];
	double theta = pInputs[1];
	double phi = pInputs[2];
	//////////////////////////////
	//add your code here;

	/////////////////////////////
}

/*******************************************************
函数名：int CDIController::Output(double *pOutputs)
输入：指针
功能：输出alpha,beta,mu给定
********************************************************/
int CDIController::Output(double* pOutputs)
{
	*(SControlVolumes*)pOutputs = *this;
	return 0;
}

/*******************************************************
函数名：int CDIController::Output(SControlVolumes &Outputs)
输入：对象的引用
功能：输出alpha,beta,mu给定
********************************************************/
int CDIController::Output(SControlVolumes& Outputs)
{
	Outputs = *this;
	return 0;
}

/*******************************************************
函数名：int CDIController::FeedBack(double *pFB)
输入：指针
功能：反馈，反馈至三个内部回路
********************************************************/
int CDIController::FeedBack(double* pFB)
{
	this->SFlightStatus::operator = (*(SFlightStatus*)pFB);
	m_gf.FeedBack(pFB);
	m_gs.FeedBack(pFB);
	m_gvs.FeedBack(pFB);
	return 0;
}

/*******************************************************
函数名：int CDIController::FeedBack(SFlightStatus fs)
输入：状态量类变量
功能：反馈，构成闭环回路
********************************************************/
int CDIController::FeedBack(SFlightStatus fs)
{
	SFlightStatus::operator = (fs);
	m_gf.FeedBack((double*)&fs);
	m_gs.FeedBack((double*)&fs);
	m_gvs.FeedBack((double*)&fs);
	return 0;
}


//特性线
void CDIController::SetCharaLine(CCharaLine* pCL)
{
	m_pCL = pCL;
	m_gf.SetCharaLine(pCL);
	m_gs.SetCharaLine(pCL);
	m_gvs.SetCharaLine(pCL);
}


/*******************************************************
函数名：void CDIController::SetCtlParams(SControllerParams cp)
输入：舵面控制量
功能：输入舵面的控制量
********************************************************/
void CDIController::SetCtlParams(SControllerParams cp)
{
	m_cp = cp;
}

/*******************************************************
函数名：void CDIController::SetStaticParams(SStaticParams sp)
输入：飞机静态参数
功能：设置飞机的静态参数
********************************************************/
void CDIController::SetStaticParams(SStaticParams sp)
{
	m_gf.SetStaticParams(sp);
	m_gs.SetStaticParams(sp);
	m_gvs.SetStaticParams(sp);
	CGeneralModel::SetStaticParams(sp);
}


/*******************************************************
函数名：void CDIController::SetT(double dT)
输入：更新周期：单位秒
功能：设置更新周期
********************************************************/
void CDIController::SetT(double dT)
{
	m_dT = dT;
	m_gf.SetT(dT);
	m_gs.SetT(dT);
	m_gvs.SetT(dT);
}

double CDIController::Gravity(double gmin)
{
	double gamad = (m_dGama - m_doGama) / m_dT;
	m_doGama = m_dGama;
	/*	double ahmam=cos((m_dGama+gmin*cos(m_dGama))/m_cp.m_dWGama/m_dV)
			*((1-gmin*sin(m_dGama))/m_cp.m_dWGama/m_dV)*gamad;
		double ahmin=cos((m_dGama-gmin*cos(m_dGama))/m_cp.m_dWGama/m_dV)
			*((1+gmin*sin(m_dGama))/m_cp.m_dWGama/m_dV)*gamad;
	*/
	return 0;
}


/*******************************************************
函数名：int CDIController::Update()
输入：无
功能：用于一般控制模式(航迹点跟踪，速向高控制保持)的状态解算更新
********************************************************/
int CDIController::Update()
{

	double tmp;//mark
	double tmp1;


	double Gamadmin;
	double khdmax = .4;

	double dBuffer[11];		//done：dbuffer要延长
							//dBuffer[8] = u;
							//dBuffer[9] = v;
							//dBuffer[10] = w;
	dBuffer[0] = m_dInputs[0];
	dBuffer[1] = m_dInputs[1];
	dBuffer[2] = m_dInputs[2]; 
	m_lpfst = m_pfst;			//赋值给上一回//记录上一个仿真周期的状态

								//if(m_iInputMod>=CTL_HERBST_INPUT_ABM_V)
								//{
								//	dBuffer[3]=m_dInputs[3];
								//	dBuffer[3] = ( dBuffer[3] - m_dV ) * m_cp.m_dWV; //V导数
								//	dBuffer[3] = m_gvs.Fun_Thrust(dBuffer[0],dBuffer[3]);
								//	if(dBuffer[3]<m_cp.m_dThrustMin) 
								//		dBuffer[3]=m_cp.m_dThrustMin;
								//	else if(dBuffer[3]>m_cp.m_dThrustMax)
								//		dBuffer[3]=m_cp.m_dThrustMax;
								//}
	switch (m_iInputMod)
	{
	case CTL_HERBST_INPUT_XYZ:
		khdmax = 1.0;//mark

		m_pfst.m_dX = dBuffer[0];
		m_pfst.m_dY = dBuffer[1];
		m_pfst.m_dZ = dBuffer[2];

		if (m_iFollowCount < 4)//求微分m_pfstd
		{
			m_pfstd.m_dX = (m_pfst.m_dX - m_lpfst.m_dX) / m_dT;
			m_pfstd.m_dY = (m_pfst.m_dY - m_lpfst.m_dY) / m_dT;
			m_pfstd.m_dZ = (m_pfst.m_dZ - m_lpfst.m_dZ) / m_dT;
		}
		else
		{
			m_pfstd.m_dX = 0;
			m_pfstd.m_dY = 0;
			m_pfstd.m_dZ = 0;
		}

		dBuffer[0] = m_pidX_d(dBuffer[0] - m_dX);
		dBuffer[1] = m_pidY_d(dBuffer[1] - m_dY);
		dBuffer[4] = m_pidZ_d(dBuffer[2] - m_dZ);			//三个PID控制
															/*	dBuffer[0] = m_pidX_d(dBuffer[0]);
															dBuffer[1] = m_pidY_d(dBuffer[1]);
															dBuffer[4] = m_pidZ_d(dBuffer[2]);*/
		dBuffer[0] = (dBuffer[0]) * m_cp.m_dWX + m_pfstd.m_dX;
		dBuffer[1] = (dBuffer[1]) * m_cp.m_dWY + m_pfstd.m_dY;
		dBuffer[4] = (dBuffer[4]) * m_cp.m_dWZ + m_pfstd.m_dZ;


		/*	dBuffer[0] = (dBuffer[0]-m_dX)*m_cp.m_dWX + m_pfstd.m_dX + m_pidX_d(dBuffer[0] - m_dX);
		dBuffer[1] = (dBuffer[1]-m_dY)*m_cp.m_dWY + m_pfstd.m_dY + m_pidY_d(dBuffer[1] - m_dY);
		dBuffer[4] = (dBuffer[2]-m_dZ)*m_cp.m_dWZ + m_pfstd.m_dZ + m_pidZ_d(dBuffer[2] - m_dZ);*/

		///////////////////////////////////////
		//极慢回路逆系统
		dBuffer[3] = dBuffer[1];
		dBuffer[1] = atan(dBuffer[1] / dBuffer[0]);
		if (dBuffer[0] < 0)
		{
			if (dBuffer[1] > 0) dBuffer[1] -= PI;
			else if (dBuffer[1] < 0) dBuffer[1] += PI;
		}

		//速度生成语句
		/*if(m_dInputs[2] > 0.1)
		{*/
		//速度做xyz分解
		dBuffer[5] = dBuffer[0];			//x轴线速度
		dBuffer[6] = dBuffer[3];			//y轴线速度
		dBuffer[7] = dBuffer[4];			//z轴线速度
		m_pfst.m_Vx = dBuffer[0];
		m_pfst.m_Vy = dBuffer[3];
		m_pfst.m_Vz = dBuffer[4];

		dBuffer[0] = sqrt(dBuffer[5] * dBuffer[5] + dBuffer[6] * dBuffer[6] + dBuffer[7] * dBuffer[7]);		//合速度


																											///////////////////////////////////////

	case CTL_HERBST_INPUT_VKH:
		tmp1 = m_pidZ_d(dBuffer[2] - m_dZ);
		dBuffer[2] = (dBuffer[2] - m_dZ) * m_cp.m_dWZ + m_pfstd.m_dZ; //计算高度的导数
		dBuffer[2] += tmp1;
		if (fabs(dBuffer[2]) > dBuffer[0])
		{
			if (dBuffer[2] > 0) dBuffer[2] = dBuffer[0];
			else	dBuffer[2] = -dBuffer[0];
		}
		dBuffer[2] = -asin(dBuffer[2] / dBuffer[0]);//Gamac
													//qDebug() << "VKH";
	case CTL_HERBST_INPUT_VKG:
		m_pfst.m_dV = dBuffer[0];
		m_pfst.m_dChi = dBuffer[1];
		m_pfst.m_dGama = dBuffer[2];

		if (m_iFollowCount < 3)
		{
			m_pfstd.m_dV = (m_pfst.m_dV - m_lpfst.m_dV) / m_dT;
			m_pfstd.m_dChi = (m_pfst.m_dChi - m_lpfst.m_dChi);
			while (m_pfstd.m_dChi > PI) m_pfstd.m_dChi -= 2 * PI;
			while (m_pfstd.m_dChi < -PI) m_pfstd.m_dChi += 2 * PI;
			m_pfstd.m_dChi /= m_dT;
			m_pfstd.m_dGama = (m_pfst.m_dGama - m_lpfst.m_dGama) / m_dT;
		}
		else
		{
			m_pfstd.m_dV = 0;
			m_pfstd.m_dChi = 0;
			m_pfstd.m_dGama = 0;
		}

		dBuffer[0] = (dBuffer[0] - m_dV) * m_cp.m_dWV + m_pfstd.m_dV; //V导数，速度反馈

																	  //-pi<delta_kh<pi
		dBuffer[1] = (dBuffer[1] - m_dChi);//Kh导数
		if (dBuffer[1] > 3.1415926535897932384626)
			dBuffer[1] -= ((int)(dBuffer[1] / (3.1415926535897932384626 * 2) + 1)) * 3.1415926535897932384626 * 2;
		else if (dBuffer[1] < -3.1415926535897932384626)
			dBuffer[1] -= ((int)(dBuffer[1] / (3.1415926535897932384626 * 2) - 1)) * 3.1415926535897932384626 * 2;
		dBuffer[1] = dBuffer[1] * m_cp.m_dWKh + m_pfstd.m_dChi;
		if (dBuffer[1] > khdmax)
			dBuffer[1] = khdmax;
		else if (dBuffer[1] < -khdmax)
			dBuffer[1] = -khdmax;//KH导数限幅
		tmp = dBuffer[1];//mark


						 //tmp1 = dBuffer[2] - m_dGama;	//Gama误差
						 //tmp1 = m_pidZ_d(dBuffer[2]-m_dZ);
		dBuffer[2] = dBuffer[2] - m_dGama;	//Gama误差
		m_dGama_I += dBuffer[2] * m_dT;		//Gama误差积分
		if (m_dGama_I > m_cp.m_dGama_IMax) m_dGama_I = m_cp.m_dGama_IMax;
		else if (m_dGama_I < -m_cp.m_dGama_IMax) m_dGama_I = -m_cp.m_dGama_IMax;//积分饱和
		dBuffer[2] = dBuffer[2] * m_cp.m_dWGama + m_dGama_I * m_cp.m_dWGama_I + m_pfstd.m_dGama;//Gama导数

		Gamadmin = (2.0 - m_dg * cos(m_dGama)) / m_dV;//防失重
		if (dBuffer[2] < Gamadmin)
			dBuffer[2] = Gamadmin;
		else if (dBuffer[2] > -Gamadmin)
			dBuffer[2] = -Gamadmin;//
								   //qDebug() << "VKG";
	case CTL_HERBST_INPUT_DVKG:
		m_gvs.Input(dBuffer);//V_d,Kh_d,H_d
		m_gvs.Update();
		m_gvs.Output(dBuffer);//Alphac,Betac,Muc,Thrust
		//qDebug() << "gvs";
	case CTL_HERBST_INPUT_ABM_V:;
	}

	//下面开始Alphac,Betac,Muc,Thrust输入到慢回路控制器
	if (dBuffer[3] < m_cp.m_dThrustMin)
		dBuffer[3] = m_cp.m_dThrustMin;
	else if (dBuffer[3] > m_cp.m_dThrustMax)
		dBuffer[3] = m_cp.m_dThrustMax;			//推力饱和

	m_dThrustc = dBuffer[3];

	if (dBuffer[0] > 1)
		dBuffer[0] = 1;
	else if (dBuffer[0] < -1)
		dBuffer[0] = -1;					//迎角饱和限制

	m_pfst.m_dAlpha = dBuffer[0];
	m_pfst.m_dBeta = dBuffer[1];
	m_pfst.m_dMu = dBuffer[2];
	if (m_iFollowCount < 2)
	{
		m_pfstd.m_dAlpha = (m_pfst.m_dAlpha - m_lpfst.m_dAlpha) / m_dT;
		m_pfstd.m_dBeta = (m_pfst.m_dBeta - m_lpfst.m_dBeta) / m_dT;
		m_pfstd.m_dMu = (m_pfst.m_dMu - m_lpfst.m_dMu);
		while (m_pfstd.m_dMu > PI) m_pfstd.m_dMu -= 2 * PI;
		while (m_pfstd.m_dMu < -PI) m_pfstd.m_dMu += 2 * PI;
		m_pfstd.m_dMu /= m_dT;

	}
	else
	{
		m_pfstd.m_dAlpha = 0;
		m_pfstd.m_dBeta = 0;
		m_pfstd.m_dMu = 0;
	}

	//todo：船姿态角转气流角

	dBuffer[0] = (dBuffer[0] - m_dAlpha) * m_cp.m_dWAlpha + m_pfstd.m_dAlpha; //Alpha导数
	dBuffer[1] = (dBuffer[1] - m_dBeta) * m_cp.m_dWBeta + m_pfstd.m_dBeta; //Beta导数
	dBuffer[2] = (dBuffer[2] - m_dMu) * m_cp.m_dWMu + m_pfstd.m_dMu;//Mu导数
	m_gs.Input(dBuffer);//Alpha_d,Beta_d,Mu_d,Thrust
	m_gs.Update();
	m_gs.Output(dBuffer);//pc,qc,rc//
						 //角速度
	//dBuffer[0] += m_ship_p / (data_time / 1000);//横滚补偿
	//dBuffer[1] += m_ship_q / (data_time / 1000);//俯仰补偿

	m_pfst.m_dp = dBuffer[0];
	m_pfst.m_dq = dBuffer[1];
	m_pfst.m_dr = dBuffer[2];
	//角加速度
	//dBuffer[5] = (m_pfst.m_dp - m_lpfst.m_dp) / m_dT;
	//dBuffer[6] = (m_pfst.m_dq - m_lpfst.m_dq) / m_dT;
	//dBuffer[7] = (m_pfst.m_dr - m_lpfst.m_dr) / m_dT;
	//m_pfst.m_Accp = dBuffer[5];
	//m_pfst.m_Accq = dBuffer[6];
	//m_pfst.m_Accr = dBuffer[7];

	if (m_iFollowCount < 1)
	{
		//		m_pfstd.m_dp = (m_pfst.m_dp - m_lpfst.m_dp)/m_dT;
		//		m_pfstd.m_dq = (m_pfst.m_dq - m_lpfst.m_dq)/m_dT;
		//		m_pfstd.m_dr = (m_pfst.m_dr - m_lpfst.m_dr)/m_dT;
	}
	else
	{
		m_iFollowCount--;
		m_pfstd.m_dp = 0;
		m_pfstd.m_dq = 0;
		m_pfstd.m_dr = 0;
	}


	dBuffer[0] = (dBuffer[0] - m_dp) * m_cp.m_dWp + m_pfstd.m_dp; //pc
	dBuffer[1] = (dBuffer[1] - m_dq) * m_cp.m_dWq + m_pfstd.m_dq; //qc
	dBuffer[2] = (dBuffer[2] - m_dr) * m_cp.m_dWr + m_pfstd.m_dr; //rc

	m_gf.Input(dBuffer);//pc,qc,rc,Thrust
	m_gf.Update();
	m_gf.Output(dBuffer);//deltaa,deltac,deltar,deltay,deltaz;//

	m_ddeltaa = dBuffer[0];
	m_ddeltac = dBuffer[1];
	m_ddeltar = dBuffer[2];
	m_ddeltay = dBuffer[3];
	m_ddeltaz = dBuffer[4];

	m_pfstd = SFlightStatus(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);//
	return 0;
}





/*******************************************************
函数名：int CDIController::Update_XYZV()
输入：无
功能：用于一般控制模式(航迹点跟踪，速向高控制保持)的状态解算更新
********************************************************/
int CDIController::Update_XYZV()
{

	double tmp;//mark
	double tmp1;


	double Gamadmin;
	double khdmax = .4;

	double dBuffer[11];		//done：dbuffer要延长
							//dBuffer[8] = u;
							//dBuffer[9] = v;
							//dBuffer[10] = w;
	dBuffer[0] = m_dInputs[0];
	dBuffer[1] = m_dInputs[1];
	dBuffer[2] = m_dInputs[2]; //舰体升沉
	m_lpfst = m_pfst;			//赋值给上一回//记录上一个仿真周期的状态

								//if(m_iInputMod>=CTL_HERBST_INPUT_ABM_V)
								//{
								//	dBuffer[3]=m_dInputs[3];
								//	dBuffer[3] = ( dBuffer[3] - m_dV ) * m_cp.m_dWV; //V导数
								//	dBuffer[3] = m_gvs.Fun_Thrust(dBuffer[0],dBuffer[3]);
								//	if(dBuffer[3]<m_cp.m_dThrustMin) 
								//		dBuffer[3]=m_cp.m_dThrustMin;
								//	else if(dBuffer[3]>m_cp.m_dThrustMax)
								//		dBuffer[3]=m_cp.m_dThrustMax;
								//}
	switch (m_iInputMod)
	{
	case CTL_HERBST_INPUT_XYZ:
		khdmax = 1.0;//mark

		m_pfst.m_dX = dBuffer[0];
		m_pfst.m_dY = dBuffer[1];
		m_pfst.m_dZ = dBuffer[2];

		if (m_iFollowCount < 4)//求微分m_pfstd
		{
			m_pfstd.m_dX = (m_pfst.m_dX - m_lpfst.m_dX) / m_dT;
			m_pfstd.m_dY = (m_pfst.m_dY - m_lpfst.m_dY) / m_dT;
			m_pfstd.m_dZ = (m_pfst.m_dZ - m_lpfst.m_dZ) / m_dT;
		}
		else
		{
			m_pfstd.m_dX = 0;
			m_pfstd.m_dY = 0;
			m_pfstd.m_dZ = 0;
		}

		dBuffer[0] = m_pidX_d(dBuffer[0] - m_dX);
		dBuffer[1] = m_pidY_d(dBuffer[1] - m_dY);
		dBuffer[4] = m_pidZ_d(dBuffer[2] - m_dZ);			//三个PID控制
															/*	dBuffer[0] = m_pidX_d(dBuffer[0]);
															dBuffer[1] = m_pidY_d(dBuffer[1]);
															dBuffer[4] = m_pidZ_d(dBuffer[2]);*/
		dBuffer[0] = (dBuffer[0]) * m_cp.m_dWX + m_pfstd.m_dX;
		dBuffer[1] = (dBuffer[1]) * m_cp.m_dWY + m_pfstd.m_dY;
		dBuffer[4] = (dBuffer[4]) * m_cp.m_dWZ + m_pfstd.m_dZ;


		/*	dBuffer[0] = (dBuffer[0]-m_dX)*m_cp.m_dWX + m_pfstd.m_dX + m_pidX_d(dBuffer[0] - m_dX);
		dBuffer[1] = (dBuffer[1]-m_dY)*m_cp.m_dWY + m_pfstd.m_dY + m_pidY_d(dBuffer[1] - m_dY);
		dBuffer[4] = (dBuffer[2]-m_dZ)*m_cp.m_dWZ + m_pfstd.m_dZ + m_pidZ_d(dBuffer[2] - m_dZ);*/

		///////////////////////////////////////
		//极慢回路逆系统
		dBuffer[3] = dBuffer[1];
		dBuffer[1] = atan(dBuffer[1] / dBuffer[0]);
		if (dBuffer[0] < 0)
		{
			if (dBuffer[1] > 0) dBuffer[1] -= PI;
			else if (dBuffer[1] < 0) dBuffer[1] += PI;
		}

		//速度生成语句
		/*if(m_dInputs[2] > 0.1)
		{*/
		//速度做xyz分解
		dBuffer[5] = dBuffer[0];			//x轴线速度
		dBuffer[6] = dBuffer[3];			//y轴线速度
		dBuffer[7] = dBuffer[4];			//z轴线速度
		m_pfst.m_Vx = dBuffer[0];
		m_pfst.m_Vy = dBuffer[3];
		m_pfst.m_Vz = dBuffer[4];

		dBuffer[0] = sqrt(dBuffer[5] * dBuffer[5] + dBuffer[6] * dBuffer[6] + dBuffer[7] * dBuffer[7]);		//合速度


																											///////////////////////////////////////

	case CTL_HERBST_INPUT_VKH:
		//qDebug() << "bf0:" << dBuffer[0] << "bf1:" << dBuffer[1] << "bf2:" << dBuffer[2] << "bf3" << dBuffer[3] << "###";
		tmp1 = m_pidZ_d(dBuffer[2] - m_dZ);
		dBuffer[2] = (dBuffer[2] - m_dZ) * m_cp.m_dWZ + m_pfstd.m_dZ; //计算高度的导数
		dBuffer[2] += tmp1;
		if (fabs(dBuffer[2]) > dBuffer[0])
		{
			if (dBuffer[2] > 0) dBuffer[2] = dBuffer[0];
			else	dBuffer[2] = -dBuffer[0];
		}
		dBuffer[2] = -asin(dBuffer[2] / dBuffer[0]);//Gamac
													//qDebug() << "VKH";
	case CTL_HERBST_INPUT_VKG:
		//qDebug() << "bf0:" << dBuffer[0] << "bf1:" << dBuffer[1] << "bf2:" << dBuffer[2] << "bf3" << dBuffer[3] << "!!!";
		m_pfst.m_dV = dBuffer[0];
		m_pfst.m_dChi = dBuffer[1];
		m_pfst.m_dGama = dBuffer[2];

		if (m_iFollowCount < 3)
		{
			m_pfstd.m_dV = (m_pfst.m_dV - m_lpfst.m_dV) / m_dT;
			m_pfstd.m_dChi = (m_pfst.m_dChi - m_lpfst.m_dChi);
			while (m_pfstd.m_dChi > PI) m_pfstd.m_dChi -= 2 * PI;
			while (m_pfstd.m_dChi < -PI) m_pfstd.m_dChi += 2 * PI;
			m_pfstd.m_dChi /= m_dT;
			m_pfstd.m_dGama = (m_pfst.m_dGama - m_lpfst.m_dGama) / m_dT;
		}
		else
		{
			m_pfstd.m_dV = 0;
			m_pfstd.m_dChi = 0;
			m_pfstd.m_dGama = 0;
		}

		dBuffer[0] = (dBuffer[0] - m_dV) * m_cp.m_dWV + m_pfstd.m_dV; //V导数，速度反馈
		//qDebug() << "bf0:" << dBuffer[0];
																	  //-pi<delta_kh<pi
		dBuffer[1] = (dBuffer[1] - m_dChi);//Kh导数
		if (dBuffer[1] > 3.1415926535897932384626)
			dBuffer[1] -= ((int)(dBuffer[1] / (3.1415926535897932384626 * 2) + 1)) * 3.1415926535897932384626 * 2;
		else if (dBuffer[1] < -3.1415926535897932384626)
			dBuffer[1] -= ((int)(dBuffer[1] / (3.1415926535897932384626 * 2) - 1)) * 3.1415926535897932384626 * 2;
		dBuffer[1] = dBuffer[1] * m_cp.m_dWKh + m_pfstd.m_dChi;
		if (dBuffer[1] > khdmax)
			dBuffer[1] = khdmax;
		else if (dBuffer[1] < -khdmax)
			dBuffer[1] = -khdmax;//KH导数限幅
		tmp = dBuffer[1];//mark


						 //tmp1 = dBuffer[2] - m_dGama;	//Gama误差
						 //tmp1 = m_pidZ_d(dBuffer[2]-m_dZ);
		dBuffer[2] = dBuffer[2] - m_dGama;	//Gama误差
		m_dGama_I += dBuffer[2] * m_dT;		//Gama误差积分
		if (m_dGama_I > m_cp.m_dGama_IMax) m_dGama_I = m_cp.m_dGama_IMax;
		else if (m_dGama_I < -m_cp.m_dGama_IMax) m_dGama_I = -m_cp.m_dGama_IMax;//积分饱和
		dBuffer[2] = dBuffer[2] * m_cp.m_dWGama + m_dGama_I * m_cp.m_dWGama_I + m_pfstd.m_dGama;//Gama导数

		Gamadmin = (2.0 - m_dg * cos(m_dGama)) / m_dV;//防失重
		if (dBuffer[2] < Gamadmin)
			dBuffer[2] = Gamadmin;
		else if (dBuffer[2] > -Gamadmin)
			dBuffer[2] = -Gamadmin;//
								   //qDebug() << "VKG";
	case CTL_HERBST_INPUT_DVKG:
		
		m_gvs.Input(dBuffer);//V_d,Kh_d,H_d																		/////////////////////////////////////极慢回路计算
		m_gvs.Update();
		m_gvs.Output(dBuffer);//Alphac,Betac,Muc,Thrust
							  //qDebug() << "gvs";
	case CTL_HERBST_INPUT_ABM_V:
		//qDebug() << "***";
		break;




	case CTL_HERBST_INPUT_XYZ_V:
		khdmax = 0.1;//mark

		m_pfst.m_dX = dBuffer[0];
		m_pfst.m_dY = dBuffer[1];
		m_pfst.m_dZ = dBuffer[2];

		if (m_iFollowCount < 4)//求微分m_pfstd
		{       
			m_pfstd.m_dX = (m_pfst.m_dX - m_lpfst.m_dX) / m_dT;
			m_pfstd.m_dY = (m_pfst.m_dY - m_lpfst.m_dY) / m_dT;
			m_pfstd.m_dZ = (m_pfst.m_dZ - m_lpfst.m_dZ) / m_dT;
		}
		else
		{
			m_pfstd.m_dX = 0;
			m_pfstd.m_dY = 0;
			m_pfstd.m_dZ = 0;
		}

		dBuffer[0] = m_pidX_d(dBuffer[0] - m_dX);
		dBuffer[1] = m_pidY_d(dBuffer[1] - m_dY);
		dBuffer[4] = m_pidZ_d(dBuffer[2] - m_dZ);			//三个PID控制
															/*	dBuffer[0] = m_pidX_d(dBuffer[0]);
															dBuffer[1] = m_pidY_d(dBuffer[1]);
															dBuffer[4] = m_pidZ_d(dBuffer[2]);*/
		dBuffer[0] = (dBuffer[0]) * m_cp.m_dWX + m_pfstd.m_dX;
		dBuffer[1] = (dBuffer[1]) * m_cp.m_dWY + m_pfstd.m_dY;
		dBuffer[4] = (dBuffer[4]) * m_cp.m_dWZ + m_pfstd.m_dZ;


		/*	dBuffer[0] = (dBuffer[0]-m_dX)*m_cp.m_dWX + m_pfstd.m_dX + m_pidX_d(dBuffer[0] - m_dX);
		dBuffer[1] = (dBuffer[1]-m_dY)*m_cp.m_dWY + m_pfstd.m_dY + m_pidY_d(dBuffer[1] - m_dY);
		dBuffer[4] = (dBuffer[2]-m_dZ)*m_cp.m_dWZ + m_pfstd.m_dZ + m_pidZ_d(dBuffer[2] - m_dZ);*/

		///////////////////////////////////////
		//极慢回路逆系统
		dBuffer[3] = dBuffer[1];
		dBuffer[1] = atan(dBuffer[1] / dBuffer[0]);
		if (dBuffer[0] < 0)
		{
			if (dBuffer[1] > 0) dBuffer[1] -= PI;
			else if (dBuffer[1] < 0) dBuffer[1] += PI;
		}

		//速度生成语句
		/*if(m_dInputs[2] > 0.1)
		{*/


		//dBuffer[0] = sqrt(dBuffer[5] * dBuffer[5] + dBuffer[6] * dBuffer[6] + dBuffer[7] * dBuffer[7]);		//合速度

		dBuffer[0] = m_dInputs[3];
																											///////////////////////////////////////


		//qDebug() << "bf0:" << dBuffer[0] << "bf1:" << dBuffer[1] << "bf2:" << dBuffer[2] << "bf3" << dBuffer[3]<<"$$$";
		tmp1 = m_pidZ_d(dBuffer[2] - m_dZ);
		dBuffer[2] = (dBuffer[2] - m_dZ) * m_cp.m_dWZ + m_pfstd.m_dZ; //计算高度的导数
		dBuffer[2] += tmp1;
		if (fabs(dBuffer[2]) > dBuffer[0])
		{
			if (dBuffer[2] > 0) dBuffer[2] = dBuffer[0];
			else	dBuffer[2] = -dBuffer[0];
		}
		dBuffer[2] = -asin(dBuffer[2] / dBuffer[0]);//Gamac
													//qDebug() << "VKH";
	
		m_pfst.m_dV = dBuffer[0];
		m_pfst.m_dChi = dBuffer[1];
		m_pfst.m_dGama = dBuffer[2];

		if (m_iFollowCount < 3)
		{
			
			m_pfstd.m_dV = (m_pfst.m_dV - m_lpfst.m_dV) / m_dT;
			m_pfstd.m_dChi = (m_pfst.m_dChi - m_lpfst.m_dChi);
			while (m_pfstd.m_dChi > PI) m_pfstd.m_dChi -= 2 * PI;
			while (m_pfstd.m_dChi < -PI) m_pfstd.m_dChi += 2 * PI;
			m_pfstd.m_dChi /= m_dT;
			m_pfstd.m_dGama = (m_pfst.m_dGama - m_lpfst.m_dGama) / m_dT;
		}
		else
		{
			m_pfstd.m_dV = 0;
			m_pfstd.m_dChi = 0;
			m_pfstd.m_dGama = 0;
		}

		dBuffer[0] = (dBuffer[0] - m_dV) * m_cp.m_dWV + m_pfstd.m_dV; //V导数，速度反馈
		
																	  //-pi<delta_kh<pi
		dBuffer[1] = (dBuffer[1] - m_dChi);//Kh导数
		if (dBuffer[1] > 3.1415926535897932384626)
			dBuffer[1] -= ((int)(dBuffer[1] / (3.1415926535897932384626 * 2) + 1)) * 3.1415926535897932384626 * 2;
		else if (dBuffer[1] < -3.1415926535897932384626)
			dBuffer[1] -= ((int)(dBuffer[1] / (3.1415926535897932384626 * 2) - 1)) * 3.1415926535897932384626 * 2;
		dBuffer[1] = dBuffer[1] * m_cp.m_dWKh + m_pfstd.m_dChi;
		if (dBuffer[1] > khdmax)
			dBuffer[1] = khdmax;
		else if (dBuffer[1] < -khdmax)
			dBuffer[1] = -khdmax;//KH导数限幅
		tmp = dBuffer[1];//mark


						 //tmp1 = dBuffer[2] - m_dGama;	//Gama误差
						 //tmp1 = m_pidZ_d(dBuffer[2]-m_dZ);
		dBuffer[2] = dBuffer[2] - m_dGama;	//Gama误差
		m_dGama_I += dBuffer[2] * m_dT;		//Gama误差积分
		if (m_dGama_I > m_cp.m_dGama_IMax) m_dGama_I = m_cp.m_dGama_IMax;
		else if (m_dGama_I < -m_cp.m_dGama_IMax) m_dGama_I = -m_cp.m_dGama_IMax;//积分饱和
		dBuffer[2] = dBuffer[2] * m_cp.m_dWGama + m_dGama_I * m_cp.m_dWGama_I + m_pfstd.m_dGama;//Gama导数

		Gamadmin = (2.0 - m_dg * cos(m_dGama)) / m_dV;//防失重
		if (dBuffer[2] < Gamadmin)
			dBuffer[2] = Gamadmin;
		else if (dBuffer[2] > -Gamadmin)
			dBuffer[2] = -Gamadmin;//
								   //qDebug() << "VKG";

		m_gvs.Input(dBuffer);//V_d,Kh_d,H_d
		m_gvs.Update();
		m_gvs.Output(dBuffer);//Alphac,Betac,Muc,Thrust
							  //qDebug() << "gvs";

		//qDebug() << "***";
		break;


	default:
		break;
	}





	//qDebug() << "dBuffer[3]" << dBuffer[3];
	//下面开始Alphac,Betac,Muc,Thrust输入到慢回路控制器
	if (dBuffer[3] < m_cp.m_dThrustMin)
		dBuffer[3] = m_cp.m_dThrustMin;
	else if (dBuffer[3] > m_cp.m_dThrustMax)
		dBuffer[3] = m_cp.m_dThrustMax;			//推力饱和

	m_dThrustc = dBuffer[3];

	//qDebug() << "m_dThrustc" << m_dThrustc;
	if (dBuffer[0] > 1)
		dBuffer[0] = 1;
	else if (dBuffer[0] < -1)
		dBuffer[0] = -1;					//迎角饱和限制

	m_pfst.m_dAlpha = dBuffer[0];
	m_pfst.m_dBeta = dBuffer[1];
	m_pfst.m_dMu = dBuffer[2];
	if (m_iFollowCount < 2)
	{
		
		m_pfstd.m_dAlpha = (m_pfst.m_dAlpha - m_lpfst.m_dAlpha) / m_dT;
		m_pfstd.m_dBeta = (m_pfst.m_dBeta - m_lpfst.m_dBeta) / m_dT;
		m_pfstd.m_dMu = (m_pfst.m_dMu - m_lpfst.m_dMu);
		while (m_pfstd.m_dMu > PI) m_pfstd.m_dMu -= 2 * PI;
		while (m_pfstd.m_dMu < -PI) m_pfstd.m_dMu += 2 * PI;
		m_pfstd.m_dMu /= m_dT;

	}
	else
	{
		m_pfstd.m_dAlpha = 0;
		m_pfstd.m_dBeta = 0;
		m_pfstd.m_dMu = 0;
	}



	dBuffer[0] = (dBuffer[0] - m_dAlpha) * m_cp.m_dWAlpha + m_pfstd.m_dAlpha; //Alpha导数
	dBuffer[1] = (dBuffer[1] - m_dBeta) * m_cp.m_dWBeta + m_pfstd.m_dBeta; //Beta导数
	dBuffer[2] = (dBuffer[2] - m_dMu) * m_cp.m_dWMu + m_pfstd.m_dMu;//Mu导数														
	m_gs.Input(dBuffer);//Alpha_d,Beta_d,Mu_d,Thrust															  /////////////////////////////////////////////////////////慢回路计算
	//qDebug() << "bf0:" << dBuffer[0] << "bf1:" << dBuffer[1] << "bf2:" << dBuffer[2] << "bf3" << dBuffer[3] << "%%%";
	m_gs.Update();
	m_gs.Output(dBuffer);//pc,qc,rc//
						 //角速度
						 //dBuffer[0] += m_ship_p / (data_time / 1000);//横滚补偿
						 //dBuffer[1] += m_ship_q / (data_time / 1000);//俯仰补偿

	m_pfst.m_dp = dBuffer[0];
	m_pfst.m_dq = dBuffer[1];
	m_pfst.m_dr = dBuffer[2];
	//角加速度
	//dBuffer[5] = (m_pfst.m_dp - m_lpfst.m_dp) / m_dT;
	//dBuffer[6] = (m_pfst.m_dq - m_lpfst.m_dq) / m_dT;
	//dBuffer[7] = (m_pfst.m_dr - m_lpfst.m_dr) / m_dT;
	//m_pfst.m_Accp = dBuffer[5];
	//m_pfst.m_Accq = dBuffer[6];
	//m_pfst.m_Accr = dBuffer[7];

	if (m_iFollowCount < 1)
	{
		//		m_pfstd.m_dp = (m_pfst.m_dp - m_lpfst.m_dp)/m_dT;
		//		m_pfstd.m_dq = (m_pfst.m_dq - m_lpfst.m_dq)/m_dT;
		//		m_pfstd.m_dr = (m_pfst.m_dr - m_lpfst.m_dr)/m_dT;
	}
	else
	{
		m_iFollowCount--;
		m_pfstd.m_dp = 0;
		m_pfstd.m_dq = 0;
		m_pfstd.m_dr = 0;
	}


	dBuffer[0] = (dBuffer[0] - m_dp) * m_cp.m_dWp + m_pfstd.m_dp; //pc
	dBuffer[1] = (dBuffer[1] - m_dq) * m_cp.m_dWq + m_pfstd.m_dq; //qc
	dBuffer[2] = (dBuffer[2] - m_dr) * m_cp.m_dWr + m_pfstd.m_dr; //rc

	m_gf.Input(dBuffer);//pc,qc,rc,Thrust
	m_gf.Update();
	m_gf.Output(dBuffer);//deltaa,deltac,deltar,deltay,deltaz;//					                                 /////////////////////////////////////////////////// 快回路计算

	m_ddeltaa = dBuffer[0];
	m_ddeltac = dBuffer[1];
	m_ddeltar = dBuffer[2];
	m_ddeltay = dBuffer[3];
	m_ddeltaz = dBuffer[4];

	m_pfstd = SFlightStatus(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);//
	return 0;
}




/*******************************************************
函数名：int CDIController::Follow
输入：x,y,z位置量，船的状态量
功能：根据输入求出舵面的控制量
********************************************************/
int CDIController::Follow(double x, double y, double z, double m_ship_dH, double m_ship_p, double m_ship_q/*,double m_shiptail_Vx,double m_shiptail_Vy,double m_shiptail_Vz*/)
{
	/*m_cp.m_dWX=data_bandwidth_dWX;
	m_cp.m_dWY=data_bandwidth_dWY;
	m_cp.m_dWZ=data_bandwidth_dWZ;
	m_cp.m_dWV=data_bandwidth_dWV;
	m_cp.m_dWKh=data_bandwidth_dWKh;
	m_cp.m_dWGama=data_bandwidth_dWGama;
	m_cp.m_dWAlpha=data_bandwidth_dWAlpha;
	m_cp.m_dWBeta=data_bandwidth_dWBeta;
	m_cp.m_dWMu=data_bandwidth_dWMu;
	m_cp.m_dWp=data_bandwidth_dWp;
	m_cp.m_dWq=data_bandwidth_dWq;
	m_cp.m_dWr=data_bandwidth_dWr;*/

	//m_pidX_d.m_dK[0]=data_PID_X_KP;
	//m_pidX_d.m_dK[1]=data_PID_X_KI;
	//m_pidX_d.m_dK[2]=data_PID_X_KD;
	//m_pidX_d.m_dILimit=data_PID_X_KI_Limit;

	////m_pidY_d.m_dK[0]=data_PID_Y_KP;
	////m_pidY_d.m_dK[1]=data_PID_Y_KI;
	////m_pidY_d.m_dK[2]=data_PID_Y_KD;
	////m_pidY_d.m_dILimit=data_PID_Y_KI_Limit;

	//m_pidZ_d.m_dK[0]=data_PID_Z_KP;
	//m_pidZ_d.m_dK[1]=data_PID_Z_KI;
	//m_pidZ_d.m_dK[2]=data_PID_Z_KD;
	//m_pidZ_d.m_dILimit=data_PID_Z_KI_Limit;

	//方案1:
	//	double vs[5];
	//	m_iInputMod = CTL_HERBST_INPUT_XYZ;
	//	m_lpfst = m_pfst;
	//	m_pfst.m_dX = m_dInputs[0] = x;
	//	m_pfst.m_dY = m_dInputs[1] = y;
	//	m_pfst.m_dZ = m_dInputs[2] = z;
	//	
	//	if(m_iFollowCount==4) goto EndFollow;
	//	///////////////////////////////////////////////
	//	//位置微分
	//	m_pfstd.m_dX = (m_pfst.m_dX - m_lpfst.m_dX)/m_dT;	//
	//	m_pfstd.m_dY = (m_pfst.m_dY - m_lpfst.m_dY)/m_dT;
	//	m_pfstd.m_dZ = (m_pfst.m_dZ - m_lpfst.m_dZ)/m_dT;
	//	
	//	///////////////////////////////////////////////
	//	//极慢回路逆系统
	//	m_pfst.m_dV = sqrt(m_pfstd.m_dX*m_pfstd.m_dX 
	//		+ m_pfstd.m_dY*m_pfstd.m_dY + m_pfstd.m_dZ*m_pfstd.m_dZ);
	//	m_pfst.m_dChi = atan(m_pfstd.m_dY/m_pfstd.m_dX);
	//	if(m_pfstd.m_dX<0)
	//	{
	//		if(m_pfst.m_dChi<0) m_pfst.m_dChi += PI;
	//		else if(m_pfst.m_dChi>0) m_pfst.m_dChi -= PI;
	//	}
	//	m_pfst.m_dGama = -asin(m_pfstd.m_dZ / m_pfst.m_dV);
	//	
	//	if(m_iFollowCount==3) goto EndFollow;
	//	///////////////////////////////////////////////
	//	//V,kh,Gama微分
	//	m_pfstd.m_dV = (m_pfst.m_dV - m_lpfst.m_dV)/m_dT;
	//	m_pfstd.m_dChi = (m_pfst.m_dChi - m_lpfst.m_dChi);
	//	while(m_pfstd.m_dChi>PI) m_pfstd.m_dChi -= 2*PI;
	//	while(m_pfstd.m_dChi<-PI) m_pfstd.m_dChi += 2*PI;
	//	m_pfstd.m_dChi /= m_dT;
	//	m_pfstd.m_dGama = (m_pfst.m_dGama - m_lpfst.m_dGama)/m_dT;
	//
	//	/////////////////////////////////////////////////
	//	/////////////////////////////////////////////////
	//
	//	vs[0] = m_pfstd.m_dV;
	//	vs[1] = m_pfstd.m_dChi;
	//	vs[2] = m_pfstd.m_dGama;
	//	m_gvs.Input(vs);
	//	m_gvs.Update();
	//	m_gvs.Output(vs);
	//
	//	m_pfst.m_dAlpha = vs[0];
	//	m_pfst.m_dBeta = vs[1];
	//	m_pfst.m_dMu = vs[2];
	//	vs[0] = m_pfstd.m_dAlpha = (m_pfst.m_dAlpha - m_lpfst.m_dAlpha)/m_dT;
	//	vs[1] = m_pfstd.m_dBeta = (m_pfst.m_dBeta - m_lpfst.m_dBeta)/m_dT;
	//	vs[2] = m_pfstd.m_dMu = (m_pfst.m_dMu - m_lpfst.m_dMu);
	//	while(m_pfstd.m_dMu>PI) m_pfstd.m_dMu -= 2*PI;
	//	while(m_pfstd.m_dMu<-PI) m_pfstd.m_dMu += 2*PI;
	//	m_pfstd.m_dMu /= m_dT;
	//
	//	m_gs.Input(vs);
	//	m_gs.Update();
	//	m_gs.Output(vs);
	//	m_pfst.m_dp = vs[0];
	//	m_pfst.m_dq = vs[1];
	//	m_pfst.m_dr = vs[2];
	//	vs[0] = m_pfstd.m_dp = (m_pfst.m_dp - m_lpfst.m_dp)/m_dT;
	//	vs[1] = m_pfstd.m_dq = (m_pfst.m_dq - m_lpfst.m_dq)/m_dT;
	//	vs[2] = m_pfstd.m_dr = (m_pfst.m_dr - m_lpfst.m_dr)/m_dT;
	//	m_gf.Input(vs);
	//	m_gf.Update();
	//	m_gf.Output(vs);
	//
	//	m_ddeltaa = vs[0];
	//	m_ddeltac = vs[1];
	//	m_ddeltar = vs[2];
	//	m_ddeltay = vs[3];
	//	m_ddeltaz = vs[4];
	//
	//	m_pfstd=SFlightStatus(0,0,0,0,0,0,0,0,0,0,0,0);
	//	//////////////////////////////////////////////////
	//	/////////////////////////////////////////////////
	//
	//	/////////////////////////////////////////////////
	//EndFollow:
	//	switch(m_iFollowCount)
	//	{
	//	case 4:
	//		m_pfstd.m_dX = m_pfstd.m_dY = m_pfstd.m_dZ = 0;
	//	case 3:
	//		m_pfstd.m_dV = m_pfstd.m_dChi = m_pfstd.m_dGama = 0;
	//	case 2:
	//		m_pfstd.m_dAlpha = m_pfstd.m_dBeta = m_pfstd.m_dMu = 0;
	//	case 1:
	//		m_pfstd.m_dp = m_pfstd.m_dq = m_pfstd.m_dr = 0;
	//		m_iFollowCount--;
	//	}//*/
	////////////////////////////////////////////////
	//方案2:
	//static double ss=0;
	//double ss1 = sqrt((m_dX-x)*(m_dX-x)+(m_dY-y)*(m_dY-y)+(m_dZ-z)*(m_dZ-z));
	//if(ss1>ss) ss=ss1;
	//ss1=ss;
	double tmp;//mark
	double tmp1;

	m_iInputMod = CTL_HERBST_INPUT_XYZ;
	double Gamadmin;
	double khdmax = .4;

	double dBuffer[11];		//done：dbuffer要延长
							//dBuffer[8] = u;
							//dBuffer[9] = v;
							//dBuffer[10] = w;
	dBuffer[0] = m_dInputs[0] = x;
	dBuffer[1] = m_dInputs[1] = y;
	dBuffer[2] = m_dInputs[2] = z + m_ship_dH; //舰体升沉
	m_lpfst = m_pfst;			//赋值给上一回

								//if(m_iInputMod>=CTL_HERBST_INPUT_ABM_V)
								//{
								//	dBuffer[3]=m_dInputs[3];
								//	dBuffer[3] = ( dBuffer[3] - m_dV ) * m_cp.m_dWV; //V导数
								//	dBuffer[3] = m_gvs.Fun_Thrust(dBuffer[0],dBuffer[3]);
								//	if(dBuffer[3]<m_cp.m_dThrustMin) 
								//		dBuffer[3]=m_cp.m_dThrustMin;
								//	else if(dBuffer[3]>m_cp.m_dThrustMax)
								//		dBuffer[3]=m_cp.m_dThrustMax;
								//}
	switch (m_iInputMod)
	{
	case CTL_HERBST_INPUT_XYZ:
		khdmax = 1.0;//mark

		m_pfst.m_dX = dBuffer[0];
		m_pfst.m_dY = dBuffer[1];
		m_pfst.m_dZ = dBuffer[2];

		if (m_iFollowCount < 4)//求微分m_pfstd
		{
			m_pfstd.m_dX = (m_pfst.m_dX - m_lpfst.m_dX) / m_dT;
			m_pfstd.m_dY = (m_pfst.m_dY - m_lpfst.m_dY) / m_dT;
			m_pfstd.m_dZ = (m_pfst.m_dZ - m_lpfst.m_dZ) / m_dT;
		}
		else
		{
			m_pfstd.m_dX = 0;
			m_pfstd.m_dY = 0;
			m_pfstd.m_dZ = 0;
		}

		dBuffer[0] = m_pidX_d(dBuffer[0] - m_dX);
		dBuffer[1] = m_pidY_d(dBuffer[1] - m_dY);
		dBuffer[4] = m_pidZ_d(dBuffer[2] - m_dZ);
		/*	dBuffer[0] = m_pidX_d(dBuffer[0]);
		dBuffer[1] = m_pidY_d(dBuffer[1]);
		dBuffer[4] = m_pidZ_d(dBuffer[2]);*/
		dBuffer[0] = (dBuffer[0]) * m_cp.m_dWX + m_pfstd.m_dX;
		dBuffer[1] = (dBuffer[1]) * m_cp.m_dWY + m_pfstd.m_dY;
		dBuffer[4] = (dBuffer[4]) * m_cp.m_dWZ + m_pfstd.m_dZ;


		/*	dBuffer[0] = (dBuffer[0]-m_dX)*m_cp.m_dWX + m_pfstd.m_dX + m_pidX_d(dBuffer[0] - m_dX);
		dBuffer[1] = (dBuffer[1]-m_dY)*m_cp.m_dWY + m_pfstd.m_dY + m_pidY_d(dBuffer[1] - m_dY);
		dBuffer[4] = (dBuffer[2]-m_dZ)*m_cp.m_dWZ + m_pfstd.m_dZ + m_pidZ_d(dBuffer[2] - m_dZ);*/

		///////////////////////////////////////
		//极慢回路逆系统
		dBuffer[3] = dBuffer[1];
		dBuffer[1] = atan(dBuffer[1] / dBuffer[0]);
		if (dBuffer[0]<0)
		{
			if (dBuffer[1]>0) dBuffer[1] -= PI;
			else if (dBuffer[1]<0) dBuffer[1] += PI;
		}

		//速度生成语句
		/*if(m_dInputs[2] > 0.1)
		{*/
		//速度做xyz分解
		dBuffer[5] = dBuffer[0];			//x轴线速度
		dBuffer[6] = dBuffer[3];			//y轴线速度
		dBuffer[7] = dBuffer[4];			//z轴线速度
		m_pfst.m_Vx = dBuffer[0];
		m_pfst.m_Vy = dBuffer[3];
		m_pfst.m_Vz = dBuffer[4];

		dBuffer[0] = sqrt(dBuffer[5] * dBuffer[5] + dBuffer[6] * dBuffer[6] + dBuffer[7] * dBuffer[7]);		//合速度

																											//三轴线加速度生成语句
																											//dBuffer[5] = (m_pfst.m_Vx - m_lpfst.m_Vx) / m_dT;			//x轴线加速度
																											//dBuffer[6] = (m_pfst.m_Vy - m_lpfst.m_Vy) / m_dT;			//y轴线加速度
																											//dBuffer[7] = (m_pfst.m_Vz - m_lpfst.m_Vz) / m_dT;			//z轴线加速度
																											//m_pfst.m_Accx = dBuffer[5];
																											//m_pfst.m_Accy = dBuffer[6];
																											//m_pfst.m_Accz = dBuffer[7];
																											//}
																											//else
																											//{
																											//	dBuffer[5] = dBuffer[0] + m_ship.m_shiptail_Vx + m_wind.m_Wind_Vx - 1.5;			//x轴线速度
																											//	dBuffer[6] = 0;			//y轴线速度
																											//	dBuffer[7] = 0;			//z轴线速度
																											//	m_pfst.m_Vx = dBuffer[5];
																											//	m_pfst.m_Vy = dBuffer[6];
																											//	m_pfst.m_Vz = dBuffer[7];
																											//	dBuffer[0] = sqrt(dBuffer[5] * dBuffer[5]);		//合速度
																											//	dBuffer[5] = (m_pfst.m_Vx - m_lpfst.m_Vx) / m_dT;			//x轴线加速度
																											//	dBuffer[6] = (m_pfst.m_Vy - m_lpfst.m_Vy) / m_dT;			//y轴线加速度
																											//	dBuffer[7] = (m_pfst.m_Vz - m_lpfst.m_Vz) / m_dT;			//z轴线加速度
																											//	m_pfst.m_Accx = dBuffer[5];
																											//	m_pfst.m_Accy = dBuffer[6];
																											//	m_pfst.m_Accz = dBuffer[7];

																											//}
																											//（暂时废弃）可根据需要使用极慢环生成的数据，或手动指定理想的速度值进行跟踪
																											//if(m_speed_pattern)
																											//	dBuffer[0] = sqrt(dBuffer[0]*dBuffer[0]+dBuffer[3]*dBuffer[3]+dBuffer[4]*dBuffer[4]);		//极慢环生成方式									
																											//else 
																											//	dBuffer[0] = data_expect_speed;	//手动指定方式，单位为m/s


																											///////////////////////////////////////
	case CTL_HERBST_INPUT_VKH:
		tmp1 = m_pidZ_d(dBuffer[2] - m_dZ);
		dBuffer[2] = (dBuffer[2] - m_dZ) * m_cp.m_dWZ + m_pfstd.m_dZ; //计算高度的导数
		dBuffer[2] += tmp1;
		if (fabs(dBuffer[2])>dBuffer[0])
		{
			if (dBuffer[2]>0) dBuffer[2] = dBuffer[0];
			else	dBuffer[2] = -dBuffer[0];
		}
		dBuffer[2] = -asin(dBuffer[2] / dBuffer[0]);//Gamac

	case CTL_HERBST_INPUT_VKG:
		m_pfst.m_dV = dBuffer[0];
		m_pfst.m_dChi = dBuffer[1];
		m_pfst.m_dGama = dBuffer[2];

		if (m_iFollowCount<3)
		{
			m_pfstd.m_dV = (m_pfst.m_dV - m_lpfst.m_dV) / m_dT;
			m_pfstd.m_dChi = (m_pfst.m_dChi - m_lpfst.m_dChi);
			while (m_pfstd.m_dChi>PI) m_pfstd.m_dChi -= 2 * PI;
			while (m_pfstd.m_dChi<-PI) m_pfstd.m_dChi += 2 * PI;
			m_pfstd.m_dChi /= m_dT;
			m_pfstd.m_dGama = (m_pfst.m_dGama - m_lpfst.m_dGama) / m_dT;
		}
		else
		{
			m_pfstd.m_dV = 0;
			m_pfstd.m_dChi = 0;
			m_pfstd.m_dGama = 0;
		}

		dBuffer[0] = (dBuffer[0] - m_dV) * m_cp.m_dWV + m_pfstd.m_dV; //V导数，速度反馈

																	  //-pi<delta_kh<pi
		dBuffer[1] = (dBuffer[1] - m_dChi);//Kh导数
		if (dBuffer[1]>3.1415926535897932384626)
			dBuffer[1] -= ((int)(dBuffer[1] / (3.1415926535897932384626 * 2) + 1))*3.1415926535897932384626 * 2;
		else if (dBuffer[1]<-3.1415926535897932384626)
			dBuffer[1] -= ((int)(dBuffer[1] / (3.1415926535897932384626 * 2) - 1))*3.1415926535897932384626 * 2;
		dBuffer[1] = dBuffer[1] * m_cp.m_dWKh + m_pfstd.m_dChi;
		if (dBuffer[1] > khdmax)
			dBuffer[1] = khdmax;
		else if (dBuffer[1] < -khdmax)
			dBuffer[1] = -khdmax;//KH导数限幅
		tmp = dBuffer[1];//mark


						 //tmp1 = dBuffer[2] - m_dGama;	//Gama误差
						 //tmp1 = m_pidZ_d(dBuffer[2]-m_dZ);
		dBuffer[2] = dBuffer[2] - m_dGama;	//Gama误差
		m_dGama_I += dBuffer[2] * m_dT;		//Gama误差积分
		if (m_dGama_I > m_cp.m_dGama_IMax) m_dGama_I = m_cp.m_dGama_IMax;
		else if (m_dGama_I < -m_cp.m_dGama_IMax) m_dGama_I = -m_cp.m_dGama_IMax;//积分饱和
		dBuffer[2] = dBuffer[2] * m_cp.m_dWGama + m_dGama_I * m_cp.m_dWGama_I + m_pfstd.m_dGama;//Gama导数

		Gamadmin = (2.0 - m_dg*cos(m_dGama)) / m_dV;//防失重
		if (dBuffer[2]<Gamadmin)
			dBuffer[2] = Gamadmin;
		else if (dBuffer[2]>-Gamadmin)
			dBuffer[2] = -Gamadmin;//

	case CTL_HERBST_INPUT_DVKG:
		m_gvs.Input(dBuffer);//V_d,Kh_d,H_d
		m_gvs.Update();
		m_gvs.Output(dBuffer);//Alphac,Betac,Muc,Thrust
	case CTL_HERBST_INPUT_ABM_V:;
	}
	//下面开始Alphac,Betac,Muc,Thrust输入到慢回路控制器
	if (dBuffer[3]<m_cp.m_dThrustMin)
		dBuffer[3] = m_cp.m_dThrustMin;
	else if (dBuffer[3]>m_cp.m_dThrustMax)
		dBuffer[3] = m_cp.m_dThrustMax;

	m_dThrustc = dBuffer[3];

	if (dBuffer[0] > 1)
		dBuffer[0] = 1;
	else if (dBuffer[0] < -1)
		dBuffer[0] = -1;

	m_pfst.m_dAlpha = dBuffer[0];
	m_pfst.m_dBeta = dBuffer[1];
	m_pfst.m_dMu = dBuffer[2];
	if (m_iFollowCount<2)
	{
		m_pfstd.m_dAlpha = (m_pfst.m_dAlpha - m_lpfst.m_dAlpha) / m_dT;
		m_pfstd.m_dBeta = (m_pfst.m_dBeta - m_lpfst.m_dBeta) / m_dT;
		m_pfstd.m_dMu = (m_pfst.m_dMu - m_lpfst.m_dMu);
		while (m_pfstd.m_dMu>PI) m_pfstd.m_dMu -= 2 * PI;
		while (m_pfstd.m_dMu<-PI) m_pfstd.m_dMu += 2 * PI;
		m_pfstd.m_dMu /= m_dT;

	}
	else
	{
		m_pfstd.m_dAlpha = 0;
		m_pfstd.m_dBeta = 0;
		m_pfstd.m_dMu = 0;
	}

	//todo：船姿态角转气流角

	dBuffer[0] = (dBuffer[0] - m_dAlpha) * m_cp.m_dWAlpha + m_pfstd.m_dAlpha; //Alpha导数
	dBuffer[1] = (dBuffer[1] - m_dBeta) * m_cp.m_dWBeta + m_pfstd.m_dBeta; //Beta导数
	dBuffer[2] = (dBuffer[2] - m_dMu) * m_cp.m_dWMu + m_pfstd.m_dMu;//Mu导数
	m_gs.Input(dBuffer);//Alpha_d,Beta_d,Mu_d,Thrust
	m_gs.Update();
	m_gs.Output(dBuffer);//pc,qc,rc//
						 //角速度
	dBuffer[0] += m_ship_p / (data_time / 1000);//横滚补偿
	dBuffer[1] += m_ship_q / (data_time / 1000);//俯仰补偿

	m_pfst.m_dp = dBuffer[0];
	m_pfst.m_dq = dBuffer[1];
	m_pfst.m_dr = dBuffer[2];
	//角加速度
	//dBuffer[5] = (m_pfst.m_dp - m_lpfst.m_dp) / m_dT;
	//dBuffer[6] = (m_pfst.m_dq - m_lpfst.m_dq) / m_dT;
	//dBuffer[7] = (m_pfst.m_dr - m_lpfst.m_dr) / m_dT;
	//m_pfst.m_Accp = dBuffer[5];
	//m_pfst.m_Accq = dBuffer[6];
	//m_pfst.m_Accr = dBuffer[7];

	if (m_iFollowCount<1)
	{
		//		m_pfstd.m_dp = (m_pfst.m_dp - m_lpfst.m_dp)/m_dT;
		//		m_pfstd.m_dq = (m_pfst.m_dq - m_lpfst.m_dq)/m_dT;
		//		m_pfstd.m_dr = (m_pfst.m_dr - m_lpfst.m_dr)/m_dT;
	}
	else
	{
		m_iFollowCount--;
		m_pfstd.m_dp = 0;
		m_pfstd.m_dq = 0;
		m_pfstd.m_dr = 0;
	}


	dBuffer[0] = (dBuffer[0] - m_dp) * m_cp.m_dWp + m_pfstd.m_dp; //pc
	dBuffer[1] = (dBuffer[1] - m_dq) * m_cp.m_dWq + m_pfstd.m_dq; //qc
	dBuffer[2] = (dBuffer[2] - m_dr) * m_cp.m_dWr + m_pfstd.m_dr; //rc

																  //----------------------------------------------------------------------------------------------------------------------------------------------
																  ////接受母舰给的欧拉角及其角速率
																  ////母舰俯仰角thetamj ;				母舰偏航角psimj ;					 母舰滚转角phimj
																  ////母舰俯仰角速率dthetamj ;		母舰偏航角速率dpsimj ;		     母舰滚转角速率dphimj
																  ////则产生的机体坐标轴的三个角速度分两pmj， qmj， rmj为
																  //pmj=dphimj-dpsimj*sin(thetamj);
																  //qmj=dthetamj*cos(phimj)+dpsimj*cos(thetamj)*sin(phimj);
																  //rmj=-dthetamj*sin(phimj)+dpsimj*cos(thetamj)*cos(phimj)
																  ////再把pmj加到dBuffer[0] ，qmj加到dBuffer[1] ，rmj加到dBuffer[2] 产生新的dBuffer
																  //dBuffer[0]+=pmj; //新的pc
																  //dBuffer[1]+=qmj; //新的qc
																  //dBuffer[2]+=rmj; //新的rc
																  //----------------------------------------------------------------------------------------------------------------------------------------------

	m_gf.Input(dBuffer);//pc,qc,rc,Thrust
	m_gf.Update();
	m_gf.Output(dBuffer);//deltaa,deltac,deltar,deltay,deltaz;//

	m_ddeltaa = dBuffer[0];
	m_ddeltac = dBuffer[1];
	m_ddeltar = dBuffer[2];
	m_ddeltay = dBuffer[3];
	m_ddeltaz = dBuffer[4];

	m_pfstd = SFlightStatus(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);//
	return 0;
}



