// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#pragma once


#include "CRay.h"

#include "CObjectRT.h"


#define PLANEEPSILON 0.0001f


class CPlane : public CObjectRT
{
public:
	CPlane();

	CVector p, n;

	virtual void frameCalc(CCamera *c);
	virtual float inline IntersectGeneral(CRay *r);
	virtual float inline intersectFixed(CRay *r);
	virtual inline bool intersects(CRay *r);
	virtual inline bool intersects(CPlaneIntersection *p) { return true; }
	virtual CVector inline Normal(CVector *poi);
	virtual void RenderGL();

private:
	
	float d, num;
};



void inline CPlane::frameCalc(CCamera *c)
{
	d = p * n;
	num = d - c->p * n;
}

float inline CPlane::IntersectGeneral(CRay *r)
{
	float denom = n * r->d;

	if (denom != 0.0f)
	{
		float t = (d - r->o * n) / denom;

		if (t > PLANEEPSILON)
		{
			CVector p = r->o + r->d * t;
			float size = 940.0f;
			if ((p.x < -size) || (p.x > size) || (p.z < -size) || (p.z > size)) return -1.0f;
			return t;
		}
	}

	return -1.0f;
}

float inline CPlane::intersectFixed(CRay *r)
{
	float denom = n * r->d;

	if (denom != 0.0f)
	{
		float t = num / denom;

		//if (t > PLANEEPSILON) return t;
		if (t > PLANEEPSILON)
		{
			CVector p = r->o + r->d * t;
			float size = 40.0f;
			if ((p.x < -size) || (p.x > size) || (p.z < -size) || (p.z > size)) return -1.0f;
			return t;
		}
	}

	return -1.0f;
}

bool inline CPlane::intersects(CRay *r)
{
	if (n * r->d != 0.0f) return true;
	return false;
}

CVector inline CPlane::Normal(CVector *poi) 
{ 
	return n; 
}
