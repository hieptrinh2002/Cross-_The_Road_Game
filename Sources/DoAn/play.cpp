// xu ly tro choi
#include "play.h"
#include "menu.h"
#include <conio.h>
#include <time.h>
#include<fstream>
#include<string>
#include<vector>

const table infotbl = { {112,0},{154,18} };
const table Rule ={{112,23},{154,40}};
bool state = true;
int trafficLight[6] = {};
int lane = 5;
int speed = 1;
int score = 0;
int c;
string name = "new game";
vector<POINT> nguoi = {};
CAR* X; // mang luu cac xe
POINT Y = { (tableGame.TLpos.x + tableGame.BRpos.x) / 2,tableGame.BRpos.y - 3 };
void txtScore() {
	ifstream txtScore;
	txtScore.open("score.txt", ios::in);
	string s;
	for (int i = 0; i < 4; i++)
	{
		getline(txtScore, s);
		GotoXY(infotbl.TLpos.x + 9, infotbl.TLpos.y+i+4);

		for (int j = 0; j < s.length(); j++)
		{
			cout << s[j];
		}
	}
	txtScore.close();
}

void printScore() {
	GotoXY(infotbl.TLpos.x + 21, infotbl.TLpos.y+10);
	cout << score;
	GotoXY(infotbl.TLpos.x + 12, infotbl.TLpos.y + 13);
	cout << "Level: " << speed;
	GotoXY(infotbl.TLpos.x + 12, infotbl.TLpos.y + 15);
	cout << "Name : " << name<<"         ";
}

void drawBkg()
{
	system("cls");
	drawTable({tableGame.TLpos.x,tableGame.TLpos.y }, { tableGame.BRpos.x,tableGame.BRpos.y }, 10); // ve khung man hinh game
	for (int i = lane; i < 40; i += lane)
		drawTable({ tableGame.TLpos.x+1, 0 + i }, { tableGame.BRpos.x-1,0 + i }, 10);               // ve cac lan duong
	drawTable({ infotbl.TLpos.x, infotbl.TLpos.y }, { infotbl.BRpos.x, infotbl.BRpos.y },10);
	txtScore();
	printScore();
	printRule();
	for (int i = 0; i < nguoi.size(); i++)
		drawPerson(nguoi[i]);
	drawPerson(Y);
	for (int i = 0; i < MAX_CAR; i++)
		drawCar(X[i].pos, X[i].type);
	system("color 70");
	PrintTrafficLight();
	txtColor(112);
	
}

void runCar(CAR &car) {
	if (car.type == 1 && car.pos.x > tableGame.BRpos.x-1) newCarPos(car);
	else if (car.type == -1 && car.pos.x + CAR_WIDTH < 2)newCarPos(car);
	eraseCar(car.pos);
	car.pos.x += speed*car.type*car.state;
	drawCar(car.pos, car.type);
}

void playgame(string Name)
{
	c = 0;
	name = Name;
	initCar();
	setData();
	drawBkg();
	for (int i = 3; i > 0; i--) {
		GotoXY(Rule.TLpos.x + 10, Rule.TLpos.y + 14);
		cout << "Game will start after " << i << " s";
		Sleep(1000);
	}
	GotoXY(Rule.TLpos.x + 10, Rule.TLpos.y + 14);
	cout << "                             ";
	dieukhien();
}

void move()
{
	if (_kbhit()) {
		erasePerson(Y);
		int key = _getch();
		key = toupper(key);
		if (key == 'A' && Y.x > tableGame.TLpos.x + 4) Y.x -= 3;
		else if (key == 'S' && Y.y < tableGame.BRpos.y - 6) Y.y += lane;
		else if (key == 'W' && Y.y > tableGame.TLpos.y + 6) Y.y -= lane;
		else if (key == 'D' && Y.x < tableGame.BRpos.x - 4) Y.x += 3;
		else if (key == 'P') pause();
		else if (key == 'L') saveGame();
		else if (key == 'T') taigame();
		else if (key == 27) exitgame();
		drawPerson(Y);
	}
}

void dieukhien()
{
	while (state) {
		if (c % 5000 == 0) {
			srand((int)time(0));
			for (int i = 0; i < 6; i++) {
				trafficLight[i] = rand() % 2;
				updateCarState();
			}
			PrintTrafficLight();
		}
		txtColor(112);
		for (int i = 0; i < MAX_CAR; i++)
			 runCar(X[i]);
		move();
		if (ktVaChamXe() || ktVachamNguoi()) vachamxe();
		if (Y.y == 2) vedich();
		c += 100;
		Sleep(100);
	}
}

void initCar()
{
	X = new CAR[MAX_CAR];
	srand((int)time(0));
	for (int i=0; i< MAX_CAR ; i++){
		newCarPos(X[i]);
	}
}


void newCarPos(CAR &car)
{
	int r = 1 + rand() % 6;
	if (r % 2 == 0) car.type = -1;
	else car.type = 1;
	car.pos.y = 1 + lane * r;
	r = rand() % 8;
	car.state = trafficLight[Lane(car.pos, lane) - 1];
	if (car.type == 1) {
		car.pos.x = tableGame.TLpos.x - 18 * r;
		if (isPossiblePos(car) == false)  newCarPos(car);
	}
	else {
		if (car.type == -1) car.pos.x = tableGame.BRpos.x + 18 * r;
		if (isPossiblePos(car) == false)  newCarPos(car);
	}
}



bool isPossiblePos(const CAR& car)
{
	for (int i = 0; i < MAX_CAR; i++) {
		if (car.pos.y == X[i].pos.y)
			if ((car.pos.x > X[i].pos.x + CAR_WIDTH || car.pos.x + CAR_WIDTH < X[i].pos.x || (car.type==X[i].type && car.pos.x==X[i].pos.x))) continue;
			else return false;
	}
	return true;
}

void pauseTxt() {
	ifstream txtPause;
	txtPause.open("pause.txt", ios::in);
	string s;
	for (int i = 0; i < 6; i++)
	{
		getline(txtPause, s);
		GotoXY(Rule.TLpos.x + 12, Rule.TLpos.y + i + 10);

		for (int j = 0; j < s.length(); j++)
		{
			cout << s[j];
		}
	}
	txtPause.close();
}

void clearPauseTxt() {
	for (int i = 0; i < 8; i++) {
		GotoXY(Rule.TLpos.x + 10, Rule.TLpos.y + 9 + i);
		for (int j = 0; j < 30; j++) cout << " ";
	}
}

void pause()
{
	pauseTxt();
	drawPerson(Y);
	GotoXY(Rule.TLpos.x + 10, Rule.TLpos.y + 16);
	cout << "Press P again to continue";
	char c = ' ';
	do {
		c = toupper(_getch());
	} while (c != 'P');
	clearPauseTxt();
}

void setData()
{
	ifstream data;
	string Name = name + ".txt";
	data.open(Name, ios::in);
	data >> score;
	data >> speed;
	int n;
	while (!nguoi.empty())
		nguoi.pop_back();
	data >> n;
	for (int i = 0; i < n; i++) {
		int x, y;
		data >> x >> y;
		nguoi.push_back({ x,y });
	}
	for (int i = 0; i < MAX_CAR; i++) {
		data >> X[i].type >> X[i].pos.x >> X[i].pos.y;
	}
	data >> Y.x >> Y.y;
	for (int i = 0; i < 6; i++)
		data >> trafficLight[i];
	data.close();

}

void drawambulance(POINT pos) {
	ifstream ambulance;
	ambulance.open("ambulance.txt", ios::in);
	string s;
	for (int i = 0; i < 9; i++)
	{
		getline(ambulance, s);
		GotoXY(pos.x, pos.y + i);
		for (int j = 0; j < s.length(); j++)
		{
			cout << s[j];
		}
	}
	ambulance.close();
}

void clearAmbulance(POINT pos) {
	for (int i = 0; i < 9; i++) {
		GotoXY(pos.x,pos.y+i);
		cout << " ";
	}
}

void youLoseTxt(POINT pos, int color) {
	ifstream lose;
	txtColor(color);
	lose.open("youlose.txt", ios::in);
	string s;
	for (int i = 0; i < 9; i++)
	{
		getline(lose, s);
		GotoXY(pos.x, pos.y + i);
		for (int j = 0; j < s.length(); j++)
		{
			cout << s[j];
		}
	}
	lose.close();
}

void vachamxe() {
	Sleep(1000);
	delete[] X;
	system("cls");
	drawPerson({65,15 });
	for (int i = 20; i < 90; i++) {
		clearAmbulance({ i-1,10 });
		drawambulance({ i,10 });
		Sleep(50);
	}
	char t = ' ';
	POINT pos = {40,10};
	system("cls");
	do {
		if(_kbhit()) 
			t = toupper(_getch());
		Sleep(50);
		youLoseTxt(pos, 113);
		Sleep(50);
		youLoseTxt(pos, 114);
		Sleep(50);
		youLoseTxt(pos, 115);
		txtColor(112);
		GotoXY(70, 25);
		cout << "Your Score: " << score;
		GotoXY(65, 26);
		cout << "Press M to return to Menu";
	} while (t != 'M');

	menuNoLoading();
}

void saveFile(int y, string s[5]) {
	GotoXY(Rule.TLpos.x + 3, Rule.TLpos.y + 12);
	cout << "Nhap ten file moi: ";
	string str;
	getline(cin, str);
	s[y] = str;
	name = str;
	printScore();
	GotoXY(Rule.TLpos.x + 3, Rule.TLpos.y + 5 + y);
	cout << "Game " << y << "\t " << s[y]<<"\t";
	ofstream savefile;
	str = str + ".txt";
	savefile.open(str, ios::out);
	savefile << score << endl << speed << endl;
	savefile << nguoi.size()<<endl;
	for (int i = 0; i < nguoi.size(); i++) {
		savefile << nguoi[i].x <<endl<< nguoi[i].y << endl;
	}
	for (int i = 0; i < MAX_CAR; i++)
		savefile << X[i].type << " " << X[i].pos.x << " " << X[i].pos.y << endl;
	savefile << Y.x << " " << Y.y<<endl;
	for (int i = 0; i < 6; i++)
		savefile << trafficLight[i] << endl;
	savefile.close();
	GotoXY(Rule.TLpos.x + 3, Rule.TLpos.y + 12);
	cout << "Save file succesfully!                ";
	ofstream savedFiles;
	savedFiles.open("savedFile.txt", ios::out);
	for (int i = 0; i < 5; i++)
		savedFiles << s[i] << endl;
	savedFiles.close();
}

void saveGame()
{
	drawTable({ 112, 23 }, { 154,40 }, 112);
	drawPerson(Y);
	GotoXY(130, 23);
	cout << "SAVE GAME";
	int u = Rule.TLpos.x;
	int v = Rule.TLpos.y;
	GotoXY(u+3, v+2);
	cout << "Chon noi de luu vao: ";
	ifstream saved;
	saved.open("savedFile.txt", ios::in);
	string s[5] = {};
	for (int i = 0; i < 5; i++)
		getline(saved, s[i]);
	for (int i = 0; i < 5; i++) {
		GotoXY(u + 3, v + 5 + i);
		cout << "Game " << i << "\t " << s[i]<<"\t";
	}
	GotoXY(u + 3, v + 12);
	cout << "Nhan Enter de chon";
	GotoXY(u + 3, v + 13);
	cout << "Nhan X de tiep tuc choi game";
	char c = ' ';
	int y = 0;
	do {
		GotoXY(u + 30, v + 5 + y);
		cout << "<----";
		c = toupper(_getch());
		if ((c == 80 || c == 'S') && (y < 4)) {
			GotoXY(u + 30, v + 5 + y);
			cout << "     ";
			y++;
		}
		else if ((c == 72 || c == 'W') && (y > 0)) {
			GotoXY(u + 30, v + 5 + y);
			cout << "     ";
			y--;
		}
		else if (c == 13) 
			saveFile(y, s);
	} while (c != 'X' && c != 13);
	printRule();
}

bool ktVaChamXe() {
	for (int i = 0; i < MAX_CAR; i++) {
		if (Y.y == X[i].pos.y + 1 &&(( Y.x < X[i].pos.x + CAR_WIDTH-1 && Y.x  > X[i].pos.x)||(Y.x+3 < X[i].pos.x + CAR_WIDTH-1 && Y.x+3 > X[i].pos.x)))return true;
	}
	return false;
}

bool ktVachamNguoi() {
	for (int i = 0; i < nguoi.size(); i++) {
		if (Y.y == nguoi[i].y && ((Y.x <= nguoi[i].x + 3 && Y.x >= nguoi[i].x) || (Y.x + 3 <= nguoi[i].x + 3 && Y.x + 3 >= nguoi[i].x)))
			return true;
	}
	return false;
}

void taigame()
{
	drawPerson(Y);
	loadgame();
	drawBkg();
}

void setCarStop(CAR &car)
{
	car.state = 0;
}

void setCarRun(CAR& car)
{
	car.state = 1;
}

void exitgame()
{
	drawPerson(Y);
	GotoXY(Rule.TLpos.x + 8, Rule.TLpos.y + 12);
	cout << "Do you want to exit game?";
	GotoXY(Rule.TLpos.x + 15, Rule.TLpos.y + 14);
	cout << "No : Press N";
	GotoXY(Rule.TLpos.x + 15, Rule.TLpos.y + 15);
	cout << "Yes: Press Y";
	char t = ' ';
	do {
		t = toupper(_getch());
	} while (t != 'N' && t != 'Y');
	if (t == 'Y') {
		delete[] X;
		system("cls");
		exit(0);
	}
	else {
		GotoXY(Rule.TLpos.x + 8, Rule.TLpos.y + 12);
		cout << "                           ";
		GotoXY(Rule.TLpos.x + 15, Rule.TLpos.y + 14);
		cout << "                  ";
		GotoXY(Rule.TLpos.x + 15, Rule.TLpos.y + 15);
		cout << "                  ";
	}
	
}

void updateCarState()
{
	for (int i = 0; i < MAX_CAR; i++) {
		X[i].state = trafficLight[Lane(X[i].pos, lane) -1];
	}
}

int Lane(POINT pos, int lanewidth)
{
	return (pos.y-tableGame.TLpos.y) / lanewidth;
}

void PrintTrafficLight()
{
	for (int i = 0; i < 6; i++) {
		GotoXY(tableGame.BRpos.x + 2, lane * (i + 1) + 2);
		if (trafficLight[i] == 0) {
			txtColor(66);
			cout << "  ";
		}
		else if (trafficLight[i] == 1) {
			txtColor(34);
			cout << "  ";
		}
	}
}


void vedich()
{
	nguoi.push_back(Y);
    Y = { (tableGame.TLpos.x + tableGame.BRpos.x) / 2,tableGame.BRpos.y - 3 };
	score += 100;
	if (speed < 3)speed++;
	else speed = 1;
	printScore();
	drawPerson(Y);
	dieukhien();

}

void printRule()
{
	drawTable({ 112, 23 }, { 154,40 }, 112);
	int t = Rule.TLpos.x;
	int u = Rule.TLpos.y;
	GotoXY(t+20, u);
	cout << "RULE";
	GotoXY(t + 10, u + 2);
	cout << "Press W to move up";
	GotoXY(t + 10, u + 3);
	cout << "Press A to move left";
	GotoXY(t + 10, u + 4);
	cout << "Press S to move down";
	GotoXY (t + 10, u + 5);
	cout << "Press D to move right";
	GotoXY(t + 10, u + 6);
	cout << "Press L to save game";
	GotoXY(t + 10, u + 7);
	cout << "Press T to load game";
	GotoXY(t + 10, u + 8);
	cout << "Press P to pause";
	GotoXY(t + 10, u + 9);
	cout << "Press ESC to exit game";
	//system("Color 70");
}
