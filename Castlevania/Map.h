#pragma once
#include<map>
#include"Layer.h"
#include<d3dx9.h>
#include<string>
#include"ObjectLayer.h"
#include<rapidxml/rapidxml.hpp>
#include<rapidxml/rapidxml_utils.hpp>
using namespace rapidxml;


struct TileSet // dùng demo nữa ta mở rộng sau h chỉ đọc duy nhất 1 tileset
{
	int imageWidth;// chiều rộng hình  Great_Hall_bank
	int imageHeight; //chiều dài hình Great_Hall_bank
	std::string name;
	int columns; // số cột được chia
	int rows; // số hàng được chia
	int tileCount;// tổng số tile được chia

	int tileWidth;
	int tileHeight;

};


// nên đọc name load qua đừng dùng id
enum class ObjLayer
{
	PlayerPos = 2,
	Ground = 3,
	Torch = 4,
	Camera=5,
};

class Map
{
private:
	int width; // chiều dài map (đã chia cho tileWidth)
	int height; // chiều cao map (đã chia cho tileHeight)

	int tileWidth;// chiều dài mỗi tile
	int tileHeight;// chiều cao mỗi tile
	TileSet tileSet;
	// lưu toàn bộ layer của map
	std::map<std::string, Layer*> layers;
	// dùng int hồi dò group = enum cho dễ
	std::map<int, ObjectLayer*> objectLayers;
	void BuildMapLayer(xml_node<>* node);
	void BuildTileSet(xml_node<>* node);
	void BuildObjectLayer(xml_node<>* node);
public:


	std::map<int, ObjectLayer*> GetObjectLayer()
	{
		return objectLayers;

	}
	Map() :width(0), height(0), tileWidth(0), tileHeight(0) {};
	void BuildMap(const std::string path);
	// vẽ toàn bộ layer theo camera
	void Render(D3DXVECTOR2 camera);
};

