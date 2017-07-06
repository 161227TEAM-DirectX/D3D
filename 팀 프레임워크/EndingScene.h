#pragma once
#include "iGameNode.h"
#include "mapObject.h"
#include "terrain.h"
#include "Environment.h"
#include "WaterTerrain.h"

class EndingScene : public iGameNode
{
private:
	terrain*			_terrain;
	mapObject          objectSet;
	Environment		env;
	WaterTerrain		water;
private:
	camera* _camera;
	lightDirection sceneBaseDirectionLight;
	vector<baseObject*> _renderObject;
	tagSaveMap envTemp;
	tagSaveMap waterTemp;

	vector<baseObject*> npcVector;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void meshInit();

	EndingScene() {}
	~EndingScene() {}
};

