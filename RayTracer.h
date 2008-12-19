// Author : Jean-Rene Bedard (jrbedard@gmail.com)

// RayTracer.h : main header file for the RayTracer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CRayTracerApp:
// See RayTracer.cpp for the implementation of this class
//

class CRayTracerApp : public CWinApp
{
public:
	CRayTracerApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRayTracerApp theApp;