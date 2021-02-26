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
	DrawStone(); // ��ȣ�� �ְų� �� ���� �ٽ� �׷������. 
	//UpdateBoard(); // ����� ������ ȭ�鿡 ����� �� 
}

void CDraw::SetGraphics() // ������ ���� ������ ���̶� ��Ȯ�� �ǹ̸� �𸣰���. 
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
	pCBit = new CachedBitmap(pBit,pGraphic); // �޸𸮿� �׷��� �׸��� ����ϱ� ���� �۾� 
	InvalidateRect(hwndDlg,NULL,FALSE);
}

void CDraw::DrawBoard()
{
	memG->DrawImage(pBoard,0,0); //�޸𸮿� ���带 �׷��� 
}

void CDraw::DrawForbidden(vector<Position> &forbiddenPoints) // �ݼ� �ڸ��� ǥ������ 
{
	while(!forbiddenPoints.empty())
	{
		Position p = forbiddenPoints.back();
		forbiddenPoints.pop_back();
		memG->DrawImage(pForbidden, p.x, p.y);
	}
}

void CDraw::DrawStone()
{
	DrawBoard();
	if(coords.empty()) return;
	
	Position p;
	int stone = 0;
	
	for(; stone < coords.size() - 1; ++stone)
	{
		p = coords[stone];
		memG->DrawImage(pImages[stone % 2], p.x, p.y);
	}
	p = coords[stone]; // ������ ���� üũ�� �� ���� �׷��� �ϹǷ� ������ �ξ�� �� 
	isShowNumber ? stone %= 2 : stone = stone % 2 + 2;
	memG->DrawImage(pImages[stone], p.x, p.y);
	if(isShowNumber) ShowNumber();
}

// ���� ��ȣ�� �ֱ� ���� ���� ��ġ�� Rect�� ��ȣ�� �����ڵ� ���ڷ� �ٲ��ش�. 
RectF CDraw::GetStringInfo(wchar_t *wStr, Position p, int size, int num)
{
	swprintf(wStr, size, L"%d", num);
	return RectF(p.x, p.y, stoneSize, stoneSize);
}

void CDraw::ShowNumber()
{
    wchar_t wNum[10];
	int i = 0, size = sizeof(wNum) / sizeof(wchar_t);

	Font F(L"Arial",13,FontStyleBold,UnitPixel);
	SolidBrush W(Color(0,0,0));
	SolidBrush B(Color(255,255,255));
	SolidBrush R(Color(255,0,0));
	SolidBrush *pB[] = {&B, &W}; 

    StringFormat SF;
    SF.SetAlignment(StringAlignmentCenter);
    SF.SetLineAlignment(StringAlignmentCenter);

	//!isAll && coords.size() > 2 ? i = coords.size() - 2 : 0;
    for(; i < coords.size() - 1; ++i)
    {
        RectF rect = GetStringInfo(wNum, coords[i], size, i + 1);
        memG->DrawString(wNum,-1,&F,rect,&SF,pB[i%2]);
    }
    RectF rect = GetStringInfo(wNum, coords[i], size, i + 1);// ������ ���� ������ �޸� �ϱ� ���� �и� 
    memG->DrawString(wNum,-1,&F,rect,&SF,&R);
}

void CDraw::OnPaint(HDC hdc) // �޸𸮿� ����� �׸��� �׷��ش�. 
{
    Graphics G(hdc);
    G.DrawCachedBitmap(pCBit,0,0);
}

void CDraw::ShowEndMsg(short stone) // �ºΰ� ������ ���� ���ڸ� �޽��� �ڽ��� Ÿ��Ʋ �ٿ� ǥ���� �� 
{
	const char *msg[] = {"Omok - Tie", "Omok - Black Win", "Omok - White Win"};

	SetTitle(msg[stone]);
	MessageBox(hwndDlg, msg[stone] + 7, "Game Over", MB_OK | MB_ICONINFORMATION);
}

void CDraw::ShowMsg(const char *msg)
{
	MessageBox(hwndDlg, msg, "Warning", MB_OK | MB_ICONSTOP);
}

void CDraw::SetTitle(const char* titleName)
{
	SetWindowText(hwndDlg, titleName);
}

void CDraw::SetTitle(int id)
{
	const char *titleName[] = {"Omok - Gomku Rule", "Omok - Renju Rule"};
	SetWindowText(hwndDlg, titleName[id]);
}
