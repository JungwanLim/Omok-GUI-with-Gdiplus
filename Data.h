#ifndef __DATA_H__
#define __DATA_H__

#include "Draw.h"
#include "Rule.h"

enum { GOMOKU, RENJU };

class CData{
	private:
		short board[boardLine][boardLine]; // �ٵ����� ���¸� �����ϱ� ���� �迭 
		//short (*pBoard)[boardLine]; // 2���� �迭�� �Ѱ��ֱ� ���� �迭������ 
		short turn; // ���� �� 
		bool  isGameOver;
		
		Position coord; // ���� ���� ��ǥ 
		Position index; // ���� ���� 2���� �迭�� board ���� ��ǥ 
		
		vector<Position> pixelCoords; // �ٵ��� ��ü�� ĭ������ �ȼ� ��ǥ (���콺 Ŭ���� ��ġ�� ã�� ����) 
		vector<Position> redo; // Undo�� �� �� Redo�� �ϱ� ���Ͽ� �ʿ��� ���� 
		vector<Position> *pCoords; // �ξ��� ���� ��ǥ�� ������ ����(CDraw class���� �ּҸ� �޾� ������) 
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
		void ResetRedo(); //Undo�� �ߴ��� ���ο� ���� ���̸� Redo�� �� �� ������ Reset�� �ʿ� 
		void SetCoords(); // ���� ���� ��ǥ�� ���� 
		void DrawStone(short stone, short mode, bool checkGame = true); // ���� ���� ��ǥ�� ã�Ƽ� �׸��� �ֵ��� Darw class�� ������ 
		void CheckForbidden();
		bool isOccupied(Position p, short mode); // ���� ������ �������� Ȯ�� 
		bool GetGameState();
		short *GetCurrentStone(); // Omok class�� �����ϱ� ���� �����͸� �Ѱ� �� 
		
	private :
		void InitBoard(); // ���ο� ������ ���۵Ǹ� �ʱ�ȭ�� �ʿ��� �������� �ʱ�ȭ ���� 
		void ClearBoard();
		void SetPixelCoords(); // ���α׷��� ���۵Ǹ� ��� ��ġ�� �簢 ������ �����ص� 
		void GetBoardIndex(); 
		void SetBoard(short stone); // board�迭�� ������ ���� ǥ�� 
		void CheckGameOver();
		bool GetCoord(Position p); // ���콺 ����Ʈ�� ���ȴ� ���� ������ �������� �˻��� 
};

#endif
