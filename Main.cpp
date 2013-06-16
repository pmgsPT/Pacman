// Main.cpp
#include <stdlib.h>
#include <ctime>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Pacman.h"
#include "Labyrinth.h"
#include "Ghosts.h"
#include "Camera.h"
#include "Main.h"
#include "Particle.h"


const double PI = 4.0*atan(1.0);
using namespace std;

Pacman* pacman = new Pacman();
Labyrinth* labyrinth = new Labyrinth();
Camera* camera = new Camera();
Ghosts* ghost1 = new Ghosts(15., -9.);
Ghosts* ghost2 = new Ghosts(17., -9.);
Ghosts* ghost3 = new Ghosts(16., -10.);
vector<Particle> particles(2000, Particle(pacman->_x, pacman->_y, 1));


void reshape(GLsizei width, GLsizei height) { w = width; h = height; }

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 27 : exit(0); break;
		case 'a':
		case 'A': pacman->_directionWanted = 'l'; break;
		case 'd':
		case 'D': pacman->_directionWanted = 'r'; break;
		case 'w':
		case 'W': pacman->_directionWanted = 'u'; break;
		case 's':
		case 'S': pacman->_directionWanted = 'd'; break;
		case 'f':
		case 'F':
			camera->_full =! camera->_full;
			if(camera->_full)
				glutFullScreen();
			else {
				glutReshapeWindow(w/2, h);
				glutPositionWindow(300, 40);
			}
			break;
		case '1':
		case '2':
		case '3':
		case '4': { int cam = key - '0'; camera->_cam = cam;} break;
		case '5':
		case '6': { int light = key - '0'; labyrinth->_light = light;} break;
	}
}


void keyboardSpecial(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_LEFT: pacman->_directionWanted = 'l';	break;
		case GLUT_KEY_RIGHT: pacman->_directionWanted = 'r'; break;
		case GLUT_KEY_UP: pacman->_directionWanted = 'u'; break;
		case GLUT_KEY_DOWN: pacman->_directionWanted = 'd'; break;
	}
}


void vulnerable(int value) {
	pacman->_ninja = 0;
	ghost1->_vulnerable = 0;
	ghost2->_vulnerable = 0;
	ghost3->_vulnerable = 0;
}


void alternateMaterials() {
	if(labyrinth->_light == 5) {
		pacman->drawPacman(pac_day, 5);
		labyrinth->drawWalls(lab_day, floor_day);
		labyrinth->drawPebbles(peb_day);
		ghost1->drawGhosts(pacman->_x, pacman->_y, g1_day, g1_day, 5);
		ghost2->drawGhosts(pacman->_x, pacman->_y, g2_day, g2_day, 5);
		ghost3->drawGhosts(pacman->_x, pacman->_y, g3_day, g3_day, 5);
	}
	else {
		pacman->drawPacman(amb_night, 6);
		labyrinth->drawWalls(amb_night,amb_night);
		labyrinth->drawPebbles(amb_night);
		ghost1->drawGhosts(pacman->_x, pacman->_y, g1_day, amb_night, 6);
		ghost2->drawGhosts(pacman->_x, pacman->_y, g2_day, amb_night, 6);
		ghost3->drawGhosts(pacman->_x, pacman->_y, g3_day, amb_night, 6);
	}
}


void alternateSpotlight() {
	switch(pacman->_angle) {
		case 0: {
			GLfloat l1_pos[4] = {pacman->_x, pacman->_y, 1, 1};
			GLfloat l1_dir[3] = {1, 0, -1};
			labyrinth->changeLight(l1_pos, l1_dir);
			break;
		}

		case 90: {
			GLfloat l1_pos[4] = {pacman->_x, pacman->_y, 1, 1};
			GLfloat l1_dir[3] = {0, 1, -1};
			labyrinth->changeLight(l1_pos, l1_dir);
			break;
		}

		case 180: {
			GLfloat l1_pos[4] = {pacman->_x, pacman->_y, 1, 1};
			GLfloat l1_dir[3] = {-1, 0, -1};
			labyrinth->changeLight(l1_pos, l1_dir);
			break;				  
		}

		case 270: {
			GLfloat l1_pos[4] = {pacman->_x, pacman->_y, 1, 1};
			GLfloat l1_dir[3] = {0, -1, -1};
			labyrinth->changeLight(l1_pos, l1_dir);
			break;
		}
	}
}


void pacmanChecks() {
	
	if(pacman->_x == labyrinth->openWay(pacman->_x, pacman->_y, pacman->_direction, pacman->_directionWanted)) /* OPTIMIZAR */
		pacman->_direction = pacman->_directionWanted;
	
	if(pacman->_x == labyrinth->openWay(pacman->_x, pacman->_y,'l', pacman->_directionWanted))
		pacman->_direction = pacman->_directionWanted;

	if(pacman->_y == labyrinth->openWay(pacman->_x, pacman->_y,'u', pacman->_directionWanted))
		pacman->_direction = pacman->_directionWanted;

	if(pacman->_y == labyrinth->openWay(pacman->_x, pacman->_y,'d', pacman->_directionWanted))
		pacman->_direction = pacman->_directionWanted;

	switch(pacman->_direction) {
		case 'r':
			if(pacman->_x >= labyrinth->colisionWalls(pacman->_x, pacman->_y, 'r'))
				pacman->_animate = false;
			else pacman->move('r');
			break;

		case 'l':
			if(pacman->_x <= labyrinth->colisionWalls(pacman->_x, pacman->_y, 'l'))
				pacman->_animate = false;
			else pacman->move('l');
			break;

		case 'u':
			if(pacman->_y >= labyrinth->colisionWalls(pacman->_x, pacman->_y, 'u'))
				pacman->_animate = false;
			else pacman->move('u');
			break;

		case 'd':
			if(pacman->_y <= labyrinth->colisionWalls(pacman->_x, pacman->_y, 'd'))
				pacman->_animate = false;
			else pacman->move('d');
			break;
	}
}


void pacmanEat() {

	if(labyrinth->gamePebbles[(int) (- pacman->_y)][(int) (pacman->_x)] == 1) {
		labyrinth->gamePebbles[(int) (- pacman->_y)][(int) (pacman->_x)] = 0;
		labyrinth->_pebblesCatched++;
	}

	if(labyrinth->gamePebbles[(int) (- pacman->_y)][(int) (pacman->_x)] == 2) {
		labyrinth->gamePebbles[(int) (- pacman->_y)][(int) (pacman->_x)] = 0;
		labyrinth->_pebblesCatched++;
		labyrinth->_pebblesCatched++; //para contar 2 vezes e dar 10 pontos
		pacman->_ninja = 1;
		ghost1->_vulnerable = 1;
		ghost2->_vulnerable = 1;
		ghost3->_vulnerable = 1;
		glutTimerFunc(10000, vulnerable, 0);
	}

	if((labyrinth->_gamePebbles - labyrinth->_pebblesCatched) == 0)
		printf("WIN");
}


void randomDirection(Ghosts* ghost) {
	int randomNumber = rand() % 4;

	switch(randomNumber) {
		case 0: ghost->_direction = 'r'; break;
		case 1: ghost->_direction = 'l'; break;
		case 2: ghost->_direction = 'u'; break;
		case 3: ghost->_direction = 'd'; break;
	}
}


void keepMoving(Ghosts* ghost, char direction) {
	switch(direction) {
		case 'r': if(ghost->_x >= labyrinth->colisionWalls(ghost->_x, ghost->_y,'r')) {}
				  else ghost->move('r'); 
				  break;
		case 'l': if(ghost->_x <= labyrinth->colisionWalls(ghost->_x, ghost->_y,'l')) {} 
				  else ghost->move('l'); 
				  break;
		case 'u': if(ghost->_y >= labyrinth->colisionWalls(ghost->_x, ghost->_y,'u')) {} 
				  else ghost->move('u'); 
				  break;
		case 'd': if(ghost->_y <= labyrinth->colisionWalls(ghost->_x, ghost->_y,'d')) {} 
				  else ghost->move('d'); 
				  break;
		
	}
}


void checkPac(Ghosts* ghost) {
	float x = pacman->_x - ghost->_x;
	float y = pacman->_y - ghost->_y;

	if(ghost->_vulnerable == 1){
		if(fabs(x)  > fabs(y) ){
			if( x > 0)
				ghost->_direction = 'l';
			else if(x < 0.)
				ghost->_direction = 'r';
		} else{
			if( y > 0.)
				ghost->_direction = 'd';
			else if(y < 0.)
				ghost->_direction = 'u';
		}
 } else {
		if(fabs(x ) > fabs(y)){
			if( x < 0.)
				ghost->_direction = 'l';
			else if(x > 0.)
				ghost->_direction = 'r';
		} else{
			if( y < 0.)
				ghost->_direction = 'u';
			else if(y > 0.)
				ghost->_direction = 'd';
		}}
}


void moveGhost(Ghosts* ghost){

	if((ghost->_x == 16) && (ghost->_y == -8))
		ghost->_direction = 'u';

	switch(ghost->_direction) {

	case 'l':
		if(ghost->_x == labyrinth->openWay(ghost->_x,ghost->_y,ghost->_direction, 'd')){
			if((rand()%4) > 0){ ghost->_direction='d';  break;} else {randomDirection(ghost); break;}}

			else{
				if(ghost->_x == labyrinth->openWay(ghost->_x,ghost->_y,ghost->_direction, 'u')){
					if((rand()%4) > 0){ ghost->_direction='u';  break;} else {randomDirection(ghost); break;}}
					
				else{
					if(!labyrinth->hitWall(ghost->_x,ghost->_y,ghost->_direction)){break;} break;}
					
			}break;

	case 'r':
		if(ghost->_x == labyrinth->openWay(ghost->_x,ghost->_y,ghost->_direction, 'u')){
			if((rand()%4) > 0){ ghost->_direction='u';  break;} else {randomDirection(ghost); break;}}

			else{
				if(ghost->_x == labyrinth->openWay(ghost->_x,ghost->_y,ghost->_direction, 'd')){
					if((rand()%4) > 0){ ghost->_direction='d';  break;} else {randomDirection(ghost); break;}}
					
				else{
					if(!labyrinth->hitWall(ghost->_x,ghost->_y,ghost->_direction)){break;} break;}
					
			}break;
				
			
		
	case 'u':
		if(ghost->_y == labyrinth->openWay(ghost->_x,ghost->_y,ghost->_direction, 'r')){
			if((rand()%4) > 0){ ghost->_direction='r';  break;}else{ randomDirection(ghost); break;}}

			else{
				if(ghost->_y == labyrinth->openWay(ghost->_x,ghost->_y,ghost->_direction, 'l')){
					if((rand()%4) > 0){ ghost->_direction='l';  break;}else {randomDirection(ghost); break;}}
					
					else{
						if(labyrinth->hitWall(ghost->_x,ghost->_y,ghost->_direction)){ break;} break;}
					
					}break;

	case 'd':
		if(ghost->_y == labyrinth->openWay(ghost->_x,ghost->_y,ghost->_direction, 'l')){
			if((rand()%4) > 0){ ghost->_direction='l';  break;}else{ randomDirection(ghost); break;}}

			else{
				if(ghost->_y == labyrinth->openWay(ghost->_x,ghost->_y,ghost->_direction, 'r')){
					if((rand()%4) > 0){ ghost->_direction='r';  break;}else {randomDirection(ghost); break;}}
					
					else{
						if(labyrinth->hitWall(ghost->_x,ghost->_y,ghost->_direction)){ break;} break;}
					
					}break;
	}
	keepMoving(ghost,ghost->_direction);
}


void drawHUD() {
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0f, 1.0f, 1.0f);
	glScalef(0.2, 0.15, 1);

	char buffer1[50], buffer2[50];
	int lives, score;

	lives = sprintf_s(buffer1, "LIVES: %d", pacman->_life);
	score = sprintf_s(buffer2, "SCORE: %d", (labyrinth->_pebblesCatched)*5);
	
	switch(camera->_cam){
	case 1:	glTranslatef(130, 100, 0);
			for(int i = 0 ; i <= lives ; i++) glutStrokeCharacter(GLUT_STROKE_ROMAN, buffer1[i]);
			glTranslatef(1400, 0, 0);
			for(int j = 0 ; j <= score; j++)  glutStrokeCharacter(GLUT_STROKE_ROMAN, buffer2[j]);
			break;
	case 2:
	case 3: glTranslatef(130, 3800, 0);
			for(int i = 0 ; i <= lives ; i++) glutStrokeCharacter(GLUT_STROKE_ROMAN, buffer1[i]);
			glTranslatef(1350, 0, 0);
			for(int j = 0 ; j <= score; j++)  glutStrokeCharacter(GLUT_STROKE_ROMAN, buffer2[j]);
			break;


	}
	glPopMatrix();
}


void reinit(int value) {
	pacman->_x = 16;
	pacman->_y = -12;
}


void pacmanExplode(int value){
	vector<Particle> particles(2000, Particle(pacman->_x, pacman->_y, 1));
	for(int i = 0 ; i < particles.size() ; i++) {
		particles[i].updateParticle();
		particles[i].drawParticle();
	}
}

void collisionPacmanGhost(Ghosts* ghost){
	if(fabs(ghost->_x - pacman->_x) <= 1 && (fabs(ghost->_y - pacman->_y) <= 1)){
		if(ghost->_vulnerable == 0){
			if(pacman->_life > 0){ 
				pacman->_life--;
				pacman->_speed = 0;
				pacmanExplode(5000);
				
			}	
			else printf("GAME OVER");
		}
		else { 
			ghost->_x = 15;
			ghost->_y = -9;
			ghost->_vulnerable = 0;
		}
	}
}

void display() {
	
	ghostCounter = 0;

	glViewport(0, 0, w, h);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	camera->changeCam(w, h, pacman->_x, pacman->_y);

	glEnable(GL_DEPTH_TEST);

	alternateSpotlight();

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	alternateMaterials();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	
	pacmanChecks();
	pacmanEat();
	srand(time(NULL));


	collisionPacmanGhost(ghost1);
	collisionPacmanGhost(ghost2);
	collisionPacmanGhost(ghost3);

	moveGhost(ghost1);
	moveGhost(ghost2);
	moveGhost(ghost3);

	
	for(int i = 0 ; i < particles.size() ; i++) {
		particles[i].updateParticle();
		particles[i].drawParticle();
	}

	drawHUD();
	glutSwapBuffers();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0); 
	glutCreateWindow("PACSIR 3D");
	labyrinth->loadTexture("tijolos.bmp");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	ghost1->_direction = 'r';
	ghost2->_direction = 'l';
	ghost3->_direction = 'u';
	ghost1->_x = ghost1->_x +1;
	ghost1->_y = ghost1->_y +2;
	ghost2->_x = ghost2->_x -1;
	ghost2->_y = ghost2->_y +2;
	ghost3->_y += 2;
	glutMainLoop();
}

