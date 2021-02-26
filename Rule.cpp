#include "Rule.h"

CRule::CRule(CData *pData) : pData(pData)
{
	pBoard = pData->GetBoard();
}

CRule::~CRule()
{
}

bool CRule::isInvalid(short x, short y)
{
	return (x < 0 || x >= boardLine || y < 0 || y >= boardLine);
}

bool CRule::isGameOver(short x, short y, short stone)
{
	for(int i = 0; i < 4; ++i)
	{
		if(5 <= GetStoneCount(x, y, stone, i)) return true;
	}
	return false;
}

short CRule::GetStoneCount(short x, short y, short stone, short direction)
{
	short x1 = x, y1 = y;
	short cnt = 1;
	
	for(short i = 0; i < 2; ++i)
	{
		Position p = GetXY(direction * 2 + i);
		x = x1, y = y1;
		while(true)
		{
			x += p.x, y += p.y;
			if(isInvalid(x, y) || pBoard[y][x] != stone) break;
			else ++cnt;
		}
	}
	return cnt;
}

Position CRule::GetXY(short direction)
{
	short arrDx[] = {-1, 1, -1, 1, 0, 0, 1, -1};
	short arrDy[] = {0, 0, -1, 1, -1, 1, -1, 1};
	
	return Position(arrDx[direction], arrDy[direction]);
}
