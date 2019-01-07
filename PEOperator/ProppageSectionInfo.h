//******************************************************************************
// License:     MIT
// Author:      Hoffman
// GitHub:      https://github.com/JokerRound
// Create Time: 2019-01-05
// Description: 
//      The header file of class CProppageSectionInfo.
//
// Modify Log:
//      2019-01-05    Hoffman
//      Info: a. Add below member variables.
//              a.1. 
//******************************************************************************

#pragma once

// CProppageSectionInfo 对话框

class CProppageSectionInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CProppageSectionInfo)

public:
	CProppageSectionInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CProppageSectionInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_SECTIONINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    afx_msg LRESULT OnFilehadanalysised(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};
