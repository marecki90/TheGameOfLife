#include "Game.h"
#include "Rules.h"
#include "wtypes.h"
#include "ShellScalingAPI.h"
#include <glut.h>

Game *Game::currentInstance = new Game();

Game::Game() :basicCellSize(0), basicTimeInterval(1), marginFactor(0) {
}

Game::Game(int *argc, char **argv) :basicCellSize(4), basicTimeInterval(50), marginFactor(15) {
	cellSize = basicCellSize * Rules::zoom;
	timeInterval = basicTimeInterval * Rules::gameSpeed;
	getDesktopResolution();
	boardInitialize();
	glutInitialize(argc, argv);
	myGlutInitialize();
	glutTimerFunc(timeInterval, Game::nextStep, 1);
	for (int x = 1; x < boardWidth - 1; x++) {
		for (int y = 1; y < boardHeight - 1; y++) {
			board[x][y]->calculateNextState();
		}
	}
	currentInstance = this;
	//calculateAllCells();
}

Game::~Game() {
}

void Game::getDesktopResolution(void) {
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	screenWidth = desktop.right;
	screenHeight = desktop.bottom;

	visibleBoardWidth = desktop.right / cellSize + 1;
	visibleBoardHeight = desktop.bottom / cellSize + 1;

	boardOffset = visibleBoardWidth * marginFactor / 100;

	boardWidth = visibleBoardWidth + 2 * boardOffset;
	boardHeight = visibleBoardHeight + 2 * boardOffset;
	//HMONITOR hMonitor = MonitorFromWindow(hDesktop, MONITOR_DEFAULTTOPRIMARY);
	//DEVICE_SCALE_FACTOR pScale;
	//if (GetScaleFactorForMonitor(hMonitor, &pScale) == S_OK) {
	//	screenScale = (int)pScale;
	//}
	//else {
	//	screenScale = 100;
	//}
}

void Game::glutInitialize(int *argc, char **argv) {
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//glutInitWindowSize(screenWidth, screenHeight);
	//glutInitWindowPosition(0, 0);
	glutCreateWindow("THE GAME OF LIFE");
	glutDisplayFunc(displayBoard);
	glutFullScreen();
}

void Game::myGlutInitialize(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (float)screenWidth, 0.0, (float)screenHeight);
	glMatrixMode(GL_MODELVIEW);
}

void Game::boardInitialize(void) {
	int counter = 0;
	board = new Cell**[boardWidth];
	for (int x = 0; x < boardWidth; x++) {
		board[x] = new Cell*[boardHeight];
		for (int y = 0; y < boardHeight; y++) {
			board[x][y] = new Cell(x, y, board);
			board[x][y]->setState(true);
			counter++;
			if (x == 0 || x == boardWidth - 1 || y == 0 || y == boardHeight - 1) {
				board[x][y]->markBorder();
			}
		}
	}
	for (int x = 1; x < boardWidth - 1; x++) {
		for (int y = 1; y < boardHeight - 1; y++) {
			board[x][y]->collectNeighbours();
		}
	}
	currentInstance = this;
}

void Game::nextStep(int timerValue) {
	Game *game = Game::currentInstance;
	for (int x = 0; x < game->boardWidth; x++) {
		for (int y = 0; y < game->boardHeight; y++) {
			game->board[x][y]->setToNextState();
		}
	}
	glutPostRedisplay();
	for (int x = 1; x < game->boardWidth - 1; x++) {
		for (int y = 1; y < game->boardHeight - 1; y++) {
			game->board[x][y]->calculateNextState();
		}
	}
	//calculateAllCells();
	glutTimerFunc(game->timeInterval, Game::nextStep, 1);
}

void Game::displayBoard(void) {
	Game *game = Game::currentInstance;
	glClear(GL_COLOR_BUFFER_BIT);
	for (int x = 0; x < game->visibleBoardWidth; x++) {
		for (int y = 0; y < game->visibleBoardHeight; y++) {
			if (game->board[x + game->boardOffset][y + game->boardOffset]->IsAlive()) {
				glBegin(GL_QUADS);
				glVertex2f((float)x * game->cellSize, (float)y * game->cellSize);
				glVertex2f((float)(x + 1) * game->cellSize, (float)y * game->cellSize);
				glVertex2f((float)(x + 1) * game->cellSize, (float)(y + 1) * game->cellSize);
				glVertex2f((float)x * game->cellSize, (float)(y + 1) * game->cellSize);
				glEnd();
			}
		}
	}
	glFlush();
}

void Game::calculateAllCells(void) {
	Game *game = Game::currentInstance;
	int x, y;
	// chceck cells without borders
	for (x = 1; x < game->boardWidth - 1; x++) {
		for (y = 1; y < game->boardHeight - 1; y++) {
			game->board[x][y]->calculateNextState();
		}
	}
	for (int x = 0; x < game->boardWidth; x++) {
		for (int y = 0; y < game->boardHeight; y++) {
			game->board[x][y]->setToNextState();
		}
	}
}
