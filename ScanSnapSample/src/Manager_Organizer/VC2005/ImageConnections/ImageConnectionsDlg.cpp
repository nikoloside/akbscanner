//******************************************************************************
//
//   ScanSnap Sample Program
//
//   Copyright PFU LIMITED 2012
//
//******************************************************************************

// ImageConnectionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageConnections.h"
#include "ImageConnectionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageConnectionsDlg dialog
CImageConnectionsDlg::CImageConnectionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageConnectionsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageConnectionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FILELIST, m_CListBox);
	DDX_Control(pDX, IDSCAN, m_CScanButton);
}

BEGIN_MESSAGE_MAP(CImageConnectionsDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOPEN, &CImageConnectionsDlg::OnBnClickedOpen)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDSCAN, &CImageConnectionsDlg::OnBnClickedScan)
	ON_LBN_DBLCLK(IDC_LIST_FILELIST, &CImageConnectionsDlg::OnLbnDblclkListFilelist)
    ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CImageConnectionsDlg message handlers

BOOL CImageConnectionsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	if(m_bScanButton == FALSE){
		m_CScanButton.EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImageConnectionsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImageConnectionsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CImageConnectionsDlg::OnBnClickedOpen()
{
	int nIndex;
	TCHAR szFileName[MAX_PATH];
	TCHAR szFilePath[MAX_PATH];

	nIndex = m_CListBox.GetCurSel();

    if (nIndex == -1) {
        return;
    }

	m_CListBox.GetText(nIndex, szFileName);
	wsprintf(szFilePath, _T("%s\\%s"), m_szTmpPath, szFileName);
	ShellExecute(NULL, NULL, szFilePath, NULL, NULL, SW_SHOW);
}

void CImageConnectionsDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	// Delete list
	m_CListBox.ResetContent();

	// Get the information from the configuration file
    POSITION pos;
    for (pos = theApp.m_lstFileName.GetHeadPosition(); pos != NULL; ) {
        m_CListBox.AddString(theApp.m_lstFileName.GetNext(pos));
    }

	// Set the horizontal extent
	CString str;
	CSize   sz;
	int     dx=0;

	CDC*    pDC = m_CListBox.GetDC();
	for (int i=0; i<m_CListBox.GetCount(); i++)
	{
	   m_CListBox.GetText(i, str);
	   sz = pDC->GetTextExtent(str);
	   if (sz.cx > dx)
		  dx = sz.cx;
	}
	m_CListBox.ReleaseDC(pDC);

	if (m_CListBox.GetHorizontalExtent() < dx)
	{
	   m_CListBox.SetHorizontalExtent(dx);
	}

    m_CListBox.SetCurSel(0);

	CDialog::OnShowWindow(bShow, nStatus);
}

void CImageConnectionsDlg::OnBnClickedScan()
{
	COPYDATASTRUCT copydata;
	SSMON_NOTIFY notify;
	SS_SCAN scan;
	LRESULT lResult;
    CString strMsg;

	ZeroMemory(&notify, sizeof(SSMON_NOTIFY));
	ZeroMemory(&scan, sizeof(SS_SCAN));

	// Find main window of ScanSnap Manager
	HWND hWnd = ::FindWindow(_T("ScanSnap Manager MainWndClass"), NULL);
	if(hWnd == NULL) {
		// Execute ScanSnap Manager		
		BOOL bRet;
		TCHAR szPath[MAX_PATH];
		bRet = GetSsManagerPath(szPath);
		if(bRet){
			ShellExecute(NULL, NULL, szPath, NULL, NULL, SW_SHOW);
			for(int i=0; i<10; i++){
				Sleep(500);
				hWnd = ::FindWindow(_T("ScanSnap Manager MainWndClass"), NULL);
				if(hWnd != NULL){
					break;
				}
			}
		}
	}
	if(hWnd == NULL) {
		MessageBox(_T("FindWindow Failed"), _T("Image Connections"), MB_OK);
		return;		
	}

	// Reserve command
	notify.Mode = 0;
	wsprintfA(notify.AppName, "%s", "ImageConnections");
	copydata.dwData = 2;
	copydata.cbData = sizeof(SSMON_NOTIFY);
	copydata.lpData = &notify;
	lResult = ::SendMessage(hWnd, WM_COPYDATA, NULL, (LPARAM)&copydata);
	if(lResult != 0){
        strMsg.Format(_T("ReserveCommand Failed (%d)"), lResult);
		MessageBox(strMsg, _T("Image Connections"), MB_OK);
		return;
	}
	
	// StartScan command
	scan.Mode = 0;
	scan.ScanningSide = 1;
	copydata.dwData = 3;
	copydata.cbData = sizeof(SS_SCAN);
	copydata.lpData = &scan;
	lResult = ::SendMessage(hWnd, WM_COPYDATA, NULL, (LPARAM)&copydata);
	if(lResult != 0){
        strMsg.Format(_T("StartScanCommand Failed (%d)"), lResult);
		MessageBox(strMsg, _T("Image Connections"), MB_OK);
	}

	// Release command
	notify.Mode = 1;
	wsprintfA(notify.AppName, "%s", "ImageConnections");
	copydata.dwData = 2;
	copydata.cbData = sizeof(SSMON_NOTIFY);
	copydata.lpData = &notify;
	lResult = ::SendMessage(hWnd, WM_COPYDATA, NULL, (LPARAM)&copydata);
	if(lResult != 0){
        strMsg.Format(_T("ReleaseCommand Failed (%d)"), lResult);
		MessageBox(strMsg, _T("Image Connections"), MB_OK);
		return;
	}
}

void CImageConnectionsDlg::OnLbnDblclkListFilelist()
{
    OnBnClickedOpen();
}

BOOL CImageConnectionsDlg::GetSsManagerPath(LPTSTR pszPath)
{
	LONG lRet;
	HKEY hKey;
	TCHAR szSuKey[] = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\PfuSsMon.exe");  
	lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, szSuKey, NULL, KEY_READ, &hKey);
	if(lRet != ERROR_SUCCESS)
	{
		return FALSE;
	}

	DWORD dwType = REG_SZ;
	DWORD dwSize = MAX_PATH;
	lRet = RegQueryValueEx(hKey, NULL, NULL, &dwType, LPBYTE(pszPath), &dwSize);
	RegCloseKey(hKey);
	if(lRet != ERROR_SUCCESS)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CImageConnectionsDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
    CString strIniFile = (LPCTSTR)pCopyDataStruct->lpData;
    theApp.m_lstFileName.RemoveAll();
    theApp.CopyFiles(strIniFile);
    int iIndex = -1;
    if (m_CListBox.GetCurSel() == LB_ERR) {
        iIndex = m_CListBox.GetCount();
    }

    POSITION pos;
    for (pos = theApp.m_lstFileName.GetHeadPosition(); pos != NULL; ) {
        m_CListBox.AddString(theApp.m_lstFileName.GetNext(pos));
    }

    if (iIndex != -1) {
        m_CListBox.SetCurSel(iIndex);
    }

    return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}
