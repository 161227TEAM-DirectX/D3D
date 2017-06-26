#pragma once
#include "iGameNode.h"
class cMinimapTest2 : public iGameNode
{
private:
	baseObject			_player;	//플레이어 오브젝트
	baseObject			_enemy;		//에너미 오브젝트
	vector<light*>		_lights;	//광원
	bool				_isHit;		//충돌했냐?
	camera				_mainCamera;

public:
	cMinimapTest2();
	virtual ~cMinimapTest2();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

