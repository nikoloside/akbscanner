//******************************************************************************
//
//   ScanSnap Sample Program
//
//   Copyright PFU LIMITED 2012
//
//******************************************************************************

// CardSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CardSettings.h"
#include "CardSettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SECTION_COMMON		_T("COMMON")
#define KEY_CHECKBOX1		_T("CHECKBOX1")
#define KEY_CHECKBOX2		_T("CHECKBOX2")


// CCardSettingsDlg dialog
CCardSettingsDlg::CCardSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCardSettingsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCardSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCardSettingsDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnOk)
END_MESSAGE_MAP()


// CCardSettingsDlg message handlers

BOOL CCardSettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	int iCheck1 = GetPrivateProfileInt(SECTION_COMMON, KEY_CHECKBOX1, 0, m_szIniPath);
	CButton* pBtn1 = (CButton*)GetDlgItem(IDC_CHECK1);
	pBtn1->SetCheck(iCheck1);

	int iCheck2 = GetPrivateProfileInt(SECTION_COMMON, KEY_CHECKBOX2, 0, m_szIniPath);
	CButton* pBtn2 = (CButton*)GetDlgItem(IDC_CHECK2);
	pBtn2->SetCheck(iCheck2);

	pBtn1->SetFocus();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCardSettingsDlg::OnPaint()
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
HCURSOR CCardSettingsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCardSettingsDlg::OnBnOk()
{
	CString strCheck;
	CButton* pBtn;
	int iCheck;

	// set ini file
	pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	iCheck = 0;
	if (pBtn->GetCheck()) {
		iCheck = 1;
	}
	strCheck.Format(_T("%d"), iCheck);
	::WritePrivateProfileString(SECTION_COMMON, KEY_CHECKBOX1, strCheck, m_szIniPath);

	pBtn = (CButton*)GetDlgItem(IDC_CHECK2);
	iCheck = 0;
	if (pBtn->GetCheck()) {
		iCheck = 1;
	}
	strCheck.Format(_T("%d"), iCheck);
	::WritePrivateProfileString(SECTION_COMMON, KEY_CHECKBOX2, strCheck, m_szIniPath);

	CDialog::OnOK();
}
