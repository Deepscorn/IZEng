//#pragma comment(lib,"corona.lib")
#include "VisObj.h"

//WIN
//#include <windows.h>

//STD
#include <fstream>
#include <cmath>
//#include <algorithm>

//OTHER
#include <corona.h>
#include "izmath.h"
#include "tstr.h" //boost dependency - must be deleted sometime

using namespace std;

typedef unsigned char byte;
char buf[260];

using namespace izmath;

//static stuff/////////////////////////////
LPDIRECTDRAW7 VisObj::m_pDDraw;
DDSURFACEDESC2 VisObj::m_SurfDesc;
LPDIRECTDRAWSURFACE7 VisObj::m_pPrimSurf;
LPDIRECTDRAWSURFACE7 VisObj::m_pBackSurf;
DDBLTFX VisObj::m_blitFX;
HWND VisObj::m_hMainWnd;
int VisObj::m_nScreenWidth,VisObj::m_nScreenHeight;
BOOL VisObj::m_bFullscreen;
int VisObj::m_nObjectsCreated=0;
POINTF VisObj::m_ptCam = {0,0};
RECT VisObj::m_rcWorldBounds;
HRESULT (STDMETHODCALLTYPE *VisObj::pFlipBackSurf)();
vector<FRAMETABLE*> VisObj::m_frame_tables;
vector<FRAMETABLEPACK*> VisObj::m_frame_table_packs;
list<VisObj*> VisObj::m_visObjs;
list<VisObj*> VisObj::m_drawnObjs;
//static stuff end//////////////////////////////

HRESULT LockSurface(LPDIRECTDRAWSURFACE7 pSurf,DDSURFACEDESC2& SurfDesc, UINT*& pnVidbuf, int& nPitch32) {
	IF_FAIL(pSurf->Lock(NULL,&SurfDesc,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL),
		"Failed to lock surface: LockSurface32");
	//ПРЕОБРАЗОВАНИЯ
	pnVidbuf = (UINT *) SurfDesc.lpSurface;
	nPitch32 = SurfDesc.lPitch/4;
	return(S_OK);
}
HRESULT LockSurface(LPDIRECTDRAWSURFACE7 pSurf,DDSURFACEDESC2& SurfDesc,UINT*& pnVidbuf, int& nPitch32, DWORD& dwTranspPixelL, DWORD& dwTranspPixelH) {
	IF_FAIL(pSurf->Lock(NULL,&SurfDesc,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL),
		"Failed to lock surface: LockSurface32");
	//ПРЕОБРАЗОВАНИЯ
	pnVidbuf = (UINT *) SurfDesc.lpSurface;
	nPitch32 = SurfDesc.lPitch/4;
	dwTranspPixelL = SurfDesc.ddckCKSrcBlt.dwColorSpaceLowValue;
	dwTranspPixelH = SurfDesc.ddckCKSrcBlt.dwColorSpaceHighValue;
	return(S_OK);
}

///////////////CONSTRUCTOR////////////////////////////////////
VisObj::VisObj() {
	if(m_nObjectsCreated<=0) {
		Build_Sin_Cos_Tables();
		//initalize draw system
		IF_FAILN(DirectDrawCreateEx(NULL,(void**)&m_pDDraw,IID_IDirectDraw7,NULL),
			"DirectDrawCreateEx failed");
		DDRAW_INIT_STRUCT(m_SurfDesc);
		DDRAW_INIT_STRUCT(m_blitFX);
		m_pBackSurf=NULL;
		m_pPrimSurf=NULL;
		Nullify(m_ptCam);
		Set(m_rcWorldBounds,-32000,-32000,32000,32000);
	}
	//counter of visual objects
	m_nObjectsCreated++;
	//physical parametres
	Nullify(m_ptCoords);
	//animation
	m_nCurAnim=0;
	for(int i=0;i<ANIMS_MAX;i++)
		m_Anims2[i]=NULL;
	//frame
	m_tmLastRefresh=GetClock();
	m_bFreeze=FALSE;
	//m_bHideFrame=TRUE;
	m_nFrameW=0;
	m_nFrameH=0;
	m_nFrameWait = 30;
	//dll params
	m_nRefCount=0;
	//cur table and tablePack
	m_pFrameTable=NULL;
	m_pFrameTablePack=NULL;
	//save this instance
	m_visObjs.push_back(this);
	m_itVisObj = m_visObjs.end();
	m_itVisObj--;
	m_itDrawnObj = m_drawnObjs.end(); //means that this object is not displayed (and not in list accordingly)
	//HUD
	//m_pHUDFrameTable = NULL;
}

VisObj::~VisObj() {
	//decrement counter
	m_nObjectsCreated--;
	//remove animations
	for(int i=0;i<ANIMS_MAX;i++)
		if(m_Anims2[i])
			delete m_Anims2[i];
	//remove from lists
	if(m_itDrawnObj != m_drawnObjs.end())
		m_drawnObjs.erase(m_itDrawnObj);
	m_visObjs.erase(m_itVisObj);
	//final - free resources and screen
	if(m_nObjectsCreated<=0) {
		FreeAllAngledTables();
		FreeAllFrameTables();
		if(m_pBackSurf) {
			m_pBackSurf->Release();
			m_pBackSurf=NULL;
		} //if
		if(m_pPrimSurf) {
			m_pPrimSurf->Release();
			m_pPrimSurf=NULL;
		} //if
		if(m_pDDraw) {
			m_pDDraw->Release();
			m_pDDraw=NULL;
		} //if
	}
}

/////////ISCREEN///////////////////////////
HRESULT STDMETHODCALLTYPE VisObj::ResetDisplay(HWND hDispWnd,int nWidth,int nHeight,int nRefRate,BOOL bFullscreen, int nFPS) {
	if(m_pBackSurf) {
		m_pBackSurf->Release();
		m_pBackSurf=NULL;
	}
	if(m_pPrimSurf) {
		m_pPrimSurf->Release();
		m_pPrimSurf=NULL;
	} //if
	m_hMainWnd = hDispWnd;
	m_bFullscreen=bFullscreen;
	m_nScreenWidth = nWidth;
	m_nScreenHeight = nHeight;
	if(bFullscreen) {
		IF_FAIL(m_pDDraw->SetCooperativeLevel(hDispWnd,DDSCL_FULLSCREEN|DDSCL_EXCLUSIVE|DDSCL_ALLOWMODEX|DDSCL_ALLOWREBOOT),
			"SetCooperativeLevel(fullscreen) failed");
		IF_FAIL(m_pDDraw->SetDisplayMode(nWidth,nHeight,32,nRefRate,0),
			"SetDisplayMode failed");
		pFlipBackSurf = &FlipBackSurfToScreen;
	}
	else { //windowed
		IF_FAIL(m_pDDraw->SetCooperativeLevel(hDispWnd,DDSCL_NORMAL),
			"SetCooperativeLevel(window) failed");
		pFlipBackSurf = &FlipBackSurfToWindow;
	}
	CreatePrimarySurface();
	AttachBackSurface();
	AttachScreenClipper();
	//init FPS
	m_nFrameWait = 1000/nFPS;
	//show IgriZdes Engine label
	ColorFill(NULL,0);
	RECT rcCentre;
	rcCentre.left = m_nScreenWidth*0.4; 
	rcCentre.top = m_nScreenHeight*0.45;
	rcCentre.right = m_nScreenWidth*0.6;
	rcCentre.bottom = m_nScreenHeight*0.55;
	DrawText(&rcCentre,L"IgriZdes Engine",0xAAAAAA,20); //0x00FF00 - green looks pretty good
	for(int i=0;i<nFPS*2;i++) //during 2 seconds show label
		UpdateScreen(); 
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::UpdateScreen() {
	list<VisObj*>::iterator it;
	for(it = m_drawnObjs.begin();it!=m_drawnObjs.end();it++) {
		(*it)->Draw();
	}
	(*pFlipBackSurf)();
	WaitClock(m_nFrameWait); //ждем до след. кадра - для сохранения опред. FPS
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::MoveCamera(POINTF* pvecD) {
	m_ptCam+=*pvecD;
	approx_coords(m_ptCam,m_nScreenWidth,m_nScreenHeight,m_rcWorldBounds);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::ShutDown() {
	list<VisObj*>::iterator it;
	list<VisObj*>::iterator itNext;
	for(it = m_visObjs.begin();it!=m_visObjs.end();) {
		itNext = it;
		itNext++;
		delete (*it);
		it = itNext;
	}
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::SetCamera(POINTF* pptCam) {
	m_ptCam=*pptCam;
	approx_coords(m_ptCam,m_nScreenWidth,m_nScreenHeight,m_rcWorldBounds);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::GetCameraPos(POINTF *pptCam) {
	*pptCam = m_ptCam;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::GetScreenRect(RECT *prcScreen) {
	prcScreen->left = 0;
	prcScreen->top = 0;
	prcScreen->right = m_nScreenWidth;
	prcScreen->bottom = m_nScreenHeight;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::GetScreenWH(POINTF *pptScreen) {
	pptScreen->x = m_nScreenWidth;
	pptScreen->y = m_nScreenHeight;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE VisObj::GetCameraRect(RECT *prcCam) {
	prcCam->left = m_ptCam.x;
	prcCam->top = m_ptCam.y;
	prcCam->right = prcCam->left + m_nScreenWidth;
	prcCam->bottom = prcCam->top + m_nScreenHeight;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE VisObj::GetCameraRBPos(POINTF *pptCam) {
	pptCam->x = m_ptCam.x+m_nScreenWidth;
	pptCam->y = m_ptCam.y+m_nScreenHeight;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::SetWorldBounds(RECT* prcBounds) {
	m_rcWorldBounds = *prcBounds;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::GetWorldBounds(RECT* prcBounds) {
	*prcBounds=m_rcWorldBounds;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::AddOrGetExistingFrameTable( int* pnID,
		 UCHAR* strPathToFile,
		 int nNeededFrameW,
		 int nNeededFrameH,
		 int nColumns,
		 int nRows,
		 BOOL bTransparent,
		 DWORD dwTranspColor) {
	*pnID = -1; //по умолчанию
	int i = 0;
	for(;i<m_frame_tables.size();i++) {
		//m_frame_tables.SelectFrameTable(i);
		FRAMETABLE* ft = m_frame_tables.at(i);
		string sName = ft->GetFileName();
		if(!sName.compare((char*)strPathToFile))
			break; //found
	}
	if(i!=m_frame_tables.size()) { //found same frame table
		*pnID = i;
		return(S_OK);
	}
	return AddFrameTable(pnID,strPathToFile,nNeededFrameW,nNeededFrameH,
		nColumns,nRows,bTransparent,dwTranspColor);
}

HRESULT STDMETHODCALLTYPE VisObj::AddFrameTable(int* pnID, //for PNG & JPG files
		UCHAR* strPathToFile,
		int nNeededFrameW, //0 - use bmp's width/nColumns
		int nNeededFrameH,
		int nColumns,
		int nRows,
		BOOL bTransparent,
		DWORD dwTranspColor) 
{
	///
	/*char buf[512];
	strcpy(buf,"AddFrameTable called: ");
	strcat(buf,(char*)strPathToFile);
	Trace(buf);*/
	////
	*pnID = -1; //по умолчанию
	//считывание картинки из файла
	corona::Image* image = corona::OpenImage((const char*)strPathToFile);//, corona::PF_R8G8B8A8);
	//потом исправлю
	sprintf(buf,"Image %s can't be opened",strPathToFile);
	IF_NOT(image,
		buf
		);
	long nPicW  = image->getWidth();
	long nPicH = image->getHeight();
	void* pixels = image->getPixels();
	corona::PixelFormat format = image->getFormat();

	// we're guaranteed that the first eight bits of every pixel is red,
	// the next eight bits is green, and so on...

	byte* pSrc = (byte*)pixels;

	//автоподсчет cols & rows (позволяет не переписывать параметры вызова функции при замене
	//картинки-таблицы кадров новой с меньшим/большим числом кадров
	//предполагается что число столбцов/рядов равно одному, а другое измерение
	//подсчитывается на основе ширины и высоты таблицы
	if(nRows==1 && nColumns==0) {
		nColumns=static_cast<int>(nPicW/nPicH);
	}
	if(nColumns==1 && nRows==0) {
		nRows=static_cast<int>(nPicH/nPicW);
	}

	////загрузка с использованием ширины и высоты самой картинки
	if(nNeededFrameW==0 && nNeededFrameH==0) {
		nNeededFrameW=nPicW/nColumns;
		nNeededFrameH=nPicH/nRows;
	}
	//разделяем картинку на кадры и скидываем в FRAMETABLE
	//подготавливаем FRAMETABLE
	FRAMETABLE *pFrameTable = new FRAMETABLE;
	RECT rcFrame = {0,0,nNeededFrameW,nNeededFrameH};
	pFrameTable->Init(rcFrame,bTransparent,dwTranspColor,(char*)strPathToFile);
	//создаем кадры
	//int num_frames = nColumns*nRows;
	long nPicFrameW = nPicW/nColumns;
	long nPicFrameH = nPicH/nRows;
	DDSURFACEDESC2 desc;
	DDRAW_INIT_STRUCT(desc);
	bool bIs32BIT = true;
	switch(format) {
		case corona::PF_R8G8B8A8:
			bIs32BIT=true;
			break;
		case corona::PF_R8G8B8:
			bIs32BIT=false;
			break;
		case corona::PF_B8G8R8:
			bIs32BIT=false;
			Trace("Format is not supported fully BGR - picture colors will be inversed:");
			Trace((char*)strPathToFile);
			break;
		default:
			Trace("Unknown format of picture:");
			Trace((char*)strPathToFile);
			return(S_FALSE);
	}
	int picStepX = 3+bIs32BIT; //24 or 32bit
	for(int j=0;j<nRows;j++) {
		for(int i=0;i<nColumns;i++) {
			//закидываем картинку в таблицу кадров
			LPDIRECTDRAWSURFACE7 pSurf;
			if(bTransparent) 
				CreateOffScreenSurface(pSurf,nPicFrameW,nPicFrameH,dwTranspColor,desc);
			else
				CreateOffScreenSurface(pSurf,nPicFrameW,nPicFrameH,desc);
			if(FAILED(pSurf->Lock(NULL,&desc,DDLOCK_WAIT,NULL))) {
				Trace("Can't lock surface for drawing while preparing frame");
				return S_FALSE;
			}
			DWORD cl = 200; //закрасим этим цветом по умолчанию
			byte *pDest = (byte *)desc.lpSurface;
			FillMemory(pDest,desc.lPitch*desc.dwHeight,cl);
			
			RECT rcNew = {i*nPicFrameW*picStepX,
				j*nPicFrameH,
				(i+1)*nPicFrameW*picStepX,
				(j+1)*nPicFrameH
			};
			//BYTE* pCurPicFrame = (BYTE*) (pSrc + rcNew.top*nPicFrameW*picStepX + rcNew.left);
			CopyByteArray(desc,pSrc,rcNew,nPicW*picStepX,bIs32BIT);
			pSurf->Unlock(NULL);
			LPDIRECTDRAWSURFACE7 pSurf2;
			if(bTransparent) 
				CreateOffScreenSurface(pSurf2,nNeededFrameW,nNeededFrameH,dwTranspColor,desc);
			else
				CreateOffScreenSurface(pSurf2,nNeededFrameW,nNeededFrameH,desc);
			RECT rcSrc = {0,0,nPicFrameW,nPicFrameH};
			RECT rcDest = {0,0,nNeededFrameW,nNeededFrameH};
			pSurf2->Blt(&rcDest,pSurf,&rcSrc,DDBLT_WAIT,NULL);
			pSurf->Release();
			pFrameTable->AddFrame(pSurf2);
			////
			/*char buf[512];
			sprintf(buf,"AddedFrame number: %i of %i",j*nColumns+i,nColumns*nRows);
			Trace(buf);*/
			////
		} //for cols
	} //for rows
	//немного прибираемся
	delete image;
	//закидываем таблицу кадров в вектор таблиц кадров
	m_frame_tables.push_back(pFrameTable);
	*pnID = m_frame_tables.size()-1;
	//Trace((char*)strPathToFile);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::AddEmptyFrameTable(
		 int* pnID,
		 int nNeededFrameW,
		 int nNeededFrameH,
		 int nColumns,
		 int nRows,
		 BOOL bTransparentFill,
		 DWORD dwFillColor) {
	*pnID = -1; //по умолчанию
	long nPicW  = nNeededFrameW * nColumns;
	long nPicH = nNeededFrameH * nRows;

	//разделяем картинку на кадры и скидываем в FRAMETABLE
	//подготавливаем FRAMETABLE
	FRAMETABLE *pFrameTable = new FRAMETABLE;
	RECT rcFrame = {0,0,nNeededFrameW,nNeededFrameH};
	pFrameTable->Init(rcFrame,bTransparentFill,dwFillColor); //extract method in FRAMETABLE
	//создаем кадры
	//int num_frames = nColumns*nRows;
	long nPicFrameW = nNeededFrameW;
	long nPicFrameH = nNeededFrameH;
	DDSURFACEDESC2 desc;
	DDRAW_INIT_STRUCT(desc);
	bool bIs32BIT = true;
	int picStepX = 3+bIs32BIT; //24 or 32bit
	for(int j=0;j<nRows;j++) {
		for(int i=0;i<nColumns;i++) {
			//закидываем картинку в таблицу кадров
			LPDIRECTDRAWSURFACE7 pSurf;
			if(bTransparentFill) 
				CreateOffScreenSurface(pSurf,nPicFrameW,nPicFrameH,dwFillColor,desc);
			else
				CreateOffScreenSurface(pSurf,nPicFrameW,nPicFrameH,desc);
			//color fill all the surface:
			m_blitFX.dwFillColor=dwFillColor;
			IF_FAIL(pSurf->Blt(NULL,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&m_blitFX),
				"VisObj::AddEmptyFrameTable() Failed to blit rectangle");
			//add frame to frame table
			pFrameTable->AddFrame(pSurf);
		} //for cols
	} //for rows
	//закидываем таблицу кадров в вектор таблиц кадров
	m_frame_tables.push_back(pFrameTable);
	*pnID = m_frame_tables.size()-1;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::AddBMPFrameTable(int* pnID,
		UCHAR* strPathToFile,
		int nNeededFrameW, //0 - use bmp's width/nColumns
		int nNeededFrameH,
		int nColumns,
		int nRows,
		BOOL bTransparent,
		DWORD dwTranspColor) 
{
	////
	/*char buf[512];
	strcpy(buf,"AddFrameTable called: ");
	strcat(buf,(char*)strPathToFile);
	Trace(buf);*/
	////
	//считывание картинки из файла
	BITMAPFILEHEADER bitmapfileheader;  // this contains the bitmapfile header
	BITMAPINFOHEADER bitmapinfoheader;  // this is all the info including the palette
	UCHAR            *buffer;           // this is a POINTFer to the data
	
	fstream inF((char*)strPathToFile,ios::in|ios::binary);
	inF.read((char*)&bitmapfileheader,sizeof(BITMAPFILEHEADER));
	inF.read((char*)&bitmapinfoheader,sizeof(BITMAPINFOHEADER));
	inF.seekg(-(long)(bitmapinfoheader.biSizeImage),ios::end);
	//inF.seekg(-(int)(bitmapinfoheader.biSizeImage),ios::end);
	buffer = (UCHAR *)malloc(bitmapinfoheader.biSizeImage);
	inF.read((char*)buffer,bitmapinfoheader.biSizeImage);
	inF.close();
	int nBmpWidth = bitmapinfoheader.biWidth;
	int nBmpHeight = bitmapinfoheader.biHeight;

	//загрузка с использованием ширины и высоты самой картинки
	if(nNeededFrameW==0 && nNeededFrameH==0) {
		nNeededFrameW=nBmpWidth/nColumns;
		nNeededFrameH=nBmpHeight/nRows;
	}

	//разделяем картинку на кадры и скидываем в FRAMETABLE
	//подготавливаем FRAMETABLE
	FRAMETABLE *pFrameTable = new FRAMETABLE;
	RECT rcFrame = {0,0,nNeededFrameW,nNeededFrameH};
	pFrameTable->Init(rcFrame,bTransparent,dwTranspColor,(char*)strPathToFile);
	//создаем кадры
	//int num_frames = nColumns*nRows;
	int nBmpFrameW = nBmpWidth/nColumns;
	int nBmpFrameH = nBmpHeight/nRows;
	DDSURFACEDESC2 desc;
	DDRAW_INIT_STRUCT(desc);
	HRESULT hRes=S_FALSE;
	for(int j=0;j<nRows;j++) {
		for(int i=0;i<nColumns;i++) {
			//закидываем картинку в таблицу кадров
			pFrameTable->AddFrame(
				CreateSurfFromFBuffer(
					bitmapinfoheader,buffer,i*nBmpFrameW,j*nBmpFrameH,nBmpFrameW,nBmpFrameH,
					desc,nNeededFrameW,nNeededFrameH,bTransparent,dwTranspColor)
					);
			////
			/*char buf[512];
			sprintf(buf,"AddedFrame number: %i of %i",j*nColumns+i,nColumns*nRows);
			Trace(buf);*/
			////
		}
	}
	//немного прибираемся
	free(buffer);
	buffer = NULL;
	//закидываем таблицу кадров в вектор таблиц кадров
	m_frame_tables.push_back(pFrameTable);
	*pnID = m_frame_tables.size()-1;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::AddAngledTables(
		int* pnID, 
	    int* pidSrcFrameTable,
		float fTurnAngle,
		float fNeededAngleOfFirstTable)
{
	////
	/*char buf[512];
	sprintf(buf,"AddAngledTables called, number is: %i, width: %i",
		*pidSrcFrameTable,m_frame_tables.at(*pidSrcFrameTable)->GetFrameRect().right);
	Trace(buf);*/
	////
	//создаем пачку таблиц кадров
	FRAMETABLEPACK* pTablePack = new FRAMETABLEPACK;
	//теперь создаем каждый кадр (поворотом кадров исходной таблицы pidSrcFrameTable)
	pTablePack->SetTurnAngle(fTurnAngle);
	FRAMETABLE* pSrcTable = m_frame_tables.at(*pidSrcFrameTable); //исх таблица,
	//ее будем поворачивать
	int nDestTablesCount = (int)360/fTurnAngle; //число необходимых повернутых таблиц
	//при заданном угле поворота
	DDSURFACEDESC2 desc; //needed
	DDRAW_INIT_STRUCT(desc);
	HRESULT hRes=S_FALSE;
	for(int DestTableNo =0;DestTableNo<nDestTablesCount;DestTableNo++) {
		//создаем таблицу
		FRAMETABLE* pDestTable = new FRAMETABLE;
		pDestTable->Init(pSrcTable->GetFrameRect(),pSrcTable->CheckTransparency(),pSrcTable->GetTranspColor(),"");
		for(int FrameNo=0;FrameNo<pSrcTable->GetFrameCount();FrameNo++) {
			//создаем кадр для таблицы
			LPDIRECTDRAWSURFACE7 pSurf;
			//готовим поверхность и ее описание
			if(pSrcTable->CheckTransparency())
				hRes=CreateOffScreenSurface(
					pSurf,
					pSrcTable->GetFrameRect().right,
					pSrcTable->GetFrameRect().bottom,
					pSrcTable->GetTranspColor(),
					desc);
			else //no transp
				hRes=CreateOffScreenSurface(
					pSurf,
					pSrcTable->GetFrameRect().right,
					pSrcTable->GetFrameRect().bottom,
					desc);
			IF_FAIL(hRes,
				"AddAngledTables: Failed to create frame-surface for new table");
			//заполняем кадр прозрачным цветом
			m_blitFX.dwFillColor=0;
			if(pSrcTable->CheckTransparency())
				m_blitFX.dwFillColor=pSrcTable->GetTranspColor();
			IF_FAIL(pSurf->Blt(&pSrcTable->GetFrameRect(),NULL,NULL,
				DDBLT_WAIT|DDBLT_COLORFILL,&m_blitFX),
				"AddAngledTables: Failed to fill with transparent color dest frame-surface");
			//поворачиваем исходный кадр и записываем его в подготовленный
			POINTF ptDest = {0,0};
			DrawRotated(pSurf,&desc,
				pSrcTable->GetFrameSurf(FrameNo),pSrcTable->GetFrameDesc_locked(),
				pSrcTable->GetFrameRect(),ptDest,pSrcTable->GetFrameRect(),
				DestTableNo*fTurnAngle+fNeededAngleOfFirstTable,pSrcTable->CheckTransparency(),pSrcTable->GetTranspColor());
			//кадр готов - помещаем в FRAMETABLE
			pDestTable->AddFrame(pSurf);
			////
			/*char buf[512];
			sprintf(buf,"Rotated and AddedFrame number: %i of %i",FrameNo,pSrcTable->GetFrameCount());
			Trace(buf);*/
			////
		} //для всех кадров
		//таблица кадров готова - помещаем ее в FRAMETABLEPACK
		pTablePack->AddFrameTable(pDestTable);
		////
		/*char buf[512];
		sprintf(buf,"AddedTable number: %i of %i",DestTableNo,nDestTablesCount);
		Trace(buf);*/
		////
	} //для всех повернутых таблиц
	//добавляем созданную пачку таблиц в вектор, чтоб потом можно было работать с ним, зная индекс или указатель
	m_frame_table_packs.push_back(pTablePack);
	*pnID = m_frame_table_packs.size()-1;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::FreeAllFrameTables() {
	for(int i=m_frame_tables.size()-1;i>=0;i--)
		delete m_frame_tables.at(i);
	m_frame_tables.resize(0);
	return(S_OK);
}
HRESULT STDMETHODCALLTYPE VisObj::FreeAllAngledTables() {
	for(int i=m_frame_table_packs.size()-1;i>=0;i--)
		delete m_frame_table_packs.at(i);
	m_frame_table_packs.resize(0);
	return(S_OK);
}

////IINPUT//////////////////////////
HRESULT STDMETHODCALLTYPE VisObj::CheckKeyDown(int vKey,BOOL* bRes) {
	*bRes = (GetAsyncKeyState(vKey)&0x80000)?1:0;
	return(S_OK);
}
HRESULT STDMETHODCALLTYPE VisObj::CheckKeyUp(int vKey,BOOL* bRes){
	*bRes = (GetAsyncKeyState(vKey)&0x80000)?0:1;
	return(S_OK);
}
////IDRAW///////////////////////////
HRESULT STDMETHODCALLTYPE VisObj::Draw() {
	//if(m_bHideFrame) return(S_OK);
	RECT rcSrc = m_pFrameTable->GetFrameRect();
	RECT rcDest = GetRect(m_ptCoords-m_ptCam,m_nFrameW,m_nFrameH);
	int nCurFrame = m_Anims2[m_nCurAnim]->GetCurFrameInd();
	if(m_pFrameTable->CheckTransparency()) {//с прозрачностью?
		if(FAILED(m_pBackSurf->Blt(&rcDest,m_pFrameTable->GetFrameSurf(nCurFrame)
			,&rcSrc,DDBLT_WAIT|DDBLT_KEYSRC,NULL)))
				Trace("Draw: Failed to blit");
	}
	else
		if(FAILED(m_pBackSurf->Blt(&rcDest,m_pFrameTable->GetFrameSurf(nCurFrame)
			,&rcSrc,DDBLT_WAIT,NULL)))
				Trace("Draw: Failed to blit");
	//смена кадра
	if(m_bFreeze) 
		return(S_OK); //не нужно сменять кадр
	int nCurTime=GetClock();
	int nFrameTime = m_Anims2[m_nCurAnim]->GetFrameTime();
	if(m_tmLastRefresh+nFrameTime<nCurTime) {
		m_tmLastRefresh=nCurTime;
		m_Anims2[m_nCurAnim]->Flip();
	}
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::Show() {
	if(!IsVisible()) {
		m_drawnObjs.push_back(this);
		m_itDrawnObj = m_drawnObjs.end();
		m_itDrawnObj--;
		return(S_OK);
	}
	return(S_OK);
}  

HRESULT STDMETHODCALLTYPE VisObj::Hide() {
	if(IsVisible()) {
		m_drawnObjs.erase(m_itDrawnObj);
		m_itDrawnObj = m_drawnObjs.end();
		return(S_OK);
	}
	return(S_OK);
}

//Добавление объекта в список вывода с соответствующей глубиной. Глубина 0 означает, что
//объект будет дальше всех от нас. Чем больше глубина, тем ближе объект к нам.
//Используйте, когда в процессе работы с графикой нужно добавить элемент не
//на передний план. Глубина - значение относительное и макс. глубина равна числу объектов
//в списке вывода.
HRESULT STDMETHODCALLTYPE VisObj::ShowOn(int depth) {
	Hide(); //for safety
	list<VisObj*>::iterator it = m_drawnObjs.begin();
	if(depth>m_drawnObjs.size())
		depth = m_drawnObjs.size();
	while(depth) { it++; depth--;};
	m_itDrawnObj = m_drawnObjs.insert(it,this);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::CheckVisible(BOOL* pRes) {
	*pRes = IsVisible();
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::GetPixel(POINTF* pptWhere,DWORD *pdwPixColor) {
	RECT rcCurFrame={0,0,0,0};
	int nW = m_pFrameTable->GetFrameRect().right;
	int nH = m_pFrameTable->GetFrameRect().bottom;
	int nPos = (rcCurFrame.top+pptWhere->y)*m_pFrameTable->GetPitch32_locked()
		+rcCurFrame.left+pptWhere->x;
	*pdwPixColor=m_pFrameTable->GetVidBuf_locked()[nPos];
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::GetTranspColor(DWORD *pdwColor) {
	*pdwColor=m_pFrameTable->GetTranspColor();
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::Lock() {
	IF_FAIL(m_pFrameTable->Lock(m_Anims2[m_nCurAnim]->GetCurFrameInd()),
		"Failed to lock frame-surface!");
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::Unlock() {
	m_pFrameTable->GetFrameSurf(m_Anims2[m_nCurAnim]->GetCurFrameInd())->Unlock(NULL);
	return(S_OK);
}

//////////////////IHUD/////////////////////////////

HRESULT STDMETHODCALLTYPE VisObj::DrawText(LPRECT prcTextBox,LPWSTR strText,DWORD dwColor,int nHeight) {
	HDC hDC;
	IF_FAIL(m_pBackSurf->GetDC(&hDC),
		"DrawText: Failed to get DC from directX");
	SetTextColor(hDC,dwColor);
	SetBkMode(hDC,TRANSPARENT);
	LOGFONT logfont;
	memset(&logfont,0,sizeof(logfont));
	logfont.lfHeight=nHeight;
	logfont.lfWidth=(int)nHeight*0.5;
	
	HFONT hNewFont = CreateFontIndirect(&logfont);
	HFONT hOldFont = (HFONT)SelectObject(hDC,hNewFont);
	DrawTextEx(hDC,strText,wcslen(strText),prcTextBox,DT_LEFT|DT_NOCLIP|DT_WORDBREAK,NULL);
	SelectObject(hDC,hOldFont);
	DeleteObject(hNewFont);

	m_pBackSurf->ReleaseDC(hDC);
	return(S_OK);
}



HRESULT STDMETHODCALLTYPE VisObj::AddText(LPRECT prcTextBox,UCHAR* strText,DWORD dwColor,int nHeight, DWORD dwFlags) {
	LPSURF pOutSurf = GetCurFrameSurf();
	HDC hDC;
	IF_FAIL(pOutSurf->GetDC(&hDC),
		"DrawText: Failed to get DC from directX");
	SetTextColor(hDC,dwColor);
	SetBkMode(hDC,TRANSPARENT);
	LOGFONT logfont;
	memset(&logfont,0,sizeof(logfont));
	logfont.lfHeight=nHeight;
	logfont.lfWidth=(int)nHeight*0.5;
	
	HFONT hNewFont = CreateFontIndirect(&logfont);
	HFONT hOldFont = (HFONT)SelectObject(hDC,hNewFont);
	wstring wstemp = tows(strText);
	LPWSTR txt = (LPWSTR)wstemp.c_str();
	DrawTextEx(hDC,txt,wcslen(txt),prcTextBox,dwFlags|DT_NOCLIP|DT_WORDBREAK,NULL);
	SelectObject(hDC,hOldFont);
	DeleteObject(hNewFont);

	pOutSurf->ReleaseDC(hDC);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::AddLine(POINTF* ppt1,POINTF *ppt2,DWORD DWORD,int nWidth) {
	LPSURF pOutSurf = GetCurFrameSurf();
	HDC hDC;
	IF_FAIL(pOutSurf->GetDC(&hDC),
		"DrawLine: Failed to get DC from directX");

	HPEN hNewPen = CreatePen(PS_SOLID,nWidth,DWORD);
	HPEN hOldPen = (HPEN) SelectObject(hDC,hNewPen);
	MoveToEx(hDC,ppt1->x,ppt1->y,NULL);
	LineTo(hDC,ppt2->x,ppt2->y);
	SelectObject(hDC,hOldPen);
	DeleteObject(hNewPen);

	pOutSurf->ReleaseDC(hDC);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::AddBtnView(RECT rcBounds, int nBorderWidth,
			DWORD clBack, DWORD clBorder, UCHAR* caption, 
			DWORD clFont, int nFontHeight, int nFontFlags) {
		RECT rcInner = {rcBounds.left + nBorderWidth, rcBounds.top + nBorderWidth,
			rcBounds.right - nBorderWidth, rcBounds.bottom - nBorderWidth};
		int wBorder2 = int(nBorderWidth /2);
		AddColorFill(&rcInner,clBack);
		AddHLine(0,rcBounds.right,wBorder2,nBorderWidth,clBorder);
		AddHLine(0,rcBounds.right,rcBounds.bottom-wBorder2,nBorderWidth,clBorder);
		AddVLine(wBorder2,0,rcBounds.bottom,nBorderWidth,clBorder);
		AddVLine(rcBounds.right-wBorder2,0,rcBounds.bottom,nBorderWidth,clBorder);
		AddText(&rcInner,(UCHAR*)caption,clFont,nFontHeight,nFontFlags);
		return(S_OK);
}

//DT_CENTER, DT_VCENTER

HRESULT STDMETHODCALLTYPE VisObj::AddColorFill(RECT *pRect, DWORD dwColor) {
	m_blitFX.dwFillColor=dwColor;
	IF_FAIL(GetCurFrameSurf()->Blt(pRect,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&m_blitFX),
		"Failed to blit rectangle");
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::AddHLine(int x0,int x1, int y,int nWidth,DWORD dwColor) {
	int nHalf = nWidth / 2;
	int nRemains = nWidth % 2;
	RECT rc = {x0,y-nHalf,x1,y+nHalf - 1 + nRemains};
	AddColorFill(&rc,dwColor);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::AddVLine(int x,int y0, int y1,int nWidth,DWORD dwColor) {
	int nHalf = nWidth / 2;
	int nRemains = nWidth % 2;
	RECT rc = {x-nHalf,y0,x+nHalf - 1 + nRemains,y1};
	AddColorFill(&rc,dwColor);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::DrawLine(POINTF* ppt1,POINTF *ppt2,DWORD DWORD,int nWidth) {
	HDC hDC;
	IF_FAIL(m_pBackSurf->GetDC(&hDC),
		"DrawLine: Failed to get DC from directX");

	HPEN hNewPen = CreatePen(PS_SOLID,nWidth,DWORD);
	HPEN hOldPen = (HPEN) SelectObject(hDC,hNewPen);
	MoveToEx(hDC,ppt1->x,ppt1->y,NULL);
	LineTo(hDC,ppt2->x,ppt2->y);
	SelectObject(hDC,hOldPen);
	DeleteObject(hNewPen);

	m_pBackSurf->ReleaseDC(hDC);
	return(S_OK);
}  

HRESULT STDMETHODCALLTYPE VisObj::DrawVLine(int x,int y0, int y1,int nRad,DWORD dwColor) {
	RECT rc = {x-nRad,y0,x+nRad,y1};
	ColorFill(&rc,dwColor);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::DrawHLine(int x0,int x1, int y,int nRad,DWORD dwColor) {
	RECT rc = {x0,y-nRad,x1,y+nRad};
	ColorFill(&rc,dwColor);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::ColorFill(RECT *pRect, DWORD dwColor) {
	m_blitFX.dwFillColor=dwColor;
	IF_FAIL(m_pBackSurf->Blt(pRect,NULL,NULL,DDBLT_WAIT|DDBLT_COLORFILL,&m_blitFX),
		"Failed to blit rectangle");
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::DrawPoint(POINTF *ppt,DWORD dwColor,int nWidth) {
	int nW2 = nWidth>>1;
	RECT rc = {ppt->x-nW2,ppt->y-nW2,ppt->x+nW2,ppt->y+nW2};
	ColorFill(&rc,dwColor);
	return(S_OK);
}

//////////////////IAngledDraw//////////////////////
HRESULT STDMETHODCALLTYPE VisObj::UseExistingAngledTables(int* pnAngledTablesPack) {
	m_pFrameTablePack = m_frame_table_packs.at(*pnAngledTablesPack);
	m_pFrameTablePack->SelectFrameTable(0);
	m_pFrameTable = m_pFrameTablePack->GetCurFrameTable();
	m_nFrameW = m_pFrameTable->GetFrameRect().right;
	m_nFrameH = m_pFrameTable->GetFrameRect().bottom;
	return(S_OK);
}
HRESULT STDMETHODCALLTYPE VisObj::UseExistingAngledTablesAndSimpleAnim(int* pnAngledTablesPack, int nNumStartTable) {
	UseExistingAngledTables(pnAngledTablesPack);
	int nMaxTables;
	GetNumTables(&nMaxTables);
	SelectTable(nNumStartTable%nMaxTables);
	return CreateSimpleAnim();
}
HRESULT STDMETHODCALLTYPE VisObj::SelectTableByVector( POINTF *pvec) { 
	float fDrawAngle=0;
	float dx=pvec->x,
		dy=pvec->y;
	if(IsNil(dx))
		fDrawAngle=((dy>0)?90:270);
	else {
		fDrawAngle = atan(dy/dx)/PI_DIV_180; 
		if(dx<0) //особенности atan
			fDrawAngle+=180;
		if(dx>0 && dy<0)
			fDrawAngle+=360;
	}
	SelectTableByAngle(fDrawAngle);
	return(S_OK);
}
HRESULT STDMETHODCALLTYPE VisObj::SelectTable( int nNo) {
	m_pFrameTablePack->SelectFrameTable(nNo);
	m_pFrameTable = m_pFrameTablePack->GetCurFrameTable();
	return(S_OK);
}
HRESULT STDMETHODCALLTYPE VisObj::GetNumTables( int* pnNumTables) { 
	*pnNumTables=m_pFrameTablePack->GetFrameTablesCount();
	return(S_OK);
}
HRESULT STDMETHODCALLTYPE VisObj::SelectTableByAngle( float fAngle) { 
	int nInd = sround(fAngle/(m_pFrameTablePack->GetTurnAngle()));
	nInd = nInd%m_pFrameTablePack->GetFrameTablesCount();
	if(nInd<0)
		nInd = m_pFrameTablePack->GetFrameTablesCount() + nInd;
	SelectTable(nInd);
	return(S_OK);
}

//////////IANIMATION/////////////////////
HRESULT STDMETHODCALLTYPE VisObj::SetFrameTime(int nAnimInd, int msTime) {
	m_Anims2[nAnimInd]->SetFrameTime(msTime);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::UseExistingFrameTable(int* pnID) {
	m_pFrameTable = m_frame_tables.at(*pnID);
	m_nFrameW = m_pFrameTable->GetFrameRect().right;
	m_nFrameH = m_pFrameTable->GetFrameRect().bottom;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::CreateAnim(int nAnimInd, int nFramesAmount,int *arrFrameInds) { 
	if(m_Anims2[nAnimInd]) delete m_Anims2[nAnimInd];
	Anim2 *newAnim = new Anim2();
	newAnim->Create(nFramesAmount,arrFrameInds);
	m_Anims2[nAnimInd] = newAnim;
	return(S_OK); 
}

HRESULT STDMETHODCALLTYPE VisObj::SetAnimType( int nAnimInd, int nPlayType) { 
	m_Anims2[nAnimInd]->SetAnimType(nPlayType);
	return(S_OK); 
}

HRESULT STDMETHODCALLTYPE VisObj::SelectActiveAnim( int nAnimInd) { 
	m_nCurAnim=nAnimInd;
	m_Anims2[nAnimInd]->Init();
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::SelectActiveFrame(int nFrameInd) { 
	 m_Anims2[m_nCurAnim]->GoToFrame(nFrameInd);
	 return(S_OK); 
}

HRESULT STDMETHODCALLTYPE VisObj::FreezeFrame(BOOL bFreeze) { 
	m_bFreeze=bFreeze;
	return(S_OK); 
}

HRESULT STDMETHODCALLTYPE VisObj::GetCurAnimInd(int *pnCurAnimInd) {
	*pnCurAnimInd=m_nCurAnim;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::CheckEndAnim(BOOL *pbEndAnim) {
	*pbEndAnim = m_Anims2[m_nCurAnim]->CheckEndAnim();
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::CheckHalfAnimPlayed(BOOL *pbHalfAnim) {
	*pbHalfAnim = m_Anims2[m_nCurAnim]->CheckHalfAnimPlayed();
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::GetFrameAmountInTable(int *pnFrames) {
	*pnFrames = m_pFrameTable->GetFrameCount();
	return(S_OK);
}
//for fast & easy use
HRESULT STDMETHODCALLTYPE VisObj::CreateSimpleAnim() {
	int nFrames;
	GetFrameAmountInTable(&nFrames);
	int *arrAnim = new int[nFrames];
	for(int j=0;j<nFrames;j++)
		arrAnim[j]=j;
	CreateAnim(0,nFrames,arrAnim);
	delete[] arrAnim;
	return(S_OK);
}
HRESULT STDMETHODCALLTYPE VisObj::CreateLinearAnim(int nAnimInd,int nStartFrame,int nEndFrame) {
	int sz = nEndFrame-nStartFrame+1;
	int *arrAnim = new int[sz];
	for(int i=0;i<sz;i++)
		arrAnim[i]=i;
	CreateAnim(nAnimInd,sz,arrAnim);
	delete arrAnim;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::LoadSimpleAnim(
	 UCHAR* strPathToFile,
	 int nNeededFrameW,
	 int nNeededFrameH,
	 int nColumns,
	 int nRows,
	 BOOL bTransparent,
	 DWORD dwTranspColor) 
{
	LoadFrameTable(strPathToFile,
	 nNeededFrameW,
	 nNeededFrameH,
	 nColumns,
	 nRows,
	 bTransparent,
	 dwTranspColor);
	return CreateSimpleAnim();
}

HRESULT STDMETHODCALLTYPE VisObj::LoadFrameTable(
		 UCHAR* strPathToFile,
		 int nNeededFrameW,
		 int nNeededFrameH,
		 int nColumns,
		 int nRows,
		 BOOL bTransparent,
		 DWORD dwTranspColor) {
	int nTemp;
	AddFrameTable(&nTemp,strPathToFile,nNeededFrameW,nNeededFrameH,
		nColumns,nRows,bTransparent,dwTranspColor);
	UseExistingFrameTable(&nTemp);
	return S_OK;
}
HRESULT STDMETHODCALLTYPE VisObj::UseExistingFrameTableAsSimpleAnim(int* pnID) {
	UseExistingFrameTable(pnID);
	return CreateSimpleAnim();
}

HRESULT STDMETHODCALLTYPE VisObj::LoadOrUseExistingSimpleAnim(
	 UCHAR* strPathToFile,
	 int nNeededFrameW,
	 int nNeededFrameH,
	 int nColumns,
	 int nRows,
	 BOOL bTransparent,
	 DWORD dwTranspColor) {
	LoadOrUseExistingFrameTable(strPathToFile,nNeededFrameW,nNeededFrameH,
		nColumns,nRows,bTransparent,dwTranspColor);
	return CreateSimpleAnim();
}
HRESULT STDMETHODCALLTYPE VisObj::LoadOrUseExistingFrameTable(
	 UCHAR* strPathToFile,
	 int nNeededFrameW,
	 int nNeededFrameH,
	 int nColumns,
	 int nRows,
	 BOOL bTransparent,
	 DWORD dwTranspColor) {
	int nTemp;
	AddOrGetExistingFrameTable(&nTemp,strPathToFile,
	 nNeededFrameW,
	 nNeededFrameH,
	 nColumns,
	 nRows,
	 bTransparent,
	 dwTranspColor);
	UseExistingFrameTable(&nTemp);
	return(S_OK);
}

//////IPARAMS//////////////////////
HRESULT STDMETHODCALLTYPE VisObj::SetPos(POINTF *pptPos) {
	m_ptCoords = *pptPos;
	return(S_OK); 
}

HRESULT STDMETHODCALLTYPE VisObj::Move(POINTF *pvecShift) {
	m_ptCoords+=*pvecShift;
	return(S_OK); 
}

HRESULT STDMETHODCALLTYPE VisObj::Resize(int nNewWidth, int nNewHeight) {
	m_nFrameW=nNewWidth;
	m_nFrameH=nNewHeight;
	return(S_OK); 
}

HRESULT STDMETHODCALLTYPE VisObj::GetSmallestRad( float *pfRad) {
	*pfRad=(double)(min((m_nFrameW>>1),(m_nFrameH>>1)));
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::GetBiggestRad(float *pfRad) {
	*pfRad=(double)(max((m_nFrameW>>1),(m_nFrameH>>1)));
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::GetCoordsRect(RECT* rcCoords) {
	*rcCoords = GetRect(m_ptCoords,m_nFrameW,m_nFrameH);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::GetCoordsWHRect(RECT* rcCoordsWH) {
	*rcCoordsWH = GetRectWH(m_ptCoords,m_nFrameW,m_nFrameH);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::GetCoordsPt(POINTF* ptCoords) {
	*ptCoords = m_ptCoords;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::GetCentreCoordsPt(POINTF* ptCentreCoords) {
	*ptCentreCoords = m_ptCoords + Vec(m_nFrameW,m_nFrameH)*0.5;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::GetWidthAndHeight(POINTF *pwhFrame) {
	pwhFrame->x=m_nFrameW;
	pwhFrame->y=m_nFrameH;
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::GetHalfWidthAndHeight(POINTF *pwhFrame) {
	pwhFrame->x=m_nFrameW>>1;
	pwhFrame->y=m_nFrameH>>1;
	return(S_OK);
}

//UNSAFE!
HRESULT STDMETHODCALLTYPE VisObj::GetLX(int *pnLX) {*pnLX=m_ptCoords.x;return(S_OK);}
HRESULT STDMETHODCALLTYPE VisObj::GetCX(int *pnCX) {*pnCX=m_ptCoords.x+(m_nFrameW>>1); return(S_OK);}
HRESULT STDMETHODCALLTYPE VisObj::GetRX(int *pnRX) {*pnRX=m_ptCoords.x+m_nFrameW; return(S_OK);}
HRESULT STDMETHODCALLTYPE VisObj::GetTY(int *pnTY) {*pnTY=m_ptCoords.y;return(S_OK);}
HRESULT STDMETHODCALLTYPE VisObj::GetCY(int *pnCY){*pnCY=m_ptCoords.y+(m_nFrameH>>1); return(S_OK);}
HRESULT STDMETHODCALLTYPE VisObj::GetBY(int *pnBY){*pnBY=m_ptCoords.y+m_nFrameH; return(S_OK);}
HRESULT STDMETHODCALLTYPE VisObj::GetWidth( int *pnWidth) {*pnWidth=m_nFrameW;return(S_OK);}
HRESULT STDMETHODCALLTYPE VisObj::GetHeight(int *pnHeight){*pnHeight=m_nFrameH;return(S_OK);}

/////////IUnknown//
STDMETHODIMP VisObj::QueryInterface(REFIID idInterface, void **ppInterface) {
	*ppInterface=NULL;
	if(idInterface == IID_IUnknown)
		*ppInterface = (IUnknown*)(IScreen*)this;
	if(idInterface == IID_IScreen)
		*ppInterface = (IScreen*)this;
	if(idInterface == IID_IInput)
		*ppInterface = (IInput*)this;
	if(idInterface == IID_IDraw)
		*ppInterface = (IDraw*)this;
	if(idInterface == IID_IAngledDraw)
		*ppInterface = (IAngledDraw*)this;
	if(idInterface == IID_IAnim)
		*ppInterface = (IAnim*)this;
	if(idInterface == IID_IParams)
		*ppInterface = (IParams*)this;
	if(idInterface == IID_IHUD)
		*ppInterface = (IHUD*)this;
	if(*ppInterface) {
		((IUnknown*)*ppInterface)->AddRef();
		return(S_OK);
	}
	if(m_nRefCount<=0) delete this;
	return(E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) VisObj::AddRef() {return(++m_nRefCount);}
	
STDMETHODIMP_(ULONG) VisObj::Release() {
	m_nRefCount--;
	if(m_nRefCount<=0)
		delete this;
	return(m_nRefCount);
}

///////////////PROCEDURE STUFF////////////////////////////////////////

HRESULT STDMETHODCALLTYPE VisObj::FlipBackSurfToScreen() {
	IF_FAIL(m_pPrimSurf->Flip(NULL,DDFLIP_WAIT),
		"Cannot flip back surface to primary - fullscreen");
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::FlipBackSurfToWindow() {
	static RECT rcWnd;
	static RECT rcClient;
	GetWindowRect(m_hMainWnd, &rcWnd);
	GetClientRect(m_hMainWnd,&rcClient);
	rcWnd.top=rcWnd.bottom-rcClient.bottom-5; //5 - каемка окна
	rcWnd.left=rcWnd.right-rcClient.right-5;
	IF_FAIL(m_pPrimSurf->Blt(&rcWnd,m_pBackSurf,NULL,DDBLT_WAIT,NULL),
			"Cannot flip back surface to primary - windowed");
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::CreatePrimarySurface() {
	if(m_bFullscreen) {
		m_SurfDesc.dwFlags=DDSD_CAPS|DDSD_BACKBUFFERCOUNT; //"правильное" поле
		m_SurfDesc.dwBackBufferCount=1;
		m_SurfDesc.ddsCaps.dwCaps=DDSCAPS_PRIMARYSURFACE|DDSCAPS_COMPLEX|DDSCAPS_FLIP;
	} //Fullscreen
	else {
		m_SurfDesc.dwFlags=DDSD_CAPS; //"правильное" поле
		m_SurfDesc.dwBackBufferCount=0;
		m_SurfDesc.ddsCaps.dwCaps=DDSCAPS_PRIMARYSURFACE;
	} //Windowed
	
	IF_FAIL(m_pDDraw->CreateSurface(&m_SurfDesc,&m_pPrimSurf,NULL),
		"CreatePrimarySurface failed");
	return(S_OK);
}
	
HRESULT STDMETHODCALLTYPE VisObj::CreateOffScreenSurface(LPDIRECTDRAWSURFACE7& pDestSurf,
									 int nWidth, int nHeight, 
									 int nTranspColor,
									 DDSURFACEDESC2& DestSurfDescr) 
{
	DDRAW_INIT_STRUCT(DestSurfDescr);

	DestSurfDescr.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_CKSRCBLT;
	DestSurfDescr.dwWidth = nWidth;
	DestSurfDescr.dwHeight = nHeight;
	DestSurfDescr.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
	//прозрачность
	DestSurfDescr.ddckCKSrcBlt.dwColorSpaceLowValue=nTranspColor;
	DestSurfDescr.ddckCKSrcBlt.dwColorSpaceHighValue=nTranspColor;

	HRESULT hRes=S_FALSE;
	if(FAILED(m_pDDraw->CreateSurface(&DestSurfDescr,&pDestSurf,NULL))) {
		DestSurfDescr.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
		hRes=m_pDDraw->CreateSurface(&DestSurfDescr,&pDestSurf,NULL);
		IF_FAIL(hRes,
			"CreateSurface(video & system memory) with transparency failed!");
		//Trace("Warning: Offscreen surface with transparency created in system memory");
	}
	return(hRes);
}

HRESULT STDMETHODCALLTYPE VisObj::CreateOffScreenSurface(LPDIRECTDRAWSURFACE7& pDestSurf,
									 int nWidth, int nHeight, 
									 DDSURFACEDESC2& DestSurfDescr) 
{
	DDRAW_INIT_STRUCT(DestSurfDescr);

	DestSurfDescr.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	DestSurfDescr.dwWidth = nWidth;
	DestSurfDescr.dwHeight = nHeight;
	DestSurfDescr.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;

	HRESULT hRes=S_FALSE;
	if(FAILED(m_pDDraw->CreateSurface(&DestSurfDescr,&pDestSurf,NULL))) {
		DestSurfDescr.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
		hRes=m_pDDraw->CreateSurface(&DestSurfDescr,&pDestSurf,NULL);
		IF_FAIL(hRes,
			"CreateSurface(video & system memory) without transparency failed!");
		//Trace("Warning: Offscreen surface without transparency created in system memory");
	}
	return(hRes);
}

HRESULT STDMETHODCALLTYPE VisObj::AttachBackSurface() {
	if(m_bFullscreen) {
		m_SurfDesc.dwFlags=DDSD_CAPS;
		m_SurfDesc.ddsCaps.dwCaps=DDSCAPS_BACKBUFFER;
		IF_FAIL(m_pPrimSurf->GetAttachedSurface(&m_SurfDesc.ddsCaps,&m_pBackSurf),
			"GetAttachedSurface(fullscreen) failed");
	} //Fullscreen
	else {
		// must be windowed, so create a double buffer that will be blitted
		// rather than flipped as in full screen mode
		IF_FAIL(CreateOffScreenSurface(m_pBackSurf,m_nScreenWidth,m_nScreenHeight,0,m_SurfDesc),
			"Create backbuffer as offscreen surface for window blitting failed!");
	} //Windowed
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::AttachScreenClipper() {
	AttachBackBufClipper_screen_bounds();
	if(!m_bFullscreen) //дополнительно, клиппер окна
		AttachWindowClipper_window_bounds();
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::AttachBackBufClipper_screen_bounds() {
	LPDIRECTDRAWCLIPPER pClipper=NULL;
	LPRGNDATA pRegionData;
	IF_FAIL(m_pDDraw->CreateClipper(0,&pClipper,NULL),
		"Failed to create clipper");
	
	pRegionData=(LPRGNDATA)malloc(sizeof(RGNDATAHEADER)+sizeof(RECT));

	IF_FAIL(m_pBackSurf->Lock(NULL,&m_SurfDesc,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL),
		"m_pBackSurf->Lock failed");

	RECT rcList[1] = {{0,0,m_SurfDesc.dwWidth,m_SurfDesc.dwHeight}};
	memcpy(pRegionData->Buffer,&rcList,sizeof(RECT));

	IF_FAIL(m_pBackSurf->Unlock(NULL),
		"m_pBackSurf->Unlock failed");
	
	pRegionData->rdh.dwSize=sizeof(RGNDATAHEADER);
	pRegionData->rdh.iType=RDH_RECTANGLES;
	pRegionData->rdh.nCount=1;
	pRegionData->rdh.nRgnSize=sizeof(RECT);
	pRegionData->rdh.rcBound.left=-64000;
	pRegionData->rdh.rcBound.top=-64000;
	pRegionData->rdh.rcBound.right=64000;
	pRegionData->rdh.rcBound.bottom=64000;
	
	IF_FAIL_OP(pClipper->SetClipList(pRegionData,0),
		"Failed to set clip list",
		free(pRegionData));
	IF_FAIL_OP(m_pBackSurf->SetClipper(pClipper),
		"Failed to set clipper onto back surface",
		free(pRegionData));
	free(pRegionData);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::AttachWindowClipper_window_bounds() {
	LPDIRECTDRAWCLIPPER pClipper=NULL;
	IF_FAIL(m_pDDraw->CreateClipper(0,&pClipper,NULL),
		"Failed to create clipper in windowed mode");
	IF_FAIL(pClipper->SetHWnd(0,m_hMainWnd),
		"Failed to set HWND to clipper in windowed mode");
	IF_FAIL(m_pPrimSurf->SetClipper(pClipper),
		"Failed to set clipper to primary surface in windowed mode");
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::DrawRotated(LPSURF pDestSurf,DESC* pDestDesc, LPSURF pSrcSurf,DESC* pSrcDesc, RECT rcSrc,POINTF ptDest,RECT rcDestBounds,float fDrawAngle,BOOL bTransparent,DWORD dwTranspColor) {
	
	UINT *vidBufDest,*vidBufSrc;
	int nPitchDest32,nPitchSrc32;
	LockSurface(pDestSurf,*pDestDesc,vidBufDest,nPitchDest32);
	LockSurface(pSrcSurf,*pSrcDesc,vidBufSrc,nPitchSrc32);

	float fAngle = fDrawAngle; //- 90;//учет фазового сдвига
	float sina = LookSin(fAngle);
	float cosa = LookCos(fAngle);
	int nW = rcSrc.right-rcSrc.left, nH = rcSrc.bottom-rcSrc.top;
	int x0=rcSrc.left, y0=rcSrc.top;
	float rX = nW>>1;
	float rY = nH>>1;

	DWORD dwPixel=RGB32BIT(0,0,0,0);	
	for(int j=0;j<nH;j++) { //соответствуют формируемому изображению
		for(int i=0;i<nW;i++) {
			if(!CheckInRect(ptDest.x+i,ptDest.y+j,rcDestBounds)) //ручное отсечение
				continue;
			int xAngled = round(rX+(rX-i)*sina-(rY-j)*cosa);
			int yAngled = round(rY+(rX-i)*cosa+(rY-j)*sina);
			if(0<=xAngled && xAngled<nW && 0<=yAngled && yAngled<nH) {
				//вывод только из рамок исходного изображения
				dwPixel = vidBufSrc[(yAngled+y0)*(nPitchSrc32)+xAngled+x0];
				if(!bTransparent || dwPixel!=dwTranspColor)
						vidBufDest[(j+(int)ptDest.y)*(nPitchDest32)+(i+(int)ptDest.x)] = dwPixel;
			}
		}
	}
	pDestSurf->Unlock(NULL);
	pSrcSurf->Unlock(NULL);
	return(S_OK);
}

HRESULT STDMETHODCALLTYPE VisObj::BoundWithScreen(LPRECT rcToBound) {
	rcToBound->left = max(rcToBound->left,0);
	rcToBound->right = min(rcToBound->right,m_SurfDesc.dwWidth-1);
	rcToBound->top = max(rcToBound->top,0);
	rcToBound->bottom = min(rcToBound->bottom,m_SurfDesc.dwHeight-1);
	return(S_OK);
}

LPDIRECTDRAWSURFACE7 STDMETHODCALLTYPE VisObj::CreateSurfFromFBuffer(BITMAPINFOHEADER& bitmapinfoheader,UCHAR *buffer,long lBmpStartX,long lBmpStartY,
				long lBmpFrameW,long lBmpFrameH,
				DDSURFACEDESC2& desc,long nNeededFrameW,long nNeededFrameH,
				bool bTransparent,DWORD dwTranspColor)
{
	LPDIRECTDRAWSURFACE7 pSurf;
	HRESULT hRes=S_FALSE;
			//готовим поверхность и ее описание
		if(bTransparent)
			hRes=CreateOffScreenSurface(
				pSurf,
				nNeededFrameW,
				nNeededFrameH,
				dwTranspColor,
				desc);
		else //no transp
			hRes=CreateOffScreenSurface(
				pSurf,
				nNeededFrameW,
				nNeededFrameH,
				desc);
		IF_FAILNULL(hRes,
			"AddFrameTable: Failed to create frame-surface for new table");
		//заполняем поверхность пустотой - чтобы не наблюдать мусор
		//и всегда знать, корректно ли загрузилась картинка после n+1 запуска приложения
		if(pSurf->Lock(NULL,&desc,DDLOCK_WAIT,NULL) == DD_OK) {
			BYTE * pDst = (BYTE *)desc.lpSurface;
			DWORD cl = 200;
			FillMemory(pDst,desc.lPitch*desc.dwHeight,cl);
			pSurf->Unlock(NULL);
		}
		//выводим картинку, подгоняя размеры
		HDC hDestSurfDC;
		int nFails=0;
		while(FAILED(pSurf->GetDC(&hDestSurfDC))) {
			nFails++;
			if(nFails>10) {
				break;
				Trace("AddFrameTable: Failed to get DC from new frame-surface");
			}
		}
		SetStretchBltMode(hDestSurfDC,COLORONCOLOR);
		StretchDIBits(hDestSurfDC,
				0, 0, nNeededFrameW, nNeededFrameH,
				lBmpStartX, lBmpStartY, lBmpFrameW,lBmpFrameH,
				buffer, (BITMAPINFO*)&bitmapinfoheader,
				DIB_RGB_COLORS, SRCCOPY);
		pSurf->ReleaseDC(hDestSurfDC);
		return pSurf;
}

LPDIRECTDRAWSURFACE7 STDMETHODCALLTYPE VisObj::PrepareSurface(int nPicFrameW,int nPicFrameH,
													  bool bTransparent,DWORD dwTranspColor,DESC& desc) {
	LPDIRECTDRAWSURFACE7 pSurf;
	if(bTransparent) 
		CreateOffScreenSurface(pSurf,nPicFrameW,nPicFrameH,dwTranspColor,desc);
	else
		CreateOffScreenSurface(pSurf,nPicFrameW,nPicFrameH,desc);
	if(FAILED(pSurf->Lock(NULL,&desc,DDLOCK_WAIT,NULL))) {
		Trace("Can't lock surface for drawing while preparing frame");
		return NULL;
	}
	DWORD cl = 200; //закрасим этим цветом по умолчанию
	byte *pDest = (byte *)desc.lpSurface;
	FillMemory(pDest,desc.lPitch*desc.dwHeight,cl);
	return pSurf;
}

HRESULT STDMETHODCALLTYPE VisObj::CopyByteArray(DESC& desc,BYTE* pSrc,RECT& rcFrame,int nSrcW,bool bIs32BIT) {
	int iStep = 3+bIs32BIT; //24bit or 32bit
	BYTE *pDest = (BYTE*)desc.lpSurface;
	int nFrameW = rcFrame.right-rcFrame.left;
	int ostatok = desc.lPitch - nFrameW;
	if(!bIs32BIT)
		ostatok -=nFrameW/3;
	//копируем байты внутри фрейма
	for(int j=rcFrame.top;j<rcFrame.bottom;j++) {
		for(int i=rcFrame.left;i<rcFrame.right;i+=iStep) {
			//int kMin = -1;
			for(int k=2;k>=0;k--)
				*pDest++ = pSrc[j*nSrcW+i+k];
			*pDest++ = 0;
			
		} //for i
		for(int i = 0;i<ostatok;i++)
			*pDest++=0;
	} //for j
	return S_OK;
}

bool VisObj::IsVisible() {
	return (m_itDrawnObj != m_drawnObjs.end());
}

LPSURF STDMETHODCALLTYPE VisObj::GetCurFrameSurf() {
	return m_pFrameTable->GetFrameSurf(m_Anims2[m_nCurAnim]->GetCurFrameInd());
}