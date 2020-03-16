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

	// truy vấn node trong file dùng xml_node<>* 
	xml_node<>* rootNode = doc.first_node("map"); //rootnode là node đầu tiên ở đây là "gamedata"
	// Đọc lên các thông tin cơ bản của map



	this->width = std::atoi(rootNode->first_attribute("width")->value());
	this->height = std::atoi(rootNode->first_attribute("height")->value());
	this->tileWidth = std::atoi(rootNode->first_attribute("tilewidth")->value());
	this->tileHeight = std::atoi(rootNode->first_attribute("tileheight")->value());


	BuildTileSet(rootNode);
	BuildMapLayer(rootNode);


}

void Map::BuildMapLayer(xml_node<>* rootNode)
{
	// lập các node trong map lấy ra các node Layer
	for (xml_node<>* child = rootNode->first_node("layer"); child; child = child->next_sibling()) //cú pháp lập
	{
		Layer* layer;

		int width = 0, height = 0;
		bool isVisible = true;
		const std::string nodeName=child->name();
		if (nodeName !="layer") // kiểm tra node có phải layer không cho chắc ăn
		{
			continue;// không phải tiếp tục vòng lặp
		}


		const std::string name = std::string(child->first_attribute("name")->value());
		
		width = std::atoi(child->first_attribute("width")->value());
		height= std::atoi(child->first_attribute("height")->value());


		xml_attribute<>* isVisibleArrt = child->first_attribute("visible");
		if (isVisibleArrt!=NULL)
		{
			isVisible = false;
		}
		// Khúc này đọc toàn bộ matrix của layer hiện tại lên


		std::vector<std::vector<int>> tileMatrix; // matrix phụ hồi gán nó vào layer

		tileMatrix.resize(height); // tạo mãng 2 chiều
		for (int i = 0; i < height; i++)
			tileMatrix[i].resize(width);

		int i = 0, j = 0;
		/// i là số hàng của ma trận
		/// j là số cột
		//đọc ma trận
		xml_node<>* dataNode = child->first_node("data");
		for (xml_node<>* child = dataNode->first_node(); child; child = child->next_sibling())
		{
			xml_attribute<>* gid = child->first_attribute("gid"); // đọc vào từng gid
			int n = 0; // biến tạm lưu giá trị của gid
			if (gid!=NULL)
			{
				n = std::atoi(gid->value());
			}
			/// ta đọc theo từng hàng
			// tức là hàng 0 đọc hết tất cả các cột của hàng 0 trước khi qua hàng 1
			tileMatrix[i][j] = n; // gán giá trị vào ma trận
			DebugOut(L"M[%d][%d]=%d  \n", i, j, n);
			j++; // tăng cột của hàng đang xét lên
			if (j > this->width - 1) // nếu số cột đã = số cột tối đa(this->width-1 vì j bắt đầu từ 0 )
			{
				i++; // tăng hàng lên
				j = 0;// duyệt từ cột 0 của hàng mới
			}



		}



		layer = new Layer(name, width, height, this->tileWidth, this->tileHeight, isVisible);

		// this->tileWidth, this->tileHeight vì chiều dài tile của layer dựa vào tileWidth,tileHeight của map

		layer->SetTileMatrix(tileMatrix);

		/// lưu layer vào map layer 

		// cú pháp thêm vào std::map<std::string, Layer*> layers;
		this->layers.insert(std::make_pair(name, layer));


	}
}

void Map::BuildTileSet(xml_node<>* node)
{
	xml_node<>* tileSetNode = node->first_node("tileset");
	tileSet.name = std::string(tileSetNode->first_attribute("name")->value());
	tileSet.columns = std::atoi(tileSetNode->first_attribute("columns")->value());
	tileSet.tileCount= std::atoi(tileSetNode->first_attribute("tilecount")->value());
	tileSet.rows = tileSet.tileCount / tileSet.columns;

	///DEMO
	CTextures* textures = CTextures::GetInstance();

	LPDIRECT3DTEXTURE9 objecttex = textures->Get(-500);


	// chú ý đánh số từ 1
	int TileId = 1;		// id of tileset


	//lưu thông tin các tile mình đánh số vào sprite dựa vào file hình và file tileset
	for (std::size_t i = 0; i < tileSet.rows; i++)
	{
		for (std::size_t j = 0; j < tileSet.columns; j++)
		{
			CSprites::GetInstance()->Add("map_" + std::to_string(TileId), j * this->tileHeight, i * this->tileHeight, j * this->tileHeight + this->tileHeight, i * this->tileHeight + this->tileHeight, objecttex);
			TileId++;
		}
	}


}

void Map::Render(D3DXVECTOR2 camera)
{

	for (auto const& x : this->layers)
	{
		x.second->Render(camera);
	}


}
