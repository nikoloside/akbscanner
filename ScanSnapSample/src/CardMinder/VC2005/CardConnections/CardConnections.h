//******************************************************************************
//
//   ScanSnap Sample Program
//
//   Copyright PFU LIMITED 2012
//
//******************************************************************************

// CardConnections.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCardConnectionsApp:
// See CardConnections.cpp for the implementation of this class
//

class CCardConnectionsApp : public CWinApp
{
public:
	CCardConnectionsApp();

// Overrides
	public:
	virtual BOOL InitInstance();
	void	SetIFFolderPath(CString strIniFile);
	void	DeleteFolder(LPCTSTR lpszPath);
    void    CopyFiles(CString strIniFile);
    CStringList m_lstFileName;

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCardConnectionsApp theApp;