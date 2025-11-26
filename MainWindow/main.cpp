#include <Windows.h>

CONST CHAR g_sz_WINDOW_CLASS[] = "My first window";

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
	wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
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
	HWND hwnd = CreateWindowEx
	(
		NULL,					//exStyle
		g_sz_WINDOW_CLASS,		//Имя класса окна
		g_sz_WINDOW_CLASS,		//Заголовок окна
		WS_OVERLAPPEDWINDOW,	//Стиль окна. Стили всегда зависят от класс окна. "WS_OVERLAPPEDWINDOW" - это главное окно
		CW_USEDEFAULT, CW_USEDEFAULT,	//Position
		CW_USEDEFAULT, CW_USEDEFAULT,	//Размер окна
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
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);


	///////////////////////////////////////////////////////////////////
	/////////3)			ЗАПУСК ЦИКЛА СООБЩЕНИЙ		      /////////////
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
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