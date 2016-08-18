//#include <winsock2.h> //g++ -Wall -o "%e" "%f" -mwindows -lopengl32 -lglu32 -lglaux -lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid -lodbc32 -lwsock32
#include <windows.h>	
		

#include <glut.h>		
#include "glaux.h"	
#include "Functions.h"
#include "Scene.h"

#include <math.h> 
#include "Ghost.h"

#pragma comment(lib, "GLAUX.LIB")

#define IDD_DIALOG1 101


HDC			hDC=NULL;		
HGLRC		hRC=NULL;		
HWND		hWnd=NULL; //основное игровое окно openGL

HINSTANCE	hInstance;		

 

int cur_pr = 0;
		
bool	fullscreen=TRUE;	

			
GLuint	texture[11],st;			

Scene Game;

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	

///*----------------таймер-------------------------*/
//
//
//struct                    // Создание структуры для информации о таймере
//{
//  __int64       frequency;                 // Частота таймера
//  float         resolution;                // Точность таймера
//  unsigned long mm_timer_start;            // Стартовое значение мультимедийного таймера
//  unsigned long mm_timer_elapsed;          // Прошедшее время мультимедийного таймера
//  bool          performance_timer;         // Использовать высокоточный таймер?
//  __int64       performance_timer_start;   // Стартовое значение высокоточного таймера
//  __int64       performance_timer_elapsed; // Прошедшее время высокоточного таймера
//} timer;                  // Структура по имени таймер
//
//int    steps[6]={ 1, 2, 4, 5, 10, 20 }; // Значения шагов для работы
//                                        // на медленных видеокартах
//
//void TimerInit(void) // Инициализация нашего таймера (Начали)
//{
//  memset(&timer, 0, sizeof(timer)); // Очистка нашей структуры
// 
//  // Проверим доступность высокоточного таймера
//  // Если доступен, то частота таймера будет задана
//  if (!QueryPerformanceFrequency((LARGE_INTEGER *) &timer.frequency))
//  {
//    // Нет высокоточного таймера
//    timer.performance_timer  = FALSE;       // Установим флаг высокоточного таймера в ЛОЖЬ
//    timer.mm_timer_start  = timeGetTime();  // Текущее время из timeGetTime()
//    timer.resolution  = 1.0f/1000.0f;       // Точность равна 0.001f
//    timer.frequency    = 1000;              // Частота равна 1000
//    timer.mm_timer_elapsed  = timer.mm_timer_start; // Прошедшее время равно текущему
//  }
//else
//  {
//    // Высокоточный таймер доступен, используем его вместо мультимедийного таймера
//    // Взять текущее время и сохранить его в performance_timer_start
//    QueryPerformanceCounter((LARGE_INTEGER *) &timer.performance_timer_start);
//    timer.performance_timer    = TRUE;        // Установить флаг наличия таймера в TRUE
//    // Вычислить точность таймера, используя частоту
//    timer.resolution    = (float) (((double)1.0f)/((double)timer.frequency));
//    // Присвоить прошедшему времени текущее время
//    timer.performance_timer_elapsed  = timer.performance_timer_start;
//  }
//}
/*-------------------------------------------------------*/

void load_texture(GLuint &x,char *s)
{
	AUX_RGBImageRec *texture1;
	texture1 = auxDIBImageLoad(s);
	// Создание текстуры
	glGenTextures(1, &x);
	glBindTexture(GL_TEXTURE_2D, x);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

}

void LoadGLTextures()
{
	// Загрузка картинки
	AUX_RGBImageRec *texture1;

	/*blinky.loadTexture("Data/10.bmp");
	blinky.setLocation(2,3);
	blinky.setPrev_location(blinky.getLocation());

	aa.loadTexture("Data/1.bmp");
	aa.setLocation(10,6);

	bb.loadTexture("Data/2.bmp");
	bb.setLocation(2,14);

	cc.loadTexture("Data/3.bmp");
	cc.setLocation(20,12);

	load_texture(st,"Data/gr.bmp");*/

	Game.setTexture();
	Game.loadFon();

	load_texture(texture[0],"Data/0.bmp");
	
	texture1 = auxDIBImageLoad("Data/1.bmp");
	// Создание текстуры
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
	
	texture1 = auxDIBImageLoad("Data/point.bmp");
	// Создание текстуры
	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

	texture1 = auxDIBImageLoad("Data/2.bmp");
	// Создание текстуры
	glGenTextures(1, &texture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
	
	texture1 = auxDIBImageLoad("Data/3.bmp");
	// Создание текстуры
	glGenTextures(1, &texture[4]);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
	
	texture1 = auxDIBImageLoad("Data/wallF.bmp");
	// Создание текстуры
	glGenTextures(1, &texture[5]);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
	
	
	texture1 = auxDIBImageLoad("Data/wall.bmp");
	// Создание текстуры
	glGenTextures(1, &texture[6]);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
}

void ReSizeGLScene(GLsizei width, GLsizei height)		
{
	if (height==0)										
	{
		height=1;										
	}

	glViewport(0,0,width,height);						

	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();									
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);				
	glLoadIdentity();
}

void InitGL(GLsizei Width, GLsizei Height)										
{
	LoadGLTextures();			// Загрузка текстур
	glEnable(GL_TEXTURE_2D);	// Разрешение наложение текстуры

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
							// Очистка экрана в черный цвет
	glClearDepth(1.0);		// Разрешить очистку буфера глубины
	glDepthFunc(GL_LESS);	// Тип теста глубины
	glEnable(GL_DEPTH_TEST);// разрешить тест глубины
	glShadeModel(GL_SMOOTH);// разрешить плавное цветовое сглаживание
	glMatrixMode(GL_PROJECTION);// Выбор матрицы проекции
	glLoadIdentity();		// Сброс матрицы проекции
	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
							// Вычислить соотношение геометрических размеров для окна
	glMatrixMode(GL_MODELVIEW);// Выбор матрицы просмотра модели				
	//BuildFont();  
}

void loadtexture(GLuint x, int m )
{
	glLoadIdentity();									
	
	glTranslatef(-9.0f,14.0f,-34.0f);  //glTranslatef(-9.0f,11.0f,-27.0f);
	glBindTexture(GL_TEXTURE_2D, x);
	
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_QUADS);  // -----28

	for(int i =0;i<28;i++) //  --------28
		for(int j = 0 ; j< 19;j++)
		{
			if(Game.map[i][j]==m)
			{
				glTexCoord2f(0.0f, 0.0f); glVertex3f (0.0f+j,  -0.0f-i-1, 0.0f);  // нижний левый
				glTexCoord2f(1.0f, 0.0f); glVertex3f (0.0f+j+1, -0.0f-i-1, 0.0f); // нихний правый 
				glTexCoord2f(1.0f, 1.0f); glVertex3f (0.0f+j+1,  -0.0f-i, 0.0f);// верхний правый 
				glTexCoord2f(0.0f, 1.0f); glVertex3f (0.0f+j,  -0.0f-i, 0.0f);	//верхний левый */
			}
		} 
	glEnd();


}


void DrawGLScene(void)									
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	loadtexture(texture[6],1);
	loadtexture(texture[5],11); //ПОРТАЛ

	loadtexture(texture[0],7);
	loadtexture(texture[1],8);
	loadtexture(texture[3],9);
	loadtexture(texture[4],10);
	
	Sleep(100);
	
	Game.draw();

	loadtexture(texture[2],2);

}

void KillGLWindow(void)								
{
	

	if (hRC)											
	{
		if (!wglMakeCurrent(NULL,NULL))					
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC))						
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			
	WNDCLASS	wc;						
	DWORD		dwExStyle;				
	DWORD		dwStyle;				
	RECT		WindowRect;				
	WindowRect.left=(long)0;			
	WindowRect.right=(long)width;		
	WindowRect.top=(long)0;				
	WindowRect.bottom=(long)height;		

	fullscreen=fullscreenflag;		

	hInstance			= GetModuleHandle(NULL);				
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	
	wc.lpfnWndProc		= (WNDPROC) WndProc;					
	wc.cbClsExtra		= 0;									
	wc.cbWndExtra		= 0;									
	wc.hInstance		= hInstance;							
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			
	wc.hbrBackground	= NULL;									
	wc.lpszMenuName		= NULL;									
	wc.lpszClassName	= "OpenGL";								

	if (!RegisterClass(&wc))									
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											
	}
	
	if (fullscreen)												
	{
		DEVMODE dmScreenSettings;								
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		
		dmScreenSettings.dmPelsWidth	= width;				
		dmScreenSettings.dmPelsHeight	= height;				
		dmScreenSettings.dmBitsPerPel	= bits;					
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		
			}
			else
			{
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									
			}
		}
	}

	if (fullscreen)												
	{
		dwExStyle=WS_EX_APPWINDOW;								
		dwStyle=WS_POPUP;										
		ShowCursor(FALSE);										
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			
		dwStyle=WS_OVERLAPPEDWINDOW;							
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);	

	if (!(hWnd=CreateWindowEx(	dwExStyle,							
								"OpenGL",							
								title,								
								dwStyle |							
								WS_CLIPSIBLINGS |					
								WS_CLIPCHILDREN,					
								0, 0,								
								WindowRect.right-WindowRect.left,	
								WindowRect.bottom-WindowRect.top,	
								NULL,								
								NULL,								
								hInstance,							
								NULL)))								
	{
		KillGLWindow();								
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}
RECT	Screen;	
	static	PIXELFORMATDESCRIPTOR pfd=				
	{
		sizeof(PIXELFORMATDESCRIPTOR),				
		1,											
		PFD_DRAW_TO_WINDOW |						
		PFD_SUPPORT_OPENGL |						
		PFD_DOUBLEBUFFER,							
		PFD_TYPE_RGBA,								
		16,										
		0, 0, 0, 0, 0, 0,						
		0,										
		0,										
		0,										
		0, 0, 0, 0,								
		16,										
		0,										
		0,										
		PFD_MAIN_PLANE,							
		0,										
		0, 0, 0									
	};
	
	//hButton = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"), TEXT("Create Server"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 0, 0, 200, 30, hWnd, (HMENU)100, GetModuleHandle(NULL), NULL);
	//hButton2 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("BUTTON"), TEXT("Connect"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 0, 30, 200, 30, hWnd, (HMENU)101, GetModuleHandle(NULL), NULL);
	//hEdit = CreateWindow(TEXT("EDIT"), TEXT ("Enter IP"),WS_CHILD|WS_VISIBLE|WS_TABSTOP|ES_MULTILINE|WS_BORDER ,0,60,200,30, hWnd,(HMENU)103, GetModuleHandle(NULL)/*hThisInstance*/, NULL);
	
	if (!(hDC=GetDC(hWnd)))							
	{
		KillGLWindow();								
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}
	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	
	{
		KillGLWindow();								
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}
	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		
	{
		KillGLWindow();								
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}
	if (!(hRC=wglCreateContext(hDC)))				
	{
		KillGLWindow();								
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}
	if(!wglMakeCurrent(hDC,hRC))					
	{
		KillGLWindow();								
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	ShowWindow(hWnd,SW_SHOW);						
	SetForegroundWindow(hWnd);						
	SetFocus(hWnd);									
	ReSizeGLScene(width, height);

	GetClientRect(hWnd, &Screen);
	InitGL(Screen.right, Screen.bottom);

	return TRUE;									
}



char IP_add[16];
LRESULT CALLBACK WndProc(	HWND	hWnd,			
							UINT	uMsg,			
							WPARAM	wParam,			
							LPARAM	lParam)			
{
	switch (uMsg)									
	{
		case WM_COMMAND:

			switch (LOWORD(wParam))
			{
				
					MessageBox(NULL,"Podclutheno","Game message",MB_OK|MB_ICONSTOP);
				
			}
			return 0;
		case WM_ACTIVATE:							
		{
			if (!HIWORD(wParam))					
			{
				Game.active=TRUE;						
			}
			else
			{
				Game.active=FALSE;						
			}

			return 0;								
		}
		case WM_SYSCOMMAND:							
		{
			switch (wParam)							
			{
				case SC_SCREENSAVE:					
				case SC_MONITORPOWER:				
				return 0;							
			}
			break;									
		}

		case WM_CLOSE:								
		{
			PostQuitMessage(0);
								
			return 0;								
		}

		case WM_KEYDOWN:							
		{
			Game.keys[wParam] = TRUE;					
			return 0;								
		}

		case WM_KEYUP:								
		{
			Game.keys[wParam] = FALSE;					
			return 0;								
		}

		case WM_SIZE:								
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  
			return 0;								
		}
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}



int WINAPI WinMain(	HINSTANCE	hInstance,			
					HINSTANCE	hPrevInstance,		
					LPSTR		lpCmdLine,			
					int			nCmdShow)			
{
	MSG		msg;									
	BOOL	done=FALSE;								



	DialogBox(hInstance, 
        MAKEINTRESOURCE(101), //(ДЛ1)
                         NULL, (DLGPROC) AboutDlgProc); 

	fullscreen=FALSE;
	char nam[] = "Anti-PacMan";
	CreateGLWindow(nam,840,680,	16,	fullscreen);
	
	while(!done)									
	{
		
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	
		{
			if (msg.message==WM_QUIT)				
			{
				done=TRUE;							
			}
			else									
			{
				TranslateMessage(&msg);				
				DispatchMessage(&msg);				
			}
		}
		else										
		{
			

				if(Game.active)
				{
					DrawGLScene();
				}
			

				if (Game.keys[VK_ESCAPE])	
				{
					done=TRUE;							
				}
				else									
				{
					SwapBuffers(hDC);					
				}

				if (Game.keys[VK_F1])						
				{
					KillGLWindow();	

					DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),  NULL, (DLGPROC) AboutDlgProc); 
					Game.keys[VK_F1]=FALSE;					
					CreateGLWindow(nam,640,480,16,fullscreen);
				}
			
			if (isKeyboardORkinect)
			{
				if (Game.keys[VK_SPACE])
				{
					Game.setGhost();
					Game.keys[VK_SPACE] = FALSE;
				}
				if (Game.keys[VK_NUMPAD0])
					Game.setGhost(0);
				if (Game.keys[VK_NUMPAD1])
					Game.setGhost(1);
				if (Game.keys[VK_NUMPAD2])
					Game.setGhost(2);
				if (Game.keys[VK_NUMPAD3])
					Game.setGhost(3);
				
				Game.setLocationGhost();		

			}
		}
	}
	// Shutdown
	KillGLWindow();									
	return (msg.wParam);							
}
