#include <iostream>
#include <windows.h>	
#define ID_KEYBOARD 1001
#define ID_KINECT 1002

BOOL isKeyboardORkinect;

BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam,LPARAM IParam) 
{ 
	switch (uMsg) { 
	case WM_INITDIALOG:
		CheckRadioButton(hDlg,ID_KEYBOARD,ID_KINECT,ID_KEYBOARD); // Initialization RadioButton selection dialog
		isKeyboardORkinect = true;
		return TRUE;
	case WM_COMMAND: 
		switch (LOWORD(wParam)) { 
			case IDOK: 
	
				PostQuitMessage(0);
				break;
			case IDCANCEL: 
				if (IsDlgButtonChecked(hDlg,ID_KINECT))
					isKeyboardORkinect = false;
			EndDialog(hDlg, 0); 
		return TRUE; 
		}
		break;
	/*case WM_DESTROY:
		
		PostQuitMessage(0);*/
	return 0;
break; 
} 
return FALSE; 
} 

