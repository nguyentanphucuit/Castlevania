#pragma once
#include<Windows.h>

class Scene
{
public:
	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;


	virtual void Update(DWORD deltaTime) {};
	virtual void Render() {};

	virtual void OnKeyDown(int KeyCode) {};
	virtual void OnKeyUp(int KeyCode) {};
	virtual void  KeyState(BYTE* states) {};

};

