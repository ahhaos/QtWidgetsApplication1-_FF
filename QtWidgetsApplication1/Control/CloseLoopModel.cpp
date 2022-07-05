// CloseLoopModel.cpp: implementation of the CCloseLoopModel class.
//
//////////////////////////////////////////////////////////////////////


//#include "Terrain3DTest.h"
#include "CloseLoopModel.h"
#include <QDebug>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCloseLoopModel::CCloseLoopModel()
{
	//m_cl.LoadCharaLine();

	//SStaticParams sp(9.8, 1.11164, 10617, 57.7, 13.11, 4.40,
	//	30, 30, 90, 30, 30,
	//	8.50, 22682, 77095, 95561, 1125);
	//SFlightStatus fs;

	//m_fst.m_dX = data_origin_X;
	//m_fst.m_dY = data_origin_Y;
	//m_fst.m_dZ = data_origin_Z;
	//m_fst.m_dV = data_origin_V;
	//m_fst.m_dAlpha = data_origin_Alpha;
	//m_fst.m_dGama = data_origin_Gama;
	//m_fst.m_dChi = data_origin_Chi;
	//m_fst.m_dBeta = data_origin_Beta;
	//m_fst.m_dMu = data_origin_Mu;
	//m_fst.m_dp = data_origin_p;
	//m_fst.m_dq = data_origin_q;
	//m_fst.m_dr = data_origin_r;

	//m_ctler.SetStaticParams(sp);
	//m_ctler.FeedBack(m_fst);
	//m_ctler.SetCharaLine(&m_cl);
	//m_ctler.SetT(data_time / 1000);

	//m_mdl.SetStaticParams(sp);
	//m_mdl.SetFlightStatus(m_fst);
	//m_mdl.SetCharaLine(&m_cl);
	//m_mdl.SetT(data_time / 1000);

	///*m_ctl[0] = 100;
	//m_ctl[1] = 0;
	//m_ctl[2] = m_fst.m_dZ;*/
	//m_dT = data_time / 1000;

	///*m_ctler.m_cp.m_dWX=0.5;
	//m_ctler.m_cp.m_dWY=0.5;
	//m_ctler.m_cp.m_dWZ=0.5;
	//m_ctler.m_cp.m_dWKh=0.8;*/

	////m_bfollow = false;
}

CCloseLoopModel::~CCloseLoopModel()
{

}

void CCloseLoopModel::initState()
{
	qDebug() << "Close Loop Init State";
	m_cl.LoadCharaLine();

	SStaticParams sp(9.8, 1.11164, 10617, 57.7, 13.11, 4.40,
		30, 30, 90, 30, 30,
		8.50, 22682, 77095, 95561, 1125);
	SFlightStatus fs;
	m_fst.m_dX = data_origin_X;
	m_fst.m_dY = data_origin_Y;
	m_fst.m_dZ = data_origin_Z;
	m_fst.m_dV = data_origin_V;
	m_fst.m_dAlpha = data_origin_Alpha;
	m_fst.m_dGama = data_origin_Gama;
	m_fst.m_dChi = data_origin_Chi;
	m_fst.m_dBeta = data_origin_Beta;
	m_fst.m_dMu = data_origin_Mu;
	m_fst.m_dp = data_origin_p;
	m_fst.m_dq = data_origin_q;
	m_fst.m_dr = data_origin_r;

	m_ctler.SetStaticParams(sp);
	m_ctler.FeedBack(m_fst);
	m_ctler.SetCharaLine(&m_cl);
	m_ctler.SetT(data_time / 1000);

	m_mdl.SetStaticParams(sp);
	m_mdl.SetFlightStatus(m_fst);
	m_mdl.SetCharaLine(&m_cl);
	m_mdl.SetT(data_time / 1000);

	/*m_ctl[0] = 100;
	m_ctl[1] = 0;
	m_ctl[2] = m_fst.m_dZ;*/
	m_dT = data_time / 1000;

	/*m_ctler.m_cp.m_dWX=0.5;
	m_ctler.m_cp.m_dWY=0.5;
	m_ctler.m_cp.m_dWZ=0.5;
	m_ctler.m_cp.m_dWKh=0.8;*/

	//m_bfollow = false;



}

void CCloseLoopModel::Level()
{
	m_ctler.m_iInputMod = CTL_HERBST_INPUT_VKG;
	m_ctl[0] = m_fst.m_dV,
		m_ctl[1] = m_fst.m_dChi,
		m_ctl[2] = 0;
	//m_bfollow = false;
}

void CCloseLoopModel::Input_VKG(double vc, double khc, double gc)
{
	m_ctler.m_iInputMod = CTL_HERBST_INPUT_VKG;
	m_ctl[0] = vc,
	m_ctl[1] = khc,
	m_ctl[2] = gc;
}

//int CCloseLoopModel::Update(double x,double y,double z,double m_ship_dH,double m_ship_roll,double m_ship_pitch,double m_shiptail_Vx,double m_shiptail_Vy,double m_shiptail_Vz);
//{
//	
//	if(m_bfollow)
//	{
//		m_ctler.Follow(m_ctl[0],m_ctl[1],m_ctl[2],m_ctl[4],m_ctl[5],m_ctl[6],m_ctl[7],m_ctl[8],m_ctl[9]);
//		if(m_ctler.m_iFollowCount>0) return 1;
//	}
//	else
//	{
//		m_ctler.Input(m_ctl);//m_iFollowCount=4;  m_iInputMod = CTL_HERBST_INPUT_VKH;//Ĭ��vkh
//	}
//	//m_ctler.Update();//mark  //ע��
//	//m_ctler.Follow(x,y,z);//mark
//	m_ctler.Output(m_cv);
//
//	m_mdl.SetControlVolumes(m_cv);
//	m_mdl.Update();
//	m_mdl.GetFlightStatus(m_fst);
//
//	m_ctler.FeedBack(m_fst);
//	return 0;
//}
//
//void CCloseLoopModel::Follow(double x,double y,double z,double m_ship_dH,double m_ship_roll,double m_ship_pitch,double m_shiptail_Vx,double m_shiptail_Vy,double m_shiptail_Vz);
//{
//	m_bfollow = true;
//	m_ctl[0]=x;
//	m_ctl[1]=y;
//	m_ctl[2]=z;
//	m_ctl[4] = m_ship_dH;
//	m_ctl[5] = m_ship_roll;
//	m_ctl[6] = m_ship_pitch;
//	m_ctl[7] = m_shiptail_Vx;
//	m_ctl[8] = m_shiptail_Vy;
//	m_ctl[9] = m_shiptail_Vz;
//
//
//}

/*******************************************************
��������int CCloseLoopModel::Update
���룺 ��
���ܣ��ջ�ϵͳ����
********************************************************/
int CCloseLoopModel::Update()
{

	//if (m_bfollow)
	//{
		//qDebug() << "m_bfollow";
		//m_ctler.Follow(m_ctl[0], m_ctl[1], m_ctl[2], m_ctl[4], m_ctl[5], m_ctl[6]/*,m_ctl[7],m_ctl[8],m_ctl[9]*/);
		//double temp[3] = {70,0.0,2800};
		//m_ctler.m_iInputMod = CTL_HERBST_INPUT_VKH;
		//m_ctler.Input(temp);
		m_ctler.Input(m_ctl);
		
		//qDebug() << m_ctl[0] << ";" << m_ctl[1] << ";" << m_ctl[2] << ";" << m_ctl[3];
		m_ctler.Update_XYZV();

		//double temp[3] = { x,y,z };
		//m_ctler.m_iInputMod = CTL_HERBST_INPUT_XYZ;
		//m_ctler.Input(temp);
		//m_ctler.Update_1(x, y, z);
		//if(m_ctler.m_iFollowCount>0) return 1;//ע�ͺ���ǰ��������x���ܸ���xc�����⣬x����Ϊֱ�ߵ�����
	//}
	//else
	//{
	//	qDebug() << "no_m_bfollow";
	//	m_ctler.Input(m_ctl);//m_iFollowCount=4;  m_iInputMod = CTL_HERBST_INPUT_VKH;//Ĭ��vkh
	//}
	//m_ctler.Update();//mark  //ע��
	//m_ctler.Follow(x,y,z);//mark
	m_ctler.Output(m_cv);				//����õ�������m_cv

	m_mdl.SetControlVolumes(m_cv);		//���ÿ�����Ϊm_cv
	m_mdl.Update();						//����ɻ���״̬
	m_mdl.GetFlightStatus(m_fst);		//��״̬��ֵ��m_fst

	m_ctler.FeedBack(m_fst);			//��״̬��������������׼����һ�ν��㣿����
	return 0;
}

/*******************************************************
��������int CCloseLoopModel::Update
���룺x,y,z,���ɻ���λ�ã�����״̬��
���ܣ��ջ�ϵͳ����
********************************************************/
int CCloseLoopModel::Update(double x, double y, double z, double m_ship_dH, double m_ship_p, double m_ship_q/*,double m_shiptail_Vx,double m_shiptail_Vy,double m_shiptail_Vz*/)
{


	m_ctler.Follow(m_ctl[0], m_ctl[1], m_ctl[2], m_ctl[4], m_ctl[5], m_ctl[6]/*,m_ctl[7],m_ctl[8],m_ctl[9]*/);
		//if(m_ctler.m_iFollowCount>0) return 1;//ע�ͺ���ǰ��������x���ܸ���xc�����⣬x����Ϊֱ�ߵ�����

	//m_ctler.Update();//mark  //ע��
	//m_ctler.Follow(x,y,z);//mark
	m_ctler.Output(m_cv);

	m_mdl.SetControlVolumes(m_cv);
	m_mdl.Update();
	m_mdl.GetFlightStatus(m_fst);

	m_ctler.FeedBack(m_fst);
	return 0;
}

/*******************************************************
��������int CCloseLoopModel::Update_Manual
���룺 ��
���ܣ��ջ�ϵͳ����(�ֶ�ģʽ�������������)
********************************************************/
int CCloseLoopModel::Update_Manual()
{



	m_cv.m_ddeltaa = m_ctl[0];
	m_cv.m_ddeltac = m_ctl[1];
	m_cv.m_ddeltar = m_ctl[2];
	m_cv.m_dThrustc = m_ctl[3];

	//qDebug() << "cv_a" << m_cv.m_ddeltaa << "cv_e" << m_cv.m_ddeltac << "cv_r" << m_cv.m_ddeltar << "cv_t" << m_cv.m_dThrustc;
	m_mdl.SetControlVolumes(m_cv);		//���ÿ�����Ϊm_cv
	m_mdl.Update();						//����ɻ���״̬
	m_mdl.GetFlightStatus(m_fst);		//��״̬��ֵ��m_fst

	m_ctler.FeedBack(m_fst);			//��״̬��������������׼����һ�ν��㣿����
	return 0;
}

/*******************************************************
��������void CCloseLoopModel::Follow
���룺x,y,z,���ɻ���λ�ã�����״̬��
���ܣ���ֵ��������λ��־λ
********************************************************/
void CCloseLoopModel::Follow(double x, double y, double z, double m_ship_dH, double m_ship_p, double m_ship_q/*,double m_shiptail_Vx,double m_shiptail_Vy,double m_shiptail_Vz*/)
{
	//m_bfollow = true;
	m_ctler.m_iInputMod = CTL_HERBST_INPUT_XYZ;
	m_ctl[0] = x;
	m_ctl[1] = y;
	m_ctl[2] = z;
	m_ctl[4] = m_ship_dH;
	m_ctl[5] = m_ship_p;
	m_ctl[6] = m_ship_q;
	/*m_ctl[7] = m_shiptail_Vx;
	m_ctl[8] = m_shiptail_Vy;
	m_ctl[9] = m_shiptail_Vz;*/


}

/*******************************************************
��������void CCloseLoopModel::Input_VKHdouble vc, double khc, double hc)
���룺v,kh,h
���ܣ�v,kh,h���뷽ʽ
********************************************************/
void CCloseLoopModel::Input_VKH(double vc, double khc, double hc)
{
	m_ctler.m_iInputMod = CTL_HERBST_INPUT_VKH;
	m_ctl[0] = vc;
	m_ctl[1] = khc;
	m_ctl[2] = hc;

}

void CCloseLoopModel::Input_DVKG(double dvc, double dkhc, double dhc)
{
	m_ctler.m_iInputMod = CTL_HERBST_INPUT_DVKG;
	m_ctl[0] = dvc;
	m_ctl[1] = dkhc;
	m_ctl[2] = dhc;
}


/*******************************************************
��������void CCloseLoopModel::Input_XYZ(double xc, double yc, double zc)
���룺x,y,z,�ɻ�������λ��
���ܣ�x,y,z,���뷽ʽ
********************************************************/
void CCloseLoopModel::Input_XYZ(double xc, double yc, double zc)
{
	//m_ctler.m_iInputMod = CTL_HERBST_INPUT_XYZ;//�Ѿ���ʼ��
	m_ctl[0] = xc;
	m_ctl[1] = yc;
	m_ctl[2] = zc;
}

/*******************************************************
��������void CCloseLoopModel::Input_XYZ_V(double xc, double yc, double zc, double V)
���룺x,y,z,V�ɻ�������λ�ú��ٶ�
���ܣ�x,y,z,V���뷽ʽ
********************************************************/
void CCloseLoopModel::Input_XYZ_V(double xc, double yc, double zc,double V)
{
	m_ctler.m_iInputMod = CTL_HERBST_INPUT_XYZ_V;//�Ѿ���ʼ��
	
	m_ctl[0] = xc;
	m_ctl[1] = yc;
	m_ctl[2] = zc;
	m_ctl[3] = V;
}

/*******************************************************
��������void CCloseLoopModel::Input_Manual(double aileron, double elevator, double rudder)
���룺aileron,  elevator,  rudder�ɻ��Ķ���
���ܣ�aileron,  elevator,  rudder���뷽ʽ
********************************************************/
void CCloseLoopModel::Input_Manual(double aileron, double elevator, double rudder,double throttle)
{
	m_ctler.m_iInputMod = CTL_HERBST_INPUT_Manual;//�Ѿ���ʼ��
	m_ctl[0] = aileron;
	m_ctl[1] = elevator;
	m_ctl[2] = rudder;
	m_ctl[3] = throttle;
	//qDebug() << "cv_a" << m_ctl[0] << "cv_e" << m_ctl[1] << "cv_r" << m_ctl[2] << "cv_t" << m_ctl[3];
}




/*******************************************************
��������void CCloseLoopModel::GetFlightStatus(double *pfst)
���룺ָ��
���ܣ���ȡ�ɻ�״̬
********************************************************/
void CCloseLoopModel::GetFlightStatus(double* pfst)
{
	*(SFlightStatus*)(pfst) = m_fst;
}

void CCloseLoopModel::GetControlStatus(double* pfstc)
{
	*(SFlightStatus*)(pfstc) = m_ctler.m_fstc;
}

/*******************************************************
��������void CCloseLoopModel::GetControlVolumes(double *pcv)
���룺ָ��
���ܣ���ȡ�ɻ��Ķ��������
********************************************************/
void CCloseLoopModel::GetControlVolumes(double* pcv)
{
	*(SControlVolumes*)(pcv) = m_cv;
}

/*******************************************************
��������double CCloseLoopModel::GetT()
���룺void
���ܣ���ȡ����ֵ
********************************************************/
double CCloseLoopModel::GetT()
{
	return m_dT;
}

/*******************************************************
��������void CCloseLoopModel::SetT(double dT)
���룺����ֵ
���ܣ���������ֵ
********************************************************/
void CCloseLoopModel::SetT(double dT)
{
	m_dT = dT;
	m_mdl.SetT(m_dT);
	m_ctler.SetT(m_dT);
}

/*******************************************************
��������void CCloseLoopModel::SetFlightStatus(double* pfst)
���룺ָ��
���ܣ����÷ɻ�״̬
********************************************************/
void CCloseLoopModel::SetFlightStatus(double* pfst)
{
	m_fst = *((SFlightStatus*)pfst);
	m_mdl.SetFlightStatus(*(SFlightStatus*)pfst);
	m_ctler.FeedBack(*(SFlightStatus*)pfst);
}

/*******************************************************
��������void CCloseLoopModel::GetStaticParams(double *psp)
���룺ָ��
���ܣ���ȡ�ɻ���̬����
********************************************************/
void CCloseLoopModel::GetStaticParams(double* psp)
{
	if (!psp) return;
	SStaticParams sp;
	m_mdl.GetStaticParams(sp);
	*(SStaticParams*)psp = sp;
}

/*******************************************************
��������void CCloseLoopModel::SetStaticParams(double *psp)
���룺ָ��
���ܣ����÷ɻ���̬����
********************************************************/
void CCloseLoopModel::SetStaticParams(double* psp)
{
	if (!psp) return;
	m_mdl.SetStaticParams(*(SStaticParams*)psp);
	m_ctler.SetStaticParams(*(SStaticParams*)psp);
}



void CCloseLoopModel::Input_Attitude(double dpsi, double dtheta, double dphi)
{

}

/*******************************************************
��������void CCloseLoopModel::Input_Vc(double vc)
���룺�ٶȸ���
���ܣ������ٶȸ���
********************************************************/
void CCloseLoopModel::Input_Vc(double vc)
{
	m_ctler.m_iInputMod = CTL_HERBST_INPUT_VKH;
	m_ctl[0] = vc;
}

/*******************************************************
��������void CCloseLoopModel::Input_Kc(double khc)
���룺��λ�Ǹ���
���ܣ����÷�λ�Ǹ���
********************************************************/
void CCloseLoopModel::Input_Kc(double khc)
{
	m_ctler.m_iInputMod = CTL_HERBST_INPUT_VKH;
	m_ctl[1] = khc;
}

/*******************************************************
��������void CCloseLoopModel::Input_Hc(double hc)
���룺�߶ȸ���
���ܣ����ø߶ȸ���
********************************************************/
void CCloseLoopModel::Input_Hc(double hc)
{
	m_ctler.m_iInputMod = CTL_HERBST_INPUT_VKH;
	m_ctl[2] = hc;
}
