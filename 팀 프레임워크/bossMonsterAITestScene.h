#pragma once
#include "iGameNode.h"

class bossMonster;
class xPlayer;
class monster;

class bossMonsterAITestScene : public iGameNode
{
private:
	bossMonster* boss;
	vector<monster*> mon;
	xPlayer* player;
	camera* _mainCamera;
	camera* _directionLightCamera;
	lightDirection* sceneBaseDirectionLight;

	terrain*			_terrain;			//지형클래스

public:
	bossMonsterAITestScene() { clear(); }
	~bossMonsterAITestScene() { destroy(); }

	HRESULT clear(void);
	void destroy(void);

	void InitMonster(void);
	
	string findMonsterName(int & Name);
	xMesh* findMonster(int & index);

	HRESULT init();
	void release();
	void update();
	void render();
};

