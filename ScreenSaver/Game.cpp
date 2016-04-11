#include "Game.h"
#include "Rules.h"
#include "wtypes.h"
//#include "ShellScalingAPI.h"
#include <glut.h>

Game *Game::currentInstance = NULL;

Game::Game(int *argc, char **argv) :basicCellSize(3), basicTimeInterval(20), marginFactor(15) {
	cellSize = basicCellSize * Rules::zoom;
	timeInterval = basicTimeInterval * Rules::gameSpeed;
	getDesktopResolution();
	boardInitialize();
	glutInitialize(argc, argv);
	myGlutInitialize();
	glutTimerFunc(timeInterval, Game::nextStep, 1);
}

Game::~Game() {
	for (int x = 0; x < boardWidth; x++) {
		for (int y = 0; y < boardHeight; y++) {
			//board[x][y]->~Cell();
			delete board[x][y];
		}
		delete[] board[x];
	}
	delete [] board;
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
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (float)screenWidth, 0.0, (float)screenHeight);
	glMatrixMode(GL_MODELVIEW);
}

void Game::boardInitialize(void) {
	numberOfAliveCells = 0;
	board = new Cell**[boardWidth];
	for (int x = 0; x < boardWidth; x++) {
		board[x] = new Cell*[boardHeight];
		for (int y = 0; y < boardHeight; y++) {
			board[x][y] = new Cell();
			board[x][y]->setState(true);
			numberOfAliveCells++;
			if (x == 0 || x == boardWidth - 1 || y == 0 || y == boardHeight - 1) {
				board[x][y]->markBorder();
			}
		}
	}
	calculateNextBoardState();
	currentInstance = this;
}

int Game::countAliveNeighbours(int x, int y) {
	int numberOfAliveNeighbours = 0;
	for (int i = -1; i <= 1; i++) for (int j = -1; j <= 1; j++) {
		if (i != 0 || j != 0) {
			if (board[x + i][y + j]->IsAlive()) {
				numberOfAliveNeighbours++;
			}
		}
	}
	return numberOfAliveNeighbours;
}

void Game::calculateNextBoardState(void) {
	loopThroughBoardWithoutBorder(x, y) {
		board[x][y]->calculateNextState(countAliveNeighbours(x, y));
	}
}

void Game::setBoardToNextState(void) {
	loopThroughBoardWithoutBorder(x, y) {
		board[x][y]->setToNextState();
	}
}

void Game::renderCell(int x, int y) {
	glBegin(GL_QUADS); {
		glVertex2i(x * cellSize, y * cellSize);
		glVertex2i((x + 1) * cellSize, y * cellSize);
		glVertex2i((x + 1) * cellSize, (y + 1) * cellSize);
		glVertex2i(x * cellSize, (y + 1) * cellSize);
	}
	glEnd();
}

void Game::nextStep(int timerValue) {
	Game *game = Game::currentInstance;
	game->setBoardToNextState();
	glutPostRedisplay();
	game->calculateNextBoardState();
	glutTimerFunc(game->timeInterval, Game::nextStep, 1);
}

void Game::displayBoard(void) {
	Game *game = Game::currentInstance;
	int cellSize = game->cellSize;
	glClear(GL_COLOR_BUFFER_BIT);
	for (int x = 0; x < game->visibleBoardWidth; x++) {
		for (int y = 0; y < game->visibleBoardHeight; y++) {
			if (game->board[x + game->boardOffset][y + game->boardOffset]->IsAlive()) {
				game->renderCell(x, y);
			}
		}
	}
	glFlush();
}