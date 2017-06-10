#pragma once
#include "gameNode.h"

class baseObject;

#define OBJECTNUM 50

class frustumTest : public gameNode
{
private:
	vector<light*>			_lights;
	vector<baseObject*>		_renderObjects;		//씬에 배치된 렌더 오브젝트 배열
	vector<baseObject*>		_cullObjects;		//컬링된 오브젝트

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	frustumTest() {}
	~frustumTest() {}
};

