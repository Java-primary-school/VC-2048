// VC++2048.cpp : 定义应用程序的入口点。
//
#pragma comment(lib, "Msimg32.lib")  
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <iostream>
#include "framework.h"
#include "VC++2048.h"
#include <map>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include "DigitalConfig.h"
#include "Checkerboard.h"

using namespace std;
#define MAX_LOADSTRING 100
#define LAYER 101 

#define MAX_WIDTH  530
#define MAX_HEIGHT 730
#define DRAW_ARRAY 1003 //变换数组画法
#define DRAW_OVER 1004 //游戏结束画法
// 全局变量:
HINSTANCE hInst;  
HWND hWnd;// 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
WCHAR szLAYERClass[LAYER];
TCHAR szBtnName1[] = TEXT("MyBtn1"); //按钮窗口类名
TCHAR szBtnName2[] = TEXT("MyBtn2");
BOOL Gdi_init(HWND hWnd);
void Gdi_paint(HWND hWnd);
BOOL Gdi_CleanUp(HWND hWnd);
void Gdi_paintMask(HWND hWnd);
//数组操作函数

HDC g_hdc = NULL; //全局设备环境句柄
HDC hBitmapDC = NULL;
HPEN g_hPen = { 0 }; //定义画笔句柄的数组
HBRUSH g_hBrush = { 0 };
HWND hbu;
HWND hbu1;
//判断是否是结束
bool transparent = false;
//当天分数
int fraction =0;
//最大分数
int maxFraction = 0;
//所有数字方块
map<int, DigitalConfig*> mapColor;
//存取最大分数
void maxFractionWandR(bool);
//2048二维数组操作类
Checkerboard* checkerboard;
// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ButWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ButWndProc1(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

 
    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_VC2048, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	
	if (!Gdi_init(hWnd)) {
		MessageBox(hWnd, L"资源初始化失败", L"消息窗口", 0); //使用MessageBox函数，创建一个消息窗口
		return FALSE;
	}
	
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VC2048));

	MSG msg = {0};
	string str;
	DWORD num = 0;
	
	
    // 主消息循环:
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
			
            TranslateMessage(&msg);
            DispatchMessage(&msg);
		}
		
		
		
    }
	
    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VC2048));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(15726842);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_VC2048);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassExW(&wcex);
	//自绘按钮注册窗口类
	wcex.hbrBackground = CreateSolidBrush(RGB(143,122,102));
	wcex.lpfnWndProc = ButWndProc;
	wcex.lpszClassName = szBtnName1;
	RegisterClassExW(&wcex);
	wcex.hbrBackground = CreateSolidBrush(RGB(143, 122, 102));
	wcex.lpfnWndProc = ButWndProc1;
	wcex.lpszClassName = szBtnName2;

    return RegisterClassExW(&wcex);
}


//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED |WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
      CW_USEDEFAULT, 0, MAX_WIDTH, MAX_HEIGHT, nullptr, nullptr, hInst, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
 
   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	bool flag = false;
    switch (message)
    {
	case WM_CREATE:
		
     		hbu = CreateWindow(szBtnName1, TEXT("再来一次"),
			WS_CHILD, 0, 0, 200, 100, hWnd, (HMENU)1002, hInst, nullptr);
			hbu1 = CreateWindow(szBtnName2, TEXT("重新开始"),
				WS_CHILD, 0, 0, 200, 100, hWnd, (HMENU)1003, hInst, nullptr);
			ShowWindow(hbu1, SW_SHOW);
		break;

	case WM_KEYDOWN:
		if (!transparent)
		{
			switch (wParam)
			{
			case VK_LEFT:

				checkerboard->left(&fraction);
				flag = true;
				break;
			case VK_RIGHT:
				checkerboard->right(&fraction);
				flag = true;
				break;
			case VK_UP:
				checkerboard->up(&fraction);
				flag = true;
				break;
			case VK_DOWN:
				checkerboard->down(&fraction);
				flag = true;
				break;
			default:
				break;
			}
		}
		if (flag)
		{   
			
			checkerboard->changeTemp();
			checkerboard->hanleNum(false);
			SendMessage(hWnd, WM_PAINT, DRAW_ARRAY, 0);
			if (checkerboard->IsGameOver())
			{
				maxFractionWandR(false);
				transparent = true;
				SendMessage(hWnd, WM_PAINT, DRAW_OVER, 0);
				ShowWindow(hbu, SW_SHOW);

			}
		}
       		break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            //case IDM_ABOUT:
               // DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            //case IDM_EXIT:
                //DestroyWindow(hWnd);
                //break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
			
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
	/*		switch (wParam)
			{
			case DRAW_ARRAY:
				
				Gdi_paint(hWnd);
				break;
			case DRAW_OVER:
				
				Gdi_paintMask(hWnd);
				break;
			case SW_SHOW:
				

			default:
				break;
			}
		*/
			if (transparent)
			{
				Gdi_paintMask(hWnd);
			}
			else
			{
				Gdi_paint(hWnd);
			}
			
			
			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
		Gdi_CleanUp(hWnd);
		
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


LRESULT CALLBACK ButWndProc(HWND hBtn1, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	
	PAINTSTRUCT ps = { 0 };
	HDC DC = NULL;
	switch (message)
	{
	case WM_CREATE:
	{
		MoveWindow(hBtn1, 200,400, 130, 50, TRUE);
		HRGN hRgn = CreateRoundRectRgn(0, 0, 130, 50, 5,5);
		SetWindowRgn(hBtn1, hRgn, TRUE);
	}
	break;
	case WM_LBUTTONDOWN: 
		checkerboard->restart();
		ShowWindow(hBtn1, SW_HIDE);
		ShowWindow(hbu1, SW_HIDE);
		fraction = 0;
		RECT rt;
		GetClientRect(hWnd, &rt);

		FillRect(hBitmapDC, &rt, (HBRUSH)GetClassLong(hWnd, GCL_HBRBACKGROUND));
		BitBlt(g_hdc, 0, 0, rt.right, rt.bottom, hBitmapDC, 0, 0, SRCCOPY);

		ShowWindow(hbu1, SW_SHOW);
		transparent = false;
		SendMessage(hWnd, WM_PAINT, DRAW_ARRAY, 0);
		
		
		break;
	case WM_PAINT:
	{
		
		DC = BeginPaint(hBtn1, &ps);
		SetBkColor(DC, RGB(143,122,102)); //按钮背景颜色
		HFONT hFont = CreateFont(22, 0, 0, 0, 900, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"宋体");
		
		SelectObject(DC, hFont);
		SetTextColor(DC, RGB(250, 248, 239)); //按钮上的文字颜色
		RECT rect;
		rect.left = 0;
		rect.top = 14;
		rect.right = 130;
		rect.bottom = 40;
		DrawText(DC, L"再来一次", 4, &rect, DT_CENTER);

		EndPaint(hBtn1, &ps);
	}
	break;
	default:
		break;
	}
	return DefWindowProc(hBtn1, message, wParam, lParam);


	}
LRESULT CALLBACK ButWndProc1(HWND hBtn1, UINT message, WPARAM wParam, LPARAM lParam)
{


	PAINTSTRUCT ps = { 0 };
	HDC DC = NULL;
	switch (message)
	{
	case WM_CREATE:
	{
		MoveWindow(hBtn1, 383, 110, 112, 40, TRUE);
		HRGN hRgn = CreateRoundRectRgn(0, 0, 112, 40, 5, 5);
		SetWindowRgn(hBtn1, hRgn, TRUE);
	}
	break;
	case WM_LBUTTONDOWN:
		if (!transparent)
		{
			maxFractionWandR(false);
			transparent = false;
			checkerboard->restart();
			fraction = 0;
			SendMessage(hWnd, WM_PAINT, DRAW_ARRAY, 0);
		}

		break;
	case WM_PAINT:
	{

		DC = BeginPaint(hBtn1, &ps);
		SetBkColor(DC, RGB(143, 122, 102)); //按钮背景颜色
		HFONT hFont = CreateFont(22, 0, 0, 0, 900, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"微软雅黑");

		SelectObject(DC, hFont);
		SetTextColor(DC, RGB(250, 248, 239)); //按钮上的文字颜色
		RECT rect;
		rect.left = 0;
		rect.top = 9;
		rect.right = 112;
		rect.bottom = 40;
		DrawText(DC, L"重新开始", 4, &rect, DT_CENTER);

		EndPaint(hBtn1, &ps);
	}
	break;
	default:
		break;
	}
	return DefWindowProc(hBtn1, message, wParam, lParam);


}

BOOL Gdi_init(HWND hWnd) 
{
	//方块颜色
	int blockColor[] = { 14345454,13164781,7975410,RGB(245,149,99),RGB(246,124,95),RGB(246,94,59),RGB(237,207,114),RGB(237,204,97),RGB(237,200,80),0x2ef8b4,
				  0x20fbb0,0x12ffac };
	
	//方块对象
	DigitalConfig* digitalConfig = new DigitalConfig();
	digitalConfig->set_digitalBk(CreateSolidBrush(11846093));
	mapColor[0] = digitalConfig;
	int j = 2;
	//保存每个数字的digitalConfig
	for (size_t i = 0; i < 12; i++)
	{
		digitalConfig = new DigitalConfig();
		digitalConfig->set_digitalBk(CreateSolidBrush(blockColor[i]));
		digitalConfig->set_digital(j);
		digitalConfig->set_digitalSize(50);
		if (j < 8) 
		{
			digitalConfig->set_digitalColor(6647415);
		}
		else
		{
			digitalConfig->set_digitalColor(0xffffff);
		}
		if (j < 100) {
			digitalConfig->set_digitalSize(60);
		}
		else if (j >= 100 && j < 1000)
		{
			digitalConfig->set_digitalSize(50);
		}
		else
		{
			digitalConfig->set_digitalSize(40);
		}
		mapColor[j] = digitalConfig;
		j *= 2;
	}

	
	RECT rt;
	GetClientRect(hWnd,&rt);
	g_hdc = GetDC(hWnd);
	hBitmapDC = CreateCompatibleDC(g_hdc); //内存DC
	HBITMAP hBitmap = CreateCompatibleBitmap(g_hdc, rt.right, rt.bottom);
	SelectObject(hBitmapDC,hBitmap);
	//// 画名字
	
	checkerboard = new Checkerboard();
	
	maxFractionWandR(true);
	Gdi_paint(hWnd);
	
	return TRUE;
}

wchar_t* char2wchar(const char* cchar)
{
	wchar_t* m_wchar;
	int len = MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), NULL, 0);
	m_wchar = new wchar_t[len+1];
	MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), m_wchar, len);
	m_wchar[len] = '\0';
	return m_wchar;
}
int i = 1;
void Gdi_paintMask(HWND hWnd) 
{
	RECT rt;
	GetClientRect(hWnd, &rt);
	//FillRect(hBitmapDC, &rt, (HBRUSH)GetClassLong(hWnd, GCL_HBRBACKGROUND));
	
	HBRUSH windowHbrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hBitmapDC, windowHbrush);

	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 0x7f; //半透明 
	bf.AlphaFormat = 0;
	Rectangle(hBitmapDC, 0, 0, rt.right, rt.bottom);
	//2048大字
	HFONT hFont = CreateFont(80, 0, 0, 0, 900, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"等线");
	SelectObject(hBitmapDC, hFont);
	SetTextColor(hBitmapDC, RGB(143,122,102));
	SetBkMode(hBitmapDC, TRANSPARENT);
	RECT rect;
	rect.left = 0;
	rect.top = 200;
	rect.right = rt.right;
	rect.bottom = 300;
	DrawText(hBitmapDC, L"游戏结束", 4, &rect, DT_CENTER);
	DeleteObject(hFont);
	DeleteObject(windowHbrush);
	windowHbrush = CreateSolidBrush(RGB(255, 238, 108));
	SelectObject(hBitmapDC, windowHbrush);

	AlphaBlend(g_hdc, 0, 0, rt.right, rt.bottom, hBitmapDC, 0, 0, rt.right, rt.bottom, bf);




}


void Gdi_paint(HWND hWnd) 
{
	if (checkerboard == nullptr)
	{
		return;
	}

	//ShowWindow(hbu1, SW_HIDE);
	
	RECT rt;
	GetClientRect(hWnd, &rt);
	
	FillRect(hBitmapDC, &rt,(HBRUSH)GetClassLong(hWnd,GCL_HBRBACKGROUND));
	//2048大字
	HFONT hFont = CreateFont(80, 0, 0, 0, 900, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"等线");
	SelectObject(hBitmapDC, hFont);
	SetTextColor(hBitmapDC, 6647415);
	
	SetBkMode(hBitmapDC, TRANSPARENT);
	
	RECT rect;
	rect.left = 20;
	rect.top = 15;
	rect.right = 200;
	rect.bottom = 100;
	DrawText(hBitmapDC, L"2048", 4, &rect, DT_CENTER);
	DeleteObject(hFont);
	SetTextColor(hBitmapDC, 14345454);
	g_hPen = CreatePen(HS_VERTICAL, 2, 10530235);
	g_hBrush = CreateSolidBrush(10530235);
	SelectObject(hBitmapDC, g_hPen);
	SelectObject(hBitmapDC, g_hBrush);
	RoundRect(hBitmapDC, 495 - 208, 20, 495 - 113, 78, 5, 5);
	RoundRect(hBitmapDC, 495 - 105, 20, 495, 78, 5, 5);
	hFont = CreateFont(15, 0, 0, 0, 900, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"黑体");
	SelectObject(hBitmapDC, hFont);
	rect.left = 495 - 208;
	rect.top = 30;
	rect.right = 495 - 113;
	rect.bottom = 50;
	DrawText(hBitmapDC, L"我的分数", 4, &rect, DT_CENTER);
	rect.left = 495 - 105;
	rect.top = 30;
	rect.right = 495;
	rect.bottom = 50;
	DrawText(hBitmapDC, L"最高分数", 4, &rect, DT_CENTER);
	DeleteObject(hFont);
	hFont = CreateFont(22, 0, 0, 0, 900, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"黑体");
	SetTextColor(hBitmapDC, 0xffffff);
	SelectObject(hBitmapDC, hFont);
	rect.left = 495 - 208;
	rect.top = 48;
	rect.right = 495 - 113;
	rect.bottom = 70;
	maxFraction = maxFraction < fraction?fraction:maxFraction;
	char strFraction[10];
	snprintf(strFraction, 9, "%d", fraction);
	
	wchar_t* wFraction = char2wchar(strFraction);
	DrawText(hBitmapDC, (LPCWSTR)wFraction, wcslen(wFraction), &rect, DT_CENTER);
	//delete wFraction;
	rect.left = 495 - 105;
	rect.top = 48;
	rect.right = 495;
	rect.bottom = 70;
	snprintf(strFraction, 9, "%d", maxFraction);
	 wFraction = char2wchar(strFraction);
	DrawText(hBitmapDC, (LPCWSTR)wFraction, wcslen(wFraction), &rect, DT_CENTER);
	//delete wFraction;
	


	
	//画数字区域
	SelectObject(hBitmapDC, g_hPen);
	SelectObject(hBitmapDC, g_hBrush);
	
	RoundRect(hBitmapDC, 20, 190, 495, 665, 6, 6);
	//hanleNum();
	
	checkerboard->drawArray([=](int** arr) {
	
	
	int y = 205;
	
	//循环画每个方块
	for (size_t i = 0; i < PIECE_LENGTH; i++)
	{
		
		int x = 35;
		for (size_t j = 0; j < PIECE_LENGTH; j++)
		{
              
			
			HFONT hFont = CreateFont(mapColor[arr[i][j]]->get_digitalSize(), 0, 0, 0, 1000, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"等线");
			SelectObject(hBitmapDC, hFont);
			SelectObject(hBitmapDC, mapColor[arr[i][j]]->get_digitalBk());
			SetTextColor(hBitmapDC, mapColor[arr[i][j]]->get_digitalColor());
			RECT rect;
			rect.left = x;
			rect.top = y+(100- mapColor[arr[i][j]]->get_digitalSize())/2;
			rect.right = x + 100;
			rect.bottom = y + 100;
			char text1[10];
			RoundRect(hBitmapDC, x, y, x + 100, y + 100,5,5);
			if (arr[i][j] == 0) {
				DrawText(hBitmapDC, L" ", 1, &rect, DT_CENTER);
				
			}
			else {
				snprintf(text1, 9, "%d", arr[i][j]);
				
				wchar_t* text = char2wchar(text1);
				
				DrawText(hBitmapDC, (LPCWSTR)text, wcslen(text), &rect, DT_CENTER);
				//delete text;
			}
			
			DeleteObject(hFont);
			
			
			//TextOutA(g_hdc, 30, 150, pbuf, 1);
			
			x += 115;
		}
		y += 115;
	}
		});
	
	TransparentBlt(g_hdc, 0, 0, rt.right, rt.bottom, hBitmapDC, 0, 0, rt.right, rt.bottom, 15726842);
	
}
BOOL Gdi_CleanUp(HWND hWnd)
{
	DeleteObject(g_hBrush);
	delete mapColor[0];
	mapColor[0] = nullptr;
	int j = 2;
	for (size_t i = 0; i < 12; i++)
	{
		delete mapColor[j];
		mapColor[j] = nullptr;
		j *= 2;
	}
	maxFractionWandR(false);
	ReleaseDC(hWnd, g_hdc); 
	delete checkerboard;

	return true;
}

void maxFractionWandR(bool isW)
{
	if (isW)
	{
		ifstream infile("max.txt");
		infile >> maxFraction;

		infile.close();

	}
	else
	{
		ofstream outfile("max.txt");
		outfile << maxFraction;
		outfile.flush();
		outfile.close();

	}


}

