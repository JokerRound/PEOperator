#pragma once


// CProppageFileInfo 对话框

class CProppageFileInfo : public CDialog
{
	DECLARE_DYNAMIC(CProppageFileInfo)

public:
	CProppageFileInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CProppageFileInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_FILEINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
    afx_msg LRESULT OnUpdatefileinfo(WPARAM wParam, LPARAM lParam);
public:
    // The edit of file info.
    CEdit m_edtFileInfo;
};
