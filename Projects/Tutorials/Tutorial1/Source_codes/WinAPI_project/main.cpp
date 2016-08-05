//шаблон 
//программист Токарев Михаил Николаевич, IgriZdes
#pragma comment(lib,"WINMM.LIB") //звук средствами Windows

//WIN
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <exception>
using namespace std;

//Настройки
//параметры вывода окна (разрешение экрана для полноэкранного режима
//в режиме отладки ВСЕГДА пользуйтесь оконным режимом!
//размеры экрана, первые два параметра всегда должны быть равны 0
RECT g_rcScreen;
const bool g_bMusic = 1; //музыку движок не поддерживает, используются стандартные средства windows

//<---ресурсы игры--->///////////////
const char* const g_fnameMusic = "C:\\MyArts\\Light\\projects\\DirectX\\Install\\Tutorials\\Tutorial1\\Gameres\\space.wav"; //музыка в игре

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

//Инициализация/////////////////
int Game_Init(void *parms,int num_parms) {
	if(g_bMusic)
		PlaySound(g_fnameMusic,g_hInst,SND_FILENAME|SND_LOOP|SND_ASYNC);
	return(0);
}

//шаг игрового процесса (кадр)
int Game_Main(void *parms,int num_parms) {
	return(0);
}

//завершение игры
int Game_Shutdown(void *parms,int num_parms) { 
	if(g_bMusic)
		PlaySound(NULL,g_hInst,SND_PURGE);
	return(0);
}