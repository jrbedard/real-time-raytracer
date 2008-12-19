// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#include "CMaterial.h"

#include "CScene.h"


CScene::CScene()
{
	xRes = yRes = 0;

	object = NULL; numObjects = 0;
	light = NULL; numLights = 0;

	xRes = 340;
	yRes = 280;

	maxDepth = 3;
	useHardware = 1;
	background.set(0.0f);

}

CScene::~CScene()
{
	delete object;
	delete light;
}

void CScene::resetObjects(int n)
{
	delete object;
	object = new CObjectRT*[n];
	numObjects = n;

}

void CScene::resetObjectsOnly()
{
	int n = numObjects;

}

void CScene::resetLights(int n)
{
	delete light;
	light = new CLight*[n];
	numLights = n;
}

CColor CScene::traceCRay(CRay *r, int depth)
{
	CColor c(0.0f);

	if (depth > maxDepth) return c;

	int i, j, owner = -1;
	float t, neart = 3.402823466E+38f;

	if (depth==1 && useHardware) {
		i = id-1;
		if (i<numObjects && i>=0) {
			t = object[i]->IntersectGeneral(r);
			if ((t > 0) && (t < neart)) { neart = t; owner = i; }
		}
	} else {
		for (i = 0; i < numObjects; i++)
		{
			t = object[i]->IntersectGeneral(r);
			if ((t > 0) && (t < neart)) { neart = t; owner = i; }
		}
	}

	if (owner == -1) return c;

	CObjectRT *intersectedObject = object[owner];
	CMaterial *intersectedObjectMaterial = intersectedObject->material;

	CVector poi = r->d * neart + r->o;

	CVector n = object[owner]->Normal(&poi);

	for (i = 0; i < numLights; i++)
	{
		CVector incomingLight = light[i]->p - poi;
		float incomingLightMagnitude = !incomingLight;
		CVector incomingLightNormalised = incomingLight / incomingLightMagnitude;

		bool visible = true;


		if (object[owner]->receiveShadow)
		{
			CRay shadow(poi,incomingLightNormalised);

			t = object[light[i]->lastOccluder]->IntersectGeneral(&shadow);
			if ((t > 0.0f) && (t < incomingLightMagnitude)) { visible = false; }

			for (j = 0; (j < numObjects) & visible; j++)
			{
				if ((j != owner) & (j != light[i]->lastOccluder) & object[j]->castShadow)
				{
					float t = object[j]->IntersectGeneral(&shadow);
					if ((t > 0.0f) && (t < incomingLightMagnitude)) { visible = false; light[i]->lastOccluder = j; }
				}
			}
		}

		if (visible)
		{
			float diffuse = incomingLightNormalised * n;
			if (diffuse > 0.0f) c += (intersectedObjectMaterial->diffuse * light[i]->diffuse) * diffuse;
		}

		c += intersectedObjectMaterial->ambient * light[i]->ambient;
	}

	if (intersectedObjectMaterial->reflectivity > 0.0f) c += traceCRay(&CRay(poi,r->Reflect(n)),depth + 1) * intersectedObjectMaterial->reflectivity;

	return c;
}


void CScene::setResolution(int xres, int yres)
{
	xRes = xres, yRes = yres;
}

void CScene::beginFrame()
{
	int i;

	for (i = 0; i < numObjects; i++) object[i]->frameCalc(&camera);
}


void CScene::render(CPoint3 origin, unsigned char *dest)
{
	CRay primary;
	primary.o = camera.p;
	unsigned int i;
	CColor pixel;

	float sx,sy, sxDelta, syDelta;
	float model[16], proj[16], finalMatrix[16];
	GLint viewport[4];
	float direction[3];
	float dist;

	glGetFloatv( GL_MODELVIEW_MATRIX, model);
	glGetFloatv( GL_PROJECTION_MATRIX, proj);
	glGetIntegerv( GL_VIEWPORT, viewport);

    x_gluMultMatricesf(model, proj, finalMatrix);
    if (!x_gluInvertMatrixf(finalMatrix, finalMatrix)) return;

	primary.o.x = origin.v[0];
	primary.o.y = origin.v[1];
	primary.o.z = origin.v[2];

	//
	// set up a 2d view
	//
	glPushAttrib( GL_ALL_ATTRIB_BITS );	   
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	gluOrtho2D(0, viewport[2], viewport[3], 0);	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	sxDelta = (float)(viewport[2]-1) / (float)(xRes);
	syDelta = (float)(viewport[3]-1) / (float)(yRes);

	i = 0;
	sy = 0.0f;
	for (int y = 0; y < yRes; y++)
	{
		sx = 0.0f;
		CVector yScanline = topLeft - upStep * (float)y;

		for (int x = 0; x < xRes; x++)
		{
			//gluUnProject( sx, sy, 1.0, model, proj, viewport, &direction[0], &direction[1], &direction[2] );
			x_gluUnProject( sx, sy, 1.0, finalMatrix, viewport, &direction[0], &direction[1], &direction[2] );

			id = screenTexture[ ((int)sy*viewport[2]+(int)sx)*3 ];

			direction[0] -= origin.v[0];
			direction[1] -= origin.v[1];
			direction[2] -= origin.v[2];

			dist = 1.0f / sqrtf( direction[0]*direction[0] + direction[1]*direction[1] + direction[2]*direction[2] );
			direction[0] *= dist;
			direction[1] *= dist;
			direction[2] *= dist;

			primary.d.x = direction[0];
			primary.d.y = direction[1];
			primary.d.z = direction[2];

			pixel = traceCRay( &primary, 1 );

			int r = Float2Int(pixel.r); if (r < 0) r = 0; if (r > 255) r = 255;
			int g = Float2Int(pixel.g); if (g < 0) g = 0; if (g > 255) g = 255;
			int b = Float2Int(pixel.b); if (b < 0) b = 0; if (b > 255) b = 255;

			dest[i++] = r;
			dest[i++] = g;
			dest[i++] = b;

			sx += sxDelta;
		}

		sy += syDelta;
	}

	//
	// End 2d view
	//
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopAttrib();
}



void CScene::RenderGL( char unique )
{
	int i;

	if (unique==0) {
		for (i=0; i<numObjects; i++)
			object[i]->RenderGL( unique );
		return;
	}

	for (i=0; i<numObjects; i++) {
		object[i]->RenderGL( i+1 );
	}
}
