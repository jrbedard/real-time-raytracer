// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#pragma once

#include "CVector.h"

class CRay
{
public:
	
	CRay();
	CRay(CVector &orig, CVector &dir);
	virtual ~CRay();

	CVector inline Reflect(CVector &n);
	CVector o,d;
};


CVector inline CRay::Reflect(CVector &n) 
{	
	return n * 2 * (n * -d) + d;
}