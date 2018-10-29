#pragma once
#ifndef THREADANALYSISFILE_H_
#define THREADANALYSISFILE_H_

#include "Thread.h"

class CThreadAnalysisFile :
    public CThread
{
public:
    CThreadAnalysisFile();
    virtual ~CThreadAnalysisFile();

    virtual bool OnThreadEventRun(LPVOID lpParam);

};

#endif // ! THREADANALYSISFILE_H_
