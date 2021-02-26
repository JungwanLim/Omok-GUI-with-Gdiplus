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
	pDraw->UpdateBoard(); // 필요한 변수들을 초기화 하고 보드를 그려 화면에 보여줌 
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

void CData::SetPixelCoords() //좌표들을 저장함 
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

short (*CData::GetBoard())[boardLine] // 배열 포인터를 넘기기 위한 함수 
{
	return pBoard;
}

void CData::SetBoard(short stone)
{
	board[index.y][index.x] = stone;
}

void CData::GetBoardIndex() // 픽셀 좌표를 board에서 사용될 일련 번호(index)로 바꿈 
{
	index.x = (coord.x - 16) / boxSize; // 픽셀 좌표에서 시작 위치를 빼고 줄 간격으로 나누어 주면 됨 
	index.y = (coord.y - 4) / boxSize;
}

bool CData::GetCoord(Position p) // 마우스 포인터가 오목판 위인지 검사 
{
	for(auto& it : pixelCoords) // C++11 이상에서 사용가능 
	{
		if(it.isCollidePoint(p)) // Position 구조체에 구현되어 있음. 
		{
			coord = it;
			return true;
		}
	}
	return false;
}

void CData::SetCoords() //줄 간격은 32이고, 돌의 크기는 30이므로 + 1씩 해서 저장해야 함. 
{
	pCoords->push_back(Position(coord.x + 1, coord.y + 1));
}

bool CData::isOccupied(Position p)
{
	if(!GetCoord(p)) return true; // 보드 밖이면 돌을 놓을 수 없으므로 돌이 있는 것과 마찬가지로 true를 반환 
	GetBoardIndex(); // 오목판 안이면 보드의 좌표를 찾는다. 
	return board[index.y][index.x]; // 보드가 차 있으면 1 이상으로 true, 비었으면 0이므로 false 반환 
}

void CData::ResetRedo()
{
	if(!redo.empty()) redo.clear();
}

void CData::DrawStone(short stone, bool isAll) // 바둑판에 돌을 그린다. 
{
	GetBoardIndex(); // 바둑판에 돌을 글릴 때는 항상 보드에도 표시를 해줘야함 
	SetBoard(stone);
	pDraw->DrawStone(isAll);
	turn = 3 - turn; // 돌을 바꿔주고 
	pDraw->UpdateBoard(); // 화면을 갱신(화면에 반영)해준다. 
}

void CData::Undo()
{
	if(pCoords->empty()) return;
	
	Position p = coord = pCoords->back(); // coords에서 redo로 좌표정보를 이동해준다. 
	pCoords->pop_back(); // 벡터에서는 데이터을 읽고 빼내는 함수가 따로 있으모로 제거를 위해서는 반드시 이 작업을 해줘야 함 
	redo.push_back(p);
	pDraw->DrawBoard();
	DrawStone(Empty, DRAWALL); // Undo 할 때는 바둑판에서 돌이 하나 없어지므로 보드부터 다시 그려줘야 함 
}

void CData::UndoAll()
{
	if(pCoords->empty()) return;
	
	while(!pCoords->empty())
	{
		redo.push_back(pCoords->back()); // 돌의 좌표정보를 redo로 전부 옮기고 
		pCoords->pop_back();
	}
	
	turn = BlackStone;
	InitBoard();
	pDraw->DrawBoard();
	pDraw->UpdateBoard(); // 필요한 변수를 초기 값으로 바꿔 보드만 그려준다. 
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

