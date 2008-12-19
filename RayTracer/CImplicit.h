// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#pragma once


#include "CObjectRT.h"

class CImplicit : public CObjectRT
{
public:
	CImplicit();
	virtual ~CImplicit();

	int refinementSteps;
	float tStep;

	CVector centre;
	float radius;

	float inline fieldEquation(CVector *v);

	virtual void frameCalc(CCamera *c);
	virtual float inline IntersectGeneral(CRay *r);
	virtual float inline intersectFixed(CRay *r);
	virtual inline bool intersects(CRay *r);
	virtual inline bool intersects(CPlaneIntersection *p);
	virtual CVector inline Normal(CVector *poi);

private:
	
	float rSquared, invRadius, cTerm;
	CVector origin;
};


float inline CImplicit::fieldEquation(CVector *v)
{
	const CVector nv = *v * 0.1f;
	const float a = (2.0f * nv.x * nv.x + nv.z * nv.z + nv.y * nv.y - 1.0f);
	const float zCube = nv.y * nv.y * nv.y;
	return a * a * a - 0.1f * nv.x * nv.x * zCube - nv.z * nv.z * zCube;

	/*CVector nv = *v * 1.0f;
	float x = nv.x, y = nv.y, z = nv.z;
	float d = (x * y * z) * 0.05f;
	return d * d - 10.0f;*/
}

// this is currently done with less precision than the primary CRay intersection
float inline CImplicit::IntersectGeneral(CRay *r)
{
	float b = r->d.x * (r->o.x - centre.x) + r->d.y * (r->o.y - centre.y) + r->d.z * (r->o.z - centre.z);
	float c = (r->o.x - centre.x) * (r->o.x - centre.x) + (r->o.y - centre.y) * (r->o.y - centre.y) + (r->o.z - centre.z) * (r->o.z - centre.z) - rSquared;

	const float d = b * b - c;

	if (d < 0.0f) return -1.0f;

	const float sqrtd = sqrtf(d);
	float t1 = -b - sqrtd, t2 = -b + sqrtd;

	if (t2 < 0.0f) return -1.0f;
	if (t1 < 0.0f) t1 = 0.0f;

	float t = t1;
	float f = fieldEquation(&(r->o + r->d * t));
	bool intersected = false;

	// iterate through volume looking for intersections
	while (t < t2)
	{
		t += tStep;
		if (f * fieldEquation(&(r->o + r->d * t)) < 0.0f) { intersected = true; break; }
	}

	if (!intersected) return -1.0f;

	float start = t - tStep, end = t;

	for (int i = 0; i < refinementSteps; i++) // do 1/4 number of refinement steps
	{
		float midpoint = (start + end) * 0.5f;
		CVector middle = r->o + r->d * midpoint;

		if (f * fieldEquation(&middle) < 0.0f) end = midpoint; else start = midpoint;
	}

	return (start + end) * 0.5f - 0.08f;
}


float inline CImplicit::intersectFixed(CRay *r)
{
	float b = r->d * origin;

	float d = b * b - cTerm;

	if (d < 0.0f) return -1.0f;

	float sqrtd = sqrtf(d);
	float t1 = -b - sqrtd, t2 = -b + sqrtd;

	//if (t2 < 0.0f) return -1.0f;
	//if (t1 < 0.0f) t1 = 0.01f;

	float t = t1;
	float f = fieldEquation(&(r->o + r->d * t));
	bool intersected = false;

	// iterate through volume looking for intersections
	while (t < t2)
	{
		t += tStep;
		if (f * fieldEquation(&(r->o + r->d * t)) < 0.0f) { intersected = true; break; }
	}

	if (!intersected) return -1.0f;

	float start = t - tStep, end = t;

	for (int i = 0; i < refinementSteps; i++)
	{
		float midpoint = (start + end) * 0.5f;
		CVector middle = r->o + r->d * midpoint;

		if (f * fieldEquation(&middle) < 0.0f) end = midpoint; else start = midpoint;
	}

	return (start + end) * 0.5f - 0.08f;
}

bool inline CImplicit::intersects(CRay *r)
{
	float b = r->d.x * (r->o.x - centre.x) + r->d.y * (r->o.y - centre.y) + r->d.z * (r->o.z - centre.z);
	float c = (r->o.x - centre.x) * (r->o.x - centre.x) + (r->o.y - centre.y) * (r->o.y - centre.y) + (r->o.z - centre.z) * (r->o.z - centre.z) - rSquared;

	float d = b * b - c;

	if (d < 0.0f) return false;

	return true;
}

bool inline CImplicit::intersects(CPlaneIntersection *p)
{
	if (fabsf(p->n * centre - p->d) > radius) return false;
	return true;
}

CVector inline CImplicit::Normal(CVector *poi)
{
	CVector v = *poi;
	float e0 = fieldEquation(poi);
	float e1x = fieldEquation(&(v + CVector(0.01f,0.0f,0.0f)));
	float e1y = fieldEquation(&(v + CVector(0.0f,0.01f,0.0f)));
	float e1z = fieldEquation(&(v + CVector(0.0f,0.0f,0.01f)));

	CVector g = CVector(e1x - e0,e1y - e0,e1z - e0) * 100.0f;
	return g | 1.0f;
}