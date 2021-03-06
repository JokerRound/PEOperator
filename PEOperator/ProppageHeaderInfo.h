//******************************************************************************
// License:     MIT
// Author:      Hoffman
// Create Time: 2018-10-29
// Description: 
//      The header file of class of CProppageHeaderInfo.
//
// Modify Log:
//      2018-10-29    Hoffman
//      Info: a. Add below member variables.
//              a.1. m_pstNtHeader;
//              a.2. m_apAllEditControl;
//              a.3. m_edtCpuMachine;
//              a.4. m_edtSectionsNum;
//              a.5. m_edtBuildTime;
//              a.6. m_edtOptionalHeaderSize;
//              a.7. m_edtFileAttributes;
//              a.8. m_edtOptionalHeaderType;
//              a.9. m_edtEntryPoint;
//              a.10. m_edtBaseOfCode;
//              a.11. m_edtBaseOfData;
//              a.12. m_edtMemoryAlign;
//              a.13. m_edtFileAlign;
//              a.14. m_edtImageSize;
//              a.15. m_edtCheckSum;
//              a.16. m_edtSubSystem;
//              a.17. m_edtPEAttributes;
//              a.18. m_edtDirectoryNum;
//              a.18. m_btnEditMode;             
//              a.18. m_btnSave;
//              a.18. m_btnRestore;    
//            b. Add below member methods.
//              b.1 SwitchEditMode();
//              b.2 OnUpdateheaderinfo();
//******************************************************************************

#pragma once
#include "HexEdit.h"

// CProppageHeaderInfo 对话框
#define EDIT_CONTROL_NUM 18

class CProppageHeaderInfo : public CDialog
{
	DECLARE_DYNAMIC(CProppageHeaderInfo)
private:
    PIMAGE_NT_HEADERS32 m_pstNtHeader = NULL;
public:
	CProppageHeaderInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CProppageHeaderInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_HEADERINFO };
#endif
private:
    CHexEdit *m_apAllEditControl[EDIT_CONTROL_NUM] = {
        &m_edtCpuMachine,
        &m_edtSectionsNum,
        &m_edtBuildTime,
        &m_edtOptionalHeaderSize,
        &m_edtFileAttributes,
        &m_edtOptionalHeaderType,
        &m_edtEntryPoint,
        &m_edtBaseOfCode,
        &m_edtBaseOfData,
        &m_edtImageBase,
        &m_edtMemoryAlign,
        &m_edtFileAlign,
        &m_edtImageSize,
        &m_edtAllHeaderSize,
        &m_edtCheckSum,
        &m_edtSubSystem,
        &m_edtPEAttributes,
        &m_edtDirectoryNum,
    };

    void SwitchEditMode(_In_ DWORD dwMode = 1);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
protected:
    afx_msg LRESULT OnFilehadanalysised(WPARAM wParam, LPARAM lParam);
public:
    // edit of "Cpu Machine Type".
    CHexEdit m_edtCpuMachine;
    // edit of "Sections Number".
    CHexEdit m_edtSectionsNum;
    // edit of "Build Time".
    CHexEdit m_edtBuildTime;
    // edit of "Optional Header Size".
    CHexEdit m_edtOptionalHeaderSize;
    // edit of "File Attributes".
    CHexEdit m_edtFileAttributes;
    // The edit of "Optional Header Type".
    CHexEdit m_edtOptionalHeaderType;
    // The edit of "Entry Point".
    CHexEdit m_edtEntryPoint;
    // The edit of "Base of Code".
    CHexEdit m_edtBaseOfCode;
    // The edit of "Base Of Data".
    CHexEdit m_edtBaseOfData;
    // The edit of "Image Base".
    CHexEdit m_edtImageBase;
    // The edit of "Memory Align".
    CHexEdit m_edtMemoryAlign;
    // The edit of "File Align".
    CHexEdit m_edtFileAlign;
    // The edit of "Image Size".
    CHexEdit m_edtImageSize;
    // The edit of "All Header Size".
    CHexEdit m_edtAllHeaderSize;
    // The edit of "Check Sum".
    CHexEdit m_edtCheckSum;
    // The edit of "Sub System".
    CHexEdit m_edtSubSystem;
    // The edit of "PE Attributes".
    CHexEdit m_edtPEAttributes;
    // The edit of "Directory Num".
    CHexEdit m_edtDirectoryNum;
    // The button of "Edit Mode".
    CButton m_btnEditMode;
    afx_msg void OnBnClickedBtnEditmode();
    // The button of "Save".
    CButton m_btnSave;
    // The button of "Restore".
    CButton m_btnRestore;
    afx_msg void OnBnClickedBtnSave();
    afx_msg void OnBnClickedBtnRestore();
};
