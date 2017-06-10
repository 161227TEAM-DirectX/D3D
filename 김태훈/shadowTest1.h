#pragma once
#include "gameNode.h"

class shadowTest1 : public gameNode
{
private:
	vector<baseObject*>	_renderObjects;	//���� ��ġ�� ���� ������Ʈ �迭
	vector<baseObject*>	_cullObjects;	//�ø��� ������Ʈ

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void renderSprite(void);

	shadowTest1() {}
	~shadowTest1() {}
};

