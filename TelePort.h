#pragma once
#include "GameObject.h"

#define TELEPORT_TYPE_FALSE 0
#define TELEPORT_TYPE_TRUE 1
#define TELEPORT_BBOX_WIDTH 30
#define TELEPORT_BBOX_HEIGHT 14
class CTelePort : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	int type;
	float teleX, teleY;
public:
	CTelePort(float x, float y, float teleX, float teleY, int type) :CGameObject(x, y){
		this->type = type;
		this->teleX = teleX;
		this->teleY = teleY;
	}
};