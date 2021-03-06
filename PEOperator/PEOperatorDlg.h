//******************************************************************************
// License:     MIT
// Author:      Hoffman
// Create Time: 2018-10-29
// Description: 
//      The header file of class CPEOperaotrDlg.
//
// Modify Log:
//      2018-10-29   Hoffman
//      Info: a. Add below member variables.
//              a.1.  m_apProppage;
//              a.2.  m_iCurSelectPage;
//              a.3.  m_pthdAnalysisFile;
//              a.4.  m_csFileFullName;
//              a.5.  m_pevtHasFileNeedToAnalysis;
//              a.6.  m_bProcessQuit;
//              a.7.  m_pstPEFileStruct32Orginal; 
//              a.8.  m_pstPEFileStruct32Modify;
//              a.9.  m_pstPEFileStruct64Orginal;
//              a.10. m_pstPEFileStruct64Modify;
//              a.11. m_pstTargetFileInfo; 
//              a.12. m_pageFileInfo;
//            b. Add below member methods.
//
//      2018-10-31  Hoffman
//      Info. a. Add below member variabls.
//              a.1. m_vctSectionInfo;
//              a.2. m_pageDirectory;
//
//      2019-01-07  Hoffman
//      Info. a. Modify below member methods.
//              a.1. SetPEFileStruct32();
//                  a.1.1. Fixed a bug that free resouce.
//******************************************************************************


#pragma once
#include "ProppageFileInfo.h"
#include "ProppageHeaderInfo.h"
#include "ProppageDirectoryInfo.h"
#include "ProppageSectionInfo.h"
#include "TypeShare.h"
#include "ThreadAnalysisFile.h"


// CPEOperatorDlg 对话框
class CPEOperatorDlg : public CDialogEx
{
// 构造
public:
	CPEOperatorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PEOPERATOR_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
private:
    CDialog *m_apProppage[TOTAL_NUM_OF_AOTI] = { NULL };
    int m_iCurSelectPage;
    CThreadAnalysisFile *m_pthdAnalysisFile = NULL;
    CString m_csFileFullName;
    CEvent *m_pevtHasFileNeedToAnalysis = NULL;
    BOOL m_bProcessQuit = FALSE;
           
    PPEFILESTRUCT32 m_pstPEFileStruct32Orginal = NULL;
    PPEFILESTRUCT32 m_pstPEFileStruct32Modify = NULL;
    PPEFILESTRUCT64 m_pstPEFileStruct64Orginal = NULL;
    PPEFILESTRUCT64 m_pstPEFileStruct64Modify = NULL;

    PTARGETFILEINFO m_pstTargetFileInfo = NULL;

    void FreeAllocMemory(BOOL bClose = FALSE);
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    // The ability option tab.
    CTabCtrl m_tabAbilityOption;
    CProppageFileInfo m_pageFileInfo;
    CProppageHeaderInfo m_pageHeaderInfo;
    CProppageDirectoryInfo m_pageDirectoryInfo;
    CProppageSectionInfo m_pageSectionInfo;
    std::vector<IMAGE_SECTION_HEADER> m_vctSectionInfo;

    afx_msg void OnTcnSelchangeTabAbilityoption(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnDropFiles(HDROP hDropInfo);
    // Edit control of target file.
    CEdit m_edtTargetFile;
    virtual void OnOK();
    virtual void OnCancel();

    BOOL CheckAnalysisFileEvent();
    inline CString GetTargetFileName() const
    {
        return m_csFileFullName;
    }

    inline void SetPEFileStruct32(PEFILESTRUCT32 *const pstPEFileStruct32)
    {
        if (NULL != m_pstPEFileStruct32Modify)
        {
            delete m_pstPEFileStruct32Modify;
            m_pstPEFileStruct32Modify = NULL;
        }

        m_pstPEFileStruct32Modify = pstPEFileStruct32;

        if (NULL != m_pstPEFileStruct32Orginal)
        {
            delete m_pstPEFileStruct32Orginal;
            m_pstPEFileStruct32Orginal = NULL;
        }

        m_pstPEFileStruct32Orginal = new PEFILESTRUCT32;
        *m_pstPEFileStruct32Orginal = *pstPEFileStruct32;
    }

    inline void SetTargetFileInfo(TARGETFILEINFO *const pstTargetFileInfo)
    {
        m_pstTargetFileInfo = pstTargetFileInfo;
    }

    inline BOOL GetProcessQuitInfo()
    {
        return m_bProcessQuit;
    }

protected:
    afx_msg LRESULT OnUpdateui(WPARAM wParam, LPARAM lParam);
public:
    // The text of operation notify
    CStatic m_txtOperationNotify;
protected:
    afx_msg LRESULT OnFilehadanalysised(WPARAM wParam, LPARAM lParam);
public:
    afx_msg void OnDestroy();
};
