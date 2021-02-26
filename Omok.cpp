#include "Omok.h"

COmok::COmok(HWND hwndDlg, CDraw *pDraw):hwndDlg(hwndDlg), pDraw(pDraw)
{
	pRule = new CRule(pDraw);
	pData = new CData(pDraw, pRule);
	pTurn = pData->GetCurrentStone();
	isGameOver = false;
	mode = RENJU;
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
	pDraw->SetTitle(mode);
}

void COmok::SetMode(short mode)
{
	this->mode = mode;
	pDraw->SetTitle(mode);
}

void COmok::PutStone(Position p) // ���� ���� ���� �Լ� 
{
	if(!isGameOver && !pData->isOccupied(p, mode)) //���� ���� ���̰� �̹� ���� �����ִ��� �˻� ������ ���� �Ǹ� �� �� ������ �� 
	{
		pData->SetCoords(); // ���� ���� ��ǥ �Է� 
		pData->DrawStone(*pTurn, mode);
		pData->ResetRedo();
		isGameOver = pData->GetGameState();
	}
}

void COmok::CheckShowNumber(HMENU hMenu, UINT state) // �޴��� üũǥ�ø� ���ְų� uncheck �� �� 
{
	UINT uCheck[] = {MF_CHECKED, MF_UNCHECKED}; // �迭�� ��������ν� if else�� ���� �ʰ� �ܼ��ϰ� ó�� �� �� ����. 
	int idx = (state & MF_CHECKED) % 7; //����� 0�� 8�� ����Ǿ 7�� ��� ���� ���� 

	pDraw->SetShowNumber();
	if(mode && *pTurn == BlackStone) pData->CheckForbidden();
	pDraw->UpdateBoard();
	CheckMenuItem(hMenu, IDM_NUMBER, uCheck[idx]);
}

void COmok::Undo()
{
	pData->Undo(mode);
}

void COmok::UndoAll()
{
	pData->UndoAll();
}

void COmok::Redo()
{
	pData->Redo(mode);
}

void COmok::RedoAll()
{
	pData->RedoAll(mode);
}


