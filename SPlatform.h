#include "Platform.h"
class SPlatform : public CPlatform {

public:
	SPlatform(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end) :CPlatform(x, y, cell_width,
			cell_height, length, sprite_id_begin, sprite_id_middle, sprite_id_end) {}
	virtual int IsSPlatform() { return 1; }
	void RenderBoundingBox();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Render();
};