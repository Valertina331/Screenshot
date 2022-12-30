// ScreenshotDlg.h
//

#pragma once

// CScreenshotDlg Generate a screenshot dialog
class CScreenshotDlg : public CDialog
{
// Constructing standard functions
public:
	CScreenshotDlg(CWnd* pParent = NULL);
// Storing dialog data
	enum { IDD = IDD_SCREENSHOT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);


// Generate message mapping functions
protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnStart();
};
