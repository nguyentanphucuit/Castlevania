#pragma once
#include"Scene.h"
#include"Simon.h"
#include"Map.h"
class PlayScene:public Scene
{
    CSIMON* SIMON;
    vector<LPGAMEOBJECT> objects;
    Map* gameMap;
    void LoadSprite(const std::string& filePath, const int tex);
    void LoadAnimation(const string& filePath);
public:

    // overide nó dùng để kt xem mình truyền các parameter vào đúng kiểu
    // của hàm kế thừa k
    //oncreate ta dùng load resource
    void OnCreate() override;
    void OnDestroy() override;
    
    // như hàm update ở đây phải đúng kiểu ưord
    void Update(DWORD deltaTime) override;
    void Render() override;

     void OnKeyDown(int KeyCode) override;
     void OnKeyUp(int KeyCode) override;
     void KeyState(BYTE* states) override;
};

