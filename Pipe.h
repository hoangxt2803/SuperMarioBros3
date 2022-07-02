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
#define PIPE_TELEPORT	1
class CPipe : public CGameObject {
	int type;
	int isTelePort;
	virtual int IsBlocking() { return 1; }
public:
	CPipe(float x, float y, int type, int isTelePort) : CGameObject(x, y) {
		this->type = type;
		this->isTelePort = isTelePort;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetType() { return this->type; }
	int GetIsTepePort() { return this->isTelePort; }
};