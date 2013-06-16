// Camera.h
#include <GL/glut.h>


class Camera {

public:
	float aspect_ratio;
	int _cam;
	int _full;

	Camera(void);

	void changeCam(float, float, float, float);

};