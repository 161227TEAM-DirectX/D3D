#pragma once
#include "iGameNode.h"

class cTerrainTest : public iGameNode
{
private:
	terrain* _terrain;			//����
	camera			_mainCamera;
	lightDirection* _sceneBaseDirectionLight;	//���� ��ġ�� �⺻������

	D3DXVECTOR3		_hitPos;	//��Ʈ ������

public:
	cTerrainTest();
	virtual ~cTerrainTest();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

