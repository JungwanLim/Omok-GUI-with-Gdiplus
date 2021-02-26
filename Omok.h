#ifndef __OMOK_H__
#define __OMOK_H__

#include "Rule.h"

class COmok{ // main���� ����� �������� �� class�� ������ �ǰ�, �ٽ� �ʿ��� ��ü�� ȣ���Ͽ� ����� �����ϱ� ���� class 
	private:
		bool isGameOver; // ������ �������� ���θ� �����ϴ� ���� 
		short *pTurn; // ���� ���� �� 
		
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
