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

bool CRule::isInvalid(short x, short y) // ������ ��ȿ�� ���������� üũ 
{
	return (x < 0 || x >= boardLine || y < 0 || y >= boardLine);
}

Position CRule::GetXY(short direction) // ���� ���̺��� ���⿡ ���� ���� �Ѱ� �� 
{
	short arrDx[] = {-1, 1, -1, 1, 0, 0, 1, -1}; // x�� ����, -1�� ����, 1�� ������, 0�� ���ϸ� ������ ���� �� �ڸ�. �밢���� ������ ���� �� �찡 ���� 
	short arrDy[] = {0, 0, -1, 1, -1, 1, -1, 1}; // y�� ���� -1�� ����, 1�� �Ʒ���, 0�� �¿츦 ������ ��, �밢���� ������ ���� �� �ϰ� ����. 
	
	return Position(arrDx[direction], arrDy[direction]);
}

short CRule::GetStoneCount(short x, short y, short stone, short direction)//���� ���� ���� �밢���� ���ѿ� ���� ������ ī��Ʈ �� 
{
	short x1 = x, y1 = y; // ���� �߽����� ����(���� �����̶�� ���ʰ� ������)�� �˻��ؾ� �ϹǷ� ó�� ��ġ�� ����ϰ� �־�� �� 
	short cnt = 1; // ���� ���� ��ġ �ϳ� ���� ī���͸� ������ 
	
	for(short i = 0; i < 2; ++i) // ���� �߽����� ������ �˻�. 
	{
		Position p = GetXY(direction * 2 + i); // ���� ���ε� 4������ �˻��ϰ�, �� ����� ����(��, ��, �Ǵ� ��, ��)�� �˻��ϹǷ� �� ���⿡ 2������ �˻簡 �ʿ��ϹǷ� * 2���� 
		x = x1, y = y1;
		while(true)
		{
			x += p.x, y += p.y;
			if(isInvalid(x, y) || pBoard[y][x] != stone) break; //���� ���̰ų� ���� ���� �ƴϸ� ���� 
			else ++cnt;
		}
	}
	return cnt;
}

Position *CRule::FindEmptyPoint(short x, short y, short stone, short direction)// �־��� ���⿡ ������ �ִ��� ã�ƺ��ϴ�. 
{
	pos = GetXY(direction); // pos�� ��� ����. �ּҸ� �Ѱ��ֱ� ���� ��� ���� ��� 
	while(true)
	{
		x = x + pos.x, y = y + pos.y; // �־��� ����(0, 1 �Ǵ� -1)���� �� ĭ�� ����
		if(isInvalid(x, y) || pBoard[y][x] != stone) break; // ���� ���� �ƴ� ���(���� �Ǵ� �� �Ǵ� ��� ��) 
	}
	if(!isInvalid(x, y) && pBoard[y][x] == Empty) // ���� ���� ���̸� ������ ���� 
	{
		pos = Position(x, y);
		return &pos; // ������ ã�� ������ ��� nullptr�� �Ѱ��ֱ� ���ؼ� �ּҸ� ��� 
	}
	return nullptr; // ������ ���� ��� nullptr ���� 
}

bool CRule::isGameOver(short x, short y, short stone) // �������� 5�� �̻��� ���� ���� ������ ���� �������� 
{
	for(int i = 0; i < 4; ++i)
	{
		if(5 <= GetStoneCount(x, y, stone, i)) return true; // ���ַ��� ��� ���� ����� �� �� �����Ƿ� �� �Լ� �ϳ��� �� �� ��� �ºθ� ���� �� �� ���� 
	}
	return false;
}

bool CRule::isSix(short x, short y, short stone, bool isShowMsg) 
{
	for(int i = 0; i < 4; ++i)
	{
		if (5 < GetStoneCount(x, y, stone, i)) 
		{
			if(isShowMsg)pDraw->ShowMsg("Over Line");//// �ݼ� �ڸ��� ���콺�� Ŭ������ ���� �޽��� ���
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

bool CRule::isFive(short x, short y, short stone, short direction) // �־��� �������� 5�� �Ǵ��� �˻�  
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

