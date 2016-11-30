// iPodPlayer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "iPodConfig.h"

#include "iPodPlayer.h"
#include "iPodPlayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CiPodPlayerApp

BEGIN_MESSAGE_MAP(CiPodPlayerApp, CWinApp)
END_MESSAGE_MAP()


// CiPodPlayerApp construction
CiPodPlayerApp::CiPodPlayerApp()
	: CWinApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CiPodPlayerApp object
CiPodPlayerApp theApp;

// CiPodPlayerApp initialization

BOOL CiPodPlayerApp::InitInstance()
{
#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
    // SHInitExtraControls should be called once during your application's initialization to initialize any
    // of the Windows Mobile specific controls such as CAPEDIT and SIPPREF.
    SHInitExtraControls();
#endif // WIN32_PLATFORM_PSPC || WIN32_PLATFORM_WFSP

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CiPodPlayerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
