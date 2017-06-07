#pragma once
#include "gameNode.h"
#include "terrain.h"

class terrainTest : public gameNode
{
private:
	camera _mainCamera;
	terrain* _terrain;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	terrainTest() {}
	~terrainTest() {}
};

