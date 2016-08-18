#pragma once



#include <glut.h>
#include "glaux.h"


#define WALL 1
#define PORTAL 11 
#define ROAD 2

#define PORTAL1_IN 1
#define PORTAL1_OUT 5
#define PORTAL2_IN 2
#define PORTAL2_OUT 6
#define PORTAL3_IN 3
#define PORTAL3_OUT 4

struct coordp
{
	int x,y;
	//coordp(){x=0;y=0;};
};



enum eventsp
{
	UPp,DOWNp,RIGHTp,LEFTp,ENDp,PAUSEp
};

class Pacman
{
	coordp location;
	GLuint texture;
	int  map[28][19];
	
	eventsp cur_event;
	int life;
	coordp portals[6];
public:
	Pacman(void);
	~Pacman(void);

	coordp getLocation(){return location;};
	GLuint getTexture(){return texture;};
	void setLocation(int x,int y){location.x = x,location.y = y;};
	void setLocation(coordp x){location = x;};
	eventsp getCur_event(){return cur_event;};
	void setCur_event(eventsp x){cur_event = x;};
	int getLife(){return life;};
	void dead();

	int getPortal(coordp x);
	coordp getPortal(int i){return portals[i-1];};
	bool isPortal(coordp x);
	//bool canEatFoods();
	bool canPacmanGo(eventsp x);
	void setLocation(eventsp x);
	void loadTexture(char *s);
	void setTextureForEvent();
	void randomWay();

	void draw();
};

