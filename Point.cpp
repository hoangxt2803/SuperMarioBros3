#include "Point.h"
#include "PlayScene.h"

void CPoint::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_POINT_100;
	if (type == POINT_TYPE_100) {
		aniId = ID_ANI_POINT_100;
	}
	else if (type == POINT_TYPE_200) {
		aniId = ID_ANI_POINT_200;
	}
	else if (type == POINT_TYPE_400) {
		aniId = ID_ANI_POINT_400;
	}
	else if (type == POINT_TYPE_800) {
		aniId = ID_ANI_POINT_800;
	}
	else if (type == POINT_TYPE_1000) {
		aniId = ID_ANI_POINT_1000;
	}
	else if (type == POINT_TYPE_2000) {
		aniId = ID_ANI_POINT_2000;
	}
	else if (type == POINT_TYPE_4000) {
		aniId = ID_ANI_POINT_4000;
	}
	else if (type == POINT_TYPE_8000) {
		aniId = ID_ANI_POINT_8000;
	}
	else if (type == POINT_TYPE_1UP) {
		aniId = ID_ANI_POINT_1UP;
	}
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CPoint::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - POINT_WIDTH / 2;
	t = y - POINT_HEIGHT / 2;
	r = l + POINT_WIDTH;
	b = t + POINT_HEIGHT;
}
void CPoint::OnNoCollision(DWORD dt)
{
	y += vy * dt;

}
void CPoint::OnCollisionWith(LPCOLLISIONEVENT e)
{
}
;
void CPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->y <= positionY) {
		CHUD* hub = (CHUD*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetHUD();
		switch (type)
		{
		case POINT_TYPE_100:
			hub->PointPlus(100);
			break;
		case POINT_TYPE_200:
			hub->PointPlus(200);
			break;
		case POINT_TYPE_400:
			hub->PointPlus(400);
			break;
		case POINT_TYPE_800:
			hub->PointPlus(800);
			break;
		case POINT_TYPE_1000:
			hub->PointPlus(1000);
			break;
		case POINT_TYPE_2000:
			hub->PointPlus(2000);
			break;
		case POINT_TYPE_4000:
			hub->PointPlus(4000);
			break;
		case POINT_TYPE_8000:
			hub->PointPlus(8000);
			break;
		case POINT_TYPE_1UP:
			hub->LifePlus(1);
			break;
		default:
			break;
		}
		this->Delete();
	}
		

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}