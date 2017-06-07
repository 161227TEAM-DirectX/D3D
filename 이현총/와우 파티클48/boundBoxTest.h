#pragma once
#include "gameNode.h"
#include "playerPlane.h"
#include "enemyPlane.h"

class boundBoxTest : public gameNode
{
private:
	playerPlane				_plane;
	vector<light*>			_lights;
	vector<enemyPlane*>		_enemyPlanes;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	boundBoxTest() {}
	~boundBoxTest() {}
};

