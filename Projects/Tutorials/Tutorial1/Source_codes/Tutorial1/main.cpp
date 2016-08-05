//������ 
//����������� ������� ������ ����������, IgriZdes
#pragma comment(lib,"WINMM.LIB") //���� ���������� Windows

//WIN
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>

//IgriZdesEngine include
#include "IZObj.h"

using namespace std;

//���������
//��������� ������ ���� (���������� ������ ��� �������������� ������
//� ������ ������� ������ ����������� ������� �������!
//������� ������, ������ ��� ��������� ������ ������ ���� ����� 0
RECT g_rcScreen;
const int g_nRefreshRate = 0; //0 - ������������ ��������� �������
const bool g_bFullscreen = 0; //� ����
const int g_tmFrame = 30; //����� �������� ����� ������� (��)
const bool g_bMusic = 1; //������ ������ �� ������������, ������������ ����������� �������� windows

//<---������� ����--->///////////////
//���� � ����� � ��������� ����
//const char[260] g_strResPath = "C:\\MyArts\\Light\\projects\\DirectX\\Common\\Gameres\\"; 
//���� � ����� � ������� ���� - IZObj.dll
const char* const g_strEngPath = "C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\IZEng\\Debug\\IZEng.dll";
const char* const g_fnameMusic = "C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\Tutorials\\Tutorial1\\Resources\\space.wav"; //������ � ����
const char* const  g_fnameBackgrnd = "C:\\MyArts\\Light\\projects\\IgriZdes\\Projects\\Tutorials\\Tutorial1\\Resources\\backgrnd.png";

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
	HWND hWnd=CreateWindow("MyClass","���� IZEngine: Tutorial 1",WS_OVERLAPPED|WS_BORDER|WS_MINIMIZEBOX|WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,
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
float w(double xPercents) { return g_rcScreen.right*xPercents;}
float h(double yPercents) { return g_rcScreen.bottom*yPercents;}

//�������� ���������� ������ ��� ���������� �������:
IZObj* izEngine = NULL;
//������� ����
IZObj* izBackgrnd = NULL;

//�������������/////////////////
int Game_Init(void *parms,int num_parms) {
	if(g_bMusic)
		PlaySound(g_fnameMusic,g_hInst,SND_FILENAME|SND_LOOP|SND_ASYNC);
	//create engine object and init display
	izEngine = new IZObj((char*)g_strEngPath); //�������� �� dll
	izEngine->pScreen->ResetDisplay(g_hMainWnd,g_rcScreen.right,g_rcScreen.bottom,g_nRefreshRate,g_bFullscreen,g_tmFrame);
	izBackgrnd = new IZObj(); //���������� ����������� �� ���������, �.�. dll ��� ��������� ����
	izBackgrnd->pAnim->LoadSimpleAnim((UCHAR*)g_fnameBackgrnd,g_rcScreen.right,g_rcScreen.bottom,1,1,FALSE,0);
	POINTF ptPos; ptPos.x = w(0); ptPos.y = h(0);
	izBackgrnd->pParams->SetPos(&ptPos);
	//������� � ������ �����������
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
	izEngine->pScreen->UpdateScreen(); //���������� �����
	return(0);
}

int Game_Shutdown(void *parms,int num_parms) { 
	if(g_bMusic)
		PlaySound(NULL,g_hInst,SND_PURGE);
	return(0);
}