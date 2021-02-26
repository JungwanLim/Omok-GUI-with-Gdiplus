#include "Rule.h"

CRule::CRule(CData *pData) : pData(pData)
{
	pBoard = pData->GetBoard();
}

CRule::~CRule()
{
}

bool CRule::isInvalid(short x, short y) // ������ ��ȿ�� ���������� üũ 
{
	return (x < 0 || x >= boardLine || y < 0 || y >= boardLine);
}

bool CRule::isGameOver(short x, short y, short stone) // �������� 5�� �̻��� ���� ���� ������ ���� �������� 
{
	for(int i = 0; i < 4; ++i)
	{
		if(5 <= GetStoneCount(x, y, stone, i)) return true;
	}
	return false;
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
