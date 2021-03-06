#ifndef __DATA_H__
#define __DATA_H__

#include "Draw.h"
#include "Rule.h"

enum { GOMOKU, RENJU };

class CData{
	private:
		short board[boardLine][boardLine]; // 바둑판의 상태를 저장하기 위한 배열 
		//short (*pBoard)[boardLine]; // 2차원 배열을 넘겨주기 위한 배열포인터 
		short turn; // 현재 돌 
		bool  isGameOver;
		
		Position coord; // 현재 돌의 좌표 
		Position index; // 현재 돌의 2차원 배열인 board 안의 좌표 
		
		vector<Position> pixelCoords; // 바둑판 전체의 칸마다의 픽셀 좌표 (마우스 클릭시 위치를 찾기 위함) 
		vector<Position> redo; // Undo를 할 때 Redo를 하기 위하여 필요한 공간 
		vector<Position> *pCoords; // 두어진 돌의 좌표를 저장할 공간(CDraw class에서 주소를 받아 공유함) 
		vector<Position> forbidden;
		
		CDraw *pDraw;
		CRule *pRule;
		
	public:
		CData(CDraw *draw, CRule *pRule);
		~CData();
		
		void InitGame();
		void Undo(short mode);
		void UndoAll();
		void Redo(short mode);
		void RedoAll(short mode);
		void ResetRedo(); //Undo를 했더라도 새로운 돌이 놓이면 Redo를 할 수 없도록 Reset이 필요 
		void SetCoords(); // 돌이 놓인 좌표를 저장 
		void DrawStone(short stone, short mode, bool checkGame = true); // 돌이 놓일 좌표를 찾아서 그릴수 있도록 Darw class에 전달함 
		void CheckForbidden();
		bool isOccupied(Position p, short mode); // 착수 가능한 공간인지 확인 
		bool GetGameState();
		short *GetCurrentStone(); // Omok class와 공유하기 위해 포인터를 넘겨 줌 
		
	private :
		void InitBoard(); // 새로운 게임이 시작되면 초기화가 필요한 변수들을 초기화 해줌 
		void ClearBoard();
		void SetPixelCoords(); // 프로그램이 시작되면 모든 위치의 사각 영역을 저장해둠 
		void GetBoardIndex(); 
		void SetBoard(short stone); // board배열에 착수한 돌을 표시 
		void CheckGameOver();
		bool GetCoord(Position p); // 마우스 포인트가 눌렸다 떼면 보드의 영역인지 검사함 
};

#endif
