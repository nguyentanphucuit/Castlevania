/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions: 
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox
		
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "SIMON.h"
#include "Brick.h"
#include "Goomba.h"

#include<rapidxml/rapidxml.hpp>
#include<rapidxml/rapidxml_utils.hpp> // Include các thư viện để đọc xml
#include"define.h"
#include"Map.h"
using namespace rapidxml; // namespace để dùng các thành phần trong thư viện rapid



CGame *game;

CSIMON *SIMON;
CGoomba *goomba;
Map* gameMap;
vector<LPGAMEOBJECT> objects;

class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] PRESS KEY DOWN: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		// ta cần kiểm tra
		//kiểm tra nếu trạng thái k phải jump thì mới cho jump
		if (SIMON->GetState() != SIMONSTATE::JUMP && SIMON->GetState()!=SIMONSTATE::SIT) { // ngooif thi k cho nhay
			SIMON->SetState(SIMONSTATE::JUMP);
		}		
		break;
	case DIK_A: // reset
		SIMON->SetState(SIMONSTATE::IDLE);
		SIMON->SetLevel(SIMON_LEVEL_BIG);
		SIMON->SetPosition(50.0f,0.0f);
		SIMON->SetSpeed(0, 0);
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{

	if (SIMON->GetState() == SIMONSTATE::JUMP) return;
	// nhay thi khong cho bam gi luon
	if (game->IsKeyDown(DIK_RIGHT)) // bắt phím mũi tên phải
	{
		SIMON->SetState(SIMONSTATE::WALKING_RIGHT); //đi phải

	}else if(game->IsKeyDown(DIK_LEFT))
	{
		SIMON->SetState(SIMONSTATE::WALKING_LEFT);
	}
	else if(game->IsKeyDown(DIK_DOWN) )
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

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and SIMON object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/



void LoadSprite(const std::string& filePath, const int tex)
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

void LoadAnimation(const string& filePath) 
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
		int timeLoop= std::atoi(child->first_attribute("timeLoop")->value());
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


void LoadResources()
{
	
	// chút mình load tẽ từ file luôn
	// thứ tự load : tex,sprite,ani , thay đổi=> lỗi
	CTextures * textures = CTextures::GetInstance();



	//textures->Add(ID_TEX_SIMON, L"GameContent\\Resource\\Simon\\SIMON.png",D3DCOLOR_XRGB(255, 255, 255));
	//textures->Add(ID_TEX_MISC, L"textures\\misc.png", D3DCOLOR_XRGB(176, 224, 248));
	//textures->Add(ID_TEX_ENEMY, L"textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));
	//textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));


	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	
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


	//
	LPANIMATION ani;

	
	ani = new CAnimation(100);		// brick
	ani->Add("GROUND_SPITE_01"); //bị trùng sprite của simon
	animations->Add("BRICK_ANI", ani);



	SIMON = new CSIMON();
	
	objects.push_back(SIMON);


	for (int i = 0; i < 30; i++)
	{
		CBrick *brick = new CBrick();
		brick->AddAnimation("BRICK_ANI");
		brick->SetPosition(0 + i*16.0f, 350);
		objects.push_back(brick);
	}

	// CHưa  thêm enemy xử lý simon trước
	//// and Goombas 
	//for (int i = 0; i < 4; i++)
	//{
	//	goomba = new CGoomba();
	//	goomba->AddAnimation(701);
	//	goomba->AddAnimation(702);
	//	goomba->SetPosition(200 + i*60, 135);
	//	goomba->SetState(GOOMBA_STATE_WALKING);
	//	objects.push_back(goomba);
	//}


	



}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that SIMON is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt,&coObjects);
	}


	// Update camera to follow SIMON
	float cx, cy;
	SIMON->GetPosition(cx, cy);

	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;

	CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
}

/*
	Render a frame 
*/


void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();
	D3DXVECTOR2 cam = game->GetCamera();
	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		gameMap->Render(cam);
		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREENSIZE::WIDTH, SCREENSIZE::HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}