#pragma once
#include "SceneStateMachine.h"
#include "Scene.h"
class MenuScene:public Scene
{
private:
	unsigned int switchToState;
	SceneStateMachine& sceneStateMachine;
public:
	MenuScene(SceneStateMachine& sceneStateMachine) :sceneStateMachine(sceneStateMachine), switchToState(0) {};
	void SetSwitchToScene(unsigned int id);

    void OnCreate() override;
    void OnDestroy() override;


    void Update(DWORD deltaTime) override;
    void Render() override;

    void OnKeyDown(int KeyCode) override;
    void OnKeyUp(int KeyCode) override;
    void KeyState(BYTE* states) override;

};

