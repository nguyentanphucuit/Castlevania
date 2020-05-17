#include "Layer.h"
#include"define.h"
#include"Sprites.h"
void Layer::Render(D3DXVECTOR2 cam)
{
	if (!isVisible) // nếu cờ này false thì k cần vẽ
	{
		return;
	}

	int beginCol = (int)(((int)cam.x) / tileHeight);
	if (beginCol < 0)
	{
		beginCol = 0;
	}

	int endCol = ((int)cam.x + SCREEN_WIDTH * 2) / tileHeight; 
	
	if (endCol >= this->width)
		endCol = this->width;
	int beginRow = (int)cam.y / tileHeight;
	int endRow = ((int)cam.y + SCREEN_HEIGHT*2) / tileHeight-1;

	for (int i = beginRow; i < height; i++)
	{

		for (int j = beginCol; j < endCol; j++)
		{
			int id = this->tileMatrix[i][j];
			if (id)
			{
				CSprites::GetInstance()->Get("map_" + std::to_string(mapID) + std::to_string(id))->Draw(j * 32, i * 32);
			}

		}
	}


}
