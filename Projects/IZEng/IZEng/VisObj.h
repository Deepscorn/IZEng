#pragma once 

//DirectX
#include "ddraw.h"

//WIN
#include <windows.h>

//COM
#include <unknwn.h>

//STL
#include <list>
#include <vector>

//OTHER
#include "interfaces_h.h"

//OTHER
#include "dllinc.h"

using namespace std;

class VisObj: public IScreen, public IDraw,public IAngledDraw, public IAnim,
	public IParams, public IInput, public IHUD {
public:
	VisObj();
	virtual ~VisObj();
public: //IScreen
	HRESULT STDMETHODCALLTYPE ResetDisplay( 
            HWND hDispWnd,
            int nWidth,
            int nHeight,
            int nRefRate,
			BOOL bFullscreen, 
			int nFPS);
    HRESULT STDMETHODCALLTYPE UpdateScreen();
	HRESULT STDMETHODCALLTYPE MoveCamera(POINTF* pvecD);
	HRESULT STDMETHODCALLTYPE SetCamera(POINTF* pptCam);
	HRESULT STDMETHODCALLTYPE GetCameraPos(POINTF *pptCam);
	HRESULT STDMETHODCALLTYPE GetScreenRect(RECT *prcScreen);
	HRESULT STDMETHODCALLTYPE GetScreenWH(POINTF *pptScreen);
	HRESULT STDMETHODCALLTYPE GetCameraRect(RECT *prcCam);
	HRESULT STDMETHODCALLTYPE GetCameraRBPos(POINTF *pptCam);
	HRESULT STDMETHODCALLTYPE SetWorldBounds(RECT* prcBounds);
	HRESULT STDMETHODCALLTYPE GetWorldBounds(RECT* prcBounds);
	HRESULT STDMETHODCALLTYPE ShutDown();
	HRESULT STDMETHODCALLTYPE AddFrameTable(
		int* pnID,
		UCHAR* strPathToFile,
		int nNeededFrameW,
		int nNeededFrameH,
		int nColumns,
		int nRows,
		BOOL bTransparent,
		DWORD dwTranspColor);
	HRESULT STDMETHODCALLTYPE AddBMPFrameTable(int* pnID,
		UCHAR* strPathToFile,
		int nNeededFrameW,
		int nNeededFrameH,
		int nColumns,
		int nRows,
		BOOL bTransparent,
		DWORD dwTranspColor);
	HRESULT STDMETHODCALLTYPE AddEmptyFrameTable(
		 int* pnID,
		 int nNeededFrameW,
		 int nNeededFrameH,
		 int nColumns,
		 int nRows,
		 BOOL bTransparentFill,
		 DWORD dwFillColor);
	HRESULT STDMETHODCALLTYPE AddAngledTables(
		int* pnID, 
	    int* pidSrcFrameTable,
		float fTurnAngle,
		float fNeededAngleOfFirstTable);
	//for fast and easy use
	HRESULT STDMETHODCALLTYPE AddOrGetExistingFrameTable( int* pnID,
		 UCHAR* strPathToFile,
		 int nNeededFrameW,
		 int nNeededFrameH,
		 int nColumns,
		 int nRows,
		 BOOL bTransparent,
		 DWORD dwTranspColor);
public: //IInput
	HRESULT STDMETHODCALLTYPE CheckKeyDown(int vKey,BOOL* bRes);
	HRESULT STDMETHODCALLTYPE CheckKeyUp(int vKey,BOOL* bRes);
public: //IDraw
	HRESULT STDMETHODCALLTYPE Show();
	HRESULT STDMETHODCALLTYPE Hide();
	HRESULT STDMETHODCALLTYPE ShowOn(int depth);
	HRESULT STDMETHODCALLTYPE GetTranspColor(DWORD *pdwColor);
	HRESULT STDMETHODCALLTYPE Lock();
	HRESULT STDMETHODCALLTYPE GetPixel(POINTF* pptWhere,DWORD *pdwPixColor);
	HRESULT STDMETHODCALLTYPE Unlock();
public: //IHUD
	HRESULT STDMETHODCALLTYPE CheckVisible(BOOL* pRes);
	HRESULT STDMETHODCALLTYPE DrawText(LPRECT prcTextBox,LPWSTR strText,DWORD dwColor,int nHeight);
	HRESULT STDMETHODCALLTYPE DrawLine(POINTF* ppt1,POINTF *ppt2,DWORD dwColor,int nWidth);  
	HRESULT STDMETHODCALLTYPE DrawVLine(int x,int y0, int y1,int nRad,DWORD dwColor);
	HRESULT STDMETHODCALLTYPE DrawHLine(int x0,int x1, int y,int nRad,DWORD dwColor);
	HRESULT STDMETHODCALLTYPE ColorFill(RECT *pRect, DWORD dwColor);
	HRESULT STDMETHODCALLTYPE DrawPoint(POINTF *ppt,DWORD dwColor,int nWidth);
	HRESULT STDMETHODCALLTYPE AddText(LPRECT prcTextBox,UCHAR* strText,DWORD dwColor,int nHeight, DWORD dwFlags);
	HRESULT STDMETHODCALLTYPE AddLine(POINTF* ppt1,POINTF *ppt2,DWORD DWORD,int nWidth);
	HRESULT STDMETHODCALLTYPE AddColorFill(RECT *pRect, DWORD dwColor);
	HRESULT STDMETHODCALLTYPE AddHLine(int x0,int x1, int y,int nWidth,DWORD dwColor);
	HRESULT STDMETHODCALLTYPE AddVLine(int x,int y0, int y1,int nWidth,DWORD dwColor);
	HRESULT STDMETHODCALLTYPE AddBtnView(RECT rcBounds, int nBorderWidth,
			DWORD clBack, DWORD clBorder, UCHAR* caption, 
			DWORD clFont, int nFontHeight, int nFontFlags);
public://IAngledDraw
	HRESULT STDMETHODCALLTYPE UseExistingAngledTables(int* pnAngledTablesPack);
	HRESULT STDMETHODCALLTYPE UseExistingAngledTablesAndSimpleAnim(int* pnAngledTablesPack, int nNumStartTable);
	HRESULT STDMETHODCALLTYPE SelectTableByVector( POINTF *pvec);
	HRESULT STDMETHODCALLTYPE SelectTable( int nNo);
	HRESULT STDMETHODCALLTYPE GetNumTables( int* pnNumTables);
	HRESULT STDMETHODCALLTYPE SelectTableByAngle( float fAngle);
public: //IAnim
	 HRESULT STDMETHODCALLTYPE UseExistingFrameTable(int* pnID);
     HRESULT STDMETHODCALLTYPE SetFrameTime(int nAnimInd, int msTime);
	 HRESULT STDMETHODCALLTYPE CreateAnim(  int nAnimInd, int nFramesAmount,int *arrFrameInds);
	 HRESULT STDMETHODCALLTYPE SetAnimType( int nAnimInd, int nPlayType);
	 HRESULT STDMETHODCALLTYPE SelectActiveAnim( int nAnimInd);
     HRESULT STDMETHODCALLTYPE SelectActiveFrame( int nFrameInd);
     HRESULT STDMETHODCALLTYPE FreezeFrame(BOOL bFreeze);
	 HRESULT STDMETHODCALLTYPE GoToFrame(int nShift);
	 HRESULT STDMETHODCALLTYPE GetCurAnimInd(int *pnCurAnimInd);
	 HRESULT STDMETHODCALLTYPE CheckEndAnim(BOOL *pbEndAnim);
	 HRESULT STDMETHODCALLTYPE CheckHalfAnimPlayed(BOOL *pbHalfAnim);
	 HRESULT STDMETHODCALLTYPE GetFrameAmountInTable(int *pnFrames);
	 //for fast & easy use
	 HRESULT STDMETHODCALLTYPE UseExistingFrameTableAsSimpleAnim(int* pnID);
	 HRESULT STDMETHODCALLTYPE CreateSimpleAnim();
	 HRESULT STDMETHODCALLTYPE CreateLinearAnim(int nAnimInd,int nStartFrame,int nEndFrame);
	 HRESULT STDMETHODCALLTYPE LoadSimpleAnim(
		 UCHAR* strPathToFile,
		 int nNeededFrameW,
		 int nNeededFrameH,
		 int nColumns,
		 int nRows,
		 BOOL bTransparent,
		 DWORD dwTranspColor);
	 HRESULT STDMETHODCALLTYPE LoadFrameTable(
		 UCHAR* strPathToFile,
		 int nNeededFrameW,
		 int nNeededFrameH,
		 int nColumns,
		 int nRows,
		 BOOL bTransparent,
		 DWORD dwTranspColor);
	 HRESULT STDMETHODCALLTYPE LoadOrUseExistingSimpleAnim(
		 UCHAR* strPathToFile,
		 int nNeededFrameW,
		 int nNeededFrameH,
		 int nColumns,
		 int nRows,
		 BOOL bTransparent,
		 DWORD dwTranspColor);
	HRESULT STDMETHODCALLTYPE LoadOrUseExistingFrameTable(
		UCHAR* strPathToFile,
		int nNeededFrameW,
		int nNeededFrameH,
		int nColumns,
		int nRows,
		BOOL bTransparent,
		DWORD dwTranspColor);
public: //IParams
	HRESULT STDMETHODCALLTYPE SetPos(POINTF *pptPos);
	HRESULT STDMETHODCALLTYPE Move(POINTF *pvecShift);
	HRESULT STDMETHODCALLTYPE Resize(int nNewWidth, int nNewHeight);
	HRESULT STDMETHODCALLTYPE GetSmallestRad( float *pfRad);
	HRESULT STDMETHODCALLTYPE GetBiggestRad(float *pfRad);
	HRESULT STDMETHODCALLTYPE GetCoordsRect(RECT* rcCoords);
	HRESULT STDMETHODCALLTYPE GetCoordsWHRect(RECT* rcCoordsWH);
	HRESULT STDMETHODCALLTYPE GetCoordsPt(POINTF* ptCoords);
	HRESULT STDMETHODCALLTYPE GetCentreCoordsPt(POINTF* ptCentreCoords);
	HRESULT STDMETHODCALLTYPE GetWidthAndHeight(POINTF *pwhFrame);
	HRESULT STDMETHODCALLTYPE GetHalfWidthAndHeight(POINTF *pwhFrame);
	//UNSAFE!
	HRESULT STDMETHODCALLTYPE GetLX(int *pnLX);
	HRESULT STDMETHODCALLTYPE GetCX(int *pnCX);
	HRESULT STDMETHODCALLTYPE GetRX(int *pnRX);
	HRESULT STDMETHODCALLTYPE GetTY(int *pnTY);
	HRESULT STDMETHODCALLTYPE GetCY(int *pnCY);
	HRESULT STDMETHODCALLTYPE GetBY(int *pnBY);
	HRESULT STDMETHODCALLTYPE GetWidth( int *pnWidth);
	HRESULT STDMETHODCALLTYPE GetHeight(int *pnHeight);
public: //IUnknown
	STDMETHODIMP QueryInterface(REFIID idInterface, void **ppInterface);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();
private:  //DirectX STUFF
	static LPDIRECTDRAW7 m_pDDraw;
	static DDSURFACEDESC2 m_SurfDesc;
	static LPDIRECTDRAWSURFACE7 m_pPrimSurf;
	static LPDIRECTDRAWSURFACE7 m_pBackSurf;
	static DDBLTFX m_blitFX;
private:  //Window STUFF
	static HWND m_hMainWnd;
private: //parametres of screen
	static int m_nScreenWidth,m_nScreenHeight;
	static BOOL m_bFullscreen;
protected:
	//camera position
	static POINTF m_ptCam;
	static RECT m_rcWorldBounds;
protected:
	static int m_nObjectsCreated; //считает объекты класса
protected: //keeps all objects, that have been created, used in ShutDown()
	static list<VisObj*> m_visObjs;
	list<VisObj*>::iterator m_itVisObj; //iterator to current element in list above
protected: //keeps objects to be drawn on screen, position in list, used in UpdateScreen()
	//sets depth of drawing
	static list<VisObj*> m_drawnObjs;
	list<VisObj*>::iterator m_itDrawnObj; //iterator to current element in list above
private:
	static vector<FRAMETABLE*> m_frame_tables;
	FRAMETABLE* m_pFrameTable; //текущая таблица кадров
	static vector<FRAMETABLEPACK*> m_frame_table_packs;
	FRAMETABLEPACK* m_pFrameTablePack; //текущая сборка повернутых таблиц, если объект не нуждается
	//в повороте = NULL
private:
	Anim2 *m_Anims2[ANIMS_MAX]; //анимации, вернее индексы из тек. таблицы кадров m_pFrameTable
	//, кот составляют анимацию
	int m_nCurAnim;
	//frame
	DWORD m_tmLastRefresh;
	//BOOL m_bHideFrame;
	BOOL m_bFreeze;
	int m_nFrameWait; //время задержки кадра, связано с FPS
private: //IHUD list of buttons. Has no elements, if object is not a HUD.
	//list<RECT> lstHUDBtns; 
	//FRAMETABLE* m_pHUDFrameTable; //HUD Frame table, NULL if none
protected: //Physical parametres
	POINTF m_ptCoords;
	int m_nFrameW;
	int m_nFrameH;
protected:
	int m_nRefCount;
private:
	static HRESULT (STDMETHODCALLTYPE *pFlipBackSurf)();
	static HRESULT STDMETHODCALLTYPE FlipBackSurfToScreen();
	static HRESULT STDMETHODCALLTYPE FlipBackSurfToWindow();
	HRESULT STDMETHODCALLTYPE CreatePrimarySurface();
	HRESULT STDMETHODCALLTYPE CreateOffScreenSurface(LPDIRECTDRAWSURFACE7& pDestSurf,
									 int nWidth, int nHeight, 
									 int nTranspColor,
									 DDSURFACEDESC2& DestSurfDescr);
	HRESULT STDMETHODCALLTYPE CreateOffScreenSurface(LPDIRECTDRAWSURFACE7& pDestSurf,
									 int nWidth, int nHeight, 
									 DDSURFACEDESC2& DestSurfDescr);
	HRESULT STDMETHODCALLTYPE AttachBackSurface();
	HRESULT STDMETHODCALLTYPE AttachScreenClipper();
	HRESULT STDMETHODCALLTYPE AttachBackBufClipper_screen_bounds();
	HRESULT STDMETHODCALLTYPE AttachWindowClipper_window_bounds();
	HRESULT STDMETHODCALLTYPE DrawRotated(RECT rcSrc,POINTF ptDest,RECT rcDestBounds);
	HRESULT STDMETHODCALLTYPE DrawRotated(LPSURF pDestSurf,DESC* pDestDesc, LPSURF pSrcSurf,DESC* pSrcDesc, RECT rcSrc,POINTF ptDest,RECT rcDestBounds,float fDrawAngle,BOOL bTransparent,DWORD dwTranspColor);
	//откуда считывем, куда рисуем и ограничитель-"окошко" для рисования; все - в одной системе координат
	HRESULT STDMETHODCALLTYPE BoundWithScreen(LPRECT rcToBound);
	LPDIRECTDRAWSURFACE7 STDMETHODCALLTYPE CreateSurfFromFBuffer(BITMAPINFOHEADER& bitmapinfoheader,UCHAR *buffer,long lBmpStartX,long lBmpStartY,
				long lBmpFrameW,long lBmpFrameH,
				DDSURFACEDESC2& desc,long nNeededFrameW,long nNeededFrameH,
				bool bTransparent,DWORD dwTranspColor);
	LPDIRECTDRAWSURFACE7 STDMETHODCALLTYPE PrepareSurface(int nPicFrameW,int nPicFrameH,
		bool bTransparent,DWORD dwTranspColor,DESC& desc);
	HRESULT STDMETHODCALLTYPE CopyByteArray(DESC& desc,BYTE* pSrc,RECT& rcFrame,int nSrcW,bool bIs32BIT);
	HRESULT STDMETHODCALLTYPE Draw();
	HRESULT STDMETHODCALLTYPE DrawPicture();
	HRESULT STDMETHODCALLTYPE FreeAllFrameTables();
	HRESULT STDMETHODCALLTYPE FreeAllAngledTables();
	bool IsVisible();
	LPSURF STDMETHODCALLTYPE GetCurFrameSurf();
};