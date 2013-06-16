#include <GL/glut.h>

/* Tem as coordenadas da particula, que no inicio são as do pacman,
e  aceleraçao e desaceleraçao para subir e descer de forma realista quando o pacman explode*/
class Particle {

public:
	float _x;
	float _y;
	float _z;
	float color[3];
	float _acceleration;
	float _accelerationX, _accelerationY, _accelerationZ;
	float _deceleration;
	float _size;
	float _speedX;
	float _speedY;
	float _speedZ;
	float _direction;
	float _life, _fade;

	Particle(float,float,float); /*x,y,size*/

	//void createParticle(void);
	void updateParticle(void);
	void drawParticle(void);
};
