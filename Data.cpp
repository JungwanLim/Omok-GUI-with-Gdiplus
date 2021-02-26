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

void CData::GetBoardIndex()
{
	index.x = (Coord.x - 16) / boxSize;
	index.y = (Coord.y - 4) / boxSize;
/*	
	char temp[256];
	sprintf(temp, "x = %d, y = %d", index.x, index.y);
	MessageBox(nullptr, temp, "index test", MB_OK);
*/
}

void CData::SetCoords()
{
	pCoords->push_back(Position(Coord.x + 1, Coord.y + 1));
}

bool CData::isOccupied(Position p)
{
	if(!GetCoord(p)) return true;
	GetBoardIndex();
	return board[index.y][index.x];
}

