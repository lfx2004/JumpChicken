#include <Windows.h>
#include <chrono>
#include "GameObject.h"
//ÐÞ¸ÄÐÞ¸Ä2
#define tp std::chrono::steady_clock::time_point
const float targetFPS = 40;
const int targetFrameTime = 1000.0 / targetFPS;
int frameTime; //ms
HBRUSH hBrush_Black = CreateSolidBrush(RGB(0, 0, 0));
HBRUSH hBrush_BG = CreateSolidBrush(RGB(255, 255, 255));
HDC hdc;
HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, L"colorTest.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
GameObject testObj(32, 32, 88, 55, hBitmap, 64, 64, true);

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		FillRect(hdc, &clientRect, hBrush_BG);
		testObj.UpdatePhy(frameTime);
		testObj.DrawImage(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		testObj.setVx(-20);
		break;
	case WM_DESTROY:
		DeleteObject(hBrush_Black);
		DeleteObject(hBrush_BG);
		DeleteDC(hdc);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE preInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const wchar_t WndClassName[] = L"MyWndClassName";
	WNDCLASS wc = { 0 };
	wc.hInstance = hInstance;
	wc.hbrBackground = hBrush_BG;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = WndClassName;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(
		WndClassName,
		L"Wnd Title",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_EX_COMPOSITED | WS_MAXIMIZEBOX, //https://learn.microsoft.com/zh-cn/windows/win32/winmsg/window-styles
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1080,
		720,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (hWnd == 0)
		return -1;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	hdc = GetDC(hWnd);


	MSG msg;
	tp curTime = std::chrono::steady_clock::now();   //std::chrono::steady_clock::time_point curTime = std::chrono::steady_clock::now();
	tp preTime;
	while (true)
	{
		preTime = curTime;
		curTime = std::chrono::steady_clock::now();
		auto dTime = std::chrono::duration_cast<std::chrono::milliseconds>(curTime - preTime);
		frameTime = dTime.count();
		InvalidateRect(hWnd, NULL, TRUE);
		if (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
		if (targetFrameTime > frameTime) Sleep(targetFrameTime - frameTime);
	}
}