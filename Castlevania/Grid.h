#pragma once
#include"GameObject.h"
#include"Map.h"
typedef std::vector<LPGAMEOBJECT> cellObjects;
#define CELL_SIZE  256
class PlayScene;
class Grid
{
	int id;
	int map_width;
	int map_height;
	int grid_col;
	int grid_row;
	int cell_size= CELL_SIZE;

	std::vector<LPGAMEOBJECT> allObjects;

	//extend map to hold object property like x,y,col,row,name
	std::map<std::string, ObjectLayer*> objectLayers;
	std::vector<std::vector<cellObjects>> grid;
	std::vector<LPGAMEOBJECT> alwaysUpdateList;
	void BuildGrid(const std::string filePath);
	
	PlayScene* pScene;
	void Add(LPGAMEOBJECT object, bool isAlwayUpdateObject = false);

public:
	Grid(PlayScene* pScene) { this->pScene = pScene; };
	void AddAfterUpdate(LPGAMEOBJECT object, bool isAlwayUpdateObject = false);
	// them object vao grid
	void LoadGrid(const std::string FilePath);
	void Update(LPGAMEOBJECT object);
	void GetListobjectFromGrid(vector<LPGAMEOBJECT>& listobjects);

};

