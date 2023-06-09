// xu ly menu
#include "menu.h"
#include "play.h"
#include<stdio.h>
#include<conio.h>
void menuHeader(int color)
{
	ifstream Header;
	string s;
	txtColor(color);
	Header.open("menu.txt", ios::in);
	for (int i = 0; i<8; i++)
	{
		getline(Header, s);
		GotoXY(12, 5 + i);

		for (int j = 0; j < s.length(); j++)
		{
			cout << s[j];
		}
	}
	Header.close();
}

void optionText()
{
	int yPos = 70;
	int xPos = 17;
	GotoXY(yPos, xPos);
	cout << " NEW GAME";
	GotoXY(yPos, xPos+=2);
	cout << "LOAD  GAME";
	GotoXY(yPos, xPos += 2);
	cout << "   HELP";
	GotoXY(yPos, xPos += 2);
	cout << "  ABOUT ";
	GotoXY(yPos, xPos += 2);
	cout << "   EXIT";
}


void mainMenu()
{
	system("cls");
	setBkgColor();
	int k = 113;
	int c = 0;
	menuHeader(k);
	for (int i = 1; i <=100 ; i++) {
		Sleep(25);
		c++;
		if (c == 5) {
			c = 0;
			k++;
			menuHeader(k);
		}
		if (k == 116) k = 113;
		loadingBar(i);
		txtColor(112);
		GotoXY(80, 27);
		cout << i << " %";
	}
	Sleep(1000);
	GotoXY(80, 27);
	cout << "     ";
	system("color 70");
	optionText();
	luaChon(70, 17);
}

void menuNoLoading() {
	system("cls");
	system("color 70");
	menuHeader(112);
	optionText();
	luaChon(70, 17);
}

void printArrow(int xPos, int yPos) {
	GotoXY(xPos - 9, yPos);
	cout << "---->";
	GotoXY(xPos + 15, yPos);
	cout << "<----";
}


void deleteArrow(int xPos, int yPos) {
	GotoXY(xPos - 9, yPos);
	cout << "     ";
	GotoXY(xPos + 15, yPos);
	cout << "     ";
}


void luaChon(int xPos,int yPos)
{
	int c = 1;
	char move =1;
	printArrow(xPos, yPos);
	while (1 == 1)
	{
		if (_kbhit()) {
			move = _getch();
			move = toupper(move);
			if ((move == 80 || move == 'S') && (c >= 1) && (c < 5))
			{
				deleteArrow(xPos, yPos);
				yPos += 2;
				printArrow(xPos, yPos);
				c++;
			}
			if ((move == 72 || move == 'W') && (c > 1) && (c <= 5))
			{
				deleteArrow(xPos, yPos);
				yPos -= 2;
				printArrow(xPos, yPos);
				c--;
			}
			if (move == 13)
				xuliChon(c);
		}
	}
}

void xuliChon(int c)
{
	switch (c) {
	case 5:
		system("cls");
		exit(0);
		break;
	case 3:
		help();
		break;
	case 4:
		about();
		break;
	case 1:
		playgame("new game");
		break;
	case 2:
		loadgame();
		menuNoLoading();
		break;
	}
}

void help()
{
	drawTable({ 55,10 }, { 100,30 }, 207);
	GotoXY(75, 12);
	cout << "HELP";
	GotoXY(60, 15);
	cout << "Press W to move up";
	GotoXY(60, 16);
	cout << "Press A to move left";
	GotoXY(60, 17);
	cout << "Press S to move down";
	GotoXY(60, 18);
	cout << "Press D to move right";
	GotoXY(60, 19);
	cout << "Press P to pause";
	GotoXY(60, 20);
	cout << "Press L to load game";
	GotoXY(60, 25);
	cout << "Press Enter to return to menu";
	char move = 1;
	do {
		move = _getch();
	} while (move != 13);
	menuNoLoading();

}

void about()
{

	drawTable({ 55,10 }, { 100,30 }, 207);
	GotoXY(75, 12);
	cout << "ABOUT";
	GotoXY(60, 15);
	cout << "Day la do an game cua nhom 9";
	GotoXY(60, 16);
	cout << "Thanh vien: ";
	GotoXY(60, 17);
	cout << "1. Le Xuan Hoang    20120089";
	GotoXY(60, 18);
	cout << "2. Trinh Huu Hiep   20120079";
	GotoXY(60, 19);
	cout << "3. Le Nguyen Khang  20120113";
	GotoXY(60, 20);
	cout << "4. Nguyen Tuan Minh 20120132";
	GotoXY(60, 21);
	cout << "5. Tran Kim Bao     20120041";
	GotoXY(60, 25);
	cout << "Press Enter to return to menu";
	char move = 1;
	do {
		move = _getch();
	} while (move != 13);
	menuNoLoading();
}


void loadgame()
{
	drawTable({ 55,10 }, { 100,30 }, 207);
	string s[5] = {};
	GotoXY(73, 12);
	cout << "LOAD GAME";
	ifstream savedFile;
	savedFile.open("savedFile.txt", ios::in);
	GotoXY(60, 15);
	cout << "Nhung game ban co the tiep tuc: ";
	for (int i = 0; i < 5; i++) {
		getline(savedFile, s[i]);
		GotoXY(60, 18 + i);
		cout << "Game " << i << "\t" << s[i];
	}
	GotoXY(60, 25);
	cout << "Press X to go back";
	char move = 1;
	int c = 0;
	do {
		GotoXY(90, 18+c);
		cout << "<----";
		move = toupper(_getch());
		if ((move == 80 || move == 'S') && (c < 4)) {
			GotoXY(90, 18 + c);
			cout << "     ";
			c++;
		}
		else if ((move == 72 || move == 'W') && (c > 0)) {
			GotoXY(90, 18 + c);
			cout << "     ";
			c--;
		}
		else if (move == 13) playgame(s[c]);

	} while (move != 'X');
	savedFile.close();
}

void loadingBar(int percent)
{
	txtColor(47);
	GotoXY(30, 25);
	for (int i = 0; i < percent; i++)
		cout << " ";
}
