//******************************************************************************
// License:     MIT
// Author:      Hoffman
// GitHub:      https://github.com/JokerRound
// Create Time: 2019-01-05
// Description: 
//      The achieve of class CProppageDirectoryInfo.
//
// Modify Log:
//      2019-01-05    Hoffman
//      Info: a. Add below member methods.
//              a.1. OnFilehadanalysised();
//******************************************************************************

// ProppageDirectoryInfo.cpp: 实现文件
//

#include "stdafx.h"
#include "PEOperator.h"
#include "ProppageDirectoryInfo.h"
#include "afxdialogex.h"


// CProppageDirectoryInfo 对话框

IMPLEMENT_DYNAMIC(CProppageDirectoryInfo, CDialogEx)

CProppageDirectoryInfo::CProppageDirectoryInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROPPAGE_DIRECTORYINFO, pParent)
{

}

CProppageDirectoryInfo::~CProppageDirectoryInfo()
{
}

void CProppageDirectoryInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDT_DIRECTORY_EXPORT_ADDR, m_edtExportAddr);
    DDX_Control(pDX, IDC_EDT_DIRECTORY_EXPORT_SIZE, m_edtExportSize);
}


BEGIN_MESSAGE_MAP(CProppageDirectoryInfo, CDialogEx)
    ON_MESSAGE(WM_FILEHADANALYSISED,
               &CProppageDirectoryInfo::OnFilehadanalysised)
    ON_BN_CLICKED(IDC_BTN_EXPORT_VIEW,
                  &CProppageDirectoryInfo::OnBnClickedBtnExportView)
END_MESSAGE_MAP()


// CProppageDirectoryInfo 消息处理程序

//******************************************************************************
// Author:              Hoffman
// Create Time:         2018-01-07
// Last Time:           2018-01-07
// Logical Descrition:  
//      
//
//******************************************************************************
afx_msg LRESULT CProppageDirectoryInfo::OnFilehadanalysised(WPARAM wParam,
                                                            LPARAM lParam)
{
    IMAGE_DATA_DIRECTORY *pastDataDirectory = (IMAGE_DATA_DIRECTORY *)wParam;

    m_edtExportAddr.SetWindowText(
        Dword2HexString(pastDataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].
                        VirtualAddress).c_str()
    );

    m_edtExportSize.SetWindowText(
        Dword2HexString(pastDataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].
                        Size).c_str()
    );

    return 0;
} //! CProppageDirectoryInfo::OnFilehadanalysised() END


void CProppageDirectoryInfo::OnBnClickedBtnExportView()
{
    // TODO: 在此添加控件通知处理程序代码
    m_MoveExportDlg.DoModal();
}
