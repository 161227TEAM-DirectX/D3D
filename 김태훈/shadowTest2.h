#pragma once
#include "gameNode.h"

#define OBJECT_NUM 30

class shadowTest2 : public gameNode
{
private:
	vector<baseObject*>		_renderObjects;		//씬에 배치된 랜더 오브젝트 배열
	vector<baseObject*>		_cullObjects;		//컬링된 오브젝트

	terrain*				_terrain;			//지형
	terrain*				_terrainShadow;		//지형 그림자

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void renderSprite(void);

	shadowTest2() {}
	~shadowTest2() {}
};

