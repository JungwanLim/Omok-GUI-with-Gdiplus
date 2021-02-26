#ifndef __RULE_H__
#define __RULE_H__

#include "Data.h"

class CRule{
	private :
		CData *pData;
		short (*pBoard)[boardLine];
		
	public :
		CRule(CData *pData);
		~CRule();
		
		bool isInvalid(short x, short y);
		bool isGameOver(short x, short y, short stone);
		short GetStoneCount(short x, short y, short stone, short direction);

		Position GetXY(short direction);
};

#endif
