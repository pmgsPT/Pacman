#include <stdlib.h>
#include <ctime>
#include <GL/glut.h>
#include <cmath>
#include "Particle.h"
#include <stdio.h>

Particle::Particle(float x,float y, float size){
	_x = x;
	_y = y;
	_z = 0.5;
	_size = size;
	srand(time(NULL));

	_direction = 0;
	_life = 1;
	_fade = .05;
	_acceleration = 0.01*(rand() % 10) -0.01*(rand() % 10);

	_speedX = 0.01*(rand() % 10) -0.01*(rand() % 10);
	_speedY = 0.01*(rand() % 10) -0.01*(rand() % 10);
	_speedZ = 0.01*(rand() % 10) -0.01*(rand() % 10);
	//printf("%f %f", _speedX, _speedY);
	_accelerationX = 0;
	_accelerationY = 0;
	_accelerationZ = -0.0015;
}

void Particle::updateParticle(){

	_speedX = 0.01*(rand() % 10) -0.01*(rand() % 10);
	_speedY = 0.01*(rand() % 10) -0.01*(rand() % 10);
	_speedZ = -0.03*(rand() % 10);
	_speedX += _accelerationX;
	_speedY += _accelerationY;
	_speedZ += _accelerationZ;
	_x += _speedX;
	_y += _speedY;
	_z += _speedZ;
}

void Particle::drawParticle(){
	glPushMatrix();

	glColor4ub(255,rand() % 255,rand() % 200,_life);
	
	glPointSize(2);
	glBegin(GL_POINTS);
	glVertex3f(_x,_y,_z);
	glEnd();

	glPopMatrix();
}