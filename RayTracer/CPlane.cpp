// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#include "CPlane.h"



CPlane::CPlane()
{ 
	p.set(0,0,0); 
	n.set(0,1,0); 
}



void CPlane::RenderGL() 
{
	/*glBegin( GL_POINTS );
	glVertex3f( p.x, p.y, p.z );
	glEnd();*/
}