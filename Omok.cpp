#include "Omok.h"

COmok::COmok(HWND hwndDlg, CDraw *pDraw):hwndDlg(hwndDlg), pDraw(pDraw)
{
	pData = new CData(pDraw);
}

COmok::~COmok()
{
	delete pData;
}

void COmok::PutStone(Position p)
{
	if(!pData->isOccupied(p))
	{
		//MessageBox(hwndDlg, "Test", "Test", MB_OK);
		pData->SetCoords();
		pData->SetBoard(BlackStone);
		pDraw->UpdateBoard();
	}
}
