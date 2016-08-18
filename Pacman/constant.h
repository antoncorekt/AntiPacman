// файл определения макроподстановок
#pragma once
#define WIDHT 600
#define HEIGTH 600

#define RED 10
#define BLUE 20
#define PINK 30
#define YELLOW 40

#define IDB_GAME 10000
#define IDB_EXIT 10001


struct coord
{
	int x,y;
};

enum events
{
	UP,DOWN,RIGHT,LEFT,END,PAUSE
};