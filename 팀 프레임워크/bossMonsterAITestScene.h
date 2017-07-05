#pragma once
#include "iGameNode.h"

class bossMonster;
class xPlayer;

class bossMonsterAITestScene : public iGameNode
{
private:
	bossMonster* boss;
	xPlayer* player;
	camera* _mainCamera;
	camera* _directionLightCamera;
	lightDirection* sceneBaseDirectionLight;

	terrain*			_terrain;			//����Ŭ����

public:
	bossMonsterAITestScene() { clear(); }
	~bossMonsterAITestScene() { destroy(); }

	HRESULT clear(void);
	void destroy(void);

	HRESULT init();
	void release();
	void update();
	void render();
};

