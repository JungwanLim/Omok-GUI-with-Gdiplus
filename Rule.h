#ifndef __RULE_H__
#define __RULE_H__

#include "Draw.h"

class CRule{
	private :
		short (*pBoard)[boardLine]; //Data class의 board와 공유함 
		Position pos;
		
		CDraw *pDraw;
		
	public :
		CRule(CDraw *pDraw);
		~CRule();
		
		void SetStone(short x, short y, short stone);
		void SetBoard(short (*pBoard)[boardLine]);
		bool isInvalid(short x, short y); 
		bool isGameOver(short x, short y, short stone);
		bool isSix(short x, short y, short stone, bool isShowMsg = false);
		bool isFive(short x, short y, short stone);
		bool isFive(short x, short y, short stone, short direction);
		bool isOpenThree(short x, short y, short stone, short direction);
		bool isFour(short x, short y, short stone, short direction);
		bool isDoubleThree(short x, short y, short stone, bool isShowMsg = false);
		bool isDoubleFour(short x, short y, short stone, bool isShowMsg = false);
		bool ForbiddenPoint(short x, short y, short stone, bool isShowMsg = false);
		
		short isOpenFour(short x, short y, short stone, short direction, bool isCheck = false);
		short GetStoneCount(short x, short y, short stone, short direction);

		Position GetXY(short direction);
		Position *FindEmptyPoint(short x, short y, short stone, short direction);
		void GetForbiddenPoint(vector<Position> &forbiddenPoints, short stone);
};

#endif
