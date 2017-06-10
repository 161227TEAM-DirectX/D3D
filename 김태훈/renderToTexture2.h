#pragma once
#include "gameNode.h"

#define OBJECT_NUM 10

class renderToTexture2 : public gameNode
{
private:
	vector<light*>			_lights;			//����
	vector<baseObject*>		_renderObjects;		//���� ��ġ�� ���� ������Ʈ �迭
	vector<baseObject*>		_cullObjects;		//�ø��� ������Ʈ
	camera*					_extraCam;			//�߰� ī�޶�

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void renderSprite(void);

	renderToTexture2() {}
	~renderToTexture2() {}
};

