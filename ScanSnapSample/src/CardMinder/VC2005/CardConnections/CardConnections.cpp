//******************************************************************************
//
//   ScanSnap Sample Program
//
//   Copyright PFU LIMITED 2012
//
//******************************************************************************

// CardConnections.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CardConnections.h"
#include "CardConnectionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//  TODO: It is necessary to change to an appropriate name. 
#define	CARDIFSAMPLE_WINDOW_CLASS	_T("CardConnections MainWndClass")
#define	CARDIFSAMPLE_MUTEX_NAME		_T("CardConnections")
//
#define SECTION_FILES		_T("FILES")
#define KEY_FILECOUNT		_T("FILECOUNT")
#define KEY_FILE			_T("File")

// CCardConnectionsApp

BEGIN_MESSAGE_MAP(CCardConnectionsApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCardConnectionsApp construction

CCardConnectionsApp::CCardConnectionsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
    m_lstFileName.RemoveAll();
}


// The one and only CCardConnectionsApp object

CCardConnectionsApp theApp;


// CCardConnectionsApp initialization

BOOL CCardConnectionsApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	//SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	
	// Set Window Class
	WNDCLASS stClass;
	HINSTANCE hInst;
	hInst = AfxGetInstanceHandle();
	if (GetClassInfo(hInst, _T("#32770"), &stClass)) {
		stClass.lpszClassName = CARDIFSAMPLE_WINDOW_CLASS;
		AfxRegisterClass(&stClass);
	}

	// CCardConnectionsDlg Class
 	CCardConnectionsDlg dlg;
	m_pMainWnd = &dlg;
 	
	// CommandLine(Get IniFile Path)
	CCommandLineInfo szCmd;
	ParseCommandLine(szCmd);
	SetIFFolderPath(szCmd.m_strFileName);

	// Set temporary directory
	if (!GetTempPath(MAX_PATH, dlg.m_szTmpPath)) {
        m_pMainWnd = NULL;
		return FALSE;
	}
	wsprintf(dlg.m_szTmpPath, _T("%s%s"), dlg.m_szTmpPath, _T("ScanSnapSampleCard"));

	HANDLE hMutex;
	HWND hWnd;
	hMutex = CreateMutex(NULL, TRUE, CARDIFSAMPLE_MUTEX_NAME);
	if (hMutex) {
		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			hWnd = FindWindow(CARDIFSAMPLE_WINDOW_CLASS, NULL);
			if (hWnd) {
                COPYDATASTRUCT cd;
                cd.dwData = 0;
                cd.cbData = MAX_PATH;
                cd.lpData = szCmd.m_strFileName.GetBuffer(MAX_PATH);
                ::SendMessage(hWnd, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&cd);
                ::ReleaseMutex(hMutex);
                m_pMainWnd = NULL;
				::SetForegroundWindow(hWnd);
                return FALSE;
			}
		}
	} else {
        m_pMainWnd = NULL;
		return FALSE;
	}

	// Delete temporary directory
	DeleteFolder(dlg.m_szTmpPath);

	// Create temporary directory
	CreateDirectory(dlg.m_szTmpPath, NULL);

    CopyFiles(szCmd.m_strFileName);

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

	DeleteFolder(dlg.m_szTmpPath);
	DeleteFolder(dlg.m_szIFFolder);
    ::ReleaseMutex(hMutex);

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CCardConnectionsApp::SetIFFolderPath(CString strIniFile)
{
	TCHAR	szDriver[MAX_PATH];
	TCHAR	szDir[_MAX_DIR];
	LPTSTR	lpszPath = ((CCardConnectionsDlg*)m_pMainWnd)->m_szIFFolder;

	_tsplitpath_s(strIniFile, szDriver, MAX_PATH, szDir, _MAX_DIR, NULL, 0, NULL, 0);
	_tmakepath_s(lpszPath, MAX_PATH, szDriver, szDir, NULL, NULL);
	if (lpszPath[_tcslen(lpszPath)-1] == _T('\\')) {
		lpszPath[_tcslen(lpszPath)-1] = _T('\0');
	}
}

void CCardConnectionsApp::DeleteFolder(LPCTSTR lpszPath)
{
	// Delete directory
    SHFILEOPSTRUCT stFOP;
    ZeroMemory(&stFOP, sizeof(SHFILEOPSTRUCT));

    stFOP.wFunc     = FO_DELETE;
    stFOP.pFrom     = lpszPath;
    stFOP.fFlags    = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI;

    ::SHFileOperation(&stFOP);
}

void CCardConnectionsApp::CopyFiles(CString strIniFile)
{
	// Get new file from ini file
	TCHAR	szFile[_MAX_FNAME];
	TCHAR	szExt[_MAX_EXT];
	TCHAR	szTemp[MAX_PATH];
	CString strBuff;
	CString	strFileKey;
	CString strNum;
	int nCnt;
	nCnt = GetPrivateProfileInt(SECTION_FILES, KEY_FILECOUNT, 0, strIniFile);
	for (int i = 0; i < nCnt; i++) {
		_itow_s(i+1, strNum.GetBuffer(MAX_PATH), MAX_PATH, 10);
		strNum.ReleaseBuffer();
		strFileKey = KEY_FILE;
		strFileKey += strNum;

		GetPrivateProfileString(SECTION_FILES, strFileKey, _T("\0"), strBuff.GetBuffer(MAX_PATH), MAX_PATH, strIniFile);
		strBuff.ReleaseBuffer();

		if (!strBuff.IsEmpty()) {
			_tsplitpath_s(strBuff, NULL, 0, NULL, 0, szFile, _MAX_FNAME, szExt, _MAX_EXT);
			if (_tcscmp(szExt, _T(".xml")) == 0 || _tcscmp(szExt, _T(".vcf")) == 0) {
				wsprintf(szTemp, _T("%s\\%s%s"), ((CCardConnectionsDlg*)m_pMainWnd)->m_szTmpPath, szFile, szExt);
				CopyFile(strBuff, szTemp, FALSE);
				wsprintf(szTemp, _T("%s%s"), szFile, szExt);
				m_lstFileName.AddTail(szTemp);
			}
		}
	}
}
