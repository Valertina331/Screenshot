// Screenshot.h : PROJECT_NAME Main header file of the application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"

// CScreenshotApp:
// Screenshot.cpp writes the specific implementation of this class.
//

class CScreenshotApp : public CWinApp
{
public:
	CScreenshotApp();

// Rewrite the class
	public:
	virtual BOOL InitInstance();


	HWND m_hwndDlg;
	virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);

// Generate files

	DECLARE_MESSAGE_MAP()
private:
	ULONG_PTR m_gdiplusToken;
public:
	virtual int ExitInstance();
};

extern CScreenshotApp theApp;
