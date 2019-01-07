//******************************************************************************
// License:     MIT
// Author:      Hoffman
// Create Time: 2018-10-29
// Description: 
//      The share macro in this project.
//
// Modify Log:
//      2018-10-29    Hoffman
//      Info: a. Add below mecroes.
//              a.1. __FILET__;
//              a.2. new;
//******************************************************************************

#pragma once
#ifndef MACROSHARE_H_
#define MACROSHARE_H_

#ifdef _UNICODE
#define __FILET__ __FILEW__
#else
#define __FILET__ __FILE__ 
#endif // _UNICODE

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#endif // !MACROSHARE_H_
