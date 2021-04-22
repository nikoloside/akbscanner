//******************************************************************************
//
//   ScanSnap Sample Program
//
//   Copyright PFU LIMITED 2012
//
//******************************************************************************

// CardSettingsDlg.h : header file
//

#pragma once


// CCardSettingsDlg dialog
class CCardSettingsDlg : public CDialog
{
// Construction
public:
	CCardSettingsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CARDSETTINGS_DIALOG };

// Declare variable
	TCHAR m_szIniPath[MAX_PATH];

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnOk();
};
