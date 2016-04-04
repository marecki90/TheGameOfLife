#include "Cell.h"

#pragma once
class Game {

#define forBoardWithoutBorder(x, y) for (int x = 1; x < boardWidth - 1; x++) for (int y = 1; y < boardHeight - 1; y++)

public:
	Game(int *argc, char **argv);
	~Game();

private:
	const int basicCellSize;
	const int basicTimeInterval;
	const int marginFactor;
	static Game *currentInstance;
	int cellSize;
	int timeInterval;
	Cell ***board;
	int screenHeight;
	int screenWidth;
	int boardHeight;
	int boardWidth;
	int visibleBoardHeight;
	int visibleBoardWidth;
	int boardOffset;
	int numberOfAliveCells;

	void getDesktopResolution(void);
	void glutInitialize(int *argc, char **argv);
	void myGlutInitialize(void);
	void boardInitialize(void);
	int countAliveNeighbours(int x, int y);
	void calculateNextBoardState(void);
	void setBoardToNextState(void);
	void renderCell(int x, int y);
	static void nextStep(int);
	static void displayBoard(void);
};