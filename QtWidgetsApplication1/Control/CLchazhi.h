// chazhi.h: interface for the Cchazhi class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHAZHI_H__D6B5C22D_AB49_47C3_8B69_44DE573EFCC2__INCLUDED_)
#define AFX_CHAZHI_H__D6B5C22D_AB49_47C3_8B69_44DE573EFCC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GeneralDefinitions.h"

class CCLchazhi : public CCharaLine
{
public:
	double alpha[121];
	double cl[20][121];
public:
	bool ChenckAlpha(double alpha, double& AvailableAlpha);
	bool LoadCharaLine();
	bool LoadDate(const char* filename, double* pcl);
	CCLchazhi();
	virtual ~CCLchazhi();

	double operator() (int iSelect, double x);

	//private:
	void divide(int& a, int& b, double alpha);
};

#endif // !defined(AFX_CHAZHI_H__D6B5C22D_AB49_47C3_8B69_44DE573EFCC2__INCLUDED_)
