//������ 
//����������� ������� ������ ����������, IgriZdes
#pragma comment(lib,"WINMM.LIB") //���� ���������� Windows

//WIN
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>

//IgriZdesEngine include
#include "izoneanim.h"

using namespace std;

//���������
//��������� ������ ���� (���������� ������ ��� �������������� ������
//� ������ ������� ������ ����������� ������� �������!
//������� ������, ������ ��� ��������� ������ ������ ���� ����� 0
RECT g_rcScreen;
const int g_nRefreshRate = 0; //0 - ������������ ��������� �������
const bool g_bFullscreen = 0; //� ����
const int g_tmFrame = 30; //����� �������� ����� ������� (��)
const bool g_bMusic = 0; //������ ������ �� ������������, ������������ ����������� �������� windows

//<---������� ����--->///////////////
//���� � ����� � ��������� ����
//const char[260] g_strResPath = "C:\\MyArts\\Light\\projects\\DirectX\\Common\\Gameres\\"; 
//���� � ����� � ������� ���� - izeng.dll
const char* const g_strEngPath = "C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\IZEng\\Debug\\izeng.dll";
const char* const g_fnameMusic = "C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\Tutorials\\Tutorial3\\Resources\\space.wav"; //������ � ����
const char* const  g_fnameBackgrnd = "C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\Tutorials\\Tutorial3\\Resources\\backgrnd.png";
const char* const  g_fnameShip = "C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\Tutorials\\Tutorial3\\Resources\\ship.png";
#define NUM_GRAPHS_ASTEROID 3
const char* const g_fnamesAsteroid[NUM_GRAPHS_ASTEROID] = { 
	"C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\Tutorials\\Tutorial3\\Resources\\Ast100_01.png",
	"C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\Tutorials\\Tutorial3\\Resources\\Ast100_02.png",
	"C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\Tutorials\\Tutorial3\\Resources\\Ast100_03.png"
};
const char* const g_fnameBang = "C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\Tutorials\\Tutorial3\\Resources\\Explosion52.png";

//����. ���������� ����������
HINSTANCE g_hInst;
HWND g_hMainWnd;

//��������������� ����������
bool MyRegisterClass(HINSTANCE hInst);
HWND MyCreateWindow(HINSTANCE hInst);
LRESULT CALLBACK MyProc(HWND, UINT nMsg, WPARAM wParam, LPARAM lParam);
int Game_Main(void *parms=NULL,int num_parms=0);
int Game_Init(void *parms=NULL,int num_parms=0);
int Game_Shutdown(void *parms=NULL,int num_parms=0);

//��� ������
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
		throw(exception("WinMain: ����� ���� Windows �� �����������������"));
	g_hMainWnd=MyCreateWindow(hInstExe);
	if(!g_hMainWnd)
		throw(exception("WinMain: ���� �� ���������"));
	//��������� ������� ����
	RECT rcClient;
	GetClientRect(g_hMainWnd,&rcClient);
	MoveWindow(g_hMainWnd,100,100,2*g_rcScreen.right-rcClient.right,
		2*g_rcScreen.bottom-rcClient.bottom,FALSE);
	//������� ����
	ShowWindow(g_hMainWnd,SW_SHOW);
	UpdateWindow(g_hMainWnd);
	//������������� ����
	Game_Init();
	while(TRUE) {
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE)) {
			if(msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//��� (step), ���������� ����� ����
		Game_Main();
	}
	//���������� ���� � ������������ ��������
	Game_Shutdown();
}
catch(std::exception& e) { //����������� ������
	MessageBox(NULL,e.what(),"����������� ������",MB_OK);
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
	//wndClass.lpszMenuName = MAKEINTRESOURCE(IDM_MYMENU); //���� ����� ������� ����
	return(RegisterClass(&wndClass)==0)?false:true;
}

HWND MyCreateWindow(HINSTANCE hInst)
{
	HWND hWnd=CreateWindow("MyClass","���� IZEngine: Tutorial 3",WS_OVERLAPPED|WS_BORDER|WS_MINIMIZEBOX|WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,
		g_rcScreen.right,g_rcScreen.bottom,NULL,NULL,hInst,NULL);
	return hWnd;
}

////////////////////////////�����������_���������/////////////////////////////////////////////

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{	
	return TRUE;
}

void OnDestroy(HWND hwnd)
{
	//������������ ������
	PostQuitMessage(0);
}

////�������� ���������

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
//����� ������ �������������

//������� ��� ����������� ������� ��������� �������� �� ������ -
//������������ ��� ����, ����� ���� ������������ �� ���������� ������
double w(double xPercents) { return g_rcScreen.right*xPercents;}
double h(double yPercents) { return g_rcScreen.bottom*yPercents;}

//��������� �������� ��������
const int g_nAsteroidsCount = 10; //����� ����������

//�������� ���������� ������ ��� ���������� �������:
IZObj* izEngine = NULL;
//������� ����
IZAnim* izBackgrnd = NULL;
//�������
IZObj* izShip = NULL;
enum {ANIM_SHIP_FLY = 0, ANIM_SHIP_COLLISION};
IZObj* izAsteroids;
//������ - �������
int g_nBigBang;

//�������������/////////////////
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
	izEngine = new IZObj((char*)g_strEngPath); //�������� �� dll
	izEngine->pScreen->ResetDisplay(g_hMainWnd,g_rcScreen.right,g_rcScreen.bottom,g_nRefreshRate,g_bFullscreen,g_tmFrame);
//background
	izBackgrnd = new IZAnim(); //���������� ����������� �� ���������, �.�. dll ��� ��������� ����
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
	//������������� �������� � ����������
	izShip->pAccelMove->SetAccel(h(0.002)); //������������� ��������� 
	izShip->pAccelMove->SetMaxSpeed(h(0.05)); //���. ����. ��������� ��������
	izShip->pAccelMove->EnableAccel(TYPE_ACCEL); //���������� ��������� (����� ��� ������������ ������)
	//����. ������������
	RECT rcShipBounds;
	rcShipBounds.left = 0; rcShipBounds.top = h(0.5); rcShipBounds.right = w(1); rcShipBounds.bottom = h(1);
	izShip->pPhysics->SetBounds(rcShipBounds,FALSE); //��������� ������� ��� ������� ������ ��������� ������
	izShip->pPhysics->SetBoundsReact(REACT_STOP); //����� ��� ������� ������ �� ������� ������� ��������
	//asteroids
	izAsteroids = new IZObj[g_nAsteroidsCount];
	for(int i=0;i<g_nAsteroidsCount;i++) {
		IZObj* izAsteroid = izAsteroids + i;
		int nTemp;
		izAsteroid->pAnim->LoadOrUseExistingSimpleAnim(
			(UCHAR*)g_fnamesAsteroid[i%NUM_GRAPHS_ASTEROID],h(0.05),h(0.05),0,1,TRUE,0);
		POINTF ptPos; ptPos.y = rand()%rcScreen.bottom; //��������� �������� � ������������ ������� �� y
		//�� � �� �� ����� ������ ����� ��� - �� ���������� REACT_RAND_TELEPORT
		izAsteroid->pParams->SetPos(&ptPos);
		izAsteroid->pPhysics->SetBounds(rcScreen,FALSE);  //������� ����������� - �����
		izAsteroid->pPhysics->SetBoundsReact(REACT_RAND_TELEPORT); //����� ���������� � ������ �������
		//������ � � ������������ ����������� x
		izAsteroid->pLineMove->SetSpeed(h(0.01));
		izAsteroid->pLineMove->SetDirY(1,false); //����� ����� ���� ��������� ������
	}
	//bangs - ������
	izEngine->pScreen->AddFrameTable(&g_nBigBang,(UCHAR*)g_fnameBang,h(0.1),h(0.1),0,1,TRUE,0x000000);
	//��������� ������� ����������
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
	izShip->pAccelMove->SetAccelDirX(0); //���� ������������ ������ �� ����

	BOOL bDown = FALSE;
	izEngine->pInput->CheckKeyDown('W',&bDown);
	if(bDown)
		izShip->pAccelMove->SetAccelDirY(-1); 
	//-1 - �����������, 
	//����� ����������� 3:
	//0 - �����
	//1 - �������� � ������� ����������� ��� X ��� Y 
	//-1 -� ������� ����������
	//�������� ��������, ��� ��� Y ���������� ����
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
			IZOneAnim::Create(ptf,g_nBigBang,100); //������� �������� ������� ���������
			izAst->pParams->GetWidthAndHeight(&ptf);
			ptf.x = -ptf.x - 1; ptf.y = -ptf.y; //-ptf.x - 1 ���� ������������ ������� �� �
			izAst->pParams->SetPos(&ptf); //�������� �������� �� ����� � �� ��� ����������
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
	//���������� ��������� � ����������
	shipMove();
	/*for(int i=0;i<g_nAsteroidsCount;i++) {
		IZObj* izAst = izAsteroids+i;
		izAst->pDraw->Show();
	}*/
	collideObjs();
	//���������� ���� � ����� �� �����
	//test new method - works well!
	//RECT rc = {100,100,400,200};
	//izBackgrnd->pHUD->AddText(&rc,(UCHAR*)"TEST TEXT",0x00FF00,20); //������ �� ����������� - ���

	izEngine->pPhysics->UpdatePhysics();
	izEngine->pScreen->UpdateScreen(); 
	
	

	IZOneAnim::Update();
	return(0);
}

int Game_Shutdown(void *parms,int num_parms) { 
	//������������ ��������
	izEngine->pScreen->ShutDown();
	if(g_bMusic)
		PlaySound(NULL,g_hInst,SND_PURGE);
	return(0);
}