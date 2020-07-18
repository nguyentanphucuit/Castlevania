#include "Map.h"
#include"debug.h"
#include"Textures.h"
#include"Sprites.h"
#include"rapidxml/rapidxml_print.hpp"
#include"rapidxml/rapidxml.hpp"
#include"rapidxml/rapidxml_utils.hpp"
void Map::BuildMap(const std::string path, int texID)
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


	BuildTileSet(rootNode, texID);
	BuildMapLayer(rootNode);
	//BuildObjectLayer(rootNode);


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



		layer = new Layer(name, width, height, this->tileWidth, this->tileHeight, isVisible, this->mapID);

		layer->SetTileMatrix(tileMatrix);
		this->layers.insert(std::make_pair(name, layer));

	}
}

void Map::BuildTileSet(xml_node<>* node, int texID)
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

	LPDIRECT3DTEXTURE9 objecttex = textures->Get(texID);

	int TileId = 1;	

	for (std::size_t i = 0; i < tileSet.rows; i++)
	{
		for (std::size_t j = 0; j < tileSet.columns ; j++)
		{
			CSprites::GetInstance()->Add("map_" + std::to_string(mapID) +std::to_string(TileId), j * this->tileHeight, i * this->tileHeight, j * this->tileHeight + this->tileHeight, i * this->tileHeight + this->tileHeight, objecttex);
			TileId++;
		}
	}

}

void Map::BuildObjectLayer(xml_node<>* rootNode)
{


	rapidxml::xml_document<> doc;

	xml_attribute<>* cellX = doc.allocate_attribute("cellcol", "256");
	xml_node<>* decl = doc.allocate_node(node_declaration);
	decl->append_attribute(doc.allocate_attribute("version", "1.0"));
	decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
	doc.append_node(decl);

	int numCol = (this->width*this->tileWidth) / 256;
	int numRow = (this->height * this->tileHeight) / 256+1;

	xml_node<>* root = doc.allocate_node(node_element, "grid");
	root->append_attribute(doc.allocate_attribute("id", doc.allocate_string(std::to_string(this->mapID).c_str())));
	root->append_attribute(doc.allocate_attribute("cellSize", "256"));

	root->append_attribute(doc.allocate_attribute("numCol",doc.allocate_string(std::to_string(numCol).c_str())));
	root->append_attribute(doc.allocate_attribute("numRow", doc.allocate_string(std::to_string(numRow).c_str())));
	doc.append_node(root);






	

	// lập các node trong map lấy ra các node objectgroup
	for (xml_node<>* child = rootNode->first_node("objectgroup"); child; child = child->next_sibling()) //cú pháp lập
	{
		const std::string nodeName = child->name();
		if (nodeName != "objectgroup") // kiểm tra node có phải layer không cho chắc ăn
		{
			continue;// không phải tiếp tục vòng lặp
		}

		xml_node<>* objectGroupNode = doc.allocate_node(node_element, "objectgroup");
		




		ObjectLayer* objectlayer;// object layer tượng chưng cho 1 object group

		const std::string name = std::string(child->first_attribute("name")->value());
		const int id = std::atoi(child->first_attribute("id")->value());

		objectGroupNode->append_attribute(doc.allocate_attribute("name", doc.allocate_string(name.c_str())));
		objectGroupNode->append_attribute(doc.allocate_attribute("id", doc.allocate_string(std::to_string(id).c_str())));
		root->append_node(objectGroupNode);

		std::map<int, ObjectTile*> objectgroup;

		// child  lúc này là 1 object group tại lần lập hiện tại
			//lập toàn bộ objectgroup node lấy ra thông tin các object
		for (xml_node<>* ggchild = child->first_node(); ggchild; ggchild = ggchild->next_sibling()) //cú pháp lập
		{
			xml_node<>* objectNode = doc.allocate_node(node_element, "object");
			//	const std::string ggname = std::string(ggchild->first_attribute("name")->value());
			const int ggid = std::atoi(ggchild->first_attribute("id")->value());
			const float x = std::atof(ggchild->first_attribute("x")->value());
			const float y = std::atof(ggchild->first_attribute("y")->value());
			const float width = std::atof(ggchild->first_attribute("width")->value());
			const float height = std::atof(ggchild->first_attribute("height")->value());

			int cellX = x / 256;
			int cellY = y / 256;


			std::string lName = "NONAME";
			xml_attribute<>* name = ggchild->first_attribute("name");
			if (name != NULL)
			{
				lName = name->value();
			}

			objectNode->append_attribute(doc.allocate_attribute("id", doc.allocate_string(std::to_string(ggid).c_str())));
			objectNode->append_attribute(doc.allocate_attribute("col", doc.allocate_string(std::to_string(cellX).c_str())));
			objectNode->append_attribute(doc.allocate_attribute("row", doc.allocate_string(std::to_string(cellY).c_str())));
			objectNode->append_attribute(doc.allocate_attribute("x", doc.allocate_string(std::to_string(x).c_str())));
			objectNode->append_attribute(doc.allocate_attribute("y", doc.allocate_string(std::to_string(y).c_str())));
			objectNode->append_attribute(doc.allocate_attribute("width", doc.allocate_string(std::to_string(width).c_str())));
			objectNode->append_attribute(doc.allocate_attribute("height", doc.allocate_string(std::to_string(height).c_str())));
			objectNode->append_attribute(doc.allocate_attribute("name", doc.allocate_string(lName.c_str())));
			objectGroupNode->append_node(objectNode);

			//ĐỌC PROPERTY CỦA OBJECT

			xml_node<>* propNode = ggchild->first_node("properties");
			ObjectTile* object = new ObjectTile(ggid, x, y, width, height, lName);
			if (propNode != NULL)
			{
				xml_node<>* PropertiesNode = doc.allocate_node(node_element, "properties");
				objectNode->append_node(PropertiesNode);
				std::map<std::string, OProperty*> properties;
				for (xml_node<>* pchild = propNode->first_node(); pchild; pchild = pchild->next_sibling()) //cú pháp lập
				{
					xml_node<>* propertyNode = doc.allocate_node(node_element, "property");
					PropertiesNode->append_node(propertyNode);
					OProperty* property = new OProperty();
					property->name = std::string(pchild->first_attribute("name")->value());
					property->value = std::string(pchild->first_attribute("value")->value());
					properties.insert(std::make_pair(property->name, property));
					propertyNode->append_attribute(doc.allocate_attribute("name", doc.allocate_string(property->name.c_str())));
					propertyNode->append_attribute(doc.allocate_attribute("value", doc.allocate_string(property->value.c_str())));


				}
				object->SetProperties(properties);
			}



			//tạo 1 object

			// cho vào object group
			// khi kết thúc vòng lập ta lưu được hết các object trong group hiện tại
			// sau đó child sẽ là objectgroup tiếp theo trong map
			objectgroup.insert(std::make_pair(ggid, object));
		}
		// khởi tạo object group với id, name và các object con nằm trong nó
		objectlayer = new ObjectLayer(id, name, objectgroup);
		//cho objectgroup vào cái std::map lưu object của Map
		this->objectLayers.insert(std::make_pair(name, objectlayer));


	}

	std::ofstream theFile("GameContent\\Grid\\grid.xml");
	theFile << doc;
	theFile.close();
}

void Map::Render(D3DXVECTOR2 cam,RECT rect)
{
	
	for (auto const& x : this->layers)
	{
		x.second->Render(cam,rect);
	}


}

Layer* Map::GetLayer(std::string name)
{
	return this->layers.at(name);
}
