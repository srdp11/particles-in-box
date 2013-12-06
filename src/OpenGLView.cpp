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

#include "stdafx.h"

#include "OpenGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenGLView

IMPLEMENT_DYNCREATE(COpenGLView, C3DView)

BEGIN_MESSAGE_MAP(COpenGLView, C3DView)
	//{{AFX_MSG_MAP(COpenGLView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, C3DView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, C3DView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, C3DView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenGLView construction/destruction

COpenGLView::COpenGLView()
{
	m_pDC = NULL;
	m_pDefaultRenderer = NULL;
}

COpenGLView::~COpenGLView()
{
}

BOOL COpenGLView::PreCreateWindow(CREATESTRUCT &cs)
{
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	return C3DView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLView drawing

void COpenGLView::OnDraw(CDC *pDC)
{
}

//virtual
void COpenGLView::CreateRenderer()
{
	m_pDefaultRenderer = new COpenGL_3D();
}

//virtual
void COpenGLView::DestroyRenderer()
{
	if (m_pDefaultRenderer)
		delete m_pDefaultRenderer;
	m_pDefaultRenderer = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLView printing

BOOL COpenGLView::OnPreparePrinting(CPrintInfo *pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenGLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenGLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLView diagnostics

#ifdef _DEBUG
void COpenGLView::AssertValid() const
{
	C3DView::AssertValid();
}

void COpenGLView::Dump(CDumpContext &dc) const
{
	C3DView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COpenGLView message handlers

int COpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (C3DView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pDC = new CClientDC(this);
	HDC hDC = m_pDC->GetSafeHdc();
	if (GetRenderer()->Init(hDC) != LOGICAL_TRUE)
		return -1;

	return 0;
}

void COpenGLView::OnDestroy() 
{
	delete m_pDC;
	C3DView::OnDestroy();
}

BOOL COpenGLView::OnEraseBkgnd(CDC *pDC) 
{
	return TRUE;
}



