#pragma once
#include "iGameNode.h"

class cMinimapTest : public iGameNode
{
private:
	terrain*		_terrain;
	camera			_mainCamera;
	lightDirection* _baseLight;
	D3DXVECTOR3		_hitPos;

	float miniX = 0;
	float miniY = 0;
	float miniWidth = 0;
	float miniHeight = 0;

	float moveX = 0;
	float moveY = 0;

	//�ʵ忡�� ������ ����
private:
	baseObject			_player;	//�÷��̾� ������Ʈ
	vector<light*>		_lights;	//����

									//�̴ϸʿ��� ������ ����
private:
	float miniMoveX = 0;
	float miniMoveY = 0;
	float angle = 0.0f;
	D3DXVECTOR3 dir ={ 0,0,1 };
	float moveValue;

public:
	cMinimapTest();
	virtual ~cMinimapTest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

