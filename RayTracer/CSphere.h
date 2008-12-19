// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#pragma once


#include "CObjectRT.h"



#define PI      3.1415926535897932384626433833f
#define TWOPI   6.283185307179586476925286766559f
#define PID2    1.5707963267948966192313216916398f


class CSphere : public CObjectRT
{
public:
	CSphere();

	CVector centre;
	CVector direction;
	float radius;

	virtual void frameCalc(CCamera *c);
	virtual float inline IntersectGeneral(CRay *r);
	virtual float inline intersectFixed(CRay *r);
	virtual inline bool intersects(CRay *r);
	virtual inline bool intersects(CPlaneIntersection *p);
	virtual CVector inline Normal(CVector *poi);
	virtual void RenderGL( char unique );
private:
	float rSquared, invRadius, cTerm;
	CVector origin;
};


float inline CSphere::IntersectGeneral(CRay *r)
{
	float b = r->d.x * (r->o.x - centre.x) + r->d.y * (r->o.y - centre.y) + r->d.z * (r->o.z - centre.z);
	float c = (r->o.x - centre.x) * (r->o.x - centre.x) + (r->o.y - centre.y) * (r->o.y - centre.y) + (r->o.z - centre.z) * (r->o.z - centre.z) - rSquared;

	float d = b * b - c;

	if (d < 0.0f) return -1.0f;

	return -b - sqrtf(d);
}

float inline CSphere::intersectFixed(CRay *r)
{
	float b = r->d.x * origin.x + r->d.y * origin.y + r->d.z * origin.z;

	float d = b * b - cTerm;

	if (d < 0.0f) return -1.0f;

	return -b - sqrtf(d);
}

bool inline CSphere::intersects(CRay *r)
{
	float b = r->d * (r->o - centre);
	float c = (r->o - centre) * (r->o - centre) - rSquared;

	float d = b * b - c;

	if (d < 0.0f) return false;
	return true;
}

bool inline CSphere::intersects(CPlaneIntersection *p)
{
	if (fabsf(p->n * centre - p->d) > radius) return false;
	return true;
}

CVector inline CSphere::Normal(CVector *poi) 
{ 
	return (*poi - centre) * invRadius; 
}
