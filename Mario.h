#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "Tail.h"
#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.35f
#define MARIO_JUMP_RUN_SPEED_Y	0.4f

#define MARIO_RACOON_FALL_VY		0.2f
#define MARIO_RACOON_FLY_VY			 0.2f
#define MARIO_GRAVITY			0.0008f
#define MARIO_GRAVITY_FALL			0.0002f
#define MARIO_JUMP_DEFLECT_SPEED  0.2f


#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301
#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500
#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601
#define MARIO_STATE_KICK			700
#define MARIO_STATE_HOLD			800
#define MARIO_STATE_TAIL_ATTACK		900
#define MARIO_STATE_FALLING			1000
#define MARIO_STATE_FLYING			1100
#define MARIO_STATE_ATTACK			1200
#define MARIO_STATE_ATTACK_RELEASE	1201


#pragma region ANIMATION_ID
//BIG
#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_KICK_RIGHT		1010
#define ID_ANI_MARIO_KICK_LEFT		1011

#define ID_ANI_MARIO_HOLD_WALK_RIGHT	1020
#define ID_ANI_MARIO_HOLD_WALK_LEFT		1021

#define ID_ANI_MARIO_HOLD_IDLE_RIGHT	1030
#define ID_ANI_MARIO_HOLD_IDLE_LEFT		1031
#define ID_ANI_MARIO_IN_PIPE		1050

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1101

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT	1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT			1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT		1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT		1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT	1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT	1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT	1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT	1601

#define ID_ANI_MARIO_SMALL_KICK_RIGHT		1700	
#define ID_ANI_MARIO_SMALL_KICK_LEFT		1701

#define ID_ANI_MARIO_SMALL_HOLD_WALK_RIGHT	1800	
#define ID_ANI_MARIO_SMALL_HOLD_WALK_LEFT	1801
#define ID_ANI_MARIO_SMALL_HOLD_IDLE_RIGHT	1810	
#define ID_ANI_MARIO_SMALL_HOLD_IDLE_LEFT	1811
#define ID_ANI_MARIO_SMALL_IN_PIPE			1950
#define ID_ANI_MARIO_IN_WORLD_MAP		1951

#define ID_ANI_MARIO_SMALL_TO_BIG_RIGHT		1960
#define ID_ANI_MARIO_SMALL_TO_BIG_LEFT		1961
//RACCON
#define ID_ANI_MARIO_RACCON_IDLE_RIGHT 2000
#define ID_ANI_MARIO_RACCON_IDLE_LEFT 2001

#define ID_ANI_MARIO_RACCON_WALKING_RIGHT 2100
#define ID_ANI_MARIO_RACCON_WALKING_LEFT 2101

#define ID_ANI_MARIO_RACCON_RUNNING_RIGHT 2200
#define ID_ANI_MARIO_RACCON_RUNNING_LEFT 2201

#define ID_ANI_MARIO_RACCON_BRACE_RIGHT 2300
#define ID_ANI_MARIO_RACCON_BRACE_LEFT 2301

#define ID_ANI_MARIO_RACCON_JUMP_WALK_RIGHT 2400
#define ID_ANI_MARIO_RACCON_JUMP_WALK_LEFT 2401

#define ID_ANI_MARIO_RACCON_JUMP_RUN_RIGHT 2500
#define ID_ANI_MARIO_RACCON_JUMP_RUN_LEFT 2501

#define ID_ANI_MARIO_RACCON_KICK_RIGHT	2600	
#define ID_ANI_MARIO_RACCON_KICK_LEFT	2601

#define ID_ANI_MARIO_RACCON_HOLD_WALK_RIGHT	2700	
#define ID_ANI_MARIO_RACCON_HOLD_WALK_LEFT	2701

#define ID_ANI_MARIO_RACCON_HOLD_IDLE_RIGHT	2710	
#define ID_ANI_MARIO_RACCON_HOLD_IDLE_LEFT	2711

#define ID_ANI_MARIO_RACCON_FLY_RIGHT	2800	
#define ID_ANI_MARIO_RACCON_FLY_LEFT	2801

#define ID_ANI_MARIO_RACCON_SIT_RIGHT 2900
#define ID_ANI_MARIO_RACCON_SIT_LEFT 2901

#define ID_ANI_MARIO_RACCON_ATTACK_RIGHT 2950
#define ID_ANI_MARIO_RACCON_ATTACK_LEFT 2951

#define ID_ANI_MARIO_RACCON_IN_PIPE		2850

#define ID_ANI_MARIO_BIG_TO_RACCON		2961
#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACCON	3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 26
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_RACCON_BBOX_WIDTH  22
#define MARIO_RACCON_BBOX_HEIGHT 26
#define MARIO_RACCON_SITTING_BBOX_WIDTH  22
#define MARIO_RACCON_SITTING_BBOX_HEIGHT 16


#define MARIO_FLYING_SPEED				0.3f
#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_FLYING_TIME 5000
#define MARIO_TAIL_ATTACK_TIME 200
#define MARIO_BIG_FORM_TRANSFORM_TIME 600
#define MARIO_RACCOON_FORM_TRANSFORM_TIME 400
#define MARIO_TELEPORT_TIME 300
#define MARIO_KICK_LIMIT_TIME 250
#define MARIO_FALLING_TIME 500


class CMario : public CGameObject
{
	BOOLEAN isSitting;
	BOOLEAN isHold = false;
	BOOLEAN isDropShell = false;
	BOOLEAN isKick = false;
	BOOLEAN isJumping = false;
	BOOLEAN isRunning = false;
	BOOLEAN isCreatedKoopa = false;
	BOOLEAN isFlying = false;
	BOOLEAN isCanFly = false;
	BOOLEAN isFalling = false;
	BOOLEAN isAttack = false;
	BOOLEAN isInWorldMap = false;
	BOOLEAN isTransformToBig = false;
	BOOLEAN isTransformToRaccon = false;
	BOOLEAN isInPipe = false;
	BOOLEAN isAuto = false;


	CTail* tail;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	ULONGLONG attack_start;
	ULONGLONG kick_start;
	ULONGLONG fly_start;
	ULONGLONG fall_start;
	ULONGLONG transform_start;
	ULONGLONG teleport_start;
	BOOLEAN isOnPlatform;
	int coin; 

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithTelePort(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithEndGameEffect(LPCOLLISIONEVENT e);
	void OnCollisionWithPSwitch(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithVenusFireTrap(LPCOLLISIONEVENT e);
	void OnCollisionWithFireBall(LPCOLLISIONEVENT e);
	void OnCollisionWithTreeWorldMap(LPCOLLISIONEVENT e);
	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRaccon();
	 
public:
	CMario(float x, float y, int isInWorldMap);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void EventCreateKoopa();
	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}
	void MarioLevelDown();
	void MarioLevelUp();

	void TailAttack();
	void Falling();
	void Fly();
	//Mario in world map
	void WalkLeft();
	void WalkRight();
	void WalkUp();
	void WalkDown();

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = (DWORD)GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int GetLevel() { return level; }

	bool GetIsSitting() { return this->isSitting; }
	void SetIsSitting(bool value) { this->isSitting = value; }

	bool GetIsRunning() { return this->isRunning; }
	void SetIsRunning(bool value) { this->isRunning = value; }

	bool GetIsJumping() { return this->isJumping; }
	void SetIsJumping(bool value) { this->isJumping = value; }

	bool GetIsHold() { return this->isHold; }
	void SetIsHold(bool value) { this->isHold = value; }

	bool GetIsDropShell() { return this->isDropShell; }
	void SetIsDropShell(bool value) { this->isDropShell = value; }

	bool GetIsKick() { return this->isKick; }
	void SetIsKick(bool value) { this->isKick = value; }

	bool GetIsOnPlatform() { return this->isOnPlatform; }
	void SetIsOnPlatform(bool value) { this->isOnPlatform = value; }

	bool GetIsFlying() { return this->isFlying; }
	void SetIsFlying(bool value) { this->isFlying = value; }

	bool GetIsCanFly() { return this->isCanFly; }
	void SetIsCanFly(bool value) { this->isCanFly = value; }

	bool GetIsFalling() { return this->isFalling; }
	void SetIsFalling(bool value) { this->isFalling = value; }

	bool GetIsAttack() { return this->isAttack; }
	void SetIsAttack(bool value) { this->isAttack = value; }

	bool GetIsInWorldMap() { return this->isAttack; }
	void SetIsInWorldMap(bool value) { this->isAttack = value; }

	bool GetIsInPipe() { return this->isInPipe; }
	void SetIsInPipe(bool value) { this->isInPipe = value; }
	//DebugOut(L"isInPipe %d", value);

	bool GetIsAuto() { return this->isAuto; }
	void SetIsAuto(bool value) {
		this->isAuto = value;
	}
	
};