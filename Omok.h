#ifndef __OMOK_H__
#define __OMOK_H__

#include "Rule.h"

class COmok{ // main에서 명령이 떨어지면 이 class로 전달이 되고, 다시 필요한 객체를 호출하여 명령을 수행하기 위한 class 
	private:
		bool isGameOver; // 게임이 끝났는지 여부를 저장하는 변수 
		short *pTurn; // 현재 돌의 색 
		
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
