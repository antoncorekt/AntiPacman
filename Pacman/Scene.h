#pragma once
/* Основной класс сцены
 *
 *
 *
*/


#include "Ghost.h"
#include "Pacman.h"
#include "ShowText.h"

#define WALL 1
#define FOOD 2
#define PORTAL 11
#define NOTFOOD 3


#define RED_GHOST 0
#define PINK_GHOST 1
#define BLUE_GHOST 2
#define YELLOW_GHOST 3

class Scene
{
	int score;
	int cur_ghost;
	Ghost ghost[4];
	GLuint fon;
	Pacman pacman;
	ShowText gui;
	int delay;
public:
	int     map[28][19];
	bool	keys[256];			
	bool	active;

	int getDelay(){return delay;};
	void setDelay(int x){delay=x;};
	void setGhost();
	void setGhost(int key);
	void loadFon();

	void getMap(int *x[28][19]);
	void setLocationGhost();
	void draw();
	void setTexture();
	bool canPacmenEatFoods();
	void PacmenEatFoods();
	void pacmanDead();
	void intellectGhost();

	Scene(void);
	~Scene(void);
};

