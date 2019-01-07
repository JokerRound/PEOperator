#include "stdafx.h"
#include "ThreadAnalysisFile.h"
#include "PEOperatorDlg.h"


CThreadAnalysisFile::CThreadAnalysisFile()
{
}


CThreadAnalysisFile::~CThreadAnalysisFile()
{
}

bool CThreadAnalysisFile::OnThreadEventRun(LPVOID lpParam)
{
#ifdef DEBUG
    DWORD dwError = -1;
    CString csErrorMessage;
#endif // DEBUG

    // Analysis parament.
    CPEOperatorDlg *pPEOperatorDlg = (CPEOperatorDlg *)lpParam;
    BOOL bRet = FALSE;

    // Main work loop
    while (TRUE)
    {
        // Wait for the event.
        bRet = pPEOperatorDlg->CheckAnalysisFileEvent();
        if (!bRet)
        {
            break;
        }

        // Check quit info is true or not.
        bRet = pPEOperatorDlg->GetProcessQuitInfo();
        if (bRet)
        {
            break;
        }

        // Get file's handle.
        HANDLE hTargetFile = CreateFile(pPEOperatorDlg->GetTargetFileName(),
                                        GENERIC_READ | GENERIC_WRITE,
                                        0,
                                        NULL,
                                        OPEN_EXISTING,
                                        FILE_ATTRIBUTE_NORMAL,
                                        NULL);
        if (INVALID_HANDLE_VALUE == hTargetFile)
        {
#ifdef DEBUG
            dwError = GetLastError();
            GetErrorMessage(dwError, csErrorMessage);
            OutputDebugStringWithInfo(csErrorMessage, __FILET__, __LINE__);
#endif // DEBUG
            CString csOperationNotify = _T("Please choice a file.");
            pPEOperatorDlg->SendMessage(WM_UPDATEUI, 
                                        (WPARAM)_T("Open file failed."
                                                   "Please check it."));
            continue;
        }

        CFile fTargetFile(hTargetFile);
        // Get file info.
        //******************************************************
        //* Alarm * This memory will free when main dialog close.
        //******************************************************
        PTARGETFILEINFO pstTargetFileInfo = new TARGETFILEINFO;
        CFileStatus TargetFileStatus;
        fTargetFile.GetStatus(TargetFileStatus);

        CPath pathFilePath = pPEOperatorDlg->GetTargetFileName();
        CPath pathFileName = pPEOperatorDlg->GetTargetFileName();
        pathFileName.StripPath();
        pathFilePath.RemoveFileSpec();

        // File path and name.
        pstTargetFileInfo->csFileName_ = pathFileName.m_strPath;
        pstTargetFileInfo->csFilePath_ = pathFilePath.m_strPath;

        // Carete time.
        pstTargetFileInfo->csCreatTime_.Format(
            _T("%d:%d:%d, %d.%d.%d"),
            TargetFileStatus.m_ctime.GetHour(),
            TargetFileStatus.m_ctime.GetMinute(),
            TargetFileStatus.m_ctime.GetSecond(),
            TargetFileStatus.m_ctime.GetDay(),
            TargetFileStatus.m_ctime.GetMonth(),
            TargetFileStatus.m_ctime.GetYear());

        pstTargetFileInfo->csLastAccessedTime_.Format(
            _T("%d:%d:%d, %d.%d.%d"),
            TargetFileStatus.m_atime.GetHour(),
            TargetFileStatus.m_atime.GetMinute(),
            TargetFileStatus.m_atime.GetSecond(),
            TargetFileStatus.m_atime.GetDay(),
            TargetFileStatus.m_atime.GetMonth(),
            TargetFileStatus.m_atime.GetYear());
        pstTargetFileInfo->csLastModifyTime_.Format(_T("%d:%d:%d, %d.%d.%d"),
                                         TargetFileStatus.m_mtime.GetHour(),
                                         TargetFileStatus.m_mtime.GetMinute(),
                                         TargetFileStatus.m_mtime.GetSecond(),
                                         TargetFileStatus.m_mtime.GetDay(),
                                         TargetFileStatus.m_mtime.GetMonth(),
                                         TargetFileStatus.m_mtime.GetYear());
        pstTargetFileInfo->csSize_.Format(_T("%I64u"), TargetFileStatus.m_size);

        // Begin to analysis.
        BOOL bHasError = FALSE;
        do
        {
            // Read dos header.
            IMAGE_DOS_HEADER stDosHeader = { 0 };
            fTargetFile.Read(&stDosHeader, sizeof(stDosHeader));

            // Check the magic member.
            if (0x5a4d != stDosHeader.e_magic)
            {
                bHasError = TRUE;
                break;
            }

            // Move the pointer of file to NT header.
            fTargetFile.Seek(stDosHeader.e_lfanew, CFile::begin);

            // Read PE fingerprint
            DWORD dwPEFingerprint;
            fTargetFile.Read(&dwPEFingerprint, sizeof(dwPEFingerprint));

            // Check PE fingerprint.
            if (0x4550 != dwPEFingerprint)
            {
                bHasError = TRUE; 
                break;
            }

            // Move the pointer of file to type of optional header.
            int iOptionalHeaderTyepPos =
                stDosHeader.e_lfanew + sizeof(DWORD) + 
                sizeof(IMAGE_FILE_HEADER);
            fTargetFile.Seek(iOptionalHeaderTyepPos, CFile::begin);

            // Read Optional header type.
            WORD wOptionalHeaderType = 0;
            fTargetFile.Read(&wOptionalHeaderType, sizeof(WORD));

            // Move the pointer of file to NT header.
            fTargetFile.Seek(stDosHeader.e_lfanew, CFile::begin);

            // Create struct of PE file 32bit.
            if (0x10b == wOptionalHeaderType)
            {
                //**************************************************************
                //* Alarm * This memory will free when main dialog close.
                //**************************************************************
                PPEFILESTRUCT32 pstPEFileStruct32 = new PEFILESTRUCT32;
                pstPEFileStruct32->stDosHeader_ = stDosHeader;

                // Read NT headers.
                fTargetFile.Read(&pstPEFileStruct32->stNtHeader_,
                                sizeof(pstPEFileStruct32->stNtHeader_));

                // Main dislog gets the PE file info.
                pPEOperatorDlg->SetPEFileStruct32(pstPEFileStruct32);

                // Read section info.
                WORD wSectionNumber = 
                    pstPEFileStruct32->stNtHeader_.FileHeader.NumberOfSections;
                WORD cntI = 0;
                while (cntI < wSectionNumber)
                {
                    //**********************************************************
                    //* Alarm * This memory will free when 
                    //          CPESectionInfo destroy.
                    //**********************************************************
                    IMAGE_SECTION_HEADER stSectionInfo = { 0 };

                    fTargetFile.Read(&stSectionInfo,
                                     sizeof(stSectionInfo));

                    pPEOperatorDlg->m_vctSectionInfo.push_back(stSectionInfo);
                    cntI++;
                }
            }
            // TODO: Create struct of PE file 64bit.
            else if (0x20b == wOptionalHeaderType)
            {

            }
            // Another
            else
            {
                bHasError = TRUE;
                break;
            }
        } while (FALSE); // do "Begin to analysis" END
        
        // Close file handle.        
        fTargetFile.Close();

        // Deal with analysis failed.
        if (bHasError)
        {
            CString csOperationNotify = _T("Target file don't belong PE.");
            pPEOperatorDlg->SendMessage(
                WM_UPDATEUI,
                MDUI_OPERATIONNOTIFY,
                (WPARAM)&csOperationNotify);

            continue;
        }

        pstTargetFileInfo->csIsPEFile_ = _T("Yes");
        // Main dialog gets file info.
        pPEOperatorDlg->SetTargetFileInfo(pstTargetFileInfo);

        // Notify analysis completed to main dailog.
        pPEOperatorDlg->SendMessage(WM_FILEHADANALYSISED);
    } //! while "Main work loop" END

    return true;
} //! CThreadAnalysisFile::OnThreadEventRun END