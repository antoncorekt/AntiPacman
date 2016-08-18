#include "Ghost.h"
#include <ctime>
#include <iostream>

Ghost::Ghost(void)
{
	location.x = 0;
	location.y = 0;
	cur_event = UP;
	//texture = 0;
	player = false;
	Next_event = UP;
	buferEvent = false;

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
for (int i=0;i<28;i++)
	for (int j=0;j<19;j++)
		map[i][j]=map1[i][j];


}


Ghost::~Ghost(void)
{
}


void Ghost::loadTexture(char *s)
{
	AUX_RGBImageRec *texture1;
	texture1 = auxDIBImageLoad(s);
	// —оздание текстуры
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);

}

void Ghost::seachPortals(coord *x[4])
{
	int k=0;
	for (int i=0;i<28;i++)
	  for (int j=0;j<19;j++)
		if (map[i][j]==1)
		{
			;
		}
}

void Ghost::setLocation(events x)
{
	
	switch (x)
	{
	case UP:
		if ((map[location.x][location.y+1]!=WALL)&&(map[location.x][location.y+1]!=PORTAL))
		location.y+=1;
		break;
	case DOWN:
		if ((map[location.x][location.y-1]!=WALL)&&(map[location.x][location.y-1]!=PORTAL))
		location.y-=1;
		break;
	case LEFT:
		if ((map[location.x-1][location.y]!=WALL)&&(map[location.x-1][location.y]!=PORTAL))
		location.x-=1;
		break;
	case RIGHT:
		if ((map[location.x+1][location.y]!=WALL)&&(map[location.x+1][location.y]!=PORTAL))
		location.x+=1;
		break;
	default:
		break;
	}
	if ((location.x==4)&&(location.y==1)) 
		location.y == 22;

}

bool Ghost::canGhostGo(events x)
{
	switch (x)
	{
	case UP:
		if ((map[location.x][location.y+1]!=WALL)&&(map[location.x][location.y+1]!=PORTAL))
			return true;
		return false;
	case DOWN:
		if ((map[location.x][location.y-1]!=WALL)&&(map[location.x][location.y-1]!=PORTAL))
			return true;
		return false;
	case LEFT:
		if ((map[location.x-1][location.y]!=WALL)&&(map[location.x-1][location.y]!=PORTAL))
			return true;
		return false;
	case RIGHT:
		if ((map[location.x+1][location.y]!=WALL)&&(map[location.x+1][location.y]!=PORTAL))
			return true;
		return false;

	default:
		return true;
		break;
	}
	return false;
}

void Ghost::randomWay()
{
	srand(time(NULL));
	int k = std::rand()%2;
	if (!(this->canGhostGo(cur_event))&&k==1)
		while (!(this->canGhostGo(cur_event)))
		{
			int k = std::rand()%4;
			switch (k)
			{
			case 0: cur_event = RIGHT; break;
			case 1: cur_event = DOWN; break;
			case 2: cur_event = LEFT; break;
			case 3: cur_event = UP; break;
			default:
				cur_event = LEFT; break;
			}
		}
	else
		this->setOtherEvent();
	this->setLocation(cur_event);
	
}

void Ghost::setOtherEvent()
{
	srand(time(NULL));
	int k = std::rand()%2;
	switch (cur_event)
	{
	case UP:
	case DOWN:
		if (k==1)
		{
			if (this->canGhostGo(LEFT))
				cur_event = LEFT;
			else
			  if (this->canGhostGo(RIGHT))
				cur_event = RIGHT;
		}
		else
		{
			if (this->canGhostGo(RIGHT))
				cur_event = RIGHT;
			else
			  if (this->canGhostGo(LEFT))
				cur_event = LEFT;
		}
		break;
	case RIGHT:
	case LEFT:
		if (k==1)
		{
		if (this->canGhostGo(UP))
			cur_event = UP;
		else
			if (this->canGhostGo(DOWN))
				cur_event = DOWN;
		}
		else
		{
			if (this->canGhostGo(DOWN))
				cur_event = DOWN;
			else
			  if (this->canGhostGo(UP))
				cur_event = UP;
		}
		break;
	}
}


events getEventForNewCoord(coord prev,coord cur)
{
	if ((prev.x==cur.x)&&(prev.y==cur.x))
		return PAUSE;
	if ((cur.x==prev.x-1)&&(prev.y==cur.x))
		return LEFT;
	if ((cur.x==prev.x+1)&&(prev.y==cur.x))
		return RIGHT;
	if ((cur.x==prev.x)&&(cur.y==prev.y+1))
		return UP;
	if ((cur.x==prev.x)&&(cur.y==prev.y-1))
		return DOWN;
};

void Ghost::draw()
{
	for (int fps=0;fps<100;fps++)
	{
	glLoadIdentity();									
	
	glTranslatef(-9.0f,14.0f,-34.0f);  //glTranslatef(-9.0f,11.0f,-27.0f);
	glBindTexture(GL_TEXTURE_2D, this->getTexture());
	
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_QUADS);  // -----28

	for(int i =0;i<28;i++) //  --------28
		for(int j = 0 ; j< 19;j++)
		{
			if((i==this->getLocation().x)&&(j==this->getLocation().y))
			{
				
				switch (getEventForNewCoord((this->getPrev_location()),(this->getLocation())))
				{
				case UP:
					

					break;
		
				default:
				break;	
				}
			glTexCoord2f(0.0f, 0.0f); glVertex3f (0.0f+j  ,  -0.0f-i-1 , 0.0f);  // нижний левый
					glTexCoord2f(1.0f, 0.0f); glVertex3f (0.0f+j+1 , -0.0f-i-1, 0.0f); // нихний правый 
					glTexCoord2f(1.0f, 1.0f); glVertex3f (0.0f+j+1 ,  -0.0f-i , 0.0f);// верхний правый 
					glTexCoord2f(0.0f, 1.0f); glVertex3f (0.0f+j ,  -0.0f-i , 0.0f);	//верхний левый */
					

				
			}
		} 
	glEnd();
	}
}

bool Ghost::doNewEventToPacman()
{
	int i=0;
	if (this->canGhostGo(UP))
		i++;
	if (this->canGhostGo(DOWN))
		i++;
	if (this->canGhostGo(LEFT))
		i++;
	if (this->canGhostGo(RIGHT))
		i++;
	if (i>2)
		return true;
	else
		return false;
}

events Ghost::getEventForCurMatrix()
{
	int cur_x = this->getLocation().x;
	int cur_y = this->getLocation().y;
	int cur_v = matrix[cur_x][cur_y][0];

	if ((matrix[cur_x-1][cur_y][0]<cur_v)&&(map[cur_x-1][cur_y]!=WALL))
		return LEFT;
	if ((matrix[cur_x+1][cur_y][0]<cur_v)&&(map[cur_x+1][cur_y]!=WALL))
		return RIGHT;
	if ((matrix[cur_x][cur_y-1][0]<cur_v)&&(map[cur_x][cur_y-1]!=WALL))
		return UP;
	if ((matrix[cur_x][cur_y+1][0]<cur_v)&&(map[cur_x][cur_y+1]!=WALL))
		return DOWN;
}

void Ghost::SearchWay(int x, int y, int x_to, int y_to)
{
	//

	const int sizei =28;
	const int sizej =19;
	
	int map1[sizei][sizej];

	for (int i=0;i<28;i++)
	for (int j=0;j<19;j++)
		if ((map[i][j]==1)||(map[i][j]==11))
			map1[i][j]=1;
		else
			map1[i][j]=0;

	int step;
	bool added=true;
		result=true;
	for(int i=0;i<sizei;i++)
	{
		for(int j=0;j<sizej;j++)
		{
			if(map1[i][j]!=0) // 0-2
			{
				matrix[i][j][0] = -2;// зан€то
			}
			else
			{
				matrix[i][j][0] = -1;// ћы еще нигде не были
			}
		}
	}
	matrix[x_to][y_to][0]= 0;// ƒо финиша ноль шагов - от него будем разбегатьс€
	step = 0; // »значально мы сделали ноль шагов
	
	// ѕока вершины добал€ютс€ и мы не дошли до старта

	while(added && matrix[x][y][0]==-1)
	{
		added = false;// ѕока что ничего не добавили
		step++;// ”величиваем число шагов

		for(int i=0;i<sizei;i++)// ѕробегаем по всей карте
		{
			for(int j=0;j<sizej;j++)
			{
				// ≈сли (i, j) была добавлена на предыдущем шаге
				// ѕробегаем по всем четырем сторонам
				if(matrix[i][j][0]== step-1)
				{
					int _i,_j;

					_i=i+1;_j=j;
					// ≈сли не вышли за пределы карты -  обрабатываем
					if(_i>=0 && _j>=0 && _i<sizei && _j<sizej)
					{
						// ≈сли (_i, _j) уже добавлено или непроходимо, то не обрабатываем 
						 if(matrix[_i][_j][0]==-1 && matrix[_i][_j][0]!=-2)
						 {
							 matrix[_i][_j][0]= step; // ƒобав-
							 matrix[_i][_j][1]= i; // л€-
							 matrix[_i][_j][2]= j; // ем
							 added = true; // „то-то добавили
						 }
					}
					_i=i-1;_j=j;
					// ≈сли не вышли за пределы карты -  обрабатываем
					if(_i>=0 && _j>=0 && _i<sizei && _j<sizej)
					{
						// ≈сли (_i, _j) уже добавлено или непроходимо, то не обрабатываем 
						if(matrix[_i][_j][0]==-1 && matrix[_i][_j][0]!=-2)
						{
							matrix[_i][_j][0]= step; // ƒобав-
							matrix[_i][_j][1]= i; // л€-
							matrix[_i][_j][2]= j; // ем
							added = true; // „то-то добавили
						}
					}
					_i=i;_j=j+1;
					// ≈сли не вышли за пределы карты -  обрабатываем
					if(_i>=0 && _j>=0 && _i<sizei && _j<sizej)
					{
						// ≈сли (_i, _j) уже добавлено или непроходимо, то не обрабатываем 
						if(matrix[_i][_j][0]==-1 && matrix[_i][_j][0]!=-2)
						{
							matrix[_i][_j][0]= step; // ƒобав-
							matrix[_i][_j][1]= i; // л€-
							matrix[_i][_j][2]= j; // ем
							added = true; // „то-то добавили
						}
					}
					_i=i;_j=j-1;
					// ≈сли не вышли за пределы карты -  обрабатываем
					if(_i>=0 && _j>=0 && _i<sizei && _j<sizej)
					{
						// ≈сли (_i, _j) уже добавлено или непроходимо, то не обрабатываем 
						if(matrix[_i][_j][0]==-1 && matrix[_i][_j][0]!=-2)
						{
							matrix[_i][_j][0]= step; // ƒобав-
							matrix[_i][_j][1]= i; // л€-
							matrix[_i][_j][2]= j; // ем
							added = true; // „то-то добавили
						}
					}
				}
			}
		}
	}

	if(matrix[x][y][0]== -1)
	{
		result = false; // то пути не существует
	}
	else 
		result = true;

	/*if(result)
	{
		int _i=x,_j=y;

		while(matrix[_i][_j][0]!=0)
		{	
                        // тут ваш код где  записываем значение клеток и шагаем дальше к началу
			// записывать надо _i _J	
			int li = matrix[_i][_j][1];
			int lj = matrix[_i][_j][2];
			_i=li;_j=lj;
		}
	}
	*/

}