#include <list>
#pragma once
class Cell {
public:
	Cell(int x, int y, Cell ***array);
	~Cell();	
	bool IsAlive(void);
	void calculateNextState(void);
	void setToNextState(void);
	void setState(bool); //TODO debug only
	void collectNeighbours(void);
	void markBorder(void);

private:
	static const int numberOfNeighbours = 8;
	int x;
	int y;
	bool isAlive;
	bool willBeAlive;
	bool isPoisoned;
	bool isNextStateCalculated;
	bool isBorderElement;
	bool areNeighboursCollected;
	int roundsToDeath;
	//std::list<Cell> _neighbours;
	Cell *neighbours[numberOfNeighbours];
	Cell ***array;

	//static void markCellsThatWillBeAlive();
	bool willCellBeAlive(void);
	void poison(void);
	void makeAlive(void);
	int countAliveNeighbours(void);
};

