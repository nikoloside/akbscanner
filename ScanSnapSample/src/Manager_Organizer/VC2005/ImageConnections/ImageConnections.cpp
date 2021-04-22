//******************************************************************************
//
//   ScanSnap Sample Program
//
//   Copyright PFU LIMITED 2012
//
//******************************************************************************

// ImageConnections.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ImageConnections.h"
#include "ImageConnectionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//  TODO: It is necessary to change to an appropriate name. 
#define	SSIFSAMPLE_WINDOW_CLASS	_T("ImageConnections MainWndClass")
#define	SSIFSAMPLE_MUTEX_NAME	_T("ImageConnections")
//
#define SECTION_FILES		_T("FILES")
#define KEY_FILECOUNT		_T("FILECOUNT")
#define KEY_FILE			_T("File")

// CImageConnectionsApp

BEGIN_MESSAGE_MAP(CImageConnectionsApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CImageConnectionsApp construction

CImageConnectionsApp::CImageConnectionsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
    m_lstFileName.RemoveAll();
}


// The one and only CImageConnectionsApp object

CImageConnectionsApp theApp;


// CImageConnectionsApp initialization

BOOL CImageConnectionsApp::InitInstance()
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
	if(GetClassInfo(hInst, _T("#32770"), &stClass)){
		stClass.lpszClassName = SSIFSAMPLE_WINDOW_CLASS;
		AfxRegisterClass(&stClass);
	}

	// CImageConnectionsDlg Class
	CImageConnectionsDlg dlg;
	m_pMainWnd = &dlg;
	dlg.m_bScanButton = TRUE;

	// CommandLine(Get IniFile Path)
	CCommandLineInfo szCmd;
	ParseCommandLine(szCmd);

	// Create temporary directory
	if(!GetTempPath(MAX_PATH, dlg.m_szTmpPath)){
        m_pMainWnd = NULL;
		return FALSE;
	}
	wsprintf(dlg.m_szTmpPath, _T("%s%s"), dlg.m_szTmpPath, _T("ScanSnapSample"));
	CreateDirectory(dlg.m_szTmpPath, NULL);

	HANDLE hMutex;
	HWND hWnd;
	hMutex = CreateMutex(NULL, TRUE, SSIFSAMPLE_MUTEX_NAME);
	if(hMutex){
		if(GetLastError() == ERROR_ALREADY_EXISTS){
			hWnd = FindWindow(SSIFSAMPLE_WINDOW_CLASS, NULL);
			if(hWnd){
                COPYDATASTRUCT cd;
                cd.dwData = 0;
                cd.cbData = MAX_PATH;
                cd.lpData = szCmd.m_strFileName.GetBuffer(MAX_PATH);
                ::SendMessage(hWnd, WM_COPYDATA, (WPARAM)NULL, (LPARAM)&cd);
                ::ReleaseMutex(hMutex);
                m_pMainWnd = NULL;
                return FALSE;
			}
		}
	}else{
        m_pMainWnd = NULL;
		return FALSE;
	}

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

	DeleteTmpFolder(dlg.m_szTmpPath);
    ::ReleaseMutex(hMutex);

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CImageConnectionsApp::DeleteTmpFolder( TCHAR *pszTmpPath )
{
	// Delete temporary directory
    SHFILEOPSTRUCT stFOP;
    ZeroMemory(&stFOP, sizeof(SHFILEOPSTRUCT));

    stFOP.wFunc     = FO_DELETE;
    stFOP.pFrom     = pszTmpPath;
    stFOP.fFlags    = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI;

    ::SHFileOperation(&stFOP);
}

void CImageConnectionsApp::CopyFiles(CString strIniFile)
{
    CString strAppName;
    GetPrivateProfileString(_T("INFO"), _T("Application"), _T(""), strAppName.GetBuffer(MAX_PATH), MAX_PATH, strIniFile);
    strAppName.ReleaseBuffer();
    BOOL bDeleteFile = strAppName.Compare(_T("ScanSnap Manager")) == 0 ? TRUE : FALSE;

	// Get new file from ini file
	TCHAR	szFile[_MAX_FNAME];
	TCHAR	szExt[_MAX_EXT];
	TCHAR	szTemp[MAX_PATH];
	CString strBuff;
	CString	strFileKey;
	CString strNum;
	int nCnt;
	nCnt = GetPrivateProfileInt(SECTION_FILES, KEY_FILECOUNT, 0, strIniFile);
	for(int i=0; i<nCnt; i++){
		((CImageConnectionsDlg*)m_pMainWnd)->m_bScanButton = FALSE;

		_itow_s(i+1, strNum.GetBuffer(MAX_PATH), MAX_PATH, 10);
		strNum.ReleaseBuffer();
		strFileKey = KEY_FILE;
		strFileKey += strNum;

		GetPrivateProfileString(SECTION_FILES, strFileKey, _T("\0"), strBuff.GetBuffer(MAX_PATH), MAX_PATH, strIniFile);
		strBuff.ReleaseBuffer();

		if(!strBuff.IsEmpty()){
			_tsplitpath_s(strBuff, NULL, 0, NULL, 0, szFile, _MAX_FNAME, szExt, _MAX_EXT);
			wsprintf(szTemp, _T("%s\\%s%s"), ((CImageConnectionsDlg*)m_pMainWnd)->m_szTmpPath, szFile, szExt);
			CopyFile(strBuff, szTemp, FALSE);
            wsprintf(szTemp, _T("%s%s"), szFile, szExt);
            m_lstFileName.AddTail(szTemp);
            if (bDeleteFile) {
			    DeleteFile(strBuff);
            }
		}
	}

	// Delete ini file
	DeleteFile(strIniFile);
}
