#include "HiddenObject.h"

void CHiddenObject::Render()
{
	//RenderBoundingBox();
}

void CHiddenObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - HIDDEN_BBOX_WIDTH / 2;
	t = y - HIDDEN_BBOX_HEIGHT / 2;
	r = l + HIDDEN_BBOX_WIDTH;
	b = t + HIDDEN_BBOX_HEIGHT;
}