/* OpenGLView.h

The MIT License (MIT)

Copyright (c) 2007 Evgeny A. Kozhevnikov <evgeny@kozhevnikov.org>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


Revision history:
	?? ??? ???? - initial creation
	05 Nov 2008 - COpenGLStatic class

*/

#ifndef __OPENGL_VIEW_H_INCLUDED__
#define __OPENGL_VIEW_H_INCLUDED__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <gl\gl.h>
#include <gl\glaux.h>

#include "3DView.h"
#include "OpenGLRenderer.h"

class COpenGLView : public C3DView
{
protected: // create from serialization only
	COpenGLView();

	DECLARE_DYNCREATE(COpenGLView)

// Attributes
public:

// Operations
public:

// Overrides
	//{{AFX_VIRTUAL(COpenGLView)
	public:
	virtual void OnDraw(CDC *pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT &cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo *pInfo);
	virtual void OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo);
	virtual void OnEndPrinting(CDC *pDC, CPrintInfo *pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COpenGLView();
	virtual CRenderer *GetRenderer() { return m_pDefaultRenderer; };
	virtual void CreateRenderer();
	virtual void DestroyRenderer();
	virtual void SetDefaultView() { GetRenderer()->SetDefaultView(); }
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext &dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COpenGLView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CClientDC *m_pDC;
	CRenderer *m_pDefaultRenderer;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __OPENGL_VIEW_H_INCLUDED__
