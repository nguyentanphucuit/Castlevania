﻿#pragma once
#include<map>
#include"Layer.h"
#include<d3dx9.h>
#include<string>
#include"ObjectLayer.h"
#include<rapidxml/rapidxml.hpp>
#include<rapidxml/rapidxml_utils.hpp>
using namespace rapidxml;


struct TileSet 
{
	int imageWidth;
	int imageHeight; 
	std::string name;
	int columns; 
	int rows; 
	int tileCount;

	int tileWidth;
	int tileHeight;

};

class Map
{
private:
	int width; 
	int height;
	int mapID;

	int tileWidth;
	int tileHeight;
	TileSet tileSet;
	// lưu toàn bộ layer của map
	std::map<std::string, Layer*> layers;

	std::map<std::string, ObjectLayer*> objectLayers;
	void BuildMapLayer(xml_node<>* node);
	void BuildTileSet(xml_node<>* node, int texID);
	void BuildObjectLayer(xml_node<>* node);
public:

	int GetWidth() { return width; };
	int GetHeight() { return height; }
	std::map<std::string, ObjectLayer*> GetObjectLayer()
	{
		return objectLayers;

	}
	Map(int id) :width(0), height(0), tileWidth(0), tileHeight(0), mapID(id) {};
	void BuildMap(const std::string path, int texID);

	void Render(D3DXVECTOR2 cam,RECT rect);
	Layer* GetLayer(std::string name);
};

