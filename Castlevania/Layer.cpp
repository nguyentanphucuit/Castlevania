#include "Layer.h"
#include"define.h"
#include"Sprites.h"
void Layer::Render(D3DXVECTOR2 cam, RECT rect)
{
	if (!isVisible) // nếu cờ này false thì k cần vẽ
	{

		return;
	}

	int beginCol = int(cam.x) / tileHeight;
	if (beginCol < 0)
	{
		beginCol = 0;
	}

	int endCol = ((int)cam.x + SCREENSIZE::WIDTH ) / tileHeight+1; 
	
	if (endCol >= this->width)
		endCol = this->width;
	int beginRow = (int)cam.y / tileHeight +1;
	int endRow = ((int)cam.y+(rect.bottom-rect.top)) / tileHeight;

	for (int i = beginRow; i <= endRow; i++)
	{

		for (int j = beginCol; j < endCol; j++)
		{
			int id = this->tileMatrix[i][j];
			if (id)
			{
				CSprites::GetInstance()->Get("map_" + std::to_string(mapID) + std::to_string(id))->Draw(DIRECTION::DEFAULT, j * 32, i * 32);
			}

		}
	}


}
