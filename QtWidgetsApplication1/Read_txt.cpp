
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

//东北天原点的地心坐标
/*******************************************************
函数名：void CRead_txt::yuandian(double lamma,double phi,double h)
输入：lamma经度，phii纬度，h高度
功能：求解东北天原点的地心坐标
********************************************************/
void CRead_txt::yuandian(double lamma,double phi,double h)    //lamma经度，phii纬度，h高度
{
	double a=6378137;//a为椭球的长半轴:a=6378.137km
	double f=1/298.257223563;
	double b=a*(1-f);
	double e=sqrt(1-pow(b ,2)/pow(a ,2)); //e为椭球的第一偏心率
	double N=a/(sqrt(1-e*e*pow(sin(phi*(PI/180)),2)));
	//第一步  经纬度到地心
	X0=(N+h)*cos(phi*(PI/180))*cos(lamma*(PI/180));  //xd,yd,zd是地心坐标系坐标
	Y0=(N+h)*cos(phi*(PI/180))*sin(lamma*(PI/180));
	Z0=(N*(1-pow(e,2))+h)*sin(phi); 
}
//经纬度到地心
/*******************************************************
函数名：void CRead_txt::transmitLbh2Dx(double lamma,double phi,double h)
输入：lamma经度，phii纬度，h高度
功能：经纬度到地心坐标变换
********************************************************/
void CRead_txt::transmitLbh2Dx(double lamma,double phi,double h)    //lamma经度，phii纬度，h高度
{
	double a=6378137;//a为椭球的长半轴:a=6378.137km
	double f=1/298.257223563;
	double b=a*(1-f);
	double e=sqrt(1-pow(b ,2)/pow(a ,2)); //e为椭球的第一偏心率
	double N=a/(sqrt(1-e*e*pow(sin(phi),2)));
	//第一步  经纬度到地心
	xd=(N+h)*cos(phi*(PI/180))*cos(lamma*(PI/180));  //xd,yd,zd是地心坐标系坐标
	yd=(N+h)*cos(phi*(PI/180))*sin(lamma*(PI/180));
	zd=(N*(1-pow(e,2))+h)*sin(phi*(PI/180)); 
}
///地心到东北天坐标系转换
/*******************************************************
函数名：void CRead_txt::transmitDx2Dbt(double lamma,double phi,double h)
输入：lamma经度，phii纬度，h高度
功能：地心到东北天坐标系转换
********************************************************/
void CRead_txt::transmitDx2Dbt(double lamma,double phi,double h)     //lamma经度，phii纬度，h高度
{
	////地心到东北天   
	//xt=-(xd-X0)*sin(longitude*(PI/180))+(yd-Y0)*cos(longitude*(PI/180)); //xx,yy,zz是东北天坐标系坐标，几个数值是东北天的原点
	//yt=-(xd-X0)*cos(longitude*(PI/180))*sin(latitude*(PI/180))-(yd-Y0)*sin(longitude*(PI/180))*sin(latitude*(PI/180))+(zd-0)*cos(latitude*(PI/180));
	//zt=(xd-X0)*cos(longitude*(PI/180))*cos(latitude*(PI/180))+(yd-Y0)*sin(longitude*(PI/180))*cos(latitude*(PI/180))+(zd-0)*sin(latitude*(PI/180)) ;
	
	double L0 = data_origin_L0;						//东北天原点
	double B0 = data_origin_B0;
	double H0 = 0;
	//地心到东北天   
	xt = -(xd - X0)*sin(L0*(PI / 180)) + (yd - Y0)*cos(L0*(PI / 180)); //xx,yy,zz是东北天坐标系坐标，几个数值是东北天的原点
	yt = -(xd - X0)*cos(L0*(PI / 180))*sin(B0*(PI / 180)) - (yd - Y0)*sin(L0*(PI / 180))*sin(B0*(PI / 180)) + (zd - 0)*cos(B0*(PI / 180));
	zt = (xd - X0)*cos(L0*(PI / 180))*cos(B0*(PI / 180)) + (yd - Y0)*sin(L0*(PI / 180))*cos(B0*(PI / 180)) + (zd - 0)*sin(B0*(PI / 180));

}
/////////////---------------


//东北天坐标系到地心
/*******************************************************
函数名：void CRead_txt::transmitDbt2Dx(double x,double y,double z)
输入：x,y,z为输入的东北天坐标系
功能：东北天坐标系到地心坐标系转换
********************************************************/
void CRead_txt::transmitDbt2Dx(double x,double y,double z) //东北天转地心，xt,yt,zt为输入的东北天坐标系
{
	double L0 = data_origin_L0;
	double B0 = data_origin_B0;
	double H0 = 0;

	xdd=-(x)*sin(L0*(PI/180))-(y)*cos(L0*(PI/180))*sin(B0*(PI/180))+(z)*cos(B0*(PI/180))*cos(L0*(PI/180))+X0;  
	ydd=(x)*cos(L0*(PI/180))-(y)*sin(L0*(PI/180))*sin(B0*(PI/180))+(z)*cos(B0*(PI/180))*sin(L0*(PI/180))+Y0;
	zdd=(y)*cos(B0*(PI/180))+(z)*sin(B0*(PI/180))+0 ;
}
///地心到经纬度
/*******************************************************
函数名：void CRead_txt::transmitDx2Lbh(double x,double y,double z)
输入：x,y,z为输入的东北天坐标系
功能：地心到经纬度坐标系转换
********************************************************/
void CRead_txt::transmitDx2Lbh(double x,double y,double z) //地心转经纬高
{
	double a=6378137;//a为椭球的长半轴:a=6378.137km
	double f=1/298.257223563;
	double b=a*(1-f);
	double e=sqrt(1-pow(b ,2)/pow(a ,2)); //e为椭球的第一偏心率
	double R1=sqrt(pow(x,2)+pow(y,2));
	double N=0 ; //N为椭球的卯酉圈曲率半径
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


//东北天坐标系到地心速度
/*******************************************************
函数名：void CRead_txt::transmitDbt2Dx(double x,double y,double z)
输入：x,y,z为输入的东北天坐标系
功能：东北天坐标系到地心坐标系转换
********************************************************/
void CRead_txt::VtransmitDbt2Dx(double Vx, double Vy, double Vz) //东北天转地心，xt,yt,zt为输入的东北天坐标系
{
	double L0 = data_origin_L0;
	double B0 = data_origin_B0;
	double H0 = 0;

	Vxdd = -(Vx)*sin(L0*(PI / 180)) - (Vy)*cos(L0*(PI / 180))*sin(B0*(PI / 180)) + (Vz)*cos(B0*(PI / 180))*cos(L0*(PI / 180));
	Vydd = (Vx)*cos(L0*(PI / 180)) - (Vy)*sin(L0*(PI / 180))*sin(B0*(PI / 180)) + (Vz)*cos(B0*(PI / 180))*sin(L0*(PI / 180));
	Vzdd = (Vy)*cos(B0*(PI / 180)) + (Vz)*sin(B0*(PI / 180)) + 0;
}