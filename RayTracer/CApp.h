// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#pragma once


#include <stdlib.h>
#include <stdio.h>


#include <windows.h>
#include <math.h>


#include "CRayTracer.h"




class CApp
{
public:

	CApp();
	~CApp();

	void GLUpdate();
	void Resize( int w, int h );

	CRayTracer	raytracer;

	GLint	RunGame;	
	GLint	glWidth;
	GLint	glHeight;	
	CPoint3 ViewPosition;

	float	yaw, pitch, roll;

	GLint	oldMouseX, oldMouseY;
	GLint	MouseX, MouseY;
	GLint	Posx, Posy;

	char wireframe;
	char CRaytraced;
	char showhelp;
	char useHardware;
	char showMask;
	char saveTGA;

	void x_start_2d( int width, int height );
	void x_end_2d();
};
