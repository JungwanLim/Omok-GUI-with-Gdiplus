#include "Omok.h"

COmok::COmok(CDraw *pDraw):pDraw(pDraw)
{
	pData = new CData(pDraw);
}

COmok::~COmok()
{
	delete pData;
}

void COmok::SetHwnd(HWND hwndDlg)
{
	this->hwndDlg = hwndDlg;
}

void COmok::PutStone(Position p)
{
	if(!pData->isOccupied(p))
	{
		pData->SetCoords(BlackStone);
		pData->SetBoard(BlackStone);
		pDraw->UpdateBoard();
	}
}
