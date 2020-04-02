#pragma once
#include<unordered_map>
#include"Scene.h"
#include <memory>
/// Quản lý các scene
class SceneStateMachine
{
	// lưu toàn bộ các scene của game
	//shared_ptr con trỏ thông minh dùng nó khỏi phải delete nó tự
	// dọn rác
	std::unordered_map<unsigned int, std::shared_ptr<Scene>> scenes;

	// lưu scene hiện tại đang hoạt động
	std::shared_ptr<Scene> curScene;


	// lưu id scene vừa thêm vào, tăng dần theo số scene hiện có
	unsigned int insertedSceneID;

public:
	SceneStateMachine() :scenes(0), curScene(0) { }
	void Update(DWORD deltaTime);
	void Render();
	// thêm 1 scene mới vào ds scene
	unsigned int Add(std::shared_ptr<Scene> scene);
	// chuyển đến scene
	void SwitchTo(unsigned int id);
	// loại bỏ scene
	void Remove(unsigned int id); 

//gọi các sự kiện phím của scene đang dùng
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void KeyState(BYTE* states);

};

