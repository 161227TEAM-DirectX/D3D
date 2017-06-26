#pragma once
#include "iGameNode.h"
class cMinimapTest2 : public iGameNode
{
private:
	baseObject			_player;	//�÷��̾� ������Ʈ
	baseObject			_enemy;		//���ʹ� ������Ʈ
	vector<light*>		_lights;	//����
	bool				_isHit;		//�浹�߳�?
	camera				_mainCamera;

public:
	cMinimapTest2();
	virtual ~cMinimapTest2();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

