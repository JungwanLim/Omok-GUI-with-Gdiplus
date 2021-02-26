#include "Rule.h"

CRule::CRule(CDraw *pDraw) : pDraw(pDraw)
{
}

CRule::~CRule()
{
}

void CRule::SetBoard(short (*pBoard)[boardLine])
{
	this->pBoard = pBoard;
}

void CRule::SetStone(short x, short y, short stone)
{
	pBoard[y][x] = stone;
}

bool CRule::isInvalid(short x, short y) // 보드의 유효한 영역인지를 체크 
{
	return (x < 0 || x >= boardLine || y < 0 || y >= boardLine);
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

Position *CRule::FindEmptyPoint(short x, short y, short stone, short direction)// 주어진 방향에 공백이 있는지 찾아봅니다. 
{
	pos = GetXY(direction); // pos는 멤버 변수. 주소를 넘겨주기 위해 멤버 변수 사용 
	while(true)
	{
		x = x + pos.x, y = y + pos.y; // 주어진 방향(0, 1 또는 -1)으로 한 칸씩 진행
		if(isInvalid(x, y) || pBoard[y][x] != stone) break; // 같은 돌이 아닐 경우(공백 또는 벽 또는 상대 돌) 
	}
	if(!isInvalid(x, y) && pBoard[y][x] == Empty) // 보드 영역 안이며 공백일 때만 
	{
		pos = Position(x, y);
		return &pos; // 공백을 찾지 못했을 경우 nullptr를 넘겨주기 위해서 주소를 사용 
	}
	return nullptr; // 공백이 없을 경우 nullptr 리턴 
}

bool CRule::isGameOver(short x, short y, short stone) // 연속으로 5개 이상의 돌이 놓여 있으면 참을 리턴해줌 
{
	for(int i = 0; i < 4; ++i)
	{
		if(5 <= GetStoneCount(x, y, stone, i)) return true; // 렌주룰일 경우 흑은 장목을 둘 수 없으므로 이 함수 하나로 흑 백 모두 승부를 판정 할 수 있음 
	}
	return false;
}

bool CRule::isSix(short x, short y, short stone, bool isShowMsg) 
{
	for(int i = 0; i < 4; ++i)
	{
		if (5 < GetStoneCount(x, y, stone, i)) 
		{
			if(isShowMsg)pDraw->ShowMsg("Over Line");//// 금수 자리에 마우스를 클릭했을 때만 메시지 출력
			return true;
		}
	}
	return false;
}

bool CRule::isFive(short x, short y, short stone)
{
	for(int i = 0; i < 4; ++i)
	{
		if (5 == GetStoneCount(x, y, stone, i)) return true;
	}
	return false;
}

bool CRule::isFive(short x, short y, short stone, short direction) // 주어진 방향으로 5가 되는지 검사  
{
	return (5 == GetStoneCount(x, y, stone, direction));
}

bool CRule::isOpenThree(short x, short y, short stone, short direction)
{
	Position *pPos, p;
	for(int i = 0; i < 2; ++i)
	{
		pPos = FindEmptyPoint(x, y, stone, direction * 2 + i);
		if(pPos)
		{
			p = *pPos;
			SetStone(p.x, p.y, stone);
			if(1 == isOpenFour(p.x, p.y, stone, direction, true))
			{
				if(!ForbiddenPoint(p.x, p.y, stone))
				{
					SetStone(p.x, p.y, Empty);
					return true;
				}
			}
			SetStone(p.x, p.y, Empty);
		}
	}
	return false;
}

short CRule::isOpenFour(short x, short y, short stone, short direction, bool isCHeck)
{
	if(isCHeck && isFive(x, y, stone)) return false;
	
	Position *p;
	int cnt = 0;
	for(int i = 0; i < 2; ++i)
	{
		p = FindEmptyPoint(x, y, stone, direction * 2 + i);
		if(p && isFive(p->x, p->y, stone, direction)) ++cnt;
	}
	if(cnt == 2) 
	{
		if(4 == GetStoneCount(x, y, stone, direction)) --cnt;
	}
	else cnt = 0;
	
	return cnt;
}

bool CRule::isFour(short x, short y, short stone, short direction)
{
	Position *p;
	for(int i = 0; i < 2; ++i)
	{
		p = FindEmptyPoint(x, y, stone, direction * 2 + i);
		if(p && isFive(p->x, p->y, stone, direction)) return true;
	}
	return false;
}

bool CRule::isDoubleThree(short x, short y, short stone, bool isShowMsg)
{
	int cnt = 0;
	SetStone(x, y, stone);
	for(int i = 0; i < 4; ++i)
	{
		if (isOpenThree(x, y, stone, i)) ++cnt;
	}
	SetStone(x, y, Empty);

	if(isShowMsg && cnt >= 2)pDraw->ShowMsg("Double Three");
	return cnt >= 2;
}

bool CRule::isDoubleFour(short x, short y, short stone, bool isShowMsg)
{
	int cnt = 0;
	SetStone(x, y, stone);
	for(int i = 0; i < 4; ++i)
	{
		if (2 == isOpenFour(x, y, stone, i)) cnt += 2;
		else if(isFour(x, y, stone, i)) ++cnt;
	}
	SetStone(x, y, Empty);

	if(isShowMsg && cnt >= 2)pDraw->ShowMsg("Double Four");
	return cnt >= 2;
}

bool CRule::ForbiddenPoint(short x, short y, short stone, bool isShowMsg)
{
	if(isFive(x, y, stone)) return false;
	return (isSix(x, y, stone, isShowMsg) || isDoubleFour(x, y, stone, isShowMsg) || isDoubleThree(x, y, stone, isShowMsg));
}

void CRule::GetForbiddenPoint(vector<Position> &forbiddenPoints, short stone)
{
	for(int y = 0; y < boardLine; ++y)
	{
		for(int x = 0; x < boardLine; ++x)
		{
			if(pBoard[y][x]) continue;
			if(ForbiddenPoint(x, y, stone, false)) forbiddenPoints.push_back(Position(x, y));
		}
	}
}

