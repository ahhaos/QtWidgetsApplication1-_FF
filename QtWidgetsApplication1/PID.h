#pragma once

#ifndef _PID_H_
#define _PID_H_




class Pid_control
{
public:
	Pid_control();
	~Pid_control();
	float err;
	float err_next;
	float err_last;
	float outPutLimit;
	float Kp0, Ki0, Kd0;
	float Kp1, Ki1, Kd1;
	float Kp2, Ki2, Kd2;
	float Kp3, Ki3, Kd3;
	float Kp4, Ki4, Kd4;
	float Kp5, Ki5, Kd5;
	double PID_realize(double inPut);

private:
	int index;
};
#endif
