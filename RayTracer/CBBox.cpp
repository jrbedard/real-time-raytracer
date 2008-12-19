// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#include "CMaterial.h"

#include "CBBox.h"


CBBox::CBBox()
{ 
	min.set( 0,0,0 ); 
	max.set(1,1,1); 
	whichPlane = 0; 
}

CBBox::~CBBox()
{

}


void CBBox::SetExtents( CPoint3 p1, CPoint3 p2 )
{
	for (int i=0; i<3; i++)
		if (p1.v[i]>p2.v[i]) {
			max.v[i] = p1.v[i];
			min.v[i] = p2.v[i];
		} else {
			max.v[i] = p2.v[i];
			min.v[i] = p1.v[i];
		} 
}


void CBBox::RenderGL( char unique )
{
	CPoint3 pnt[8];

	if (unique==0)
		glColor3d( material->diffuse.r/255.0, material->diffuse.g/255.0, material->diffuse.b/255.0 );
	else glColor3f( unique/255.0, unique/255.0, unique/255.0 );

	pnt[0] = CPoint3 ( min.v[0], min.v[1], min.v[2] );
	pnt[1] = CPoint3 ( min.v[0], max.v[1], min.v[2] );
	pnt[2] = CPoint3 ( max.v[0], max.v[1], min.v[2] );
	pnt[3] = CPoint3 ( max.v[0], min.v[1], min.v[2] );
	pnt[4] = CPoint3 ( min.v[0], min.v[1], max.v[2] );
	pnt[5] = CPoint3 ( min.v[0], max.v[1], max.v[2] );
	pnt[6] = CPoint3 ( max.v[0], max.v[1], max.v[2] );
	pnt[7] = CPoint3 ( max.v[0], min.v[1], max.v[2] );

	glBegin( GL_QUADS );
		glVertex3fv( pnt[0].v );
		glVertex3fv( pnt[1].v );
		glVertex3fv( pnt[2].v );
		glVertex3fv( pnt[3].v );

		glVertex3fv( pnt[4].v );
		glVertex3fv( pnt[5].v );
		glVertex3fv( pnt[6].v );
		glVertex3fv( pnt[7].v );

		glVertex3fv( pnt[0].v );
		glVertex3fv( pnt[1].v );
		glVertex3fv( pnt[5].v );
		glVertex3fv( pnt[4].v );

		glVertex3fv( pnt[1].v );
		glVertex3fv( pnt[2].v );
		glVertex3fv( pnt[6].v );
		glVertex3fv( pnt[5].v );

		glVertex3fv( pnt[2].v );
		glVertex3fv( pnt[3].v );
		glVertex3fv( pnt[7].v );
		glVertex3fv( pnt[6].v );

		glVertex3fv( pnt[3].v );
		glVertex3fv( pnt[0].v );
		glVertex3fv( pnt[4].v );
		glVertex3fv( pnt[7].v );
	glEnd();
}