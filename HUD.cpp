#include "HUD.h"
#include "AssetIDs.h"
#include "Textures.h"
#include "Mario.h"
#include "PlayScene.h"


void CHUD::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + SCREEN_WIDTH;
	bottom = top + HUB_BBOX_HEIGHT;
}
CHUD::CHUD() {
	this->x = CGame::GetInstance()->GetCamX() + HUB_WITDH;
	this->y = CGame::GetInstance()->GetCamY() + SCREEN_HEIGHT - HUB_HEIGHT;
	world = 1;
	running_start = 0;
	coin = 0;
	point = 0;
	life = 3;
	time = 300;
}


void CHUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CGame* game = CGame::GetInstance();
	this->x = game->GetCamX() + HUB_WITDH;
	this->y = game->GetCamY() + SCREEN_HEIGHT - HUB_HEIGHT;
	int step = ((mario->GetIsOnPlatform() && mario->GetIsRunning())) ? 1 : -1;
	if (GetTickCount64() - running_start >= 100) {
		levelSpeedBar += step;
		running_start = GetTickCount64();
	}
	
	if (levelSpeedBar > 7) {
		levelSpeedBar = 7;
		mario->SetIsCanFly(true);
	}
	
	if (levelSpeedBar < 0)
		levelSpeedBar = 0;

}

void CHUD::Render()
{
	
	CAnimations::GetInstance()->Get(ANI_BLACK_BACKGROUND_2)->Render(x, y + BLACK_BACKGROUND);
	CAnimations::GetInstance()->Get(ANI_HUB)->Render(x, y);
	//world number
	CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_1)->Render(x - WORLD_NUMBER_WIDTH, y - WORLD_NUMBER_HEIGHT);
	//speed bar
	RenderSpeedBar(levelSpeedBar);
	//CAnimations::GetInstance()->Get(ANI_HUB_SPEED_BAR_LEVEL_MAX)->Render(x - SPEED_BAR_WIDTH, y - SPEED_BAR_HEIGHT);
	//life
	CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_0)->Render(x - LIFE1_WIDTH, y + LIFE1_HEIGHT);
	CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_3)->Render(x - LIFE2_WIDTH, y + LIFE2_HEIGHT);
	//score
	RenderNumberPoint(point);
	/*CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_0)->Render(x - SCORE_WIDTH, y + SCORE_HEIGHT);
	CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_1)->Render(x - SCORE_WIDTH + 8, y + LIFE1_HEIGHT);
	CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_2)->Render(x - SCORE_WIDTH + 16, y + LIFE1_HEIGHT);
	CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_3)->Render(x - SCORE_WIDTH + 24, y + LIFE1_HEIGHT);
	CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_4)->Render(x - SCORE_WIDTH + 32, y + LIFE1_HEIGHT);
	CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_5)->Render(x - SCORE_WIDTH + 40, y + LIFE1_HEIGHT);
	CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_6)->Render(x - SCORE_WIDTH + 48, y + LIFE1_HEIGHT);*/

	//Time
	RenderNumberTime(this->time);
	/*CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_0)->Render(x + TIME_WIDTH, y + TIME_HEIGHT);
	CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_1)->Render(x + TIME_WIDTH + 8, y + TIME_HEIGHT);
	CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_2)->Render(x + TIME_WIDTH + 16, y + TIME_HEIGHT);*/
	//Coin
	RenderNumberCoin(this->coin);
	/*CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_0)->Render(x + COUNT_COIN_WIDTH, y - COUNT_COIN_HEIGHT);
	CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_1)->Render(x + COUNT_COIN_WIDTH + 8, y - COUNT_COIN_HEIGHT);*/
	//item stack
	CAnimations::GetInstance()->Get(ANI_ITEM_STACK_1)->Render(x + ITEM_WIDTH, y);
	CAnimations::GetInstance()->Get(ANI_ITEM_STACK_2)->Render(x + ITEM_WIDTH + 24, y);
	CAnimations::GetInstance()->Get(ANI_ITEM_STACK_3)->Render(x + ITEM_WIDTH + 48, y);
}
void CHUD::RenderNumberCoin(int coin) {
	int donVi, hangChuc;
	donVi = coin % 10;
	hangChuc = coin / 10;
	RenderNumber(hangChuc, x + COUNT_COIN_WIDTH, y - COUNT_COIN_HEIGHT);
	RenderNumber(donVi, x + COUNT_COIN_WIDTH + 8, y - COUNT_COIN_HEIGHT);
}
void CHUD::RenderNumberLife(int lift)
{
}
void CHUD::RenderNumberPoint(int point)
{
	int donVi, hangChuc, hangTram, hangNgan, hangChucNgan, hangTramNgan, hangTrieu;
	donVi = point % 10;
	hangChuc = point % 100 / 10;
	hangTram = point % 1000 / 100;
	hangNgan = point % 10000 / 1000;
	hangChucNgan = point % 100000 / 10000;
	hangTramNgan = point % 1000000 / 100000;
	hangTrieu = point % 10000000 / 1000000;
	RenderNumber(hangTrieu, x - SCORE_WIDTH, y + SCORE_HEIGHT);
	RenderNumber(hangTramNgan, x - SCORE_WIDTH + 8, y + LIFE1_HEIGHT);
	RenderNumber(hangChucNgan, x - SCORE_WIDTH + 16, y + LIFE1_HEIGHT);
	RenderNumber(hangNgan, x - SCORE_WIDTH + 24, y + LIFE1_HEIGHT);
	RenderNumber(hangTram, x - SCORE_WIDTH + 32, y + LIFE1_HEIGHT);
	RenderNumber(hangChuc, x - SCORE_WIDTH + 40, y + LIFE1_HEIGHT);
	RenderNumber(donVi, x - SCORE_WIDTH + 48, y + LIFE1_HEIGHT);
}
void CHUD::RenderNumberTime(int time)
{
	int donVi, hangChuc, hangTram;
	donVi = time % 10;
	hangChuc = time % 100 / 10;
	hangTram = time % 1000 / 100;
	RenderNumber(hangTram, x + TIME_WIDTH, y + TIME_HEIGHT);
	RenderNumber(hangChuc, x + TIME_WIDTH + 8, y + TIME_HEIGHT);
	RenderNumber(donVi, x + TIME_WIDTH + 16, y + TIME_HEIGHT);
}
void CHUD::RenderNumber(int number, float x, float y) {
	switch (number)
	{
	case NUMBER_0:
		CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_0)->Render(x, y);
		break;
	case NUMBER_1:
		CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_1)->Render(x, y);
		break;
	case NUMBER_2:
		CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_2)->Render(x, y);
		break;
	case NUMBER_3:
		CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_3)->Render(x, y);
		break;
	case NUMBER_4:
		CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_4)->Render(x, y);
		break;
	case NUMBER_5:
		CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_5)->Render(x, y);
		break;
	case NUMBER_6:
		CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_6)->Render(x, y);
		break;
	case NUMBER_7:
		CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_7)->Render(x, y);
		break;
	case NUMBER_8:
		CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_8)->Render(x, y);
		break;
	case NUMBER_9:
		CAnimations::GetInstance()->Get(ANI_HUB_NUMBER_9)->Render(x, y);
		break;
	default:
		break;
	}
}

int CHUD::GetLevelSpeedBar(float v) {
	if (abs(v) < SPEED_FLY / 7)
		levelSpeedBar = SPEED_BAR_LEVEL_0;
	else if (abs(v) < SPEED_FLY * 2 / 7)
		levelSpeedBar = SPEED_BAR_LEVEL_1;
	else if (abs(v) < SPEED_FLY * 3 / 7)
		levelSpeedBar = SPEED_BAR_LEVEL_2;
	else if (abs(v) < SPEED_FLY * 4 / 7)
		levelSpeedBar = SPEED_BAR_LEVEL_3;
	else if (abs(v) < SPEED_FLY * 5 / 7)
		levelSpeedBar = SPEED_BAR_LEVEL_4;
	else if (abs(v) < SPEED_FLY * 6 / 7)
		levelSpeedBar = SPEED_BAR_LEVEL_5;
	else if (abs(v) == SPEED_FLY)
		levelSpeedBar = SPEED_BAR_LEVEL_MAX;
	return levelSpeedBar;
}
void CHUD::RenderSpeedBar(int lv) {
	switch (lv)
	{
	case 0:
		CAnimations::GetInstance()->Get(ANI_HUB_SPEED_BAR_LEVEL_0)->Render(x - SPEED_BAR_WIDTH, y - SPEED_BAR_HEIGHT);
		break;
	case 1:
		CAnimations::GetInstance()->Get(ANI_HUB_SPEED_BAR_LEVEL_1)->Render(x - SPEED_BAR_WIDTH, y - SPEED_BAR_HEIGHT);
		break;
	case 2:
		CAnimations::GetInstance()->Get(ANI_HUB_SPEED_BAR_LEVEL_2)->Render(x - SPEED_BAR_WIDTH, y - SPEED_BAR_HEIGHT);
		break;
	case 3:
		CAnimations::GetInstance()->Get(ANI_HUB_SPEED_BAR_LEVEL_3)->Render(x - SPEED_BAR_WIDTH, y - SPEED_BAR_HEIGHT);
		break;
	case 4:
		CAnimations::GetInstance()->Get(ANI_HUB_SPEED_BAR_LEVEL_4)->Render(x - SPEED_BAR_WIDTH, y - SPEED_BAR_HEIGHT);
		break;
	case 5:
		CAnimations::GetInstance()->Get(ANI_HUB_SPEED_BAR_LEVEL_5)->Render(x - SPEED_BAR_WIDTH, y - SPEED_BAR_HEIGHT);
		break;
	case 6:
		CAnimations::GetInstance()->Get(ANI_HUB_SPEED_BAR_LEVEL_6)->Render(x - SPEED_BAR_WIDTH, y - SPEED_BAR_HEIGHT);
		break;
	case 7:
		CAnimations::GetInstance()->Get(ANI_HUB_SPEED_BAR_LEVEL_MAX)->Render(x - SPEED_BAR_WIDTH, y - SPEED_BAR_HEIGHT);
		break;
	default:
		break;
	}
}

void CHUD::PointPlus(int value)
{
	 this->point += value;
}
