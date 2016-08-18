#include "Pacman.h"
#include <ctime>


Pacman::Pacman(void)
{

	location.x = 0;
	location.y = 0;
	life = 3;
	cur_event = DOWNp;

	int map1[28][19] =        { 
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
int k=0;
for (int i=0;i<28;i++)
	for (int j=0;j<19;j++)
	{
			map[i][j]=map1[i][j];
			if (map[i][j]==PORTAL)
			{
				portals[k].x=i;
				portals[k].y=j;
				k++;
			}
	}


}


Pacman::~Pacman(void)
{
}

void Pacman::loadTexture(char *s)
{
	AUX_RGBImageRec *texture1;
	texture1 = auxDIBImageLoad(s);
	// Создание текстуры
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

}

void Pacman::dead()
{
	if (this->getLife()>0)
		life--;
}

int Pacman::getPortal(coordp x)
{
	for (int	i=0;i<6;i++)
		if ((x.x==portals[i].x)&&(x.y==portals[i].y))
			return i+1;
	return -1;
}

bool Pacman::isPortal(coordp x)
{
	for (int i=0;i<6;i++)
		if ((x.x==portals[i].x)&&(x.y==portals[i].y))
			return true;
	return false;
}

bool Pacman::canPacmanGo(eventsp x)
{
	switch (cur_event)
	{
	case UPp:
		if (map[location.x][location.y+1]!=WALL)
			return true;
		return false;
		
	case DOWNp:
		if (map[location.x][location.y-1]!=WALL)
			return true;
		return false;
	case RIGHTp:
		if (map[location.x+1][location.y]!=WALL)
			return true;
		return false;
	case LEFTp:
		if (map[location.x-1][location.y]!=WALL)
			return true;
		return false;
	}
	return false;
}

void Pacman::setLocation(eventsp x)
{
	switch (cur_event)
	{
	case UPp:
		if ((map[location.x][location.y+1]!=WALL))
		location.y+=1;
		break;
	case DOWNp:
		if ((map[location.x][location.y-1]!=WALL))
		location.y-=1;
		break;
	case RIGHTp:
		if ((map[location.x+1][location.y]!=WALL))
		location.x+=1;
		break;
	case LEFTp:
		if ((map[location.x-1][location.y]!=WALL))
		location.x-=1;
		break;
	}
	if (this->isPortal(location))
	{
		int xx = getPortal(location);
		switch (xx)
		{
		case PORTAL1_IN:
			/*location.x = portals[PORTAL1_OUT].x;
			location.y = portals[PORTAL1_OUT].y-1;*/
			this->setLocation(14,10);
			break;
		case PORTAL1_OUT:
			/*location.x = portals[PORTAL1_IN].x;
			location.y = portals[PORTAL1_IN].y+1;*/
			this->setLocation(14,10);			break;
		case PORTAL2_IN:
			/*location.x = portals[PORTAL2_OUT].x;
			location.y = portals[PORTAL2_OUT].y-1;*/
			this->setLocation(14,10);
		case PORTAL2_OUT:
			/*location.x = portals[PORTAL2_IN].x;
			location.y = portals[PORTAL2_IN].y+1;*/
			this->setLocation(14,10);
			break;
		case PORTAL3_IN:
			/*location.x = portals[PORTAL3_OUT].x-1;
			location.y = portals[PORTAL3_OUT].y;*/
			this->setLocation(14,10);
		case PORTAL3_OUT:
			/*location.x = portals[PORTAL3_IN].x+2;
			location.y = portals[PORTAL3_IN].y;*/
			this->setLocation(14,10);
			break;
		break;
		}
		
		//0Sleep(5000);
		//this->getTexture();
	}

}

void Pacman::setTextureForEvent()
{
	switch (cur_event)
	{
	case UPp:
		this->loadTexture("Data/pacmanRIGHT.bmp");
		break;
	case DOWNp:
		this->loadTexture("Data/pacmanLEFT.bmp");
		break;
	case RIGHTp:
		this->loadTexture("Data/pacmanDOWN.bmp");
		break;
	case LEFTp:
		this->loadTexture("Data/pacmanUP.bmp");
		break;
	default:
		this->loadTexture("Data/pacmanRIGHT.bmp");
		break;
	}

}

void Pacman::randomWay()
{
	srand(time(NULL));	

	do
	{
		int k = rand()%4;
		switch (k)
		{
		case 0:
			cur_event = UPp;
			break;
		case 1:
			cur_event = DOWNp;
			break;
		case 2:
			cur_event = LEFTp;
			break;
		case 3:
			cur_event = RIGHTp;
			break;
		default:
			cur_event = UPp;
			break;
		}

	} while (!(this->canPacmanGo(this->getCur_event())));
	if (this->canPacmanGo(this->getCur_event()))
	this->setLocation(cur_event);
}

void Pacman::draw()
{
	glLoadIdentity();		//отчищает матрицу							
	glTranslatef(-9.0f,14.0f,-34.0f);  // смещение по координатам
	glBindTexture(GL_TEXTURE_2D, this->getTexture()); // выбор текстуры
	glColor3f(1.0f,1.0f,1.0f); // цвет
	glBegin(GL_QUADS);  // начало прорисовки
	for(int i =0;i<28;i++) // цыкл по карте
		for(int j = 0 ; j< 19;j++)
		{
			if((i==this->getLocation().x)&&(j==this->getLocation().y)) // положение пакмена
			{		
					glTexCoord2f(0.0f, 0.0f); glVertex3f (0.0f+j  ,  -0.0f-i-1 , 0.0f);  // нижний левый
					glTexCoord2f(1.0f, 0.0f); glVertex3f (0.0f+j+1 , -0.0f-i-1, 0.0f); // нихний правый 
					glTexCoord2f(1.0f, 1.0f); glVertex3f (0.0f+j+1 ,  -0.0f-i , 0.0f);// верхний правый 
					glTexCoord2f(0.0f, 1.0f); glVertex3f (0.0f+j ,  -0.0f-i , 0.0f);	//верхний левый */				
			}
		} 
	glEnd(); // конец рисования
	}

