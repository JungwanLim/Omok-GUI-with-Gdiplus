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

class CGdiPlusStarter
{
private:
	ULONG_PTR m_gpToken;

public:
	bool m_bSuccess;
	CGdiPlusStarter() {
		GdiplusStartupInput gpsi;
		m_bSuccess=(GdiplusStartup(&m_gpToken,&gpsi,NULL) == Ok);
	}
	~CGdiPlusStarter() {
		GdiplusShutdown(m_gpToken);
	}
};

class CDraw{
	private :
		Image *pBoard;
		Image *pBlack;
		Image *pWhite;
		Image *pForbidden;
		Image *pBlack_a;	
		Image *pWhite_a;
		Image *pImages[5];

		CGdiPlusStarter g_gps;
		Graphics *pGraphic;
		CachedBitmap *pCBit;
		HWND hwndDlg;

		vector<Position> coords;
		
	public :
		CDraw();
		~CDraw();
		
		void DrawStone(short x, short y, short type);
		void DrawBoard();
		void OnPaint(HDC hdc);
		void SetHwnd(HWND hwndDlg);
		void UpdateBoard();
		bool InitGdiplus();
		
		vector<Position>* GetCoords() { return &coords; }
};
#endif
