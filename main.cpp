#include "Main.h"

HINSTANCE hInst;
HMENU hMenu;
CDraw *pDraw;
COmok *pOmok;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_MAINDLG), NULL, (DLGPROC)DlgMain);
}

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
    hMenu = GetMenu(hwndDlg);

    switch(uMsg)
    {
    	
    case WM_INITDIALOG:
    { 
		if (g_gps.m_bSuccess == FALSE) {
			MessageBox(NULL,TEXT("GDI+ 라이브러리를 초기화할 수 없습니다."),
				TEXT("알림"),MB_OK);
			SendMessage(hwndDlg, WM_CLOSE, 0, 0);
			return false;
		}
    	pDraw = new CDraw(hwndDlg);
		pOmok = new COmok(hwndDlg, pDraw);
    }
    return TRUE;

    case WM_CLOSE:
    {
    	delete pOmok;
    	delete pDraw;
        EndDialog(hwndDlg, 0);
        return 0;
    }
    return TRUE;
    
    case WM_LBUTTONUP:
	{
		short xPos = LOWORD(lParam);
		short yPos = HIWORD(lParam);
		pOmok->PutStone(Position(xPos, yPos));
	}
	return TRUE;

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        	case IDM_NEW :
        		pOmok->InitGame();
        		break;
        		
            case IDM_QUIT :
                SendMessage(hwndDlg, WM_CLOSE, 0, 0);
                break;
                
            case IDM_NUMBER :
            {
                UINT state = GetMenuState(hMenu, IDM_NUMBER, MF_BYCOMMAND);
                pOmok->CheckShowNumber(hMenu, state);
                break;
			}
                
            case IDC_UNDO :
            	pOmok->Undo();
            	break;

            case IDC_UNDOALL :
            	pOmok->UndoAll();
            	break;

            case IDC_REDO :
            	pOmok->Redo();
            	break;

            case IDC_REDOALL :
            	pOmok->RedoAll();
            	break;
        }
        return TRUE;
    }
    return TRUE;
    
	case WM_PAINT:
		hdc=BeginPaint(hwndDlg, &ps);
		pDraw->OnPaint(hdc);
		EndPaint(hwndDlg, &ps);
		return 0;
    
	return TRUE;
    }
    
    return FALSE;
}
