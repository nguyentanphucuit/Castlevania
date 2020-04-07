#include "PlayScene.h"
#include "define.h"
#include"Game.h"
#include"Textures.h"
#include "Candle.h"
#include "Torch.h"
#include"HiddenObject.h"
#include"Ground.h"
#include"debug.h"
void PlayScene::LoadSprite(const std::string& filePath, const int tex)
{
	// ở đây mình truyền vào man
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();


	LPDIRECT3DTEXTURE9 objecttex = textures->Get(tex);
	// đọc vào file xml
	char* fileLoc = new char[filePath.size() + 1]; // filepath lưu đường dẫn đến file XML đang đọc
#



	   //TODO: make multi format version of string copy
	// phần này k quan tâm lắm dạng như cú pháp thôi
#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, filePath.size() + 1, filePath.c_str());
#endif 

	//TODO: error checking - check file exists before attempting open.
	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	// truy vấn node trong file dùng xml_node<>* 
	xml_node<>* rootNode = doc.first_node("gamedata"); //rootnode là node đầu tiên ở đây là "gamedata"

	////à ví dụ đọc vào node sprite đầu tiên
	//xml_node<>* spriteNode = rootNode->first_node("sprite");

	//// đọc ở đây man. đây hả um đọc node lên game thôi man code đọc node lên game ấy

	//xml_node<>* frameNode = spriteNode->first_node("frame");

	// cách đọc thuộc tính của node vd như thằng id của node sprite


	//std::string Id = std::string(spriteNode->first_attribute("ID")->value()); // đọc attibute thì dùng node->first_attribute("name")

	//// quăng ra debug luôn
	//std::wstring cover = std::wstring(Id.begin(), Id.end()); 
	//DebugOut(L"ID= %s", cover.c_str()); //%s truyền biến kiểu string, %d kiểu int, %f kiểu float






	// lập toàn bộ các node con của node gamedata

	for (xml_node<>* child = rootNode->first_node(); child; child = child->next_sibling()) //cú pháp lập
	{
		// lấy ra id của sprite
		const std::string& ID = std::string(child->first_attribute("ID")->value());
		// truy vấn vào node frame
		xml_node<>* frameNode = child->first_node("frame");

		// std::string đọc lên kiểu string
		//std::atoi đọc lên kiểu int
		//std::atof đọc lên kiểu float


		int l = std::atoi(frameNode->first_attribute("l")->value());
		int t = std::atoi(frameNode->first_attribute("t")->value());
		int r = std::atoi(frameNode->first_attribute("r")->value());
		int b = std::atoi(frameNode->first_attribute("b")->value());


		/*	std::wstring cover = std::wstring(ID.begin(), ID.end());


			DebugOut(L" ID= %s, l=%d, t=%d , r=%d , b=%d \n", cover.c_str(),l,t,r,b);*/
			//	DebugOut(L" ID= %d, l=%d, t=%d , r=%d , b=%d \n", ID, l, t, r, b);
		sprites->Add(ID, l, t, r, b, objecttex);
	}




}
void PlayScene::LoadAnimation(const string& filePath)
{
	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani;

	char* fileLoc = new char[filePath.size() + 1]; // filepath lưu đường dẫn đến file XML đang đọc
#
	   //TODO: make multi format version of string copy
	// phần này k quan tâm lắm dạng như cú pháp thôi
#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, filePath.size() + 1, filePath.c_str());
#endif 

	//TODO: error checking - check file exists before attempting open.
	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	// truy vấn node trong file dùng xml_node<>* 
	xml_node<>* rootNode = doc.first_node("gamedata"); //rootnode là node đầu tiên ở đây là "gamedata"

	for (xml_node<>* child = rootNode->first_node(); child; child = child->next_sibling())
	{

		const std::string& ID = std::string(child->first_attribute("ID")->value());
		int timeLoop = std::atoi(child->first_attribute("timeLoop")->value());
		ani = new CAnimation(timeLoop);	// idle big right
		for (xml_node<>* grand = child->first_node(); grand; grand = grand->next_sibling())// lập thêm lần nữa lấy hết sprite id
		{
			const std::string& spriteID = std::string(grand->first_attribute("ID")->value());

			ani->Add(spriteID);
			//	DebugOut(L"ANI ID=%d sprite =%d \n", ID, spriteID);
		}

		animations->Add(ID, ani);


	}


}
void PlayScene::OnCreate()
{
	// chút mình load tẽ từ file luôn
	// thứ tự load : tex,sprite,ani , thay đổi=> lỗi
	CTextures* textures = CTextures::GetInstance();



	//textures->Add(ID_TEX_SIMON, L"GameContent\\Resource\\Simon\\SIMON.png",D3DCOLOR_XRGB(255, 255, 255));
	//textures->Add(ID_TEX_MISC, L"textures\\misc.png", D3DCOLOR_XRGB(176, 224, 248));
	//textures->Add(ID_TEX_ENEMY, L"textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));
	//textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));


	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	// load từ đây nha man, nữa tex mình cũng viết thêm hàm load như load sprite


	const std::string filePath = "GameContent\\Base.xml";

	// cú pháp load file
	// đọc vào file xml
	char* fileLoc = new char[filePath.size() + 1]; // filepath lưu đường dẫn đến file XML đang đọc
#
	   //TODO: make multi format version of string copy
	// phần này k quan tâm lắm dạng như cú pháp thôi
#ifdef MACOS
	strlcpy(fileLoc, file.c_str(), file.size() + 1);
#else
	strcpy_s(fileLoc, filePath.size() + 1, filePath.c_str());
#endif 

	//TODO: error checking - check file exists before attempting open.
	rapidxml::file<> xmlFile(fileLoc);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	// truy vấn node trong file dùng xml_node<>* 
	xml_node<>* rootNode = doc.first_node("Base"); //rootnode là node đầu tiên ở đây là "gamedata"

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


	xml_node<>* spriteNode = rootNode->first_node("sprites"); // tex voi ani chua dung man, dung trc sprite da
//	xml_node<>* objNode = spriteNode->first_node("objectSprite");
	//load sprite
	for (xml_node<>* child = spriteNode->first_node(); child; child = child->next_sibling()) //cú pháp lập
	{
		// duyệtt	
		//mình load từ file lên mà man. 
		// load path và idtex lên truyền vào loadsprite
		int idTex;
		// nhớ ép kiểu
		const std::string& path = std::string(child->first_attribute("path")->value());
		idTex = std::atoi(child->first_attribute("idTex")->value());

		LoadSprite(path, idTex);

	}
	// h mình load file base lên rồi load node sprites trong base
	//để lấy đường dẫn sprite của object rồi truyền vào hàm load sprite
	// mục đính là dùng vòng lập load tâtts cả các sprite của object luôn


	//load ani
	xml_node<>* aniNode = rootNode->first_node("animations");
	for (xml_node<>* child = aniNode->first_node(); child; child = child->next_sibling())
	{
		const std::string& path = std::string(child->first_attribute("path")->value());
		LoadAnimation(path);

	}


	//file here
	gameMap = new Map();
	//load map
	xml_node<>* mapNode = rootNode->first_node("map");
	const std::string& path = std::string(mapNode->first_attribute("path")->value());
	gameMap->BuildMap(path);





	SIMON = new CSIMON();

	objects.push_back(SIMON);




	for (auto const& x : gameMap->GetObjectLayer())
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
			break; //lol

		case ObjLayer::Camera:
			for (auto const& y : x.second->GetObjectGroup())
			{
				this->cameraBoder.left = y.second->GetX();
				this->cameraBoder.top = y.second->GetX();
				this->cameraBoder.right = y.second->GetX()+y.second->GetWidth();
				this->cameraBoder.bottom = y.second->GetY()+y.second->GetHeight();
					
			}
			break; //lol
		case ObjLayer::Ground:
			for (auto const& y : x.second->GetObjectGroup())
			{
				HiddenObject* ground = new Ground();
				// với loại object vẽ bằng hình chữ nhật 
				// không - y.second->GetHeight()
				ground->SetPosition(y.second->GetX(), y.second->GetY());
				ground->SetSize(y.second->GetWidth(), y.second->GetHeight());
				objects.push_back(ground);
			}
			break;
		default:
			break;
		}
	}




	CGame::GetInstance()->SetCamPos(0, 0);
}

// dọn rác
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

	/// Thêm các object trong hàng đợi vào ds object

	while (!qObjects.empty()) // lập nếu queue còn phần tử
	{
		this->objects.push_back(qObjects.front());
		qObjects.pop();// thêm vào object rồi thì xóa object vừa thêm khỏi queue
	}

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	/// truyền playscene vào hàm update của các object
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt,this, &coObjects);
	}


	// Update camera to follow SIMON
	float cx, cy;
	SIMON->GetPosition(cx, cy);

	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;
	if (cx> this->cameraBoder.left && cx<this->cameraBoder.right- SCREENSIZE::WIDTH)
	{
		CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
	}
	
}

void PlayScene::Render()
{
	CGame* game = CGame::GetInstance();
	D3DXVECTOR2 cam = game->GetCamera();
	gameMap->Render(cam);
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	SIMON->Render();// vẽ simon lên trên tất cả object

}

void PlayScene::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] PRESS KEY DOWN: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		// ta cần kiểm tra
		//kiểm tra nếu trạng thái k phải jump thì mới cho jump
		if (SIMON->GetFightTime() == 0 // k phải đang đánh mới cho nhảy
			&& SIMON->GetState() != SIMONSTATE::JUMP
			&& SIMON->GetState() != SIMONSTATE::SIT) { // ngooif thi k cho nhay
			SIMON->SetState(SIMONSTATE::JUMP);
		}
		break;
	case DIK_K:
		if (SIMON->GetFightTime() == 0) // không đánh mới cho đánh tránh trường hợp chưa đánh xong đã đánh lại
		{
			if (SIMON->GetState() != SIMONSTATE::SIT) // 
			{
				SIMON->SetState(SIMONSTATE::FIGHT_STAND);
			}
			else
			{
				SIMON->SetState(SIMONSTATE::FIGHT_SIT);
			}
		}
		break;
	case DIK_A: // reset
		SIMON->SetState(SIMONSTATE::IDLE);
		SIMON->SetLevel(SIMON_LEVEL_BIG);
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
	if (SIMON->GetState() == SIMONSTATE::JUMP) return;
	if (SIMON->GetFightTime() != 0 && GetTickCount() - SIMON->GetFightTime() > SIMON_ATTACT_TIME)
	{
		//reset chỗ này
		SIMON->ResetAttack();

	}

	if (SIMON->GetFightTime() != 0) // còn đánh thì return tránh trường hợp bị set lại state là idle
	{
		return;
	}

	// nhay thi khong cho bam gi luon
	if (game->IsKeyDown(DIK_RIGHT)) // bắt phím mũi tên phải
	{
		SIMON->SetState(SIMONSTATE::WALKING_RIGHT); //đi phải

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

	// disable control key when SIMON die 
	/*if (SIMON->GetState() == SIMON_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
		SIMON->SetState(SIMON_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		SIMON->SetState(SIMON_STATE_WALKING_LEFT);
	else
		SIMON->SetState(SIMON_STATE_IDLE);*/
}
