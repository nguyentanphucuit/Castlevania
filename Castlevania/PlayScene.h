#pragma once
#include "Scene.h"
#include "Simon.h"
#include "Map.h"
#include <queue>
class PlayScene:public Scene
{
    RECT cameraBoder;// giới hạn vùng hiển thị cam
    CSIMON* SIMON;
    vector<LPGAMEOBJECT> objects;
    Map* gameMap;
    void LoadSprite(const std::string& filePath, const int tex);
    void LoadAnimation(const string& filePath);
    // lưu những object vừa thêm vào ở lần upload hiện tại vào hàng đợi
    // sẽ thêm vào ds objects ở lần cập nhật tiếp theo
    std::queue<LPGAMEOBJECT> qObjects;
public:

    D3DXVECTOR2 GetCamera();
    void SpawnObject(LPGAMEOBJECT obj) { this->qObjects.push(obj); }
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

