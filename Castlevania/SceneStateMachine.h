#pragma once
#include<unordered_map>
#include"Scene.h"
#include <memory>

class SceneStateMachine
{
	std::unordered_map<unsigned int, std::shared_ptr<Scene>> scenes;
	std::shared_ptr<Scene> curScene;
	unsigned int insertedSceneID;

public:
	SceneStateMachine() :scenes(0), curScene(0) { }
	void Update(DWORD deltaTime);
	void Render();

	unsigned int Add(std::shared_ptr<Scene> scene);

	void SwitchTo(unsigned int id);
	void Remove(unsigned int id); 

	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void KeyState(BYTE* states);

};

