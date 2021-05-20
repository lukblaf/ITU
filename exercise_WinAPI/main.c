#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Global variable
HINSTANCE hInst;
UINT  MessageCount = 0;
UINT  Count = 0;
int move = 0;
int hood_posY = 575;

// Function prototypes.
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
void paintCar(HWND hWnd, HDC hDC, PAINTSTRUCT ps, int move_speed);
void paintPosition(HWND hWnd, HDC hDC, PAINTSTRUCT ps, POINT* posCursor);
void paintPlatform(HWND hWnd, HDC hDC, PAINTSTRUCT ps, int posX0, int posY0, int posX1, int posY1);

// Application entry point. This is the same as main() in standart C.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	BOOL bRet;
	WNDCLASS wcx;          // register class
	HWND hWnd;

	hInst = hInstance;     // Save the application-instance handle.
		// Fill in the window class structure with parameters that describe the main window.

	wcx.style = CS_HREDRAW | CS_VREDRAW;              // redraw if size changes
	wcx.lpfnWndProc = (WNDPROC)MainWndProc;          // points to window procedure
	wcx.cbClsExtra = 0;                               // no extra class memory
	wcx.cbWndExtra = 0;                               // no extra window memory
	wcx.hInstance = hInstance;                        // handle to instance
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);      // predefined app. icon
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);        // predefined arrow
	wcx.hbrBackground = GetStockObject(WHITE_BRUSH);  // white background brush
	wcx.lpszMenuName = (LPCSTR)"MainMenu";          // name of menu resource
	wcx.lpszClassName = (LPCSTR)"MainWClass";        // name of window class

	// Register the window class.

	if (!RegisterClass(&wcx)) return FALSE;

	// create window of registered class

	hWnd = CreateWindow(
		"MainWClass",        // name of window class
		"ITU",               // title-bar string
		WS_OVERLAPPEDWINDOW, // top-level window
		200,                  // default horizontal position
		25,                 // default vertical position
		1000,                // default width
		700,                 // default height
		(HWND)NULL,         // no owner window
		(HMENU)NULL,        // use class menu
		hInstance,           // handle to application instance
		(LPVOID)NULL);      // no window-creation data
	if (!hWnd) return FALSE;

	// Show the window and send a WM_PAINT message to the window procedure.
	// Record the current cursor position.

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// loop of message processing
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			// handle the error and possibly exit
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}


LRESULT CALLBACK MainWndProc(
	HWND hWnd,        // handle to window
	UINT uMsg,        // message identifier
	WPARAM wParam,    // first message parameter
	LPARAM lParam)    // second message parameter
{
	HDC         hDC;
	PAINTSTRUCT ps;


	POINT cursorPosition;

	// init cursor position 
	GetCursorPos(&cursorPosition);
	ScreenToClient(hWnd, &cursorPosition);

	switch (uMsg)
	{
	case WM_CREATE:
		break;

		// character input 
	case WM_CHAR:
		switch (wParam) {
		case 0x08:  // backspace
		case 0x0A:  // linefeed
		case 0x1B:  // escape
			break;

		case 0x09:  // tab
			break;

		default:
			break;
		}
		break;

		// key input
	case WM_KEYDOWN:
		switch (wParam) {
			// update posX and posY in order to move object
		case VK_LEFT: // left arrow
			move -= 5;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_RIGHT: // right arrow
			move += 5;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_UP: // up arrow
			break;
		case VK_DOWN: // down arrow
			break;

			// react on the other pressed keys 
		case VK_SPACE: // space		

			InvalidateRect(hWnd, NULL, TRUE);

			break;
		case VK_BACK: // backspace
			break;
		case VK_TAB: // tab
			break;
			// more virtual codes can be found here: https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
		default:
			break;
		}
		break;

		// get cursor position 
	case WM_MOUSEMOVE:
		break;

		// react on mouse clicks
	case WM_LBUTTONDOWN:
		hood_posY = 550;
		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_LBUTTONUP:
		hood_posY = 575;
		InvalidateRect(hWnd, NULL, TRUE);
		break;

		
		// paint objects
	case WM_PAINT:
		
		hDC = BeginPaint(hWnd, &ps);
		paintPlatform(hWnd, hDC, ps, 0, 610, 1366, 650);
		paintCar(hWnd, hDC, ps, move);
		EndPaint(hWnd, &ps);
		DeleteDC(hDC);
		break;

		//
		// Process other messages.
		//

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}


void paintCar(HWND hWnd, HDC hDC, PAINTSTRUCT ps, int move_speed)
{

	SetDCBrushColor(hDC, RGB(255, 255, 255));
	// BODY
	MoveToEx(hDC, 50 + move_speed, 575, NULL);
	LineTo(hDC, 50 + move_speed, 600);

	MoveToEx(hDC, 50 + move_speed, 575, NULL);
	LineTo(hDC, 75 + move_speed, 575);

	MoveToEx(hDC, 75 + move_speed, 575, NULL);
	LineTo(hDC, 100 + move_speed, 550);

	MoveToEx(hDC, 100 + move_speed, 550, NULL);
	LineTo(hDC, 200 + move_speed, 550);

	MoveToEx(hDC, 200 + move_speed, 550, NULL);
	LineTo(hDC, 225 + move_speed, 575);

	MoveToEx(hDC, 225 + move_speed, 575, NULL);
	LineTo(hDC, 275 + move_speed, 575);

	MoveToEx(hDC, 275 + move_speed, 575, NULL);
	LineTo(hDC, 275 + move_speed, 600);

	MoveToEx(hDC, 225 + move_speed, 600, NULL);
	LineTo(hDC, 225 + move_speed, 600);

	MoveToEx(hDC, 275 + move_speed, 600, NULL);
	LineTo(hDC, 215 + move_speed, 600);

	MoveToEx(hDC, 215 + move_speed, 600, NULL);
	LineTo(hDC, 215 + move_speed, 580);

	MoveToEx(hDC, 215 + move_speed, 580, NULL);
	LineTo(hDC, 185 + move_speed, 580);

	MoveToEx(hDC, 185 + move_speed, 580, NULL);
	LineTo(hDC, 185 + move_speed, 600);

	MoveToEx(hDC, 185 + move_speed, 600, NULL);
	LineTo(hDC, 140 + move_speed, 600);

	MoveToEx(hDC, 140 + move_speed, 600, NULL);
	LineTo(hDC, 140 + move_speed, 580);

	MoveToEx(hDC, 140 + move_speed, 580, NULL);
	LineTo(hDC, 110 + move_speed, 580);

	MoveToEx(hDC, 110 + move_speed, 580, NULL);
	LineTo(hDC, 110 + move_speed, 600);

	MoveToEx(hDC, 110 + move_speed, 600, NULL);
	LineTo(hDC, 50 + move_speed, 600);

	//WINDOWS
	int x1, y1, x2, y2, x3, y3;
	x1 = 75 + move_speed;
	y1 = 575;
	x2 = 100 + move_speed;
	y2 = 550;
	x3 = 100 + move_speed;
	y3 = 575;
	POINT vertices[] = { {x1, y1}, {x2, y2}, {x3, y3} };		SetDCBrushColor(hDC, RGB(0, 255, 255));	Polygon(hDC, vertices, 3);
	//WHEELS 
	// grey
	SetDCBrushColor(hDC, RGB(102, 102, 153));
	Ellipse(hDC, 110 + move_speed, 580, 140 + move_speed, 610);
	Ellipse(hDC, 185 + move_speed, 580, 215 + move_speed, 610);
	
	
	// CAR HOOD 
	MoveToEx(hDC, 225 + move_speed, 575, NULL);
	LineTo(hDC, 225 + move_speed, hood_posY);



	//LIGHTHOUSE
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	SelectObject(hDC, pen);
	SetDCBrushColor(hDC, RGB(rand() % 256, rand() % 256, rand() % 256));
	Rectangle(hDC, 190 + move_speed, 540, 200 + move_speed, 550);
	DeleteObject(pen);

	return;
}

void paintPosition(HWND hWnd, HDC hDC, PAINTSTRUCT ps, POINT *posCursor)
{
	char        text[40];          // buffer to store an output text
	HFONT       font;              // new large font
	HFONT       oldFont;           // saves the previous font

	font = CreateFont(25, 0, 0, 0, 0, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, 0);
	oldFont = (HFONT)SelectObject(hDC, font);
	sprintf(text, "Position -- x:%d, y:%d", posCursor->x, posCursor->y);
	TextOut(hDC, 50, 50, text, (int)strlen(text));
	SelectObject(hDC, oldFont);
	DeleteObject(font);
}


void paintPlatform(HWND hWnd, HDC hDC, PAINTSTRUCT ps, int posX0, int posY0, int posX1, int posY1) {
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	SelectObject(hDC, pen);
	SelectObject(hDC, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hDC, RGB(128, 0, 0));

	Rectangle(hDC, posX0, posY0, posX1, posY1);
	
	DeleteObject(pen);
}