#include "Hud.h"
#include"PlayScene.h"
#include"WeaponFactory.h"
#include"Game.h"
int Hud::bossHP = 0;
void Hud::Update()
{
	this->playerEnergy = scene->GetSimon()->GetEnergy();
	string energy = playerEnergy < 10 ? "0" + std::to_string(playerEnergy) : std::to_string(playerEnergy);
	this->playerHP = scene->GetSimon()->GetHp();

	unsigned int score_ =00000;
	string score;
	if (score_ < 10)
	{
		score = "00000" + std::to_string(score_);
	}
	else if (score_ < 100)
	{
		score = "0000" + std::to_string(score_);
	}
	else if (score_ < 1000) {
		score = "000" + std::to_string(score_);
	}
	else if (score_ < 10000)
	{
		score = "00" + std::to_string(score_);
	}
	else if (score_ < 100000)
	{
		score = "0" + std::to_string(score_);
	}
	else {
		score = std::to_string(score_);
	}


	_UIinfor = "SCORE-" + score + " TIME 0" +  + " STAGE 0" + std::to_string(this->state) + "\n";
	_UIinfor = _UIinfor + "PLAYER                  -" + energy + "\n";
	_UIinfor += "ENEMY                   -02\n";
}

void Hud::Render()
{
	CSprites::GetInstance()->Get("BLACKBOARD_UI_SPRITE")->DrawUI( 290, 32, 255);
	switch (scene->GetSimon()->GetCurrentWeapon())
	{
	case EWeapon::AXE:{

		CSprites::GetInstance()->Get("AXE_UI_SPRITE")->DrawUI(305, 39, 255);
		break;
	}
	case  EWeapon::DAGGER: {
		CSprites::GetInstance()->Get("KNIFE_UI_SPRITE")->DrawUI( 300, 40, 255);
		break;
	}
	case  EWeapon::FIREBOMB: {
		CSprites::GetInstance()->Get("HOLY_WATER_UI_SPRITE")->DrawUI( 305, 35, 255);
		break;
	}
	case  EWeapon::STOPWATCH: {
		CSprites::GetInstance()->Get("STOP_WATCH_UI_SPRITE")->DrawUI(305, 35, 255);
		break;
	}
	case  EWeapon::BOOMERANG: {
		CSprites::GetInstance()->Get("BOOMERANG_UI_SPRITE")->DrawUI(305, 35, 255);
		break;
	}
	}


	CGame::GetInstance()->DrawUIText(this->_UIinfor, bound);
	for (size_t i = 0; i < this->playerHP; i++)
	{
		CSprites::GetInstance()->Get("PLAYER_HP_SPRITE")->DrawUI( 105 + i * 9, 32, 255);

	}
	for (size_t i = 0; i < bossHP; i++)
	{
		CSprites::GetInstance()->Get("BOSS_HP_SPRITE")->DrawUI( 105 + i * 9, 50, 255);
	}
	for (size_t i = this->playerHP; i < 16; i++)
	{
		CSprites::GetInstance()->Get("NOHP_UI_SPRITE")->DrawUI( 105 + i * 9, 32, 255);
	}
	for (size_t i = this->bossHP; i < 16; i++)
	{
		CSprites::GetInstance()->Get("NOHP_UI_SPRITE")->DrawUI( 105 + i * 9, 50, 255);
	}




}

Hud::Hud(PlayScene* scene)
{
	this->scene = scene;
	SetRect(&bound, 0, 15, SCREENSIZE::WIDTH, 80);
	this->bossHP = 16;
	this->state = 1;

	_UIinfor = "SCORE-000000 TIME 0000 STAGE 0" + std::to_string(this->state) + "\n";
	_UIinfor += "PLAYER                  -00\n";
	_UIinfor += "ENEMY                   -00\n";
}


Hud::~Hud()
{

}
