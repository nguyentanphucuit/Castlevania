#pragma once
#include "SceneStateMachine.h"
#include "Scene.h"
class MenuScene:public Scene
{
private:
	// lưu scene muốn chuyển đến
	unsigned int switchToState;
	//dùng để gọi sceneStateMachine.switchto để chuyển sang scene khác
	// dấu & ở đâu là tham chiếu tức là nếu sceneStateMachine bị thay đổi
	// thì biến truyền vào cũng bị thay đổi theo
	SceneStateMachine& sceneStateMachine;// 
public:
	MenuScene(SceneStateMachine& sceneStateMachine) :sceneStateMachine(sceneStateMachine), switchToState(0) {};
	void SetSwitchToScene(unsigned int id);//set scene muốn chuyển đến


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

