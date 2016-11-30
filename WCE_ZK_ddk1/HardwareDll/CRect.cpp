#include "StdAfx.h"
#include "CRect.h"

CRect::CRect(){	left = top = right = bottom = 0;
} 

CRect::CRect(const RECT& src)
{
	left = src.left;
	top = src.top;
	right = src.right;
	bottom = src.bottom;
}

CRect::CRect(int iLeft, int iTop, int iRight, int iBottom)
{
	left = iLeft;
	top = iTop;
	right = iRight;
	bottom = iBottom;
}

BOOL CRect::operator==(CRect &rc)
{
	if (left == rc.left && top == rc.top && right == rc.right && bottom == rc.bottom)
	{
		return TRUE;
	}
	return FALSE;
}

int CRect::Width() const
{
	return right - left;
}

int CRect::Height() const
{
	return bottom - top;
}

void CRect::Empty()
{
	left = top = right = bottom = 0;
}

BOOL CRect::IsRectEmpty()
{
	return ::IsRectEmpty(this);
}

void CRect::Join(const RECT& rc)
{
	if( rc.left < left ) left = rc.left;
	if( rc.top < top ) top = rc.top;
	if( rc.right > right ) right = rc.right;
	if( rc.bottom > bottom ) bottom = rc.bottom;
}

void CRect::ResetOffset()
{
	::OffsetRect(this, -left, -top);
}

void CRect::Normalize()
{
	if( left > right ) { int iTemp = left; left = right; right = iTemp; }
	if( top > bottom ) { int iTemp = top; top = bottom; bottom = iTemp; }
}

void CRect::Offset(int cx, int cy)
{
	::OffsetRect(this, cx, cy);
}

void CRect::Inflate(int cx, int cy)
{
	::InflateRect(this, cx, cy);
}

void CRect::Deflate(int cx, int cy)
{
	::InflateRect(this, -cx, -cy);
}

void CRect::Union(CRect& rc)
{
	::UnionRect(this, this, &rc);
}

void CRect::SetRect(int iLeft, int iTop, int iRight, int iBottom)
{
	left = iLeft;
	top = iTop;
	right = iRight;
	bottom = iBottom;
}

void CRect::MoveTo(POINT pt)
{
	int width = Width();
	int height = Height();
	left = pt.x;
	top = pt.y;
	right = left + width;
	bottom = top + height;
}

CRect CRect::Intersect(CRect &src)
{
	CRect rect(max(left, src.left), max(top, src.top), min(right, src.right), min(bottom, src.bottom));
	return rect;
}

CRect CRect::Offrect(int x, int y)
{
	CRect rect(left+x, top+y, right+x, bottom+y);
	return rect;
}

BOOL CRect::PtInRect(POINT pt)
{
	return ::PtInRect(this, pt);
}