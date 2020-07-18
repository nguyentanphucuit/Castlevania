#pragma once
#include "Scene.h"
#include "Simon.h"
#include "Whip.h"
#include "Map.h"
#include <queue>
#include "Grid.h"
#include "Hud.h"
#include"rapidxml/rapidxml_print.hpp"
#include"rapidxml/rapidxml.hpp"
#include"rapidxml/rapidxml_utils.hpp"

#define CROSS_EFFECT_TIME 500

class Phantom;
class Enemy;
struct pScene {
    int id;
    int mapID;
    std::string border;
    std::string entry;
    bool isRight = false;
    int state;
};
class PlayScene:public Scene
{
    RECT cameraBorder;
    CSIMON* SIMON;
    Grid* grid;
    
    vector<LPGAMEOBJECT> objects;
    Hud* hud;
    void LoadSprite(const std::string& filePath, const int tex);
    void LoadAnimation(const string& filePath);
    void LoadSceneContent(xml_node<>* root);
    void LoadGrid();

  
    std::queue<LPGAMEOBJECT> qObjects;

    std::unordered_map<int, Map*> Maps;
  
    Map* currentMap;

    std::map<int, pScene*> pScenes;
    pScene* currentPScene;

    ShotState shotState;
    int numShot;

   
    D3DXVECTOR2 currentEntryPoints;
    int subWeapon = 0;
    bool isEntrance = false;
    bool switchScene = false;
    bool isAttack = false;
    unsigned int time = 300;
    DWORD timeCounter = 0;
    DWORD revival = 0;
    bool playCrossEffect = false;
    DWORD cross_start = 0;
    void GetListobjectFromGrid();
    void UpdateGrid();
    void GameTimeCounter();
public:
    Phantom* boss;
    std::unordered_map<std::string, D3DXVECTOR2> entryPoints;
    std::unordered_map<std::string, RECT> pSceneBorders;
    bool PauseCam = false;
    bool aniSubWeapon = false;
    vector<Enemy*> enemies;

    void KillAllEnemies();
    unsigned int GetTime() {
        return this->time;
    }
    void Motionless(bool flag);
    D3DXVECTOR2 GetCamera();
    bool IsAttack() { return isAttack; };
    int GetNumObj() { return this->objects.size(); };
    CSIMON* GetSimon() { return this->SIMON; };
    int GetCurrentSceneID() { return this->currentPScene->id; }
    void SwitchPScene(int sceneID) {
        this->currentPScene = this->pScenes.at(sceneID);
        this->switchScene = true;
    }

    void HandleCrossEffect();
    bool CheckPlayCrossEffect() {
        return this->playCrossEffect;
    };
   

    void SpawnObject(LPGAMEOBJECT obj) { this->qObjects.push(obj); }

    void OnCreate() override;
    void OnDestroy() override;

    void MotionlessEnemy(bool flag);
    
    void Update(DWORD deltaTime) override;
    void Render() override;

    void OnKeyDown(int KeyCode) override;
    void OnKeyUp(int KeyCode) override;
    void KeyState(BYTE* states) override;

};

