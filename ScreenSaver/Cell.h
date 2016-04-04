#include <list>
#pragma once
class Cell {
public:
	Cell();
	~Cell();	
	bool IsAlive(void);
	void calculateNextState(int numberOfAliveNeighbours);
	void setToNextState(void);
	void setState(bool); //TODO debug only
	void markBorder(void);

private:
	bool isAlive;
	bool willBeAlive;
	bool isPoisoned;
	bool isNextStateCalculated;
	bool isBorderElement;
	int roundsToDeath;


	bool willCellBeAlive(int numberOfAliveNeighbours);
	//void poison(void);
	void makeAlive(void);
};

