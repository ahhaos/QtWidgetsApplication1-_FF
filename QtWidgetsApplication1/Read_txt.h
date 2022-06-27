#pragma once

#include <fstream>
#include <iostream>
#include <string>

using namespace std;


#ifndef R	
#define R   6378137 //����뾶
#endif

//extern double L0;  //����������ϵ��ԭ��
//extern double B0;
//extern double H0;

class CRead_txt
{
public:
	CRead_txt(void);
	~CRead_txt(void);
	void CRead_txt::yuandian(double lamma,double phi,double h);
	void transmitLbh2Dx(double lamma,double phi,double h);//LBH-->XYZ
	void transmitDx2Dbt(double lamma,double phi,double h);// XYZ-->xyz
	void transmitDbt2Dx(double x,double y,double z); //������ת���ģ�xt,yt,ztΪ����Ķ���������ϵ
	void transmitDx2Lbh(double x,double y,double z); //����ת��γ��
	void VtransmitDbt2Dx(double Vx, double Vy, double Vz); //�ٶȶ�����ת���ģ�Vx,Vy,VyΪ����Ķ���������ϵ

	double X0;  //������ԭ��ĵ���x����
	double Y0; 
	double Z0; 

	double xd;  //��������ϵ��x����
	double yd; //��������ϵ��y����
	double zd; //��������ϵ��z����

	double xt;  //����������ϵ��x����
	double yt; //����������ϵ��y����
	double zt; //����������ϵ��z����

	double xdd;  //ת���ĵ�������ϵ��x����
	double ydd; //ת���ĵ�������ϵ��y����
	double zdd; //ת���ĵ�������ϵ��z����

	double latitude;  //ת����γ��
	double longitude;//ת���ľ���
	double altitude;//ת���ĸ߶�

	double Vxdd;  //ת���ĵ�������ϵ��Vx�ٶ�
	double Vydd; //ת���ĵ�������ϵ��Vy�ٶ�
	double Vzdd; //ת���ĵ�������ϵ��Vz�ٶ�

};

