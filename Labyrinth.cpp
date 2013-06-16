// Labyrinth.cpp
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "Labyrinth.h"
#include "glbmp.h"

//material das paredes
GLfloat matLabyrinth_Kd[] = {0, 0, .65, 1};
GLfloat matLabyrinth_Ks[] = {0, 0, 0, 1};

//material da comida
GLfloat matPebbles_Kd[] = {1, 1, 1, 1};
GLfloat matPebbles_Ks[] = {1, 1, 1, 1};

//material do chao
GLfloat matFloor_Kd[] = {1, 1, 1, 1};
GLfloat matFloor_Ks[] = {1, 1, 1, 1};

//luz 0
GLfloat l0_pos[4] = {0, -1, 1, 0};
GLfloat l0_amb[4]  = {0, 0, 0, 1};
GLfloat l0_spec[4] = {1, 1, 1, 1};
GLfloat l0_diff[4] = {1, 1, 1, 1};

//luz 1
GLfloat l1_amb[4]  = {0, 0, 0, 1};
GLfloat l1_spec[4] = {1, 1, 1, 1};
GLfloat l1_diff[4] = {1, 1, 1, 1};


// Matriz das paredes
int walls[20][33] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,1,1,1,0,1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,1,1,0,1,1,0,1},
	{1,0,1,1,0,1,1,1,0,1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,1,1,0,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,1,0,1,1,1,1,0,1,0,1,0,0,0,1,0,1,0,1,1,1,1,0,1,0,1,1,0,1},
	{1,0,0,0,0,1,0,0,0,1,0,0,1,0,1,1,0,1,1,0,1,0,0,1,0,0,0,1,0,0,0,0,1},
	{1,1,1,1,0,1,0,1,0,1,0,1,1,0,0,0,0,0,0,0,1,1,0,1,0,1,0,1,0,1,1,1,1},
	{1,1,1,1,0,1,0,1,0,0,0,0,1,0,1,1,0,1,1,0,1,0,0,0,0,1,0,1,0,1,1,1,1},
	{0,0,0,0,0,0,0,1,0,1,1,0,1,0,1,0,0,0,1,0,1,0,1,1,0,1,0,0,0,0,0,0,0},
	{1,1,1,1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,1,1,1},
	{1,1,1,1,0,1,0,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,0,1,0,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,0,1},
	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1},
	{1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
	{1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};


// Matriz das bolas de comida
int pebbles[20][33] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0},
	{0,1,0,0,1,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,1,0,0,1,0},
	{0,2,0,0,1,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,1,0,0,2,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,0,0,1,0,1,0,0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,0,0,0,1,0,1,0,0,1,0},
	{0,1,1,1,1,0,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,1,1,1,1,0},
	{0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0},
	{0,0,0,0,1,0,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,1,0,0,0,0},
	{0,0,0,0,1,1,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1,0,0,0,0},
	{0,0,0,0,1,0,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,1,0,0,0,0},
	{0,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0},
	{0,2,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,2,0},
	{0,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0},
	{0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0},
	{0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	

Labyrinth::Labyrinth() {
	_light = 5;
	_pebblesCatched = 0;
	_gamePebbles = 0;

	for (int nRow = 0; nRow < 20; nRow++) {
		for (int nCol = 0; nCol < 33; nCol++) {
			gamePebbles[nRow][nCol] = pebbles[nRow][nCol];
			if(pebbles[nRow][nCol] == 1 || pebbles[nRow][nCol] ==2)
				_gamePebbles++;
		}
	}
}

void Labyrinth::drawWalls(GLfloat amb[4], GLfloat floorAmb[4]) {
	for (int nRow = 0; nRow < 20; nRow++) {
		for (int nCol = 0; nCol < 33; nCol++) {

			glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, floorAmb);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, matFloor_Kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, matFloor_Ks);
			glMaterialf(GL_FRONT, GL_SHININESS, 120);
			glTranslatef(nCol, - nRow, 0.0f);
						glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texname);
			glBegin(GL_QUADS);
				glNormal3f(0, 0, 1);
				glTexCoord2f(1, 1); glVertex3f(0, 0.5, -0.5);
				glTexCoord2f(0, 1); glVertex3f(-0.5, 0.5, -0.5);
				glTexCoord2f(0, 0);	glVertex3f(-0.5, 0, -0.5);
				glTexCoord2f(1, 0); glVertex3f(0, 0, -0.5);

				glTexCoord2f(1, 1); glVertex3f(0.5, 0.5, -0.5);
				glTexCoord2f(0, 1); glVertex3f(0, 0.5, -0.5);
				glTexCoord2f(0, 0);	glVertex3f(0, 0, -0.5);
				glTexCoord2f(1, 0); glVertex3f(0.5, 0, -0.5);

				glTexCoord2f(1, 1); glVertex3f(0, 0, -0.5);
				glTexCoord2f(0, 1); glVertex3f(-0.5, 0, -0.5);
				glTexCoord2f(0, 0);	glVertex3f(-0.5, -0.5, -0.5);
				glTexCoord2f(1, 0); glVertex3f(0, -0.5, -0.5);

				glTexCoord2f(1, 1); glVertex3f(0.5, 0, -0.5);
				glTexCoord2f(0, 1); glVertex3f(0, 0, -0.5);
				glTexCoord2f(0, 0);	glVertex3f(0, -0.5, -0.5);
				glTexCoord2f(1, 0); glVertex3f(0.5, -0.5, -0.5);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();
			glPopMatrix();

			if (walls[nRow][nCol] == 1) {
				glPushMatrix();
				glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, matLabyrinth_Kd);
				glMaterialfv(GL_FRONT, GL_SPECULAR, matLabyrinth_Ks);
				glMaterialf(GL_FRONT, GL_SHININESS, 0);
				glTranslatef(nCol, - nRow, 0.0f);

				//cima
				glBegin(GL_TRIANGLE_FAN);
					glNormal3f(0, 0, 1);
					glVertex3f(0, 0, 0.2);
					glVertex3f(0.5, -0.5, 0.1);
					glVertex3f(0.5, 0.5, 0.1);
					glVertex3f(-0.5, 0.5, 0.1);
					glVertex3f(-0.5, -0.5, 0.1);
					glVertex3f(0.5, -0.5, 0.1);
				glEnd();

				//face esquerda
				glBegin(GL_POLYGON);
					glNormal3f(-1, 0, 0);
					glVertex3f(-0.5, -0.5, -0.3);
					glVertex3f(-0.5, -0.5, 0.1);
					glVertex3f(-0.5, 0.5, 0.1);
					glVertex3f(-0.5, 0.5, -0.3);
				glEnd();

				//face direita
				glBegin(GL_POLYGON);
					glNormal3f(1, 0, 0);
					glVertex3f(0.5, 0.5, -0.3);
					glVertex3f(0.5, 0.5, 0.1);
					glVertex3f(0.5, -0.5, 0.1);
					glVertex3f(0.5, -0.5, -0.3);
				glEnd();

				//face frente
				glBegin(GL_POLYGON);
					glNormal3f(0, -1, 0);
					glVertex3f(0.5, -0.5, -0.3);
					glVertex3f(0.5, -0.5, 0.1);
					glVertex3f(-0.5, -0.5, 0.1);
					glVertex3f(-0.5, -0.5, -0.3);
				glEnd();
				glPopMatrix();
			}
		}
	}
}

void Labyrinth::drawPebbles(GLfloat amb[4]) {

	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matPebbles_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matPebbles_Ks);
	glMaterialf(GL_FRONT, GL_SHININESS, 120);

	for (int nRow = 0; nRow < 20; nRow++)
	{
		for (int nCol = 0; nCol < 33; nCol++) 
		{
			if (gamePebbles[nRow][nCol] == 1) {
				glPushMatrix();
				glTranslatef(nCol, - nRow ,0.0);
				glutSolidSphere(0.1, 10, 10);
				glPopMatrix();
			}
			else{
				if (gamePebbles[nRow][nCol] == 2) {
					glPushMatrix();
					glTranslatef(nCol , - nRow ,0.0);
					glutSolidSphere(0.2, 10, 10);
					glPopMatrix();
				}
			}		
		}
	}
}


/*verifica em que coordenadas há parede dependendo da direcção*/
float Labyrinth::colisionWalls(int x, int y, char direction) {
	
	int i;

	switch(direction) {
		case 'r':
			for(i = x; i <= 33; i++) { if(walls[-y][i] == 1) return i - 1;} 
			break;

		case 'l':
			for(i = x; i >= 0; i--) { if(walls[-y][i] == 1) return i + 1;}
			break;

		case 'u':
			for(i = -y; i >= 0; i--) { if(walls[i][x] == 1) return -i - 1;} 
			break;

		case 'd':	
			for(i = -y; i <= 20; i++) { if(walls[i][x] == 1) return -i + 1;} 
			break;
	}
}


float Labyrinth::openWay(int x, int y, char direction, char directionWanted) {
	
	int i;

	switch(direction) {
		case 'r':
			switch(directionWanted) {
				case 'u':
					for(i = x; i <= 33; i++) { if(walls[-y - 1][i] == 0) return i;} 
					break;
				case 'd':
					for(i = x; i <= 33; i++) { if(walls[-y + 1][i] == 0) return i;} 
					break;
			}
		case 'l':
			switch(directionWanted) {
				case 'u':
					for(i = x; i >= 0; i--) { if(walls[-y - 1][i] == 0) return i;}
					break;
				case 'd':
					for(i = x; i >= 0; i--) { if(walls[-y + 1][i] == 0) return i;} 
					break;
			}
		case 'u':
			switch(directionWanted) {
				case 'r':
					for(i = -y; i >= 0; i--) { if(walls[i][x + 1] == 0) return -i;} 
					break;
				case 'l':
					for(i =-y; i >= 0; i--) { if(walls[i][x - 1] == 0) return -i;}
					break;
			}
		case 'd':
			switch(directionWanted) {
				case 'r':
					for(i = -y; i <= 20; i++) { if(walls[i][x + 1] == 0) return -i;} 
					break;
				case 'l':
					for(i =-y; i <= 20; i++) { if(walls[i][x - 1] == 0) return -i;}
					break;
			}
	}
}


bool Labyrinth::hitWall(float x, float y, char direction) {
	int x1, y1;

	switch(direction){
	case 'r': 
		x1 = (int) x; y1 = (int) y;
		if(walls[-y1][x1+1] == 1) return true; else return false; break;

	case 'l': 
		x1 = (int) floor(x); y1 = (int) y;
		if(walls[-y1][x1-1] == 1) return true; else return false; break;

	case 'u': 
		x1 = (int) floor(x); y1 = (int) ceil(y);
		if(walls[-y1-1][x1] == 1) return true; else return false; break;

	case 'd': 
		x1 = (int) x; y1 = (int) y;
		if(walls[-y1+1][x1] == 1) return true; else return false; break;
	}
}


void Labyrinth::changeLight(GLfloat pos[4], GLfloat dir[3]) {

	switch(_light) {
		default:
		case 5:
			glDisable(GL_LIGHT1);
			glEnable(GL_LIGHT0);
			glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);
			glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_diff);
			glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spec);
			break;

		case 6:
			glDisable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			glLightfv(GL_LIGHT1, GL_POSITION, pos);
			glLightfv(GL_LIGHT1, GL_AMBIENT, l1_amb);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, l1_diff);
			glLightfv(GL_LIGHT1, GL_SPECULAR, l1_spec);
			glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir);
			glLightf(GL_LIGHT1,GL_SPOT_EXPONENT, 0);
			glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45);
			break;	
	}
}

void Labyrinth::loadTexture(const char * bitmap) {
	glbmp_t texture;
	if(!glbmp_LoadBitmap(bitmap, 4, &texture)) {
		fprintf(stderr, "Error loading bitmap file: %s\n", bitmap);
		exit(1);
	}
	glGenTextures(1, &texname);
	glBindTexture(GL_TEXTURE_2D, texname);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.rgb_data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glbmp_FreeBitmap(&texture);
}
