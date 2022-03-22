#pragma once
#include "GameObject.h"


#define HIDDEN_BBOX_WIDTH 10
#define HIDDEN_BBOX_HEIGHT 150

class CHiddenObject : public CGameObject {
	
public:
	CHiddenObject(float x, float y) : CGameObject(x,y){}
	void Update(DWORD dt) {}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }

};