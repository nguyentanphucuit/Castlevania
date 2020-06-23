#pragma once
#include<string>
#include<Windows.h>
class PlayScene;
class CSprite;
class Hud
{

	PlayScene* scene;
	int score;
	int playerHP;
	int playerEnery;
	static int bossHP;
	int gameTime;
	int currentWeapon;
	int state;
	RECT bound;
	std::string  _UIinfor;
public:
	static void SetBossHp(int hp) { bossHP = hp; }
	void setState(int state) {
		this->state = state;
	}
	void Update();
	
	void Render();
	Hud(PlayScene* scene);
	~Hud();
};

