///////////////////////////////////////////////////////////
//  IZOneAnim.h
//  Implementation of the Class IZOneAnim
//  Created on:      22-���-2011 17:13:28
//  Original author: turner
///////////////////////////////////////////////////////////

#if !defined(EA_16195644_C825_4e70_BEE7_759B09C1191E__INCLUDED_)
#define EA_16195644_C825_4e70_BEE7_759B09C1191E__INCLUDED_

#include "izobj.h"

//STL
#include <list>

using namespace std;

/**
 * ��������� ��������, ����� ����������� - ������������� ������������, � ������
 * ���� ����������� ����� ��� �������� ���������� ������
 */
class IZOneAnim : public IZAnim
{

public:
	IZOneAnim(): IZAnim() {}
	virtual ~IZOneAnim() {
		//�������������� ������ ������ ������������ ���������� izeng.dll
	}
	/**
	 * ������� ��������� ������ (����� ���������� �� ����� - �������������), ��������: ������� ��� �� ����, �� �������� ���, �����
	 * ���������� ��������.
	 */
	static void Create(POINTF posCentre, int idGraphTable) {
		IZOneAnim *pBang = CreateInitial(posCentre,idGraphTable);
		pBang->pDraw->Show();
	}
	/**
	 * ������� ��������� ������ � ������� ��� �� ����� �� �������� ������, 
	 * ��������: ������� ��� �� ����, �� �������� ���, �����
	 * ���������� ��������.
	 */
	static void Create(POINTF posCentre, int idGraphTable, int nLayer) {
		IZOneAnim *pBang = CreateInitial(posCentre,idGraphTable);
		pBang->pDraw->ShowOn(nLayer);
	}
	/**
	 * ������� �������, �������� ������� ��������� �� �����
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
private: //�����. ������
	/*
	* ������� ����� ��������� ������� ������, ���������� �������������� � ���������� ��������� �� ����,
	* �� ������ �� �����.
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
	 * �������� ��� ���������� ������
	 */
	static list<IZOneAnim*> m_tempAnims;

};
#endif // !defined(EA_16195644_C825_4e70_BEE7_759B09C1191E__INCLUDED_)
