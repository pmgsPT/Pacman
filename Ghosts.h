// Ghosts.h
#include <GL/glut.h>


class Ghosts {

private:


public:
	float _speed;
	int _angle;
	float _x;
	float _y;
	float matGhost[4];
	int _vulnerable;
	char _direction;

	Ghosts(float, float);

	void drawGhosts(float, float, GLfloat[], GLfloat[], int);

	void move(char);
};