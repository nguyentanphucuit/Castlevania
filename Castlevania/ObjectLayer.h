#pragma once
#include<string>
#include<map>


struct OProperty
{
	std::string name;
	std::string value;
	OProperty() :name(""), value("-1") {};
};


class ObjectTile
{
private:
	std::string name;
	int id;
	float x;
	float y;
	float width;
	float height;
	int col;
	int row;
	std::map<std::string, OProperty*> properties;
public:
	ObjectTile(int id, float x, float y, float width, float height, std::string name,int row=-1,int col=-1) :id(id), x(x), y(y)
		, width(width), height(height), name(name) {
		this->row = row;
		this->col = col;
	
	};

	void SetProperties(std::map<std::string, OProperty*> properties) { this->properties = properties; };
	int GetID() { return id; }
	float GetX() { return x; }
	float GetY() { return y; }
	float GetWidth() { return width; }
	float GetHeight() { return height; }

	int GetRow() { return this->row; }
	int GetCol() { return this->col; }
	std::string GetProperty(std::string key);
	std::string GetName() { return name; }
};

class ObjectLayer
{
private:
	int id;
	std::string name;
	std::map<int, ObjectTile*> objectgroup;
public:
	ObjectLayer() :id(0), name("") {};
	ObjectLayer(int id, std::string name, std::map<int, ObjectTile*> objectgroup) :id(id)
		, name(name), objectgroup(objectgroup) {};

	std::map<int, ObjectTile*> GetObjectGroup() {
		return objectgroup;
	}

};

