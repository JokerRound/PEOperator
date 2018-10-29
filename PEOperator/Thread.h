#pragma once
#ifndef THREAD_H_
#define THREAD_H_
#include "StructShare.h"

struct tagThreadProcParameter
{
    LPVOID pClass_;
    LPVOID pParameter_;
    BOOL bStartSuccess_;
};

class CThread
{
public:
    // �߳̾��
    HANDLE m_hThread = INVALID_HANDLE_VALUE;
    // �߳�ID
    unsigned int m_dwThreadId = 0;
protected:
    
    // �̻߳ص���������
    tagThreadProcParameter m_stThreadProcParameter = { 0 };
    
    // �ɹ���ʼ���¼�
    CEvent *m_pevtThreadStartSuccess = NULL;

public:
    CThread();
    virtual ~CThread();
    
    virtual BOOL StartThread(LPVOID pParameter = NULL,
                             BOOL bInheritHandle = TRUE,
                             BOOL bIsSuspended = FALSE);


    //�����߳�
    virtual BOOL ConcludeThread(DWORD dwWaitTime = INFINITE);

    //�߳�ִ������
    virtual bool OnThreadEventStart()
    {
        return true;
    };

    virtual bool OnThreadEventRun(LPVOID lpParam)
    {
        return true;
    };

    virtual bool OnThreadEventEnd()
    {
        return true;
    }

    static DWORD ThreadFunc(LPVOID lpParam);
};

#endif // !THREAD_H_
