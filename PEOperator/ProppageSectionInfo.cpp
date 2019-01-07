//******************************************************************************
// License:     MIT
// Author:      Hoffman
// GitHub:      https://github.com/JokerRound
// Create Time: 2019-01-07
// Description: 
//      The achieve of class CProppageSectionInfo.
//
// Modify Log:
//      2019-01-07    Hoffman
//      Info: a. Add below member methods.
//              a.1. 
//******************************************************************************

// ProppageSectionInfo.cpp: 实现文件
//

#include "stdafx.h"
#include "PEOperator.h"
#include "ProppageSectionInfo.h"
#include "afxdialogex.h"


// CProppageSectionInfo 对话框

IMPLEMENT_DYNAMIC(CProppageSectionInfo, CDialogEx)

CProppageSectionInfo::CProppageSectionInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROPPAGE_SECTIONINFO, pParent)
{

}

CProppageSectionInfo::~CProppageSectionInfo()
{
}

void CProppageSectionInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProppageSectionInfo, CDialogEx)
    ON_MESSAGE(WM_FILEHADANALYSISED, &CProppageSectionInfo::OnFilehadanalysised)
END_MESSAGE_MAP()


// CProppageSectionInfo 消息处理程序
afx_msg LRESULT CProppageSectionInfo::OnFilehadanalysised(WPARAM wParam,
                                                          LPARAM lParam)
{

    return 0;
}
