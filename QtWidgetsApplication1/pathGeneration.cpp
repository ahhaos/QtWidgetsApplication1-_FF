#include "pathGeneration.h"
#include <QDebug>


pathGeneration::pathGeneration(double X_n, double Y_n, double Z_n, std::vector<std::vector<double>> targetNode_X_Y_Z_, double V_)
{
	X_now = X_n;
	Y_now = Y_n;
	Z_now = Z_n;
	targetNode_X_Y_Z = targetNode_X_Y_Z_;
	V = V_;
	it = targetNode_X_Y_Z.begin();
	Lstep = V/ 1000 * 25;
	//qDebug() << Lstep << "Lstep";
}
pathGeneration::~pathGeneration()
{
}

int pathGeneration::getNode(double &X, double &Y, double &Z)
{
	int r = -3;
	X_next = it->at(0);
	Y_next = it->at(1);
	Z_next = it->at(2);
	double L = sqrt(pow(X_next - X_now, 2) + pow(Y_next - Y_now, 2) + pow(Z_next - Z_now, 2));
	if (L < 2 * Lstep)
	{
		r = i;
		if (it != (targetNode_X_Y_Z.end() - 1))
		{
			X_now = it->at(0);
			Y_now = it->at(1);
			Z_now = it->at(2);
			it++;
			i++;
			X_next = it->at(0);
			Y_next = it->at(1);
			Z_next = it->at(2);
		}
		else
		{
			return -2;
		}
	}
	L = sqrt(pow(X_next - X_now, 2) + pow(Y_next - Y_now, 2) + pow(Z_next - Z_now, 2));
	X = X_now + (X_next - X_now) / L * Lstep;
	Y = Y_now + (Y_next - Y_now) / L * Lstep;
	Z = Z_now + (Z_next - Z_now) / L * Lstep;
	X_now = X;
	Y_now = Y;
	Z_now = Z;

	return r;
}