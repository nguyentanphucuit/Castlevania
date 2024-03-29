﻿#include "Grid.h"
#include"Weapon.h"
#include"Item.h"
#include"Effect.h"
#include"Phantom.h"
#include"Enemy.h"
#include "Torch.h"
#include"Hunchback.h"
#include"Spawer.h"
#include"Convert.h"
#include "debug.h"
#include "Game.h"
#include "Textures.h"
#include "Torch.h"
#include "HiddenObject.h"
#include "Ground.h"
#include "WeaponFactory.h"
#include "HMoney.h"
#include "Entrance.h"
#include "RetroGrade.h"
#include "SwitchScene.h"
#include "Stair.h"
#include "Candle.h"
#include "Bat.h"
#include "Spawer.h"
#include "Platform.h"
#include "BrickWall.h"
#include "StairDual.h"
#include "HCrown.h"
#include "Dual.h"
#include "ItemFactory.h"
#include "Abyss.h"

void Grid::BuildGrid(const std::string filePath)
{
}
void Grid::LoadGrid(const std::string FilePath)
{

	char* fileLoc = new char[FilePath.size() + 1]; // filepath lưu đường dẫn đến file XML đang đọc

#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, FilePath.size() + 1, FilePath.c_str());
#endif 

	//TODO: error checking - check file exists before attempting open.
	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	// grid main property
	xml_node<>* rootNode = doc.first_node("grid");
	int cellSize = std::atoi(rootNode->first_attribute("cellSize")->value());;
	int id = std::atoi(rootNode->first_attribute("id")->value());;
	int  num_col = std::atoi(rootNode->first_attribute("numCol")->value());
	int  num_row = std::atoi(rootNode->first_attribute("numRow")->value());
	this->cell_size = cellSize;
	this->grid_col = num_col;
	this->grid_row = num_row;
	this->id = id;

	// create vector to hold objects
	this->grid.resize(grid_row);
	for (int i = 0; i < grid_row; i++)
		grid[i].resize(grid_col);

	for (size_t i = 0; i < grid_row; i++) {
		for (size_t j = 0; j < grid_col; j++) {
			this->grid[i][j].clear();
		}
	}







	// lập các node trong map lấy ra các node objectgroup
	for (xml_node<>* child = rootNode->first_node("objectgroup"); child; child = child->next_sibling()) //cú pháp lập
	{
		const std::string nodeName = child->name();
		if (nodeName != "objectgroup") // kiểm tra node có phải layer không cho chắc ăn
		{
			continue;// không phải tiếp tục vòng lặp
		}

		ObjectLayer* objectlayer;// object layer tượng chưng cho 1 object group

		const std::string name = std::string(child->first_attribute("name")->value());
		const int id = std::atoi(child->first_attribute("id")->value());
		std::map<int, ObjectTile*> objectgroup;

		// child  lúc này là 1 object group tại lần lập hiện tại
			//lập toàn bộ objectgroup node lấy ra thông tin các object
		for (xml_node<>* ggchild = child->first_node(); ggchild; ggchild = ggchild->next_sibling()) //cú pháp lập
		{
			//	const std::string ggname = std::string(ggchild->first_attribute("name")->value());
			const int ggid = std::atoi(ggchild->first_attribute("id")->value());
			const float x = std::atof(ggchild->first_attribute("x")->value());
			const float y = std::atof(ggchild->first_attribute("y")->value());
			const float width = std::atof(ggchild->first_attribute("width")->value());
			const float height = std::atof(ggchild->first_attribute("height")->value());

			const int row = std::atof(ggchild->first_attribute("row")->value());
			const int col = std::atof(ggchild->first_attribute("col")->value());

			std::string lName = "NONAME";
			xml_attribute<>* name = ggchild->first_attribute("name");
			if (name != NULL)
			{
				lName = name->value();
			}
			//ĐỌC PROPERTY CỦA OBJECT

			xml_node<>* propNode = ggchild->first_node("properties");
			ObjectTile* object = new ObjectTile(ggid, x, y, width, height, lName, row, col);
			if (propNode != NULL)
			{
				std::map<std::string, OProperty*> properties;
				for (xml_node<>* pchild = propNode->first_node(); pchild; pchild = pchild->next_sibling()) //cú pháp lập
				{
					OProperty* property = new OProperty();
					property->name = std::string(pchild->first_attribute("name")->value());
					property->value = std::string(pchild->first_attribute("value")->value());
					properties.insert(std::make_pair(property->name, property));

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




	for (auto const& x : objectLayers)
	{
		
		ObjectID objID = string2EntityType.at(x.first);
		/*DebugOut(L"ID= %d", static_cast<ObjLayer>(x.first));*/
		switch (objID)
		{

		case _Player:
			for (auto const& y : x.second->GetObjectGroup())
			{
				D3DXVECTOR2 entry;
				entry.x = y.second->GetX();
				entry.y = y.second->GetY() - y.second->GetHeight();
				pScene->entryPoints.insert(std::make_pair(y.second->GetName(), entry));
			}
			break;

		case _Torch:
			for (auto const& y : x.second->GetObjectGroup())
			{
				CTorch* torch = new CTorch();
				torch->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
				torch->SetItem(static_cast<EItem>(std::atoi(y.second->GetProperty("item").c_str())));
				torch->SetCellIndex(y.second->GetCol(), y.second->GetRow());
				Add(torch);
			
				

			}
			break;

		case _Camera:
			for (auto const& y : x.second->GetObjectGroup())
			{
				RECT border;
				border.left = y.second->GetX();
				border.top = y.second->GetY();
				border.right = y.second->GetX() + y.second->GetWidth();
				border.bottom = y.second->GetY() + y.second->GetHeight();

				pScene->pSceneBorders.insert(std::make_pair(y.second->GetName(), border));

			}
			break;
		case _Ground:
			for (auto const& y : x.second->GetObjectGroup())
			{
				HiddenObject* ground = new Ground();
				ground->SetPosition(y.second->GetX(), y.second->GetY());
				ground->SetSize(y.second->GetWidth(), y.second->GetHeight());
				ground->SetCellIndex(y.second->GetCol(), y.second->GetRow());
				Add(ground, true);
			}
			break;
		case _HMoney:
			for (auto const& y : x.second->GetObjectGroup()) {
				HMoney* hMoney = new HMoney();
				hMoney->SetPosition(y.second->GetX(), y.second->GetY());
				hMoney->SetSize(y.second->GetWidth(), y.second->GetHeight());
				auto moneyLayer = objectLayers.at("IMoney");
				for (auto const& child : moneyLayer->GetObjectGroup()) {
					auto moneyItem = ItemFactory::SpawnItem<Item*>(EItem::MONEY);
					moneyItem->SetPosition(child.second->GetX(), child.second->GetY() - child.second->GetHeight());
					moneyItem->SetCellIndex(y.second->GetCol(), y.second->GetRow());
					hMoney->SetItem(moneyItem);
				}
				hMoney->SetCellIndex(y.second->GetCol(), y.second->GetRow());
				Add(hMoney);
			}
			break;
		case _Entrance:
			for (auto const& y : x.second->GetObjectGroup()) {
				Entrance* entrance = new Entrance();
				entrance->SetSize(y.second->GetWidth(), y.second->GetHeight());
				entrance->SetPosition(y.second->GetX(), y.second->GetY());
				entrance->SetCellIndex(y.second->GetCol(), y.second->GetRow());
				Add(entrance);
			}
			break;
		case _CheckRetrograde:
			for (auto const& y : x.second->GetObjectGroup()) {
				RetroGrade* retroGrade = new RetroGrade();
				retroGrade->SetSize(y.second->GetWidth(), y.second->GetHeight());
				retroGrade->SetPosition(y.second->GetX(), y.second->GetY());
				retroGrade->SetCellIndex(y.second->GetCol(), y.second->GetRow());
				Add(retroGrade);
			}
			break;
		case _Enemy:
			for (auto const& y : x.second->GetObjectGroup()) {
				Spawner* spawner = new Spawner(static_cast<CEnemy>(std::atoi(y.second->GetProperty("edef").c_str())), std::atoi(y.second->GetProperty("time").c_str()), std::atoi(y.second->GetProperty("num").c_str()), std::atoi(y.second->GetProperty("startPos").c_str()), std::atoi(y.second->GetProperty("endPos").c_str()), std::atoi(y.second->GetProperty("nx").c_str()));
				spawner->SetSize(y.second->GetWidth(), y.second->GetHeight());
				spawner->SetPosition(y.second->GetX(), y.second->GetY());
				spawner->SetCellIndex(y.second->GetCol(), y.second->GetRow());
				Add(spawner, true);
			}
			break;
		case _NextScene:
			for (auto const& y : x.second->GetObjectGroup()) {
				auto pSwitch = new SwitchScene(std::atoi(y.second->GetProperty("sceneID").c_str()));
				pSwitch->SetSize(y.second->GetWidth(), y.second->GetHeight());
				pSwitch->SetPosition(y.second->GetX(), y.second->GetY());
				pSwitch->SetCellIndex(y.second->GetCol(), y.second->GetRow());
				Add(pSwitch);
			}
			break;
		case _Stair:
			for (auto const& y : x.second->GetObjectGroup()) {
				Stair* stair = new Stair();
				stair->SetSize(y.second->GetWidth(), y.second->GetHeight());
				stair->SetPosition(y.second->GetX(), y.second->GetY());
				stair->SetDirection(std::atoi(y.second->GetProperty("dir").c_str()));
				stair->SetCellIndex(y.second->GetCol(), y.second->GetRow());
				Add(stair);
			}
			break;
		case _Candle:
			for (auto const& y : x.second->GetObjectGroup())
			{
				CCandle* candle = new CCandle();
				candle->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
				candle->SetItem(static_cast<EItem>(std::atoi(y.second->GetProperty("item").c_str())));
				candle->SetCellIndex(y.second->GetCol(), y.second->GetRow());
				Add(candle);
			}
			break;
		case _Platform:
			for (auto const& y : x.second->GetObjectGroup()) {
				CPlatform* platform = new CPlatform();
				platform->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
				platform->SetCellIndex(y.second->GetCol(), y.second->GetRow());
				Add(platform);
			}
			break;
		case _BrickWall:
			for (auto const& y : x.second->GetObjectGroup()) {
				CBrickWall* brickwall = new CBrickWall();
				brickwall->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
				brickwall->SetItem(static_cast<EItem>(std::atoi(y.second->GetProperty("item").c_str())));
				brickwall->SetCellIndex(y.second->GetCol(), y.second->GetRow());

				Add(brickwall);
			}
			break;
		case _HCrown:
			for (auto const& y : x.second->GetObjectGroup()) {
				HCrown* hCrown = new HCrown();
				hCrown->SetPosition(y.second->GetX(), y.second->GetY());
				hCrown->SetSize(y.second->GetWidth(), y.second->GetHeight());
				auto crownLayer = objectLayers.at("ICrown");
				for (auto const& child : crownLayer->GetObjectGroup()) {
					auto crownItem = ItemFactory::SpawnItem<Item*>(EItem::CROWN);
					crownItem->SetPosition(child.second->GetX(), child.second->GetY() - child.second->GetHeight());
					crownItem->SetCellIndex(y.second->GetCol(), y.second->GetRow());
					hCrown->SetItem(crownItem);
				}
				hCrown->SetCellIndex(y.second->GetCol(), y.second->GetRow());
				Add(hCrown);
			}
			break;
		case _Boss:
			for (auto const& y : x.second->GetObjectGroup()) {
				pScene->boss->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
				pScene->boss->SetCellIndex(y.second->GetCol(), y.second->GetRow());
				
				Add(pScene->boss);
			}
			break;
		case _StairDual:
			for (auto const& y : x.second->GetObjectGroup()) {
				Dual* dual = new Dual();
				dual->SetSize(y.second->GetWidth(), y.second->GetHeight());
				dual->SetPosition(y.second->GetX(), y.second->GetY());
				dual->SetCellIndex(y.second->GetCol(), y.second->GetRow());
				Add(dual);
			}
			break;
		case _Abyss:
			for (auto const& y : x.second->GetObjectGroup()) {
				Abyss* abyss = new Abyss();
				abyss->SetSize(y.second->GetWidth(), y.second->GetHeight());
				abyss->SetPosition(y.second->GetX(), y.second->GetY());
				abyss->SetCellIndex(y.second->GetCol(), y.second->GetRow());
				Add(abyss);
			}
			break;
		default:
			break;
		}
	}


}

void Grid::Add(LPGAMEOBJECT object, bool isAlwayUpdateObject)
{
	CellIndex index = object->GetCellIndex();
	if (index.x > grid_col || index.y > grid_row - 1)
		return;
	//đánh dấu object thuộc cell nào
	// để có thể truy vấn nhanh vị trị của object trong grid
	

	if (!isAlwayUpdateObject)
		this->grid[index.y][index.x].push_back(object);
	else
		alwaysUpdateList.push_back(object);
}

void Grid::AddAfterUpdate(LPGAMEOBJECT object, bool isAlwayUpdateObject)
{
	float x_, y_;
	object->GetPosition(x_, y_);
	//tính vị trí của object
	int cellX = (int)(x_ / this->cell_size);
	int cellY = (int)(y_ / this->cell_size);
	if (cellX > grid_col || cellY > grid_row - 1)
		return;
	//đánh dấu object thuộc cell nào
	// để có thể truy vấn nhanh vị trị của object trong grid

	object->SetCellIndex(cellX, cellY);
	if (!isAlwayUpdateObject)
		this->grid[cellY][cellX].push_back(object);
	else
		alwaysUpdateList.push_back(object);
}

void Grid::Update(LPGAMEOBJECT object)
{
	float cx_, cy_;

	D3DXVECTOR2 cam = CGame::GetInstance()->GetCamera();

	cx_ = cam.x;
	cy_ = cam.y;

	float x, y;
	object->GetPosition(x, y);

	float l, t, r, b;
	object->GetBoundingBox(l, t, r, b);

	if (object->AABB(l, t, r, b, cx_, cy_, cx_ + SCREENSIZE::WIDTH, cy_ + SCREENSIZE::HEIGHT))
		object->SetActive();
	else {
		if (object->CheckActive()) {
			if (dynamic_cast<Item*>(object)
				|| dynamic_cast<Enemy*>(object)
				|| dynamic_cast<Weapon*>(object)
				) {
				if (!dynamic_cast<Phantom*>(object))
					object->isDestroy = true;
			}

		}
	}

	CellIndex oldCell = object->GetCellIndex();

	int cellX = (int)(x / this->cell_size);
	int cellY = (int)(y / this->cell_size);

	if (object->IsDestroy())
	{
		for (vector<LPGAMEOBJECT>::iterator it = grid[oldCell.y][oldCell.x].begin(); it != grid[oldCell.y][oldCell.x].end(); ) {
			if ((*it) == object) {
				if (dynamic_cast<Hunchback*>(*it)) {
					auto hum = dynamic_cast<Hunchback*>(*it);
					hum->spawnOwner->numHunchback--;
				}
				if (dynamic_cast<BlackKnight*>(*it)) {
					auto blackKnight = dynamic_cast<BlackKnight*>(*it);
					blackKnight->spawnOwner->numBlackKnight--;
				}
				if (dynamic_cast<Bat*>(*it)) {
					auto bat = dynamic_cast<Bat*>(*it);
					bat->spawnOwner->numBat--;
				}
				if (dynamic_cast<Ghost*>(*it)) {
					auto ghost = dynamic_cast<Ghost*>(*it);
					ghost->spawnOwner->numGhost--;
				}
				if (dynamic_cast<White*>(*it)) {
					auto white = dynamic_cast<White*>(*it);
					white->spawnOwner->numWhite--;
				}
				if (dynamic_cast<Raven*>(*it)) {
					auto raven = dynamic_cast<Raven*>(*it);
					raven->spawnOwner->numRaven--;
				}
				if (dynamic_cast<Zombie*>(*it)) {
					auto zombie = dynamic_cast<Zombie*>(*it);
					zombie->spawnOwner->numZombie--;
				}

				it = grid[oldCell.y][oldCell.x].erase(it);
			}
			else ++it;
		}
		return;
	}

	if (oldCell.x == cellX && oldCell.y == cellY) return;
	if (oldCell.x != -1 && oldCell.y != -1) {				// loại bỏ cell cũ
		for (vector<LPGAMEOBJECT>::iterator it = grid[oldCell.y][oldCell.x].begin(); it != grid[oldCell.y][oldCell.x].end(); ) {
			if ((*it) == object) {
				it = grid[oldCell.y][oldCell.x].erase(it);
			}
			else ++it;
		}
	}
	AddAfterUpdate(object);
}

void Grid::GetListobjectFromGrid(vector<LPGAMEOBJECT>& listobjects)
{
	vector<LPGAMEOBJECT> enemiesobject;
	vector<LPGAMEOBJECT> itemobject;
	vector<LPGAMEOBJECT> subWeaponobject;
	vector<LPGAMEOBJECT> effectobject;
	enemiesobject.clear();
	itemobject.clear();
	subWeaponobject.clear();
	effectobject.clear();

	float camx, camy;
	D3DXVECTOR2 cam = CGame::GetInstance()->GetCamera();
	camx = cam.x;
	camy = cam.y;
	int startCol = floor(camx / this->cell_size);
	startCol = startCol > 0 ? startCol + -1 : 0;
	int endCol = floor((camx + SCREENSIZE::WIDTH) / this->cell_size);
	endCol = endCol > grid_col ? grid_col : endCol + 1;
	for (int i = 0; i < this->grid_row; i++) {
		for (int j = startCol; j < endCol; j++) {
			for (size_t k = 0; k < this->grid[i][j].size(); k++) {
				LPGAMEOBJECT obj = this->grid[i][j].at(k);
				if (!obj->IsDestroy()) {
					if (dynamic_cast<Enemy*>(obj))
						enemiesobject.push_back(obj);
					else if (dynamic_cast<Item*>(obj))
						itemobject.push_back(obj);
					else if (dynamic_cast<Weapon*>(obj))
						subWeaponobject.push_back(obj);
					else if (dynamic_cast<Effect*>(obj))
						effectobject.push_back(obj);
					else
						listobjects.push_back(obj);
				}
				else
				{
					//	DebugOut(L" LOSING OBJECT \n");
				}
			}
		}
	}

	listobjects.insert(listobjects.end(), alwaysUpdateList.begin(), alwaysUpdateList.end());
	listobjects.insert(listobjects.end(), itemobject.begin(), itemobject.end());
	listobjects.insert(listobjects.end(), enemiesobject.begin(), enemiesobject.end());
	listobjects.insert(listobjects.end(), subWeaponobject.begin(), subWeaponobject.end());
	listobjects.insert(listobjects.end(), effectobject.begin(), effectobject.end());

}
