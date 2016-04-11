#include "Cell.h"
#include "Rules.h"
#include <list>


Cell::Cell() {
	//isPoisoned = false;
	isNextStateCalculated = false;
	isAlive = false;
	willBeAlive = false;
	isBorderElement = false;
	roundsToDeath = Rules::maxRoundsToDeath;
}

Cell::~Cell() {
}

bool Cell::IsAlive(void) {
	return isAlive;
}

void Cell::setState(bool state) {
	isAlive = state;
}

void Cell::markBorder(void) {
	isBorderElement = true;
	isAlive = false;
}

bool Cell::willCellBeAlive(int numberOfAliveNeighbours) {
	if (isBorderElement) {
		return false;
	}
	//if (Rules::areBordersPoisoned && isPoisoned) {
	//	return false;
	//}
	if (Rules::maxRoundsToDeath > 0 && --roundsToDeath == 0) {
		return false;
	}
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

//void Cell::poison(void) {
//	if (areNeighboursCollected) {
//		if (isAlive && !isPoisoned) {
//			isPoisoned = true;
//			//for each (Cell neighbour in getNeighbours()) {
//			for (int i = 0; i < numberOfNeighbours; i++) {
//				neighbours[i]->poison();
//			}
//		}
//	}
//}

void Cell::makeAlive(void) {
	if (!isAlive) {
		isAlive = true;
		roundsToDeath = Rules::maxRoundsToDeath;
	}
}

void Cell::calculateNextState(int numberOfAliveNeighbours) {
	willBeAlive = willCellBeAlive(numberOfAliveNeighbours);
	isNextStateCalculated = true;
}

void Cell::setToNextState(void) {
	if (isNextStateCalculated) {
		if (!isBorderElement) {
			if (isAlive) {
				isAlive = willBeAlive;
			}
			else if(willBeAlive) {
				makeAlive();
			}
		}
		isNextStateCalculated = false;
		willBeAlive = false;
	}
}