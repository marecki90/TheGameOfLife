#include "Rules.h"

bool Rules::areBordersPoisoned = false;
int Rules::maxRoundsToDeath = 0;
int Rules::zoom = 1;
int Rules::gameSpeed = 1;
bool Rules::numberOfNeighboursToStayCellAlive[9] = { false, false, true, false, false, false, false, false, true };
//bool Rules::numberOfNeighboursToStayCellAlive[9] = { true, true, true, true, true, true, true, true, true };
bool Rules::numberOfNeighboursToMakeCellAlive[9] = { false, false, false, true, false, false, false, false, false };


Rules::Rules() {
}


Rules::~Rules() {
}
