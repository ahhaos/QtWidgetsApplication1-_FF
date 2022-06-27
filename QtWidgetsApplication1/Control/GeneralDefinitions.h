#if !defined GENERA_DEFINITIONS
#define GENERA_DEFINITIONS

#pragma once
#ifndef PI
#define PI 3.1415926535897932384626
#endif

#ifndef KSCAlE
#define KSCAlE 1000
#endif

//������̬�������
struct att
{
	//��̬������
	double dtheta;
	double dphi;
	double dpsi;
	//��̬�Ǽ��ٶ�
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
	double m_comb_deltaY;		//�����ƫ��
	double m_comb_deltaZ;		//����ƫ��
	int m_comb_valid;
	comb();
	comb(double deltaX, double deltaY, double deltaZ, int valid);
};





struct SStaticParams	//��̬����
{
	//��������
	double m_dg;	//�������ٶ�g
	double m_dRho;	//�����ܶ�

	//�ɻ�����
	double m_dM;	//�ɻ�����
	double m_dS;	//�������
	double m_db;	//����չ��
	double m_dC_;	//ƽ������������
	double m_dxT;	//��������ܾ����ľ���
	double m_da_max;//��������
	double m_dr_max;//��������
	double m_dc_max;//Ѽ������
	double m_dy_max;//����ʸ�������
	double m_dz_max;//����ʸ�������
	//ת������
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


struct SFlightStatus	//����״̬
{
	//
 //	int drawspeed;

	double m_dX;		//��������ϵX����
	double m_dY;		//��������ϵY����
	double m_dZ;		//��������ϵZ����
	double m_dV;		//�����ٶ�
	double m_dChi;		//������λ��
	double m_dGama;		//����������
	double m_dAlpha;	//ӭ��
	double m_dBeta;		//�໬��
	double m_dMu;		//��ת��
	double m_dp;		//��ת���ٶ�
	double m_dq;		//�������ٶ�
	double m_dr;		//ƫ�����ٶ�

	double m_dtheta;     //������
	double m_dpsi;      //ƫ����
	double m_dphi;       //��ת��

	double m_dVtheta;
	double m_dVphi;
	double m_dVpsi;

	double m_Vx;         //x�����ٶ�
	double m_Vy;         //y�����ٶ�
	double m_Vz;         //z�����ٶ�

	double m_Accx;		//x�����߼��ٶ�
	double m_Accy;		//y�����߼��ٶ�
	double m_Accz;		//z�����߼��ٶ�

	double m_Accp;		//��ת�Ǽ��ٶ�
	double m_Accq;		//�����Ǽ��ٶ�
	double m_Accr;		//ƫ���Ǽ��ٶ�

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
	double m_dX;		//��������ϵX����(m)
	double m_dY;		//��������ϵY����(m)
	double m_dZ;		//��������ϵZ����(m)
	double m_dbu;		//X�����ٶ�(b:��������ϵ,m/s)
	double m_dbv;		//Y�����ٶ�(b:��������ϵ,m/s)
	double m_dbw;		//Z�����ٶ�(b:��������ϵ,m/s)
	double m_dpsi;		//ƫ����(rad)
	double m_dtheta;	//������(rad)
	double m_dphi;		//��ת��(rad)
	double m_dp;		//��ת��(rad/s)
	double m_dq;		//������(rad/s)
	double m_dr;		//ƫ����(rad/s)
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


struct SControlVolumes	//������
{
	//5�����ƶ���ƫ��
	double m_ddeltaa;	//����ƫ��
	double m_ddeltac;	//Ѽ���ƫ��
	double m_ddeltar;	//�����ƫ��
	double m_ddeltay;	//����ʸ��ƫ��
	double m_ddeltaz;	//����ʸ��ƫ��
	//����
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
	//���±������ڱ��������ȱ��
	const int C_L;			//00����ϵ��
	const int C_D;			//01����ϵ��
	const int C_ldeltaa;	//02����	����Ĺ�ת����ϵ��
	const int C_ldeltac;	//03Ѽ��� ����Ĺ�ת����ϵ��
	const int C_ldeltar;	//04����� ����Ĺ�ת����ϵ��
	const int C_lp;			//05��ת�� ����Ĺ�ת����ϵ��
	const int C_lr;			//06ƫ���� ����Ĺ�ת����ϵ��
	const int C_lbeta;		//07�໬�� ����Ĺ�ת����ϵ��
	const int C_mo;			//08��������ϵ��
	const int C_mdeltac;	//09Ѽ��� ����ĸ�������ϵ��
	const int C_mq;			//10�������ٶ� ����ĸ�������ϵ��
	const int C_ndeltaa;	//11���� �����ƫ������ϵ��
	const int C_ndeltar;	//12����� �����ƫ������ϵ��
	const int C_np;			//13��ת�� �����ƫ������ϵ��
	const int C_nr;			//14ƫ���� �����ƫ������ϵ��
	const int C_nbeta;		//15�໬�� �����ƫ������ϵ��
	const int C_ydeltaa;	//16���� ����Ĳ���ϵ��
	const int C_ydeltar;	//17����� ����Ĳ���ϵ��
	const int C_ybeta;		//18�໬�� ����Ĳ���ϵ��
	const int delta_c0;		//19Ѽ��ƫ�����λ��
	CCharaLine();
	virtual double operator()(int iSelect,	//�����߱��
		double x		//alphaֵ
		);	//�����߶�ȡ����
	virtual bool ChenckAlpha(double alpha,	//������alphaֵ
		double& AvailableAlpha//������Ч��alphaֵ
	);	//�����alpha����Ч�Լ�飬
		//��alphaֵ������Ч��Χ���򷵻�false
};


struct SFlightAttitude
{
	double m_dPsi;
	double m_dTheta;
	double m_dPhi;
	SFlightAttitude();
	SFlightAttitude(double dPsi, double dTheta, double dPhi);
	SFlightAttitude(const double mT[3][3]);
	void mT2Angle(const double mT[3][3]);			//�任���󵽽Ƕ�
	void Angle2mT(double mT[3][3]);					//�Ƕȵ��任����
	SFlightAttitude operator=(SFlightAttitude fat);
	SFlightAttitude operator=(SFlightStatus fst);	//����״̬����̬��	
	SFlightAttitude operator+(SFlightAttitude fat);	//����任���
	SFlightAttitude operator-(SFlightAttitude fat);	//����任���
};


struct SRestrictions
{
	double m_dH_Max;		//�������(20000m)
	double m_dH_Min;		//��С��ȫ���и߶�
	double m_dThrust_Max;	//�������
	double m_dThrust_Min;	//��С����
	double m_dV_Max;		//���ȫ�����ٶ�
	double m_dV_Min;		//��С��ȫ�����ٶ�
	double m_dRadius_Min;	//��Сת��뾶
	double m_dGamma_Max;	//������󺽼����
	double m_dNG_Max;		//�����ؼ��ٶ�
	double m_dBeta_Max;		//���໬��

	double m_dp_Max;		//�������ת���ٶ�
	double m_dq_Max;		//����������ٶ�
	double m_dr_Max;		//������ƫ�����ٶ�
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
	double		m_dT;	//��������
	CCharaLine* m_pCL;	//������ָ��
public:
	void GetStaticParams(SStaticParams& sp);	//��ȡ��̬����
	void GetFlightStatus(SFlightStatus& fs);	//��ȡ����״̬
	void GetControlVolumes(SControlVolumes& cv);	//��ȡ������
	void SetStaticParams(SStaticParams sp);		//���÷��в���
	void SetFlightStatus(SFlightStatus fs);		//���÷���״̬
	void SetControlVolumes(SControlVolumes cv);	//���ÿ�����
	CGeneralModel();
	CGeneralModel(SStaticParams Static, SFlightStatus Status,
		SControlVolumes Control, CCharaLine* pCL, double dT);
	CGeneralModel operator =(CGeneralModel Model);//��ֵ����
	void SetCharaLine(CCharaLine* pCL);	//����������
	void SetT(double dT);	//���÷�������
};
#endif