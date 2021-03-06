//******************************************************************************
// License:     MIT
// Author:      Hoffman
// Create Time: 2018-10-29
// Description: 
//      The achieve of class CPEOperatorDlg.
//
// Modify Log:
//      2018-10-29    Hoffman
//      Info: a. Add achieve of below member methods.
//              a.1. FreeAllocMemory();
//              a.2. OnTcnSelchangeTabAbilityoption();
//              a.3. OnDropFiles();
//              a.3. OnOK();
//              a.3. OnCancel();
//              a.3. CheckAnalysisFileEvent();
//              a.3. OnFilehadanalysised();
//              a.3. OnDestroy();
//            b. Modify achieve of below member methods.
//              b.1. OnInitDialog();
//                  b.1.1. Add the init acitve such as alloc resouce.
//
//      2019-01-05    Hoffman
//      Info: a. Modify below member methods.
//              a.1. OnInitDialog();
//                  a.1.1. Add section info and directory info pages.
//              a.2. OnFilehadanalysised();
//                  a.2.1. Add notify active for section and direcotry page.
//******************************************************************************

#include "stdafx.h"
#include "PEOperator.h"
#include "PEOperatorDlg.h"
#include "afxdialogex.h"
#include "MacroShare.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPEOperatorDlg 对话框



CPEOperatorDlg::CPEOperatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PEOPERATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);



}

void CPEOperatorDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB_ABILITYOPTION, m_tabAbilityOption);
    DDX_Control(pDX, IDC_EDIT_TARGETFILE, m_edtTargetFile);
    DDX_Control(pDX, IDC_STATIC_OPERATIONNOTIFY, m_txtOperationNotify);
}

BEGIN_MESSAGE_MAP(CPEOperatorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_ABILITYOPTION, &CPEOperatorDlg::OnTcnSelchangeTabAbilityoption)
    ON_WM_DROPFILES()
    ON_MESSAGE(WM_UPDATEUI, &CPEOperatorDlg::OnUpdateui)
    ON_MESSAGE(WM_FILEHADANALYSISED, &CPEOperatorDlg::OnFilehadanalysised)
    ON_WM_DESTROY()
END_MESSAGE_MAP()


// CPEOperatorDlg 消息处理程序

void CPEOperatorDlg::FreeAllocMemory(BOOL bClose /*=FALSE*/)
{
    if (NULL != m_pstPEFileStruct32Modify)
    {
        delete m_pstPEFileStruct32Modify;
        m_pstPEFileStruct32Modify = NULL;
    }

    if (NULL != m_pstPEFileStruct32Orginal)
    {
        delete m_pstPEFileStruct32Orginal;
        m_pstPEFileStruct32Orginal = NULL;
    }

    if (NULL != m_pstPEFileStruct64Orginal)
    {
        delete m_pstPEFileStruct64Orginal;
        m_pstPEFileStruct64Orginal = NULL;
    }

    if (NULL != m_pstPEFileStruct64Modify)
    {
        delete m_pstPEFileStruct64Modify;
        m_pstPEFileStruct64Modify = NULL;
    }

    if (NULL != m_pstTargetFileInfo)
    {
        delete m_pstTargetFileInfo;
        m_pstTargetFileInfo = NULL;
    }

    if (bClose)
    {
        m_bProcessQuit = TRUE;

        if (NULL != m_pthdAnalysisFile)
        {
            m_pevtHasFileNeedToAnalysis->SetEvent();

            delete m_pthdAnalysisFile;
            m_pthdAnalysisFile = NULL;
        }

        if (NULL != m_pevtHasFileNeedToAnalysis)
        {
            delete m_pevtHasFileNeedToAnalysis;
            m_pevtHasFileNeedToAnalysis = NULL;
        }
    }
} //! CPEOperatorDlg::FreeAllocMemory() END;

BOOL CPEOperatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

#ifdef DEBUG
    DWORD dwError = -1;
    CString csErrorMessage;
    DWORD dwLine = 0;
    BOOL bOutputErrMsg = FALSE;
#endif // DEBUG

    BOOL bRet = FALSE;
    do
    {
        // Carete event auto and unsigned.
        //******************************************************
        //* Alarm * This memory will free when main dialog close.
        //******************************************************
        m_pevtHasFileNeedToAnalysis = new CEvent(FALSE, FALSE);
        if (NULL == m_pevtHasFileNeedToAnalysis)
        {
#ifdef DEBUG
            dwError = GetLastError();
            GetErrorMessage(dwError, csErrorMessage);
            OutputDebugStringWithInfo(csErrorMessage, __FILET__, __LINE__);
#endif // DEBUG
            break;
        }

        // Start work thread to analysis this file.
        //******************************************************
        //* Alarm * This memory will free when main dialog close.
        //******************************************************
        m_pthdAnalysisFile = new CThreadAnalysisFile();
        if (NULL == m_pthdAnalysisFile) 
        {
#ifdef DEBUG
            dwError = GetLastError();
            GetErrorMessage(dwError, csErrorMessage);
            OutputDebugStringWithInfo(csErrorMessage, __FILET__, __LINE__);
#endif // DEBUG
            break;
        }
        m_pthdAnalysisFile->StartThread(this);

        // Save point of page.
        m_apProppage[AOTI_FILEINFO] = &m_pageFileInfo;
        m_apProppage[AOTI_HEADERINFO] = &m_pageHeaderInfo;
        m_apProppage[AOTI_DIRECTORYINFO] = &m_pageDirectoryInfo;
        m_apProppage[AOTI_SECTIONINFO] = &m_pageSectionInfo;

        // Initialize 'File Info' page.
        bRet = m_pageFileInfo.Create(IDD_PROPPAGE_FILEINFO,
                                     &m_tabAbilityOption);
        if (!bRet)
        {
#ifdef DEBUG
            dwError = GetLastError();
            GetErrorMessage(dwError, csErrorMessage);
            OutputDebugStringWithInfo(csErrorMessage, __FILET__, __LINE__);
#endif // DEBUG
        }

        // Initialize 'Header Info' page.
        bRet = m_pageHeaderInfo.Create(IDD_PROPPAGE_HEADERINFO,
                                       &m_tabAbilityOption);
        if (!bRet)
        {
#ifdef DEBUG
            dwError = GetLastError();
            GetErrorMessage(dwError, csErrorMessage);
            OutputDebugStringWithInfo(csErrorMessage, __FILET__, __LINE__);
#endif // DEBUG
        }

        // Initialize 'Directory Info' page
        bRet = m_pageDirectoryInfo.Create(IDD_PROPPAGE_DIRECTORYINFO,
                                          &m_tabAbilityOption);
        if (!bRet)
        {
#ifdef DEBUG
            dwError = GetLastError();
            GetErrorMessage(dwError, csErrorMessage);
            OutputDebugStringWithInfo(csErrorMessage, __FILET__, __LINE__);
#endif // DEBUG
        }

        // Initialize 'Section Info' page
        bRet = m_pageSectionInfo.Create(IDD_PROPPAGE_SECTIONINFO,
                                        &m_tabAbilityOption);
        if (!bRet)
        {
#ifdef DEBUG
            dwError = GetLastError();
            GetErrorMessage(dwError, csErrorMessage);
            OutputDebugStringWithInfo(csErrorMessage, __FILET__, __LINE__);
#endif // DEBUG
        }

        // Initialize tab ability option.
        m_tabAbilityOption.InsertItem(AOTI_FILEINFO, _T("File info"));
        m_tabAbilityOption.InsertItem(AOTI_HEADERINFO, _T("Header info"));
        m_tabAbilityOption.InsertItem(AOTI_DIRECTORYINFO, _T("Direcotry info"));
        m_tabAbilityOption.InsertItem(AOTI_SECTIONINFO, _T("Section info"));

        // Get client aera of tab.
        CRect rctFeildToShow;
        m_tabAbilityOption.GetClientRect(&rctFeildToShow);
        rctFeildToShow.top += 25;
        rctFeildToShow.bottom -= 5;
        rctFeildToShow.left += 5;
        rctFeildToShow.right -= 5;

        // Set first page to show, and maek another page hidely.
        for (int cntI = AOTI_FILEINFO; cntI < TOTAL_NUM_OF_AOTI; cntI++)
        {
            m_apProppage[cntI]->MoveWindow(rctFeildToShow);
            m_apProppage[cntI]->ShowWindow(SW_HIDE);
        }

        m_iCurSelectPage = AOTI_FILEINFO;
        m_tabAbilityOption.SetCurSel(AOTI_FILEINFO);
        m_apProppage[AOTI_FILEINFO]->ShowWindow(SW_NORMAL);

        // Change text of operational notify.
        CString csOperationNotify = _T("Please choice a file.");
        this->SendMessage(WM_UPDATEUI,
                          MDUI_OPERATIONNOTIFY,
                          (LPARAM)&csOperationNotify);
        return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
    } while (FALSE);
   
#ifdef DEBUG
    if (bOutputErrMsg && 0 != dwLine)
    {
        dwError = GetLastError();
        GetErrorMessage(dwError, csErrorMessage);
        OutputDebugStringWithInfo(csErrorMessage, __FILET__, dwLine);
    }
#endif // DEBUG 

    this->SendMessage(WM_CLOSE);
    return FALSE;
} //! CPEOperatorDlg::OnInitDialog END

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPEOperatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND,
                    reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPEOperatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CPEOperatorDlg::OnTcnSelchangeTabAbilityoption(NMHDR *pNMHDR,
                                                    LRESULT *pResult)
{
    int iTargetPage = m_tabAbilityOption.GetCurSel();

    m_apProppage[iTargetPage]->ShowWindow(SW_NORMAL);
    m_apProppage[m_iCurSelectPage]->ShowWindow(SW_HIDE);
    m_iCurSelectPage = iTargetPage;

    *pResult = 0;
} //! CPEOperatorDlg::OnTcnSelchangeTabAbilityoption END


void CPEOperatorDlg::OnDropFiles(HDROP hDropInfo)
{
#ifdef DEBUG
    DWORD dwError = -1;
    CString csErrorMessage;
#endif // DEBUG
    FreeAllocMemory();

    BOOL bRet = FALSE;
    int iRet = DragQueryFile(hDropInfo,
                             0,
                             m_csFileFullName.GetBufferSetLength(MAX_PATH),
                             MAX_PATH);
    m_csFileFullName.ReleaseBuffer();

    // Show full name of file in edit.
    this->SendMessage(WM_UPDATEUI, MDUI_FILEPATH);


    // The thread begin to analysis target file.
    bRet = m_pevtHasFileNeedToAnalysis->SetEvent();
    if (!bRet)
    {
#ifdef DEBUG
            dwError = GetLastError();
            GetErrorMessage(dwError, csErrorMessage);
            OutputDebugStringWithInfo(csErrorMessage, __FILET__, __LINE__);
#endif // DEBUG        
    }

    DragFinish(hDropInfo);
    CDialogEx::OnDropFiles(hDropInfo);
} //! CPEOperatorDlg::OnDropFile END


void CPEOperatorDlg::OnOK()
{

}


void CPEOperatorDlg::OnCancel()
{
    //TODO: Notify save or not if had changed.

    CDialogEx::OnCancel();
}

BOOL CPEOperatorDlg::CheckAnalysisFileEvent()
{
    DWORD dwRet = WAIT_FAILED;
    if (NULL != m_pevtHasFileNeedToAnalysis)
    {
        dwRet = WaitForSingleObject(m_pevtHasFileNeedToAnalysis->m_hObject,
                                    INFINITE);
    }

    return WAIT_FAILED == dwRet ? FALSE : TRUE;
}

afx_msg LRESULT CPEOperatorDlg::OnUpdateui(WPARAM wParam, LPARAM lParam)
{
    MAINDLGUPDATEITEM eUpdateItem = (MAINDLGUPDATEITEM)wParam;

    switch (eUpdateItem)
    {
        case MDUI_FILEPATH:
        {
            m_edtTargetFile.SetWindowText(m_csFileFullName);

            break;
        }
        case MDUI_OPERATIONNOTIFY:
        {
            CString *pcsOperationNotify = (CString *)lParam;
            m_txtOperationNotify.SetWindowText(*pcsOperationNotify);

            break;
        }
        default:
        {
            break;
        }
    }

    return 0;
} //! CPEOperatorDlg::OnUpdateui END


afx_msg LRESULT CPEOperatorDlg::OnFilehadanalysised(WPARAM wParam, 
                                                    LPARAM lParam)
{
    // Notify File info page to update.
    m_pageFileInfo.SendMessage(WM_FILEHADANALYSISED,
                               (WPARAM)m_pstTargetFileInfo);

    // Notify Header Info page to update.
    m_pageHeaderInfo.SendMessage(WM_FILEHADANALYSISED,
                                 32,
                                 (LPARAM)m_pstPEFileStruct32Modify);

    // Notify Directory info page to update.
    m_pageDirectoryInfo.SendMessage(WM_FILEHADANALYSISED,
                                    (WPARAM)m_pstPEFileStruct32Modify->
                                    stNtHeader_.OptionalHeader.DataDirectory);

    // Notify Section info page to update.
    m_pageSectionInfo.SendMessage(WM_FILEHADANALYSISED,
                                  (WPARAM)&m_vctSectionInfo);

    // Flush operation notify.
    CString csOperationNotify = _T("Analysis completed.");
    SendMessage(WM_UPDATEUI,
                MDUI_OPERATIONNOTIFY,
                (WPARAM)&csOperationNotify);

    UpdateData();

    return 0;
} //! CPEOperatorDlg::OnFilehadanalysised END


void CPEOperatorDlg::OnDestroy()
{
    FreeAllocMemory(TRUE);

    CDialogEx::OnDestroy();
} //! CPEOperatorDlg::OnDestroy END
