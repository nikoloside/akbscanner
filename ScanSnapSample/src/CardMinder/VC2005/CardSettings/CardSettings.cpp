//******************************************************************************
//
//   ScanSnap Sample Program
//
//   Copyright PFU LIMITED 2012
//
//******************************************************************************

// CardSettings.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CardSettings.h"
#include "CardSettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define	CARDIFSETTINGS_WINDOW_CLASS	_T("CardSettings MainWndClass")


// CCardSettingsApp

BEGIN_MESSAGE_MAP(CCardSettingsApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCardSettingsApp construction

CCardSettingsApp::CCardSettingsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCardSettingsApp object

CCardSettingsApp theApp;


// CCardSettingsApp initialization

BOOL CCardSettingsApp::InitInstance()
{
	CWinApp::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	//SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	// Set window class
	WNDCLASS stClass;
	HINSTANCE hInst;
	hInst = AfxGetInstanceHandle();
	if (GetClassInfo(hInst, _T("#32770"), &stClass)) {
		stClass.lpszClassName = CARDIFSETTINGS_WINDOW_CLASS;
		AfxRegisterClass(&stClass);
	}

	CCardSettingsDlg dlg;
	m_pMainWnd = &dlg;

	// Get ini file path
    CString strModulePath;
    ::GetModuleFileName(m_hInstance, strModulePath.GetBuffer(MAX_PATH), MAX_PATH);
    strModulePath.ReleaseBuffer();
    TCHAR szDrive[_MAX_DRIVE] = {0};
    TCHAR szDir[_MAX_DIR] = {0};
    ::_tsplitpath_s(strModulePath, szDrive, _MAX_DRIVE, szDir, _MAX_DIR, NULL, 0, NULL, 0);
    ::wsprintf(dlg.m_szIniPath, _T("%s%sCardSettings.ini"), szDrive, szDir);

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
