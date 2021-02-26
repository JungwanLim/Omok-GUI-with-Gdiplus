#include "Data.h"

CData::CData(CDraw *pDraw, CRule *pRule) : pDraw(pDraw), pRule(pRule)
{
	SetPixelCoords();
	this->pCoords = pDraw->GetCoords();
	pRule->SetBoard(board);
	InitGame();
}

CData::~CData()
{
}

void CData::InitGame()
{
	isGameOver = false;
	pCoords->clear();
	redo.clear();
	ClearBoard();
}

void CData::ClearBoard()
{
	turn = BlackStone;
	InitBoard();
	pDraw->DrawBoard();
	pDraw->UpdateBoard(); // �ʿ��� �������� �ʱ�ȭ �ϰ� ���带 �׷� ȭ�鿡 ������ 
}

void CData::InitBoard()
{
	for(int i = 0; i < boardLine; ++i)
	{
		for(int j = 0; j < boardLine; ++j)
		{
			board[i][j] = 0;
		}
	}
}

void CData::SetPixelCoords() //��ǥ���� ������ 
{
	short x = 16, y = 4;
	for(int i = 0; i < boardLine; ++i)
	{
		y = 4 + i * 32;
		for(int j = 0; j < boardLine; ++j)
		{
			x = 16 + j * 32;
			pixelCoords.push_back(Position(x, y));
		}
	}
}

short *CData::GetCurrentStone()
{
	return &turn;
}

void CData::SetBoard(short stone)
{
	board[index.y][index.x] = stone;
}

void CData::GetBoardIndex() // �ȼ� ��ǥ�� board���� ���� �Ϸ� ��ȣ(index)�� �ٲ� 
{
	index.x = (coord.x - 16) / boxSize; // �ȼ� ��ǥ���� ���� ��ġ�� ���� �� �������� ������ �ָ� �� 
	index.y = (coord.y - 4) / boxSize;
}

bool CData::GetCoord(Position p) // ���콺 �����Ͱ� ������ ������ �˻� 
{
	for(auto& it : pixelCoords) // C++11 �̻󿡼� ��밡�� 
	{
		if(it.isCollidePoint(p)) // Position ����ü�� �����Ǿ� ����. 
		{
			coord = it;
			return true;
		}
	}
	return false;
}

void CData::SetCoords() //�� ������ 32�̰�, ���� ũ��� 30�̹Ƿ� + 1�� �ؼ� �����ؾ� ��. 
{
	pCoords->push_back(Position(coord.x + 1, coord.y + 1));
}

bool CData::isOccupied(Position p, short mode)
{
	if(!GetCoord(p)) return true; // ���� ���̸� ���� ���� �� �����Ƿ� ���� �ִ� �Ͱ� ���������� true�� ��ȯ 
	GetBoardIndex(); // ������ ���̸� ������ ��ǥ�� ã�´�. 
	if(!board[index.y][index.x] && mode == RENJU && turn == BlackStone)
	{
		return pRule->ForbiddenPoint(index.x, index.y, turn, true);
	}
	return board[index.y][index.x]; // ���尡 �� ������ 1 �̻����� true, ������� 0�̹Ƿ� false ��ȯ 
}

void CData::ResetRedo()
{
	if(!redo.empty()) redo.clear();
}

void CData::CheckForbidden()
{
	pRule->GetForbiddenPoint(forbidden, turn);
	for(auto& p : forbidden)
	{
		p.x = p.x * boxSize + 16 + 1;
		p.y = p.y * boxSize + 4 - 1;
	}
	pDraw->DrawForbidden(forbidden);
}

void CData::DrawStone(short stone, short mode, bool checkGame) // �ٵ��ǿ� ���� �׸���. 
{
	GetBoardIndex(); // �ٵ��ǿ� ���� �۸� ���� �׻� ���忡�� ǥ�ø� ������� 
	SetBoard(stone);
	pDraw->DrawStone();
	turn = 3 - turn; // ���� �ٲ��ְ� 
	if(mode && turn == BlackStone) CheckForbidden();
	pDraw->UpdateBoard(); // ȭ���� ����(ȭ�鿡 �ݿ�)���ش�. 
	if(checkGame)CheckGameOver();
}

void CData::Undo(short mode)
{
	if(pCoords->empty()) return;
	
	redo.push_back(coord = pCoords->back()); // coords���� redo�� ��ǥ������ �̵����ش�. 
	pCoords->pop_back(); // ���Ϳ����� �������� �а� ������ �Լ��� ���� ������� ���Ÿ� ���ؼ��� �ݵ�� �� �۾��� ����� �� 
	DrawStone(Empty, mode, false); // Undo �� ���� �ٵ��ǿ��� ���� �ϳ� �������Ƿ� ������� �ٽ� �׷���� �� 
}

void CData::UndoAll()
{
	if(pCoords->empty()) return;
	
	while(!pCoords->empty())
	{
		redo.push_back(pCoords->back()); // ���� ��ǥ������ redo�� ���� �ű�� 
		pCoords->pop_back();
	}
	ClearBoard();
}

void CData::Redo(short mode)
{
	if(redo.empty()) return;
	
	pCoords->push_back(coord = redo.back());
	redo.pop_back();
	DrawStone(turn, mode, false);
}

void CData::RedoAll(short mode)
{
	if(redo.empty()) return;
	
	while(redo.size() > 1)
	{
		pCoords->push_back(coord = redo.back());
		redo.pop_back();
		GetBoardIndex(); // �ٵ��ǿ� ���� �۸� ���� �׻� ���忡�� ǥ�ø� ������� 
		SetBoard(turn);
		turn = 3 - turn;
	}
	Redo(mode); // ������ ���� �׸� ���� ȭ�鿡 ��ü�� �׷���� �ϹǷ�  
}

void CData::CheckGameOver() // ������ ��������(�ºΰ� ������ ������) �˻��ϴ� �Լ� 
{
	if(!isGameOver && pRule->isGameOver(index.x, index.y, 3 - turn))
	{
		isGameOver = true;
		pDraw->ShowEndMsg(3 - turn);
	}
}

bool CData::GetGameState()
{
	return isGameOver;
}
