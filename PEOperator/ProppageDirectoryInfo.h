//******************************************************************************
// License:     MIT
// Author:      Hoffman
// GitHub:      https://github.com/JokerRound
// Create Time: 2019-01-05
// Description: 
//      The header file of class CProppageDirectoryInfo.
//
// Modify Log:
//      2019-01-07    Hoffman
//      Info: a. Add below member variables.
//              a.1. 
//******************************************************************************

#pragma once
#include "MoveDirectoryDlg.h"

// CProppageDirectoryInfo 对话框

class CProppageDirectoryInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CProppageDirectoryInfo)

public:
	CProppageDirectoryInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CProppageDirectoryInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_DIRECTORYINFO };
#endif
private:
    CMoveDirectoryDlg m_MoveExportDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    afx_msg LRESULT OnFilehadanalysised(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
    // The edit control of export directory's address
    CEdit m_edtExportAddr;
    CEdit m_edtExportSize;
    afx_msg void OnBnClickedBtnExportView();
};
