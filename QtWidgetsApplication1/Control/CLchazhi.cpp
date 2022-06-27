// chazhi.cpp: implementation of the Cchazhi class.
//
//////////////////////////////////////////////////////////////////////


#include "CLchazhi.h"
#include <stdio.h>
#include <QDebug>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCLchazhi::CCLchazhi()
{
}

CCLchazhi::~CCLchazhi()
{

}

void CCLchazhi::divide(int& a, int& b, double al)
{
	if (a < 0 || b>121 || a >= b) return;
	if (b - a == 1) return;
	int m = (a + b) / 2;
	if (al > alpha[m]) a = m;
	else	b = m;
	divide(a, b, al);
}

double CCLchazhi::operator ()(int iSelect, double x)
{
	int a = 0, b = 121;
	divide(a, b, x);
	return (cl[iSelect][b] - cl[iSelect][a]) / (alpha[b] - alpha[a]) * (x - alpha[a]) + cl[iSelect][a];
}

bool CCLchazhi::LoadDate(const char* filename, double* pcl)
{
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		qDebug() << "Can not find StaticParamsFile"<< filename;
		return false;
	}
	for (int i = 0; i < 121; i++)
	{
		fscanf(fp, "%lf", pcl + i);
	}
	fclose(fp);
	return true;
}

bool CCLchazhi::LoadCharaLine()
{
	bool b = true;
	b = b && LoadDate("Control\\StaticParamsFile\\al.txt", alpha);
	b = b && LoadDate("Control\\StaticParamsFile\\C_L_al.txt", cl[C_L]);
	b = b && LoadDate("Control\\StaticParamsFile\\C_D_al.txt", cl[C_D]);
	b = b && LoadDate("Control\\StaticParamsFile\\C_ldeltaa_al.txt", cl[C_ldeltaa]);
	b = b && LoadDate("Control\\StaticParamsFile\\C_ldeltac_al.txt", cl[C_ldeltac]);
	b = b && LoadDate("Control\\StaticParamsFile\\C_ldeltar_al.txt", cl[C_ldeltar]);
	b = b && LoadDate("Control\\StaticParamsFile\\C_lp_al.txt", cl[C_lp]);
	b = b && LoadDate("Control\\StaticParamsFile\\C_lr_al.txt", cl[C_lr]);
	b = b && LoadDate("Control\\StaticParamsFile\\C_lbeta_al.txt", cl[C_lbeta]);
	b = b && LoadDate("Control\\StaticParamsFile\\C_mo_al.txt", cl[C_mo]);
	b = b && LoadDate("Control\\StaticParamsFile\\C_mdeltac_al.txt", cl[C_mdeltac]);
	b = b && LoadDate("Control\\StaticParamsFile\\C_mq_al.txt", cl[C_mq]);
	b = b && LoadDate("Control\\StaticParamsFile\\C_ndeltaa_al.txt", cl[C_ndeltaa]);
	b = b && LoadDate("Control\\StaticParamsFile\\C_ndeltar_al.txt", cl[C_ndeltar]);
	b = b && LoadDate("Control\\StaticParamsFile\\C_np_al.txt", cl[C_np]);
	b = b && LoadDate("Control\\StaticParamsFile\\C_nr_al.txt", cl[C_nr]);
	b = b && LoadDate("Control\\StaticParamsFile\\C_nbeta_al.txt", cl[C_nbeta]);
	b = b && LoadDate("Control\\StaticParamsFile\\C_ydeltaa_al.txt", cl[C_ydeltaa]);
	b = b && LoadDate("Control\\StaticParamsFile\\C_ydeltar_al.txt", cl[C_ydeltar]);
	b = b && LoadDate("Control\\StaticParamsFile\\C_ybeta_al.txt", cl[C_ybeta]);
	b = b && LoadDate("Control\\StaticParamsFile\\delta_c0.txt", cl[delta_c0]);
	return b;
}

bool CCLchazhi::ChenckAlpha(double alpha, double& AvailableAlpha)
{
	if (alpha < this->alpha[0])
	{
		AvailableAlpha = this->alpha[0];
		return false;
	}
	if (alpha > this->alpha[120])
	{
		AvailableAlpha = this->alpha[120];
		return false;
	}
	AvailableAlpha = alpha;
	return true;
}
