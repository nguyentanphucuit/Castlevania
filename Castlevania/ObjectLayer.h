#pragma once
#include<string>
#include<map>


struct OProperty
{
	std::string name;
	int value;
	OProperty() :name(""), value(-1) {};
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
	std::map<std::string, OProperty*> properties;
public:
	ObjectTile(int id, float x, float y, float width, float height) :id(id), x(x), y(y)
		, width(width), height(height) {};

	void SetProerties(std::map<std::string, OProperty*> properties) { this->properties = properties; };
	int GetID() { return id; }
	float GetX() { return x; }
	float GetY() { return y; }
	float GetWidth() { return width; }
	float GetHeight() { return height; }

	int GetProperty(std::string key);
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

