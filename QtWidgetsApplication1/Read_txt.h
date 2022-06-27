#pragma once

#include <fstream>
#include <iostream>
#include <string>

using namespace std;


#ifndef R	
#define R   6378137 //地球半径
#endif

//extern double L0;  //东北天坐标系的原点
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
	void transmitDbt2Dx(double x,double y,double z); //东北天转地心，xt,yt,zt为输入的东北天坐标系
	void transmitDx2Lbh(double x,double y,double z); //地心转经纬高
	void VtransmitDbt2Dx(double Vx, double Vy, double Vz); //速度东北天转地心，Vx,Vy,Vy为输入的东北天坐标系

	double X0;  //东北天原点的地心x坐标
	double Y0; 
	double Z0; 

	double xd;  //地心坐标系的x坐标
	double yd; //地心坐标系的y坐标
	double zd; //地心坐标系的z坐标

	double xt;  //东北天坐标系的x坐标
	double yt; //东北天坐标系的y坐标
	double zt; //东北天坐标系的z坐标

	double xdd;  //转化的地心坐标系的x坐标
	double ydd; //转化的地心坐标系的y坐标
	double zdd; //转化的地心坐标系的z坐标

	double latitude;  //转化的纬度
	double longitude;//转化的经度
	double altitude;//转化的高度

	double Vxdd;  //转化的地心坐标系的Vx速度
	double Vydd; //转化的地心坐标系的Vy速度
	double Vzdd; //转化的地心坐标系的Vz速度

};

