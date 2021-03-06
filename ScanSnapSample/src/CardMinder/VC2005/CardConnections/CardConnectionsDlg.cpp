//******************************************************************************
//
//   ScanSnap Sample Program
//
//   Copyright PFU LIMITED 2012
//
//******************************************************************************

// CardConnectionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CardConnections.h"
#include "CardConnectionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCardConnectionsDlg dialog
CCardConnectionsDlg::CCardConnectionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCardConnectionsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCardConnectionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FILELIST, m_CListBox);
}

BEGIN_MESSAGE_MAP(CCardConnectionsDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOPEN, OnBnOpen)
	ON_WM_SHOWWINDOW()
	ON_LBN_DBLCLK(IDC_LIST_FILELIST, OnDblclkList)
    ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CCardConnectionsDlg message handlers

BOOL CCardConnectionsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCardConnectionsDlg::OnPaint()
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
HCURSOR CCardConnectionsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCardConnectionsDlg::OnBnOpen()
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

void CCardConnectionsDlg::OnShowWindow(BOOL bShow, UINT nStatus)
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
	CSize sz;
	int dx = 0;

	CDC* pDC = m_CListBox.GetDC();
	for (int i = 0; i < m_CListBox.GetCount(); i++) {
		m_CListBox.GetText(i, str);
		sz = pDC->GetTextExtent(str);
		if (sz.cx > dx) {
			dx = sz.cx;
		}
	}
	m_CListBox.ReleaseDC(pDC);

	if (m_CListBox.GetHorizontalExtent() < dx) {
		m_CListBox.SetHorizontalExtent(dx);
	}

	m_CListBox.SetCurSel(0);

	CDialog::OnShowWindow(bShow, nStatus);
}

void CCardConnectionsDlg::OnDblclkList()
{
	OnBnOpen();
}

BOOL CCardConnectionsDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	CString strIniFile = (LPCTSTR)pCopyDataStruct->lpData;
    theApp.m_lstFileName.RemoveAll();
	theApp.DeleteFolder(m_szIFFolder);
	theApp.SetIFFolderPath(strIniFile);
	theApp.DeleteFolder(m_szTmpPath);
	CreateDirectory(m_szTmpPath, NULL);
    theApp.CopyFiles(strIniFile);
	m_CListBox.ResetContent();
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
