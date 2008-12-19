// Author : Jean-Rene Bedard (jrbedard@gmail.com)

// RayTracerView.h : interface of the CRayTracerView class
//


#pragma once

#include "RayTracerDoc.h"
#include "CApp.h"

class CRayTracerView : public CView
{
protected: // create from serialization only
	CRayTracerView();
	DECLARE_DYNCREATE(CRayTracerView)

// Attributes
public:
	CRayTracerDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view

	virtual void OnSize(UINT nType, int cx, int cy);
	virtual void OnDestroy();
	virtual int OnEraseBkgnd(CDC* pDC);
	virtual void OnTimer(UINT nIDEvent);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);


	BOOL SetupPixelFormat();
	BOOL InitOpenGL();

	void ChangeResolution(int x, int y);

	CPalette   m_cPalette;

	CApp	   m_app;

	//HDC		   m_hDC;
	CDC*	   m_pCDC;
	HGLRC	   m_hRC;

protected:

	bool leftClick, rightClick;

	int	oldMouseX, oldMouseY;
	int MouseX, MouseY;


// Implementation
public:
	virtual ~CRayTracerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RayTracerView.cpp
inline CRayTracerDoc* CRayTracerView::GetDocument() const
   { return reinterpret_cast<CRayTracerDoc*>(m_pDocument); }
#endif

