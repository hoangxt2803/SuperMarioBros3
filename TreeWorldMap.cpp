#include "Animations.h"
#include "TreeWorldMap.h"
void CTreeWorldMap::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_TREE_WORLD_MAP)->Render(x, y);

}
CTreeWorldMap::CTreeWorldMap(float x, float y) : CGameObject(x, y) {};