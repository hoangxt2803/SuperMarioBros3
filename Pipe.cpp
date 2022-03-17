#include "Pipe.h"

void CPipe::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (type == PIPE_TYPE_1) {
		animations->Get(ID_ANI_PIPE_1)->Render(x, y);
	}
	else {
		animations->Get(ID_ANI_PIPE_2)->Render(x, y);
	}

	RenderBoundingBox();
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PIPE_BBOX_WIDTH / 2;
	t = y - PIPE_BBOX_HEIGHT / 2;
	r = l + PIPE_BBOX_WIDTH;
	b = t + PIPE_BBOX_HEIGHT;
}