#pragma once
#ifndef ASSISTFUNC_H_
#define ASSISTFUNC_H_
#include "StructShare.h"
#include "MacroShare.h"

void OutputDebugStringWithInfo(_In_ const CString csOuput,
                               _In_ const CString csFileNmae,
                               _In_ DWORD dwFileLine);


void GetErrorMessage(_In_ DWORD dwError,
                     _In_ CString &ref_csMessage);


std::basic_string<TCHAR> Byte2HexString(_In_ const BYTE bytTarget);
std::basic_string<TCHAR> Word2HexString(_In_ const WORD wTarget);
std::basic_string<TCHAR> Dword2HexString(_In_ const DWORD dwTarget);

#endif // !ASSISTFUNC_H_
