//******************************************************************************
// License:     MIT
// Author:      Hoffman
// Create Time: 2018-10-29
// Description: 
//      The header file of class CHexEdit.
//
// Modify Log:
//      2018-10-29    Hoffman
//      Info: a. Add declare of below member methods.
//              a.1. 
//******************************************************************************

#pragma once

// CHexEidt

class CHexEdit : public CEdit
{
	DECLARE_DYNAMIC(CHexEdit)

public:
	CHexEdit();
	virtual ~CHexEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


