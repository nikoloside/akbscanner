//******************************************************************************
//
//   ScanSnap Sample Program
//
//   Copyright PFU LIMITED 2012
//
//******************************************************************************

// CardConnectionsDlg.h : header file
//

#pragma once
#include "afxwin.h"

// CCardConnectionsDlg dialog
class CCardConnectionsDlg : public CDialog
{
// Construction
public:
	CCardConnectionsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CARDCONNECTIONS_DIALOG };

// Declare variable
	TCHAR m_szTmpPath[MAX_PATH];
	TCHAR m_szIFFolder[MAX_PATH];
	CListBox m_CListBox;

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
	afx_msg void OnBnOpen();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDblclkList();
    afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
};
