// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#pragma once


#include <vector>


#include "FloatToInt.h"
#include "CLight.h"
#include "CObjectRT.h"






class CScene
{
public:
	CScene();
	~CScene();

	//std::vector<CObjectRT*>	m_object_list;
	//std::vector<CLight*>	m_light_list;

	int numObjects; CObjectRT **object;
	int numLights; CLight **light;

	CCamera camera;

	CColor background;

	int maxDepth,useHardware;

	void resetObjects(int n);
	void resetLights(int n);
	void resetObjectsOnly();

	void setResolution(int xres, int yres);

	void beginFrame();

	void RenderGL( char unique );
	void render(CPoint3 origin, unsigned char *dest);

	
	GLubyte *screenTexture;
	GLubyte id;

	int xRes, yRes;

private:
	CColor traceCRay(CRay *r, int depth);


	CVector rightStep, upStep, topLeft;


	CPlaneIntersection intersectionPlane;
	
};




static void x_gluMultMatricesf(const GLfloat a[16], const GLfloat b[16], GLfloat r[16])
{
    int i, j;

    for (i = 0; i < 4; i++) 
	{
		for (j = 0; j < 4; j++) 
		{
			r[i*4+j] = 
			a[i*4+0]*b[0*4+j] +
			a[i*4+1]*b[1*4+j] +
			a[i*4+2]*b[2*4+j] +
			a[i*4+3]*b[3*4+j];
		}
    }
}

static void x_gluMakeIdentityf(GLfloat m[16])
{
    m[0+4*0] = 1; m[0+4*1] = 0; m[0+4*2] = 0; m[0+4*3] = 0;
    m[1+4*0] = 0; m[1+4*1] = 1; m[1+4*2] = 0; m[1+4*3] = 0;
    m[2+4*0] = 0; m[2+4*1] = 0; m[2+4*2] = 1; m[2+4*3] = 0;
    m[3+4*0] = 0; m[3+4*1] = 0; m[3+4*2] = 0; m[3+4*3] = 1;
}

static int x_gluInvertMatrixf(const GLfloat src[16], GLfloat inverse[16])
{
    int i, j, k, swap;
    float t;
    GLfloat temp[4][4];

    for (i=0; i<4; i++) {
	for (j=0; j<4; j++) {
	    temp[i][j] = src[i*4+j];
	}
    }
    x_gluMakeIdentityf(inverse);

    for (i = 0; i < 4; i++) {
	/*
	** Look for largest element in column
	*/
	swap = i;
	for (j = i + 1; j < 4; j++) {
	    if (fabs(temp[j][i]) > fabs(temp[i][i])) {
		swap = j;
	    }
	}

	if (swap != i) {
	    /*
	    ** Swap rows.
	    */
	    for (k = 0; k < 4; k++) {
		t = temp[i][k];
		temp[i][k] = temp[swap][k];
		temp[swap][k] = t;

		t = inverse[i*4+k];
		inverse[i*4+k] = inverse[swap*4+k];
		inverse[swap*4+k] = t;
	    }
	}

	if (temp[i][i] == 0) {
	    /*
	    ** No non-zero pivot.  The matrix is singular, which shouldn't
	    ** happen.  This means the user gave us a bad matrix.
	    */
	    return GL_FALSE;
	}

	t = temp[i][i];
	for (k = 0; k < 4; k++) {
	    temp[i][k] /= t;
	    inverse[i*4+k] /= t;
	}
	for (j = 0; j < 4; j++) {
	    if (j != i) {
		t = temp[j][i];
		for (k = 0; k < 4; k++) {
		    temp[j][k] -= temp[i][k]*t;
		    inverse[j*4+k] -= inverse[i*4+k]*t;
		}
	    }
	}
    }
    return GL_TRUE;
}

inline void x_gluMultMatrixVec(const GLfloat matrix[16], const GLfloat in[4], GLfloat out[4])
{
    int i;

    for (i=0; i<4; i++) {
	out[i] = 
	    in[0] * matrix[0*4+i] +
	    in[1] * matrix[1*4+i] +
	    in[2] * matrix[2*4+i] +
	    in[3] * matrix[3*4+i];
    }
}

inline GLint x_gluUnProject( GLfloat winx, GLfloat winy, GLfloat winz,
					  float finalMatrix[16],  const GLint viewport[4], GLfloat *objx, GLfloat *objy, GLfloat *objz)
{
    float in[4];
    float out[4];
	float o3;

    in[0]=winx;
    in[1]=winy;
    in[2]=winz;
    in[3]=1.0;

    /* Map x and y from window coordinates */
    in[0] = (in[0] - viewport[0]) / viewport[2];
    in[1] = (in[1] - viewport[1]) / viewport[3];
    //in[0] = (in[0] - viewport[0]) * viewport[2];
    //in[1] = (in[1] - viewport[1]) * viewport[3];

    /* Map to range -1 to 1 */
    in[0] = in[0] * 2 - 1;
    in[1] = in[1] * 2 - 1;
    in[2] = in[2] * 2 - 1;

    x_gluMultMatrixVec(finalMatrix, in, out);
    if (out[3] == 0.0) return(GL_FALSE);

	o3 = 1.0f / out[3];
    out[0] *= o3;
    out[1] *= o3;
    out[2] *= o3;
    *objx = out[0];
    *objy = out[1];
    *objz = out[2];
    return(GL_TRUE);
}
