#include "BrickEffect.h"
#include "Sprites.h"
CBrickEffect::CBrickEffect(float x, float y) {
	this->x = x1 = x2 = x;
	this->y = y1 = y2 = y;
	CSprites* sprites = CSprites::GetInstance();
	for (int i = 0; i < 4; i++) {
		effectSprite.push_back(sprites->Get(BRICK_EFFECT_SPRITE_ID));
	}
	state = BRICK_EFFECT_STATE_APPEAR;
	appear_start = GetTickCount64();

	SetState(BRICK_EFFECT_STATE_APPEAR);
}

void CBrickEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == BRICK_EFFECT_STATE_INACTIVE)
		return;
	float dy1, dy2;
	dy1 = vy1 * dt;
	dy2 = vy2 * dt;
	x1 += 2;
	x2 -= 2;
	y1 += dy1;
	y2 += dy2;
	/*vy1 += dt * BROKEN_BRICK_EFFECT_GRAVITY;
	vy2 += dt * BROKEN_BRICK_EFFECT_GRAVITY;*/
	/*x += vx * dt;
	x1 += x;
	x2 -= x;*/
	/*y1 += vy1 * dt;
	y2 += vy2 * dt;*/
	if (state == BRICK_EFFECT_STATE_APPEAR && GetTickCount64() - appear_start > BRICK_EFFECT_APPEAR_TIME) {
	vy1 += dt * 0.002f;
	vy2 += dt * 0.002f;
		this->Delete();
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CBrickEffect::Render()
{
	if (state == BRICK_EFFECT_STATE_INACTIVE)
		return;
	effectSprite.at(0)->Draw(round(x1), round(y1));
	effectSprite.at(1)->Draw(round(x1), round(y2));
	effectSprite.at(2)->Draw(round(x2), round(y1));
	effectSprite.at(3)->Draw(round(x2), round(y2));
}
void CBrickEffect::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_EFFECT_STATE_APPEAR:
		appear_start = GetTickCount64();
		vx = BRICK_EFFECT_SPEED_VX;
		vy1 = -BRICK_EFFECT_SPEED_VY1;
		vy2 = -BRICK_EFFECT_SPEED_VY2;
		break;
	case BRICK_EFFECT_STATE_INACTIVE:
		break;
	}
}
void CBrickEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}