// RayTracerDoc.h : interface of the CRayTracerDoc class

// Author : Jean-Rene Bedard (jrbedard@gmail.com)


#pragma once

class CRayTracerDoc : public CDocument
{
protected: // create from serialization only
	CRayTracerDoc();
	DECLARE_DYNCREATE(CRayTracerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CRayTracerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


