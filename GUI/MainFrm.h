// MainFrm.h : interface of the CMainFrame class
//
// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#pragma once
class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	afx_msg void OnPaletteChanged( CWnd* pFocusWnd );
	afx_msg BOOL OnQueryNewPalette();



// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnResolution160x120();
	afx_msg void OnResolution340x280();
	afx_msg void OnResolution640x480();
	afx_msg void OnResolution800x600();
};


