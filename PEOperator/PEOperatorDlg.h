
// PEOperatorDlg.h: 头文件
//

#pragma once
#include "ProppageFileInfo.h"
#include "ProppageHeaderInfo.h"
#include "StructShare.h"
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
        m_pstPEFileStruct32Modify = pstPEFileStruct32;
        if (NULL == m_pstPEFileStruct32Orginal)
        {
            m_pstPEFileStruct32Orginal = new PEFILESTRUCT32;
            *m_pstPEFileStruct32Orginal = *pstPEFileStruct32;
        }
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
