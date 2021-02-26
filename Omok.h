#ifndef __OMOK_H__
#define __OMOK_H__

#include "Rule.h"

class COmok{
	private:
		bool isGameOver;
		
		CData *pData;
		CDraw *pDraw;
		CRule *pRule;
		HWND hwndDlg;
		
	public:
		COmok(HWND hwndDlge, CDraw *pDraw);
		~COmok();
		
		void PutStone(Position p);
		void CheckShowNumber(HMENU hMenu, UINT state);
		void InitGame();
		void Undo();
		void UndoAll();
		void Redo();
		void RedoAll();
		void ShowEndMsg();
		void CheckGameOver(); 
};

#endif
