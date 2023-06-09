// Ve cac doi tuong: xe, table,..
#include "draw.h"
#include<conio.h>

const char simpleCar[CAR_HEIGHT][CAR_WIDTH] = { " _______",
												"| O | O \\____",
												"|_____________\\",
												"  (0)     (0)  "
};

const char leftCar[CAR_HEIGHT][CAR_WIDTH] = {  "    ________   ",
											   " __| O | O  |_ ",
											   "|_____________|",
											   "  (0)     (0)  "

};

const char carErase[CAR_HEIGHT][CAR_WIDTH] = { "               ",
											   "               ",
											   "               ",
											   "               "
};

const char NGUOI[3][4] = { " o ",
						   "/|\\",
						   "/ \\"
};

void drawCar(const POINT &pos, int type)
{
	int start =0;
	for (int i = 0; i < CAR_HEIGHT; i++) {
		if (pos.x < tableGame.TLpos.x+1) {
			start = tableGame.TLpos.x - pos.x+1;
			GotoXY(tableGame.TLpos.x+1, pos.y + i);
		}
		else GotoXY(pos.x, pos.y + i);
		for (int j = start; j < CAR_WIDTH; j++)
			if (j + pos.x < tableGame.BRpos.x && j + pos.x >tableGame.TLpos.x)
				if (type == 1) cout << simpleCar[i][j];
				else cout << leftCar[i][j];
	}
}
void eraseCar(const POINT &pos)
{
	int start = 0;
	for (int i = 0; i < CAR_HEIGHT; i++) {
		if (pos.x < tableGame.TLpos.x+1) {
			start = tableGame.TLpos.x - pos.x+1;
			GotoXY(tableGame.TLpos.x+1, pos.y + i);
		}
		else GotoXY(pos.x, pos.y + i);
		for (int j = 0; j < CAR_WIDTH; j++)
			if (j + pos.x < tableGame.BRpos.x  && j + pos.x >tableGame.TLpos.x)  cout << carErase[i][j];
	}
}

void drawPerson(const POINT& pos) {
	for (int i = 0; i < 3; i++) {
		GotoXY(pos.x, pos.y + i);
		for (int j = 0; j < 3; j++)
			cout << NGUOI[i][j];
	}
}

void erasePerson(const POINT& pos)
{
	for (int i = 0; i < 3; i++) {
		GotoXY(pos.x, pos.y + i);
		for (int j = 0; j < 3; j++)
			cout << " ";
	}
}

void drawTable(const POINT& TLpos, const POINT &BRpos,  const short &color) {
	int width = BRpos.x - TLpos.x + 1;
	int height = BRpos.y - TLpos.y + 1;
	GotoXY(TLpos.x, TLpos.y);
	txtColor(color);
	cout << " ";
	for (int i = 0; i < width-2; i++) {
		cout << "-";
	}
	cout << " ";
	for (int i = 1; i < height-1; i++) {
		GotoXY(TLpos.x, TLpos.y + i);
		cout << "|";
		for (int i = 1; i < width - 1; i++)
			cout << " ";
		cout << "|";
	}
	GotoXY(TLpos.x, BRpos.y);
	cout << " ";
	for (int i = 0; i < width-2; i++) {
		cout << "-";
	}
	cout << " ";
}


