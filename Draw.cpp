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

void CDraw::SetHwnd(HWND hwndDlg)
{
	this->hwndDlg = hwndDlg;
}

void CDraw::UpdateBoard()
{
	Graphics G(hwndDlg);
	Bitmap pBit(500, 500, &G);
	Graphics memG(&pBit);
	
	memG.DrawImage(pBoard,0,0);
	for(auto& p : coords)
	{
		memG.DrawImage(pBlack, p.x, p.y);
	}
	
	if (pCBit) 
	{
	  delete pCBit;
	  //MessageBox(hwndDlg, "Deleted", "Test", MB_OK);
	}
	pCBit=new CachedBitmap(&pBit,&G);
	InvalidateRect(hwndDlg,NULL,FALSE);
}

void CDraw::DrawBoard()
{
	pGraphic->DrawImage(pBoard,0,0);
}

void CDraw::DrawStone(short x, short y, short type)
{
	pGraphic->DrawImage(pBlack, x, y);
}

void CDraw::OnPaint(HDC hdc)
{
    Graphics G(hdc);
	if (pCBit == NULL) {
	  UpdateBoard();
	}
    G.DrawCachedBitmap(pCBit,0,0);
}
