#include <glut.h>
#include <stdlib.h>
#include "Game.h"



void main(int argc, char **argv) {
	Game *game = new Game(&argc, argv);
	glutMainLoop();
}