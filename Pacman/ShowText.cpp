#include "ShowText.h"


ShowText::ShowText(void)
{
}


ShowText::~ShowText(void)
{
}

void load(GLuint x, int m )
{
	glLoadIdentity();									
	
	glTranslatef(-9.0f,14.0f,-34.0f);  //glTranslatef(-9.0f,11.0f,-27.0f);
	glBindTexture(GL_TEXTURE_2D, x);
	
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_QUADS);  // -----28

	for(int i =0;i<28;i++) //  --------28
		for(int j = 0 ; j< 19;j++)
		{
			if((i==0)&&(j==m))
			{		
					glTexCoord2f(0.0f, 0.0f); glVertex3f (0.0f+j  ,  -0.0f-i-1 , 0.0f);  // нижний левый
					glTexCoord2f(1.0f, 0.0f); glVertex3f (0.0f+j+1 , -0.0f-i-1, 0.0f); // нихний правый 
					glTexCoord2f(1.0f, 1.0f); glVertex3f (0.0f+j+1 ,  -0.0f-i , 0.0f);// верхний правый 
					glTexCoord2f(0.0f, 1.0f); glVertex3f (0.0f+j ,  -0.0f-i , 0.0f);	//верхний левый */
				
			}
		} 
	glEnd();
	}



void ShowText::loadTexture(char *s,GLuint &texture)
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

int ShowText::lenght(int x)
{
	char s[20];
	itoa(x,s,10);
	return strlen(s);
}

void ShowText::draw(int x)
{
	GLuint gl;

	loadTexture("Data/S.bmp",gl);load(gl,0);
	loadTexture("Data/C.bmp",gl);load(gl,1);
	loadTexture("Data/O.bmp",gl);load(gl,2);
	loadTexture("Data/R.bmp",gl);load(gl,3);
	loadTexture("Data/E.bmp",gl);load(gl,4);
	loadTexture("Data/TT.bmp",gl);load(gl,5);
	
	int len = lenght(x);
	char sss[15]="Data/Q";
	char s[30];
	char ss[5]=".bmp";
	itoa(x,s,10);
	for (int i = 0;i<strlen(s);i++)
	{
	strcpy(sss,"Data/Q");
	strcpy(ss,".bmp");
	sss[6]=s[i];
	sss[7]='\0';
	strcat(sss,ss);
	loadTexture(sss,gl);
	load(gl,6+i);
	}

}

void ShowText::log(int x,int q)
{
	GLuint gl;

	int len = lenght(x);
	char sss[15]="Data/Q";
	char s[30];
	char ss[5]=".bmp";
	itoa(x,s,10);
	for (int i = 0;i<strlen(s);i++)
	{
	strcpy(sss,"Data/Q");
	strcpy(ss,".bmp");
	sss[6]=s[i];
	sss[7]='\0';
	strcat(sss,ss);
	loadTexture(sss,gl);
	load(gl,q+i);
	}

}