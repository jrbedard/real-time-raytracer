// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#pragma once



#include "CObjectRT.h"


#define NUMDIM	3
#define RIGHT	0
#define LEFT	1
#define MIDDLE	2



class CBBox : public CObjectRT
{
public:
	CBBox();
	virtual ~CBBox();

	CPoint3 min, max;

	void SetExtents( CPoint3 p1, CPoint3 p2 );
	virtual float inline IntersectGeneral(CRay *r);
	virtual CVector inline Normal(CVector *poi);
	virtual void RenderGL( char unique );

private:
	char quadrant[NUMDIM], actual_side;
	int whichPlane, actual_plane;
	GLfloat origin[3], direction[3], hit_point[3], hit_normal[3];
};





float inline CBBox::IntersectGeneral(CRay *r)
{
	char inside = TRUE;
	float maxT[NUMDIM];
	float candidatePlane[NUMDIM];
	register unsigned char i;

	origin[0] = r->o.x;
	origin[1] = r->o.y;
	origin[2] = r->o.z;

	direction[0] = r->d.x;
	direction[1] = r->d.y;
	direction[2] = r->d.z;

	/* Find candidate planes; this loop can be avoided if
   	CRays cast all from the eye(assume perpsective view) */
	for (i=0; i<NUMDIM; i++)
		if(origin[i] < min.v[i]) 
			{
				quadrant[i] = LEFT;
				candidatePlane[i] = min.v[i];
				inside = 0;
				maxT[i] = (candidatePlane[i]-origin[i]) / direction[i];
			}
		else if (origin[i] > max.v[i]) 
			{
				quadrant[i] = RIGHT;
				candidatePlane[i] = max.v[i];			
				inside = 0;
				maxT[i] = (candidatePlane[i]-origin[i]) / direction[i];
			}
		else	
			{
				quadrant[i] = MIDDLE;
				maxT[i] = -1.0f;
			}

	/* CRay origin inside bounding box */
	if(inside)	{
		whichPlane = 0;
		hit_point[0] = origin[0];
		hit_point[1] = origin[1];
		hit_point[2] = origin[2];
		return sqrtf( (r->o.x-hit_point[0])*(r->o.x-hit_point[0]) + 
					  (r->o.y-hit_point[1])*(r->o.y-hit_point[1]) + 
					  (r->o.z-hit_point[2])*(r->o.z-hit_point[2]) );
	}

	/* Get largest of the maxT's for final choice of intersection */
	whichPlane = 0;
	if(maxT[1] > maxT[whichPlane])	whichPlane = 1;
	if(maxT[2] > maxT[whichPlane])	whichPlane = 2;

	/* Check final candidate actually inside box */
	if (maxT[whichPlane] < 0.) return false;

	for (i = 0; i < NUMDIM; i++)
		if (whichPlane != i) 
			{
				hit_point[i] = origin[i] + maxT[whichPlane] * direction[i];				
				if (hit_point[i] < min.v[i] || hit_point[i] > max.v[i])	return false;
			} 
		else 
			hit_point[i] = candidatePlane[i];

	return sqrtf( (r->o.x-hit_point[0])*(r->o.x-hit_point[0]) + 
				  (r->o.y-hit_point[1])*(r->o.y-hit_point[1]) + 
				  (r->o.z-hit_point[2])*(r->o.z-hit_point[2]) );
}

CVector inline CBBox::Normal(CVector *poi)
{
	CVector normal;

	if (whichPlane==2)
		{
			normal.x = 0.0f;
			normal.y = 0.0f;
			if (quadrant[ whichPlane ]==LEFT)	normal.z = -1.0f;
			else normal.z = 1.0f;
			return normal;
		}
	else if (whichPlane==1)
		{
			normal.x = 0.0f;
			normal.z = 0.0f;
			if (quadrant[ whichPlane ]==LEFT)	normal.y = 1.0f;
			else normal.y = -1.0f;
			return normal;
		}
	else 
		{
			normal.z = 0.0f;
			normal.y = 0.0f;
			if (quadrant[ whichPlane ]==LEFT)	normal.x = 1.0f;
			else normal.x = -1.0f;
			return normal;
		}
}
