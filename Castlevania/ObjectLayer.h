#pragma once
#include<string>
#include<map>


// hiện tại property chỉ hỗ trợ kiểu int
// mỗi object có thể có 1 ds property
struct OProperty
{
	std::string name;
	int value;
	OProperty() :name(""), value(-1) {};
};


class ObjectTile
{
private:
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

