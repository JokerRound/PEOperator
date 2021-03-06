//******************************************************************************
// License:     MIT
// Author:      Hoffman
// Create Time: 2018-10-29
// Description: 
//      The ahcieve of class CProppageFileInfo.
//
// Modify Log:
//      2018-10-29    Hoffman
//      Info: a. Add achieve of below member methods.
//              a.1. OnUpdatefileinfo();
//******************************************************************************

#include "stdafx.h"
#include "PEOperator.h"
#include "ProppageFileInfo.h"
#include "afxdialogex.h"


// CProppageFileInfo 对话框

IMPLEMENT_DYNAMIC(CProppageFileInfo, CDialog)

CProppageFileInfo::CProppageFileInfo(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PROPPAGE_FILEINFO, pParent)
{

}

CProppageFileInfo::~CProppageFileInfo()
{
}

void CProppageFileInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDT_FILEINFO, m_edtFileInfo);
}


BEGIN_MESSAGE_MAP(CProppageFileInfo, CDialog)
    ON_MESSAGE(WM_FILEHADANALYSISED, &CProppageFileInfo::OnFilehadanalysised)
END_MESSAGE_MAP()


// CProppageFileInfo 消息处理程序


afx_msg LRESULT CProppageFileInfo::OnFilehadanalysised(WPARAM wParam,
                                                       LPARAM lParam)
{
    PTARGETFILEINFO pstTargetFileInfo = (PTARGETFILEINFO)wParam;

    CString csShowOnScreen;
    csShowOnScreen += _T("Name: ");
    csShowOnScreen += pstTargetFileInfo->csFileName_ + _T("\r\n");
    csShowOnScreen += _T("Path: ");
    csShowOnScreen += pstTargetFileInfo->csFilePath_ + _T("\r\n");
    csShowOnScreen += _T("Size: ");
    csShowOnScreen += pstTargetFileInfo->csSize_ + _T("\r\n");
    csShowOnScreen += _T("Create Time: ");
    csShowOnScreen += pstTargetFileInfo->csCreatTime_ + _T("\r\n");
    csShowOnScreen += _T("Last Modify Time: ");
    csShowOnScreen += pstTargetFileInfo->csLastModifyTime_ + _T("\r\n");
    csShowOnScreen += _T("Last Access Time: ");
    csShowOnScreen += pstTargetFileInfo->csLastAccessedTime_ + _T("\r\n");
    csShowOnScreen += _T("Is Stander PE: ");
    csShowOnScreen += pstTargetFileInfo->csIsPEFile_ + _T("\r\n");
    
    m_edtFileInfo.SetWindowText(csShowOnScreen);
    return 0;
} //! CProppageFileInfo::OnUpdatefileinfo END
