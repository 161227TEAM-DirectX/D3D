#pragma once
#include "iGameNode.h"

class cTerrainTest3 : public iGameNode
{
private:
	camera			m_csCamera;		//ī�޶�
	terrain			m_csTerrain;	//����
	lightDirection  m_csLightDir;	//����
	D3DXVECTOR3		m_vHitPos;		//��ŷ��ġ
	D3DXVECTOR2		m_vSelectIdx;	//��ŷ�� ���� �ε���

public:
	cTerrainTest3();
	virtual ~cTerrainTest3();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

