#ifndef __PLAY_H__
#define __PLAY_H__
#include"draw.h"
void drawBkg();
void playgame(string name);
void move();
void dieukhien();
void initCar();
void newCarPos(CAR &car);
bool isPossiblePos(const CAR& car);
void pause();
void setData();
void vedich();
void printRule();
bool ktVaChamXe();
void vachamxe();
void saveGame();
bool ktVachamNguoi();
void taigame();
void setCarStop(CAR &car);
void setCarRun(CAR& car);
void exitgame();
void updateCarState();
int Lane(POINT pos, int lanewidth);
void PrintTrafficLight();
#endif // !__PLAY_H__
