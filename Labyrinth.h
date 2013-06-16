// Labyrinth.h
#include <GL/glut.h>


class Labyrinth {
	
public:
	int _light;
	int _pebblesCatched;
	int _gamePebbles;
	GLuint texname;

	int gamePebbles[20][33];

	Labyrinth(void);

	void drawWalls(GLfloat[], GLfloat[]);

	void drawPebbles(GLfloat[]);

	float colisionWalls(int, int, char);

	float openWay(int, int, char, char);

	bool hitWall(float,float,char);

	void changeLight(GLfloat[], GLfloat[]);

	void loadTexture(const char *);
};


