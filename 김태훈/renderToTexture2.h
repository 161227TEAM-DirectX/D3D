#pragma once
#include "gameNode.h"

#define OBJECT_NUM 10

class renderToTexture2 : public gameNode
{
private:
	vector<light*>			_lights;			//광원
	vector<baseObject*>		_renderObjects;		//씬에 배치된 렌더 오브젝트 배열
	vector<baseObject*>		_cullObjects;		//컬링된 오브젝트
	camera*					_extraCam;			//추가 카메라

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void renderSprite(void);

	renderToTexture2() {}
	~renderToTexture2() {}
};

