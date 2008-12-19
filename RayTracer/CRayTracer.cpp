// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#include "CRayTracer.h"




CRayTracer::CRayTracer()
{
	numspheres= 5;
}


CRayTracer::~CRayTracer()
{

}



void CRayTracer::setRes( int width, int height ) 
{
	scene.setResolution(width, height);
	scene.resetObjectsOnly();
}

void CRayTracer::updateScene( CPoint3 viewposition, unsigned char *screen, char unique ) 
{
	int i;
	float angle = GetTickCount()*0.0001f; //(float)glfwGetTime() * 0.05f;// * -0.0005f;

	for (i = 0; i < numspheres; i++)
	{

		if(sphere[i].centre.x > 75 || sphere[i].centre.x < -75 )
			sphere[i].direction.set(-sphere[i].direction.x, sphere[i].direction.y, 0);

		if(sphere[i].centre.y > 75 || sphere[i].centre.y < -75 )
			sphere[i].direction.set(sphere[i].direction.x, -sphere[i].direction.y, 0);
/*
		// center piece
		if((sphere[i].centre.x > -5 || sphere[i].centre.x < 5) && (sphere[i].centre.y > -10  && sphere[i].centre.y < 10) )
			sphere[i].direction.set(-sphere[i].direction.x, sphere[i].direction.y, 0);

		if((sphere[i].centre.y > -5 || sphere[i].centre.x < 5) && (sphere[i].centre.x > -10  && sphere[i].centre.x < 10) )
			sphere[i].direction.set(sphere[i].direction.x, -sphere[i].direction.y, 0);
*/

		if(sphere[i].direction.x == 0 && sphere[i].direction.y == 0)
		sphere[i].direction = CVector(rand()%4-2,rand()%4-2,0);

		sphere[i].centre += sphere[i].direction;
	}


	float radius = cosf(angle * 3.0f) * 10.0f + 75.0f;
	float height = cosf(angle * 5.0f) * 25.0f + 35.0f;
	scene.camera.p.set(cosf(angle) * radius,height,sinf(angle) * radius);
	scene.camera.lookAt(CVector(0.0f),0.0f);

	light.p.set(0, -20, 60);

	scene.beginFrame();	
	scene.useHardware = 0;

	if (screen==NULL)
		scene.RenderGL( unique );
	else {
		scene.useHardware = unique;
		scene.render(viewposition, screen);
	}
}

int CRayTracer::InitScene()
{
	//scene.setResolution(XRES,YRES);
	scene.maxDepth = 3;

	scene.resetObjects(numspheres + 6);
	scene.resetLights(1);

	scene.background.set(255.0f);

	m[0].ambient.set(10.0f);
	m[0].diffuse.set(95.0f,174.0f,83.0f);
	m[0].reflectivity = 0.0f;

	m[1].ambient.set(10.0f);
	m[1].diffuse.set(160.0f,53.0f,40.0f);
	m[1].diffuse *= 1.8f;
	m[1].reflectivity = 0.0f;

	m[2].ambient.set(10.0f);
	m[2].diffuse.set(127.0f,78.0f,51.0f);
	m[2].diffuse *= 1.3f;
	m[2].reflectivity = 0.2f;

	m[3].ambient.set(10.0f);
	m[3].diffuse.set(183.0f,114.0f,95.0f);
	m[3].diffuse *= 1.3f;
	m[3].reflectivity = 0.0f;

	m[4].ambient.set(10.0f);
	m[4].diffuse.set(103.0f,50.0f,90.0f);
	m[4].diffuse *= 1.3f;
	m[4].reflectivity = 0.7f;

	m[5].ambient.set(10.0f);
	m[5].diffuse.set(90,90,90);
	m[5].diffuse *= 1.3f;
	m[5].reflectivity = 0.7f;

	m[6].ambient.set(10.0f);
	m[6].diffuse.set(185.0f,10.0f,23.0f);
	m[6].diffuse *= 2.3f;
	m[6].reflectivity = 0.1f;


	sphere = new CSphere[numspheres];
	for (int i = 0; i < numspheres; i++)
	{
		sphere[i].radius = 5;
		sphere[i].centre = CVector( rand()%80-10,rand()%80-10,5 );
		sphere[i].direction.set(0.0f);
		//sphere[i].castShadow = false;
		//sphere[i].receiveShadow = false;
		sphere[i].material = &m[rand()%5];
		scene.object[i] = &sphere[i];
	}

	box[0].SetExtents( CPoint3(-80,-80,0), CPoint3(80,80,-1) );
	box[0].castShadow = false;
	box[0].material = &m[0];

	box[1].SetExtents( CPoint3(-10,-10,0), CPoint3(10,10,20) );
	box[2].castShadow = false;
	box[1].material = &m[5];

	box[2].SetExtents( CPoint3(-80,80,0), CPoint3(80,80,20) );
	box[2].castShadow = false;
	box[2].material = &m[5];

	box[3].SetExtents( CPoint3(-80,-80,0), CPoint3(-80,80,20) );
	box[3].castShadow = false;
	box[3].material = &m[5];

	box[4].SetExtents( CPoint3(80,-80,0), CPoint3(80,80,20) );
	box[4].castShadow = false;
	box[4].material = &m[5];

	box[5].SetExtents( CPoint3(-80,-80,0), CPoint3(80,-80,20) );
	box[5].castShadow = false;
	box[5].material = &m[5];


	scene.object[i]		= &box[0];
	scene.object[++i]   = &box[1];
	scene.object[++i]   = &box[2];
	scene.object[++i]   = &box[3];
	scene.object[++i]   = &box[4];
	scene.object[++i]   = &box[5];

	light.ambient.set(4.0f);
	light.diffuse.set(0.9f);
	scene.light[0] = &light;

	screen = new unsigned char[1000 * 1000 * 3];

	return 0;
}

void CRayTracer::destroyScene() 
{
	delete screen;
	delete sphere;
}