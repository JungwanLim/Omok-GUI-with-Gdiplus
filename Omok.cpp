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

void COmok::PutStone(Position p) // ���� ���� ���� �Լ� 
{
	if(!pData->isOccupied(p) && !isGameOver) //���� ���� ���̰� �̹� ���� �����ִ��� �˻� ������ ���� �Ǹ� �� �� ������ �� 
	{
		pData->SetCoords(); // ���� ���� ��ǥ �Է� 
		pData->DrawStone(*pTurn);
		pData->ResetRedo();
		CheckGameOver();
	}
}

void COmok::CheckShowNumber(HMENU hMenu, UINT state) // �޴��� üũǥ�ø� ���ְų� uncheck �� �� 
{
	UINT uCheck[] = {MF_CHECKED, MF_UNCHECKED}; // �迭�� ��������ν� if else�� ���� �ʰ� �ܼ��ϰ� ó�� �� �� ����. 
	int idx = (state & MF_CHECKED) % 7; //����� 0�� 8�� ����Ǿ 7�� ��� ���� ���� 

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

void COmok::CheckGameOver() // ������ ��������(�ºΰ� ������ ������) �˻��ϴ� �Լ� 
{
	short stone = 3 - *pTurn; //������ �����̹Ƿ� ���� ���� �˻縦 �ؾ��� 

	Position p = pData->GetIndex();
	if(pRule->isGameOver(p.x, p.y, stone))
	{
		isGameOver = true;
		ShowEndMsg();
	}
}

void COmok::ShowEndMsg() // �ºΰ� ������ ���� ���ڸ� �޽��� �ڽ��� Ÿ��Ʋ �ٿ� ǥ���� �� 
{
	TCHAR title[256];
	short stone = 3 - *pTurn; // ���� �� �����̹Ƿ� ���� ���� �¸� 
	const char *msg[] = {"Black Win!!!", "White Win!!!"};

	sprintf(title, TEXT("Omok - %s"), msg[stone - 1]);
	SetWindowText(hwndDlg, title);
	MessageBox(hwndDlg, msg[stone - 1], "Game Over", MB_OK);
}

