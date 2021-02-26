#include "Draw.h"

CDraw::CDraw(HWND hwndDlg) : hwndDlg(hwndDlg)
{
	pBoard = Image::FromFile(L".\\Image\\board.png");
	pImages[0] = pBlack = Image::FromFile(L".\\Image\\Black.png");
	pImages[1] = pWhite = Image::FromFile(L".\\Image\\White.png");
	pImages[2] = pBlack_a = Image::FromFile(L".\\Image\\Black_a.png");
	pImages[3] = pWhite_a = Image::FromFile(L".\\Image\\White_a.png");
	pImages[4] = pForbidden = Image::FromFile(L".\\Image\\forbidden.png");
	SetGraphics();
	isShowNumber = true;
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

void CDraw::SetShowNumber(bool isShow)
{
	isShowNumber = isShow;
	DrawStone(true);
	UpdateBoard();
}

void CDraw::SetGraphics()
{
	pGraphic = new Graphics(hwndDlg);
	pBit = new Bitmap(500, 500, pGraphic);
	memG = new Graphics(pBit);
	pCBit = nullptr;
	DrawBoard();
	UpdateBoard();
}

void CDraw::UpdateBoard()
{
	if (pCBit) 
	{
		delete pCBit;
		pCBit = nullptr;
	}
	pCBit = new CachedBitmap(pBit,pGraphic);
	InvalidateRect(hwndDlg,NULL,FALSE);
}

void CDraw::DrawBoard()
{
	memG->DrawImage(pBoard,0,0);
}

void CDraw::DrawStone(bool isAll)
{
	Position p;
	int stone = 0;
	!isAll && coords.size() > 2 ? stone = coords.size() - 2 : 0;
	if(!coords.empty())
	{
		for(; stone < coords.size() - 1; ++stone)
		{
			p = coords[stone];
			memG->DrawImage(pImages[stone % 2], p.x, p.y);
		}
		p = coords[stone];
		isShowNumber ? stone %= 2 : stone = stone % 2 + 2;
		memG->DrawImage(pImages[stone], p.x, p.y);
		if(isShowNumber) ShowNumber(isAll);
	}
}

void CDraw::ShowNumber(bool isAll)
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
	!isAll && coords.size() > 2 ? i = coords.size() - 2 : 0;
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
