#pragma once
#include "iGameNode.h"
#include "mapObject.h"
#include "terrain.h"
#include "Environment.h"
#include "WaterTerrain.h"

enum ENDINGNUMBER { EONE = 1, ETWO, ETHREE, EFOUR, EFIVE, SIX };

struct ENDINGTEXURES
{
	LPDIRECT3DTEXTURE9 tex;
	RECT rc1, rc2;
};

class EndingScene : public iGameNode
{
private:
	terrain*		_terrain;
	mapObject		objectSet;
	Environment		env;
	WaterTerrain	water;

private:
	camera* _camera;
	lightDirection sceneBaseDirectionLight;
	vector<baseObject*> _renderObject;
	tagSaveMap envTemp;
	tagSaveMap waterTemp;

	vector<baseObject*> npcVector;
	ENDINGTEXURES directxBye;
	ENDINGTEXURES directxBye2;
	int byeX;
	int byeY;
	bool stop;
public:
	EndingScene();
	~EndingScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void meshInit();

	void loadingScene();
};

extern EndingScene* ex_pEnding;
