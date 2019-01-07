//******************************************************************************
// License:     MIT
// Author:      Hoffman
// Create Time: 2018-10-29
// Description: 
//      The type are shared in this project.
//
// Modify Log:
//      2018-10-29    Hoffman
//      Info: a. Add below types.
//              a.1. enum tagAbilityOptionTabItem;
//              a.1. enum tagMainDlgUpdateItem;
//              a.1. struct tagTargetFileInfo;
//              a.1. struct tagPEFileStruct32;
//              a.1. struct tagPEFileStruct64;
//
//      2018-01-05    Hoffman
//      Info: a. Modify below type.
//              a.1. enum tagAbilityOptionTabItem;
//                  a.1.1. Add AOTI_DIRECTORYINFO and AOTI_SECTIONINFO;
//******************************************************************************

#pragma once
#ifndef STRUCTSHARE_H_
#define STRUCTSHARE_H_

typedef enum tagAbilityOptionTabItem
{
    AOTI_FILEINFO,
    AOTI_HEADERINFO,
    AOTI_DIRECTORYINFO,
    AOTI_SECTIONINFO,

    TOTAL_NUM_OF_AOTI
} ABILITYOPTIONTABITEM, *PABILITYOPTIONTABITEM;

typedef enum tagMainDlgUpdateItem
{
    MDUI_FILEPATH,
    MDUI_OPERATIONNOTIFY,
} MAINDLGUPDATEITEM, *PMAINDLGUPDATEITEM;

typedef struct tagTargetFileInfo
{
    CString csFileName_;
    CString csFilePath_;
    CString csSize_;
    CString csCreatTime_;
    CString csLastModifyTime_;
    CString csLastAccessedTime_;
    CString csIsPEFile_;
} TARGETFILEINFO, *PTARGETFILEINFO;

typedef struct tagPEFileStruct32
{
    IMAGE_DOS_HEADER                stDosHeader_;
    IMAGE_NT_HEADERS32              stNtHeader_;
} PEFILESTRUCT32, *PPEFILESTRUCT32;

typedef struct tagPEFileStruct64
{
    IMAGE_DOS_HEADER                stDosHeader_;
    
} PEFILESTRUCT64, *PPEFILESTRUCT64;

#endif // !STRUCTSHARE_H_

