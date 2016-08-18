#pragma once
/* Класс Призрак


*/

#include "constant.h"
#include <glut.h>
#include "glaux.h"

#define WALL 1
#define PORTAL 11 // ПОКА НЕТ ПОРТАЛОВ НА КАРТЕ
#define ROAD 2

class Ghost
{
	coord location; // текущее местоположение призрака
	bool player; // переменная определяющия кто управляет призраком
	events cur_event; // текущее направление движения
	GLuint texture;
	int  map[28][19];
	events Next_event;
	coord prev_location;
	bool buferEvent;
	
	bool result;
public:
	Ghost(void);
	~Ghost(void);
	int matrix[28][19][3];

	events getCur_event(){return cur_event;};
	events getNext_event(){return Next_event;}; 
	coord getLocation(){return location;};
	coord getPrev_location(){return prev_location;};
	GLuint getTexture(){return texture;};
	void setLocation(coord x) {prev_location = location;location = x;};
	void setPrev_location(coord x) {prev_location = x;};
	void setLocation(int x,int y) {prev_location = location;location.x = x;location.y = y;};
	void setCur_event(events x){Next_event=cur_event;  cur_event = x;};
	void setNext_event(events x){Next_event = x;};
	void setResult(bool x){result = x;};
	bool getResult(){return result;};
	bool isPlayer(){return (player==true);};
	bool isBuferEvent(){return (buferEvent==true);};
	void setPlayer(bool x){player = x;};
	void re_Player(){player = !player;};
	void setTexture(GLuint x){texture = x;};
	void setBuferEvent(bool x){buferEvent = x;};
	
	void setLocation(events x);
	void seachPortals(coord *x[4]);
	void loadTexture(char *s);
	bool canGhostGo(events x);
	void randomWay();
	void draw();

	void setOtherEvent();  //для выбора альтернативного движения
	bool doNewEventToPacman(); // требуется ли поменять решение приведению для ловли пакмена
	events getEventForCurMatrix();
	void SearchWay(int x, int y, int x_to, int y_to);


};

