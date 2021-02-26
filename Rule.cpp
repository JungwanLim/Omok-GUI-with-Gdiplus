#include "Rule.h"

CRule::CRule(CData *pData) : pData(pData)
{
	pBoard = pData->GetBoard();
}

CRule::~CRule()
{
}

bool CRule::isInvalid(short x, short y) // 보드의 유효한 영역인지를 체크 
{
	return (x < 0 || x >= boardLine || y < 0 || y >= boardLine);
}

bool CRule::isGameOver(short x, short y, short stone) // 연속으로 5개 이상의 돌이 놓여 있으면 참을 리턴해줌 
{
	for(int i = 0; i < 4; ++i)
	{
		if(5 <= GetStoneCount(x, y, stone, i)) return true;
	}
	return false;
}

Position CRule::GetXY(short direction) // 방향 테이블에서 방향에 대한 값을 넘겨 줌 
{
	short arrDx[] = {-1, 1, -1, 1, 0, 0, 1, -1}; // x의 방향, -1은 왼쪽, 1을 오른쪽, 0은 상하를 조사할 때는 제 자리. 대각선을 조사할 때도 좌 우가 있음 
	short arrDy[] = {0, 0, -1, 1, -1, 1, -1, 1}; // y의 방향 -1은 위쪽, 1은 아래쪽, 0은 좌우를 조사할 때, 대각선을 조사할 때도 상 하가 있음. 
	
	return Position(arrDx[direction], arrDy[direction]);
}

short CRule::GetStoneCount(short x, short y, short stone, short direction)//가로 세로 양쪽 대각선에 대한여 돌의 개수를 카운트 함 
{
	short x1 = x, y1 = y; // 돌을 중심으로 양쪽(가로 방향이라면 왼쪽과 오른쪽)을 검사해야 하므로 처음 위치를 기억하고 있어야 함 
	short cnt = 1; // 돌이 놓인 위치 하나 부터 카운터를 시작함 
	
	for(short i = 0; i < 2; ++i) // 돌을 중심으로 양쪽을 검사. 
	{
		Position p = GetXY(direction * 2 + i); // 가로 세로등 4방향을 검사하고, 한 방향당 양쪽(좌, 우, 또는 상, 하)을 검사하므로 한 방향에 2개씩의 검사가 필요하므로 * 2해줌 
		x = x1, y = y1;
		while(true)
		{
			x += p.x, y += p.y;
			if(isInvalid(x, y) || pBoard[y][x] != stone) break; //영역 밖이거나 같은 돌이 아니면 멈춤 
			else ++cnt;
		}
	}
	return cnt;
}
