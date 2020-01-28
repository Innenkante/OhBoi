#include "stdafx.h"
#include "JUi.h"
#include "Globals.h"

JWindow JUi::targetWindow;
JWindow JUi::overlayWindow;


MSG JUi::windowMessage;

IDirect3D9Ex* JUi::d3dObject = {};
IDirect3DDevice9Ex* JUi::d3dDevice = {};

JsValueRef JUi::renderCallback;

std::map<int, D3DCOLOR> JUi::colors;

void JUi::Create()
{
	targetWindow = JWindow::GetCurrentWindow();
	WNDCLASSW wClass;
	wClass.cbClsExtra = NULL;
	wClass.cbWndExtra = NULL;
	wClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	wClass.hCursor = LoadCursor(0, IDC_ARROW);
	wClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	wClass.hInstance = GetModuleHandleA(0);
	wClass.lpfnWndProc = WinMessageCallback;
	wClass.lpszClassName = L"OhBoi";
	wClass.lpszMenuName = L"OhBoi";
	wClass.style = CS_VREDRAW | CS_HREDRAW;

	auto error = RegisterClass(&wClass);

	if (targetWindow.Hwnd)
	{

		overlayWindow = targetWindow;

		overlayWindow.Hwnd = CreateWindowExA(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, "OhBoi", "OhBoi", WS_POPUP, 1, 1, targetWindow.Width, targetWindow.Height, 0, 0, 0, 0); // 


		SetLayeredWindowAttributes(overlayWindow.Hwnd, 0, 1.0f, LWA_ALPHA);
		SetLayeredWindowAttributes(overlayWindow.Hwnd, 0, RGB(0, 0, 0), LWA_COLORKEY);
		auto error = ShowWindow(overlayWindow.Hwnd, SW_SHOW);
	}

	InitializeDirectX();

	InitializeColors();

	InitializeMessageLoop();


}

void JUi::AttachRenderCallback(JsValueRef callback)
{
	renderCallback = callback;
}

void JUi::DrawBox(int x, int y, int width, int height,int colorId)
{
	D3DRECT rect = { x,y,x + width,y + height };
	d3dDevice->Clear(1, &rect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, colors[colorId], 0, 0);
}

void JUi::DrawLine(int x1, int y1, int x2, int y2, int thickness, int colorId)
{
	ID3DXLine* line;
	D3DXCreateLine(d3dDevice, &line);
	D3DXVECTOR2 dots[] = { D3DXVECTOR2(x1,y1), D3DXVECTOR2(x2,y2) };
	line->SetWidth(thickness);

	line->Begin();
	line->Draw(dots, 2, colors[colorId]);
	line->End();
	line->Release();
}

void JUi::DrawRectangle(int x, int y, int width, int height, int thickness, int colorId)
{
	DrawLine(x, y, x + width, y, thickness, colorId); //  -------
	DrawLine(x, y, x, y + height, thickness, colorId); // |
	DrawLine(x, y + height, x + width, y + height, thickness, colorId); // -------
	DrawLine(x + width, y + height, x + width, y, thickness, colorId); //  |
}

void JUi::DrawString(int x, int y, int size, int colorId, std::string text)
{
	ID3DXFont* font;
	D3DXCreateFont(d3dDevice, size, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &font);
	RECT pos;
	pos.left = x;
	pos.top = y;
	font->DrawTextA(0, text.c_str(), text.length(), &pos, DT_NOCLIP, colors[colorId]);
}

long __stdcall JUi::WinMessageCallback(HWND window, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_PAINT:
		Render();
		break;
	case WM_CLOSE:
		exit(0);
		return 0;
	default:
		return DefWindowProc(window, Message, wParam, lParam);
		break;
	}
	return 0;
}

void JUi::InitializeColors()
{
	colors.insert(std::pair<int, D3DCOLOR>(0, D3DCOLOR_XRGB(0, 0, 0))); //black
	colors.insert(std::pair<int, D3DCOLOR>(1, D3DCOLOR_XRGB(255, 0, 0))); //red
	colors.insert(std::pair<int, D3DCOLOR>(2, D3DCOLOR_XRGB(0, 255, 0))); //green
	colors.insert(std::pair<int, D3DCOLOR>(3, D3DCOLOR_XRGB(0, 0, 255))); //blue
	colors.insert(std::pair<int, D3DCOLOR>(4, D3DCOLOR_XRGB(255, 255, 255))); //white
	colors.insert(std::pair<int, D3DCOLOR>(5, D3DCOLOR_XRGB(255, 255, 0))); //yellow
	colors.insert(std::pair<int, D3DCOLOR>(6, D3DCOLOR_XRGB(255, 0, 255))); //pink
	colors.insert(std::pair<int, D3DCOLOR>(7, D3DCOLOR_XRGB(0, 255, 255))); //cyan
}

void JUi::InitializeMessageLoop()
{
	for (;;)
	{
		if (PeekMessage(&windowMessage, overlayWindow.Hwnd, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&windowMessage);

			TranslateMessage(&windowMessage);
		}
		Sleep(1);
	}
}

int JUi::Render()
{
	d3dDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);

	targetWindow.Refresh();
	MoveWindow(overlayWindow.Hwnd, targetWindow.X, targetWindow.Y, targetWindow.Width, targetWindow.Height, true);

	DwmExtendFrameIntoClientArea(overlayWindow.Hwnd, &(overlayWindow.Margin)); //ay this somewhat "works"

	d3dDevice->BeginScene();

	//might wanna extract this method
	Globals::JavascriptRuntime->SetCurrentContext();
	JsValueRef undefined;
	auto result = JsGetUndefinedValue(&undefined);

	JsValueRef* refs = new JsValueRef[1];

	refs[0] = undefined;

	auto r = JsCallFunction(renderCallback, refs, 1, nullptr);
	delete[] refs;


	//

	/*
	ID3DXFont* pFont;
	D3DXCreateFontA(d3dDevice, 50, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont);
	RECT FontPos;
	FontPos.left = 100;
	FontPos.top = 100;
	pFont->DrawTextA(0, "Hello World", strlen("Hello World"), &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
	*/

	d3dDevice->EndScene();
	d3dDevice->PresentEx(0, 0, 0, 0, 0);

	Globals::JavascriptRuntime->DisposeContext();

	return 0;
}

void JUi::InitializeDirectX()
{
	Direct3DCreate9Ex(D3D_SDK_VERSION, &d3dObject);

	D3DPRESENT_PARAMETERS d3dParameters = { 0 };


	d3dParameters.Windowed = TRUE;
	d3dParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dParameters.hDeviceWindow = overlayWindow.Hwnd;
	d3dParameters.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	d3dParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dParameters.BackBufferWidth = overlayWindow.Width;
	d3dParameters.BackBufferHeight = overlayWindow.Height;
	d3dParameters.EnableAutoDepthStencil = TRUE;
	d3dParameters.AutoDepthStencilFormat = D3DFMT_D16;
	d3dParameters.BackBufferCount = 2;



	auto result = d3dObject->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, overlayWindow.Hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dParameters, 0, &d3dDevice);

	auto winError = GetLastError();
	auto error1 = DXGetErrorStringA(result);
	auto error = DXGetErrorDescriptionA(result); //that one gives me a classic "invalid call"
}

JWindow JWindow::GetCurrentWindow()
{
	HWND result = 0;
	auto consoleWindow = GetConsoleWindow();

	if (consoleWindow == 0)
	{
		EnumWindows([](HWND window, LPARAM param) -> BOOL
		{
			DWORD processId;
			GetWindowThreadProcessId(window, &processId);

			if (processId == GetCurrentProcessId())
			{
				WINDOWINFO i;
				i.cbSize = sizeof(WINDOWINFO);

				GetWindowInfo(window, &i);

				if ((i.rcClient.right - i.rcClient.left) != 0 && (i.rcClient.bottom - i.rcClient.top) != 0) //verifying if the window has an actual size
				{
					*reinterpret_cast<LPARAM*>(param) = reinterpret_cast<LPARAM>(window);
					return FALSE; //quiting the enumeration
				}
			}

			return TRUE;
		},reinterpret_cast<LPARAM>(&result));
	}
	else
		return JWindow(consoleWindow);


	return JWindow(result);
}

void JWindow::Refresh()
{
	RECT windowRect;
	GetWindowRect(Hwnd, &windowRect);

	X = windowRect.left;
	Y = windowRect.top;

	Width = windowRect.right - windowRect.left;
	Height = windowRect.bottom - windowRect.top;

	Margin = { 0,0,Width,Height };
}

JWindow::JWindow(HWND h)
{
	RECT windowRect;
	GetWindowRect(h, &windowRect);
	auto error = GetLastError();

	X = windowRect.left;
	Y = windowRect.top;

	Width = windowRect.right - windowRect.left;
	Height = windowRect.bottom - windowRect.top;

	Margin = { 0,0,Width,Height };

	Hwnd = h;
}

int __stdcall JWindow::EnumWindowCallback(HWND window, LPARAM param)
{
	DWORD processId;
	GetWindowThreadProcessId(window, &processId);

	if (processId == GetCurrentProcessId())
		MessageBoxA(0, "Hoora", "", 0);

	return 1;
}
