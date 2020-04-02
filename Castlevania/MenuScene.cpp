#include "MenuScene.h"
#include "Game.h"
void MenuScene::SetSwitchToScene(unsigned int id)
{
	this->switchToState = id;
}

void MenuScene::OnCreate()
{
}

void MenuScene::OnDestroy()
{
}

void MenuScene::Update(DWORD deltaTime)
{
}

void MenuScene::Render()
{
}

void MenuScene::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
		// bấm space để chuyển scene
	case DIK_SPACE: {
		this->sceneStateMachine.SwitchTo(this->switchToState);
		break;
	}
	default:
		break;
	}
}

void MenuScene::OnKeyUp(int KeyCode)
{
}

void MenuScene::KeyState(BYTE* states)
{
}
