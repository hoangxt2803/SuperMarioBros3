#include "VenusFireTrap.h"
#include "PlayScene.h"
#include "AssetIDs.h"
CVenusFireTrap::CVenusFireTrap(float x, float y, int type) :CGameObject(x, y)
{
	this->oldX = x;
	this->oldY = y;
	this->type = type;
	this->SetState(VENUS_FIRE_TRAP_STATE_MOVE);
	this->ny = 1;
	marioXX = 0;
	marioYY = 0;
}

void CVenusFireTrap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (this->type == VENUS_FIRE_TRAP_TYPE_RED) {
		left = x - VENUS_FIRE_TRAP_RED_BBOX_WIDTH / 2;
		top = y - VENUS_FIRE_TRAP_RED_BBOX_HEIGHT / 2;
		right = left + VENUS_FIRE_TRAP_RED_BBOX_WIDTH;
		bottom = top + VENUS_FIRE_TRAP_RED_BBOX_HEIGHT;
	}
	else if (this->type == VENUS_FIRE_TRAP_TYPE_GREEN) {
		left = x - VENUS_FIRE_TRAP_GREEN_BBOX_WIDTH / 2;
		top = y - VENUS_FIRE_TRAP_GREEN_BBOX_HEIGHT / 2;
		right = left + VENUS_FIRE_TRAP_GREEN_BBOX_WIDTH;
		bottom = top + VENUS_FIRE_TRAP_GREEN_BBOX_HEIGHT;
	}
}

void CVenusFireTrap::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CVenusFireTrap::OnCollisionWith(LPCOLLISIONEVENT e)
{

}
void CVenusFireTrap::ShootFireball() {
	SetState(VENUS_FIRE_TRAP_STATE_SHOOT);
	countFire = 1;
	CGameObject* obj = NULL;
	//obj->SetState(FIRE_STATE_ACTIVE);
	if (marioXX < x) {
		obj = new CFireBall(x - FIRE_BBOX_WIDTH, y - FIRE_BBOX_HEIGHT, nx, ny);
	}
	else {
		obj = new CFireBall(x + FIRE_BBOX_WIDTH, y - FIRE_BBOX_HEIGHT / 2, nx, ny);
	}
	LPPLAYSCENE playscreen = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	playscreen->AddObject(obj);
	vy = VENUS_FIRE_TRAP_SPEED;
}
void CVenusFireTrap::Appear() {
	if (marioXX < x)
	{
		if ((marioXX + SCREEN_WIDTH / 2) > x)
			state = VENUS_FIRE_TRAP_STATE_MOVE;
		else
		{
			state = VENUS_FIRE_TRAP_STATE_IDE;
			SetPosition(oldX, oldY);
		}
	}
	else if (marioXX > x) {
		if ((marioXX - SCREEN_WIDTH / 2) < x)
			state = VENUS_FIRE_TRAP_STATE_MOVE;
		else
		{
			state = VENUS_FIRE_TRAP_STATE_IDE;
			SetPosition(oldX, oldY);
		}
	}
}
void CVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	LPPLAYSCENE playscreen = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)playscreen->GetPlayer();
	
	mario->GetPosition(marioXX, marioYY);

	if (marioXX < x) {
		nx = -1;
		if (marioYY < y) {
			ny = -1;
		}
		else {
			ny = 1;
		}
	}
	else if (marioXX > x) {
		nx = 1;
		if (marioYY < y) {
			ny = -1;
		}
		else {
			ny = 1;
		}
	}
	//appear
	Appear();

	if (this->type == VENUS_FIRE_TRAP_TYPE_RED) {
		if (state == VENUS_FIRE_TRAP_STATE_MOVE && this->y <= oldY - VENUS_FIRE_TRAP_RED_BBOX_HEIGHT) {
			//shoot
			ShootFireball();
		}
		else if (state == VENUS_FIRE_TRAP_STATE_MOVE && this->y >= oldY) {
			vy = -VENUS_FIRE_TRAP_SPEED;
		}

	}
	else if (this->type == VENUS_FIRE_TRAP_TYPE_GREEN) {
		if (state == VENUS_FIRE_TRAP_STATE_MOVE && this->y <= oldY - VENUS_FIRE_TRAP_GREEN_BBOX_HEIGHT) {
			//shoot
			ShootFireball();
		}
		else if (state == VENUS_FIRE_TRAP_STATE_MOVE && this->y >= oldY) {
			vy = -VENUS_FIRE_TRAP_SPEED;
		}
	}
	if (state == VENUS_FIRE_TRAP_STATE_SHOOT && countFire > 0 && (DWORD)GetTickCount64() - fire_start > 1000) {
		SetState(VENUS_FIRE_TRAP_STATE_MOVE);
		vy = -vy;
		countFire = 0;
	}
	


	//
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CVenusFireTrap::Render()
{
	int aniId = -1;
	LPPLAYSCENE playscreen = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)playscreen->GetPlayer();
	float marioX, marioY;
	mario->GetPosition(marioX, marioY);

	if (this->type == VENUS_FIRE_TRAP_TYPE_RED) {
		if (this->state == VENUS_FIRE_TRAP_STATE_IDE || this->state == VENUS_FIRE_TRAP_STATE_MOVE)
			if (marioX < x)
				aniId = ID_ANI_VENUS_FIRE_TRAP_RED_LEFT_DOWN;
			else
				aniId = ID_ANI_VENUS_FIRE_TRAP_RED_RIGHT_DOWN;
		else if (this->state == VENUS_FIRE_TRAP_STATE_SHOOT) {
			if (marioX < x) {
				if (marioY < y) {
					aniId = ID_ANI_VENUS_FIRE_TRAP_RED_LEFT_UP;
				}
				else {
					aniId = ID_ANI_VENUS_FIRE_TRAP_RED_LEFT_DOWN;
				}
			}
			else if (marioX > x) {
				if (marioY < y) {
					aniId = ID_ANI_VENUS_FIRE_TRAP_RED_RIGHT_UP;
				}
				else {
					aniId = ID_ANI_VENUS_FIRE_TRAP_RED_RIGHT_DOWN;
				}

			}

		}
	}
	else if (this->type == VENUS_FIRE_TRAP_TYPE_GREEN) {
		if (this->state == VENUS_FIRE_TRAP_STATE_IDE || this->state == VENUS_FIRE_TRAP_STATE_MOVE)
			aniId = ID_ANI_VENUS_FIRE_TRAP_GREEN_LEFT_DOWN;
		else if (this->state == VENUS_FIRE_TRAP_STATE_SHOOT) {
			if (marioX < x) {
				if (marioY < y)
					aniId = ID_ANI_VENUS_FIRE_TRAP_GREEN_LEFT_UP;
				else
					aniId = ID_ANI_VENUS_FIRE_TRAP_GREEN_LEFT_DOWN;
			}
			else if (marioX > x) {
				if (marioY < y)
					aniId = ID_ANI_VENUS_FIRE_TRAP_GREEN_RIGHT_UP;
				else
					aniId = ID_ANI_VENUS_FIRE_TRAP_GREEN_RIGHT_DOWN;
			}

		}
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CVenusFireTrap::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case VENUS_FIRE_TRAP_STATE_IDE:
		vx = 0;
		vy = 0;
		break;
	case VENUS_FIRE_TRAP_STATE_MOVE:
		vy = -VENUS_FIRE_TRAP_SPEED;
		break;
	case VENUS_FIRE_TRAP_STATE_SHOOT:
		fire_start = (DWORD)GetTickCount64();
		vy = 0;
		break;
	}
}
