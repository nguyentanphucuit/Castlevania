#include "Map.h"
#include"debug.h"
#include"Textures.h"
#include"Sprites.h"
void Map::BuildMap(const std::string path)
{
	char* fileLoc = new char[path.size() + 1]; // filepath lưu đường dẫn đến file XML đang đọc

#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, path.size() + 1, path.c_str());
#endif 

	//TODO: error checking - check file exists before attempting open.
	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	xml_node<>* rootNode = doc.first_node("map"); 

	this->width = std::atoi(rootNode->first_attribute("width")->value());
	this->height = std::atoi(rootNode->first_attribute("height")->value());
	this->tileWidth = std::atoi(rootNode->first_attribute("tilewidth")->value());
	this->tileHeight = std::atoi(rootNode->first_attribute("tileheight")->value());


	BuildTileSet(rootNode);
	BuildMapLayer(rootNode);
	BuildObjectLayer(rootNode);


}

void Map::BuildMapLayer(xml_node<>* rootNode)
{
	for (xml_node<>* child = rootNode->first_node("layer"); child; child = child->next_sibling()) //cú pháp lập
	{
		Layer* layer;

		int width = 0, height = 0;
		bool isVisible = true;
		const std::string nodeName = child->name();
		if (nodeName != "layer")
		{
			continue;
		}

		const std::string name = std::string(child->first_attribute("name")->value());

		width = std::atoi(child->first_attribute("width")->value());
		height = std::atoi(child->first_attribute("height")->value());


		xml_attribute<>* isVisibleArrt = child->first_attribute("visible");
		if (isVisibleArrt != NULL)
		{
			isVisible = false;
		}

		std::vector<std::vector<int>> tileMatrix; 

		tileMatrix.resize(height); 
		for (int i = 0; i < height; i++)
			tileMatrix[i].resize(width);

		int i = 0, j = 0; 

		xml_node<>* dataNode = child->first_node("data");
		for (xml_node<>* child = dataNode->first_node(); child; child = child->next_sibling())
		{
			xml_attribute<>* gid = child->first_attribute("gid"); 
			int n = 0; 
			if (gid != NULL)
			{
				n = std::atoi(gid->value());
			}
			tileMatrix[i][j] = n; 
			j++;
			if (j > this->width - 1) 
			{
				i++; 
				j = 0;
			}
		}



		layer = new Layer(name, width, height, this->tileWidth, this->tileHeight, isVisible);

		layer->SetTileMatrix(tileMatrix);
		this->layers.insert(std::make_pair(name, layer));

	}
}

void Map::BuildTileSet(xml_node<>* node)
{

	xml_node<>* tileSetNode = node->first_node("tileset");
	tileSet.name = std::string(tileSetNode->first_attribute("name")->value());
	
	tileSet.tileWidth = std::atoi(tileSetNode->first_attribute("tilewidth")->value());
	tileSet.tileHeight = std::atoi(tileSetNode->first_attribute("tileheight")->value());


	xml_node<>* imgNode = tileSetNode->first_node("image");
	tileSet.imageHeight = std::atoi(imgNode->first_attribute("height")->value());
	tileSet.imageWidth = std::atoi(imgNode->first_attribute("width")->value());

	tileSet.columns = tileSet.imageWidth / tileSet.tileWidth;
	tileSet.rows = tileSet.imageHeight / tileSet.tileHeight;

	///DEMO
	CTextures* textures = CTextures::GetInstance();

	LPDIRECT3DTEXTURE9 objecttex = textures->Get(-500);

	int TileId = 1;	

	for (std::size_t i = 0; i < tileSet.rows; i++)
	{
		for (std::size_t j = 0; j < tileSet.columns; j++)
		{
			CSprites::GetInstance()->Add("map_" + std::to_string(TileId), j * this->tileHeight, i * this->tileHeight, j * this->tileHeight + this->tileHeight, i * this->tileHeight + this->tileHeight, objecttex);
			TileId++;
		}
	}


}

void Map::BuildObjectLayer(xml_node<>* rootNode)
{
	for (xml_node<>* child = rootNode->first_node("objectgroup"); child; child = child->next_sibling()) //cú pháp lập
	{
		const std::string nodeName = child->name();
		if (nodeName != "objectgroup") 
		{
			continue;
		}

		ObjectLayer* objectlayer;

		const std::string name = std::string(child->first_attribute("name")->value());
		const int id = std::atoi(child->first_attribute("id")->value());
		std::map<int, ObjectTile*> objectgroup;

		for (xml_node<>* ggchild = child->first_node(); ggchild; ggchild = ggchild->next_sibling()) //cú pháp lập
		{
		
			const int ggid = std::atoi(ggchild->first_attribute("id")->value());
			const float x = std::atof(ggchild->first_attribute("x")->value());
			const float y = std::atof(ggchild->first_attribute("y")->value());
			const float width = std::atof(ggchild->first_attribute("width")->value());
			const float height = std::atof(ggchild->first_attribute("height")->value());


			//ĐỌC PROPERTY CỦA OBJECT

			xml_node<>* propNode = ggchild->first_node("properties");
			ObjectTile* object = new ObjectTile(ggid, x, y, width, height);
			if (propNode != NULL)
			{
				std::map<std::string, OProperty*> properties;
				for (xml_node<>* pchild = propNode->first_node(); pchild; pchild = pchild->next_sibling()) //cú pháp lập
				{
					OProperty* property=new OProperty();
					property->name= std::string(pchild->first_attribute("name")->value());
					property->value = std::atoi(pchild->first_attribute("value")->value());
					properties.insert(std::make_pair(property->name, property));

				}
				object->SetProerties(properties);
			}


			objectgroup.insert(std::make_pair(ggid, object));
		}
		
		objectlayer = new ObjectLayer(id, name, objectgroup);

		this->objectLayers.insert(std::make_pair(id, objectlayer));


	}
}

void Map::Render(D3DXVECTOR2 camera)
{
	
	for (auto const& x : this->layers)
	{
		x.second->Render(camera);
	}


}

Layer* Map::GetLayer(std::string name)
{
	return this->layers.at(name);
}
