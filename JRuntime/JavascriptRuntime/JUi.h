#pragma once
#include <Windows.h>
#include <string>
#include <map>

#define D3D_DEBUG_INFO

#include <d3d9.h>
#include <d3dx9.h>
#include <dwmapi.h>
#include <DxErr.h>

#include <ChakraCore.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "dxerr.lib")


class JWindow
{
public:
	JWindow() {};
	int X;
	int Y;
	int Height;
	int Width;
	HWND Hwnd;
	MARGINS Margin;

	static JWindow GetCurrentWindow();
	void Refresh();

private:
	JWindow(HWND h);
	static int __stdcall EnumWindowCallback(HWND window, LPARAM param);
};

class JUi
{
public:
	static void Create();
	static void AttachRenderCallback(JsValueRef callback);

	static void DrawBox(int x, int y, int width, int height,int colorId);
	static void DrawLine(int x1, int y1, int x2, int y2, int thickness, int colorId);
	static void DrawRectangle(int x, int y, int width, int height, int thickness, int colorId);
	static void DrawString(int x, int y, int size, int colorId, std::string text);
private:

	static long __stdcall WinMessageCallback(HWND window, UINT Message, WPARAM wParam, LPARAM lParam);

	static void InitializeColors();
	static void InitializeMessageLoop();
	static int Render();

	static void InitializeDirectX();

	static JWindow targetWindow;
	static JWindow overlayWindow;
	static MSG windowMessage;
	static MARGINS  frameMargin;

	static IDirect3D9Ex* d3dObject;
	static IDirect3DDevice9Ex* d3dDevice;
	
	static JsValueRef renderCallback;

	static std::map<int, D3DCOLOR> colors;
};
