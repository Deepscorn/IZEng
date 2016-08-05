//шаблон 
//программист Токарев Михаил Николаевич, IgriZdes
#pragma comment(lib,"WINMM.LIB") //звук средствами Windows

//WIN
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>

//IgriZdesEngine include
#include "izoneanim.h"

using namespace std;

//Настройки
//параметры вывода окна (разрешение экрана для полноэкранного режима
//в режиме отладки ВСЕГДА пользуйтесь оконным режимом!
//размеры экрана, первые два параметра всегда должны быть равны 0
RECT g_rcScreen;
const int g_nRefreshRate = 0; //0 - использовать системную частоту
const bool g_bFullscreen = 0; //в окне
const int g_tmFrame = 30; //время задержки между кадрами (мс)
const bool g_bMusic = 0; //музыку движок не поддерживает, используются стандартные средства windows

//<---ресурсы игры--->///////////////
//путь к папке с ресурсами игры
//const char[260] g_strResPath = "C:\\MyArts\\Light\\projects\\DirectX\\Common\\Gameres\\"; 
//путь к папке с движком игры - izeng.dll
const char* const g_strEngPath = "C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\IZEng\\Debug\\izeng.dll";
const char* const g_fnameMusic = "C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\Tutorials\\Tutorial3\\Resources\\space.wav"; //музыка в игре
const char* const  g_fnameBackgrnd = "C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\Tutorials\\Tutorial3\\Resources\\backgrnd.png";
const char* const  g_fnameShip = "C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\Tutorials\\Tutorial3\\Resources\\ship.png";
#define NUM_GRAPHS_ASTEROID 3
const char* const g_fnamesAsteroid[NUM_GRAPHS_ASTEROID] = { 
	"C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\Tutorials\\Tutorial3\\Resources\\Ast100_01.png",
	"C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\Tutorials\\Tutorial3\\Resources\\Ast100_02.png",
	"C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\Tutorials\\Tutorial3\\Resources\\Ast100_03.png"
};
const char* const g_fnameBang = "C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\Tutorials\\Tutorial3\\Resources\\Explosion52.png";

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
	HWND hWnd=CreateWindow("MyClass","Демо IZEngine: Tutorial 3",WS_OVERLAPPED|WS_BORDER|WS_MINIMIZEBOX|WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,
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
double w(double xPercents) { return g_rcScreen.right*xPercents;}
double h(double yPercents) { return g_rcScreen.bottom*yPercents;}

//настройки игрового процесса
const int g_nAsteroidsCount = 10; //число астероидов

//Создадим глобальный объект для управления движком:
IZObj* izEngine = NULL;
//объекты игры
IZAnim* izBackgrnd = NULL;
//корабль
IZObj* izShip = NULL;
enum {ANIM_SHIP_FLY = 0, ANIM_SHIP_COLLISION};
IZObj* izAsteroids;
//взрывы - графика
int g_nBigBang;

//Инициализация/////////////////
int Game_Init(void *parms,int num_parms) {
	if(g_bMusic)
		PlaySound(g_fnameMusic,g_hInst,SND_FILENAME|SND_LOOP|SND_ASYNC);
//screen rect
	RECT rcScreen;
	rcScreen.left = w(0);
	rcScreen.top = h(0);
	rcScreen.right = w(1);
	rcScreen.bottom = h(1);
//create engine object and init display
	izEngine = new IZObj((char*)g_strEngPath); //загрузка из dll
	izEngine->pScreen->ResetDisplay(g_hMainWnd,g_rcScreen.right,g_rcScreen.bottom,g_nRefreshRate,g_bFullscreen,g_tmFrame);
//background
	izBackgrnd = new IZAnim(); //вызывается конструктор по умолчанию, т.к. dll уже загружена выше
	izBackgrnd->pAnim->LoadSimpleAnim((UCHAR*)g_fnameBackgrnd,g_rcScreen.right,g_rcScreen.bottom,1,1,FALSE,0);
	POINTF ptPos; ptPos.x = w(0); ptPos.y = h(0);
	izBackgrnd->pParams->SetPos(&ptPos);
//ship
	izShip = new IZObj;
	izShip->pAnim->LoadFrameTable((UCHAR*)g_fnameShip,h(0.1),h(0.1),0,1,TRUE,rgb32bit(0,0,0,0));
	int nShipFrameTableFrames;
	izShip->pAnim->GetFrameAmountInTable(&nShipFrameTableFrames);
	izShip->pAnim->CreateLinearAnim(ANIM_SHIP_FLY,0,nShipFrameTableFrames*0.57-1);
	izShip->pAnim->CreateLinearAnim(ANIM_SHIP_COLLISION,nShipFrameTableFrames*0.57,nShipFrameTableFrames-1);
	ptPos.x = w(0.2); ptPos.y = h(0.2);
	izShip->pParams->SetPos(&ptPos);
	//инициализация движения с ускорением
	izShip->pAccelMove->SetAccel(h(0.002)); //устанавливаем ускорение 
	izShip->pAccelMove->SetMaxSpeed(h(0.05)); //уст. макс. возможную скорость
	izShip->pAccelMove->EnableAccel(TYPE_ACCEL); //активируем ускорение (можно еще активировать тормоз)
	//иниц. столкновения
	RECT rcShipBounds;
	rcShipBounds.left = 0; rcShipBounds.top = h(0.5); rcShipBounds.right = w(1); rcShipBounds.bottom = h(1);
	izShip->pPhysics->SetBounds(rcShipBounds,FALSE); //ограничим область для корабля нижней половиной экрана
	izShip->pPhysics->SetBoundsReact(REACT_STOP); //пусть при попытке выхода за область корабль тормозит
	//asteroids
	izAsteroids = new IZObj[g_nAsteroidsCount];
	for(int i=0;i<g_nAsteroidsCount;i++) {
		IZObj* izAsteroid = izAsteroids + i;
		int nTemp;
		izAsteroid->pAnim->LoadOrUseExistingSimpleAnim(
			(UCHAR*)g_fnamesAsteroid[i%NUM_GRAPHS_ASTEROID],h(0.05),h(0.05),0,1,TRUE,0);
		POINTF ptPos; ptPos.y = rand()%rcScreen.bottom; //установим астероид в произвольную позицию по y
		//по х то же самое делать нужды нет - мы используем REACT_RAND_TELEPORT
		izAsteroid->pParams->SetPos(&ptPos);
		izAsteroid->pPhysics->SetBounds(rcScreen,FALSE);  //область ограничения - экран
		izAsteroid->pPhysics->SetBoundsReact(REACT_RAND_TELEPORT); //пусть появляются с другой стороны
		//экрана и с произвольной координатой x
		izAsteroid->pLineMove->SetSpeed(h(0.01));
		izAsteroid->pLineMove->SetDirY(1,false); //пусть летят вниз навстречу игроку
	}
	//bangs - взрывы
	izEngine->pScreen->AddFrameTable(&g_nBigBang,(UCHAR*)g_fnameBang,h(0.1),h(0.1),0,1,TRUE,0x000000);
	//установим порядок прорисовки
	izBackgrnd->pDraw->ShowOn(0);
	izShip->pDraw->ShowOn(2);
	for(int i=0;i<g_nAsteroidsCount;i++) {
		IZObj* izAsteroid = izAsteroids + i;
		izAsteroid->pDraw->ShowOn(100);
	}
	//izShip->pSignalKeybord->addSlotKeyDown(shipMove);
	//test text
	RECT rc = { 100,100,200,140};
	izBackgrnd->pHUD->AddText(&rc,(UCHAR*)"Hello world!",0x00FF00,20);

	return(0);
}

void shipMove() {
	POINTF vecShipMove;
	izShip->pAccelMove->SetAccelDirY(0); 
	izShip->pAccelMove->SetAccelDirX(0); //если пользователь ничего не жмет

	BOOL bDown = FALSE;
	izEngine->pInput->CheckKeyDown('W',&bDown);
	if(bDown)
		izShip->pAccelMove->SetAccelDirY(-1); 
	//-1 - направление, 
	//всего направлений 3:
	//0 - стоим
	//1 - движемся в сторону возрастания оси X или Y 
	//-1 -в сторону уменьшения
	//Обратите внимание, что ось Y направлена вниз
	izEngine->pInput->CheckKeyDown('S',&bDown);
	if(bDown) {
		izShip->pAccelMove->SetAccelDirY(1);
		
	}
	izEngine->pInput->CheckKeyDown('A',&bDown);
	if(bDown)
		izShip->pAccelMove->SetAccelDirX(-1);
	izEngine->pInput->CheckKeyDown('D',&bDown);
	if(bDown) 
		izShip->pAccelMove->SetAccelDirX(1);
}

void collideObjs() {
	for(int i=0;i<g_nAsteroidsCount;i++) {
		BOOL bCollision = FALSE;
		IZObj* izAst = izAsteroids+i;
		izShip->pPhysics->CheckCollisionCircleCircle(izAst->pParams,&bCollision);
		if(bCollision) {
			//izAst->pDraw->Hide();
			POINTF ptf;
			izAst->pParams->GetCentreCoordsPt(&ptf);
			IZOneAnim::Create(ptf,g_nBigBang,100); //создаем анимацию разлома астероида
			izAst->pParams->GetWidthAndHeight(&ptf);
			ptf.x = -ptf.x - 1; ptf.y = -ptf.y; //-ptf.x - 1 даст произвольную позицию по х
			izAst->pParams->SetPos(&ptf); //поместим астероид за экран — он еще пригодится
		}
	}
}



int Game_Main(void *parms,int num_parms) {
	BOOL bDown = FALSE;
	izEngine->pInput->CheckKeyDown(VK_ESCAPE,&bDown);
	if(bDown) 
		SendMessage(g_hMainWnd,WM_DESTROY,0,0);
	//makeRidiculus();
	//control
	//управление движением с ускорением
	shipMove();
	/*for(int i=0;i<g_nAsteroidsCount;i++) {
		IZObj* izAst = izAsteroids+i;
		izAst->pDraw->Show();
	}*/
	collideObjs();
	//обновление мира и кадра на экран
	//test new method - works well!
	//RECT rc = {100,100,400,200};
	//izBackgrnd->pHUD->AddText(&rc,(UCHAR*)"TEST TEXT",0x00FF00,20); //рисует на поверхность - фон

	izEngine->pPhysics->UpdatePhysics();
	izEngine->pScreen->UpdateScreen(); 
	
	

	IZOneAnim::Update();
	return(0);
}

int Game_Shutdown(void *parms,int num_parms) { 
	//освобождение ресурсов
	izEngine->pScreen->ShutDown();
	if(g_bMusic)
		PlaySound(NULL,g_hInst,SND_PURGE);
	return(0);
}