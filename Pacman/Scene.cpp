#include "Scene.h"


Scene::Scene(void)
{
int map1[28][19] =        {  // было [22][19]
							{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}, //+1
                            {1,1,1,1,11,1,1,1,1,1,1,1,1,1,11,1,1,1,1},
                            {1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,0,1},
                            {1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,2,1},
                            {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                            {1,2,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,2,1},
                            {1,2,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,1},
                            {1,1,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,1},
                            {1,1,1,1,2,1,2,2,2,2,2,2,2,1,2,1,1,1,1},
                            {1,2,2,2,2,2,2,1,1,0,1,1,2,2,2,2,2,2,11},
                            {1,2,1,1,2,1,2,1,0,0,0,1,2,1,2,1,1,2,1},
                            {1,2,1,1,2,1,2,1,0,0,0,1,2,1,2,1,1,2,1},
                            {11,2,2,2,2,1,2,1,0,0,0,1,2,1,2,2,2,2,1},
                            {1,1,1,1,2,2,2,1,1,1,1,1,2,2,2,1,1,1,1},
                            {1,1,1,1,2,1,2,2,2,2,2,2,2,1,2,1,1,1,1},
                            {1,2,2,2,2,1,1,1,2,1,2,1,1,1,2,2,2,2,1},
                            {1,2,1,1,2,2,2,2,2,1,2,2,2,2,2,1,1,2,1},
                            {1,2,2,1,2,1,1,2,1,1,1,2,1,1,2,1,2,2,1},
                            {1,1,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,1,1},
                            {1,1,2,2,1,2,2,2,1,1,1,2,2,2,1,2,2,1,1},
                            {1,2,2,1,1,2,1,2,1,1,1,2,1,2,1,1,2,2,1},
                            {1,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,1},
                            {1,1,1,1,11,1,1,1,1,1,1,1,1,1,11,1,1,1,1},
							{5,5,-1,7,5,5,-1,8,5,5,-1,9,5,5,5,-1,10,5,5}, //+1
							{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6}, //+1
							{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},  //+1
							{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6}  //+1
                            };
	
score =0;
for (int i=0;i<28;i++)
	for (int j=0;j<19;j++)
	{
		map[i][j]=map1[i][j];
		if (map[i][j]==1)
			score++;
	}

delay=100;

active = true;
cur_ghost = RED_GHOST;

for (int i=0;i<255;i++)
	keys[i]=false;


ghost[RED_GHOST].loadTexture("Data/0.bmp");
ghost[PINK_GHOST].loadTexture("Data/1.bmp");
ghost[BLUE_GHOST].loadTexture("Data/2.bmp");
ghost[YELLOW_GHOST].loadTexture("Data/3.bmp");

for (int i=0;i<4;i++)
{
	ghost[i].setLocation(12,10-i);
	ghost[i].setPrev_location(ghost[i].getLocation());
}

pacman.setLocation(14,10);

}


Scene::~Scene(void)
{
}


void Scene::setGhost()
{
	char sss[15]="Data/";
	char s[10];
	char ss[5]=".bmp";
	ghost[cur_ghost].setPlayer(false);
	itoa(cur_ghost,s,10);
	strcat(sss,s);
	strcat(sss,ss);


	ghost[cur_ghost].loadTexture(sss);

	switch (cur_ghost)
	{
	case PINK_GHOST:
		cur_ghost = BLUE_GHOST;
		break;
	case RED_GHOST:
		cur_ghost = PINK_GHOST;
		break;
	case BLUE_GHOST:
		cur_ghost = YELLOW_GHOST;
		break;
	case YELLOW_GHOST:
		cur_ghost = RED_GHOST;
		break;
	default:
		cur_ghost = RED_GHOST;
		break;
	}

	strcpy(sss,"Data/");
	strcpy(ss,".bmp");
	ghost[cur_ghost].setPlayer(false);
	itoa(cur_ghost+10,s,10);
	strcat(sss,s);
	strcat(sss,ss);
	ghost[cur_ghost].loadTexture(sss);
	this->loadFon();
}

void Scene::setGhost(int key)
{
	char sss[15]="Data/";
	char s[10];
	char ss[5]=".bmp";
	ghost[cur_ghost].setPlayer(false);
	itoa(cur_ghost,s,10);
	strcat(sss,s);
	strcat(sss,ss);
	ghost[cur_ghost].loadTexture(sss);

	switch (key)
	{
	case 2:
		cur_ghost = BLUE_GHOST;
		break;
	case 1:
		cur_ghost = PINK_GHOST;
		break;
	case 3:
		cur_ghost = YELLOW_GHOST;
		break;
	case 0:
		cur_ghost = RED_GHOST;
		break;
	}
	strcpy(sss,"Data/");
	strcpy(ss,".bmp");
	ghost[cur_ghost].setPlayer(false);
	itoa(cur_ghost+10,s,10);
	strcat(sss,s);
	strcat(sss,ss);
	ghost[cur_ghost].loadTexture(sss);
	this->loadFon();
}

void Scene::setTexture()
{
	ghost[RED_GHOST].setPlayer(TRUE);
	ghost[RED_GHOST].loadTexture("Data/10.bmp");
	ghost[PINK_GHOST].loadTexture("Data/1.bmp");
	ghost[BLUE_GHOST].loadTexture("Data/2.bmp");
	ghost[YELLOW_GHOST].loadTexture("Data/3.bmp");
	pacman.setTextureForEvent();
}

void Scene::draw()
{
	for (int i=0;i<4;i++)
	{
		ghost[i].draw();
	}

	glLoadIdentity();									
	
	glTranslatef(-9.0f,14.0f,-34.0f);  //glTranslatef(-9.0f,11.0f,-27.0f);
	glBindTexture(GL_TEXTURE_2D, fon);
	
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_QUADS);  // -----28

	for(int i =0;i<28;i++) //  --------28
		for(int j = 0 ; j< 19;j++)
		{
			if(map[i][j]==6)
			{
				glTexCoord2f(0.0f, 0.0f); glVertex3f (0.0f+j,  -0.0f-i-1, 0.0f);  // нижний левый
				glTexCoord2f(1.0f, 0.0f); glVertex3f (0.0f+j+1, -0.0f-i-1, 0.0f); // нихний правый 
				glTexCoord2f(1.0f, 1.0f); glVertex3f (0.0f+j+1,  -0.0f-i, 0.0f);// верхний правый 
				glTexCoord2f(0.0f, 1.0f); glVertex3f (0.0f+j,  -0.0f-i, 0.0f);	//верхний левый */
			}
		} 
	glEnd();

	pacman.draw();
	gui.draw(score);

	gui.log(pacman.getLife());
	/*if (ghost[BLUE_GHOST].matrix[ghost[BLUE_GHOST].getLocation().x][ghost[BLUE_GHOST].getLocation().y][0]>0)
	gui.log(ghost[BLUE_GHOST].matrix[ghost[BLUE_GHOST].getLocation().x][ghost[BLUE_GHOST].getLocation().y][0]);*/
	//Sleep(900);
}

void Scene::loadFon()
{
	char s[20];
	switch (cur_ghost)
	{
	case RED_GHOST:
		strcpy(s,"Data/100.bmp");
		break;
	case PINK_GHOST:
		strcpy(s,"Data/101.bmp");
		break;
	case BLUE_GHOST:
		strcpy(s,"Data/102.bmp");
		break;
	case YELLOW_GHOST:
		strcpy(s,"Data/103.bmp");
		break;
	default:
		break;
	}
	AUX_RGBImageRec *texture1;
	texture1 = auxDIBImageLoad(s);
	// Создание текстуры
	glGenTextures(1, &fon);
	glBindTexture(GL_TEXTURE_2D, fon);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
}

bool Scene::canPacmenEatFoods()
{
	if (map[pacman.getLocation().x][pacman.getLocation().y]==FOOD)
		return true;
	return false;
}

void Scene::PacmenEatFoods()
{
	if (map[pacman.getLocation().x][pacman.getLocation().y]==FOOD)
		map[pacman.getLocation().x][pacman.getLocation().y]=NOTFOOD;
	score--;
}

void Scene::pacmanDead()
{
	if (pacman.getLife()>1)
	{
		for (int i=0;i<4;i++)
		{
			ghost[i].setLocation(12,10-i);
			ghost[i].setPrev_location(ghost[i].getLocation());
		}
		pacman.dead();
		score+=50;
		pacman.setLocation(14,10);
		setDelay(2000);	
	}
	else
	 keys[VK_F1]=true;
}

void Scene::setLocationGhost()
{
	//intellectGhost();
	
	//Sleep(4000);

	if(this->keys[VK_UP])
	{
		this->keys[VK_UP]=FALSE;

		
		if (ghost[cur_ghost].canGhostGo(LEFT))	
			ghost[cur_ghost].setCur_event(LEFT);
		else
			{
			ghost[cur_ghost].setNext_event(LEFT);
			ghost[cur_ghost].setBuferEvent(true);
			}
	}
		
	if(this->keys[VK_DOWN])
	{				
		this->keys[VK_DOWN]=FALSE;
					
		if (ghost[cur_ghost].canGhostGo(RIGHT))	
			ghost[cur_ghost].setCur_event(RIGHT);
		else
		{
			ghost[cur_ghost].setNext_event(RIGHT);
		    ghost[cur_ghost].setBuferEvent(true);
		}
	}
	if(this->keys[VK_LEFT])
	{
		this->keys[VK_LEFT]=FALSE;
		if (ghost[cur_ghost].canGhostGo(DOWN))	
			ghost[cur_ghost].setCur_event(DOWN);
		else
		{
			ghost[cur_ghost].setNext_event(DOWN);
			ghost[cur_ghost].setBuferEvent(true);
		}
	} 
	if(this->keys[VK_RIGHT]) //right
	{
		this->keys[VK_RIGHT]=FALSE;
		if (ghost[cur_ghost].canGhostGo(UP))	
			ghost[cur_ghost].setCur_event(UP);
		else
			{
			ghost[cur_ghost].setNext_event(UP);
			ghost[cur_ghost].setBuferEvent(true);
			}
	}
				
	if (ghost[cur_ghost].isBuferEvent()&&ghost[cur_ghost].canGhostGo(ghost[cur_ghost].getNext_event()))
	{
			ghost[cur_ghost].setBuferEvent(false);
			ghost[cur_ghost].setLocation(ghost[cur_ghost].getNext_event());
			ghost[cur_ghost].setCur_event(ghost[cur_ghost].getNext_event());
	}
	else
			if (ghost[cur_ghost].canGhostGo(ghost[cur_ghost].getCur_event()))
					ghost[cur_ghost].setLocation(ghost[cur_ghost].getCur_event());
			/*else
					{
						blinky.setOtherEvent();
						blinky.setLocation(blinky.getCur_event());
			}*/
	for (int i=0;i<4;i++)
		if ((i!=cur_ghost))
			ghost[i].randomWay();

	pacman.randomWay();
	pacman.setTextureForEvent();
	if (this->canPacmenEatFoods())
		this->PacmenEatFoods();

	for (int i=0;i<4;i++)
		if ((ghost[i].getLocation().x==pacman.getLocation().x)&&(ghost[i].getLocation().y==pacman.getLocation().y))
			this->pacmanDead();
}

void Scene::intellectGhost()
{
	//ghost[BLUE_GHOST].SearchWay(ghost[BLUE_GHOST].getLocation().x,ghost[BLUE_GHOST].getLocation().y,pacman.getLocation().x,pacman.getLocation().y);
	int i=BLUE_GHOST;

	if (ghost[i].doNewEventToPacman())
	{
		ghost[i].SearchWay(ghost[i].getLocation().x,ghost[i].getLocation().y,pacman.getLocation().x,pacman.getLocation().y);
		if (ghost[i].canGhostGo(ghost[i].getEventForCurMatrix()))
		{
			ghost[i].setCur_event(ghost[i].getEventForCurMatrix());
			ghost[i].setLocation(ghost[i].getCur_event());
		}
	}

	ghost[i].setLocation(ghost[i].getCur_event());

}