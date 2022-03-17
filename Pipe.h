#pragma once

#include "GameObject.h"

#define ID_ANI_PIPE_1 11100	
#define ID_ANI_PIPE_2 11101	
#define PIPE_WIDTH 32
#define PIPE_HEIGHT 16
#define PIPE_BBOX_WIDTH 32
#define PIPE_BBOX_HEIGHT 16
#define PIPE_TYPE_1	1
#define PIPE_TYPE_2	2
class CPipe : public CGameObject {
	int type;
	virtual int IsBlocking() { return 1; }
public:
	CPipe(float x, float y, int type) : CGameObject(x, y) {
		this->type = type;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};