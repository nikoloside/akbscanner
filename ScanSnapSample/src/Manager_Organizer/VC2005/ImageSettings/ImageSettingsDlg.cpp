//******************************************************************************
//
//   ScanSnap Sample Program
//
//   Copyright PFU LIMITED 2012
//
//******************************************************************************

// ImageSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageSettings.h"
#include "ImageSettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageSettingsDlg dialog




CImageSettingsDlg::CImageSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageSettingsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CImageSettingsDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CImageSettingsDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CImageSettingsDlg message handlers

BOOL CImageSettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(m_bRadioButton1);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(m_bRadioButton2);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImageSettingsDlg::OnPaint()
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
HCURSOR CImageSettingsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CImageSettingsDlg::OnBnClickedOk()
{
	// TODO: Place code here to handle.
	m_bRadioButton1 = ((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck();
	m_bRadioButton2 = ((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck();

	OnOK();
}
