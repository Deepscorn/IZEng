///////////////////////////////////////////////////////////
//  dllinc.h
//  All dll subsidary funds
//  Created on:      25-мар-2011 21:59:07
///////////////////////////////////////////////////////////

#if !defined(GUID_9003CDF8_C392_4ac1_9B92_B751A6F4C417__INCLUDED_)
#define GUID_9003CDF8_C392_4ac1_9B92_B751A6F4C417__INCLUDED_

//#define WIN32_LEAN_AND_MEAN  // make sure all macros are included
//#define INITGUID            // include all GUIDs

//Include

//DirectX
#include "ddraw.h"

//WIN
#include <windows.h>

//COM
//#include <unknwn.h>

//STL
//#include <list>
#include <vector>

//OTHER
#include "interfaces_h.h"
#include "tstr.h"

using namespace std;

//METHOD
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppV);
STDAPI DllCreateInstance(REFCLSID rclsid, REFIID riid, LPVOID FAR* ppv);
void Trace(char* strError);

//MACRO
#define ANIMS_MAX 64
#define RGB32BIT(a,r,g,b) ((a)<<24)+((r)<<16)+((g)<<8)+(b)
#define LPSURF LPDIRECTDRAWSURFACE7
#define DESC DDSURFACEDESC2
#define IF_FAIL(expression,error) if(FAILED(expression)) { Trace(error); return(S_FALSE); }
#define IF_FAILN(expression,error) if(FAILED(expression)) { Trace(error); return; }
#define	IF_NOT(expression,error) if(!(expression)) { Trace(error); return(S_FALSE); }
#define DDRAW_INIT_STRUCT(ddstruct) { memset(&ddstruct,0,sizeof(ddstruct)); ddstruct.dwSize=sizeof(ddstruct); }
#define INIT_STRUCT(struc) { memset(&struc,0,sizeof(struc)); struc.lStructSize = sizeof(struc); }
#define IF_FAILNULL(expression,error) if(FAILED(expression)) { Trace(error); return(NULL); }
#define IF_FAIL_OP(expression,error,operation) if(FAILED(expression)) { Trace(error); operation; return(S_FALSE); }

//CLASS

class Anim2 {
private:
	vector<int> m_vecFrameInds;
	int m_nCur;
	int m_nPlayType;
	BOOL m_bAnimationEnd;
	int m_nFrameTime;
public:
	Anim2() { m_nFrameTime=30;}
	~Anim2() {}
	void Create(int nNumFrames,int* arrFrameInds) {
		for(int i=0;i<nNumFrames;i++)
			m_vecFrameInds.push_back(arrFrameInds[i]);
		SetAnimType(PLAY_REPEAT);
		Init();
	}
	void Init() { m_nCur=0; m_bAnimationEnd=FALSE; }
	void SetAnimType(int nType) {
		m_nPlayType=nType;
	}
	void Flip() {
		if(m_nPlayType==PLAY_REPEAT) {
			m_nCur++;
			if(m_nCur>=m_vecFrameInds.size())
				m_nCur=0;
			return;
		}
		if(m_nPlayType==PLAY_ONCE) {
			if(m_nCur>=m_vecFrameInds.size()-1)
				m_bAnimationEnd=TRUE;
			else
				m_nCur++;
			return;
		}
	}
	int GetCurFrameInd() { return m_vecFrameInds.at(m_nCur); }
	void GoToFrame(int nInd) {
		m_nCur=nInd;
		m_bAnimationEnd=FALSE;
	}
	BOOL CheckEndAnim() { return m_bAnimationEnd; }
	BOOL CheckHalfAnimPlayed() { return(m_nCur>=m_vecFrameInds.size()*0.5); }
	void SetFrameTime(int msTime) { m_nFrameTime=msTime;}
	int GetFrameTime() { return m_nFrameTime; }
};

//таблица кадров, представляет собой набор кадров с методами
//доступа к поверхностям DirectDraw
//одна таблица содержит кадры из одного графического файла на диске
class FRAMETABLE {
public:
	void Init(RECT rcFrame, BOOL bTransparent,DWORD dwTranspColor,string strFileName) {
		m_rcFrame=rcFrame;
		m_bTransparent=bTransparent;
		m_dwTranspColor=dwTranspColor;
		m_strFileName = strFileName;
	}
	void Init(RECT rcFrame,BOOL bTransparent,DWORD dwTranspColor) {
		m_rcFrame=rcFrame;
		m_bTransparent=bTransparent;
		m_dwTranspColor=dwTranspColor;
		m_strFileName = string("@")+
			tos(m_rcFrame.left)+string("|")+
			tos(m_rcFrame.top)+string("|")+
			tos(m_rcFrame.right)+string("|")+
			tos(m_rcFrame.bottom)+string("|")+
			tos(bTransparent)+string("|")+
			tos(dwTranspColor);
	}
	void AddFrame(LPSURF pSurf) {
		m_surfs.push_back(pSurf);
	}
	LPSURF GetFrameSurf(int nInd) { return m_surfs.at(nInd); }
	RECT GetFrameRect() { return m_rcFrame; }
	BOOL CheckTransparency() { return m_bTransparent; }
	DWORD GetTranspColor() { return m_dwTranspColor; }
	int GetFrameCount() { return m_surfs.size(); }
	string GetFileName() { return m_strFileName; }
public: //LOCK / UNLOCK
	HRESULT Lock(int nInd) { return(m_surfs.at(nInd)->Lock(NULL,&m_desc,
		DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL)); }
	DESC* GetFrameDesc_locked() { return &m_desc; }
	UINT* GetVidBuf_locked() { return (UINT *) m_desc.lpSurface; }
	int GetPitch32_locked() { return m_desc.lPitch/4; }
	HRESULT Unlock(int nInd) { return(m_surfs.at(nInd)->Unlock(NULL)); }
private:
	vector<LPSURF> m_surfs;
	BOOL m_bTransparent; 
	DWORD m_dwTranspColor;
	RECT m_rcFrame;
	DESC m_desc; //одно описание для всех кадров-поверхностей данной таблицы кадров
	//работает после вызова Lock()
	string m_strFileName; //имя загруженного граф. файла, для "повернутых" таблиц равен "" (пусто)
public:
	FRAMETABLE() {DDRAW_INIT_STRUCT(m_desc); m_bTransparent=FALSE; m_dwTranspColor=0; ZeroMemory(&m_rcFrame,sizeof(m_rcFrame));}
	~FRAMETABLE() { for(int i=m_surfs.size()-1;i>=0;i--) m_surfs.at(i)->Release(); }
};

//Пачка таблиц кадров, используется, (1) в основном, для отображения
//т.н. "поворачиваемых" анимаций, где каждая таблица кадров
//соответствует определенному углу поворота
//(2) также может быть использована просто для объединения таблиц кадров по
//какому-то признаку/принципу
class FRAMETABLEPACK {
private:
	vector<FRAMETABLE*> m_frame_tables;
	int m_nCurTable;
	float m_fVisTurnAngle;
public:
	FRAMETABLEPACK() {m_nCurTable=0; m_fVisTurnAngle=30; }
	~FRAMETABLEPACK() {for(int i=m_frame_tables.size()-1;i>=0;i--) delete m_frame_tables.at(i); }
	FRAMETABLE* GetCurFrameTable() { return m_frame_tables.at(m_nCurTable); }
	void SelectFrameTable(int nInd) { m_nCurTable=nInd; }
	int GetFrameTablesCount() { return m_frame_tables.size(); }
	void AddFrameTable(FRAMETABLE* pNewFrameTable) { m_frame_tables.push_back(pNewFrameTable); }
	float GetTurnAngle() { return m_fVisTurnAngle; }
	void SetTurnAngle(float fTurnAngle) { m_fVisTurnAngle=fTurnAngle; }
};

#endif //!defined(GUID_9003CDF8_C392_4ac1_9B92_B751A6F4C417__INCLUDED_)