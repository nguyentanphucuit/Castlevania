#include "ObjectLayer.h"

std::string ObjectTile::GetProperty(std::string key)
{
	if (this->properties.count(key)>0) // có property tưng ứng với key 
	{
		return this->properties.at(key)->value;
	}
	return "-999";
}
