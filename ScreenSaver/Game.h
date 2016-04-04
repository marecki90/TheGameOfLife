#include "Cell.h"

#pragma once
class Game {
public:
	Game(int *argc, char **argv);
	~Game();

private:
	Game();
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

	void getDesktopResolution(void);
	void glutInitialize(int *argc, char **argv);
	void myGlutInitialize(void);
	void boardInitialize(void);
	static void nextStep(int);
	static void displayBoard(void);
	static void calculateAllCells(void);
};