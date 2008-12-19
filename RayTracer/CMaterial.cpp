// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#include "CMaterial.h"


CMaterial::CMaterial()
{
	ambient.set(25.0f);
	diffuse.set(225.0f);
	specular.set(255.0f);
	reflectivity = 0.25f;
	specularity = 20.0f;
	shinyness = 0.5f;
}



CMaterial::~CMaterial()
{

}