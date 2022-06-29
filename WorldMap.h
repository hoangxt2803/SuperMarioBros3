#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Mario.h"
#include "HUD.h"
#include "Map.h"
//#include "Koopas.h"


class CWorldMap : public CScene
{
protected:
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;
	LPHUD hud;
	LPMAP map;
	vector<LPGAMEOBJECT> objects;
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	//map
	void _ParseSection_MAPS(string line);
	//HUD
	void _ParseSection_HUD(string line);
	void LoadAssets(LPCWSTR assetFile);

public:
	CWorldMap(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }
	LPHUD GetHUD() { return hud; }
	vector<LPGAMEOBJECT> GetObjects();
	void Clear();
	void PurgeDeletedObjects();
	void AddObject(CGameObject* obj);
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CWorldMap* LPWORLDMAP;

class WorldMapSceneKeyHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	WorldMapSceneKeyHandler(CScene* s) :CSceneKeyHandler(s) {}
};