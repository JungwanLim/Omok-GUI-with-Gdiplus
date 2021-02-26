#ifndef __OMOK_H__
#define __OMOK_H__

#include "Rule.h"
#include "Data.h"

class COmok{ // main���� ����� �������� �� class�� ������ �ǰ�, �ٽ� �ʿ��� ��ü�� ȣ���Ͽ� ����� �����ϱ� ���� class 
	private:
		bool isGameOver; // ������ �������� ���θ� �����ϴ� ���� 
		short mode; // Game Mode (Renju rule or Gomoku rule) 
		short *pTurn; // ���� ���� �� 
		
		CData *pData; 
		CDraw *pDraw;
		CRule *pRule;
		HWND hwndDlg;
		
	public:
		COmok(HWND hwndDlge, CDraw *pDraw);
		~COmok();
		
		void SetMode(short mode);
		void PutStone(Position p);
		void CheckShowNumber(HMENU hMenu, UINT state);
		void InitGame();
		void Undo();
		void UndoAll();
		void Redo();
		void RedoAll();
};

#endif
