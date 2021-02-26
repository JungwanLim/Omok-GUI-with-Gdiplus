#ifndef __DATA_H__
#define __DATA_H__

#include "Draw.h"

#define boardLine 15
#define stoneSize 30
#define boxSize 32
#define boardSize 500

class CData{
	private:
		short board[boardLine][boardLine];
		Position Coord;
		Position index;
		
		vector<Position> pixelCoords;
		vector<Position> redo;
		vector<Position> *pCoords;
		
		CDraw *pDraw;
		
	public:
		CData(CDraw *draw);
		~CData();
		
		void InitBoard();
		void SetPixelCoords();
		void Undo();
		void UndoAll();
		void Redo();
		void RedoAll();
		void SetBoard(short stone);
		void SetCoords();

		bool isOccupied(Position p);
		bool GetCoord(Position p);
		void GetBoardIndex();
};

#endif
