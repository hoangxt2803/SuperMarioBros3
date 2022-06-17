#pragma once

#include "GameObject.h"

#define ID_ANI_POINT_100	7701
#define ID_ANI_POINT_200	7702
#define ID_ANI_POINT_400	7703
#define ID_ANI_POINT_800	7704
#define ID_ANI_POINT_1000	7705
#define ID_ANI_POINT_2000	7706
#define ID_ANI_POINT_4000	7707
#define ID_ANI_POINT_8000	7708
#define ID_ANI_POINT_1UP	7709
#define POINT_WIDTH 16
#define POINT_HEIGHT 8
#define POINT_TYPE_100	1
#define POINT_TYPE_200	2
#define POINT_TYPE_400	3
#define POINT_TYPE_800	4
#define POINT_TYPE_1000 5
#define POINT_TYPE_2000 6
#define POINT_TYPE_4000 7
#define POINT_TYPE_8000 8
#define POINT_TYPE_1UP	9

#define POINT_SPEED 0.05f
class CPoint : public CGameObject {
	int type;
	float positionY;

	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CPoint(float x, float y, int type) : CGameObject(x, y) {
		this->type = type;
		this->positionY = (y - POINT_HEIGHT * 3);
		this->vy = - POINT_SPEED;
		this->vx = 0;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};