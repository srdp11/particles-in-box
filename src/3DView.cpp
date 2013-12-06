/* 3DView.h

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
	03 0ct 2008 - cursors
	05 Nov 2008 - C3DStatic class

*/


#include "stdafx.h"
#include "3DView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static SCursorDesc g_CursorDescs[] = {
	{ IDC_ARROW, NULL },
	{ IDC_IBEAM, NULL },
	{ IDC_WAIT, NULL },
	{ IDC_CROSS, NULL },
	{ IDC_UPARROW, NULL },
	{ IDC_SIZEALL, NULL },
	{ IDC_SIZENWSE, NULL },
	{ IDC_SIZENESW, NULL },
	{ IDC_SIZEWE, NULL },
	{ IDC_SIZENS, NULL }
};

/////////////////////////////////////////////////////////////////////////////
// C3DView

IMPLEMENT_DYNCREATE(C3DView, CView)

C3DView::C3DView()
{
}

C3DView::~C3DView()
{
}

BEGIN_MESSAGE_MAP(C3DView, CView)
	//{{AFX_MSG_MAP(C3DView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3DView drawing

void C3DView::OnDraw(CDC *pDC)
{
}


/////////////////////////////////////////////////////////////////////////////
// C3DView diagnostics

#ifdef _DEBUG
void C3DView::AssertValid() const
{
	CView::AssertValid();
}

void C3DView::Dump(CDumpContext &dc) const
{
	CView::Dump(dc);
}

#endif //_DEBUG

void C3DView::ChangeCursor()
{
	CursorTypeEnum NewCursor = GetRenderer()->GetCursor();
	//if (NewCursor == m_OldCursor)
	//	return; // do nothing
	if (!g_CursorDescs[NewCursor].hCursor)
	{
		g_CursorDescs[NewCursor].hCursor = AfxGetApp()->LoadStandardCursor(g_CursorDescs[NewCursor].pszCursorName);
	}
	SetCursor(g_CursorDescs[NewCursor].hCursor);
	m_OldCursor = NewCursor;
}

/////////////////////////////////////////////////////////////////////////////
// C3DView message handlers

int C3DView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CreateRenderer();
	m_OldCursor = GetRenderer()->GetCursor();
	
	return 0;
}

void C3DView::OnDestroy() 
{
	DestroyRenderer();	
	CView::OnDestroy();
}

void C3DView::OnSize(UINT nType, int cx, int cy) 
{
	if (GetRenderer())
		GetRenderer()->OnSize(cx,cy);
	CView::OnSize(nType, cx, cy);
}

void C3DView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (GetRenderer())
	{
		GetRenderer()->OnLButtonDown(nFlags, point.x, point.y);
		ChangeCursor();
	}
	SetCapture();
	CView::OnLButtonDown(nFlags, point);
}

void C3DView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (GetRenderer())
	{
		GetRenderer()->OnMouseMove(nFlags, point.x, point.y);
		ChangeCursor();
	}
	CView::OnMouseMove(nFlags, point);
}

void C3DView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (GetRenderer())
	{
		GetRenderer()->OnLButtonUp(nFlags, point.x, point.y);
		ChangeCursor();
	}
	ReleaseCapture();
	CView::OnLButtonUp(nFlags, point);
}

void C3DView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if (GetRenderer())
	{
		GetRenderer()->OnRButtonDown(nFlags, point.x, point.y);
		ChangeCursor();
	}
	SetCapture();
	CView::OnRButtonDown(nFlags, point);
}

void C3DView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	if (GetRenderer())
	{
		GetRenderer()->OnRButtonUp(nFlags, point.x, point.y);
		ChangeCursor();
	}
	ReleaseCapture();
	CView::OnRButtonUp(nFlags, point);
}

void C3DView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (GetRenderer())
		GetRenderer()->OnKeyDown(nChar, nRepCnt, nFlags); 
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void C3DView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if (GetRenderer())
		GetRenderer()->Redraw();	
}


