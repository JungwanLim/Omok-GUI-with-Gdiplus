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

using namespace Gdiplus;
using namespace std;

struct Position{
	int x, y;

	Position() {}

	Position(short x, short y):x(x), y(y)
	{
	}

	bool operator ==(const Position &P) const 
	{
		return (x == P.x && y == P.y);
	}

	bool operator !=(const Position &P) const
	{
		return (x != P.x || y != P.y);
	}
};

class CDraw{
	private :
		bool isShowNumber;
		
		Image *pBoard;
		Image *pBlack;
		Image *pWhite;
		Image *pForbidden;
		Image *pBlack_a;	
		Image *pWhite_a;
		Image *pImages[5];

		Bitmap *pBit;
		Graphics *memG;
		Graphics *pGraphic;
		CachedBitmap *pCBit;
		HWND hwndDlg;

		vector<Position> coords;
		
	public :
		CDraw(HWND hwndDlg);
		~CDraw();
		
		void DrawStone(bool isAll = false);
		void DrawBoard();
		void ShowNumber(bool isAll = false);
		void OnPaint(HDC hdc);
		void SetGraphics();
		void UpdateBoard();
		void SetShowNumber(bool isShow);
		
		vector<Position>* GetCoords() { return &coords; }
};
#endif
