// RayTracerDoc.cpp : implementation of the CRayTracerDoc class
//
// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#include "stdafx.h"

#include "RayTracer.h"

#include "RayTracerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRayTracerDoc

IMPLEMENT_DYNCREATE(CRayTracerDoc, CDocument)

BEGIN_MESSAGE_MAP(CRayTracerDoc, CDocument)
END_MESSAGE_MAP()


// CRayTracerDoc construction/destruction

CRayTracerDoc::CRayTracerDoc()
{
	// TODO: add one-time construction code here

}

CRayTracerDoc::~CRayTracerDoc()
{
}

BOOL CRayTracerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CRayTracerDoc serialization

void CRayTracerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CRayTracerDoc diagnostics

#ifdef _DEBUG
void CRayTracerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRayTracerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRayTracerDoc commands
