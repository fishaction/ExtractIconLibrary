# ExtractIconLibrary
Golangから叩く用 V1は32x32, V2は255x255のアイコンを出力できる。V3はサイズの指定が可能。
```
extern "C" EXTRACTICONLIBRARY_API int ExtractIconV1(const wchar_t* pszPath, const wchar_t* expPath);

extern "C" EXTRACTICONLIBRARY_API int ExtractIconV2(const wchar_t* pszPath, const wchar_t* expPath);

extern "C" EXTRACTICONLIBRARY_API int ExtractIconV3(const wchar_t* pszPath, const wchar_t* expPath, int size);
```
`pszPath`: exeファイルのパス  
`expPath`: pngファイルの出力先  
`size`: MSが公開しているドキュメントに基づく定数  
`size`に関して`Parameters`の`[int]iImageList`に該当 以下url参照  
https://learn.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-shgetimagelist
