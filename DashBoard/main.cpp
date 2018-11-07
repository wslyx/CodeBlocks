#include <windows.h>
#include <math.h>
#include <iostream>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

extern void Render(HWND hWnd,double aef);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("DashBoard");

	HWND		hwnd;

	MSG			msg;

	WNDCLASS	wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	wndclass.lpfnWndProc = WndProc;

	wndclass.cbClsExtra = 0;

	wndclass.cbWndExtra = 0;

	wndclass.hInstance = hInstance;

	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);

	wndclass.hbrBackground = NULL;

	wndclass.lpszMenuName = NULL;

	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{

		MessageBox(NULL, TEXT("Program requires Windows NT!"),szAppName, MB_ICONERROR);

		return 0;

	}

	hwnd = CreateWindow(szAppName, TEXT("smart dashboard"),
		WS_EX_LAYERED | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT,CW_USEDEFAULT,
		1000, 600,
		NULL, NULL, hInstance, NULL);


	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);


    SetTimer(hwnd,WM_PAINT,1,NULL);


	while (GetMessage(&msg, NULL, 0, 0))
	{

		TranslateMessage(&msg);

		DispatchMessage(&msg);

	}

	return msg.wParam;
}


double PAINT_CYCLE=1.16;
int DCount=0,UCount=0;

extern Slide_Bar(HWND,int,int,int,int);
extern Clock_Board(HWND,double);

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int  cxClient, cyClient;

	static int xPos,yPos;

	HDC hdc;

	int length;

	int value;

	TCHAR szBuffer[100];

	PAINTSTRUCT ps;

	switch (message)
	{

	case   WM_SIZE:

		cxClient = LOWORD(lParam);

		cyClient = HIWORD(lParam);

	case   WM_PAINT:

	    //Clock Board

	    if(PAINT_CYCLE<-(0.16)) PAINT_CYCLE=1.16;

	    PAINT_CYCLE=PAINT_CYCLE-0.001;

		Clock_Board(hwnd,PAINT_CYCLE);

		//end

		//slide bar

		value = Slide_Bar(hwnd,xPos,yPos,DCount,UCount);

		//end

		hdc=GetDC(hwnd);

        length=wsprintf(szBuffer,"RETURN VALUE:%d",value);

        SelectObject(hdc,GetStockObject(WHITE_PEN));

        Rectangle(hdc,700,490,800,710);

        SelectObject(hdc,GetStockObject(BLACK_PEN));

        TextOut(hdc,700,490,szBuffer,length);

        ReleaseDC(hwnd,hdc);

        //hdc=GetDC(NULL);

        //length=wsprintf(szBuffer,"hello Desktop:%d",yPos);
        //TextOut(hdc,300,300,szBuffer,length);

        //ReleaseDC(NULL,hdc);

		return 0;

    case WM_LBUTTONDOWN:

        hdc=GetDC(hwnd);

        DCount++;

        length=wsprintf(szBuffer,"LBUTTON_DOWN:%d",DCount);

        TextOut(hdc,700,510,szBuffer,length);

        ReleaseDC(hwnd,hdc);

        return 0;

    case WM_LBUTTONUP:

        hdc=GetDC(hwnd);

        UCount++;

        length=wsprintf(szBuffer,"LBUTTON_UP:%d",UCount);

        TextOut(hdc,700,530,szBuffer,length);

        ReleaseDC(hwnd,hdc);

        return 0;

    case WM_MOUSEMOVE:

        xPos=LOWORD(lParam);

        yPos=HIWORD(lParam);

        hdc=GetDC(hwnd);

        length=wsprintf(szBuffer,"MOUSE_MOVE:  xPos:%d  yPos:%d",xPos,yPos);

        TextOut(hdc,700,550,szBuffer,length);

        ReleaseDC(hwnd,hdc);

        return 0;

	case   WM_DESTROY:

		PostQuitMessage(0);

		return 0;

	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
