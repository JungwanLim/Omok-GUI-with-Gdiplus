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

void COmok::PutStone(Position p) // 돌을 놓기 위한 함수 
{
	if(!isGameOver && !pData->isOccupied(p, mode)) //보드 영역 밖이거 이미 돌이 놓여있는지 검사 게임이 종료 되면 둘 수 없도록 함 
	{
		pData->SetCoords(); // 돌이 놓일 좌표 입력 
		pData->DrawStone(*pTurn, mode);
		pData->ResetRedo();
		isGameOver = pData->GetGameState();
	}
}

void COmok::CheckShowNumber(HMENU hMenu, UINT state) // 메뉴의 체크표시를 해주거나 uncheck 해 줌 
{
	UINT uCheck[] = {MF_CHECKED, MF_UNCHECKED}; // 배열을 사용함으로써 if else를 쓰지 않고 단순하게 처리 할 수 있음. 
	int idx = (state & MF_CHECKED) % 7; //결과가 0과 8이 검출되어서 7의 모드 값을 취함 

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


