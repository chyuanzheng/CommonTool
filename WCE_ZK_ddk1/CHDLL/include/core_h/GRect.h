#pragma once

static inline LONG SkMax32(LONG a, LONG b) {
	if (a < b)
		a = b;
	return a;
}

static inline LONG SkMin32(LONG a, LONG b) {
	if (a > b)
		a = b;
	return a;
}

struct CE_CONTROL_API  GRect: public tagRECT  {
    static GRect MakeEmpty() {
        GRect r;
        r.setEmpty();
        return r;
    }
    
    static GRect MakeWH(LONG w, LONG h) {
        GRect r;
        r.set(0, 0, w, h);
        return r;
    }
    
    static GRect MakeSize(const GRect& size) {
        GRect r;
        r.set(0, 0, size.width(), size.height());
        return r;
    }
    
    static GRect MakeLTRB(LONG l, LONG t, LONG r, LONG b) {
        GRect rect;
        rect.set(l, t, r, b);
        return rect;
    }
    
    static GRect MakeXYWH(LONG x, LONG y, LONG w, LONG h) {
        GRect r;
        r.set(x, y, x + w, y + h);
        return r;
    }
    
	void operator=(RECT & rect)
	{
		this->setLTRB(rect.left,rect.top,rect.right,rect.bottom);
	}
    /** Return true if the rectangle's width or height are <= 0
    */
    bool isEmpty() const { return left >= right || top >= bottom; }

    /** Returns the rectangle's width. This does not check for a valid rectangle (i.e. nleft <= nright)
        so the result may be negative.
    */
    int width() const { return right - left; }

    /** Returns the rectangle's height. This does not check for a valid rectangle (i.e. ntop <= nbottom)
        so the result may be negative.
    */
    int height() const { return bottom - top; }

    friend int operator==(const GRect& a, const GRect& b) {
        return !memcmp(&a, &b, sizeof(a));
    }

    friend int operator!=(const GRect& a, const GRect& b) {
        return memcmp(&a, &b, sizeof(a));
    }


    /** Set the rectangle to (0,0,0,0)
    */
    void setEmpty() { memset(this, 0, sizeof(*this)); }

    void set(LONG nleft, LONG ntop, LONG nright, LONG nbottom) {
        left   = nleft;
        top    = ntop;
        right  = nright;
        bottom = nbottom;
    }
    // alias for set(l, t, r, b)
    void setLTRB(LONG nleft, LONG ntop, LONG nright, LONG nbottom) {
        this->set(nleft, ntop, nright, nbottom);
    }

    void setXYWH(LONG x, LONG y, LONG width, LONG height) {
        left = x;
        top = y;
        right = x + width;
        bottom = y + height;
    }



    
    /** Offset set the rectangle by adding dx to its nleft and nright,
        and adding dy to its ntop and nbottom.
    */
    void offset(LONG dx, LONG dy) {
        left   += dx;
        top    += dy;
        right  += dx;
        bottom += dy;
    }


    /** Inset the rectangle by (dx,dy). If dx is positive, then the sides are moved inwards,
        making the rectangle narrower. If dx is negative, then the sides are moved outwards,
        making the rectangle wider. The same hods true for dy and the ntop and nbottom.
    */
    void inset(LONG dx, LONG dy) {
        left   += dx;
        top    += dy;
        right  -= dx;
        bottom -= dy;
    }

    bool quickReject(int l, int t, int r, int b) const {
        return l >= right || left >= r || t >= bottom || top >= b;
    }
    
    /** Returns true if (x,y) is inside the rectangle and the rectangle is not
        empty. The nleft and ntop are considered to be inside, while the nright
        and nbottom are not. Thus for the rectangle (0, 0, 5, 10), the
        points (0,0) and (0,9) are inside, while (-1,0) and (5,9) are not.
    */
    bool contains(LONG x, LONG y) const {
        return  (unsigned)(x - left) < (unsigned)(right - left) &&
                (unsigned)(y - top) < (unsigned)(bottom - top);
    }

    /** Returns true if the 4 specified sides of a rectangle are inside or equal to this rectangle.
        If either rectangle is empty, contains() returns false.
    */
    bool contains(LONG nleft, LONG ntop, LONG nright, LONG nbottom) const {
        return  nleft < nright && ntop < nbottom && !this->isEmpty() && // check for empties
                left <= nleft && top <= ntop &&
                right >= nright && bottom >= nbottom;
    }

    /** Returns true if the specified rectangle r is inside or equal to this rectangle.
    */
    bool contains(const GRect& r) const {
        return  !r.isEmpty() && !this->isEmpty() &&     // check for empties
                left <= r.left && top <= r.top &&
                right >= r.right && bottom >= r.bottom;
    }

    /** Return true if this rectangle contains the specified rectangle.
		For speed, this method does not check if either this or the specified
		rectangles are empty, and if either is, its return value is undefined.
		In the debugging build however, we assert that both this and the
		specified rectangles are non-empty.
    */
    bool containsNoEmptyCheck(LONG nleft, LONG ntop,
							  LONG nright, LONG nbottom) const {
		ASSERT(left < right && top < bottom);
        ASSERT(nleft < nright && ntop < nbottom);

        return left <= nleft && top <= ntop &&
			   right >= nright && bottom >= nbottom;
    }
    
    /** If r intersects this rectangle, return true and set this rectangle to that
        intersection, otherwise return false and do not change this rectangle.
        If either rectangle is empty, do nothing and return false.
    */
    bool intersect(const GRect& r) {
        ASSERT(&r);
        return this->intersect(r.left, r.top, r.right, r.bottom);
    }

    /** If rectangles a and b intersect, return true and set this rectangle to
        that intersection, otherwise return false and do not change this
        rectangle. If either rectangle is empty, do nothing and return false.
    */
    bool intersect(const GRect& a, const GRect& b) {
        ASSERT(&a && &b);
        
        if (!a.isEmpty() && !b.isEmpty() &&
                a.left < b.right && b.left < a.right &&
                a.top < b.bottom && b.top < a.bottom) {
            left   = SkMax32(a.left,   b.left);
            top    = SkMax32(a.top,    b.top);
            right  = SkMin32(a.right,  b.right);
            bottom = SkMin32(a.bottom, b.bottom);
            return true;
        }
        return false;
    }
    
    /** If rectangles a and b intersect, return true and set this rectangle to
        that intersection, otherwise return false and do not change this
        rectangle. For speed, no check to see if a or b are empty is performed.
        If either is, then the return result is undefined. In the debug build,
        we assert that both rectangles are non-empty.
    */
    bool intersectNoEmptyCheck(const GRect& a, const GRect& b) {
        ASSERT(&a && &b);
        ASSERT(!a.isEmpty() && !b.isEmpty());
        
        if (a.left < b.right && b.left < a.right &&
                a.top < b.bottom && b.top < a.bottom) {
            left   = SkMax32(a.left,   b.left);
            top    = SkMax32(a.top,    b.top);
            right  = SkMin32(a.right,  b.right);
            bottom = SkMin32(a.bottom, b.bottom);
            return true;
        }
        return false;
    }

    /** If the rectangle specified by nleft,ntop,nright,nbottom intersects this rectangle,
        return true and set this rectangle to that intersection,
        otherwise return false and do not change this rectangle.
        If either rectangle is empty, do nothing and return false.
    */
    bool intersect(LONG nleft, LONG ntop, LONG nright, LONG nbottom) {
        if (nleft < nright && ntop < nbottom && !this->isEmpty() &&
                left < nright && nleft < right && top < nbottom && ntop < bottom) {
            if (left < nleft) left = nleft;
            if (top < ntop) top = ntop;
            if (right > nright) right = nright;
            if (bottom > nbottom) bottom = nbottom;
            return true;
        }
        return false;
    }
    
    /** Returns true if a and b are not empty, and they intersect
    */
    static bool Intersects(const GRect& a, const GRect& b) {
        return  !a.isEmpty() && !b.isEmpty() &&              // check for empties
                a.left < b.right && b.left < a.right &&
                a.top < b.bottom && b.top < a.bottom;
    }
    
    /** Update this rectangle to enclose itself and the specified rectangle.
        If this rectangle is empty, just set it to the specified rectangle. If the specified
        rectangle is empty, do nothing.
    */
    void join(LONG nleft, LONG ntop, LONG nright, LONG nbottom);

    /** Update this rectangle to enclose itself and the specified rectangle.
        If this rectangle is empty, just set it to the specified rectangle. If the specified
        rectangle is empty, do nothing.
    */
    void join(const GRect& r) {
        this->join(r.left, r.top, r.right, r.bottom);
    }

    /** Swap ntop/nbottom or nleft/nright if there are flipped.
        This can be called if the edges are computed separately,
        and may have crossed over each other.
        When this returns, nleft <= nright && ntop <= nbottom
    */
    void sort();

    static const GRect& EmptyIRect() {
		static const GRect gEmpty = GRect::MakeEmpty();
        return gEmpty;
    }
};
