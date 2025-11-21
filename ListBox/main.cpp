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
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_EDIT_DIALOG), hwnd, (DLGPROC)EditDlgProc, (LPARAM)-1);
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
					DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_EDIT_DIALOG), hwnd, (DLGPROC)EditDlgProc, (LPARAM)index);
				}
			}

		}
		break;
		case IDOK:
		{
			INT index = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			if (index != LB_ERR)
			{
				DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_EDIT_DIALOG), hwnd, (DLGPROC)EditDlgProc, (LPARAM)index);
			}
			else
			{
				
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