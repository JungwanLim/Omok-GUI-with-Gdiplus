#include "Omok.h"

COmok::COmok(HWND hwndDlg, CDraw *pDraw):hwndDlg(hwndDlg), pDraw(pDraw)
{
	pData = new CData(pDraw);
	pRule = new CRule(pData);
	isGameOver = false;
}

COmok::~COmok()
{
	delete pData;
	delete pRule;
}

void COmok::InitGame()
{
	isGameOver = false;
	pData->InitGame();
	pDraw->DrawBoard();
	pDraw->UpdateBoard();
	SetWindowText(hwndDlg, TEXT("Omok"));
}

void COmok::PutStone(Position p)
{
	if(!pData->isOccupied(p) && !isGameOver)
	{
		//MessageBox(hwndDlg, "Test", "Test", MB_OK);
		pData->SetCoords();
		pData->SetBoard(BlackStone);
		pData->DrawStone();
		pDraw->UpdateBoard();
		CheckGameOver();
	}
}

void COmok::CheckShowNumber(HMENU hMenu, UINT state)
{
    if(state & MF_CHECKED)
    {
    	pDraw->SetShowNumber(false);
    	CheckMenuItem(hMenu, IDM_NUMBER, MF_UNCHECKED);
	}
	else
	{
    	pDraw->SetShowNumber(true);
    	CheckMenuItem(hMenu, IDM_NUMBER, MF_CHECKED);
	}
}

void COmok::Undo()
{
	pData->Undo();
	pDraw->UpdateBoard();
}

void COmok::UndoAll()
{
	pData->UndoAll();
	pDraw->UpdateBoard();
}

void COmok::Redo()
{
	pData->Redo();
	pDraw->UpdateBoard();
}

void COmok::RedoAll()
{
	pData->RedoAll();
	pDraw->UpdateBoard();
}

void COmok::CheckGameOver()
{
	Position p = pData->GetIndex();
	if(pRule->isGameOver(p.x, p.y, pData->GetCurrentStone()))
	{
		isGameOver = true;
		ShowEndMsg();
	}
}

void COmok::ShowEndMsg()
{
	const char *msg[] = {"Black Win!!!", "White Win!!!"};
	TCHAR title[256];
	sprintf(title, TEXT("Omok - %s"), msg[pData->GetCurrentStone() - 1]);
	SetWindowText(hwndDlg, title);
	MessageBox(hwndDlg, msg[pData->GetCurrentStone() - 1], "Game Over", MB_OK);
}

