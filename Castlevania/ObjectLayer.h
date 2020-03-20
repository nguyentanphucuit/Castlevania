#pragma once
#include<string>
#include<map>

class ObjectTile
{
private:
	int id;
	float x;
	float y;
	float width;
	float height;
public:
	ObjectTile(int id, float x, float y, float width, float height) :id(id), x(x), y(y)
		, width(width), height(height) {};

	int GetID() { return id; }
	float GetX() { return x; }
	float GetY() { return y; }
	float GetWidth() { return width; }
	float GetHeight() { return height; }


};

class ObjectLayer
{
private:
	int id;
	std::string name;
	// khúc này có thể dùng vector cho dễ, còn dùng map thì có thể mở rộng sau này
	std::map<int, ObjectTile*> objectgroup;
public:
	ObjectLayer() :id(0), name("bla bla") {};
	ObjectLayer(int id, std::string name, std::map<int, ObjectTile*> objectgroup) :id(id)
		, name(name), objectgroup(objectgroup) {};

	std::map<int, ObjectTile*> GetObjectGroup() {
		return objectgroup;
	}


};

