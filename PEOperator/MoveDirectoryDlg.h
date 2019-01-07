#pragma once


// CMoveDirectoryDlg 对话框

class CMoveDirectoryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMoveDirectoryDlg)

public:
    CString csTitle;
    DWORD dwNeedSize = 0;
	CMoveDirectoryDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMoveDirectoryDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOVE_DIRECTORY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
