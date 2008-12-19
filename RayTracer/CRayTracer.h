// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#pragma once


#define LETTERBOX 50


#include "windows.h"


#include <vector>

#include "CSphere.h"
#include "CMaterial.h"
#include "CScene.h"
#include "CLight.h"
#include "CBBox.h"
#include "CPlane.h"


class CRayTracer
{
public:

	CRayTracer();
	~CRayTracer();

	void setRes( int width, int height );
	void updateScene( CPoint3 viewposition, unsigned char *screen, char unique );
	int InitScene();
	void destroyScene();

	int numspheres;
	CSphere *sphere;

	std::vector<CMaterial*> m_vMaterial;

	CMaterial m[8];
	CScene scene;
	
	CLight light;

	std::vector<CLight*> m_vLight;

	CBBox box[6];


	std::vector<CBBox*> m_vBBox;
	
	unsigned char *screen;
};
