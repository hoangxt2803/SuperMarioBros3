#pragma once
#include "GameObject.h"
#define END_GAME_EFFECT_VY 0.1f

#define END_GAME_EFFECT_BBOX_WIDTH 16
#define END_GAME_EFFECT_BBOX_HEIGHT 16

#define ID_ANI_END_GAME_EFFECT_MUSHROOM 7200
#define ID_ANI_END_GAME_EFFECT_FIRE_FLOWER 7201
#define ID_ANI_END_GAME_EFFECT_STAR 7202

class CEndGameEffect : public CGameObject
{
	bool isCollected;
	int number;
	ULONGLONG number_start;
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
public:
	CEndGameEffect(float x, float y);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetIsCollected(bool value) { this->isCollected = value; }
}; 
