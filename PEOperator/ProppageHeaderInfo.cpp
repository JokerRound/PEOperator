//******************************************************************************
// License:     MIT
// Author:      Hoffman
// Create Time: 2018-10-29
// Description: 
//      The achieve of class CProppageHeaderInfo.
//
// Modify Log:
//      2018-10-29    Hoffman
//      Info: a. Add achieve of below member methods.
//              a.1. SwitchEditMode();
//              a.2. OnUpdateheaderinfo();
//              a.3. OnBnClickedBtnEditmode();
//              a.4. OnBnClickedBtnSave();
//      
//      2019-01-07    Hoffman
//      Info: a. Modify below member methods.
//              a.1. OnFilehadanalysised()
//                  a.1.1. Fixed a check bug.
//******************************************************************************

#include "stdafx.h"
#include "PEOperator.h"
#include "ProppageHeaderInfo.h"
#include "afxdialogex.h"


// CProppageHeaderInfo 对话框

IMPLEMENT_DYNAMIC(CProppageHeaderInfo, CDialog)

CProppageHeaderInfo::CProppageHeaderInfo(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PROPPAGE_HEADERINFO, pParent)
{

}

CProppageHeaderInfo::~CProppageHeaderInfo()
{
}

void CProppageHeaderInfo::SwitchEditMode(DWORD dwMode /*=1*/)
{
    // Readonly mode of edit control or not.
    BOOL bReadOnly = FALSE;

    if (1 == dwMode)
    {
        // Set button of "Edit Mode" disabled.
        m_btnEditMode.EnableWindow(0);
        // Set buttons of "Save" and "Restore" visible.
        m_btnSave.ShowWindow(1);
        m_btnRestore.ShowWindow(1);
    }
    else if (0 == dwMode)
    {
        // Set button of "Edit Mode" abled.
        m_btnEditMode.EnableWindow(1);
        // Set buttons of "Save" and "Restore" unvisible.
        m_btnSave.ShowWindow(0);
        m_btnRestore.ShowWindow(0);

        // Set all edit control read only.
        bReadOnly = TRUE;
    }
    else
    {
#ifdef DEBUG

#endif // DEBUG
    }

    // Switch all edit control can be writed.
    for (int cntI = 0; cntI < EDIT_CONTROL_NUM; cntI++)
    {
        m_apAllEditControl[cntI]->SetReadOnly(bReadOnly);
    }
} //! CProppageHeaderInfo::SwitchEditMode END 

void CProppageHeaderInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDT_CPUMACHINE, m_edtCpuMachine);
    DDX_Control(pDX, IDC_EDT_SECTIONSNUM, m_edtSectionsNum);
    DDX_Control(pDX, IDC_EDT_BUILDTIME, m_edtBuildTime);
    DDX_Control(pDX, IDC_EDT_OPTIONALHEADERSIZE, m_edtOptionalHeaderSize);
    DDX_Control(pDX, IDC_EDT_FILEATTRIBUTES, m_edtFileAttributes);
    DDX_Control(pDX, IDC_EDT_OPTIONALHEADERTYPE, m_edtOptionalHeaderType);
    DDX_Control(pDX, IDC_EDT_ENTRYPOINT, m_edtEntryPoint);
    DDX_Control(pDX, IDC_EDT_BASEOFCODE, m_edtBaseOfCode);
    DDX_Control(pDX, IDC_EDT_BASEOFDATA, m_edtBaseOfData);
    DDX_Control(pDX, IDC_EDT_IMAGEBASE, m_edtImageBase);
    DDX_Control(pDX, IDC_EDT_MEMORYALIGN, m_edtMemoryAlign);
    DDX_Control(pDX, IDC_EDT_FILEALIGN, m_edtFileAlign);
    DDX_Control(pDX, IDC_EDT_IMAGESIZE, m_edtImageSize);
    DDX_Control(pDX, IDC_EDT_ALLHEADERSIZE, m_edtAllHeaderSize);
    DDX_Control(pDX, IDC_EDT_CHECKSUM, m_edtCheckSum);
    DDX_Control(pDX, IDC_EDT_SUBSYSTEM, m_edtSubSystem);
    DDX_Control(pDX, IDC_EDT_PEATTRIBUTES, m_edtPEAttributes);
    DDX_Control(pDX, IDC_EDT_DIRECTORYNUM, m_edtDirectoryNum);
    DDX_Control(pDX, IDC_BTN_EDITMODE, m_btnEditMode);
    DDX_Control(pDX, IDC_BTN_SAVE, m_btnSave);
    DDX_Control(pDX, IDC_BTN_RESTORE, m_btnRestore);
}


BEGIN_MESSAGE_MAP(CProppageHeaderInfo, CDialog)
    ON_MESSAGE(WM_FILEHADANALYSISED,
               &CProppageHeaderInfo::OnFilehadanalysised)
    ON_BN_CLICKED(IDC_BTN_EDITMODE,
                  &CProppageHeaderInfo::OnBnClickedBtnEditmode)
    ON_BN_CLICKED(IDC_BTN_SAVE, &CProppageHeaderInfo::OnBnClickedBtnSave)
    ON_BN_CLICKED(IDC_BTN_RESTORE, &CProppageHeaderInfo::OnBnClickedBtnRestore)
END_MESSAGE_MAP()


// CProppageHeaderInfo 消息处理程序

// Deal with WM_UPDATEHEADERINFO
// The wParam is type of PE file struct.
// The lParam is point of PE file struct maybe modify.
afx_msg LRESULT CProppageHeaderInfo::OnFilehadanalysised(WPARAM wParam,
                                                         LPARAM lParam)
{
    // The PE struct is 32 bit.
    if (32 == wParam)
    {
        m_pstNtHeader = &((PPEFILESTRUCT32)lParam)->stNtHeader_;

        // Set items info of file header.
        m_edtCpuMachine.SetWindowText(
            Word2HexString(m_pstNtHeader->FileHeader.Machine).c_str());
        m_edtSectionsNum.SetWindowText(
            Word2HexString(
                m_pstNtHeader->FileHeader.NumberOfSections).c_str());
        m_edtBuildTime.SetWindowText(
            Dword2HexString(m_pstNtHeader->FileHeader.TimeDateStamp).c_str());
        m_edtOptionalHeaderSize.SetWindowText(
            Word2HexString(
                m_pstNtHeader->FileHeader.SizeOfOptionalHeader).c_str());
        m_edtFileAttributes.SetWindowText(
            Word2HexString(m_pstNtHeader->FileHeader.Characteristics).c_str());
            
        // Set items info of optional header.
        m_edtOptionalHeaderType.SetWindowText(
            Word2HexString(m_pstNtHeader->OptionalHeader.Magic).c_str());
        m_edtEntryPoint.SetWindowText(
            Dword2HexString(
                m_pstNtHeader->OptionalHeader.AddressOfEntryPoint).c_str());
        m_edtBaseOfCode.SetWindowText(
            Dword2HexString(m_pstNtHeader->OptionalHeader.BaseOfCode).c_str());
        m_edtBaseOfData.SetWindowText(
            Dword2HexString(m_pstNtHeader->OptionalHeader.BaseOfData).c_str());
        m_edtImageBase.SetWindowText(
            Dword2HexString(m_pstNtHeader->OptionalHeader.ImageBase).c_str());
        m_edtMemoryAlign.SetWindowText(
            Dword2HexString(
                m_pstNtHeader->OptionalHeader.SectionAlignment).c_str());
        m_edtFileAlign.SetWindowText(
            Dword2HexString(
                m_pstNtHeader->OptionalHeader.FileAlignment).c_str());
        m_edtImageSize.SetWindowText(
            Dword2HexString(
                m_pstNtHeader->OptionalHeader.SizeOfImage).c_str());
        m_edtAllHeaderSize.SetWindowText(
            Dword2HexString(
                m_pstNtHeader->OptionalHeader.SizeOfHeaders).c_str());
        m_edtCheckSum.SetWindowText(
            Dword2HexString(
                m_pstNtHeader->OptionalHeader.CheckSum).c_str());
        m_edtSubSystem.SetWindowText(
            Word2HexString(
                m_pstNtHeader->OptionalHeader.Subsystem).c_str());
        m_edtPEAttributes.SetWindowText(
            Word2HexString(
                m_pstNtHeader->OptionalHeader.DllCharacteristics).c_str());
        m_edtDirectoryNum.SetWindowText(
            Dword2HexString(
                m_pstNtHeader->OptionalHeader.NumberOfRvaAndSizes).c_str());

    } //! if "The PE struct is 32 bit" END
    // TODO: The PE struct is 64 bit.
    else
    {

    }

    UpdateWindow();

    return 0;
} //! CProppageHeaderInfo::OnUpdateheaderinfo END



void CProppageHeaderInfo::OnBnClickedBtnEditmode()
{
    SwitchEditMode(1);

} //! CProppageHeaderInfo::OnBnClickedBtnEditmode END


void CProppageHeaderInfo::OnBnClickedBtnSave()
{
    SwitchEditMode(0);
    // TODO: Save info to file.

} //! CProppageHeaderInfo::OnBnClickedBtnSave END


void CProppageHeaderInfo::OnBnClickedBtnRestore()
{
    SwitchEditMode(0);

} //! CProppageHeaderInfo::OnBnClickedBtnRestore END 