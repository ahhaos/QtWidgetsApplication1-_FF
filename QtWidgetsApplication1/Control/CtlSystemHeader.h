#pragma once
#define CTL_ERROR_NONCHARALINE		0x1001
#define	CTL_ERROR_ALPHAC_INVALID	0x1002
#ifndef PI
#define PI 3.1415926535892932384626
#endif

#include "..\global.h"

enum
{
	CTL_HERBST_INPUT_XYZ = 1,
	CTL_HERBST_INPUT_VKH,	//速度、方位角、高度输入方式
	CTL_HERBST_INPUT_VKG,
	CTL_HERBST_INPUT_DVKG,		//速度变、方位角、俯仰角导数输入          //G应该是倾斜角
	CTL_HERBST_INPUT_ABM_V,
	CTL_HERBST_INPUT_XYZ_V,		//坐标、速度输入
	CTL_HERBST_INPUT_Manual
};
struct SControllerParams
{
	double m_dWp;
	double m_dWq;
	double m_dWr;

	double m_dWAlpha;
	double m_dWBeta;
	double m_dWMu;
	double m_dMu_dT;//Mu导数传递函数时间常数
	double m_dMu_dMax;//Mu导数幅限

	double m_dWV;
	double m_dThrustMax;	//最大推力
	double m_dThrustMin;	//最小推力
	double m_dWKh;
	double m_dKh_dMax;		//最大转转向速度
	double m_dWGama;
	double m_dWGama_I;
	double m_dGama_IMax;//积分饱和

	double m_dWX;
	double m_dWY;
	double m_dWZ;
	SControllerParams::SControllerParams()
	{
		DefaultSet();
	}
	void DefaultSet()//默认设置
	{


		m_dWp = data_bandwidth_dWp;
		m_dWq = data_bandwidth_dWq;
		m_dWr = data_bandwidth_dWr;//改带宽  10

		/*m_dWAlpha=1.5;
		m_dWBeta=2;
		m_dWMu=1.8;*/

		m_dWAlpha = data_bandwidth_dWAlpha;
		m_dWBeta = data_bandwidth_dWBeta;
		m_dWMu = data_bandwidth_dWMu;
		m_dWV = data_bandwidth_dWV;
		m_dWKh = data_bandwidth_dWKh;
		m_dWGama = data_bandwidth_dWGama;
		m_dWX = data_bandwidth_dWX;
		m_dWY = data_bandwidth_dWY;
		m_dWZ = data_bandwidth_dWX;

		m_dThrustMax = data_model_dThrustMax;
		m_dThrustMin = data_model_dThrustMin;
		m_dKh_dMax = 0.2;
		m_dWGama_I = 0.05;
		m_dMu_dT = 4;
		m_dMu_dMax = 2.5;
		m_dGama_IMax = PI / 8;
	}


	SControllerParams operator=(SControllerParams sp)
	{
		m_dWp = sp.m_dWp;
		m_dWq = sp.m_dWq;
		m_dWr = sp.m_dWr;

		m_dWAlpha = sp.m_dWAlpha;
		m_dWBeta = sp.m_dWBeta;
		m_dWMu = sp.m_dWMu;
		m_dMu_dT = sp.m_dMu_dT;
		m_dMu_dMax = sp.m_dMu_dMax;

		m_dWV = sp.m_dWV;
		m_dWKh = sp.m_dWKh;
		m_dWGama = sp.m_dWGama;
		m_dWGama_I = sp.m_dWGama_I;

		m_dWX = sp.m_dWX;
		m_dWY = sp.m_dWY;
		m_dWZ = sp.m_dWZ;
		return *this;
	}
};

//PID类
class CPID
{
	bool   m_bDAvaliable;
	double m_dLastInput;
	double m_dIntegral;
	double m_dT;
public:
	double m_dILimit;
	double m_dK[3];
	CPID() :m_dLastInput(0.0), m_dIntegral(0.0), m_bDAvaliable(false), m_dT(0.1), m_dILimit(-1.0)
	{
		m_dK[0] = m_dK[1] = m_dK[2] = 0.0;

	}

	void Reset()
	{
		m_dLastInput = 0;
		m_dIntegral = 0;
	}
	void SetT(double dT)
	{
		if (dT < 0) return;
		m_dT = dT;
	}
	void Initialize(double dT, double dK[3], double dILimit = -1.0)
	{
		SetT(dT);
		m_dILimit = dILimit;
	}
	void SetControlParams(double dK[3])
	{
		m_dK[0] = dK[0];
		m_dK[1] = dK[1];
		m_dK[2] = dK[2];
	}
	double operator()(double e)
	{
		double d = 0;
		if (m_bDAvaliable)
		{
			d = (e - m_dLastInput) / m_dT;
		}
		m_dLastInput = e;
		m_bDAvaliable = true;
		m_dIntegral += e * m_dT;
		if (m_dILimit > 0)
		{
			if (m_dIntegral > m_dILimit) m_dIntegral = m_dILimit;
			else if (m_dIntegral < -m_dILimit) m_dIntegral = -m_dILimit;
		}
		return e * m_dK[0] + m_dIntegral * m_dK[1] + d * m_dK[2];
	}
};