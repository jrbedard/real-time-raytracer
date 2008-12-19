// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#pragma once

#include "CVector.h"
#include "CColor.h"


class CLight
{
public:
	
	CLight();
	virtual ~CLight();

	CVector p;
	CColor ambient, diffuse, specular;

	int lastOccluder;
};