#pragma once
#include "izobj.h"

//BOOST
#include "boost\ptr_container\ptr_vector.hpp"
#include "boost\ptr_container\ptr_list.hpp"

//OTHER
#include "izmath.h"

using namespace boost;
using namespace izmath;

//поведение аналогично встроенному типу - нельзя изменить часть объекта,
//меняется только целиком
struct IZFont {
	const DWORD color;
	const int height;
	const int flags;
public://0xFFFFFF,20,TXT_CENTER
	IZFont(DWORD nColor = 0xFFFFFF,int nHeight = 20,int nFlags = TXT_CENTER):
		color(nColor),height(nHeight),flags(nFlags) {}
};
extern const IZFont def_font;

//поведение аналогично встроенному типу - нельзя изменить часть объекта,
//меняется только целиком
//описывает отображение кнопки
//обведенный прямоугольник заданных цветов
struct IZBtnView {
	const POINTF size; //ширина и высота
	const int border_width;
	const DWORD color, border_color;
public:
	IZBtnView(float width = 150,float height = 30, int new_border_width = 5,
		DWORD new_color = 0x666666,DWORD new_border_color = 0xFF):
		size(Pt(width,height)),border_width(new_border_width),
			color(new_color), border_color(new_border_color) {}
	RECT AsRect() {
		RECT result = {0,0,
			size.x,size.y};
		return result;
	}
	/*RECT GetInnerRect() {
		RECT result = { bounds.left + border_width, bounds.top + border_width,
			bounds.right - border_width, bounds.bottom - border_width };
		return result;
	}*/
	/*RECT GetBounds(POINTF coordsForBtn) {
		RECT result = {coordsForBtn.x,coordsForBtn.y,
			coordsForBtn.x+size.x,coordsForBtn.y+size.y};
		return result;
	}*/
};

extern const IZBtnView def_btnView;

//описание кнопки
//кнопка реагирует на наведение курсора и щелчок лев. кн.
//обработчики - ставятся присваиванием, напр:
//IZBtn btn;
////init here
//btn.OnClick = &OnClickListener; //OnClickListener - user function
//btn.OnFocus = &OnFocusListener; //OnFocusListener - user function
////call btn.Update(mouse_coords) every frame to make button live
class IZBtn: public IZAnim
{
public:
	IZBtn() 
	{
		OnClick = &IZBtn::doNothing;
		OnFocus = &IZBtn::doNothing;
	}
	~IZBtn() {}
	void Init(POINTF ptCoords, IZBtnView def_rect, char* caption, const IZFont& font = def_font, 
		DWORD clSelect = 0x00AA21) 
	{
		int tmp;
		this->pScreen->AddEmptyFrameTable(&tmp,def_rect.size.x,def_rect.size.y,3,1,TRUE,0x000000);
		this->pAnim->UseExistingFrameTableAsSimpleAnim(&tmp);
		this->pParams->SetPos(&ptCoords);
		
		//рисуем кнопку :)

		AddBtnFrame(0,caption,ptCoords,def_rect,font);
		IZBtnView btnViewOnFocus(def_rect.size.x,def_rect.size.y,
			def_rect.border_width,def_rect.color,clSelect);
		AddBtnFrame(1,caption,ptCoords,btnViewOnFocus,font);
		IZBtnView btnViewOnClick(def_rect.size.x,def_rect.size.y,
			def_rect.border_width,def_rect.color,clSelect+0x555555);
		AddBtnFrame(2,caption,ptCoords,btnViewOnClick,font);

		//остановимся на первом кадре
		this->pAnim->SelectActiveFrame(0);
		this->pAnim->FreezeFrame(TRUE);

		//show list
		this->pDraw->Show();
	}
	void Init(POINTF ptCoords, 
		IZBtnView btnView, IZBtnView btnViewOnFocus, IZBtnView btnViewOnClick,
		char* caption, 
		IZFont font, IZFont fontOnFocus, IZFont fontOnClick,
		DWORD clSelect) 
	{
		int tmp;
		POINTF whMax = MaxWH(btnView.size,btnViewOnFocus.size,btnViewOnClick.size);
		this->pScreen->AddEmptyFrameTable(&tmp,whMax.x,whMax.y,3,1,TRUE,0x000000);
		this->pAnim->UseExistingFrameTableAsSimpleAnim(&tmp);
		this->pParams->SetPos(&ptCoords);
		
		//рисуем кнопку :)

		AddBtnFrame(0,caption,ptCoords,btnView,font);
		/*IZBtnView btnViewOnFocus(btnView.size.x,btnView.size.y,
			btnView.border_width,btnView.color,clSelect);*/
		AddBtnFrame(1,caption,ptCoords,btnViewOnFocus,font);
		/*IZBtnView btnViewOnClick(btnView.size.x,btnView.size.y,
			btnView.border_width,btnView.color,clSelect+0x555555);*/
		AddBtnFrame(2,caption,ptCoords,btnViewOnClick,font);

		//остановимся на первом кадре
		this->pAnim->SelectActiveFrame(0);
		this->pAnim->FreezeFrame(TRUE);

		//show list
		this->pDraw->Show();
	}
	void Update(POINTF pt_mouse) {
		//updateBtn(this,ptf);
		BOOL bDown;
		//обычный вид кнопки
		this->pAnim->SelectActiveFrame(0);
		RECT rcBtn;
		this->pParams->GetCoordsRect(&rcBtn);
		if(CheckInRect(pt_mouse.x,pt_mouse.y,rcBtn)) {
			this->pInput->CheckKeyDown(VK_LBUTTON,&bDown);
			if(bDown) {
				this->pAnim->SelectActiveFrame(2); //на кнопку наведена мышь и нажата лев. кн.
				OnClick(this); //здесь вызов обработчика нажатия
			}
			else {
				this->pAnim->SelectActiveFrame(1); //на кнопку наведена мышь
				OnFocus(this); //здесь вызов обработчика фокуса
			}
		}
	}
	void (*OnClick)(IZBtn* sender);
	void (*OnFocus)(IZBtn* sender);
private:
	//static void doNothing(POINTF pt_clicked) {}
	static void doNothing(IZBtn* sender) {}
	void AddBtnFrame(int indFrame, char* caption, POINTF ptCoords,
				 IZBtnView& pretty_rect, const IZFont& font = def_font) 
	{
		this->pAnim->SelectActiveFrame(indFrame);
		this->pHUD->AddBtnView(pretty_rect.AsRect(),pretty_rect.border_width, pretty_rect.color,
			pretty_rect.border_color, (UCHAR*)caption, font.color, font.height, font.flags);
	}
private: //math
	inline float imax(float a, float b) {
		return (a<b)?b:a;
	}
	inline float imax(float a,float b,float c) {
		return imax(a,imax(b,c));
	}
	POINTF MaxWH(const POINTF& wh1,const POINTF& wh2,const POINTF& wh3) {
		POINTF result = { imax(wh1.x,wh2.x,wh3.x), imax(wh1.y,wh2.y,wh3.y) };
		return result;
	}
};

//описание меню - контейнера кнопок и изображений
//наследуйте от этого класса свои пользовательские меню
//чтобы посмотреть пример функциональности класса - вызовите CreateSimple()
class IZMenu
{
public:
	/*IZMenu(void) {

	}*/
	//меню с увеличивающимися кнопками при наведении
	IZMenu(float factorMultiply = 2, IZFont font = def_font, IZBtnView btnView = def_btnView):
		m_font(font), m_fontOnClick(font),
		m_btnView(btnView), m_btnViewOnClick(btnView),
		m_fontOnFocus(font.color,font.height * factorMultiply, font.flags),
		m_btnViewOnFocus(btnView.size.x * factorMultiply, btnView.size.y * factorMultiply,
			btnView.border_width * factorMultiply,btnView.color,btnView.border_color)
	{
	}
	//меню с обводом контура опред. цветом при наведении и нажатии - сделаю позже
	/*IZMenu(void) {

	}*/
	virtual ~IZMenu(void);
public: 
	// Creates simple menu
	void CreateSimple(UCHAR* fnameBackground,POINTF whBack,BOOL bTransparent = FALSE,DWORD clTransp = 0x0);
	void Update(POINTF pt_mouse);
	IZBtn* Btn(int ind) { return &m_btns.at(ind); }
private:
	ptr_vector<IZBtn> m_btns;
	ptr_list<IZAnim> m_pics;
	//оформление
	IZFont m_font;
	IZFont m_fontOnFocus;
	IZFont m_fontOnClick;
	IZBtnView m_btnView;
	IZBtnView m_btnViewOnFocus;
	IZBtnView m_btnViewOnClick;
};
