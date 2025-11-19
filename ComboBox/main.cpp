#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>
#include"resource1.h"

CONST CHAR* g_sz_VALUES[] = { "This", "is", "my", "fisrt", "Combo", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
		for (int i = 0; i < sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
		}
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};	//sz_ - String Zero (NULL Terminated Line) Обычная сишная строка
			CHAR sz_message[SIZE]{};
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
			INT i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);	//GetCurrentSelection - получить текущий выбранный элемент
			if (i != CB_ERR)
			{
				SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);
				sprintf(sz_message, "Вы выбрали элемент №%i со значением \"%s\".", i, sz_buffer);	//1.буффер куда помещаем сообщение
				MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				MessageBox(hwnd, "Вы ничего не выбрали", "Info", MB_OK | MB_ICONWARNING);
			}
		}
		break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}



//IDOK ВЫВОД ВЫБРАННОЙ ИНФОРМАЦИИ В COMBOBOX
/*HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
			int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			if (index != CB_ERR)
			{
				char selectedText[256];
				SendMessage(hCombo, CB_GETLBTEXT, index, (LPARAM)selectedText);

				char message[512];
				char numberStr[16];

				_itoa(index, numberStr, 10);

				lstrcpy(message, "Вы выбрали элемент № ");
				lstrcat(message, numberStr);
				lstrcat(message, " со значением '");
				lstrcat(message, selectedText);
				lstrcat(message, "'");

				MessageBox(hwnd, message, "Выбор элемента", MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				MessageBox(hwnd, "Пожалуйста, выберите элемент из списка", "Предупреждение", MB_OK | MB_ICONWARNING);
			}*/