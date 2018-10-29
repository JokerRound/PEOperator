#pragma once
#ifndef MACROSHARE_H_
#define MACROSHARE_H_

#ifdef _UNICODE
#define __FILET__ __FILEW__
#else
#define __FILET__ __FILE__ 
#endif // _UNICODE

#endif // !MACROSHARE_H_
