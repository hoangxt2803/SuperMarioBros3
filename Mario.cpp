#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"
#include "PlayScene.h"
#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"

#include "Collision.h"
#include "Koopa.h"
#include "Brick.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "AssetIDs.h"
#include "EndGameEffect.h"
#include "PSwitch.h"
#include "PiranhaPlant.h"
#include "VenusFireTrap.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	// event create 3 wing koopa and 1 normal koopa
	if (!isCreatedKoopa) {
		EventCreateKoopa();
	}
	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CEndGameEffect*>(e->obj))
		OnCollisionWithEndGameEffect(e);
	else if (dynamic_cast<CPSwitch*>(e->obj))
		OnCollisionWithPSwitch(e);
	else if (dynamic_cast<CPiranhaPlant*>(e->obj))
		OnCollisionWithPiranhaPlant(e);
	else if (dynamic_cast<CVenusFireTrap*>(e->obj))
		OnCollisionWithVenusFireTrap(e);
	else if (dynamic_cast<CFireBall*>(e->obj))
		OnCollisionWithFireBall(e);
	
}
void CMario::OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e)
{
	CPiranhaPlant* piranhaPlant = dynamic_cast<CPiranhaPlant*>(e->obj);
	if (piranhaPlant->GetState() != PIRANHAPLANT_STATE_IDE)
	{
		if (untouchable == 0)
		{
			MarioLevelDown();
		}
	}
	
	

}
void CMario::OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e)
{
	CVenusFireTrap* venusFireTrap = dynamic_cast<CVenusFireTrap*>(e->obj);
	if (venusFireTrap->GetState() != VENUS_FIRE_TRAP_STATE_IDE)
	{
		if (untouchable == 0)
		{
			MarioLevelDown();
		}
	}
	
	
}
void CMario::OnCollisionWithFireBall(LPCOLLISIONEVENT e)
{
	CFireBall* fireball = dynamic_cast<CFireBall*>(e->obj);
	if (untouchable == 0)
	{
		MarioLevelDown();
	}
}
void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() == GOOMBA_STATE_WALKING)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (goomba->GetLevel() != GOOMBA_LEVEL_NORMAL)
		{
			goomba->SetLevel(GOOMBA_LEVEL_NORMAL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				MarioLevelDown();
			}
		}
	}
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (koopa->GetLevel() > KOOPA_TROOPA_LEVEL_NORMAL) {
			koopa->SetKoopaToShell(false);
			koopa->SetLevel(KOOPA_TROOPA_LEVEL_NORMAL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (koopa->GetState() == KOOPA_TROOPA_STATE_WALKING)
		{
			koopa->SetKoopaToShell(true);
			koopa->SetState(KOOPA_TROOPA_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (koopa->GetState() == KOOPA_TROOPA_STATE_SHELL) {
			koopa->SetKoopaToShell(false);
			koopa->SetState(KOOPA_TROOPA_STATE_SHELL_MOVE);
			koopa->IsKicked(this->nx);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (koopa->GetState() == KOOPA_TROOPA_STATE_SHELL_MOVE) {
			koopa->SetKoopaToShell(false);
			koopa->SetState(KOOPA_TROOPA_STATE_SHELL);
			koopa->SetSpeed(0, 0);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	} //đá
	else if (e->nx != 0 && koopa->GetState() == KOOPA_TROOPA_STATE_SHELL && !isRunning) {
		this->SetState(MARIO_STATE_KICK);
		koopa->SetKoopaToShell(false);
		koopa->SetState(KOOPA_TROOPA_STATE_SHELL_MOVE);
		koopa->IsKicked(this->nx);

	}//hold
	else if (e->nx != 0 && koopa->GetState() == KOOPA_TROOPA_STATE_SHELL && isRunning) {
		koopa->SetIsHolded(true);
		koopa->SetState(KOOPA_TROOPA_STATE_HOLED);
		this->isHold = true;
	}
	
	else // hit by KoopaTroopa
	{
		if (untouchable == 0)
		{
			if (koopa->GetState() != KOOPA_TROOPA_STATE_SHELL)
			{
				MarioLevelDown();
			}
		}
	}
}


void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}
void CMario::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	if (e->ny > 0)
	{
		if (brick->GetBrickType() == BRICK_TYPE_QBRICK_1UP || brick->GetBrickType() == BRICK_TYPE_QBRICK_MUSHROOM || brick->GetBrickType() == BRICK_TYPE_QBRICK_COIN) {
			if (brick->GetState() != BRICK_STATE_BRICK_EMPTY)
			{
				brick->SetState(BRICK_STATE_BRICK_UP);
			}
		}
		
	}
	if (brick->GetBrickType() == BRICK_TYPE_BROKEN && brick->GetState() == BRICK_STATE_BROKEN_BRICK_COIN) {
		e->obj->Delete();
		coin++;
	}
}
void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
	if (mushroom->GetType() == MUSHROOM_TYPE_RED) {
		MarioLevelUp();
	}
	else if (mushroom->GetType() == MUSHROOM_TYPE_GREEN) {
		// +1up
	}
	e->obj->Delete();
}

void CMario::OnCollisionWithPSwitch(LPCOLLISIONEVENT e)
{
	CPSwitch* pswitch = dynamic_cast<CPSwitch*>(e->obj);
	if(pswitch->GetState()== P_SWITCH_STATE_APPEAR)
		pswitch->SetState(P_SWITCH_STATE_ACTIVATED);
}
void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	MarioLevelUp();
	e->obj->Delete();
}
void CMario::OnCollisionWithEndGameEffect(LPCOLLISIONEVENT e)
{
	CEndGameEffect* end = (CEndGameEffect*)e->obj;
	end->SetIsCollected(true);
}


void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

//
// Get animdation ID for big Mario
//
int CMario::GetAniIdRaccon()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCON_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCON_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCON_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCON_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCON_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (isHold) {
					if (nx > 0) aniId = ID_ANI_MARIO_RACCON_HOLD_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_RACCON_HOLD_IDLE_LEFT;
				}
				else {
					if (nx > 0) aniId = ID_ANI_MARIO_RACCON_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_RACCON_IDLE_LEFT;
				}

			}
	/*else if (vx > 0 && isKick && (DWORD)GetTickCount64() - kick_start > 200)
	{
		aniId = ID_ANI_MARIO_RACCON_KICK_RIGHT;
	}
	else if (vx < 0 && isKick && (DWORD)GetTickCount64() - kick_start > 200)
	{
		aniId = ID_ANI_MARIO_RACCON_KICK_LEFT;
	}*/
			else if (vx > 0)
			{
				if (isHold) {
					aniId = ID_ANI_MARIO_RACCON_HOLD_WALK_RIGHT;
				}
				else {
					if (ax < 0)
						aniId = ID_ANI_MARIO_RACCON_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_RACCON_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_RACCON_WALKING_RIGHT;
				}

			}
			else // vx < 0
			{
				if (isHold) {
					aniId = ID_ANI_MARIO_RACCON_HOLD_WALK_LEFT;
				}
				else {
					if (ax > 0)
						aniId = ID_ANI_MARIO_RACCON_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_RACCON_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_RACCON_WALKING_LEFT;
				}

			}

	if (aniId == -1) aniId = ID_ANI_MARIO_RACCON_IDLE_RIGHT;

	return aniId;
}
void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACCON)
		aniId = GetAniIdRaccon();
	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		isRunning = false;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		isRunning = false;
		break;
	case MARIO_STATE_JUMP:
		isJumping = true;
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
			ny = 1;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		isJumping = false;
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		ny = -1;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		isKick = false;
		isRunning = false;
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:

		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	case MARIO_STATE_KICK:
		isKick = true;
		kick_start = (DWORD)GetTickCount64();
		break;
	}


	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_RACCON) {
		if (isSitting)
		{
			left = x - MARIO_RACCON_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_RACCON_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_RACCON_SITTING_BBOX_WIDTH / 2;
			bottom = top + MARIO_RACCON_SITTING_BBOX_HEIGHT;
		}
		else
		{
			if (nx > 0) {
				left = x - MARIO_RACCON_BBOX_WIDTH / 2 + 7;
				top = y - MARIO_RACCON_BBOX_HEIGHT / 2;
				right = left + MARIO_RACCON_BBOX_WIDTH - 7;
				bottom = top + MARIO_RACCON_BBOX_HEIGHT;
			}
			else if (nx < 0) {
				left = x - MARIO_RACCON_BBOX_WIDTH / 2;
				top = y - MARIO_RACCON_BBOX_HEIGHT / 2;
				right = left + MARIO_RACCON_BBOX_WIDTH - 7;
				bottom = top + MARIO_RACCON_BBOX_HEIGHT;
			}
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

void CMario::EventCreateKoopa() {
	//x: 1100 - 1500, y: 170
	if ((this->x >= POSITION_EVENT_CREATE_KOOPA_X1 && this->x <= POSITION_EVENT_CREATE_KOOPA_X2) 
		&& this->y >= POSITION_EVENT_CREATE_KOOPA_Y) {
		CGameObject* obj = NULL;
		LPPLAYSCENE playscreen = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		for(int i = 0; i < 3; i++) {
			obj = new CKoopa((float)POSITION_WING_KOOPA_X + i* DISTANCE_2_KOOPA, POSITION_WING_KOOPA_Y, 2, 2);
			playscreen->AddObject(obj);
		}
		obj = new CKoopa(POSITION_NORMAL_KOOPA_X, POSITION_NORMAL_KOOPA_Y, 2, 1);
		playscreen->AddObject(obj);
		isCreatedKoopa = true;
	}
}

void CMario::MarioLevelDown() {
	if (level > MARIO_LEVEL_BIG)
	{
		level = MARIO_LEVEL_BIG;
		StartUntouchable();
	}
	else if (level > MARIO_LEVEL_SMALL)
	{
		level = MARIO_LEVEL_SMALL;
		StartUntouchable();
	}
	else
	{
		DebugOut(L">>> Mario DIE >>> \n");
		SetState(MARIO_STATE_DIE);
	}
}

void CMario::MarioLevelUp() {
	if (this->level == MARIO_LEVEL_SMALL)
	{
		SetLevel(MARIO_LEVEL_BIG);
	}
	else if (this->level == MARIO_LEVEL_BIG) {
		SetLevel(MARIO_LEVEL_RACCON);
	}
}