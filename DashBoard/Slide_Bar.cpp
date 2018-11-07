#include<windows.h>

int Slide_Bar(HWND hwnd,int xPos,int yPos,int DCount,int UCount)
{

    HDC hdc;

    int left=600,top=20,right=left+80,buttom=top+300;

    hdc = GetDC(hwnd);

    static double YPOS=buttom-20;


    SelectObject(hdc,GetStockObject(WHITE_PEN));

    Rectangle(hdc,left,top,right,buttom+30);

    SelectObject(hdc,GetStockObject(BLACK_PEN));

    Rectangle(hdc,left+20,top,right-20,buttom);

    if (xPos<right)
    if (xPos>left)
    if (yPos>top)
    if (yPos<buttom)
    if (DCount>UCount)
    {
        YPOS=yPos;
    }

    Rectangle(hdc,left,YPOS,right,YPOS+20);

    ReleaseDC(hwnd,hdc);

    return (buttom-YPOS);
}
