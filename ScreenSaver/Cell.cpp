#include "Cell.h"
#include "Rules.h"
#include <list>


Cell::Cell(int x, int y, Cell ***array) {
	this->x = x;
	this->y = y;
	this->array = array;
	isPoisoned = false;
	isNextStateCalculated = false;
	isAlive = false;
	willBeAlive = false;
	isBorderElement = false;
	areNeighboursCollected = false;
	roundsToDeath = 0;
}

Cell::~Cell() {
}

bool Cell::IsAlive(void)
{
	return isAlive;
}

void Cell::setState(bool state)
{
	isAlive = state;
}

void Cell::collectNeighbours(void) {
	if (!isBorderElement) {
		int index = 0;
		for (int i = -1; i <= 1; i++) for (int j = -1; j <= 1; j++) {
			if (i != 0 || j != 0) {
				neighbours[index] = array[x + i][y + j];
				index++;
			}
		}
	}
	areNeighboursCollected = true;
}

void Cell::markBorder(void) {
	isBorderElement = true;
	isAlive = false;
}

bool Cell::willCellBeAlive(void)
{
	if (isBorderElement) {
		return false;
	}
	if (Rules::areBordersPoisoned && isPoisoned) {
		return false;
	}
	if (Rules::maxRoundsToDeath > 0 && roundsToDeath == 1) {
		return false;
	}
	int numberOfAliveNeighbours;
	numberOfAliveNeighbours = countAliveNeighbours();
	if (Rules::numberOfNeighboursToMakeCellAlive[numberOfAliveNeighbours]) {
		return true;
	}
	if (isAlive && Rules::numberOfNeighboursToStayCellAlive[numberOfAliveNeighbours]) {
		return true;
	}
	else {
		return false;
	}
}

void Cell::poison(void) {
	if (areNeighboursCollected) {
		if (isAlive && !isPoisoned) {
			isPoisoned = true;
			//for each (Cell neighbour in getNeighbours()) {
			for (int i = 0; i < numberOfNeighbours; i++) {
				neighbours[i]->poison();
			}
		}
	}
}

void Cell::makeAlive(void) {
	if (!isAlive) {
		isAlive = true;
		roundsToDeath = Rules::maxRoundsToDeath;
	}
}

void Cell::calculateNextState(void) {
	willBeAlive = willCellBeAlive();
	isNextStateCalculated = true;
}

void Cell::setToNextState(void) {
	if (isNextStateCalculated) {
		isAlive = willBeAlive;
		isNextStateCalculated = false;
		willBeAlive = false;
	}
}

int Cell::countAliveNeighbours(void) {
	int counter = 0;
	if (areNeighboursCollected) {
		//for each (Cell neighbour in neighbours()) {
		for (int i = 0; i < numberOfNeighbours; i++) {
			if (neighbours[i]->isAlive) {
				counter++;
			}
		}
	}
	return counter;
}
