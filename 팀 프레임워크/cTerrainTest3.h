#pragma once
#include "iGameNode.h"

class cTerrainTest3 : public iGameNode
{
private:
	camera			m_csCamera;		//카메라
	terrain			m_csTerrain;	//지형
	lightDirection  m_csLightDir;	//광원
	D3DXVECTOR3		m_vHitPos;		//피킹위치
	D3DXVECTOR2		m_vSelectIdx;	//피킹시 지형 인덱스

public:
	cTerrainTest3();
	virtual ~cTerrainTest3();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

