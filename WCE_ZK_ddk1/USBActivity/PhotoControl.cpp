#include "stdafx.h"
#include "PhotoControl.h"

CEffect	PhotoControl::effectView;
GxxDCContainer* PhotoControl::pDcContainer = NULL;
wstring PhotoControl::sPlayFile;
int PhotoControl::degree = 0;
CImage*	PhotoControl::pImage = NULL;
int PhotoControl::zoom = 100;


/*GxxDCContainer* PhotoControl::pDcContainer = NULL;
GXString PhotoControl::sPlayFile;
int PhotoControl::degree = 0;
CImage*	PhotoControl::pImage = NULL;
int PhotoControl::zoom = 100;
CEffect	PhotoControl::effectView*/;