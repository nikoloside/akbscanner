//******************************************************************************
//
//   ScanSnap Sample Program
//
//   Copyright PFU LIMITED 2012
//
//******************************************************************************

// ImageConnectionsDlg.h : header file
//

#pragma once
#include "afxwin.h"

// Define Struct
typedef struct tagSS_NOTIFY
{
	DWORD Mode;
	char AppName[255];
}SSMON_NOTIFY;

typedef  struct  tagSS_SCAN
{
	DWORD	Mode;
	BOOL	ScanningSide;
} SS_SCAN,  * PSS_SCAN;


// CImageConnectionsDlg dialog
class CImageConnectionsDlg : public CDialog
{
// Construction
public:
	CImageConnectionsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SAMPLE_DIALOG };

// Declare variable
	TCHAR m_szTmpPath[MAX_PATH];
	CListBox m_CListBox;
	CButton m_CScanButton;
	BOOL m_bScanButton;

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
	afx_msg void OnBnClickedOpen();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedScan();
	afx_msg void OnLbnDblclkListFilelist();
	BOOL GetSsManagerPath(LPTSTR pszPath);
    afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
};
