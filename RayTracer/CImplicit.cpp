// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#include "CImplicit.h"


CImplicit::CImplicit() 
{
	centre.set(0.0f);
	radius = 1.0f;
	tStep = 1.0f;
	refinementSteps = 6;
}


CImplicit::~CImplicit()
{


}


void CImplicit::frameCalc(CCamera *c)
{
	rSquared = radius * radius;
	invRadius = 1.0f / radius;
	origin = c->p - centre;
	cTerm = origin * origin - rSquared;
}
