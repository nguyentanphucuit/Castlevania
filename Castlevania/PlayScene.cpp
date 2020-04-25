#include "PlayScene.h"
#include "define.h"
#include "Game.h"
#include "Textures.h"
#include "Candle.h"
#include "Torch.h"
#include "HiddenObject.h"
#include "Ground.h"
#include "debug.h"
#include "WeaponFactory.h"
#include "HMoney.h"
#include "Entrance.h"
#include "RetroGrade.h"
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

	for (xml_node<>* child = rootNode->first_node(); child; child = child->next_sibling())
	{

		const std::string& ID = std::string(child->first_attribute("ID")->value());
		int timeLoop = std::atoi(child->first_attribute("timeLoop")->value());
		ani = new CAnimation(timeLoop);
		for (xml_node<>* grand = child->first_node(); grand; grand = grand->next_sibling())// lập thêm lần nữa lấy hết sprite id
		{
			const std::string& spriteID = std::string(grand->first_attribute("ID")->value());

			ani->Add(spriteID);
			//	DebugOut(L"ANI ID=%d sprite =%d \n", ID, spriteID);
		}

		animations->Add(ID, ani);


	}


}
D3DXVECTOR2 PlayScene::GetCamera()
{

	return CGame::GetInstance()->GetCamera();
}
void PlayScene::OnCreate()
{
	CTextures* textures = CTextures::GetInstance();

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	const std::string filePath = "GameContent\\Base.xml";

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

	xml_node<>* rootNode = doc.first_node("Base"); 
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
		idTex = std::atoi(child->first_attribute("idTex")->value());

		LoadSprite(path, idTex);
	}

	//load ani
	xml_node<>* aniNode = rootNode->first_node("animations");
	for (xml_node<>* child = aniNode->first_node(); child; child = child->next_sibling())
	{
		const std::string& path = std::string(child->first_attribute("path")->value());
		LoadAnimation(path);

	}

	gameMap = new Map();

	//load map
	xml_node<>* mapNode = rootNode->first_node("map");
	const std::string& path = std::string(mapNode->first_attribute("path")->value());
	gameMap->BuildMap(path);



	SIMON = new CSIMON();

	objects.push_back(SIMON);


	auto objectLayer = gameMap->GetObjectLayer();

	for (auto const& x : objectLayer)
	{
		DebugOut(L"ID= %d", static_cast<ObjLayer>(x.first));
		switch (static_cast<ObjLayer>(x.first))
		{

		case ObjLayer::PlayerPos:
			for (auto const& y : x.second->GetObjectGroup())
			{
				SIMON->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
			}
			break;

		case ObjLayer::Torch:
			for (auto const& y : x.second->GetObjectGroup())
			{
				CTorch* torch = new CTorch();

				torch->SetPosition(y.second->GetX(), y.second->GetY() - y.second->GetHeight());
				torch->SetItem(static_cast<EItem>(y.second->GetProperty("item")));
				objects.push_back(torch);
			}
			break;

		case ObjLayer::Camera:
			for (auto const& y : x.second->GetObjectGroup())
			{
				this->cameraBoder.left = y.second->GetX();
				this->cameraBoder.top = y.second->GetX();
				this->cameraBoder.right = y.second->GetX() + y.second->GetWidth();
				this->cameraBoder.bottom = y.second->GetY() + y.second->GetHeight();

			}
			break;
		case ObjLayer::Ground:
			for (auto const& y : x.second->GetObjectGroup())
			{
				HiddenObject* ground = new Ground();
				ground->SetPosition(y.second->GetX(), y.second->GetY());
				ground->SetSize(y.second->GetWidth(), y.second->GetHeight());
				objects.push_back(ground);
			}
			break;
		case ObjLayer::HMoney:
			for (auto const& y : x.second->GetObjectGroup()) {
				HMoney* hMoney = new HMoney();
				hMoney->SetPosition(y.second->GetX(), y.second->GetY());
				hMoney->SetSize(y.second->GetWidth(), y.second->GetHeight());
				auto moneyLayer = objectLayer.at(11);
				for (auto const& child : moneyLayer->GetObjectGroup()) {
					auto moneyItem = ItemFactory::SpawnItem<Item*>(EItem::MONEY);
					moneyItem->SetPosition(child.second->GetX(), child.second->GetY() - child.second->GetHeight());
					hMoney->SetItem(moneyItem);
				}
				objects.push_back(hMoney);
			}
			break;
		case ObjLayer::Entrance:
			for (auto const& y : x.second->GetObjectGroup()) {
				Entrance* entrance = new Entrance();
				entrance->SetSize(y.second->GetWidth(), y.second->GetHeight());
				entrance->SetPosition(y.second->GetX(), y.second->GetY());
				objects.push_back(entrance);
			}
			break;
		case ObjLayer::CheckRetrograde:
			for (auto const& y : x.second->GetObjectGroup()) {
				RetroGrade* retroGrade = new RetroGrade();
				retroGrade->SetSize(y.second->GetWidth(), y.second->GetHeight());
				retroGrade->SetPosition(y.second->GetX(), y.second->GetY());
				objects.push_back(retroGrade);
			}
		default:
			break;
		}
	}

	CGame::GetInstance()->SetCamPos(0, 0);
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
	// We know that SIMON is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	while (!qObjects.empty()){
		this->objects.push_back(qObjects.front());
		qObjects.pop();
	}

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, this, &coObjects);
	}


	// Update camera to follow SIMON
	float cx, cy;
	SIMON->GetPosition(cx, cy);

	cx -= SCREEN_WIDTH / 1.5;
	cy -= SCREEN_HEIGHT / 1.5;
	if (cx > this->cameraBoder.left && cx < this->cameraBoder.right - SCREENSIZE::WIDTH)
	{
		CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
	}

	for (vector<LPGAMEOBJECT>::iterator it = objects.begin(); it != objects.end(); ) {

		if ((*it)->IsDestroy()) {
			if (dynamic_cast<WDagger*>(*it))
			{
				subWeapon--;
			}
			it = objects.erase(it);
		}
		else ++it;
	}



}

void PlayScene::Render()
{
	CGame* game = CGame::GetInstance();
	D3DXVECTOR2 cam = game->GetCamera();
	gameMap->Render(cam);

	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();

	SIMON->Render();
	if (SIMON->GetState() == SIMONSTATE::ENTERENTRANCE)
	{
		gameMap->GetLayer("font")->Render(cam);
		isEntrance = true;
	}


}

void PlayScene::OnKeyDown(int KeyCode)
{
	CGame* game = CGame::GetInstance();

	DebugOut(L"[INFO] PRESS KEY DOWN: %d\n", KeyCode);
	if (isEntrance || SIMON->GetState() == SIMONSTATE::UPWHIP ) return;
	switch (KeyCode)
	{
	case DIK_SPACE:
		if (SIMON->GetFightTime() == 0 
			&& SIMON->GetState() != SIMONSTATE::JUMP
			&& SIMON->GetState() != SIMONSTATE::SIT
			&& SIMON->isOnGround){
			SIMON->SetState(SIMONSTATE::JUMP);
		}
		break;
	case DIK_F:
		if (SIMON->GetFightTime() == 0) 
		{
			if (game->IsKeyDown(DIK_UP))
			{
				if (SIMON->GetCurrentWeapon() != EWeapon::NONE && subWeapon < 1) {

					subWeapon++;

					SIMON->ResetSpawnWeapon();
					SIMON->SpawnWeapon(true);
					if (SIMON->GetState() != SIMONSTATE::SIT) {
						SIMON->SetState(SIMONSTATE::FIGHT_STAND);
					}
					else {
						SIMON->SetState(SIMONSTATE::FIGHT_SIT);
					}
				}
				else
				{
					SIMON->SpawnWeapon(false);
					if (SIMON->GetState() != SIMONSTATE::SIT) 
					{
						SIMON->SetState(SIMONSTATE::FIGHT_STAND);
					}
					else
					{
						SIMON->SetState(SIMONSTATE::FIGHT_SIT);
					}
				}

			}
			else
			{
				SIMON->SpawnWeapon(false);
				if (SIMON->GetState() != SIMONSTATE::SIT) 
				{
					SIMON->SetState(SIMONSTATE::FIGHT_STAND);
				}
				else
				{
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
	if (SIMON->GetState() == SIMONSTATE::RETROGRADE) return;
	if (SIMON->GetFightTime() != 0 && GetTickCount() - SIMON->GetFightTime() > SIMON_ATTACK_TIME)
	{
		SIMON->ResetAttack();

	}

	if (SIMON->GetFightTime() != 0) 
	{
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
