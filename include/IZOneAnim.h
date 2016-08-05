///////////////////////////////////////////////////////////
//  IZOneAnim.h
//  Implementation of the Class IZOneAnim
//  Created on:      22-мар-2011 17:13:28
//  Original author: turner
///////////////////////////////////////////////////////////

#if !defined(EA_16195644_C825_4e70_BEE7_759B09C1191E__INCLUDED_)
#define EA_16195644_C825_4e70_BEE7_759B09C1191E__INCLUDED_

#include "izobj.h"

//STL
#include <list>

using namespace std;

/**
 * временна€ анимаци€, когда завершаетс€ - автоматически уничтожаетс€, в классе
 * есть статический метод дл€ создани€ экземпл€ра класса
 */
class IZOneAnim : public IZAnim
{

public:
	IZOneAnim(): IZAnim() {}
	virtual ~IZOneAnim() {
		//автоматическую сборку мусора осуществл€ет библиотека izeng.dll
	}
	/**
	 * создает экземпл€р класса (вывод экземпл€ра на экран - автоматически), внимание: удал€ть его не надо, он удалитс€ сам, когда
	 * закончитс€ анимаци€.
	 */
	static void Create(POINTF posCentre, int idGraphTable) {
		IZOneAnim *pBang = CreateInitial(posCentre,idGraphTable);
		pBang->pDraw->Show();
	}
	/**
	 * создает экземпл€р класса и выводит его на экран на заданном уровне, 
	 * внимание: удал€ть его не надо, он удалитс€ сам, когда
	 * закончитс€ анимаци€.
	 */
	static void Create(POINTF posCentre, int idGraphTable, int nLayer) {
		IZOneAnim *pBang = CreateInitial(posCentre,idGraphTable);
		pBang->pDraw->ShowOn(nLayer);
	}
	/**
	 * удал€ет объекты, анимаци€ которых проиграна до конца
	 */
	static void Update() {
		list<IZOneAnim*>::iterator it;
		list<IZOneAnim*>::iterator itNext;
		for(it = m_tempAnims.begin();it!=m_tempAnims.end();) {
			itNext = it;
			itNext++;
			BOOL bEndAnim(FALSE);
			(*it)->pAnim->CheckEndAnim(&bEndAnim);
			if(bEndAnim) {
				delete (*it);
				m_tempAnims.erase(it);
			}
			it = itNext;
		}
	}
private: //вспом. методы
	/*
	* —оздает новый экземпл€р данного класса, минимально инициализирует и возвращает указатель на него,
	* не вывод€ на экран.
	*/
	static IZOneAnim* CreateInitial(POINTF posCentre, int idGraphTable) {
		IZOneAnim *pRes = new IZOneAnim;
		pRes->pAnim->UseExistingFrameTableAsSimpleAnim(&idGraphTable);
		POINTF wh2;
		pRes->pParams->GetHalfWidthAndHeight(&wh2);
		posCentre.x -= wh2.x; posCentre.y -=wh2.y;
		pRes->pParams->SetPos(&posCentre);
		pRes->pAnim->SetAnimType(0,PLAY_ONCE);
		m_tempAnims.push_back(pRes);
		return pRes;
	}
private:
	/**
	 * содержит все экземпл€ры класса
	 */
	static list<IZOneAnim*> m_tempAnims;

};
#endif // !defined(EA_16195644_C825_4e70_BEE7_759B09C1191E__INCLUDED_)
