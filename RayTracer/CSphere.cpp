// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#include "CMaterial.h"

#include "CSphere.h"



CSphere::CSphere() 
{ 
	centre.set(0.0f);
	direction.set(0.0f);
	radius = 1.0f;
}


void CSphere::frameCalc(CCamera *c)
{
	rSquared = radius * radius;
	invRadius = 1.0f / radius;
	origin = c->p - centre;
	cTerm = origin * origin - rSquared;
}


void CSphere::RenderGL( char unique )
{
	int i,j,n = 15;
	float theta1,theta2,theta3;
	CVector e,p;

	if (unique==0)
		glColor3d( material->diffuse.r/255.0, material->diffuse.g/255.0, material->diffuse.b/255.0 );
	else
		glColor3f( unique/255.0, unique/255.0, unique/255.0 );

	if (radius < 0)
		radius = -radius;
	if (n < 0)
		n = -n;
	if (n < 4 || radius <= 0) {
		glBegin(GL_POINTS);
		glVertex3f(centre.x,centre.y,centre.z);
		glEnd();
		return;
	}

	for (j=0;j<n/2;j++) {
		theta1 = j * TWOPI / n - PID2;
		theta2 = (j + 1) * TWOPI / n - PID2;

		glBegin(GL_QUAD_STRIP);
		for (i=0;i<=n;i++) {
			theta3 = i * TWOPI / n;

			e.x = cosf(theta2) * cosf(theta3);
			e.y = sinf(theta2);
			e.z = cosf(theta2) * sinf(theta3);
			p.x = centre.x + radius * e.x;
			p.y = centre.y + radius * e.y;
			p.z = centre.z + radius * e.z;

			glNormal3f(e.x,e.y,e.z);
			glTexCoord2f(i/(float)n,2*(j+1)/(float)n);
			glVertex3f(p.x,p.y,p.z);

			e.x = cosf(theta1) * cosf(theta3);
			e.y = sinf(theta1);
			e.z = cosf(theta1) * sinf(theta3);
			p.x = centre.x + radius * e.x;
			p.y = centre.y + radius * e.y;
			p.z = centre.z + radius * e.z;

			glNormal3f(e.x,e.y,e.z);
			glTexCoord2f(i/(float)n,2*j/(float)n);
			glVertex3f(p.x,p.y,p.z);
		}
		glEnd();
	}
}