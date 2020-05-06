#pragma once
#include "Scene.h"
#include "Simon.h"
#include "Map.h"
#include <queue>

class PlayScene:public Scene
{
    RECT cameraBoder;
    CSIMON* SIMON;
    vector<LPGAMEOBJECT> objects;

    Map* Maps;

    void LoadSprite(const std::string& filePath, const int tex);
    void LoadAnimation(const string& filePath);

    std::queue<LPGAMEOBJECT> qObjects;

   
    int subWeapon = 0;
    bool isEntrance = false;
public:

    D3DXVECTOR2 GetCamera();
    void SpawnObject(LPGAMEOBJECT obj) { this->qObjects.push(obj); }

    void OnCreate() override;
    void OnDestroy() override;
    
    
    void Update(DWORD deltaTime) override;
    void Render() override;

    void OnKeyDown(int KeyCode) override;
    void OnKeyUp(int KeyCode) override;
    void KeyState(BYTE* states) override;
};

