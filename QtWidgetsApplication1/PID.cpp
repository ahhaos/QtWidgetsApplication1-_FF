#include <iostream>
#include "pid.h"

using namespace std;

Pid_control::Pid_control()
{
	err = 0.0;
	err_last = 0.0;
	err_next = 0.0;
	outPutLimit = 25;
	Kp0 = 0.1;
	Kd0 = 0.03;
	Ki0 = 0.05;

	Kp1 = 0.4;
	Kd1 = 0.02;
	Kp2 = 0.4;
	Kd2 = 0.02;
	Kp3 = 0.4;
	Kd3 = 0.02;
	Kp4 = 0.4;
	Kd4 = 0.02;
}
Pid_control::~Pid_control()
{

}


double Pid_control::PID_realize(double inPut) 
{
	err = inPut;
	double incrementSpeed;
	static double inter=0;
	incrementSpeed = Kd0*(err - err_next) + Kp0*err+Ki0*inter;
	//cout << "err" << err << endl;
	//cout << "incrementSpeed" << incrementSpeed << endl;
	inter += err;
	if (inter <= -20)
		inter = -20;
	if (inter >= 20)
		inter = 20;
	err_last = err_next;
	err_next = err;
	if (incrementSpeed > outPutLimit)
		incrementSpeed = outPutLimit;
	if (incrementSpeed < -outPutLimit)
		incrementSpeed = -outPutLimit;
	return incrementSpeed;
}
