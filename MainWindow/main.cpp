#include <Windows.h>
#include "resource.h"

#define IDC_BUTTON 1000

CONST CHAR g_sz_WINDOW_CLASS[] = "My first window";

VOID UpdateWindowTitle(HWND hwnd);
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinst, LPSTR lpCmdLine, INT nCmdShow)
{
	///////////////////////////////////////////////////////////////////
	/////////1)			ИНИЦИАЛИЗАЦИЯ КЛАССА ОКНА		   ////////////
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));	//нужна для обнуления

	//Инициализируем размеры и стиль.
	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);	//cb_ - Count Bytes. Кол-во байт
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	//Инициализируем внешний вид окон:
	//wClass.hIcon = (HICON)LoadImage(NULL, "bmw.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hIconSm = (HICON)LoadImage(NULL, "dollars.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_DOLLARS));
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_BMW));

	/*wClass.hCursor = (HCURSOR)LoadImage
	(
		hInstance,
		"warframe\\Working.ani",
		IMAGE_CURSOR,
		LR_DEFAULTSIZE, LR_DEFAULTSIZE,
		LR_LOADFROMFILE
	);*/
	wClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	//Инициализация системных переменных:
	wClass.hInstance = hInstance;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpszMenuName = NULL;
	wClass.lpfnWndProc = WndProc;

	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration failed", "", MB_OK | MB_ICONERROR);
		return 0;
	}

	///////////////////////////////////////////////////////////////////
	////////////2)			СОЗДАНИЕ ОКНА		      /////////////////

	int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	int WindowWidth = GetSystemMetrics(SM_CXSCREEN) * 3 / 4;
	int WindowHeight = GetSystemMetrics(SM_CYSCREEN) * 3 / 4;



	HWND hwnd = CreateWindowEx
	(
		NULL,					//exStyle
		g_sz_WINDOW_CLASS,		//Имя класса окна
		g_sz_WINDOW_CLASS,		//Заголовок окна
		WS_OVERLAPPEDWINDOW,	//Стиль окна. Стили всегда зависят от класс окна. "WS_OVERLAPPEDWINDOW" - это главное окно
		(ScreenWidth - WindowWidth) / 2, (ScreenHeight - WindowHeight) / 2,	//Position
		WindowWidth, WindowHeight,	//Размер окна
		NULL,
		NULL,	//Для главного окна это ResourceID главного меню, 
		//для дочернего окна - Resource ID дочернего окна(IDC_BUTTON_COPY)
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Windows creation failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);	//Задаёт режим отображения окна. Развёрнуто на весь экран, свёрнуто в окно...
	UpdateWindow(hwnd);	//Обновляет рабочую область окна, отправляет сообщение WM_PAINT, 
	//если клиентская область окна не пустая


///////////////////////////////////////////////////////////////////
/////////3)			ЗАПУСК ЦИКЛА СООБЩЕНИЙ		      /////////////
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);	//Преобразует сообщения виртуальных клавиш в символьные сообщения. 
		DispatchMessage(&msg);	//Отправляет сообщение в процедуру окна.
	}
	return msg.wParam;
}

VOID UpdateWindowTitle(HWND hwnd)
{
	RECT rect;
	GetWindowRect(hwnd, &rect);

	INT x = rect.left, y = rect.top;
	INT Width = rect.right - rect.left;
	INT Height = rect.bottom - rect.top;

	CONST INT SIZE = 256;
	CHAR sz_buffer[SIZE] = {};
	wsprintf(sz_buffer, "Позиция: X=%d Y=%d, Размер: Ширина: %d, Высота: %d", x, y, Width, Height);

	SetWindowText(hwnd, sz_buffer);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hButton = CreateWindowExA
		(
			NULL,					//exStyle
			"Button",				//Class
			"Кнопка",				//Title
			WS_CHILD | WS_VISIBLE,	//Style
			10, 10,					//Position
			150, 80,				//Size
			hwnd,					//Parent
			(HMENU)IDC_BUTTON,			//
			GetModuleHandle(NULL),	//hInstance
			NULL					//??????
		);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON:
			MessageBox(hwnd, "Cursor check", "Info", MB_OK | MB_ICONINFORMATION);
			break;
		}
	}
	break;
	case WM_WINDOWPOSCHANGED:
		UpdateWindowTitle(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}