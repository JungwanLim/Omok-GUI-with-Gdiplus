#ifndef __DATA_H__
#define __DATA_H__

#include "Draw.h"

#define boardLine 15
#define stoneSize 30
#define boxSize 32
#define boardSize 500

enum{ Empty, BlackStone, WhiteStone};

class CData{
	private:
		short board[boardLine][boardLine];
		short (*pBoard)[boardLine];
		short stoneCount;
		short currentStone;
		
		Position coord;
		Position index;
		
		vector<Position> pixelCoords;
		vector<Position> redo;
		vector<Position> *pCoords;
		
		CDraw *pDraw;
		
	public:
		CData(CDraw *draw);
		~CData();
		
		void InitGame();
		void Undo();
		void UndoAll();
		void Redo();
		void RedoAll();
		void SetBoard(short stone);
		void SetCoords();
		void DrawStone(bool isRedo = true);
		bool isOccupied(Position p);
		short (*GetBoard())[boardLine];
		short GetCurrentStone();
		Position GetIndex();
		
	private :
		void InitBoard();
		void SetPixelCoords();
		void GetBoardIndex();
		bool GetCoord(Position p);
};

#endif
