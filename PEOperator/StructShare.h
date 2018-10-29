#pragma once
#ifndef STRUCTSHARE_H_
#define STRUCTSHARE_H_

typedef enum tagAbilityOptionTabItem
{
    AOTI_FILEINFO,
    AOTI_HEADERINFO,


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
    IMAGE_NT_HEADERS32              stNtHeaer_;
    
} PEFILESTRUCT32, *PPEFILESTRUCT32;

typedef struct tagPEFileStruct64
{
    IMAGE_DOS_HEADER                stDosHeader_;
    
} PEFILESTRUCT64, *PPEFILESTRUCT64;

#endif // !STRUCTSHARE_H_

