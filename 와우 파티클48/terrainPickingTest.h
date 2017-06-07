#pragma once
#include "gameNode.h"
#include "terrain.h"

class terrainPickingTest : public gameNode
{
private:
	terrain*		_terrain;	//����Ŭ����
	transform*		_trans;		//Ʈ������
	lightDirection* _dirLight;	//�𷺼Ƕ���Ʈ
	D3DXVECTOR3		_hitPos;	//��Ʈ ������

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	terrainPickingTest() {}
	~terrainPickingTest() {}
};

