#include "pch.h"
#include "ExtractIconLibrary.h"

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "comctl32.lib")

using namespace Gdiplus;

int ExtractIconV1(const wchar_t*,const wchar_t*);
int ExtractIconV2(const wchar_t*, const wchar_t*);
int ExtractIconV3(const wchar_t*, const wchar_t*, int);
int GetEncoderClsid(const WCHAR*, CLSID*);


int ExtractIconV1(const wchar_t* pszPath, const wchar_t* expPath) {

    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    DWORD dwFileAttributes = -1;
    SHFILEINFOW psfi = { 0 };
    UINT cbFileInfo = sizeof(psfi);
    UINT uFlags = SHGFI_ICON | SHGFI_LARGEICON;

    int result = SHGetFileInfoW(pszPath, dwFileAttributes, &psfi, cbFileInfo, uFlags);
    if (result == 0) {
        return -1;
    }

    HICON hicon = psfi.hIcon;
    Bitmap* bitmap = Bitmap::FromHICON(hicon);

    CLSID encoderClsid;

    WCHAR  strGuid[39];


    GetEncoderClsid(L"image/png", &encoderClsid);
    Status stat = bitmap->Save(expPath, &encoderClsid, NULL);

    delete bitmap;
    GdiplusShutdown(gdiplusToken);

    if (stat == Ok) {

    }
    else {
        return -1;
    }

    return 0;
}

int ExtractIconV2(const wchar_t* pszPath, const wchar_t* expPath) {

    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    DWORD dwFileAttributes = -1;
    SHFILEINFOW psfi = { 0 };
    UINT cbFileInfo = sizeof(psfi);
    UINT uFlags = SHGFI_SYSICONINDEX;

    int result = SHGetFileInfo(pszPath, dwFileAttributes, &psfi, cbFileInfo, uFlags);
    if (result == 0) {
        return -1;
    }

    HIMAGELIST* imageList;

    HRESULT hresult = SHGetImageList(SHIL_JUMBO, IID_IImageList, (void**)&imageList);
    if (hresult != S_OK) {
        return -1;
    }
    HICON hicon;
    hresult = ((IImageList*)imageList)->GetIcon(psfi.iIcon, ILD_TRANSPARENT, &hicon);
    if (hresult != S_OK) {
        return -1;
    }
    Bitmap* bitmap = Bitmap::FromHICON(hicon);

    CLSID encoderClsid;

    WCHAR  strGuid[39];


    GetEncoderClsid(L"image/png", &encoderClsid);
    Status stat = bitmap->Save(expPath, &encoderClsid, NULL);

    delete bitmap;
    GdiplusShutdown(gdiplusToken);

    if (stat == Ok) {
    }
    else {
        return -1;
    }

    return 0;
}

int ExtractIconV3(const wchar_t* pszPath, const wchar_t* expPath, int size) {

    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    DWORD dwFileAttributes = -1;
    SHFILEINFOW psfi = { 0 };
    UINT cbFileInfo = sizeof(psfi);
    UINT uFlags = SHGFI_SYSICONINDEX;

    int result = SHGetFileInfo(pszPath, dwFileAttributes, &psfi, cbFileInfo, uFlags);
    if (result == 0) {
        return -1;
    }

    HIMAGELIST* imageList;

    HRESULT hresult = SHGetImageList(size, IID_IImageList, (void**)&imageList);
    if (hresult != S_OK) {
        return -1;
    }
    HICON hicon;
    hresult = ((IImageList*)imageList)->GetIcon(psfi.iIcon, ILD_TRANSPARENT, &hicon);
    if (hresult != S_OK) {
        return -1;
    }
    Bitmap* bitmap = Bitmap::FromHICON(hicon);

    CLSID encoderClsid;

    WCHAR  strGuid[39];


    GetEncoderClsid(L"image/png", &encoderClsid);
    Status stat = bitmap->Save(expPath, &encoderClsid, NULL);

    delete bitmap;
    GdiplusShutdown(gdiplusToken);

    if (stat == Ok) {
    }
    else {
        return -1;
    }

    return 0;
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
    UINT  num = 0;
    UINT  size = 0;

    ImageCodecInfo* pImageCodecInfo = NULL;

    GetImageEncodersSize(&num, &size);
    if (size == 0)
        return -1;

    pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
    if (pImageCodecInfo == NULL)
        return -1;

    GetImageEncoders(num, size, pImageCodecInfo);

    for (UINT j = 0; j < num; ++j)
    {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
        {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;
        }
    }

    free(pImageCodecInfo);
    return -1;
}