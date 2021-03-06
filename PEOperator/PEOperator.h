
//******************************************************************************
// License:     MIT
// Author:      Hoffman
// Create Time: 2018-10-29
// Description: 
//      The header file of class CPEOperatorApp.
//
// Modify Log:
//      None.
//******************************************************************************

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CPEOperatorApp:
// 有关此类的实现，请参阅 PEOperator.cpp
//

class CPEOperatorApp : public CWinApp
{
public:
	CPEOperatorApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CPEOperatorApp theApp;
