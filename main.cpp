#include <windows.h>
#include <commctrl.h>
#include <gdiplus.h>
#include <iostream>
//#include <tchar.h>
#include "resource.h"

using namespace Gdiplus;

HINSTANCE hInst;
HMENU hMenu;

class CGdiPlusStarter
{
private:
	ULONG_PTR m_gpToken;

public:
	bool m_bSuccess;
	CGdiPlusStarter() {
		GdiplusStartupInput gpsi;
		m_bSuccess=(GdiplusStartup(&m_gpToken,&gpsi,NULL) == Ok);
	}
	~CGdiPlusStarter() {
		GdiplusShutdown(m_gpToken);
	}
};
CGdiPlusStarter g_gps;

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT num, size;
	bool bFound = false;
	
	ImageCodecInfo* pImageCodecInfo = nullptr;
	GetImageEncodersSize(&num, &size);

	pImageCodecInfo = (ImageCodecInfo*)malloc(size);
	GetImageEncoders(num, size, pImageCodecInfo);
	
	for(UINT i = 0; i < num; ++i)
	{
		if(wcscmp(pImageCodecInfo[i].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[i].Clsid;
			bFound = true;
			break;
		}
	}
	free(pImageCodecInfo);
	return bFound;
}

void MakeImage(Bitmap *pBitmap)
{
	CLSID pngClsid;
	bool result = GetEncoderClsid(L"image/png", &pngClsid);
	if(result == false)
	{
		//TRACE("Encoder Error!!");
		return;
	}
	pBitmap->Save(L"black.png", &pngClsid, nullptr);
}

BYTE Opa=128;
void OnPaint(HDC hdc)
{
	Graphics G(hdc);
	Bitmap bitmap(500, 500, &G);
	Graphics G2(&bitmap);
	Pen P1(Color(0, 0, 0), 2);
	Pen P2(Color(0, 0, 0), 1);
	SolidBrush S(Color(204,153,0));
	SolidBrush S1(Color(0,0,0));

	G2.FillRectangle(&S,0,0,500,500);
	G2.DrawRectangle(&P1, 32, 20, 480 - 32, 480 - 32);
    int start = 32;
    int end_line = 16 + 32 * 14;
    int x = 32 + 32;
    int y = x - 14;
	for(int i = 1; i < 14; ++i)
    {
        G2.DrawLine(&P2, x, start - 12, x, end_line + 2);
        G2.DrawLine(&P2, start, y, end_line + 16, y);
        x += 32;
        y += 32;
    }

    Font F(L"Arial",13,FontStyleBold,UnitPixel);
    SolidBrush B(Color(0,0,0));
    StringFormat SF;

    SF.SetAlignment(StringAlignmentCenter);

    const wchar_t* wStr = L"ABCDEFGHIJKLMNO";
    wchar_t wText[10];
    wchar_t wNum[10];

    for(int i = 0; i < 15; ++i)
    {
    	int dx = 24;
    	int dy = 10;
        PointF P(i * 32.0 + 32.0f,483.0f);
        PointF P1(10.0f, i * 32 + 10.0f);
        swprintf(wText, sizeof(wText) / sizeof(wchar_t), L"%c", wStr[i]);
        swprintf(wNum, sizeof(wText) / sizeof(wchar_t), L"%d", 15 - i);
        G2.DrawString(wText,-1,&F,P,&SF,&B);
        G2.DrawString(wNum,-1,&F,P1,&SF,&B);
    }
    G2.FillEllipse(&S1,29 + 32 * 3, 16+32*3,6,6);
    G2.FillEllipse(&S1,29 + 32 * 3, 16+32*11,6,6);
    G2.FillEllipse(&S1,29 + 32 * 11, 16+32*3,6,6);
    G2.FillEllipse(&S1,29 + 32 * 11, 16+32*11,6,6);
    G2.FillEllipse(&S1,29 + 32 * 7, 16+32*7,6,6);
    G.DrawImage(&bitmap, 0, 0);
	Image *pBlack;
	Image *pWhite;
	pBlack = Image::FromFile(L".\\Image\\Black.png");
	pWhite = Image::FromFile(L".\\Image\\White.png");
	Bitmap bitmap1(30, 30, &G);
	Graphics G3(&bitmap1);
	G3.SetInterpolationMode(InterpolationModeHighQuality);
	G3.DrawImage(pBlack, 0, 0, 30, 30);
	G.DrawImage(&bitmap1, 100, 100);
    MakeImage(&bitmap1);
}


BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR str[128];
    hMenu = GetMenu(hwndDlg);

    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
            case IDM_QUIT :
                SendMessage(hwndDlg, WM_CLOSE, 0, 0);
                break;
        }
    }
	case WM_PAINT:
		hdc=BeginPaint(hwndDlg, &ps);
		OnPaint(hdc);
		EndPaint(hwndDlg, &ps);
		return 0;
    return TRUE;
    }
    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
	if (g_gps.m_bSuccess == FALSE) {
		MessageBox(NULL,TEXT("GDI+ 라이브러리를 초기화할 수 없습니다."),
			TEXT("알림"),MB_OK);
		return 0;
	}
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_MAINDLG), NULL, (DLGPROC)DlgMain);
}
