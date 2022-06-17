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
#include "TreeWorldMap.h"
#include "Point.h"
#include "TelePort.h"

CMario::CMario(float x, float y, int inWorldMap) : CGameObject(x, y)
{
	isSitting = false;
	isKick = false;
	isHold = false;
	isDropShell = false;
	isRunning = false;
	isJumping = false;
	isCreatedKoopa = false;
	maxVx = 0.0f;
	ax = 0.0f;
	ay = MARIO_GRAVITY;

	level = MARIO_LEVEL_SMALL;
	untouchable = 0;
	untouchable_start = -1;
	isOnPlatform = false;
	coin = 0;

	kick_start = 0;
	attack_start = 0;
	fly_start = 0;
	fall_start = 0;
	transform_start = 0;
	teleport_start = 0;
	this->isInWorldMap = inWorldMap;
	tail = NULL;
	if (!isInWorldMap) {
		CGameObject* obj = NULL;
		LPPLAYSCENE playscreen = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		tail = new CTail(x, y);
		obj = tail;
		playscreen->AddObject(obj);
	}
		
}
void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (isTransformToBig && GetTickCount64() - transform_start > MARIO_BIG_FORM_TRANSFORM_TIME) {
		isTransformToBig = false;
	}
	else if (isTransformToBig && GetTickCount64() - transform_start < MARIO_BIG_FORM_TRANSFORM_TIME)
		return;
	if (isTransformToRaccon && GetTickCount64() - transform_start > MARIO_BIG_FORM_TRANSFORM_TIME) {
		isTransformToRaccon = false;
	}
	else if (isTransformToRaccon && GetTickCount64() - transform_start < MARIO_BIG_FORM_TRANSFORM_TIME)
		return;
	if (isFalling && GetTickCount64() - fall_start > MARIO_FALLING_TIME) {
		isFalling = false;
	}
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;
	if (isFlying || isFalling) {
		ay = MARIO_GRAVITY_FALL;
	}
	else {
		ay = MARIO_GRAVITY;
	}
	
	
	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (GetTickCount64() - attack_start > MARIO_TAIL_ATTACK_TIME && isAttack)
	{
		isAttack = false;
		//tail->SetState(TAIL_STATE_INACTIVE);
	}
	// event create 3 wing koopa and 1 normal koopa
	if (!isCreatedKoopa) {
		EventCreateKoopa();
	}
	isOnPlatform = false;
	LPPLAYSCENE playscreen = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	if (playscreen->GetSceneId() == 4)
		isInWorldMap = true;
	else
		isInWorldMap = false;
	if (isInWorldMap)
	{
		vy = 0;
		vx = 0;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (isInWorldMap && e->obj->IsBlocking()) {
		x = 10;
	}
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) {
			isOnPlatform = true;
			isFlying = false;
			isFalling = false;
			isJumping = false;
			fly_start = 0;
		}
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}
	if (dynamic_cast<CTail*>(e->obj))
		return;
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CTelePort*>(e->obj))
		OnCollisionWithTelePort(e);
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

void CMario::OnCollisionWithTreeWorldMap(LPCOLLISIONEVENT e)
{
	if (isInWorldMap) {
		if (nx > 0)
			x -= 16;
		else if (nx < 0)
			x += 16;
		else if (ny > 0)
			y -= 16;
		else if (ny < 0)
			y += 16;
	}
}
void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	CGameObject* obj = NULL;
	LPPLAYSCENE playscreen = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	float goombaX, goombaY;
	goomba->GetPosition(goombaX, goombaY);
	
	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() == GOOMBA_STATE_WALKING)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			obj = new CPoint(goombaX, goombaY - 4, POINT_TYPE_100);
			playscreen->AddObject(obj);
		}
		else if (goomba->GetLevel() != GOOMBA_LEVEL_NORMAL)
		{
			goomba->SetLevel(GOOMBA_LEVEL_NORMAL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			obj = new CPoint(goombaX, goombaY - 4, POINT_TYPE_400);
			playscreen->AddObject(obj);
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
	CGameObject* obj = NULL;
	LPPLAYSCENE playscreen = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	float XX, YY;
	koopa->GetPosition(XX, YY);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (koopa->GetLevel() > KOOPA_TROOPA_LEVEL_NORMAL) {
			koopa->SetKoopaToShell(false);
			koopa->SetLevel(KOOPA_TROOPA_LEVEL_NORMAL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			obj = new CPoint(XX, YY - 4, POINT_TYPE_200);
			playscreen->AddObject(obj);

		}
		else if (koopa->GetState() == KOOPA_TROOPA_STATE_WALKING)
		{
			koopa->SetKoopaToShell(true);
			koopa->SetState(KOOPA_TROOPA_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			obj = new CPoint(XX, YY - 4, POINT_TYPE_100);
			playscreen->AddObject(obj);
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
	CHUD* hub = (CHUD*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetHUD();
	hub->CoinPlus();
	hub->PointPlus(50);
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
		if (brick->GetBrickType() == BRICK_TYPE_QBRICK_COIN && brick->GetState() != BRICK_STATE_BRICK_EMPTY) {
			CHUD* hub = (CHUD*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetHUD();
			hub->CoinPlus();
			hub->PointPlus(50);
			brick->SetState(BRICK_STATE_BRICK_UP);
		}
	}
	//Broken brick chuyển sang coin
	if (brick->GetBrickType() == BRICK_TYPE_BROKEN && brick->GetState() == BRICK_STATE_BROKEN_BRICK_COIN) {
		CHUD* hub = (CHUD*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetHUD();
		hub->CoinPlus();
		hub->PointPlus(50);
		e->obj->Delete();
	}
}
void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
	CGameObject* obj = NULL;
	LPPLAYSCENE playscreen = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	float XX, YY;
	mushroom->GetPosition(XX, YY);

	if (mushroom->GetType() == MUSHROOM_TYPE_RED) {
		MarioLevelUp();
		obj = new CPoint(XX, YY - 4, POINT_TYPE_1000);
		playscreen->AddObject(obj);

	}
	else if (mushroom->GetType() == MUSHROOM_TYPE_GREEN) {
		CHUD* hub = (CHUD*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetHUD();
		hub->LifePlus(1);
	}
	isInPipe = true;
	this->SetPosition(2105, 510);
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
	CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);
	MarioLevelUp();
	CGameObject* obj = NULL;
	LPPLAYSCENE playscreen = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	float XX, YY;
	leaf->GetPosition(XX, YY);
	obj = new CPoint(XX, YY - 4, POINT_TYPE_1000);
	playscreen->AddObject(obj);
	e->obj->Delete();
}
void CMario::OnCollisionWithEndGameEffect(LPCOLLISIONEVENT e)
{
	CEndGameEffect* end = (CEndGameEffect*)e->obj;
	end->SetIsCollected(true);
}


void CMario::OnCollisionWithTelePort(LPCOLLISIONEVENT e)
{
	isInPipe = true;
	this->SetPosition(2105, 510);
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
				if (isHold) {
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_LEFT;
				}
				else {
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
				}
			}
			else if (vx > 0)
			{
				if (isHold) {
					aniId = ID_ANI_MARIO_SMALL_HOLD_WALK_RIGHT;
				}
				else {
					if (ax < 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
				}
			}
			else // vx < 0
			{
				if (isHold) {
					aniId = ID_ANI_MARIO_SMALL_HOLD_WALK_LEFT;
				}
				else {
					if (ax > 0)
						aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
				}
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
				if (isHold) {
					if (nx > 0) aniId = ID_ANI_MARIO_HOLD_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_HOLD_IDLE_LEFT;
				}
				else {
					if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_IDLE_LEFT;
				}
			}
			else if (vx > 0)
			{
				if (isHold) {
					aniId = ID_ANI_MARIO_HOLD_WALK_RIGHT;
				}
				else {
					if (ax < 0)
						aniId = ID_ANI_MARIO_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_WALKING_RIGHT;
				}
			}
			else // vx < 0
			{
				if (isHold) {
					aniId = ID_ANI_MARIO_HOLD_WALK_LEFT;
				}
				else {
					if (ax > 0)
						aniId = ID_ANI_MARIO_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_MARIO_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_MARIO_WALKING_LEFT;
				}
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
	if (isFlying)
		if (vx > 0)
			aniId = ID_ANI_MARIO_RACCON_FLY_LEFT;
		else if(vx < 0)
			aniId = ID_ANI_MARIO_RACCON_FLY_RIGHT;
	if(isAttack)
		if (nx > 0)
			aniId = ID_ANI_MARIO_RACCON_ATTACK_RIGHT;
		else if (nx < 0)
			aniId = ID_ANI_MARIO_RACCON_ATTACK_LEFT;
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
	
	if (level == MARIO_LEVEL_RACCON && isAttack) {
		if(nx>0)
			animations->Get(aniId)->Render(x + 7, y);
		else if(nx<0)
			animations->Get(aniId)->Render(x - 7, y);
	}
	else if (isInWorldMap) {
		aniId = ID_ANI_MARIO_IN_WORLD_MAP;
		animations->Get(aniId)->Render(x, y);
	}
	else if (isTransformToBig) {
		if (nx > 0) {
			aniId = ID_ANI_MARIO_SMALL_TO_BIG_LEFT;
			animations->Get(aniId)->Render(x, y);
		}
		else if (nx < 0) {
			aniId = ID_ANI_MARIO_SMALL_TO_BIG_RIGHT;
			animations->Get(aniId)->Render(x, y);
		}
	}
	else if (isTransformToRaccon) {
		aniId = ID_ANI_MARIO_BIG_TO_RACCON;
		animations->Get(aniId)->Render(x, y);
	}
	else 
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
		isRunning = true;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		isRunning = true;
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
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
			ny = 1;
			isJumping = true;
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
		kick_start = GetTickCount64();
		break;
	case MARIO_STATE_FLYING:
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
		isTransformToBig = true;
		transform_start = GetTickCount64();
		level = MARIO_LEVEL_BIG;
		StartUntouchable();
	}
	else if (level > MARIO_LEVEL_SMALL)
	{
		isTransformToRaccon = true;
		transform_start = GetTickCount64();
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
		isTransformToBig = true;
		transform_start = GetTickCount64();
		SetLevel(MARIO_LEVEL_BIG);
	}
	else if (this->level == MARIO_LEVEL_BIG) {
		isTransformToRaccon = true;
		transform_start = GetTickCount64();
		SetLevel(MARIO_LEVEL_RACCON);
	}
}

void CMario::Fly()
{

	if (level == MARIO_LEVEL_RACCON)
	{
		ULONGLONG current = GetTickCount64();
		if (fly_start != 0 &&
			current - fly_start < MARIO_FLYING_TIME)
		{
			this->SetState(MARIO_STATE_FLYING);
			this->vy = -MARIO_FLYING_SPEED;
			this->vx = 0.001f*nx;
			this->isFlying = true;
			this->isCanFly = false;
		}
		else if (isCanFly)
		{
			//power full -> isCanFly = true
			fly_start = current;
			this->vy = -MARIO_FLYING_SPEED;
			this->vx = 0.1f * nx;
		}
	}
}

void CMario::WalkLeft()
{
	if (isInWorldMap) {
		this->x -= 16;
		this->nx = -1;
	}
}

void CMario::WalkRight()
{
	if (isInWorldMap) {
		this->x += 16;
		this->nx = 1;
	}
}

void CMario::WalkUp()
{
	if (isInWorldMap) {
		this->y -= 16;
		this->ny = -1;
	}
}

void CMario::WalkDown()
{
	if (isInWorldMap) {
		this->y += 16;
		this->ny = 1;
	}
}

void CMario::Falling()
{
	isFalling = true;
	vy = 0.0035f;
	fall_start = GetTickCount64();
}
void CMario::TailAttack()
{
	vx = 0;
	if (GetTickCount64() - attack_start > MARIO_TAIL_ATTACK_TIME && level == MARIO_LEVEL_RACCON)
	{
		isAttack = true;
		attack_start = GetTickCount64();
		CGame* game = CGame::GetInstance();
		if (nx > 0)
		{
			tail->Attack(x, (y + 5), this->nx);
		}
		if (nx < 0)
		{
			tail->Attack(x, (y + 5),this->nx);
		}

	}
}