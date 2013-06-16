// Pacman.cpp
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "Pacman.h"

const double PI = 4.0*atan(1.0);

GLfloat matPacman_Kd[] = {.75, .70, 0, 1};
GLfloat matPacman_Ks[] = {1, 1, 1, 1};
GLfloat matPacman_S[] = {120};

GLfloat matPacNinja_Ka[] = {0, 0, 0, 1};
GLfloat matPacNinja_Kd[] = {.01, .01, .01, 1};
GLfloat matPacNinja_Ks[] = {1, 1, 1, 1};
GLfloat matPacNinja_S[] = {120};
GLfloat matPacHeadband[] = {1, 0, 0, 1};

GLfloat matPacmanWhite[] = {1, 1, 1, 1};
GLfloat matPacmanBlack[] = {0, 0, 0, 1};

Pacman::Pacman() {
	_speed = .125;
	_animate = true;
	_angle = 0;
	_x = 16;
	_y = -12;
	_radius = 0.5;
	_pause = 0;
	_ninja = 0;
	_direction = 'r';
	_life = 3;
}


void Pacman::drawPacman(GLfloat amb[4], int light) {
	
	//pacSir
	glPushMatrix();
	if (_ninja) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, matPacNinja_Ka);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matPacNinja_Kd);
		glMaterialfv(GL_FRONT, GL_SPECULAR, matPacNinja_Ks);
		glMaterialfv(GL_FRONT, GL_SHININESS, matPacNinja_S);
	}
	else {
		glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matPacman_Kd);
		glMaterialfv(GL_FRONT, GL_SPECULAR, matPacman_Ks);
		glMaterialfv(GL_FRONT, GL_SHININESS, matPacman_S);
	}

	glTranslatef(_x, _y, 0.0);
	glRotatef(_angle, 0.0, 0.0, 1.0);
	glutSolidSphere(_radius, 10, 10);
	
	//olho esquerdo
	glPushMatrix();
	if(light == 5)
		glMaterialfv(GL_FRONT, GL_AMBIENT, matPacmanWhite);
	else
		glMaterialfv(GL_FRONT, GL_AMBIENT, matPacmanBlack);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matPacmanWhite);
	glTranslatef(0.3, 0.2, 0.15);
	glutSolidSphere(0.15, 10, 10);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matPacmanBlack);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matPacmanBlack);
	glTranslatef(0.11, 0.02, 0.0);
	glutSolidSphere(0.05, 10, 10);
	glPopMatrix();
	
	//olho direito
	glPushMatrix();
	if(light == 5)
		glMaterialfv(GL_FRONT, GL_AMBIENT, matPacmanWhite);
	else
		glMaterialfv(GL_FRONT, GL_AMBIENT, matPacmanBlack);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matPacmanWhite);
	glTranslatef(0.3, -0.2, 0.15);
	glutSolidSphere(0.15, 10, 10);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matPacmanBlack);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matPacmanBlack);
	glTranslatef(0.11, -0.02, 0.0);
	glutSolidSphere(0.05, 10, 10);
	glPopMatrix();
	
	//sobrancelha esqerda
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, matPacmanBlack);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matPacmanBlack);
	glTranslatef(0.35, 0.2, 0.3);
	glRotatef(20.0, 1.0, 0.0, 0.0);
	glScalef(1.0, 2.5, 1.0);
	glutSolidCube(0.1);
	glPopMatrix();

	//sobrancelha direita
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, matPacmanBlack);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matPacmanBlack);
	glTranslatef(0.35, -0.2, 0.3);
	glRotatef(-20.0, 1.0, 0.0, 0.0);
	glScalef(1.0, 2.5, 1.0);
	glutSolidCube(0.1);
	glPopMatrix();
	
	//bigode
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, matPacmanBlack);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matPacmanBlack);
	glTranslatef(0.41, 0.0, -0.1);
	glScalef(1.0, 1.0, 2.0);
	glutSolidCube(0.1);
	glPopMatrix();

	//ninja
	if (_ninja) {
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, matPacHeadband);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matPacHeadband);
		glMaterialfv(GL_FRONT, GL_SPECULAR, matPacHeadband);
		glMaterialf(GL_FRONT, GL_SHININESS, 120);
		glTranslatef(0, 0, 0.2);
		glScalef(0.9, 1, 1.25);
		glutSolidTorus(0.25, 0.27, 3, 20);
		glPopMatrix();
	}
	glPopMatrix();
}

// Movimento
void Pacman::move(char direction) {


	if(_x == 32 && _y == -9) _x = 0;

	if(_x == 0 && _y == -9) _x = 32;


	switch(direction) {
		case 'r': _angle = 0;	 _x += _speed; break;
		case 'l': _angle = 180;	 _x -= _speed; break;
		case 'u': _angle = 90;	 _y += _speed; break;
		case 'd': _angle = 270;  _y -= _speed; break;
	

	glRotatef(_angle, 0.0, 0.0, 1.0);
	glutPostRedisplay();
	}
}