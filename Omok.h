#ifndef __OMOK_H__
#define __OMOK_H__

#include "Data.h"

enum{ Empty, BlackStone, WhiteStone};

class COmok{
	private:
		CData *pData;
		CDraw *pDraw;
		HWND hwndDlg;
		
	public:
		COmok(HWND hwndDlge, CDraw *pDraw);
		~COmok();
		
		void PutStone(Position p);
};

#endif
