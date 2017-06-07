#pragma once
#include "gameNode.h"

class collisionTest : public gameNode
{
private:
	baseObject		_player;	//플레이어 오브젝트
	baseObject		_enemy;		//에너미 오브젝트
	vector<light*>	_lights;	//조명
	bool			_isHit;		//충돌했냐?

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	collisionTest() {}
	~collisionTest() {}
};

