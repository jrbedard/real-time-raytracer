// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#include "CRay.h"



CRay::CRay() 
{

}

CRay::CRay(CVector &orig, CVector &dir)
{ 
	o = orig; 
	d = dir; 
}

CRay::~CRay()
{

}
