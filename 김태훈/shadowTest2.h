#pragma once
#include "gameNode.h"

#define OBJECT_NUM 30

class shadowTest2 : public gameNode
{
private:
	vector<baseObject*>		_renderObjects;		//���� ��ġ�� ���� ������Ʈ �迭
	vector<baseObject*>		_cullObjects;		//�ø��� ������Ʈ

	terrain*				_terrain;			//����
	terrain*				_terrainShadow;		//���� �׸���

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void renderSprite(void);

	shadowTest2() {}
	~shadowTest2() {}
};

