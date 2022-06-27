
#include "Read_txt.h"
#include "math.h"
#include "global.h"
#define  PI 3.141592653



CRead_txt::CRead_txt(void)
{
}
CRead_txt::~CRead_txt(void)
{
}

//������ԭ��ĵ�������
/*******************************************************
��������void CRead_txt::yuandian(double lamma,double phi,double h)
���룺lamma���ȣ�phiiγ�ȣ�h�߶�
���ܣ���ⶫ����ԭ��ĵ�������
********************************************************/
void CRead_txt::yuandian(double lamma,double phi,double h)    //lamma���ȣ�phiiγ�ȣ�h�߶�
{
	double a=6378137;//aΪ����ĳ�����:a=6378.137km
	double f=1/298.257223563;
	double b=a*(1-f);
	double e=sqrt(1-pow(b ,2)/pow(a ,2)); //eΪ����ĵ�һƫ����
	double N=a/(sqrt(1-e*e*pow(sin(phi*(PI/180)),2)));
	//��һ��  ��γ�ȵ�����
	X0=(N+h)*cos(phi*(PI/180))*cos(lamma*(PI/180));  //xd,yd,zd�ǵ�������ϵ����
	Y0=(N+h)*cos(phi*(PI/180))*sin(lamma*(PI/180));
	Z0=(N*(1-pow(e,2))+h)*sin(phi); 
}
//��γ�ȵ�����
/*******************************************************
��������void CRead_txt::transmitLbh2Dx(double lamma,double phi,double h)
���룺lamma���ȣ�phiiγ�ȣ�h�߶�
���ܣ���γ�ȵ���������任
********************************************************/
void CRead_txt::transmitLbh2Dx(double lamma,double phi,double h)    //lamma���ȣ�phiiγ�ȣ�h�߶�
{
	double a=6378137;//aΪ����ĳ�����:a=6378.137km
	double f=1/298.257223563;
	double b=a*(1-f);
	double e=sqrt(1-pow(b ,2)/pow(a ,2)); //eΪ����ĵ�һƫ����
	double N=a/(sqrt(1-e*e*pow(sin(phi),2)));
	//��һ��  ��γ�ȵ�����
	xd=(N+h)*cos(phi*(PI/180))*cos(lamma*(PI/180));  //xd,yd,zd�ǵ�������ϵ����
	yd=(N+h)*cos(phi*(PI/180))*sin(lamma*(PI/180));
	zd=(N*(1-pow(e,2))+h)*sin(phi*(PI/180)); 
}
///���ĵ�����������ϵת��
/*******************************************************
��������void CRead_txt::transmitDx2Dbt(double lamma,double phi,double h)
���룺lamma���ȣ�phiiγ�ȣ�h�߶�
���ܣ����ĵ�����������ϵת��
********************************************************/
void CRead_txt::transmitDx2Dbt(double lamma,double phi,double h)     //lamma���ȣ�phiiγ�ȣ�h�߶�
{
	////���ĵ�������   
	//xt=-(xd-X0)*sin(longitude*(PI/180))+(yd-Y0)*cos(longitude*(PI/180)); //xx,yy,zz�Ƕ���������ϵ���꣬������ֵ�Ƕ������ԭ��
	//yt=-(xd-X0)*cos(longitude*(PI/180))*sin(latitude*(PI/180))-(yd-Y0)*sin(longitude*(PI/180))*sin(latitude*(PI/180))+(zd-0)*cos(latitude*(PI/180));
	//zt=(xd-X0)*cos(longitude*(PI/180))*cos(latitude*(PI/180))+(yd-Y0)*sin(longitude*(PI/180))*cos(latitude*(PI/180))+(zd-0)*sin(latitude*(PI/180)) ;
	
	double L0 = data_origin_L0;						//������ԭ��
	double B0 = data_origin_B0;
	double H0 = 0;
	//���ĵ�������   
	xt = -(xd - X0)*sin(L0*(PI / 180)) + (yd - Y0)*cos(L0*(PI / 180)); //xx,yy,zz�Ƕ���������ϵ���꣬������ֵ�Ƕ������ԭ��
	yt = -(xd - X0)*cos(L0*(PI / 180))*sin(B0*(PI / 180)) - (yd - Y0)*sin(L0*(PI / 180))*sin(B0*(PI / 180)) + (zd - 0)*cos(B0*(PI / 180));
	zt = (xd - X0)*cos(L0*(PI / 180))*cos(B0*(PI / 180)) + (yd - Y0)*sin(L0*(PI / 180))*cos(B0*(PI / 180)) + (zd - 0)*sin(B0*(PI / 180));

}
/////////////---------------


//����������ϵ������
/*******************************************************
��������void CRead_txt::transmitDbt2Dx(double x,double y,double z)
���룺x,y,zΪ����Ķ���������ϵ
���ܣ�����������ϵ����������ϵת��
********************************************************/
void CRead_txt::transmitDbt2Dx(double x,double y,double z) //������ת���ģ�xt,yt,ztΪ����Ķ���������ϵ
{
	double L0 = data_origin_L0;
	double B0 = data_origin_B0;
	double H0 = 0;

	xdd=-(x)*sin(L0*(PI/180))-(y)*cos(L0*(PI/180))*sin(B0*(PI/180))+(z)*cos(B0*(PI/180))*cos(L0*(PI/180))+X0;  
	ydd=(x)*cos(L0*(PI/180))-(y)*sin(L0*(PI/180))*sin(B0*(PI/180))+(z)*cos(B0*(PI/180))*sin(L0*(PI/180))+Y0;
	zdd=(y)*cos(B0*(PI/180))+(z)*sin(B0*(PI/180))+0 ;
}
///���ĵ���γ��
/*******************************************************
��������void CRead_txt::transmitDx2Lbh(double x,double y,double z)
���룺x,y,zΪ����Ķ���������ϵ
���ܣ����ĵ���γ������ϵת��
********************************************************/
void CRead_txt::transmitDx2Lbh(double x,double y,double z) //����ת��γ��
{
	double a=6378137;//aΪ����ĳ�����:a=6378.137km
	double f=1/298.257223563;
	double b=a*(1-f);
	double e=sqrt(1-pow(b ,2)/pow(a ,2)); //eΪ����ĵ�һƫ����
	double R1=sqrt(pow(x,2)+pow(y,2));
	double N=0 ; //NΪ�����î��Ȧ���ʰ뾶
	double B1=atan2(z,R) ,B2=0;
	double H=0;
	while(1)
	{
		N = a/sqrt(1-pow(e ,2)*pow(sin(B1) ,2));
		B2 = atan2(z+N*e*e*sin(B1),R1);
		if(fabs(B2-B1)<1E-10)
		break;
		B1=B2;
	}
	double m=PI/180;
	latitude=B1/m;
	longitude=atan2(y,x)/m;
	altitude=R1/cos(B2)-N;
}


//����������ϵ�������ٶ�
/*******************************************************
��������void CRead_txt::transmitDbt2Dx(double x,double y,double z)
���룺x,y,zΪ����Ķ���������ϵ
���ܣ�����������ϵ����������ϵת��
********************************************************/
void CRead_txt::VtransmitDbt2Dx(double Vx, double Vy, double Vz) //������ת���ģ�xt,yt,ztΪ����Ķ���������ϵ
{
	double L0 = data_origin_L0;
	double B0 = data_origin_B0;
	double H0 = 0;

	Vxdd = -(Vx)*sin(L0*(PI / 180)) - (Vy)*cos(L0*(PI / 180))*sin(B0*(PI / 180)) + (Vz)*cos(B0*(PI / 180))*cos(L0*(PI / 180));
	Vydd = (Vx)*cos(L0*(PI / 180)) - (Vy)*sin(L0*(PI / 180))*sin(B0*(PI / 180)) + (Vz)*cos(B0*(PI / 180))*sin(L0*(PI / 180));
	Vzdd = (Vy)*cos(B0*(PI / 180)) + (Vz)*sin(B0*(PI / 180)) + 0;
}