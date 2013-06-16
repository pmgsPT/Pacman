// Camera.cpp
#include <GL/glut.h>
#include <math.h>
#include "Camera.h"


Camera::Camera() {
	_cam = 1;
	_full = 0;
}



// Alterar camara
void Camera::changeCam(float w, float h, float x, float y) {
	
	aspect_ratio = ((float)w)/h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	switch(_cam) {
		default:
		case 1:
			if(aspect_ratio >= 1.)
				glOrtho(-18. * aspect_ratio, 18. * aspect_ratio, -11., 11.5, -10, 10);
			else
				glOrtho(-18. / aspect_ratio, 18. / aspect_ratio, -11. / aspect_ratio, 11.5 / aspect_ratio, -10, 10);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(16, -10, 4, 16, -10, 0, 0, 1, 0);
			break;

		case 2:
			gluPerspective(90.0, aspect_ratio, 1, 10);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(x, y - 3, 4, x, y, 0, 0, 1, 0);
			break;

		case 3:
			gluPerspective(90.0, aspect_ratio, 1, 20);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(x, y - 3, 1, x, y, 0, 0, 1, 0);
			break;

		case 4:
			gluPerspective(45.0, aspect_ratio * 1.3, 1, 30);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(x, y, 30, 16, -10, 0, 0, -1, 0);
			break;
	}
}