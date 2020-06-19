#pragma once
#include"GameObject.h"
typedef std::vector<LPGAMEOBJECT> cellObjects;
#define CELL_SIZE  256
class Grid
{
	int map_width;
	int map_height;
	int grid_col;
	int grid_row;
	int cell_size= CELL_SIZE;

	std::vector<std::vector<cellObjects>> grid;
	std::vector<LPGAMEOBJECT> alwaysUpdateList;
public:
	Grid( int mapWidth,  int mapHeight);
	// them object vao grid
	void Add(LPGAMEOBJECT object,bool isAlwayUpdateObject=false);
	void Update(LPGAMEOBJECT object);
	void GetListobjectFromGrid(vector<LPGAMEOBJECT>& listobjects);

};

