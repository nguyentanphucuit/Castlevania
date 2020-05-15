#pragma once
#include "Scene.h"
#include "Simon.h"
#include "Map.h"
#include <queue>

struct pScene {
    int id;
    int mapID;
    std::string border;
    std::string entry;
};
class PlayScene:public Scene
{
    RECT cameraBorder;
    CSIMON* SIMON;
    vector<LPGAMEOBJECT> objects;

    void LoadSprite(const std::string& filePath, const int tex);
    void LoadAnimation(const string& filePath);
    void LoadSceneContent(xml_node<>* root);

    std::queue<LPGAMEOBJECT> qObjects;

    std::unordered_map<int, Map*> Maps;
    std::unordered_map<std::string, RECT> pSceneBorders;
    Map* currentMap;

    std::map<int, pScene*> pScenes;
    pScene* currentPScene;

    std::unordered_map<std::string, D3DXVECTOR2> entryPoints;
    D3DXVECTOR2 currentEntryPoints;
   
    int subWeapon = 0;
    bool isEntrance = false;
    bool switchScene = false;
public:

    D3DXVECTOR2 GetCamera();

    int GetNumObj() { return this->objects.size(); };
    CSIMON* GetSimon() { return this->SIMON; };
    int GetCurrentSceneID() { return this->currentPScene->id; }
    void SwitchPScene(int sceneID) {
        this->currentPScene = this->pScenes.at(sceneID);
        this->switchScene = true;
    }


    void SpawnObject(LPGAMEOBJECT obj) { this->qObjects.push(obj); }

    void OnCreate() override;
    void OnDestroy() override;
    
    
    void Update(DWORD deltaTime) override;
    void Render() override;

    void OnKeyDown(int KeyCode) override;
    void OnKeyUp(int KeyCode) override;
    void KeyState(BYTE* states) override;
};

