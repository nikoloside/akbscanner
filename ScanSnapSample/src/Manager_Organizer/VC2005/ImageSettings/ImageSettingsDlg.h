//******************************************************************************
//
//   ScanSnap Sample Program
//
//   Copyright PFU LIMITED 2012
//
//******************************************************************************

// ImageSettingsDlg.h : header file
//

#pragma once


// CImageSettingsDlg dialog
class CImageSettingsDlg : public CDialog
{
// Construction
public:
	CImageSettingsDlg(CWnd* pParent = NULL);	// standard constructor
	BOOL	m_bRadioButton1;
	BOOL	m_bRadioButton2;

// Dialog Data
	enum { IDD = IDD_USERAPPLICATION_OPTION_DIALOG };

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
	afx_msg void OnBnClickedOk();
};
