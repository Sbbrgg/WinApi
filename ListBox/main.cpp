#include<Windows.h>
#include"resource.h"

CONST CHAR* g_sz_VALUES[] = { "багажник", "подушка", "зеркало" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK EditDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hListBox = GetDlgItem(hwnd, IDC_LISTBOX1);
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		//hListBox = GetDlgItem(hwnd, IDC_LISTBOX1);
		for (int i = 0; i < sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]); i++)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
		}
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_ADDBUTTON:
		{
			DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_EDIT_DIALOG), hwnd, (DLGPROC)EditDlgProc, (LPARAM)-1);
		}
		break;
		case IDC_BUTTON_DELETE:
			break;
		case IDC_LISTBOX1:
		{
			if (HIWORD(wParam) == LBN_DBLCLK)
			{
				INT index = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
				if (index != LB_ERR)
				{
					DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_EDIT_DIALOG), hwnd, (DLGPROC)EditDlgProc, (LPARAM)index);
				}
			}

		}
		break;
		case IDOK:
		{
			INT index = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			if (index != LB_ERR)
			{
				DialogBoxParam(GetPar, MAKEINTRESOURCE(IDD_EDIT_DIALOG), hwnd, (DLGPROC)EditDlgProc, (LPARAM)index);
			}
			else DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_EDIT_DIALOG), hwnd, (DLGPROC)EditDlgProc, (LPARAM)-1);
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

BOOL CALLBACK EditDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static INT editIndex;
	static HWND hMainListBox;

	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		hMainListBox = GetDlgItem(GetParent(hwnd), IDC_LISTBOX1);
		editIndex = lParam;
		if (editIndex != -1)
		{
			char sz_Buffer[256];
			SendMessage(hMainListBox, LB_GETTEXT, editIndex, (LPARAM)sz_Buffer);
			SetDlgItemText(hwnd, IDC_EDIT_ITEM, sz_Buffer);
		}
		else
		{
			SetDlgItemText(hwnd, IDC_EDIT_ITEM, "");
		}
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CHAR szBuffer[256];
			GetDlgItemText(hwnd, IDC_EDIT_ITEM, szBuffer, sizeof(szBuffer));

			if (strlen(szBuffer) > 0)
			{
				if (editIndex == -1)
				{
					INT newIndex = SendMessage(hMainListBox, LB_ADDSTRING, 0, (LPARAM)szBuffer);
					if (newIndex != LB_ERR)
					{
						SendMessage(hMainListBox, LB_SETCURSEL, newIndex, 0);
					}
				}
				else
				{
					SendMessage(hMainListBox, LB_DELETESTRING, editIndex, 0);
					SendMessage(hMainListBox, LB_INSERTSTRING, editIndex, (LPARAM)szBuffer);
					SendMessage(hMainListBox, LB_SETCURSEL, editIndex, 0);
				}
			}

		EndDialog(hwnd, 0);
		}
		break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;

	}
	return TRUE;
}