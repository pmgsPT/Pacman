// Ghosts.cpp
#include <GL/glut.h>
#include <cmath>
#include "Ghosts.h"

const double PI = 4.0*atan(1.0);
#define PI_180	PI/180

GLfloat matGhostWhite[] = {1, 1, 1, 1};
GLfloat matGhostBlack[] = {0, 0, 0, 1};



Ghosts::Ghosts(float x, float y) {
	_speed = 0.125;
	_angle = 270;
	_x = x;
	_y = y;
	_vulnerable = 0;
}


void Ghosts::drawGhosts(float x, float y, GLfloat matGhost[4], GLfloat amb[4], int light) {

	//angulo utilizado no desenho para calcular os senos e cossenos
	float _drawAngle = 0;

	glPushMatrix();
	if(_vulnerable) {
		if(light == 5)
			glMaterialfv(GL_FRONT, GL_AMBIENT, matGhostWhite);
		else
			glMaterialfv(GL_FRONT, GL_AMBIENT, matGhostBlack);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matGhostWhite);
		glMaterialfv(GL_FRONT, GL_SPECULAR, matGhostWhite);
		glMaterialf(GL_FRONT, GL_SHININESS, 120);
	}
	else {
		glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matGhost);
		glMaterialfv(GL_FRONT, GL_SPECULAR, matGhost);
		glMaterialf(GL_FRONT, GL_SHININESS, 120);
	}

	glTranslatef(_x, _y, 0.);

	//virar os fantasmas na direcçao do pacSir
	glRotatef(atan2((y - _y), (x - _x)) * (180 / PI) + 90 , 0, 0, 1);

	//parte de cima 1-inicio do efeito redondo
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 0, 1);
		glVertex3f (0, 0, .5);
		for(int i = 0; i <= 10; i++) {
			glNormal3f(cos(_drawAngle * PI_180), sin(_drawAngle * PI_180), 0.48);
			glVertex3f(cos(_drawAngle * PI_180)/6, sin(_drawAngle * PI_180)/6, 0.48);
			_drawAngle += 36.;
		}
	glEnd();
	
	
	glBegin(GL_QUAD_STRIP);
		//parte de cima 2-efeito redondo
		for(int i = 0; i <= 10; i++) {
			glNormal3f(cos(_drawAngle * PI_180), sin(_drawAngle * PI_180), .48);
			glVertex3f(cos(_drawAngle * PI_180)/6, sin(_drawAngle * PI_180)/6, 0.48);
			glNormal3f(cos(_drawAngle * PI_180), sin(_drawAngle * PI_180), .46);
			glVertex3f(cos(_drawAngle * PI_180)/4, sin(_drawAngle * PI_180)/4, 0.46);
			_drawAngle += 36.;
		}

		//parte de cima 3-efeito redondo
		for(int i = 0; i <= 10; i++) {
			glNormal3f(cos(_drawAngle * PI_180), sin(_drawAngle * PI_180), .46);
			glVertex3f(cos(_drawAngle * PI_180)/4, sin(_drawAngle * PI_180)/4, 0.46);
			glNormal3f(cos(_drawAngle * PI_180), sin(_drawAngle * PI_180), .42);
			glVertex3f(cos(_drawAngle * PI_180)/2.5, sin(_drawAngle * PI_180)/2.5, 0.42);
			_drawAngle += 36.;
		}

		//parte de cima 4-efeito redondo
		for(int i = 0; i <= 10; i++) {
			glNormal3f(cos(_drawAngle * PI_180), sin(_drawAngle * PI_180), .42);
			glVertex3f(cos(_drawAngle * PI_180)/2.5, sin(_drawAngle * PI_180)/2.5, 0.42);
			glNormal3f(cos(_drawAngle * PI_180), sin(_drawAngle * PI_180), .38);
			glVertex3f(cos(_drawAngle * PI_180)/2, sin(_drawAngle * PI_180)/2, 0.38);
			_drawAngle += 36.;
		}

		//corpo
		for(int i = 0; i <= 10; i++) {
			glNormal3f(cos(_drawAngle * PI_180), sin(_drawAngle * PI_180), .38);
			glVertex3f(cos(_drawAngle * PI_180)/2, sin(_drawAngle * PI_180)/2, 0.38);
			glNormal3f(cos(_drawAngle * PI_180), sin(_drawAngle * PI_180), -0.3);
			glVertex3f(cos(_drawAngle * PI_180)/2, sin(_drawAngle * PI_180)/2, -0.3);
			_drawAngle += 36.;
		}

	glEnd();


	//pico da esquerda
	glPushMatrix();
	glTranslatef(-.375, 0, 0);
	glRotatef(180., 0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -0.5);
		for(int i = 0; i <= 5; i++) {
			glNormal3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			glVertex3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			_drawAngle += 72.;
		}
	glEnd();
	glRotatef(180., 0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -0.5);
		for(int i = 0; i <= 5; i++) {
			glNormal3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			glVertex3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			_drawAngle += 72.;
		}
	glEnd();
	glPopMatrix();


	//pico do meio esquerda
	glPushMatrix();
	glTranslatef(-.125, 0, 0);
	glRotatef(180., 0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -0.5);
		for(int i = 0; i <= 5; i++) {
			glNormal3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			glVertex3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			_drawAngle += 72.;
		}
	glEnd();
	glRotatef(180., 0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -0.5);
		for(int i = 0; i <= 5; i++) {
			glNormal3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			glVertex3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			_drawAngle += 72.;
		}
	glEnd();
	glPopMatrix();


	//pico do meio direita
	glPushMatrix();
	glTranslatef(.125, 0, 0);
	glRotatef(180., 0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -0.5);
		for(int i = 0; i <= 5; i++) {
			glNormal3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			glVertex3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			_drawAngle += 72.;
		}
	glEnd();
	glRotatef(180., 0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -0.5);
		for(int i = 0; i <= 5; i++) {
			glNormal3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			glVertex3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			_drawAngle += 72.;
		}
	glEnd();
	glPopMatrix();


	//pico da direita
	glPushMatrix();
	glTranslatef(.375, 0, 0);
	glRotatef(180., 0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -0.5);
		for(int i = 0; i <= 5; i++) {
			glNormal3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			glVertex3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			_drawAngle += 72.;
		}
	glEnd();
	glRotatef(180., 0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -0.5);
		for(int i = 0; i <= 5; i++) {
			glNormal3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			glVertex3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			_drawAngle += 72.;
		}
	glEnd();
	glPopMatrix();


	//pico da frente
	glPushMatrix();
	glTranslatef(0, -.35, 0);
	glRotatef(180., 0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -0.5);
		for(int i = 0; i <= 5; i++) {
			glNormal3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			glVertex3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			_drawAngle += 72.;
		}
	glEnd();
	glRotatef(180., 0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -0.5);
		for(int i = 0; i <= 5; i++) {
			glVertex3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			_drawAngle += 72.;
		}
	glEnd();
	glPopMatrix();


	//pico do meio frente
	glPushMatrix();
	glTranslatef(0, -.125, 0);
	glRotatef(180., 0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -0.5);
		for(int i = 0; i <= 5; i++) {
			glVertex3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			_drawAngle += 72.;
		}
	glEnd();
	glRotatef(180., 0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -0.5);
		for(int i = 0; i <= 5; i++) {
			glNormal3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			glVertex3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			_drawAngle += 72.;
		}
	glEnd();
	glPopMatrix();


	//pico do meio trás
	glPushMatrix();
	glTranslatef(0, .125, 0);
	glRotatef(180., 0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -0.5);
		for(int i = 0; i <= 5; i++) {
			glNormal3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			glVertex3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			_drawAngle += 72.;
		}
	glEnd();
	glRotatef(180., 0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -0.5);
		for(int i = 0; i <= 5; i++) {
			glNormal3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			glVertex3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			_drawAngle += 72.;
		}
	glEnd();
	glPopMatrix();


	//pico de trás
	glPushMatrix();
	glTranslatef(0, .35, 0);
	glRotatef(180., 0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -0.5);
		for(int i = 0; i <= 5; i++) {
			glNormal3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			glVertex3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			_drawAngle += 72.;
		}
	glEnd();
	glRotatef(180., 0, 0, 1);
	glBegin(GL_TRIANGLE_FAN);
		glNormal3f(0, 0, -1);
		glVertex3f(0, 0, -0.5);
		for(int i = 0; i <= 5; i++) {
			glNormal3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			glVertex3f(cos(_drawAngle * PI_180)/8, sin(_drawAngle * PI_180)/8, -0.3);
			_drawAngle += 72.;
		}
	glEnd();
	glPopMatrix();


	//olho esquerdo
	glPushMatrix();
	if(light == 5)
			glMaterialfv(GL_FRONT, GL_AMBIENT, matGhostWhite);
		else
			glMaterialfv(GL_FRONT, GL_AMBIENT, matGhostBlack);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matGhostWhite);
	glTranslatef(-0.2, -0.4, 0.15);
	glutSolidSphere(0.15, 10, 10);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matGhostBlack);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matGhostBlack);
	glTranslatef(0, -0.11, 0.0);
	glutSolidSphere(0.05, 10, 10);
	glPopMatrix();
	
	//olho direito
	glPushMatrix();
	if(light == 5)
			glMaterialfv(GL_FRONT, GL_AMBIENT, matGhostWhite);
		else
			glMaterialfv(GL_FRONT, GL_AMBIENT, matGhostBlack);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matGhostWhite);
	glTranslatef(0.2, -0.4, 0.15);
	glutSolidSphere(0.15, 10, 10);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matGhostBlack);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matGhostBlack);
	glTranslatef(0, -0.11, 0.0);
	glutSolidSphere(0.05, 10, 10);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}


// Movimento
void Ghosts::move(char direction) {
	if(_vulnerable == 1)
		_speed = 0.125 / 2;

	switch(direction) {
		case 'r': _angle = 0;	 _x += _speed; break;
		case 'l': _angle = 180;	 _x -= _speed; break;
		case 'u': _angle = 90;	 _y += _speed; break;
		case 'd': _angle = 270;  _y -= _speed; break;
	}
	glutPostRedisplay();
}