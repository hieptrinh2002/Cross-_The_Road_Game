#pragma once
#ifndef __MENU_H__
#define __MENU_H__
#include "common.h"
#include "draw.h"
#include<fstream>
#include<iostream>
#include<string>
using namespace std;

void menuHeader(int color);
void optionText();
void mainMenu();
void luaChon(int xPos, int yPos);
void xuliChon(int c);
void help();
void about();

void loadgame();
void loadingBar(int percent);
void menuNoLoading();
#endif // !__MENU_H__
