#ifndef __DATA_H__
#define __DATA_H__

#include "Draw.h"

enum{ Empty, BlackStone, WhiteStone};

class CData{
	private:
		short board[boardLine][boardLine]; // �ٵ����� ���¸� �����ϱ� ���� �迭 
		short (*pBoard)[boardLine]; // 2���� �迭�� �Ѱ��ֱ� ���� �迭������ 
		short turn; // ���� �� 
		
		Position coord; // ���� ���� ��ǥ 
		Position index; // ���� ���� 2���� �迭�� board ���� ��ǥ 
		
		vector<Position> pixelCoords; // �ٵ��� ��ü�� ĭ������ �ȼ� ��ǥ (���콺 Ŭ���� ��ġ�� ã�� ����) 
		vector<Position> redo; // Undo�� �� �� Redo�� �ϱ� ���Ͽ� �ʿ��� ���� 
		vector<Position> *pCoords; // �ξ��� ���� ��ǥ�� ������ ����(CDraw class���� �ּҸ� �޾� ������) 
		
		CDraw *pDraw;
		
	public:
		CData(CDraw *draw);
		~CData();
		
		void InitGame();
		void Undo();
		void UndoAll();
		void Redo();
		void RedoAll();
		void ResetRedo(); //Undo�� �ߴ��� ���ο� ���� ���̸� Redo�� �� �� ������ Reset�� �ʿ� 
		void SetBoard(short stone); // board�迭�� ������ ���� ǥ�� 
		void SetCoords(); // ���� ���� ��ǥ�� ���� 
		void DrawStone(short stone, bool isAll = false); // ���� ���� ��ǥ�� ã�Ƽ� �׸��� �ֵ��� Darw class�� ������ 
		bool isOccupied(Position p); // ���� ������ �������� Ȯ�� 
		short (*GetBoard())[boardLine]; // ������ �迭�� board�� �迭 �����͸� �Ѱ��ִ� �Լ�(�Լ��� ������) 
		short *GetCurrentStone(); // Omok class�� �����ϱ� ���� �����͸� �Ѱ� �� 
		Position GetIndex(); // board�迭�� in�� �Ѱ���
		
	private :
		void InitBoard(); // ���ο� ������ ���۵Ǹ� �ʱ�ȭ�� �ʿ��� �������� �ʱ�ȭ ���� 
		void SetPixelCoords(); // ���α׷��� ���۵Ǹ� ��� ��ġ�� �簢 ������ �����ص� 
		void GetBoardIndex(); 
		bool GetCoord(Position p); // ���콺 ����Ʈ�� ���ȴ� ���� ������ �������� �˻��� 
};

#endif
