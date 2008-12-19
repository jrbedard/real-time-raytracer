// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#include "CLight.h"


CLight::CLight() 
{	
	ambient.set(0.0f);
	diffuse.set(0.0f);
	specular.set(0.0f);
	lastOccluder = 0;
}


CLight::~CLight() 
{

}