#pragma once
#include<string>
#include<vector>
#include<d3dx9.h>

class Layer
{
private:
	bool isVisible; 
	int width;  
	int height;
	int tileWidth;
	int tileHeight;

	std::string name;
	std::vector<std::vector<int>> tileMatrix;

	int mapID;

public:
	Layer(std::string name, int width, int height, int tileWidth, int tileHeight, bool isVisible, int mapID)
		:name(name), width(width), height(height), tileWidth(tileWidth), tileHeight(tileHeight), isVisible(isVisible), mapID(mapID)
	{

		tileMatrix.resize(height); 
		for (int i = 0; i < height; i++)
			tileMatrix[i].resize(width);

	};

	void Render(D3DXVECTOR2 cam);


	void SetTileMatrix(std::vector<std::vector<int>> tileMatrix)
	{
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
			{
				this->tileMatrix[i][j] = tileMatrix[i][j];
			}
		}

	}

};

