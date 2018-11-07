#include<Windows.h>
#include<math.h>

int left=0,top=0,right=left+300,buttom=top+300;

#define PI (3.1415926)

int length;
TCHAR szBuffer[100];

void Clock_Board(HWND hwnd, double aef) {

    HDC hdc=GetDC(hwnd);

	Rectangle(hdc, left, top, right, 150 * sin(PI / 6) + 150);

	Pie(hdc, left, top, right, buttom, 150 * cos(PI / 6) + 150, -150 * sin(-(PI / 6)) + 150, 150 * cos(PI * 7 / 6) + 150, -150 * sin(PI * 7 / 6) + 150);

	MoveToEx(hdc, left+150, top+150, NULL);

	LineTo(hdc, 150 * cos(PI*aef) + left + 150, -150 * sin(PI*aef) + left + 150);

	length = wsprintf(szBuffer, (char *)"dashboard_1");

	TextOut(hdc, left+110, top+200, szBuffer, length);

	ReleaseDC(hwnd,hdc);

	Sleep(100);
}
