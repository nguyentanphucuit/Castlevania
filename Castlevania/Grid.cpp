#include "Grid.h"
#include"debug.h"
#include"Game.h"
#include"Weapon.h"
#include"Item.h"
#include"Effect.h"
#include"Phantom.h"
#include"Enemy.h"
#include "Torch.h"
Grid::Grid(int mapWidth, int mapHeight) :
	map_width(mapWidth*32),
	map_height(mapHeight * 32 + 80)// + 80: la cai hub
{
	this->cell_size = CELL_SIZE;
	this->grid_col = ceil((float)this->map_width/ this->cell_size);
	this->grid_row = ceil((float)this->map_height / this->cell_size);
	// clear grid

	this->grid.resize(grid_row);

	for (int i = 0; i < grid_row; i++)
		grid[i].resize(grid_col);

	for (size_t i = 0; i < grid_row; i++)
	{
		for (size_t j = 0; j < grid_col; j++)
		{
			this->grid[i][j].clear();
		}
	}





}

void Grid::Add(LPGAMEOBJECT object, bool isAlwayUpdateObject)
{
	float x_, y_;
	object->GetPosition(x_, y_);
	//tính vị trí của object
	int cellX = (int)(x_ / this->cell_size);
	int cellY = (int)(y_ / this->cell_size);
	if (cellX > grid_col)//safe 
	{
		return;
	}
	if (cellY > grid_row - 1)
	{
		return;
	}
	object->SetCellIndex(cellX, cellY);
	if (!isAlwayUpdateObject)
	{
		this->grid[cellY][cellX].push_back(object);
	}
	else
	{
		alwaysUpdateList.push_back(object);
	}
	

	/*if (dynamic_cast<Candle*> (object)
		|| dynamic_cast<Torch*> (object)
		|| dynamic_cast<CBrick*> (object)
		|| dynamic_cast<BossZone*> (object))
	{
		this->statisObject.push_back(object);
	}*/
}

 void Grid::Update(LPGAMEOBJECT object)
{
	float cx_, cy_;

	D3DXVECTOR2 cam = CGame::GetInstance()->GetCamera();

	cx_ = cam.x;
	cy_ = cam.y;

	float x, y;
	object->GetPosition(x, y);


	float l, t, r, b;
	object->GetBoundingBox(l, t, r, b);


	if (object->AABB(l, t, r, b, cx_, cy_, cx_ + SCREENSIZE::WIDTH, cy_ + SCREENSIZE::HEIGHT))
	{
		object->SetActive();
	}
	else
	{
		if (object->CheckActive()) {
			if (dynamic_cast<Item*>(object)
				|| dynamic_cast<Enemy*>(object)
				|| dynamic_cast<Weapon*>(object)
				)
			{
				if (!dynamic_cast<Phantom*>(object))
				{
					object->isDestroy=true;
				}

			}

		}
	}

	CellIndex oldCell = object->GetCellIndex();

	// tìm vị trí cũ của cell chứa object 

	// xem object h đang ở cell nào

	int cellX = (int)(x / this->cell_size);
	int cellY = (int)(y / this->cell_size);


	if (true)
	{
		if (object->IsDestroy())
		{

			// loại bỏ cell cũ
			for (vector<LPGAMEOBJECT>::iterator it = grid[oldCell.y][oldCell.x].begin(); it != grid[oldCell.y][oldCell.x].end(); ) {
				if ((*it) == object) {
					it = grid[oldCell.y][oldCell.x].erase(it);
				}
				else ++it;
			}
			// xóa luôn
			
			return;
		}
	}

	// nếu k ra khỏi cell 
	if (oldCell.x == cellX && oldCell.y == cellY)
	{
		return;
	}
	if (oldCell.x != -1 && oldCell.y != -1) // loại bỏ cell cũ
	{
		for (vector<LPGAMEOBJECT>::iterator it = grid[oldCell.y][oldCell.x].begin(); it != grid[oldCell.y][oldCell.x].end(); ) {
			if ((*it) == object) {
				it = grid[oldCell.y][oldCell.x].erase(it);
			}
			else ++it;
		}

	}

	//thêm lại vào cell mới
	Add(object);
}

void Grid::GetListobjectFromGrid(vector<LPGAMEOBJECT>& listobjects)
{
	// dùng để sắp xếp lại thứ tự các loại object
	vector<LPGAMEOBJECT> enemiesobject;
	vector<LPGAMEOBJECT> itemobject;
	vector<LPGAMEOBJECT> subWeaponobject;
	vector<LPGAMEOBJECT> effectobject;
	enemiesobject.clear();
	itemobject.clear();
	subWeaponobject.clear();
	effectobject.clear();




	float camx, camy;
	D3DXVECTOR2 cam= CGame::GetInstance()->GetCamera();
	camx = cam.x;
	camy = cam.y;
	int startCol = floor(camx / this->cell_size);
	startCol = startCol > 0 ? startCol + -1 : 0;
	int endCol = floor((camx + SCREENSIZE::WIDTH) / this->cell_size);
	endCol = endCol > grid_col ? grid_col : endCol + 1;
	for (int i = 0; i < this->grid_row; i++)
	{
		for (int j = startCol; j < endCol; j++)
		{
			for (size_t k = 0; k < this->grid[i][j].size(); k++)
			{
				LPGAMEOBJECT obj = this->grid[i][j].at(k);
				if (!obj->IsDestroy())
				{
					if (dynamic_cast<Enemy*>(obj))
					{

						enemiesobject.push_back(obj);
					}
					else if (dynamic_cast<Item*>(obj))
					{
						itemobject.push_back(obj);
					}
					else if (dynamic_cast<Weapon*>(obj))
					{
						subWeaponobject.push_back(obj);

					}
					else if (dynamic_cast<Effect*>(obj))
					{
						effectobject.push_back(obj);
					}
					else
					{
						listobjects.push_back(obj);
					}
				}
				else
				{
					//	DebugOut(L" LOSING OBJECT \n");
				}
			}


			// chi render nhung cell co object


		}
	}



	// lấy theo thứ tự
	listobjects.insert(listobjects.end(), alwaysUpdateList.begin(), alwaysUpdateList.end());
	listobjects.insert(listobjects.end(), itemobject.begin(), itemobject.end());
	listobjects.insert(listobjects.end(), enemiesobject.begin(), enemiesobject.end());
	listobjects.insert(listobjects.end(), subWeaponobject.begin(), subWeaponobject.end());
	listobjects.insert(listobjects.end(), effectobject.begin(), effectobject.end());

}
