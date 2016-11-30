#include "StdAfx.h"
#include "GRect.h"

void GRect::join(LONG nleft, LONG ntop, LONG nright, LONG nbottom) {
	// do nothing if the params are empty
	if (nleft >= nright || ntop >= nbottom) {
		return;
	}

	// if we are empty, just assign
	if (left >= right || top >= bottom) {
		this->set(nleft, ntop, nright, nbottom);
	} else {
		if (nleft < left) left = nleft;
		if (ntop < top) top = ntop;
		if (nright > right) right = nright;
		if (nbottom > bottom) bottom = nbottom;
	}
}

void GRect::sort() {
	if (left > right) {
		std::swap(left, right);
	}
	if (top > bottom) {
		std::swap(top, bottom);
	}
}