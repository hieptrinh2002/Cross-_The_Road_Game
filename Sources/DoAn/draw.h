#ifndef __DRAW_H__
#define __DRAW_H__
#include "common.h"
using namespace std;


void drawCar(const POINT &pos, int type);
void eraseCar(const POINT &pos);
void drawPerson(const POINT& pos);
void erasePerson(const POINT& pos);
void drawTable(const POINT& TLpos, const POINT& BRpos, const short& color);

#endif // !__DRAW_H__

