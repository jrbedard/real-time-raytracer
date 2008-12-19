// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#pragma once


#include "windows.h"

#include <GL/gl.h>
#include <GL/glu.h>


#include "CPoint.h"
#include "CRay.h"

//#include "CMaterial.h"

#include "CCamera.h"


// Author : Jean-René Bédard

class CPlaneIntersection;
class CMaterial;



class CObjectRT
{
public:

	CObjectRT() { castShadow = receiveShadow = true; }

	virtual void frameCalc(CCamera *c)	{ }
	virtual void RenderGL( char unique ){ };
	
	virtual inline float IntersectGeneral(CRay *r)			{ return -1.0f; }
	virtual inline float intersectFixed(CRay *r)			{ return -1.0f; }
	virtual inline bool intersects(CRay *r)					{ return false; }
	virtual inline bool intersects(CPlaneIntersection *p)	{ return false; }
	virtual inline CVector Normal(CVector *poi)				{ return CVector(0.0f); }

	CMaterial *material;

	bool castShadow, receiveShadow;
};





class CPlaneIntersection
{
public:
	CPlaneIntersection() { p.set(0.0f); n.set(0.0f,1.0f,0.0f); }

	void define3points(CVector &u, CVector &v, CVector &w)
	{
		float x1 = u.x, x2 = v.x, x3 = w.x;
		float y1 = u.y, y2 = v.y, y3 = w.y;
		float z1 = u.z, z2 = v.z, z3 = w.z;

		float a = y1 * (z2 - z3) + y2 * (z3 - z1) + y3 * (z1 - z2);
		float b = z1 * (x2 - x3) + z2 * (x3 - x1) + z3 * (x1 - x2);
		float c = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
		d = -(x1 * (y2 * z3 - y3 * z2) + x2 * (y3 * z1 - y1 * z3) + x3 * (y1 * z2 - y2 * z1));

		p = u;
		n = CVector(a,b,c) | 1.0f; // TODO: is this needed?
	}

	CVector p, n;
	float d;
};
