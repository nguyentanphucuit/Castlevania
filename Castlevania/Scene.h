#pragma once
#include<Windows.h>
///
///abtrack class dùng để kế thừa
class Scene
{
public:
	//dùng thay thế cho controctor mấy lớp kế  thừa
	virtual void OnCreate() = 0;
	//dùng thay thế cho distractor mấy lớp kế  thừa
	virtual void OnDestroy() = 0;


	virtual void Update(DWORD deltaTime) {};
	virtual void Render() {};

	//dùng để bắt phím của từng scene k bắt từ hàm main
	virtual void OnKeyDown(int KeyCode) {};
	virtual void OnKeyUp(int KeyCode) {};
	virtual void  KeyState(BYTE* states) {};



};

