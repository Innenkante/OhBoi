#include "stdafx.h"
#include "JUi.h"

JWindow JUi::targetWindow;
JWindow JUi::overlayWindow;


MSG JUi::windowMessage;

IDirect3D9Ex* JUi::d3dObject = {};
IDirect3DDevice9Ex* JUi::d3dDevice = {};

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

	InitializeMessageLoop();
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

	auto result = DwmExtendFrameIntoClientArea(overlayWindow.Hwnd, &(overlayWindow.Margin)); //ay this somewhat "works"

	d3dDevice->BeginScene();

	//JsCall...

	ID3DXFont* pFont;
	D3DXCreateFontA(d3dDevice, 50, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont);
	RECT FontPos;
	FontPos.left = 100;
	FontPos.top = 100;
	pFont->DrawTextA(0, "Hello World", strlen("Hello World"), &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));


	d3dDevice->EndScene();
	d3dDevice->PresentEx(0, 0, 0, 0, 0);

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
