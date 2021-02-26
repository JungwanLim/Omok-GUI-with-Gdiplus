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
	bool isCollidePoint(const Position &p) // 파이썬의 Collidepoint를 흉내 내봄. 마우스 포인터가 사각 영역에 있는지 검사 
	{
		return (x <= p.x && x + boxSize > p.x && y <= p.y && y + boxSize > p.y);
	}
};

class CDraw{
	private :
		bool isShowNumber; // 돌에 번호를 표시할지 여부를 결정하는 변수 
		HWND hwndDlg; // Main Dialog의 HWND 
		
		Image *pBoard; // 보드(오목판) 이미지 
		Image *pBlack; // 흑 돌 이미지 
		Image *pWhite; // 흰 돌 이미지 
		Image *pForbidden; // 금수표시 이미지 
		Image *pBlack_a; // 체크된 흑 돌 
		Image *pWhite_a; // 체크된 흰 돌 
		Image *pImages[5]; // 이미지들의 포인터 배열(if를 쓰지 않고 그리기 위함) 

		Bitmap *pBit; // 더블 버퍼링에 사룡될 변수들 
		Graphics *memG;
		Graphics *pGraphic;
		CachedBitmap *pCBit;
		
		vector<Position> coords; // 착수한 돌의 좌표를 저장하는 변수 
		
	public :
		CDraw(HWND hwndDlg);
		~CDraw();
		
		void DrawStone(); // 돌을 그리는 함수 
		void DrawBoard(); // 보드를 그리는 하수 
		void DrawForbidden(vector<Position> &forbiddenPoints);
		void ShowNumber(); // 번호를 넣어주는 함수 
		void OnPaint(HDC hdc); // WM_PAINT 이벤트가 발생하면 호출 됨(화면 갱신) 
		void SetGraphics(); //Graphics 관련 변수(더블 버퍼링을 위한)들을 초기화 
		void UpdateBoard(); // 화면을 갱신 해주기위한 변수 
		void SetShowNumber(); //메뉴에서 선택이 되면 변수 변경 
		void ShowEndMsg(short stone);
		void ShowMsg(const char *msg);
		void SetTitle(const char* titleName);
		void SetTitle(int id);
		
		vector<Position>* GetCoords() { return &coords; } // Data class에 주소를 넘겨줌 
		RectF GetStringInfo(wchar_t *wStr, Position p, int size, int num); //번호를 넣기 위한 함수 
};
#endif
