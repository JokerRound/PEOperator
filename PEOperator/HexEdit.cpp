//******************************************************************************
// License:     MIT
// Author:      Hoffman
// Create Time: 2018-10-29
// Description: 
//      The achieve of class CHexEdit.
//
// Modify Log:
//      2018-10-29    Hoffman
//      Info: a. Add ahcieve below member methods.
//              a.1. OnChar();
//******************************************************************************

#include "stdafx.h"
#include "HexEdit.h"


// CHexEidt

IMPLEMENT_DYNAMIC(CHexEdit, CEdit)

CHexEdit::CHexEdit()
{

}

CHexEdit::~CHexEdit()
{
}


BEGIN_MESSAGE_MAP(CHexEdit, CEdit)
    ON_WM_CHAR()
END_MESSAGE_MAP()



// CHexEidt 消息处理程序

void CHexEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    if (isdigit(nChar) 
        || (nChar >= 'a' && nChar <= 'f')
        || (nChar >= 'A' && nChar <= 'F')
        || nChar == VK_DELETE
        || nChar == VK_BACK)
    {
        CEdit::OnChar(nChar, nRepCnt, nFlags);
    }
}
