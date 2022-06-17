#include "Animations.h"
#include "TreeWorldMap.h"
void CTreeWorldMap::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if(type == TYPE_NONE)
		animations->Get(ID_ANI_TREE_WORLD_MAP)->Render(x, y);
	else if(type == TYPE_TREE)
		animations->Get(ID_ANI_NONE_WORLD_MAP)->Render(x, y);
	animations->Get(ID_ANI_TREE_WORLD_MAP)->Render(x, y);
}
void CTreeWorldMap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 12 / 2;
	t = y - 12 / 2;
	r = l + 12;
	b = t + 12;
}
CTreeWorldMap::CTreeWorldMap(float x, float y, int type) : CGameObject(x, y) {
	this->type = type;
}