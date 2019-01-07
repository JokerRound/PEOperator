// MoveDirectoryDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "PEOperator.h"
#include "MoveDirectoryDlg.h"
#include "afxdialogex.h"


// CMoveDirectoryDlg 对话框

IMPLEMENT_DYNAMIC(CMoveDirectoryDlg, CDialogEx)

CMoveDirectoryDlg::CMoveDirectoryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MOVE_DIRECTORY_DIALOG, pParent)
{

}

CMoveDirectoryDlg::~CMoveDirectoryDlg()
{
}

void CMoveDirectoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMoveDirectoryDlg, CDialogEx)
END_MESSAGE_MAP()


// CMoveDirectoryDlg 消息处理程序
