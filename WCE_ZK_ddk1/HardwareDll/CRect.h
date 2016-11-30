#pragma once

class  __declspec(dllexport) CRect : public tagRECT
{
public:
	CRect();
	CRect(const RECT& src);
	CRect(int iLeft, int iTop, int iRight, int iBottom);

	BOOL operator==(CRect &);

	int Width() const;
	int Height() const;
	void Empty();
	BOOL IsRectEmpty();
	void Join(const RECT& rc);
	void ResetOffset();
	void Normalize();
	void Offset(int cx, int cy);
	void Inflate(int cx, int cy);
	void Deflate(int cx, int cy);
	void Union(CRect& rc);
	void SetRect(int iLeft, int iTop, int iRight, int iBottom);
	void MoveTo(POINT pt);
	CRect Intersect(CRect &src);
	CRect Offrect(int x, int y);
	BOOL PtInRect(POINT pt);
};