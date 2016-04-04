#pragma once
class Rules {
public:
	Rules();
	~Rules();

	static bool areBordersPoisoned;
	static int maxRoundsToDeath;
	static int zoom;
	static int gameSpeed;
	static bool numberOfNeighboursToStayCellAlive[9];
	static bool numberOfNeighboursToMakeCellAlive[9];
	//static bool numberOfNeighboursToKillCell[9];
};

