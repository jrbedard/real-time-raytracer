// Author : Jean-Rene Bedard (jrbedard@gmail.com)

// RayTracerView.cpp : implementation of the CRayTracerView class
//

#include "stdafx.h"
#include "RayTracer.h"

#include "RayTracerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRayTracerView

IMPLEMENT_DYNCREATE(CRayTracerView, CView)

BEGIN_MESSAGE_MAP(CRayTracerView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CRayTracerView construction/destruction

CRayTracerView::CRayTracerView()
{
	// TODO: add construction code here

}

CRayTracerView::~CRayTracerView()
{
}


BOOL CRayTracerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CS_OWNDC;

	return CView::PreCreateWindow(cs);
}



BOOL CRayTracerView::InitOpenGL()
{
	//Get a DC for the Client Area
	m_pCDC = new CClientDC(this);

	//Failure to Get DC
	if( m_pCDC == NULL )
		return FALSE;

	if( !SetupPixelFormat() )	
		return FALSE;

    //Create Rendering Context
	m_hRC = ::wglCreateContext( m_pCDC->GetSafeHdc() );

    //Failure to Create Rendering Context
    if( m_hRC == 0 )
        return FALSE;

	//Make the RC Current
	if( ::wglMakeCurrent( m_pCDC->GetSafeHdc(), m_hRC ) == FALSE )
		return FALSE;

	// Usual OpenGL stuff
/*
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClearDepth(1.0f);
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_TEXTURE_2D );
	glLineWidth( 2.0f );
	glPointSize( 3.0f );
*/
	// Set filled polygon mode as default (not wireframe)
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	m_app.wireframe = 0;

	// Enable face culling
	glDisable( GL_CULL_FACE );

	m_app.Resize(340,480);

	m_app.raytracer.InitScene();

	return TRUE;
}


BOOL CRayTracerView::SetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd
		1,                                // version number
		PFD_DRAW_TO_WINDOW |              // support window
		PFD_SUPPORT_OPENGL |              // support OpenGL
		PFD_DOUBLEBUFFER,                 // double buffered
		PFD_TYPE_RGBA,                    // RGBA type
		24,                               // 24-bit color depth
		0, 0, 0, 0, 0, 0,                 // color bits ignored
		0,                                // no alpha buffer
		0,                                // shift bit ignored
		0,                                // no accumulation buffer
		0, 0, 0, 0,                       // accumulation bits ignored
		16,                               // 16-bit z-buffer
		0,                                // no stencil buffer
		0,                                // no auxiliary buffer
		PFD_MAIN_PLANE,                   // main layer
		0,                                // reserved
		0, 0, 0                           // layer masks ignored
	};

   int m_nPixelFormat = ::ChoosePixelFormat( m_pCDC->GetSafeHdc(), &pfd );

    if ( m_nPixelFormat == 0 )
        return FALSE;

    return ::SetPixelFormat( m_pCDC->GetSafeHdc(), m_nPixelFormat, &pfd );
}



int CRayTracerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	if ( !InitOpenGL() )
	{
		MessageBox( "Error setting up OpenGL!", "Init Error!",
			MB_OK | MB_ICONERROR );
		return -1;
	}

	oldMouseX = MouseX = 0;
	oldMouseY = MouseY = 0;
	leftClick = false;
	rightClick = false;

	SetTimer(1,16,0);

	srand(time(NULL));


	return 0;
}


// CRayTracerView drawing

void CRayTracerView::OnDraw(CDC* /*pDC*/)
{
	CRayTracerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	wglMakeCurrent( m_pCDC->GetSafeHdc(), m_hRC); 

	m_app.GLUpdate();

	SwapBuffers(m_pCDC->GetSafeHdc());

	wglMakeCurrent( NULL, NULL ); 

	ValidateRect(NULL);
}


void CRayTracerView::OnTimer(UINT nIDEvent)
{
	InvalidateRect(NULL);
}


void CRayTracerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	ChangeResolution(cx, cy);
}


void CRayTracerView::ChangeResolution(int x, int y)
{
	wglMakeCurrent( m_pCDC->GetSafeHdc(), m_hRC );
	glViewport( 0, 0, x, y);

	m_app.Resize( x, y );

	m_app.raytracer.scene.setResolution(x,y);

	wglMakeCurrent( NULL, NULL );
	InvalidateRect(NULL);
}


int CRayTracerView::OnEraseBkgnd(CDC* pDC) 
{ 
	// TODO: Add your message handler code here and/or call default 

	return 1; 
} 



void CRayTracerView::OnDestroy()
{
	m_app.raytracer.destroyScene();

	//if (screenTexture)
	//	delete [] screenTexture;

	CView::OnDestroy(); 

	wglMakeCurrent( NULL, NULL ); 
	wglDeleteContext( m_hRC ); 
	::ReleaseDC( m_hWnd, m_pCDC->GetSafeHdc() );

	delete m_pCDC;
}




void CRayTracerView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	oldMouseX = MouseX = point.x;
	oldMouseY = MouseY = point.y;

	leftClick = true;
	//OnLButtonDown(nFlags, point);
}

void CRayTracerView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	oldMouseX = MouseX = 0;
	oldMouseY = MouseY = 0;

	leftClick = false;
	//OnLButtonUp(nFlags, point);
}


void CRayTracerView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	oldMouseX = MouseX = point.x;
	oldMouseY = MouseY = point.y;

	rightClick = true;
	//OnLButtonDown(nFlags, point);
}

void CRayTracerView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	oldMouseX = MouseX = 0;
	oldMouseY = MouseY = 0;

	rightClick = false;
	//OnLButtonUp(nFlags, point);
}


void CRayTracerView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ( leftClick ) 
	{
		oldMouseX = MouseX;
		oldMouseY = MouseY;

		MouseX = point.x;
		MouseY = point.y;

		m_app.yaw += (MouseX - oldMouseX);
		m_app.pitch += (MouseY - oldMouseY);
	}
	else if( rightClick )
	{
		oldMouseX = MouseX;
		oldMouseY = MouseY;

		MouseX = point.x;
		MouseY = point.y;

		//float deltaY = (float)(MouseX - oldMouseX);
		float deltaY = (float)(MouseY - oldMouseY);
		m_app.ViewPosition.v[0] += 0.5f*deltaY*(m_app.raytracer.scene.camera.dir.x);
		m_app.ViewPosition.v[1] += 0.5f*deltaY*(m_app.raytracer.scene.camera.dir.y);
		m_app.ViewPosition.v[2] += 0.5f*deltaY*(m_app.raytracer.scene.camera.dir.z);

		//m_app.ViewPosition.v[2] += delta*m_app.raytracer.scene.camera.p.z;
	}

	//OnMouseMove(nFlags, point);
}




// CRayTracerView diagnostics

#ifdef _DEBUG
void CRayTracerView::AssertValid() const
{
	CView::AssertValid();
}

void CRayTracerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRayTracerDoc* CRayTracerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRayTracerDoc)));
	return (CRayTracerDoc*)m_pDocument;
}
#endif //_DEBUG


// CRayTracerView message handlers
