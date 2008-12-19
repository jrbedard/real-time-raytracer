// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#pragma once


#include "CVector.h"


class CCamera
{

public:

	CCamera();
	virtual ~CCamera();
	
	CVector p, up, dir, right;

	float fov;
	void lookAt(CVector target, float roll);
};
