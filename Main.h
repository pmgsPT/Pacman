// Main.h
#include <GL/glut.h>

GLuint texname;
int w, h, ghostCounter;
void drawHUD();

//geral
GLfloat amb_night[4] = {0, 0, 0, 1};

//pacman
GLfloat pac_day[4] = {0, 0, 0, 1};

//labirinto
GLfloat lab_day[4] = {0, 0, .5, 1};
GLfloat peb_day[4] = {1, 1, 1, 1};
GLfloat floor_day[4] = {1, 1, 1, 1};

//fantasmas
GLfloat g1_day[4] = {1, 0.6, 0, 1};
GLfloat g2_day[4] = {0, 1, 1, 1};
GLfloat g3_day[4] = {1, 0, 1, 1};

//luz
GLfloat ambLight[4] = {.2, .2, .2, 0};


//luz 2
GLfloat l2_amb[4]  = {.2, .2, .2, 1};
GLfloat l2_spec[4] = {1, 1, 1, 1};
GLfloat l2_diff[4] = {1, 1, 1, 1};
GLfloat l2_dir[3]  = {0, 0, -1};

//luz 3
GLfloat l3_amb[4]  = {.2, .2, .2, 1};
GLfloat l3_spec[4] = {1, 1, 1, 1};
GLfloat l3_diff[4] = {1, 1, 1, 1};
GLfloat l3_dir[3]  = {0, 0, -1};

//luz 4
GLfloat l4_amb[4]  = {.2, .2, .2, 1};
GLfloat l4_spec[4] = {1, 1, 1, 1};
GLfloat l4_diff[4] = {1, 1, 1, 1};
GLfloat l4_dir[3]  = {0, 0, -1};

//luz 5
GLfloat l5_amb[4]  = {.2, .2, .2, 1};
GLfloat l5_spec[4] = {1, 1, 1, 1};
GLfloat l5_diff[4] = {1, 1, 1, 1};
GLfloat l5_dir[3]  = {0, 0, -1};