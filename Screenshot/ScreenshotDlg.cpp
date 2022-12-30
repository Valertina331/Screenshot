// ScreenshotDlg.cpp : Implementation of dialog box
//

#include "stdafx.h"
#include "Screenshot.h"
#include "ScreenshotDlg.h"

#include "CatchScreenDlg.h"


#ifdef _DEBUG
//#define new DEBUG_NEW
#endif


// Generate CScreenshotDlg dialog box


CScreenshotDlg::CScreenshotDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScreenshotDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScreenshotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CScreenshotDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_START, &CScreenshotDlg::OnBnClickedBtnStart)
	ON_WM_CTLCOLOR()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// Handling operations

BOOL CScreenshotDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog
	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);

	// make the form topmost
	::SetWindowPos(GetSafeHwnd(), HWND_TOPMOST, 150, 150, 0, 0, 
		SWP_NOMOVE|SWP_NOSIZE|SWP_NOREDRAW);

	return TRUE;
}

// If you want to add a minimize button to a dialog, you need the code below
// to draw the icon. For MFC applications using document/view models,
// This will be done automatically by the framework.

void CScreenshotDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center the icon in the workspace
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//When the user drags the minimized window, the system calls this function to get the cursor display.

HCURSOR CScreenshotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// Thread function for taking screenshots

UINT SccreenShot_Thread (LPVOID lpParam)
{
	HWND hWndMain = (HWND) lpParam;
	CCatchScreenDlg dlg;
	dlg.DoModal();

	::ShowWindow(hWndMain,SW_SHOW);
	return 0;
}

void CScreenshotDlg::OnBnClickedBtnStart()
{
	::ShowWindow (m_hWnd, SW_HIDE);
	//Bring the activated window to the foreground for screenshots          
	::AfxBeginThread (SccreenShot_Thread, (LPVOID)GetSafeHwnd());
	//::ShowWindow (GetSafeHwnd(), SW_SHOW);
}

