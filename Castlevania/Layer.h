#pragma once
#include<string>
#include<vector>
#include<d3dx9.h>
/// Lưu ma trận của tile
class Layer
{
private:
	bool isVisible; // dùng để ẩn hiện layer;

	int width; // chiều dài layer đã chia tilesize(tilesize= đúng tilesize của map) 
	int height;
	int tileWidth;
	int tileHeight;

	std::string name; //tên layer
	std::vector<std::vector<int>> tileMatrix; // <=> int** tilematrix dùng vector 2 chiều khỏi dọn rác

public:
	Layer(std::string name, int width, int height, int tileWidth, int tileHeight, bool isVisible)
		:name(name), width(width), height(height), tileWidth(tileWidth), tileHeight(tileHeight), isVisible(isVisible)
	{
		//tạo ma trận 2 chiều

		tileMatrix.resize(height); // tạo ra số hàng = với height
		for (int i = 0; i < height; i++)// mỗi hàng tạo ra số cột = width
			tileMatrix[i].resize(width);

	};

	void Render(D3DXVECTOR2 cam);

	// hàm gán 2 ma trận
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

