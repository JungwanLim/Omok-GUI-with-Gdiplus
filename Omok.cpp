#include "Omok.h"

COmok::COmok(HWND hwndDlg, CDraw *pDraw):hwndDlg(hwndDlg), pDraw(pDraw)
{
	pData = new CData(pDraw);
	pRule = new CRule(pData);
	pTurn = pData->GetCurrentStone();
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
	SetWindowText(hwndDlg, TEXT("Omok"));
}

void COmok::PutStone(Position p) // 돌을 놓기 위한 함수 
{
	if(!pData->isOccupied(p) && !isGameOver) //보드 영역 밖이거 이미 돌이 놓여있는지 검사 게임이 종료 되면 둘 수 없도록 함 
	{
		pData->SetCoords(); // 돌이 놓일 좌표 입력 
		pData->DrawStone(*pTurn);
		pData->ResetRedo();
		CheckGameOver();
	}
}

void COmok::CheckShowNumber(HMENU hMenu, UINT state) // 메뉴의 체크표시를 해주거나 uncheck 해 줌 
{
	UINT uCheck[] = {MF_CHECKED, MF_UNCHECKED}; // 배열을 사용함으로써 if else를 쓰지 않고 단순하게 처리 할 수 있음. 
	int idx = (state & MF_CHECKED) % 7; //결과가 0과 8이 검출되어서 7의 모드 값을 취함 

	pDraw->SetShowNumber();
	CheckMenuItem(hMenu, IDM_NUMBER, uCheck[idx]);
}

void COmok::Undo()
{
	pData->Undo();
}

void COmok::UndoAll()
{
	pData->UndoAll();
}

void COmok::Redo()
{
	pData->Redo();
}

void COmok::RedoAll()
{
	pData->RedoAll();
}

void COmok::CheckGameOver() // 게임이 끝났는지(승부가 결정이 났는지) 검사하는 함수 
{
	short stone = 3 - *pTurn; //착수한 이후이므로 이전 돌로 검사를 해야함 

	Position p = pData->GetIndex();
	if(pRule->isGameOver(p.x, p.y, stone))
	{
		isGameOver = true;
		ShowEndMsg();
	}
}

void COmok::ShowEndMsg() // 승부가 결정이 나면 승자를 메시지 박스와 타이틀 바에 표시해 줌 
{
	TCHAR title[256];
	short stone = 3 - *pTurn; // 돌을 둔 다음이므로 이전 돌이 승리 
	const char *msg[] = {"Black Win!!!", "White Win!!!"};

	sprintf(title, TEXT("Omok - %s"), msg[stone - 1]);
	SetWindowText(hwndDlg, title);
	MessageBox(hwndDlg, msg[stone - 1], "Game Over", MB_OK);
}

