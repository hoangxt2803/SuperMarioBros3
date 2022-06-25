#include <iostream>
#include <fstream>

#include "WorldMap.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Utils.h"
#include "AssetIDs.h"
#include "TreeWorldMap.h"

#include "Mario.h"

using namespace std;

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_MAPS	3
#define SCENE_SECTION_HUD	4

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

CWorldMap::CWorldMap(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	hud = NULL;
	player = NULL;
	key_handler = new WorldMapSceneKeyHandler(this);
}

void CWorldMap::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CWorldMap::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CWorldMap::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(i) + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS]
*/
void CWorldMap::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO: {
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		int inWorldMap = atoi(tokens[3].c_str());
		obj = new CMario(x, y, inWorldMap);
		//DebugOut(L"[INFO] Player object has been created!\n");
		player = (CMario*)obj;
		///DebugOut(L"[INFO] Player object has been created!\n");
		break;
	}
	case OBJECT_TYPE_TREE_WORLD_MAP: {
		int type = atoi(tokens[3].c_str());
		obj = new CTreeWorldMap(x, y, type);
		//DebugOut(L"[INFO] Tree world map object has been created!\n");
		break;
	}
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

/*
	Parse a line in section [MAPS]
*/


void CWorldMap::_ParseSection_HUD(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	hud = new CHUD();

}
void CWorldMap::LoadAssets(LPCWSTR assetFile)
{
	//DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	//DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CWorldMap::Load()
{
	//DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[HUD]") { section = SCENE_SECTION_HUD; continue; };
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_HUD: _ParseSection_HUD(line); break;
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	//DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CWorldMap::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;
	CGame::GetInstance()->SetCamPos(0, 0);

	hud->Update(dt, &coObjects);
	PurgeDeletedObjects();
}

void CWorldMap::Render()
{
	CAnimations::GetInstance()->Get(ANI_BLACK_BACKGROUND)->Render(50, 120);
	hud->Render();
	CAnimations::GetInstance()->Get(5000)->Render(155, 82);
	//CMap::getInstance()->Render();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
*	Clear all objects from this scene
*/
void CWorldMap::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
	//CMap::getInstance()->Clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void CWorldMap::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	//DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CWorldMap::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }
vector<LPGAMEOBJECT> CWorldMap::GetObjects() { return objects; }
void CWorldMap::AddObject(CGameObject* obj) {
	objects.push_back(obj);
}
void CWorldMap::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CWorldMap::IsGameObjectDeleted),
		objects.end());
}



void WorldMapSceneKeyHandler::KeyState(BYTE* states)
{
}

void WorldMapSceneKeyHandler::OnKeyDown(int KeyCode)
{
	CMario* mario = (CMario*)((LPWORLDMAP)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (KeyCode)
	{
	case DIK_DOWN: {
		mario->WalkDown();
		break;
	}
	case DIK_UP: {
		mario->WalkUp();
		break;
	}
	case DIK_LEFT: {
		mario->WalkLeft();
		break;
	}
	case DIK_RIGHT: {
		mario->WalkRight();
		break;
	}
	case DIK_S: {
		CGame::GetInstance()->InitiateSwitchScene(1);
		CWorldMap* WorldMapScene = (LPWORLDMAP)CGame::GetInstance()->GetCurrentScene();
		WorldMapScene->Clear();
		break;
	}
	default:
		break;
	}
}

void WorldMapSceneKeyHandler::OnKeyUp(int KeyCode)
{
}