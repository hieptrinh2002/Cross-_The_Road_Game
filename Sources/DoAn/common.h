#ifndef __COMMON_H__
#define __COMMON_H__
#include<iostream>
#include<Windows.h>
#define MAX_CAR 24
#define CAR_HEIGHT 4
#define CAR_WIDTH 16

struct PONIT {
	int x; int y;
};
struct table {
	POINT TLpos; // vi tri trai tren (top left)
	POINT BRpos; // vi tri phai duoi (bottom right)
};
struct CAR {
	POINT pos = { 1,1 };
	int type = 1;
	int state = 1; // state =0 la dung yen, state =1 la di chuyen
};
const table tableGame = { {1,0},{105,40} };
using namespace std;
void FixConsoleWindow();
void createWindow();
void setWindowSize(SHORT width, SHORT height, SHORT bufferWidth, SHORT bufferHeight);
void GotoXY(int x, int y);
void setBkgColor();
void txtColor(int x);

#endif 
