#include "Draw.h"

CDraw::CDraw()
{
	pBoard = Image::FromFile(L".\\Image\\board.png");
	pBlack = Image::FromFile(L".\\Image\\Black.png");
	pWhite = Image::FromFile(L".\\Image\\White.png");
	pForbidden = Image::FromFile(L".\\Image\\forbidden.png");
	pBlack_a = Image::FromFile(L".\\Image\\Black_a.png");
	pWhite_a = Image::FromFile(L".\\Image\\White_a.png");
}

CDraw::~CDraw()
{
	delete pBoard;
	delete pBlack;
	delete pWhite;
	delete pForbidden;
	delete pBlack_a;
	delete pWhite_a;
}

bool CDraw::InitGdiplus()
{
	g_gps = CGdiPlusStarter();
	if (g_gps.m_bSuccess == FALSE) {
		MessageBox(NULL,TEXT("GDI+ 라이브러리를 초기화할 수 없습니다."),
			TEXT("알림"),MB_OK);
		return false;
	}
	return true;
}

void CDraw::DrawBoard()
{
	
}

void CDraw::DrawStone(int x, int y, int type)
{
}

void CDraw::OnPaint(HDC hdc)
{
	Graphics G(hdc);

	G.SetInterpolationMode(InterpolationModeHighQualityBilinear);
	G.DrawImage(pBoard,0,0);
	G.DrawImage(pBlack,49 - 32,35, 30, 30);
	G.DrawImage(pWhite,49,67, 30, 30);
	G.DrawImage(pForbidden,49,99);
	G.DrawImage(pWhite,49 + 32 * 10,131 + 32 * 10, 30, 30);
	G.DrawImage(pWhite,81,99, 30, 30);
	G.DrawImage(pBlack,17,99 + 32 * 11, 30, 30);
	G.DrawImage(pForbidden,49 + 32*5 ,99);
	G.DrawImage(pBlack_a,49 + 64 + 32*5 ,99);
}
