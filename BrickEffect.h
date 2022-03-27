#pragma once
#include "GameObject.h"
#include "Sprite.h"

#define BRICK_EFFECT_SPRITE_ID 20300 

#define BRICK_EFFECT_STATE_APPEAR 100
#define BRICK_EFFECT_STATE_INACTIVE 200

#define BRICK_EFFECT_SPEED_VX 0.001f
#define BRICK_EFFECT_SPEED_VY1 0.003f
#define BRICK_EFFECT_SPEED_VY2 0.005f

#define BRICK_EFFECT_APPEAR_TIME 1500

#define BRICK_EFFECT_GRAVITY	0.0002f;
class CBrickEffect : public CGameObject
{
	ULONGLONG appear_start;
	float x1, x2, y1, y2, vy1, vy2;
	vector<LPSPRITE> effectSprite;
	

	virtual int IsBlocking() { return 0; }
public:
	CBrickEffect(float x, float y);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
};