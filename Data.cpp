#include "Data.h"

CData::CData(CDraw *pdraw)
{
	SetPixelCoords();
	this->pDraw = pdraw;
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
	stoneCount = 1;
	currentStone = BlackStone;
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

void CData::SetPixelCoords()
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

short CData::GetCurrentStone()
{
	return 3 - currentStone;
}

Position CData::GetIndex()
{
	return index;
}

short (*CData::GetBoard())[boardLine]
{
	return pBoard;
}

void CData::SetBoard(short stone)
{
	if(stone) stone = currentStone; 
	board[index.y][index.x] = stone;
}

void CData::GetBoardIndex()
{
	index.x = (coord.x - 16) / boxSize;
	index.y = (coord.y - 4) / boxSize;
}

bool CData::GetCoord(Position p)
{
	for(auto& it : pixelCoords)
	{
		if(p.x >= it.x && p.y >= it.y && p.x < it.x + boxSize && p.y < it.y + boxSize)
		{
			coord = it;
			return true;
		}
	}
	return false;
}

void CData::SetCoords()
{
	pCoords->push_back(Position(coord.x + 1, coord.y + 1));
}

bool CData::isOccupied(Position p)
{
	if(!GetCoord(p)) return true;
	GetBoardIndex();
	return board[index.y][index.x];
}

void CData::DrawStone(bool isNotRedo)
{
	pDraw->DrawStone();
	++stoneCount;
	currentStone = 3 - currentStone;
	if(isNotRedo) redo.clear();
}

void CData::Undo()
{
	if(pCoords->empty()) return;
	
	Position p = coord = pCoords->back();
	pCoords->pop_back();
	redo.push_back(p);
	--stoneCount;
	currentStone = 3 - currentStone;
	GetBoardIndex();
	SetBoard(Empty);
	
	pDraw->DrawBoard();
	pDraw->DrawStone(true);
}

void CData::UndoAll()
{
	if(pCoords->empty()) return;
	
	while(!pCoords->empty())
	{
		redo.push_back(pCoords->back());
		pCoords->pop_back();
	}
	
	stoneCount = 1;
	currentStone = BlackStone;
	InitBoard();
	
	pDraw->DrawBoard();
}

void CData::Redo()
{
	if(redo.empty()) return;
	
	Position p = coord = redo.back();
	redo.pop_back();
	pCoords->push_back(p);
	GetBoardIndex();
	SetBoard(currentStone);
	DrawStone(false);
}

void CData::RedoAll()
{
	if(redo.empty()) return;
	
	while(!redo.empty())
	{
		Position p = coord = redo.back();
		pCoords->push_back(p);
		redo.pop_back();
		GetBoardIndex();
		SetBoard(currentStone);
		DrawStone(false);
	}
}

