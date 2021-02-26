#include "Omok.h"

HINSTANCE hInst;
HMENU hMenu;
CDraw *pDraw;
COmok *pOmok;

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
    hMenu = GetMenu(hwndDlg);

    switch(uMsg)
    {
    	
    case WM_INITDIALOG:
    { 
    	pDraw = new CDraw(hwndDlg);
	    pDraw->InitGdiplus();
		pOmok = new COmok(hwndDlg, pDraw);
    }
    return TRUE;

    case WM_CLOSE:
    {
    	delete pOmok;
    	delete pDraw;
        EndDialog(hwndDlg, 0);
        break;
    }
    return TRUE;
    
    case WM_LBUTTONUP:
	{
		short xPos = LOWORD(lParam);
		short yPos = HIWORD(lParam);
		pOmok->PutStone(Position(xPos, yPos));
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
		pDraw->OnPaint(hdc);
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
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_MAINDLG), NULL, (DLGPROC)DlgMain);
}
