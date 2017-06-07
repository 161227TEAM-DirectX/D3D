#pragma once
#include "gameNode.h"

class gizmoTestScene : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	gizmoTestScene() {}
	~gizmoTestScene() {}
};

