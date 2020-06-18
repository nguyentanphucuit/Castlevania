#include "PlayScene.h"
#include "define.h"
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
#include "Convert.h"
#include "Stair.h"
#include "Candle.h"
#include "Bat.h"
#include "Spawer.h"
#include "Platform.h"
#include "BrickWall.h"
#include "StairDual.h"

void PlayScene::LoadSprite(const std::string& filePath, const int tex)
{
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();


	LPDIRECT3DTEXTURE9 objecttex = textures->Get(tex);
	char* fileLoc = new char[filePath.size() + 1];
#



	//TODO: make multi format version of string copy
#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, filePath.size() + 1, filePath.c_str());
#endif 

	//TODO: error checking - check file exists before attempting open.
	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	xml_node<>* rootNode = doc.first_node("gamedata");

	for (xml_node<>* child = rootNode->first_node(); child; child = child->next_sibling())
	{
		const std::string& ID = std::string(child->first_attribute("ID")->value());
		xml_node<>* frameNode = child->first_node("frame");

		int l = std::atoi(frameNode->first_attribute("l")->value());
		int t = std::atoi(frameNode->first_attribute("t")->value());
		int r = std::atoi(frameNode->first_attribute("r")->value());
		int b = std::atoi(frameNode->first_attribute("b")->value());

		//	DebugOut(L" ID= %d, l=%d, t=%d , r=%d , b=%d \n", ID, l, t, r, b);
		sprites->Add(ID, l, t, r, b, objecttex);
	}


}
void PlayScene::LoadAnimation(const string& filePath)
{
	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani;

	char* fileLoc = new char[filePath.size() + 1];
#
	//TODO: make multi format version of string copy
#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, filePath.size() + 1, filePath.c_str());
#endif 

	//TODO: error checking - check file exists before attempting open.
	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	xml_node<>* rootNode = doc.first_node("gamedata");
	xml_node<>* aniNode = rootNode->first_node("animation");
	for (xml_node<>* child = rootNode->first_node(); child; child = child->next_sibling())
	{

		const std::string& ID = std::string(child->first_attribute("ID")->value());
		int timeLoop = std::atoi(child->first_attribute("timeLoop")->value());
		ani = new CAnimation(timeLoop);
		for (xml_node<>* grand = child->first_node(); grand; grand = grand->next_sibling())// lặp thêm lần nữa lấy hết sprite id
		{
			const std::string& spriteID = std::string(grand->first_attribute("ID")->value());

			ani->Add(spriteID);
			//	DebugOut(L"ANI ID=%d sprite =%d \n", ID, spriteID);
		}

		animations->Add(ID, ani);


	}


}

void PlayScene::LoadSceneContent(xml_node<>* root)
{
	xml_node<>* sceneNode = root->first_node("scenes");
	xml_node<>* playSceneNode = sceneNode->first_node("pscene");
	const int activeID = std::atoi(playSceneNode->first_attribute("activeID")->value());
	for (xml_node<>* child = playSceneNode->first_node(); child; child = child->next_sibling()) {
		pScene* _pScene = new pScene();
		const int _id = std::atoi(child->first_attribute("id")->value());
		const int _mapID = std::atoi(child->first_attribute("mapID")->value());
		const int _isRight = std::atoi(child->first_attribute("isRight")->value());
		const std::string& _border = std::string(child->first_attribute("border")->value());
		const std::string& _entry = std::string(child->first_attribute("entry")->value());

		_pScene->id = _id;
		_pScene->mapID = _mapID;
		_pScene->border = _border;
		_pScene->isRight = !_isRight;

		
		_pScene->entry = _entry;
		this->pScenes.insert(std::make_pair(_id, _pScene));
	}
	this->currentPScene = this->pScenes.at(activeID);

	this->currentMap = this->Maps.at(this->currentPScene->mapID);
	this->cameraBorder = this->pSceneBorders.at(this->currentPScene->border);
	this->currentEntryPoints = this->entryPoints.at(this->currentPScene->entry);
	
	this->SIMON->SetPosition(currentEntryPoints.x, currentEntryPoints.y);
	CGame::GetInstance()->SetCamPos(cameraBorder.left, cameraBorder.top);
}

void PlayScene::GetListobjectFromGrid()
{
}

void PlayScene::UpdateGrid()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		LPGAMEOBJECT obj = objects[i];
		float x_, y_;
		obj->GetPosition(x_, y_);
		grid->Update(obj);
	}
}

D3DXVECTOR2 PlayScene::GetCamera()
{

	return CGame::GetInstance()->GetCamera();
}
void PlayScene::AddToGrid(LPGAMEOBJECT object, bool isAlwayUpdate)
{
	grid->Add(object, isAlwayUpdate);
}
void PlayScene::OnCreate()
{
	CTextures* textures = CTextures::GetInstance();

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	const std::string filePath = "GameContent\\Data.xml";

	char* fileLoc = new char[filePath.size() + 1];
#
	//TODO: make multi format version of string copy
#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, filePath.size() + 1, filePath.c_str());
#endif 

	//TODO: error checking - check file exists before attempting open.
	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	xml_node<>* rootNode = doc.first_node("Data");
	xml_node<>* texNode = rootNode->first_node("textures");

	for (xml_node<>* child = texNode->first_node(); child; child = child->next_sibling()) //cú pháp lập
	{
		int idTex;
		int red;
		int green;
		int blue;

		const std::string& path = std::string(child->first_attribute("path")->value());
		idTex = std::atoi(child->first_attribute("ID")->value());

		red = std::atoi(child->first_attribute("red")->value());
		green = std::atoi(child->first_attribute("green")->value());
		blue = std::atoi(child->first_attribute("blue")->value());

		// ép kiểu nó đòi lpcwstr
		std::wstring cover = std::wstring(path.begin(), path.end());
		textures->Add(idTex, cover.c_str(), D3DCOLOR_XRGB(red, green, blue));

	}


	xml_node<>* spriteNode = rootNode->first_node("sprites");
	// load sprite
	for (xml_node<>* child = spriteNode->first_node(); child; child = child->next_sibling()) //cú pháp lập
	{
		int idTex;
		const std::string& path = std::string(child->first_attribute("path")->value());
		idTex = std::atoi(child->first_attribute("ID")->value());

		LoadSprite(path, idTex);
	}

	//load ani
	xml_node<>* aniNode = rootNode->first_node("animations");
	for (xml_node<>* child = aniNode->first_node(); child; child = child->next_sibling())
	{
		const std::string& path = std::string(child->first_attribute("path")->value());
		LoadAnimation(path);

	}

	//load map
	xml_node<>* mapsNode = rootNode->first_node("maps");
	for (xml_node<>* child = mapsNode->first_node(); child; child = child->next_sibling()) {
		const std::string& path = std::string(child->first_attribute("path")->value());
		const int id = std::atoi(child->first_attribute("id")->value());
		const int texID = std::atoi(child->first_attribute("texID")->value());
		Map* map = new Map(id);
		map->BuildMap(path, texID);
		this->Maps.insert(std::make_pair(id, map));
	}



	SIMON = new CSIMON();
	

	for (auto const& m : Maps) {
		auto objectLayer = m.second->GetObjectLayer();
		 grid = new Grid(m.second->GetWidth(), m.second->GetHeight());

		for (auto const& x : objectLayer)
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
					this->entryPoints.insert(std::make_pair(y.second->GetName(), entry));
				}
				break;

			case _Torch:
				for (auto const& y : x.second->GetObjectGroup())
				{
					CTorch* torch = new CTorch();
					torch->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
					torch->SetItem(static_cast<EItem>(std::atoi(y.second->GetProperty("item").c_str())));
					AddToGrid(torch);
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

					this->pSceneBorders.insert(std::make_pair(y.second->GetName(), border));

				}
				break;
			case _Ground:
				for (auto const& y : x.second->GetObjectGroup())
				{
					HiddenObject* ground = new Ground();
					ground->SetPosition(y.second->GetX(), y.second->GetY());
					ground->SetSize(y.second->GetWidth(), y.second->GetHeight());
					AddToGrid(ground,true);
				}
				break;
			case _HMoney:
				for (auto const& y : x.second->GetObjectGroup()) {
					HMoney* hMoney = new HMoney();
					hMoney->SetPosition(y.second->GetX(), y.second->GetY());
					hMoney->SetSize(y.second->GetWidth(), y.second->GetHeight());
					auto moneyLayer = objectLayer.at("IMoney");
					for (auto const& child : moneyLayer->GetObjectGroup()) {
						auto moneyItem = ItemFactory::SpawnItem<Item*>(EItem::MONEY);
						moneyItem->SetPosition(child.second->GetX(), child.second->GetY() - child.second->GetHeight());
						hMoney->SetItem(moneyItem);
					}
					AddToGrid(hMoney);
				}
				break;
			case _Entrance:
				for (auto const& y : x.second->GetObjectGroup()) {
					Entrance* entrance = new Entrance();
					entrance->SetSize(y.second->GetWidth(), y.second->GetHeight());
					entrance->SetPosition(y.second->GetX(), y.second->GetY());
					AddToGrid(entrance);
				}
				break;
			case _CheckRetrograde:
				for (auto const& y : x.second->GetObjectGroup()) {
					RetroGrade* retroGrade = new RetroGrade();
					retroGrade->SetSize(y.second->GetWidth(), y.second->GetHeight());
					retroGrade->SetPosition(y.second->GetX(), y.second->GetY());
					AddToGrid(retroGrade);
				}
				break;
			case _Enemy:
				for (auto const& y : x.second->GetObjectGroup()) {
					Spawner* spawner = new Spawner(static_cast<CEnemy>(std::atoi(y.second->GetProperty("edef").c_str())), std::atoi(y.second->GetProperty("time").c_str()),std::atoi(y.second->GetProperty("num").c_str()), std::atoi(y.second->GetProperty("startPos").c_str()), std::atoi(y.second->GetProperty("endPos").c_str()));
					spawner->SetSize(y.second->GetWidth(), y.second->GetHeight());
					spawner->SetPosition(y.second->GetX(), y.second->GetY());
					AddToGrid(spawner,true);
				}
				break;
			case _NextScene:
				for (auto const& y : x.second->GetObjectGroup()) {
					auto pSwitch = new SwitchScene(std::atoi(y.second->GetProperty("sceneID").c_str()));
					pSwitch->SetSize(y.second->GetWidth(), y.second->GetHeight());
					pSwitch->SetPosition(y.second->GetX(), y.second->GetY());
					AddToGrid(pSwitch);
				}
				break;
			case _Stair:
				for (auto const& y : x.second->GetObjectGroup()) {
					Stair* stair = new Stair();
					stair->SetSize(y.second->GetWidth(), y.second->GetHeight());
					stair->SetPosition(y.second->GetX(), y.second->GetY());
					stair->SetDirection(std::atoi(y.second->GetProperty("dir").c_str()));
					AddToGrid(stair);
				}
				break;
			case _Candle:
				for (auto const& y : x.second->GetObjectGroup())
				{
					CCandle* candle = new CCandle();
					candle->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
					candle->SetItem(static_cast<EItem>(std::atoi(y.second->GetProperty("item").c_str())));
					AddToGrid(candle);
				}
				break;
			case _Platform:
				for (auto const& y : x.second->GetObjectGroup()) {
					CPlatform* platform = new CPlatform();
					platform->SetPosition(y.second->GetX(), y.second->GetY()-y.second->GetHeight());
					AddToGrid(platform);
				}
				break;
			case _BrickWall:
				for (auto const& y : x.second->GetObjectGroup()) {
					CBrickWall* brickwall = new CBrickWall();
					brickwall->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
					AddToGrid(brickwall);
				}
				break;     
			default:
				break;
			}
		}

		LoadSceneContent(rootNode);
	}
}


void PlayScene::OnDestroy()
{
	for (auto& x : objects)
	{
		delete x;
	}
}

void PlayScene::Update(DWORD dt)
{
	objects.clear();
	// We know that SIMON is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	while (!qObjects.empty()) {
		this->objects.push_back(qObjects.front());

		AddToGrid(qObjects.front());
		qObjects.pop();
	}
	grid->GetListobjectFromGrid(objects);
	vector<LPGAMEOBJECT> coObjects;
	coObjects.push_back(SIMON);
	for (int i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	SIMON-> Update(dt,this,&coObjects);
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, this, &coObjects);
	}


	// Update camera to follow SIMON
	float cx, cy;
	SIMON->GetPosition(cx, cy);

	cx -= SCREEN_WIDTH / 1.5;
	cy -= SCREEN_HEIGHT / 1.5;
	if (cx > this->cameraBorder.left && cx < this->cameraBorder.right - SCREENSIZE::WIDTH)
	{
		CGame::GetInstance()->SetCamPos(cx, this->cameraBorder.top /*cy*/);
	}



	if (switchScene) {
		this->currentMap = this->Maps.at(this->currentPScene->mapID);
		this->cameraBorder = this->pSceneBorders.at(this->currentPScene->border);

		switchScene = false;
	
		this->currentEntryPoints = this->entryPoints.at(this->currentPScene->entry);
		this->SIMON->SetPosition(currentEntryPoints.x, currentEntryPoints.y);
		this->SIMON->LastStepOnStairPos = { currentEntryPoints.x, currentEntryPoints.y };
		if (this->currentPScene->isRight)
		{
			CGame::GetInstance()->SetCamPos(cameraBorder.right-SCREENSIZE::WIDTH, cameraBorder.top);
		}
		else	CGame::GetInstance()->SetCamPos(cameraBorder.left, cameraBorder.top);
	}

	UpdateGrid();
	for (vector<LPGAMEOBJECT>::iterator it = objects.begin(); it != objects.end(); ) {

		if ((*it)->IsDestroy()) {
			if (dynamic_cast<Weapon*>(*it))
			{
				subWeapon--;
			}
			it = objects.erase(it);
			//delete* it;
		}
		else ++it;
	}


}

void PlayScene::Render()
{
	CGame* game = CGame::GetInstance();
	D3DXVECTOR2 cam = game->GetCamera();

	currentMap->Render(cam, cameraBorder);

	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();

	SIMON->Render();
	if (SIMON->GetState() == SIMONSTATE::ENTERENTRANCE)
	{
		currentMap->GetLayer("font")->Render(cam, cameraBorder);
		isEntrance = true;
	}


}

void PlayScene::OnKeyDown(int KeyCode)
{
	CGame* game = CGame::GetInstance();
	DebugOut(L"[INFO] PRESS KEY DOWN: %d\n", KeyCode);
	if (SIMON->GetState() == SIMONSTATE::ENTERENTRANCE
		|| SIMON->GetState() == SIMONSTATE::UPWHIP
		) return;
	switch (KeyCode)
	{
	case DIK_1:
		this->switchScene = true;
		this->currentPScene = this->pScenes.at(0);
		break;
	case DIK_2:
		this->switchScene = true;
		this->currentPScene = this->pScenes.at(1);
		break;
	case DIK_3:
		this->switchScene = true;
		this->currentPScene = this->pScenes.at(2);
			SIMON->SetState(SIMONSTATE::UP_STAIR_RIGHT);
			
		break;
	case DIK_4:
		this->switchScene = true;
		this->currentPScene = this->pScenes.at(3);
		break;
	case DIK_5:
		this->switchScene = true;
		this->currentPScene = this->pScenes.at(4);
		break;
	case DIK_6:
		this->switchScene = true;
		this->currentPScene = this->pScenes.at(5);
		break;
	case DIK_SPACE:
		if (SIMON->GetFightTime() == 0
			&& SIMON->GetState() != SIMONSTATE::JUMP
			&& SIMON->GetState() != SIMONSTATE::SIT
			&& (SIMON->isOnGround || SIMON->isOnPlatform)
			&& !SIMON->CheckIsOnStair()) {
			SIMON->SetState(SIMONSTATE::JUMP);
		}
		break;
	case DIK_F:
		if (SIMON->GetState() == SIMONSTATE::DOWN_STAIR_LEFT
			|| SIMON->GetState() == SIMONSTATE::DOWN_STAIR_RIGHT
			|| SIMON->GetState() == SIMONSTATE::UP_STAIR_LEFT
			|| SIMON->GetState() == SIMONSTATE::UP_STAIR_RIGHT)
		{
			return;
		}
		if (SIMON->GetFightTime() == 0)
		{
			if (game->IsKeyDown(DIK_UP)){
				if (SIMON->GetCurrentWeapon() != EWeapon::NONE && subWeapon < 1) {

					subWeapon++;
					SIMON->ResetSpawnWeapon();
					SIMON->SpawnWeapon(true);
				}
				else 
					SIMON->SpawnWeapon(false);
			}
			else 
				SIMON->SpawnWeapon(false);
			if (SIMON->CheckIsOnStair())
			{
				if (SIMON->CheckStepOnStairDirection() == STAIRDIRECTION::UPLEFT
					|| SIMON->CheckStepOnStairDirection() == STAIRDIRECTION::UPRIGHT
					&& SIMON->GetState() == SIMONSTATE::UP_STAIR_IDLE)
				{
					SIMON->SetState(SIMONSTATE::UP_STAIR_FIGHT);
				}
				else if (SIMON->CheckStepOnStairDirection() == STAIRDIRECTION::DOWNLEFT
					|| SIMON->CheckStepOnStairDirection() == STAIRDIRECTION::DOWNRIGHT
					&& SIMON->GetState() == SIMONSTATE::DOWN_STAIR_IDLE)
				{
					SIMON->SetState(SIMONSTATE::DOWN_STAIR_FIGHT);
				}
			}
			else {
				if (SIMON->GetState() != SIMONSTATE::SIT)
					SIMON->SetState(SIMONSTATE::FIGHT_STAND);
				else
					SIMON->SetState(SIMONSTATE::FIGHT_SIT);
			}
		}
		break;
	case DIK_A:
		SIMON->SetState(SIMONSTATE::IDLE);
		SIMON->SetPosition(50.0f, 0.0f);
		SIMON->SetSpeed(0, 0);
		break;
		

	}
}

void PlayScene::OnKeyUp(int KeyCode)
{
}

void PlayScene::KeyState(BYTE* states)
{

	CGame* game = CGame::GetInstance();

	if (SIMON->GetState() == SIMONSTATE::ENTERENTRANCE) return;
	

	if (SIMON->GetUpgradeTime() != 0 && GetTickCount() - SIMON->GetUpgradeTime() > SIMON_UPGRADE_WHIP_TIME) {
		SIMON->ResetUpgradeTime();
		SIMON->SetState(SIMONSTATE::IDLE);
	}
	if (SIMON->GetState() == SIMONSTATE::UPWHIP) return;
	if (SIMON->GetState() == SIMONSTATE::JUMP) return;
	if (SIMON->GetState() == SIMONSTATE::DEFLECT) return;
	if (SIMON->GetFightTime() != 0 && GetTickCount() - SIMON->GetFightTime() > SIMON_ATTACK_TIME)
	{
		SIMON->ResetAttack();
		if (SIMON->GetState()==SIMONSTATE::UP_STAIR_FIGHT )
		{
			SIMON->SetState(SIMONSTATE::UP_STAIR_IDLE);
		}
		if (SIMON->GetState() == SIMONSTATE::DOWN_STAIR_FIGHT)
		{
			SIMON->SetState(SIMONSTATE::DOWN_STAIR_IDLE);
		}

	}

	if (SIMON->GetFightTime() != 0)
	{
		return;
	}

	if (game->IsKeyDown(DIK_UP))
	{
			
		if (SIMON->GetState() == SIMONSTATE::DOWN_STAIR_IDLE) {


			if (SIMON->CheckStepOnStairDirection() == STAIRDIRECTION::DOWNLEFT)
				SIMON->SetStepOnStairDirection(STAIRDIRECTION::UPRIGHT);
			else if (SIMON->CheckStepOnStairDirection() == STAIRDIRECTION::DOWNRIGHT)
				SIMON->SetStepOnStairDirection(STAIRDIRECTION::UPLEFT);
			SIMON->SetStartStepOnStair();
			DebugOut(L"Simon up to down \n");
			return;
		}

		else if (SIMON->CheckCanStepUp()) {
			if (!SIMON->CheckIsOnStair() && SIMON->CheckCollideWithStair()) {
				SIMON->SetStartStepOnStair();
			}
			else if (SIMON->GetState() == SIMONSTATE::UP_STAIR_IDLE) {

				SIMON->SetStartStepOnStair();
			}
			return;
		}

	}
	else if (game->IsKeyDown(DIK_DOWN))
	{

		if (SIMON->GetState() == SIMONSTATE::UP_STAIR_IDLE) {
			if (SIMON->CheckStepOnStairDirection() == STAIRDIRECTION::UPRIGHT)
				SIMON->SetStepOnStairDirection(STAIRDIRECTION::DOWNLEFT);
			else if (SIMON->CheckStepOnStairDirection() == STAIRDIRECTION::UPLEFT) {
				SIMON->SetStepOnStairDirection(STAIRDIRECTION::DOWNRIGHT);
			}
			SIMON->SetStartStepOnStair();
			DebugOut(L"Simon up to down \n");
			return;
		}
		if (SIMON->CheckCanStepDown()) {
			if (!SIMON->CheckIsOnStair() && SIMON->CheckCollideWithStair()) {
				SIMON->SetStartStepOnStair();
			}
			else if (SIMON->GetState() == SIMONSTATE::DOWN_STAIR_IDLE) {
				SIMON->SetStartStepOnStair();
			}
			return;
		}

	}
	if (SIMON->CheckIsOnStair() || SIMON->CheckStairOnStair()) {
		return;
	}

	if (game->IsKeyDown(DIK_RIGHT))
	{
		SIMON->SetState(SIMONSTATE::WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		SIMON->SetState(SIMONSTATE::WALKING_LEFT);
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		SIMON->SetState(SIMONSTATE::SIT);
	}
	else
	{
		SIMON->SetState(SIMONSTATE::IDLE);
	}


}
