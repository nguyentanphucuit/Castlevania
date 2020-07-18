#pragma once
#include<string>
#include<Windows.h>

#define GAME_TIME 300

class PlayScene;
class CSprite;
class Hud
{

	PlayScene* scene;
	int score;
	int playerHP;
	int playerEnergy;
	static int bossHP;
	int gameTime;
	int currentWeapon;
	int state;
	int p;
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

