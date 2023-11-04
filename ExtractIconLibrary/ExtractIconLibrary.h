#pragma once


#ifdef EXTRACTICONLIBRARY_EXPORTS
#define EXTRACTICONLIBRARY_API __declspec(dllexport)
#else
#define EXTRACTICONLIBRARY_API __declspec(dllimport)
#endif

extern "C" EXTRACTICONLIBRARY_API int ExtractIconV1(const wchar_t* pszPath, const wchar_t* expPath);

extern "C" EXTRACTICONLIBRARY_API int ExtractIconV2(const wchar_t* pszPath, const wchar_t* expPath);

extern "C" EXTRACTICONLIBRARY_API int ExtractIconV3(const wchar_t* pszPath, const wchar_t* expPath, int size);