#include "EndGameEffect.h"

CEndGameEffect::CEndGameEffect(float x, float y) :CGameObject(x, y)
{
	isColleceted = false;
	number = 1;
	number_start = GetTickCount64();
}

void CEndGameEffect::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - END_GAME_EFFECT_BBOX_WIDTH / 2;
	top = y - END_GAME_EFFECT_BBOX_HEIGHT / 2;
	right = left + END_GAME_EFFECT_BBOX_WIDTH;
	bottom = top + END_GAME_EFFECT_BBOX_HEIGHT;
}


void CEndGameEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isColleceted) {
		if (number > 3)
		{
			number = 1;
		}
		else
		{
			if (GetTickCount64() - number_start > 300)
			{
				number++;
				number_start = GetTickCount64();
			}
		}
			
	}
	else
	{
		y++;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CEndGameEffect::Render()
{	
	int aniId = ID_ANI_END_GAME_EFFECT_MUSHROOM;
	if (number == 1)
		aniId = ID_ANI_END_GAME_EFFECT_MUSHROOM;
	else if(number == 2)
		aniId = ID_ANI_END_GAME_EFFECT_FIRE_FLOWER;
	else if (number == 3)
		aniId = ID_ANI_END_GAME_EFFECT_STAR;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}
