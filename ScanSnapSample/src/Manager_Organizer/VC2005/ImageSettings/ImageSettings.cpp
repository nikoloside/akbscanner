//******************************************************************************
//
//   ScanSnap Sample Program
//
//   Copyright PFU LIMITED 2012
//
//******************************************************************************

// ImageSettings.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ImageSettings.h"
#include "ImageSettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define	SSIFSETTINGS_WINDOW_CLASS	_T("ImageSettings MainWndClass")

#define SECTION_COMMON		_T("COMMON")
#define KEY_RADIOBUTTON		_T("RADIOBUTTON")


// CImageSettingsApp

BEGIN_MESSAGE_MAP(CImageSettingsApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CImageSettingsApp construction

CImageSettingsApp::CImageSettingsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CImageSettingsApp object

CImageSettingsApp theApp;


// CImageSettingsApp initialization

BOOL CImageSettingsApp::InitInstance()
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
	if(GetClassInfo(hInst, _T("#32770"), &stClass)){
		stClass.lpszClassName = SSIFSETTINGS_WINDOW_CLASS;
		AfxRegisterClass(&stClass);
	}

	// CommandLine(Get IniFile Path)
	CCommandLineInfo szCmd;
	ParseCommandLine(szCmd);

	// Get new file from ini file
    if (szCmd.m_strFileName.IsEmpty()) {
        CString strModulePath;
        ::GetModuleFileName(m_hInstance, strModulePath.GetBuffer(MAX_PATH), MAX_PATH);
        strModulePath.ReleaseBuffer();
        TCHAR szDrive[_MAX_DRIVE] = {0};
        TCHAR szFolder[_MAX_DIR] = {0};
        ::_tsplitpath_s(strModulePath, szDrive, _MAX_DRIVE, szFolder, _MAX_DIR, NULL, 0, NULL, 0);
        ::wsprintf(szCmd.m_strFileName.GetBuffer(MAX_PATH), _T("%s%sImageSettings.ini"), szDrive, szFolder);
        szCmd.m_strFileName.ReleaseBuffer();
    }
	int iRadioButton = GetPrivateProfileInt(SECTION_COMMON, KEY_RADIOBUTTON, 0, szCmd.m_strFileName);

	CImageSettingsDlg dlg;
	dlg.m_bRadioButton2 = iRadioButton;
	dlg.m_bRadioButton1 = dlg.m_bRadioButton2 ? FALSE : TRUE;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
		CString strSave;
		strSave.Format(_T("%d"), dlg.m_bRadioButton2);
		WritePrivateProfileString(SECTION_COMMON, KEY_RADIOBUTTON, strSave, szCmd.m_strFileName);
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
