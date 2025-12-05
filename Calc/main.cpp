#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "resource.h"
#include <stdio.h>

CONST CHAR g_sz_WINDOW_CLASS[] = "Calc PV_521";

CONST INT g_i_BUTTON_SIZE = 50;
CONST INT g_i_INTERVAL = 1;
CONST INT g_i_DISPLAY_INTERVAL = 10;
CONST INT g_i_DOUBLE_BUTTON_SIZE = g_i_BUTTON_SIZE * 2 + g_i_INTERVAL;
CONST INT g_i_DISPLAY_WIDTH = g_i_BUTTON_SIZE * 5 + g_i_INTERVAL * 4;
CONST INT g_i_DISPLAY_HEIGHT = 22;
CONST INT g_i_START_X = 10;
CONST INT g_i_START_Y = 10;
CONST INT g_i_BUTTON_START_X = g_i_START_X;
CONST INT g_i_BUTTON_START_Y = g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_DISPLAY_INTERVAL;

CONST INT g_i_WINDOW_WIDTH = g_i_DISPLAY_WIDTH + g_i_START_X * 2 + 16;
CONST INT g_i_WINDOW_HEIGHT = g_i_DISPLAY_HEIGHT + g_i_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 4 + 48 + g_i_DISPLAY_INTERVAL;

#define X_BUTTON_POSITION(position) g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * position
#define Y_BUTTON_POSITION(position) g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * position

CONST CHAR g_OPERATIONS[] = "+-*/";

LRESULT CALLBACK WndProc(HWND hwnd, INT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1)Регистрация класс окна:
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = 0;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	wClass.hInstance = hInstance;
	wClass.lpszMenuName = NULL;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;

	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registratio failed", NULL, MB_OK | MB_ICONINFORMATION);
		return 0;
	}

	//2)Создагие окна:
	HWND hwnd = CreateWindowEx
	(
		NULL,													//exStyle
		g_sz_WINDOW_CLASS,										//Class
		g_sz_WINDOW_CLASS,										//Title
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,	//Style
		CW_USEDEFAULT, CW_USEDEFAULT,							//Position
		g_i_WINDOW_WIDTH, g_i_WINDOW_HEIGHT,					//Size
		NULL,													//Parent
		NULL,
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "WindowCreation failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	//3)Запуск цикла сообщений:
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, INT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		CreateWindowEx
		(
			NULL,
			"Edit",
			"0",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
			10, 10,
			g_i_DISPLAY_WIDTH, g_i_DISPLAY_HEIGHT,
			hwnd,
			(HMENU)IDC_DISPLAY,
			GetModuleHandle(NULL),
			NULL
		);
		CHAR sz_button[2] = {};
		for (int i = 6; i >= 0; i -= 3)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_button[0] = i + j + '1';
				CreateWindowEx
				(
					NULL, "Button", sz_button,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					X_BUTTON_POSITION(j), Y_BUTTON_POSITION((2 - i / 3)),
					g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
					hwnd,
					(HMENU)(IDC_BUTTON_1 + i + j),
					GetModuleHandle(NULL),
					NULL
				);
			}
		}
		CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			X_BUTTON_POSITION(0), Y_BUTTON_POSITION(3),
			g_i_DOUBLE_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			X_BUTTON_POSITION(2), Y_BUTTON_POSITION(3),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL),
			NULL
		);
		CHAR sz_operation[2] = "";
		for (int i = 0; i < 4; i++)
		{
			sz_operation[0] = g_OPERATIONS[i];
			CreateWindowEx
			(
				NULL, "BUTTON", sz_operation,
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				X_BUTTON_POSITION(3), Y_BUTTON_POSITION((3 - i)),
				g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
				//sz_operation[0] == '+' ? g_i_DOUBLE_BUTTON_SIZE : g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
				hwnd,
				HMENU(IDC_BUTTON_PLUS + i),
				GetModuleHandle(NULL),
				NULL
			);
		}
		CreateWindowEx
		(
			NULL, "Button", "<-",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			X_BUTTON_POSITION(4), Y_BUTTON_POSITION(0),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_BSP,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "BUTTON", "C",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			X_BUTTON_POSITION(4), Y_BUTTON_POSITION(1),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_CLR,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "=",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			X_BUTTON_POSITION(4), Y_BUTTON_POSITION(2),
			g_i_BUTTON_SIZE, g_i_DOUBLE_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL),
			NULL
		);
	}
	break;
	case WM_COMMAND:
	{
		static DOUBLE savedNumber = 0.0;
		static INT CurrentOperationID = 0;
		static BOOL IsChoosenOperation = FALSE;
		static BOOL IsNewNumber = TRUE;

		CONST INT SIZE = 256;
		CHAR sz_CurrentEdit[256] = {};

		HWND hDisplay = GetDlgItem(hwnd, IDC_DISPLAY);

		SendMessage(hDisplay, WM_GETTEXT, sizeof(sz_CurrentEdit), (LPARAM)sz_CurrentEdit);

		WORD PressedButtonId = LOWORD(wParam);

		if (PressedButtonId >= IDC_BUTTON_0 && PressedButtonId <= IDC_BUTTON_9)
		{
			CHAR Digit[2] = {};
			if (IsChoosenOperation || IsNewNumber)
			{
				sz_CurrentEdit[0] = 0;
				IsChoosenOperation = FALSE;
				IsNewNumber = FALSE;
			}
			Digit[0] = '0' + (PressedButtonId - IDC_BUTTON_0);
			Digit[1] = '\0';

			if (lstrcmp(sz_CurrentEdit, "0") == 0)
			{
				SendMessage(hDisplay, WM_SETTEXT, NULL, (LPARAM)Digit);
			}
			else
			{
				lstrcat(sz_CurrentEdit, Digit);
				SendMessage(hDisplay, WM_SETTEXT, NULL, (LPARAM)sz_CurrentEdit);
			}
		}//0-9
		else if (PressedButtonId >= IDC_BUTTON_PLUS && PressedButtonId <= IDC_BUTTON_SLASH)
		{
			DOUBLE CurrentValue = atof(sz_CurrentEdit);
			if (CurrentOperationID != 0 && !IsNewNumber)
			{
				switch (CurrentOperationID)
				{
				case IDC_BUTTON_PLUS:
					savedNumber += CurrentValue;
					break;
				case IDC_BUTTON_MINUS:
					savedNumber -= CurrentValue;
					break;
				case IDC_BUTTON_ASTER:
					savedNumber *= CurrentValue;
					break;
				case IDC_BUTTON_SLASH:
					if (CurrentValue != 0)
						savedNumber /= CurrentValue;
					else
					{
						MessageBox(NULL, "Error", "Error", MB_OK | MB_ICONERROR);
						savedNumber = 0;
					}
					break;
				}
				CHAR buffer[SIZE] = {};
				sprintf(buffer, "%g", savedNumber);
				SendMessage(hDisplay, WM_SETTEXT, NULL, (LPARAM)buffer);
			}
			else
			{
				savedNumber = atof(sz_CurrentEdit);
			}
			CurrentOperationID = PressedButtonId;
			IsChoosenOperation = TRUE;
			IsNewNumber = FALSE;

		}//+-/*
		else if (PressedButtonId == IDC_BUTTON_POINT)
		{
			if (IsChoosenOperation || IsNewNumber)
			{
				SendMessage(hDisplay, WM_SETTEXT, NULL, (LPARAM)"0.");
				IsChoosenOperation = FALSE;
				IsNewNumber = FALSE;
			}
			else if (strchr(sz_CurrentEdit, '.') == NULL)
			{
				lstrcat(sz_CurrentEdit, ".");
				SendMessage(hDisplay, WM_SETTEXT, NULL, (LPARAM)sz_CurrentEdit);
			}
		}//'.'
		else if (PressedButtonId == IDC_BUTTON_EQUAL)
		{
			if (CurrentOperationID != 0)
			{
				DOUBLE CurrentValue = atof(sz_CurrentEdit);
				CHAR buffer[SIZE] = {};

				switch (CurrentOperationID)
				{
				case IDC_BUTTON_PLUS:
					savedNumber += CurrentValue;
					break;
				case IDC_BUTTON_MINUS:
					savedNumber -= CurrentValue;
					break;
				case IDC_BUTTON_ASTER:
					savedNumber *= CurrentValue;
					break;
				case IDC_BUTTON_SLASH:
					if (CurrentValue != 0)
						savedNumber /= CurrentValue;
					else
					{
						MessageBox(NULL, "Error", "Error", MB_OK | MB_ICONERROR);
						savedNumber = 0;
					}
					break;
				}
				
				sprintf(buffer, "%g", savedNumber);
				SendMessage(hDisplay, WM_SETTEXT, NULL, (LPARAM)buffer);

				CurrentOperationID = 0;
				IsChoosenOperation = FALSE;
				IsNewNumber = TRUE;
			}
		}//=
		else if (PressedButtonId == IDC_BUTTON_CLR)
		{
			SendMessage(hDisplay, WM_SETTEXT, NULL, (LPARAM)"0");
			ZeroMemory(sz_CurrentEdit, sizeof(sz_CurrentEdit));
			savedNumber = 0;
			IsChoosenOperation = FALSE;
			CurrentOperationID = 0;
			IsNewNumber = TRUE;
		}//Clear
		else if (PressedButtonId == IDC_BUTTON_BSP)
		{
			if (strlen(sz_CurrentEdit) > 1)
			{
				sz_CurrentEdit[strlen(sz_CurrentEdit) - 1] = '\0';
				SendMessage(hDisplay, WM_SETTEXT, NULL, (LPARAM)sz_CurrentEdit);
			}
			else
			{
				SendMessage(hDisplay, WM_SETTEXT, NULL, (LPARAM)"0");
				IsNewNumber = TRUE;
			}
		}//Backspase
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}


/*
switch (wParam)
{
case IDC_BUTTON_0:
case IDC_BUTTON_1:
case IDC_BUTTON_2:
case IDC_BUTTON_3:
case IDC_BUTTON_4:
case IDC_BUTTON_5:
case IDC_BUTTON_6:
case IDC_BUTTON_7:
case IDC_BUTTON_8:
case IDC_BUTTON_9:
{
	CHAR digit = '0' + (LOWORD(wParam) - IDC_BUTTON_0);
	CHAR sz_digit[2];
	sz_digit[0] = digit;
	sz_digit[1] = '\0';

	INT textLength = SendMessage(GetDlgItem(hwnd, IDC_DISPLAY), WM_GETTEXTLENGTH, 0, 0);

	CHAR* sz_buffer = new CHAR[textLength + 2];

	SendMessage(GetDlgItem(hwnd, IDC_DISPLAY), WM_GETTEXT, textLength + 1, (LPARAM)sz_buffer);

	if (strcmp(sz_buffer, "0") == 0)
	{
		SendMessage(GetDlgItem(hwnd, IDC_DISPLAY), WM_SETTEXT, NULL, (LPARAM)sz_digit);
	}
	else
	{
		strcat(sz_buffer, sz_digit);
		SendMessage(GetDlgItem(hwnd, IDC_DISPLAY), WM_SETTEXT, NULL, (LPARAM)sz_buffer);
	}
	delete[] sz_buffer;
	break;
}
//Кнопки 0-9



//Конец свича
}
*/
/*CHAR digit = '0' + (PressedButtonId - IDC_BUTTON_0);
			CHAR sz_digit[2];
			sz_digit[0] = digit;
			sz_digit[1] = '\0';

			INT textLength = SendMessage(GetDlgItem(hwnd, IDC_DISPLAY), WM_GETTEXTLENGTH, 0, 0);

			CHAR* sz_buffer = new CHAR[textLength + 2];

			SendMessage(GetDlgItem(hwnd, IDC_DISPLAY), WM_GETTEXT, textLength + 1, (LPARAM)sz_buffer);

			if (strcmp(sz_buffer, "0") == 0)
			{
				SendMessage(GetDlgItem(hwnd, IDC_DISPLAY), WM_SETTEXT, NULL, (LPARAM)sz_digit);
			}
			else
			{
				strcat(sz_buffer, sz_digit);
				SendMessage(GetDlgItem(hwnd, IDC_DISPLAY), WM_SETTEXT, NULL, (LPARAM)sz_buffer);
			}
			delete[] sz_buffer;*/
