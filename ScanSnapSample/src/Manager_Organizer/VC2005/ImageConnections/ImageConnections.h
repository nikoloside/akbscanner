//******************************************************************************
//
//   ScanSnap Sample Program
//
//   Copyright PFU LIMITED 2012
//
//******************************************************************************

// ImageConnections.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CImageConnectionsApp:
// See ImageConnections1.cpp for the implementation of this class
//

class CImageConnectionsApp : public CWinApp
{
public:
	CImageConnectionsApp();

// Overrides
	public:
	virtual BOOL InitInstance();
	void	DeleteTmpFolder( TCHAR *pszTmpPath );
    void    CopyFiles(CString strIniFile);
    CStringList m_lstFileName;

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CImageConnectionsApp theApp;