// Screenshot.cpp : Defines the class behavior of the application.
//

#include "stdafx.h"
#include "Screenshot.h"
#include "ScreenshotDlg.h"
#include "CatchScreenDlg.h"
#include <GdiPlus.h>


using namespace Gdiplus;
#pragma comment(lib,"GdiPlus.lib")





#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SHIFTED 0x8000 


// CScreenshotApp

BEGIN_MESSAGE_MAP(CScreenshotApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// structure CScreenshotApp

CScreenshotApp::CScreenshotApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中

}


CScreenshotApp theApp;


// initialize CScreenshotApp

BOOL CScreenshotApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	
	GdiplusStartupInput input;
	GdiplusStartup(&m_gdiplusToken,&input,NULL);

	AfxEnableControlContainer();

	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CScreenshotDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Put code here that handles 
		// when you close the dialog with "OK"
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Put code here to handle
		// when to close the dialog with "Cancel"
	}

	// Since the dialog is closed, FALSE will be returned to exit the application,
	// Instead of starting the application's message pump.
	return FALSE;
}

BOOL CScreenshotApp::ProcessMessageFilter(int code, LPMSG lpMsg) 
{
	if(m_hwndDlg != NULL)
	{
		// If the message is sent from a dialog box or its sub-control, it will be processed
		if((lpMsg->hwnd == m_hwndDlg) || ::IsChild(m_hwndDlg, lpMsg->hwnd))
		{
			// If the message is WM_KEYDOWN, use the arrow keys to adjust the position
			if(lpMsg->message == WM_KEYDOWN)
			{
				CRect rect(0,0,0,0);
				CCatchScreenDlg * pDlg=(CCatchScreenDlg *)AfxGetMainWnd();

				rect = pDlg->m_rectTracker.m_rect;

				if(pDlg->m_bFirstDraw)
				{
					// If Shift key is pressed then the arrow keys resize
					BOOL bIsShiftDown = FALSE;

					if (GetKeyState(VK_SHIFT) & SHIFTED) 
						bIsShiftDown = TRUE;

					////////////////////////////////////////////////////

					switch(lpMsg->wParam)
					{
					case VK_UP:

						// If Shift is pressed, only one side is adjusted
						if(!bIsShiftDown)
							rect.top-=1;

						rect.bottom-=1;
						pDlg->m_rectTracker.m_rect = rect;
						pDlg->InvalidateRgnWindow();
						break;

					case VK_DOWN:
						rect.top+=1;
						if(!bIsShiftDown)
							rect.bottom+=1;

						pDlg->m_rectTracker.m_rect=rect;
						pDlg->InvalidateRgnWindow();
						break;

					case VK_LEFT:
						if(!bIsShiftDown)
							rect.left-=1;
						rect.right-=1;

						pDlg->m_rectTracker.m_rect=rect;
						pDlg->InvalidateRgnWindow();
						break;

					case VK_RIGHT:
						rect.left+=1;
						if(!bIsShiftDown)
							rect.right+=1;

						pDlg->m_rectTracker.m_rect=rect;
						pDlg->InvalidateRgnWindow();
						break;
					}
				}
			}

		}
	} 

	return CWinApp::ProcessMessageFilter(code, lpMsg);
}
int CScreenshotApp::ExitInstance()
{
	GdiplusShutdown(m_gdiplusToken);

	return CWinApp::ExitInstance();
}
