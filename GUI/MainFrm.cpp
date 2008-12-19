// MainFrm.cpp : implementation of the CMainFrame class
//
// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#include "stdafx.h"
#include "RayTracer.h"

#include "MainFrm.h"

#include "RayTracerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_COMMAND(ID_RESOLUTION_160X120, OnResolution160x120)
	ON_COMMAND(ID_RESOLUTION_340X280, OnResolution340x280)
	ON_COMMAND(ID_RESOLUTION_640X480, OnResolution640x480)
	ON_COMMAND(ID_RESOLUTION_800X600, OnResolution800x600)
END_MESSAGE_MAP()


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;

	cs.cx = 340;
	cs.cy = 280;

	return TRUE;
}


void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd)
{
    CFrameWnd::OnPaletteChanged(pFocusWnd);

    if (pFocusWnd != this)
        OnQueryNewPalette();
}


BOOL CMainFrame::OnQueryNewPalette()
{
    WORD   i;
    CPalette   *pOldPal;
    CRayTracerView *pView = (CRayTracerView *)GetActiveView();
    CClientDC   dc(pView);

    pOldPal = dc.SelectPalette(&pView->m_cPalette, FALSE);
    i = dc.RealizePalette();
    dc.SelectPalette(pOldPal, FALSE);

    if (i > 0)
        InvalidateRect(NULL);

    return CFrameWnd::OnQueryNewPalette();
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers


void CMainFrame::OnResolution160x120()
{
	CRayTracerView *pView = (CRayTracerView *)GetActiveView();
	pView->ChangeResolution(160,120);
}

void CMainFrame::OnResolution340x280()
{
	CRayTracerView *pView = (CRayTracerView *)GetActiveView();
	pView->ChangeResolution(340,280);
}

void CMainFrame::OnResolution640x480()
{
	CRayTracerView *pView = (CRayTracerView *)GetActiveView();
	pView->ChangeResolution(640,480);
}

void CMainFrame::OnResolution800x600()
{
	CRayTracerView *pView = (CRayTracerView *)GetActiveView();
	pView->ChangeResolution(800,600);
}
