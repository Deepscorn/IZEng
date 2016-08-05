//шаблон 
//программист Токарев Михаил Николаевич, IgriZdes
#pragma comment(lib,"WINMM.LIB") //звук средствами Windows

//WIN
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>

//IgriZdesEngine include
#include "IZObj.h"

using namespace std;

//Настройки
//параметры вывода окна (разрешение экрана для полноэкранного режима
//в режиме отладки ВСЕГДА пользуйтесь оконным режимом!
//размеры экрана, первые два параметра всегда должны быть равны 0
RECT g_rcScreen;
const int g_nRefreshRate = 0; //0 - использовать системную частоту
const bool g_bFullscreen = 0; //в окне
const int g_tmFrame = 30; //время задержки между кадрами (мс)
const bool g_bMusic = 1; //музыку движок не поддерживает, используются стандартные средства windows

//<---ресурсы игры--->///////////////
//путь к папке с ресурсами игры
//const char[260] g_strResPath = "C:\\MyArts\\Light\\projects\\DirectX\\Common\\Gameres\\"; 
//путь к папке с движком игры - IZObj.dll
const char* const g_strEngPath = "C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\IZEng\\Debug\\IZEng.dll";
const char* const g_fnameMusic = "C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\Tutorials\\Tutorial1\\Resources\\space.wav"; //музыка в игре
const char* const  g_fnameBackgrnd = "C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\Tutorials\\Tutorial1\\Resources\\backgrnd.png";

//глоб. переменные приложения
HINSTANCE g_hInst;
HWND g_hMainWnd;

//предварительные объявления
bool MyRegisterClass(HINSTANCE hInst);
HWND MyCreateWindow(HINSTANCE hInst);
LRESULT CALLBACK MyProc(HWND, UINT nMsg, WPARAM wParam, LPARAM lParam);
int Game_Main(void *parms=NULL,int num_parms=0);
int Game_Init(void *parms=NULL,int num_parms=0);
int Game_Shutdown(void *parms=NULL,int num_parms=0);

//сам шаблон
int WINAPI WinMain(HINSTANCE hInstExe, HINSTANCE hINstPrevExe, LPSTR lpszCmdLine, int nCmdShow)
{	
	MSG msg;
try {

	g_rcScreen.left=0;
	g_rcScreen.top=0;
	g_rcScreen.right=1024;
	g_rcScreen.bottom=768;

	g_hInst=hInstExe;
	if(!MyRegisterClass(hInstExe))
		throw(exception("WinMain: Класс окна Windows не зарегистрировался"));
	g_hMainWnd=MyCreateWindow(hInstExe);
	if(!g_hMainWnd)
		throw(exception("WinMain: Окно не создалось"));
	//подгоняем размеры окна
	RECT rcClient;
	GetClientRect(g_hMainWnd,&rcClient);
	MoveWindow(g_hMainWnd,100,100,2*g_rcScreen.right-rcClient.right,
		2*g_rcScreen.bottom-rcClient.bottom,FALSE);
	//выводим окно
	ShowWindow(g_hMainWnd,SW_SHOW);
	UpdateWindow(g_hMainWnd);
	//инициализация игры
	Game_Init();
	while(TRUE) {
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE)) {
			if(msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//шаг (step), аналогичен кадру игры
		Game_Main();
	}
	//завершение игры и освобождение ресурсов
	Game_Shutdown();
}
catch(std::exception& e) { //критические ошибки
	MessageBox(NULL,e.what(),"Критическая ошибка",MB_OK);
	if(g_hMainWnd)
		DestroyWindow(g_hMainWnd); //quit
}
	return msg.wParam;
}

bool MyRegisterClass(HINSTANCE hInst)
{
	WNDCLASS wndClass;
	memset(&wndClass,0,sizeof(wndClass));
	wndClass.style=CS_DBLCLKS|CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	wndClass.lpfnWndProc=MyProc;
	wndClass.hInstance=hInst;
	//wndClass.hIcon=LoadIcon(hInst,MAKEINTRESOURCE(IDI_MYICON));
	//wndClass.hCursor=LoadCursor(hInst,MAKEINTRESOURCE(IDC_DEADARROW));
	wndClass.hbrBackground=CreateSolidBrush(RGB(0,0,40));
	wndClass.lpszClassName="MyClass";
	//wndClass.lpszMenuName = MAKEINTRESOURCE(IDM_MYMENU); //если нужна полоска меню
	return(RegisterClass(&wndClass)==0)?false:true;
}

HWND MyCreateWindow(HINSTANCE hInst)
{
	HWND hWnd=CreateWindow("MyClass","Демо IZEngine: Tutorial 1",WS_OVERLAPPED|WS_BORDER|WS_MINIMIZEBOX|WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,
		g_rcScreen.right,g_rcScreen.bottom,NULL,NULL,hInst,NULL);
	return hWnd;
}

////////////////////////////ОБРАБОТЧИКИ_СООБЩЕНИЙ/////////////////////////////////////////////

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{	
	return TRUE;
}

void OnDestroy(HWND hwnd)
{
	//освобождение памяти
	PostQuitMessage(0);
}

////Менеджер сообщений

LRESULT CALLBACK MyProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	switch(nMsg)
	{
	HANDLE_MSG(hWnd,WM_CREATE,OnCreate);
	HANDLE_MSG(hWnd,WM_DESTROY,OnDestroy);
	default:
		return DefWindowProc(hWnd,nMsg,wParam,lParam);
	}
	return 0;
}
//здесь шаблон заканчивается

//функции для процентного задания положения объектов на экране -
//используются для того, чтобы быть независимыми от разрешения экрана
float w(double xPercents) { return g_rcScreen.right*xPercents;}
float h(double yPercents) { return g_rcScreen.bottom*yPercents;}

//Создадим глобальный объект для управления движком:
IZObj* izEngine = NULL;
//объекты игры
IZObj* izBackgrnd = NULL;

//Инициализация/////////////////
int Game_Init(void *parms,int num_parms) {
	if(g_bMusic)
		PlaySound(g_fnameMusic,g_hInst,SND_FILENAME|SND_LOOP|SND_ASYNC);
	//create engine object and init display
	izEngine = new IZObj((char*)g_strEngPath); //загрузка из dll
	izEngine->pScreen->ResetDisplay(g_hMainWnd,g_rcScreen.right,g_rcScreen.bottom,g_nRefreshRate,g_bFullscreen,g_tmFrame);
	izBackgrnd = new IZObj(); //вызывается конструктор по умолчанию, т.к. dll уже загружена выше
	izBackgrnd->pAnim->LoadSimpleAnim((UCHAR*)g_fnameBackgrnd,g_rcScreen.right,g_rcScreen.bottom,1,1,FALSE,0);
	POINTF ptPos; ptPos.x = w(0); ptPos.y = h(0);
	izBackgrnd->pParams->SetPos(&ptPos);
	//добавим в список отображения
	izBackgrnd->pDraw->Show();
	RECT rc = { 100,100,200,140};
	izBackgrnd->pHUD->AddText(&rc,(UCHAR*)"Hello world!",0x00FF00,20);
	return(0);
}

int Game_Main(void *parms,int num_parms) {
	BOOL bKeyDown = FALSE;
	izEngine->pInput->CheckKeyDown(VK_ESCAPE,&bKeyDown);
	if(bKeyDown) 
		SendMessage(g_hMainWnd,WM_DESTROY,0,0);
	izEngine->pScreen->UpdateScreen(); //обновление кадра
	return(0);
}

int Game_Shutdown(void *parms,int num_parms) { 
	if(g_bMusic)
		PlaySound(NULL,g_hInst,SND_PURGE);
	return(0);
}