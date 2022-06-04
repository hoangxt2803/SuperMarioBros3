#pragma once
#include "GameObject.h"

#define SPEED_BAR_LEVEL_0 0
#define SPEED_BAR_LEVEL_1 1
#define SPEED_BAR_LEVEL_2 2
#define SPEED_BAR_LEVEL_3 3
#define SPEED_BAR_LEVEL_4 4
#define SPEED_BAR_LEVEL_5 5
#define SPEED_BAR_LEVEL_6 6
#define SPEED_BAR_LEVEL_MAX 7

#define ANI_BLACK_BACKGROUND 6000	
#define ANI_BLACK_BACKGROUND_2 6040
#define ANI_HUB 6001	
#define ANI_HUB_SPEED_BAR_LEVEL_0 6010
#define ANI_HUB_SPEED_BAR_LEVEL_1 6011
#define ANI_HUB_SPEED_BAR_LEVEL_2 6012
#define ANI_HUB_SPEED_BAR_LEVEL_3 6013
#define ANI_HUB_SPEED_BAR_LEVEL_4 6014
#define ANI_HUB_SPEED_BAR_LEVEL_5 6015
#define ANI_HUB_SPEED_BAR_LEVEL_6 6016
#define ANI_HUB_SPEED_BAR_LEVEL_MAX 6017
#define ANI_ITEM_STACK_1 6020	
#define ANI_ITEM_STACK_2 6021
#define ANI_ITEM_STACK_3 6022
#define ANI_HUB_NUMBER_0 6030	
#define ANI_HUB_NUMBER_1 6031	
#define ANI_HUB_NUMBER_2 6032
#define ANI_HUB_NUMBER_3 6033
#define ANI_HUB_NUMBER_4 6034
#define ANI_HUB_NUMBER_5 6035
#define ANI_HUB_NUMBER_6 6036	
#define ANI_HUB_NUMBER_7 6037	
#define ANI_HUB_NUMBER_8 6038
#define ANI_HUB_NUMBER_9 6039
#define HUB_HEIGHT 70
#define HUB_WITDH 160
#define HUB_BBOX_HEIGHT 28
#define HUB_BBOX_WITDH 224
#define BLACK_BACKGROUND 23
#define WORLD_NUMBER_WIDTH 70
#define WORLD_NUMBER_HEIGHT 4
#define SPEED_BAR_WIDTH 28
#define SPEED_BAR_HEIGHT 4
#define LIFE1_WIDTH 80
#define LIFE1_HEIGHT 5
#define LIFE2_WIDTH 70
#define LIFE2_HEIGHT 5
#define SCORE_WIDTH 56
#define SCORE_HEIGHT 5

#define COUNT_COIN_WIDTH 24
#define COUNT_COIN_HEIGHT 4

#define TIME_WIDTH 16
#define TIME_HEIGHT 5

#define ITEM_WIDTH 52
#define ITEM_HEIGHT 5
//number
#define NUMBER_0 0
#define NUMBER_1 1
#define NUMBER_2 2
#define NUMBER_3 3
#define NUMBER_4 4
#define NUMBER_5 5
#define NUMBER_6 6
#define NUMBER_7 7
#define NUMBER_8 8
#define NUMBER_9 9
#define SPEED_FLY 0.2f
class CHUD : public CGameObject {
	static CHUD* instance;
	int world;
	int levelSpeedBar = 0;;
	ULONGLONG running_start;
	int coin;
	
public:
	CHUD();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	
	void RenderNumber(int number, float x, float y);
	void RenderNumberCoin(int coin);
	int GetLevelSpeedBar(float vx);
	void RenderSpeedBar(int lv);

	void CoinPlus() { coin++; }
};
typedef CHUD* LPHUD;