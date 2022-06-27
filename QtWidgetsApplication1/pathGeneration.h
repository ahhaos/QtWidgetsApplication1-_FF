#pragma once


#include "math.h"

#include <vector>

using namespace std;

class pathGeneration
{
public:
	pathGeneration(double X_n, double Y_n, double Z_n, std::vector<std::vector<double>> targetNode_X_Y_Z_, double V_);
	~pathGeneration();
	int getNode(double &X, double &Y, double &Z);

	double X_last, Y_last, Z_last;
	double X_now, Y_now, Z_now;
	double X_next, Y_next, Z_next;
	double V;
	double Lstep;
	int i = 0;

	std::vector<std::vector<double>>::iterator it;
	std::vector<std::vector<double>> targetNode_X_Y_Z;
};

