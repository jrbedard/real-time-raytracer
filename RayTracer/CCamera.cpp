// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#include "CCamera.h"


CCamera::CCamera()
{	
	p.set(0.0f);
	up.set(0.0f,1.0f,0.0f);
	dir.set(0.0f,0.0f,1.0f);
	right.set(1.0f,0.0f,0.0f);
	fov = 30.0f;
}

CCamera::~CCamera()
{	

}


void CCamera::lookAt(CVector target,float roll)
{
	up.x = sinf(roll * 3.1415926535f / 180.0f);
	up.y = cosf(roll * 3.1415926535f / 180.0f);
	up.z = 0.0f;

	dir = (target - p) | 1.0f;
	right = (up ^ dir) | 1.0f;
	up = (dir ^ right) | 1.0f;
}
