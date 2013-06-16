// Pacman.h
#include <GL/glut.h>


class Pacman {



public:
	bool _animate;
	int _angle;
	float _x;
	float _y;
	float _radius;
	int _pause;
	int _ninja;
	char _direction;
	char _directionWanted;
	int _life;
	float _speed;
	Pacman(void);

	void drawPacman(GLfloat[], int);

	void move(char);
};