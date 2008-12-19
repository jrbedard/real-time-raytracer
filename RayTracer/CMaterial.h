// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#pragma once


#include "CColor.h"


class CMaterial
{
public:
	CMaterial();
	virtual ~CMaterial();

	CColor ambient, diffuse, specular;
	float reflectivity, specularity, shinyness;
};
