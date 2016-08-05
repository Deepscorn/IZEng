#include "IZMenu.h"

//OTHER
#include "izmath.h"

const IZFont def_font;
const IZBtnView def_btnView;

IZMenu::~IZMenu(void)
{
}

float w(float xPercents,POINTF whBack) { return whBack.x * xPercents; }
	float h(float yPercents,POINTF whBack) { return whBack.y * yPercents; }

// Creates simple menu
void IZMenu::CreateSimple(UCHAR* fnameBackground,POINTF whBack,BOOL bTransparent,DWORD clTransp)
{
	IZAnim* back = new IZAnim();
	back->pAnim->LoadSimpleAnim(fnameBackground,whBack.x,whBack.y,1,1,bTransparent,clTransp);
	back->pDraw->Show();
	IZBtn* btn = new IZBtn();
	//
	POINTF ptCoords = {w(0.2,whBack),h(0.1,whBack)};
	//
	btn->Init(ptCoords,m_btnView,"Начать игру",m_font,0x0021AA);
	m_btns.push_back(btn);
}

void IZMenu::Update(POINTF pt_mouse) {
	ptr_vector<IZBtn>::iterator it;
	for(it = m_btns.begin();it!=m_btns.end();it++)
		it->Update(pt_mouse);
}