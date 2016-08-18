#pragma once
#include <iostream>
#include "glaux.h"
#include <glut.h>

class ShowText
{
	int x[10];
	int n;
public:
	ShowText(void);
	~ShowText(void);
	
	void loadTexture(char *s,GLuint &texture);
	int lenght(int x); 
	void draw(int x);

	void log(int x,int q=11);
};

