#include<Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	/*MessageBox
	(
		NULL,
		"Hello WinAPI!",
		"MessageBox",
		MB_YESNOCANCEL 
		| MB_ICONERROR 
		| MB_HELP 
		| MB_DEFBUTTON3 
		| MB_SYSTEMMODAL
		| MB_RIGHT
	);*/
	//MB - message box

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DLGPROC(DlgProg), 0);
	
	//MB_ICONINFORMATION
	// Information, question, error, warning
	return 0;
}
BOOL CALLBACK DlgProg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:	//Выполняется один раз, при запуска окна
		break;
	case WM_COMMAND:	//Обрабатывает команды с клавиатуры и мыши.
		switch (LOWORD(wParam))
		{
		case IDOK:
			MessageBox(NULL, "Была нажата кнопка 'OK'", "Info", MB_OK | MB_ICONINFORMATION);
				break;
		}
		break;
	case WM_CLOSE:		//Выполняется при нажатии кнопки "X".
		EndDialog(hwnd, 0);
	}
	return FALSE;
}