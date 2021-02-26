#ifndef __DRAW_H__
#define __DRAW_H__

#include <windows.h>
#include <commctrl.h>
#include <gdiplus.h>
#include <iostream>
#include <vector>
#include "resource.h"

#pragma comment(lib,"comctl32")
#pragma comment(lib,"gdiplus")
#pragma warning(disable : 4996)

#define boardLine 15
#define stoneSize 30
#define boxSize 32
#define boardSize 500

using namespace Gdiplus;
using namespace std;

enum{ Empty, BlackStone, WhiteStone};

struct Position{
	int x, y;

	Position() {}
	Position(short x, short y):x(x), y(y) {}
	bool isCollidePoint(const Position &p) // ���̽��� Collidepoint�� �䳻 ����. ���콺 �����Ͱ� �簢 ������ �ִ��� �˻� 
	{
		return (x <= p.x && x + boxSize > p.x && y <= p.y && y + boxSize > p.y);
	}
};

class CDraw{
	private :
		bool isShowNumber; // ���� ��ȣ�� ǥ������ ���θ� �����ϴ� ���� 
		HWND hwndDlg; // Main Dialog�� HWND 
		
		Image *pBoard; // ����(������) �̹��� 
		Image *pBlack; // �� �� �̹��� 
		Image *pWhite; // �� �� �̹��� 
		Image *pForbidden; // �ݼ�ǥ�� �̹��� 
		Image *pBlack_a; // üũ�� �� �� 
		Image *pWhite_a; // üũ�� �� �� 
		Image *pImages[5]; // �̹������� ������ �迭(if�� ���� �ʰ� �׸��� ����) 

		Bitmap *pBit; // ���� ���۸��� ���� ������ 
		Graphics *memG;
		Graphics *pGraphic;
		CachedBitmap *pCBit;
		
		vector<Position> coords; // ������ ���� ��ǥ�� �����ϴ� ���� 
		
	public :
		CDraw(HWND hwndDlg);
		~CDraw();
		
		void DrawStone(); // ���� �׸��� �Լ� 
		void DrawBoard(); // ���带 �׸��� �ϼ� 
		void DrawForbidden(vector<Position> &forbiddenPoints);
		void ShowNumber(); // ��ȣ�� �־��ִ� �Լ� 
		void OnPaint(HDC hdc); // WM_PAINT �̺�Ʈ�� �߻��ϸ� ȣ�� ��(ȭ�� ����) 
		void SetGraphics(); //Graphics ���� ����(���� ���۸��� ����)���� �ʱ�ȭ 
		void UpdateBoard(); // ȭ���� ���� ���ֱ����� ���� 
		void SetShowNumber(); //�޴����� ������ �Ǹ� ���� ���� 
		void ShowEndMsg(short stone);
		void ShowMsg(const char *msg);
		void SetTitle(const char* titleName);
		void SetTitle(int id);
		
		vector<Position>* GetCoords() { return &coords; } // Data class�� �ּҸ� �Ѱ��� 
		RectF GetStringInfo(wchar_t *wStr, Position p, int size, int num); //��ȣ�� �ֱ� ���� �Լ� 
};
#endif
