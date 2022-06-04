#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Mario.h"
#include "HUD.h"
//#include "Koopas.h"


class CIntro : public CScene
{
protected:
	vector<LPGAMEOBJECT> objects;
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void LoadAssets(LPCWSTR assetFile);

public:
	CIntro(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	vector<LPGAMEOBJECT> GetObjects();
	void Clear();
	void PurgeDeletedObjects();
	void AddObject(CGameObject* obj);
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CIntro* LPINTRO;

class IntroSceneKeyHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	IntroSceneKeyHandler(CScene* s) :CSceneKeyHandler(s) {}
};