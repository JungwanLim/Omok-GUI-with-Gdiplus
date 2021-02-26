#include "Data.h"

CData::CData(CDraw *pdraw)
{
	InitBoard();
	SetPixelCoords();
	this->pDraw = pdraw;
	this->pCoords = pDraw->GetCoords();
}

CData::~CData()
{
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

void CData::SetBoard(short stone)
{
	board[index.y][index.x] = stone;
}

bool CData::GetCoord(Position p)
{
	for(auto& it : pixelCoords)
	{
		if(p.x >= it.x && p.y >= it.y && p.x < it.x + boxSize && p.y < it.y + boxSize)
		{
			Coord = it;
			return true;
		}
	}
	return false;
}

Position CData::GetBoardIndex(Position p)
{
	Position pos;
	pos.x = (p.x - 16) / 32;
	pos.y = (p.y - 4) / 32;
	return pos;
}

void CData::SetCoords(short stone)
{
	pCoords->push_back(Position(Coord.x + 1, Coord.y + 1));
}

bool CData::isOccupied(Position p)
{
	if(GetCoord(p)) return false;
	index = GetBoardIndex(Coord);
	return board[index.y][index.x];
}

