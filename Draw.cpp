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

void CDraw::SetShowNumber()
{
	isShowNumber = !isShowNumber; 
	DrawStone(true); // 번호를 넣거나 뺄 때는 다시 그려줘야함. 
	UpdateBoard(); // 변경된 내용을 화면에 출력해 줌 
}

void CDraw::SetGraphics() // 예제를 보고 적용한 것이라 정확한 의미를 모르겠음. 
{                         // http://soen.kr/lecture/library/gdiplus/gdiplus.htm
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
	pCBit = new CachedBitmap(pBit,pGraphic); // 메모리에 그려진 그림을 출력하기 위한 작업 
	InvalidateRect(hwndDlg,NULL,FALSE);
}

void CDraw::DrawBoard()
{
	memG->DrawImage(pBoard,0,0); //메모리에 보드를 그려줌 
}

void CDraw::DrawStone(bool isAll)
{
	if(coords.empty()) return;
	
	Position p;
	int stone = 0;
	
	// 마지막 돌에 체크가 되어있거나 번호의 색깔이 다르므로 항상 두 개를 그려줘야 함 
	// 돌 전체를 그리지 않고 하나만 그릴때는 마지막 돌과 마지막 이전 돌만 그리면 되므로 
	!isAll && coords.size() > 2 ? stone = coords.size() - 2 : 0; 
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

// 돌에 번호를 넣기 위해 돌이 위치한 Rect와 번호를 유니코드 문자로 바꿔준다. 
RectF CDraw::GetStringInfo(wchar_t *wStr, Position p, int size, int num)
{
	swprintf(wStr, size, L"%d", num);
	return RectF(p.x, p.y, stoneSize, stoneSize);
}

// 매번 같은 값을 사용하므로 상수와 같다. 매번 초기화 하는 것을 방지하기 위해 전역으로 뺌 
Font F(L"Arial",13,FontStyleBold,UnitPixel);
SolidBrush W(Color(0,0,0));
SolidBrush B(Color(255,255,255));
SolidBrush R(Color(255,0,0));

void CDraw::ShowNumber(bool isAll)
{
    wchar_t wNum[10];
	int i = 0, size = sizeof(wNum) / sizeof(wchar_t);

	SolidBrush *pB[] = {&B, &W}; 
    StringFormat SF;
    SF.SetAlignment(StringAlignmentCenter);
    SF.SetLineAlignment(StringAlignmentCenter);

	!isAll && coords.size() > 2 ? i = coords.size() - 2 : 0;
    for(; i < coords.size() - 1; ++i)
    {
        RectF rect = GetStringInfo(wNum, coords[i], size, i + 1);
        memG->DrawString(wNum,-1,&F,rect,&SF,pB[i%2]);
    }
    RectF rect = GetStringInfo(wNum, coords[i], size, i + 1);
    memG->DrawString(wNum,-1,&F,rect,&SF,&R);
}

void CDraw::OnPaint(HDC hdc) // 메모리에 저장된 그림을 그려준다. 
{
    Graphics G(hdc);
    G.DrawCachedBitmap(pCBit,0,0);
}
