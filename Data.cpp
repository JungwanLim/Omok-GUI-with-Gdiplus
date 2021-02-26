#include "Data.h"

CData::CData(CDraw *pDraw) : pDraw(pDraw)
{
	SetPixelCoords();
	this->pCoords = pDraw->GetCoords();
	pBoard = board;
	InitGame();
}

CData::~CData()
{
}

void CData::InitGame()
{
	InitBoard();
	pCoords->clear();
	redo.clear();
	turn = BlackStone;
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

Position CData::GetIndex()
{
	return index;
}

short (*CData::GetBoard())[boardLine] // �迭 �����͸� �ѱ�� ���� �Լ� 
{
	return pBoard;
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

bool CData::isOccupied(Position p)
{
	if(!GetCoord(p)) return true; // ���� ���̸� ���� ���� �� �����Ƿ� ���� �ִ� �Ͱ� ���������� true�� ��ȯ 
	GetBoardIndex(); // ������ ���̸� ������ ��ǥ�� ã�´�. 
	return board[index.y][index.x]; // ���尡 �� ������ 1 �̻����� true, ������� 0�̹Ƿ� false ��ȯ 
}

void CData::ResetRedo()
{
	if(!redo.empty()) redo.clear();
}

void CData::DrawStone(short stone, bool isAll) // �ٵ��ǿ� ���� �׸���. 
{
	GetBoardIndex(); // �ٵ��ǿ� ���� �۸� ���� �׻� ���忡�� ǥ�ø� ������� 
	SetBoard(stone);
	pDraw->DrawStone(isAll);
	turn = 3 - turn; // ���� �ٲ��ְ� 
	pDraw->UpdateBoard(); // ȭ���� ����(ȭ�鿡 �ݿ�)���ش�. 
}

void CData::Undo()
{
	if(pCoords->empty()) return;
	
	Position p = coord = pCoords->back(); // coords���� redo�� ��ǥ������ �̵����ش�. 
	pCoords->pop_back(); // ���Ϳ����� �������� �а� ������ �Լ��� ���� ������� ���Ÿ� ���ؼ��� �ݵ�� �� �۾��� ����� �� 
	redo.push_back(p);
	pDraw->DrawBoard();
	DrawStone(Empty, DRAWALL); // Undo �� ���� �ٵ��ǿ��� ���� �ϳ� �������Ƿ� ������� �ٽ� �׷���� �� 
}

void CData::UndoAll()
{
	if(pCoords->empty()) return;
	
	while(!pCoords->empty())
	{
		redo.push_back(pCoords->back()); // ���� ��ǥ������ redo�� ���� �ű�� 
		pCoords->pop_back();
	}
	
	turn = BlackStone;
	InitBoard();
	pDraw->DrawBoard();
	pDraw->UpdateBoard(); // �ʿ��� ������ �ʱ� ������ �ٲ� ���常 �׷��ش�. 
}

void CData::Redo()
{
	if(redo.empty()) return;
	
	Position p = coord = redo.back();
	redo.pop_back();
	pCoords->push_back(p);
	DrawStone(turn);
}

void CData::RedoAll()
{
	if(redo.empty()) return;
	
	while(!redo.empty())
	{
		Position p = coord = redo.back();
		pCoords->push_back(p);
		redo.pop_back();
		DrawStone(turn);
	}
}

