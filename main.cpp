#include "Draw.h"

HINSTANCE hInst;
HMENU hMenu;
CDraw draw;

/*
BYTE Opa=128;
void OnPaint(HDC hdc)
{
	Graphics G(hdc);
	Image *pBoard, *pBlack, *pWhite, *pForbidden, *pBlack_a;
	pBoard = Image::FromFile(L".\\Image\\board.png");
	pBlack = Image::FromFile(L".\\Image\\Black.png");
	pBlack_a = Image::FromFile(L".\\Image\\Black_a.png");
	pWhite = Image::FromFile(L".\\Image\\White.png");
	pForbidden = Image::FromFile(L".\\Image\\forbidden.png");

	G.SetInterpolationMode(InterpolationModeHighQualityBilinear);
	G.DrawImage(pBoard,0,0);
	G.DrawImage(pBlack,49 - 32,35, 30, 30);
	G.DrawImage(pWhite,49,67, 30, 30);
	G.DrawImage(pForbidden,49,99);
	G.DrawImage(pWhite,49 + 32 * 10,131 + 32 * 10, 30, 30);
	G.DrawImage(pWhite,81,99, 30, 30);
	G.DrawImage(pBlack,17,99 + 32 * 11, 30, 30);
	G.DrawImage(pForbidden,49 + 32*5 ,99);
	G.DrawImage(pBlack_a,49 + 64 + 32*5 ,99);
	delete pBoard;
	delete pBlack;
	delete pWhite;
	delete pForbidden;
	delete pBlack_a;
}
*/

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
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
        break;
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
		draw.OnPaint(hdc);
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
    if(!draw.InitGdiplus())
    {
    	return false;
	}
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_MAINDLG), NULL, (DLGPROC)DlgMain);
}
