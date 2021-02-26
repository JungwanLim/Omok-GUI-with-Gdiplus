#ifndef __DRAW_H__
#define __DRAW_H__

#include <windows.h>
#include <commctrl.h>
#include <gdiplus.h>
#include <iostream>
#include "resource.h"

using namespace Gdiplus;

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

		CGdiPlusStarter g_gps;

	public :
		CDraw();
		~CDraw();
		
		void DrawStone(int x, int y, int type);
		void DrawBoard();
		void OnPaint(HDC hdc);
		bool InitGdiplus();
		
};
#endif
