// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#include "CApp.h"




CApp::CApp()
{
	RunGame			= 1;
	glWidth			= 0;
	glHeight		= 0;
	ViewPosition	= CPoint3(60,-47,41);
	yaw				= -44.0f;
	pitch			= -71.0f;
	roll			= 0.0f;
	oldMouseX		= 0;
	oldMouseY		= 0;
	MouseX			= 0;
	MouseY			= 0;
	Posx			= 0;
	Posy			= 0;

	wireframe		= 0;
	CRaytraced		= 1;
	showhelp		= 0;
	useHardware		= 0;
	showMask		= 0;
	saveTGA			= 0;
}


CApp::~CApp()
{

}




//========================================================================
// Main update Routine (moset rendering code goes here)
//========================================================================
void CApp::GLUpdate()
{
	double time;
	int x,y;
	unsigned int i;
	float cInv = 1.0f / 255.0f;

//	time = glfwGetTime();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(pitch,	1,0,0);
	glRotatef(roll,		0,1,0);
	glRotatef(yaw,		0,0,1);
	glTranslatef( -ViewPosition.v[0], -ViewPosition.v[1], -ViewPosition.v[2]);


	if ((CRaytraced && useHardware) || showMask)
	{
		raytracer.updateScene( ViewPosition, NULL, 1 );
		if (!showMask) 
		{
			glFlush();
			glFinish();
			glPixelStorei(GL_PACK_ALIGNMENT, 1);
			glPixelStorei(GL_PACK_ROW_LENGTH,  glWidth);
			if (!showMask) glReadPixels(0, 0, glWidth, glHeight, GL_RGB, GL_UNSIGNED_BYTE, raytracer.scene.screenTexture);
			if (!showMask) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glFlush();
			glFinish();
		}
	}

	int XRES = raytracer.scene.xRes;
	int YRES = raytracer.scene.yRes;

	if (!showMask) 
	{
		if (CRaytraced)
		{
			raytracer.updateScene( ViewPosition, raytracer.screen, useHardware );
			i = 0;

			x_start_2d( XRES-1, YRES-1 );

			for (y=0; y<YRES; y++) 
			{
				glBegin( GL_TRIANGLE_STRIP );
				for (x=0; x<XRES; x++)
				{
					i = y*XRES*3+x*3;
					glColor3f( raytracer.screen[i+0]*cInv, raytracer.screen[i+1]*cInv, raytracer.screen[i+2]*cInv );
					glVertex2i( x,YRES-y );

					i += XRES*3;
					glColor3f( raytracer.screen[i+0]*cInv, raytracer.screen[i+1]*cInv, raytracer.screen[i+2]*cInv );
					glVertex2i( x,YRES-y-1 );
				}
				glEnd();
			}
			x_end_2d();
		} 
		else 
		{
			raytracer.updateScene( ViewPosition, NULL, 0 );
		}
	}

	// FPS Counter
	glColor3f( 1,1,1 );
	//TEXT.set_size( 12 );
	//TEXT.draw( 0,0, "%0.2f FPS\n", 1.0 / (glfwGetTime()-time) );

	glColor3d( 0.8,0.8,0.8 );

	if (showhelp && !saveTGA) 
	{
		/*
		TEXT.set_size( 12 );
		TEXT.draw( 0,20, "xres=%d (x/X)", XRES);
		TEXT.draw( 0,32, "yres=%d (y/Y)", YRES);

		TEXT.draw( 0,50, "TOGGLES");
		TEXT.draw( 0,62, "W : Wireframe (%s)", wireframe ? "ON":"OFF");
		TEXT.draw( 0,74, "E : Hardware Acceleration (%s)", useHardware ? "ON":"OFF");
		TEXT.draw( 0,86, "R : Draw Mode (%s)", CRaytraced ? "CRaytraced":"OpenGL");		
		TEXT.draw( 0,98, "M : Hardware Mask (%s)", showMask ? "ON":"OFF");		
		TEXT.draw( 0,110, "P : Take TGA screenshot");
		TEXT.draw( 0,122, "H : Help");

		TEXT.set_size( 8 );
		glColor3f( 1,1,0 );
		TEXT.draw( 0,glHeight-14, "pos(%0.2f %0.2f %0.2f)  Look(%0.2f %0.2f %0.2f)\n", ViewPosition.v[0], ViewPosition.v[1], ViewPosition.v[2], yaw, pitch, roll );
		*/
	}
/*
	// Save screenshot
	if (saveTGA) 
	{
		char filename[30];
		FILE *fp;
		x_image img;

		fp = NULL;
		i = 1;
		do {
			if (fp) fclose( fp );
			sprintf( filename, "RayTracer%d.tga", i++ );
			fp = fopen( filename, "rt" );
		} while (fp);

		img.grab_tga( filename, glWidth, glHeight, 24 );

		saveTGA = 0;
	}
*/
	// Swap buffers
	//glfwSwapBuffers();

	// Update key states
	//keyUnBuffered( glfwGetTime()-time );
}


void CApp::x_start_2d( int width, int height )
{
	GLint vPort[4];

	glPushAttrib( GL_ALL_ATTRIB_BITS );   
	glGetIntegerv(GL_VIEWPORT, vPort);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	if (width<0 || height<0)
		gluOrtho2D(0, vPort[2], vPort[3], 0);
	else
		gluOrtho2D(0, width, height, 0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void CApp::x_end_2d()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();   
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glPopAttrib();
}


//========================================================================
// Resize() - GLFW window resize callback function
//========================================================================

void CApp::Resize( int w, int h )
{
	glWidth = w;
	glHeight = h;
	//glHeight = h > 0 ? h : 1;   // Prevent division by zero in aspect calc.

	glViewport(0, 0, glWidth, glHeight);

	glEnable(GL_TEXTURE_2D);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,(GLfloat)glWidth/(GLfloat)glHeight,1.0f, 10000 );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glfwPollEvents();
	Posx = 0;
	Posy = 0;

	//if (raytracer.scene.screenTexture) delete [] raytracer.scene.screenTexture;

	raytracer.scene.screenTexture = new GLubyte[ w*h*3 ];
}



