#pragma once
#include "gameNode.h"

class baseObject;

#define OBJECTNUM 50

class frustumTest : public gameNode
{
private:
	vector<light*>			_lights;
	vector<baseObject*>		_renderObjects;		//���� ��ġ�� ���� ������Ʈ �迭
	vector<baseObject*>		_cullObjects;		//�ø��� ������Ʈ

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	frustumTest() {}
	~frustumTest() {}
};

