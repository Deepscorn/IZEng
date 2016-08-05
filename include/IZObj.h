///////////////////////////////////////////////////////////
//  IZObj.h
//  Implementation of the Class IZObj
//  Created on:      22-мар-2011 19:16:09
//  Original author: turner
///////////////////////////////////////////////////////////

#if !defined(EA_5A578F0F_C81F_44ba_9F8D_59E2287DF982__INCLUDED_)
#define EA_5A578F0F_C81F_44ba_9F8D_59E2287DF982__INCLUDED_

//IZEng
#include "..\Projects\IZEng\IZEng\interfaces_h.h"

//WINDOWS
#include <windowsx.h>

//STL
#include <exception>

//typedef
typedef HRESULT (STDAPICALLTYPE *PDLLGETCLASSOBJECT)(REFCLSID rclsid, REFIID riid, void **ppV);

//inline methods
inline DWORD rgb32bit(char a, char r,char g, char b) {
	return ((a)<<24)+((r)<<16)+((g)<<8)+(b);
}

/**
 * базовый класс, упрощающий работу с движком IZEngine рекоммендуется для любых
 * объектов игры, которые нужно выводить на экран
 */
class IZAnim
{
public:
	IAngledDraw* pAngledDraw;
	IAnim* pAnim;
	IDraw* pDraw;
	IHUD* pHUD;
	IInput* pInput;
	IParams* pParams;
	IScreen* pScreen;
public:
	IZAnim() {
		if(m_nObjects<=0) { //must be tested!
			delete this;
			return;
		}
		pClFactory->CreateInstance(NULL,IID_IScreen,(void**)&pScreen);
		m_nObjects++;
		pScreen->QueryInterface(IID_IAngledDraw,(void**)&pAngledDraw);
		pScreen->QueryInterface(IID_IAnim,(void**)&pAnim);
		pScreen->QueryInterface(IID_IDraw,(void**)&pDraw);
		pScreen->QueryInterface(IID_IHUD,(void**)&pHUD);
		pScreen->QueryInterface(IID_IInput,(void**)&pInput);
		pScreen->QueryInterface(IID_IParams,(void**)&pParams);
	}
	/*
	 * This method must be called first - to say IZObj, where the dll is situated
	 */
	IZAnim(char* strDllFullName) {
		//use this if DirectX realization is outside project - in *.dll
		if(m_nObjects<=0) {
			m_hDll = ::LoadLibraryA(strDllFullName);
			if(!m_hDll) {
				throw(std::exception("Не удается загрузить движок IZEng.dll"));
			}
			PDLLGETCLASSOBJECT pDllGetClassObject = (PDLLGETCLASSOBJECT)::GetProcAddress(m_hDll,"DllGetClassObject");
			(*pDllGetClassObject)(CLSID_VisObj,IID_IClassFactory,(void**)&pClFactory);
		}
		pClFactory->CreateInstance(NULL,IID_IScreen,(void**)&pScreen);
		m_nObjects++;
		pScreen->QueryInterface(IID_IAngledDraw,(void**)&pAngledDraw);
		pScreen->QueryInterface(IID_IAnim,(void**)&pAnim);
		pScreen->QueryInterface(IID_IDraw,(void**)&pDraw);
		pScreen->QueryInterface(IID_IHUD,(void**)&pHUD);
		pScreen->QueryInterface(IID_IInput,(void**)&pInput);
		pScreen->QueryInterface(IID_IParams,(void**)&pParams);
	}
	virtual ~IZAnim() {
		pScreen->Release();
		pAngledDraw->Release();
		pAnim->Release();
		pDraw->Release();
		pHUD->Release();
		pInput->Release();
		pParams->Release();
		m_nObjects--;
		if(m_nObjects<=0) {
			pClFactory->Release();
			FreeLibrary(m_hDll);
		}
	}
private:
	static HINSTANCE m_hDll;
	static int m_nObjects;
	static IClassFactory* pClFactory;
};

/**
 * базовый класс, упрощающий работу с движком IZEngine рекоммендуется для любых
 * объектов игры, которые нужно не только выводить на экран, но и перемещать по опред. траектории
 */
class IZObj: public IZAnim
{

public:
	IAccelMovement* pAccelMove;
	IJump* pJump;
	ILinearMovement* pLineMove;
	IOrbitMovement* pOrbitMove;
	IPhysics* pPhysics;
	IResistForces* pResist;
	IRotation* pRotation;
public:
	IZObj():IZAnim() {
		pScreen->QueryInterface(IID_IAccelMovement,(void**)&pAccelMove);
		pScreen->QueryInterface(IID_IJump,(void**)&pJump);
		pScreen->QueryInterface(IID_ILinearMovement,(void**)&pLineMove);
		pScreen->QueryInterface(IID_IOrbitMovement,(void**)&pOrbitMove);
		pScreen->QueryInterface(IID_IPhysics,(void**)&pPhysics);
		pScreen->QueryInterface(IID_IResistForces,(void**)&pResist);
		pScreen->QueryInterface(IID_IRotation,(void**)&pRotation);
	}
	IZObj(char* strDllFullName): IZAnim(strDllFullName) {
		pScreen->QueryInterface(IID_IAccelMovement,(void**)&pAccelMove);
		pScreen->QueryInterface(IID_IJump,(void**)&pJump);
		pScreen->QueryInterface(IID_ILinearMovement,(void**)&pLineMove);
		pScreen->QueryInterface(IID_IOrbitMovement,(void**)&pOrbitMove);
		pScreen->QueryInterface(IID_IPhysics,(void**)&pPhysics);
		pScreen->QueryInterface(IID_IResistForces,(void**)&pResist);
		pScreen->QueryInterface(IID_IRotation,(void**)&pRotation);
	}
	~IZObj() {
		pAccelMove->Release();
		pJump->Release();
		pLineMove->Release();
		pOrbitMove->Release();
		pPhysics->Release();
		pResist->Release();
		pRotation->Release();
	}
};

#endif // !defined(EA_5A578F0F_C81F_44ba_9F8D_59E2287DF982__INCLUDED_)
