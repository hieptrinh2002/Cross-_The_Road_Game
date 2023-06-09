// khoi tao console va cac ham can thiet trong suot chuong trinh
#include "common.h"

void FixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}


void createWindow()
{
	FixConsoleWindow();
	setWindowSize(157,41,157,41);
}

void setWindowSize(SHORT width, SHORT height, SHORT bufferWidth, SHORT bufferHeight)
{
	CONSOLE_SCREEN_BUFFER_INFOEX consolesize;
	consolesize.cbSize = sizeof(consolesize);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(hConsole, &consolesize);
	COORD c;
	c.X =bufferWidth;
	c.Y = bufferHeight;
	consolesize.dwSize = c;
	consolesize.srWindow.Left = 0;
	consolesize.srWindow.Right = width;
	consolesize.srWindow.Top = 0;
	consolesize.srWindow.Bottom = height;
	SetConsoleScreenBufferInfoEx(hConsole, &consolesize);
}


void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setBkgColor()
{
	system("color 70");
}

void txtColor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}
