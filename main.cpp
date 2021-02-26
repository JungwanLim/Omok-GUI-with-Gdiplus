#include "Omok.h"

HINSTANCE hInst;
HMENU hMenu;
CDraw draw;
COmok omok(&draw);

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
    hMenu = GetMenu(hwndDlg);

    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
	    draw.SetHwnd(hwndDlg);
	    omok.SetHwnd(hwndDlg);
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
        break;
    }
    return TRUE;
    
    case WM_LBUTTONUP:
	{
		short xPos = LOWORD(lParam);
		short yPos = HIWORD(lParam);
		omok.PutStone(Position(xPos, yPos));
		return 0;
	}

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
