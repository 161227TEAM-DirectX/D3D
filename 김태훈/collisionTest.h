#pragma once
#include "gameNode.h"

class collisionTest : public gameNode
{
private:
	baseObject		_player;	//�÷��̾� ������Ʈ
	baseObject		_enemy;		//���ʹ� ������Ʈ
	vector<light*>	_lights;	//����
	bool			_isHit;		//�浹�߳�?

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	collisionTest() {}
	~collisionTest() {}
};

