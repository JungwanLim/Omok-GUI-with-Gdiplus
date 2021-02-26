#include "Draw.h"

CDraw::CDraw(HWND hwndDlg) : hwndDlg(hwndDlg)
{
	pBoard = Image::FromFile(L".\\Image\\board.png");
	pImages[0] = pBlack = Image::FromFile(L".\\Image\\Black.png");
	pImages[1] = pWhite = Image::FromFile(L".\\Image\\White.png");
	pImages[2] = pBlack_a = Image::FromFile(L".\\Image\\Black_a.png");
	pImages[3] = pWhite_a = Image::FromFile(L".\\Image\\White_a.png");
	pImages[4] = pForbidden = Image::FromFile(L".\\Image\\forbidden.png");
}

CDraw::~CDraw()
{
	delete pBoard;
	delete pBlack;
	delete pWhite;
	delete pForbidden;
	delete pBlack_a;
	delete pWhite_a;
	delete pBit;
	delete memG;
	delete pGraphic;
	if(pCBit){
		delete pCBit;
	}
}

bool CDraw::InitGdiplus()
{
	g_gps = CGdiPlusStarter();
	if (g_gps.m_bSuccess == FALSE) {
		MessageBox(NULL,TEXT("GDI+ 라이브러리를 초기화할 수 없습니다."),
			TEXT("알림"),MB_OK);
		SendMessage(hwndDlg, WM_CLOSE, 0, 0);
		return false;
	}
	SetGraphics();
	return true;
}

void CDraw::SetGraphics()
{
	pGraphic = new Graphics(hwndDlg);
	pBit = new Bitmap(500, 500, pGraphic);
	memG = new Graphics(pBit);
	DrawBoard();
	UpdateBoard();
}

void CDraw::UpdateBoard()
{
	int stone = 0;
	Position p;
	if(!coords.empty())
	{
		for(; stone < coords.size() - 1; ++stone)
		{
			p = coords[stone];
			memG->DrawImage(pImages[stone % 2], p.x, p.y);
		}
		p = coords[stone];
		memG->DrawImage(pImages[stone % 2 + 2], p.x, p.y);
		ShowNumber();
	}
	if (pCBit) 
	{
	  delete pCBit;
	}
	pCBit = new CachedBitmap(pBit,pGraphic);
	InvalidateRect(hwndDlg,NULL,FALSE);
}

void CDraw::DrawBoard()
{
	memG->DrawImage(pBoard,0,0);
}

void CDraw::DrawStone(short x, short y, short type)
{
	memG->DrawImage(pImages[type], x, y);
}

void CDraw::ShowNumber()
{

	Font F(L"Arial",13,FontStyleBold,UnitPixel);
	SolidBrush W(Color(0,0,0));
	SolidBrush B(Color(255,255,255));
	SolidBrush R(Color(255,0,0));
	SolidBrush *pB[] = {&B, &W}; 

    StringFormat SF;
    SF.SetAlignment(StringAlignmentCenter);

    wchar_t wNum[10];
	int i = 0;
    for(; i < coords.size(); ++i)
    {
        PointF P(coords[i].x + 15.0, coords[i].y + 7);
        swprintf(wNum, sizeof(wNum) / sizeof(wchar_t), L"%d", i + 1);
        if(i == coords.size() - 1)
        {
        	memG->DrawString(wNum,-1,&F,P,&SF,&R);
		}
		else
		{
	        memG->DrawString(wNum,-1,&F,P,&SF,pB[i%2]);
		}
    }
    
}

void CDraw::OnPaint(HDC hdc)
{
    Graphics G(hdc);
    G.DrawCachedBitmap(pCBit,0,0);
}
