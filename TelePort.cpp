#include "TelePort.h"
#include "Mario.h"

void CTelePort::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - TELEPORT_BBOX_WIDTH / 2;
	top = y - TELEPORT_BBOX_HEIGHT / 2;
	right = left + TELEPORT_BBOX_WIDTH;
	bottom = top + TELEPORT_BBOX_HEIGHT;
}



void CTelePort::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CTelePort::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CTelePort::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj)) {
		CMario* mario = dynamic_cast<CMario*>(e->obj);
		mario->SetPosition(teleX, teleY);
		mario->SetIsInPipe(!mario->GetIsInPipe());
		
	}
}

void CTelePort::Render()
{
	//RenderBoundingBox();
}
