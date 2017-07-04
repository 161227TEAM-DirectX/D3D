#pragma once
#include "iGameNode.h"

class cTerrainTest2 : public iGameNode
{
private:
	terrain			m_csTerrain;
	camera			m_csCamera;
	lightDirection  m_csLightDir;
	D3DXVECTOR3		m_vHitPos;

private:
	string			m_sCurTex;
	D3DXVECTOR3		m_vSelectPos;
	D3DXVECTOR3		m_vSelectColor;
	D3DXVECTOR2		m_vSelectIdx;

	LPDIRECT3DTEXTURE9 m_pSplatBase;
	int m_nSplatRange;		//»öÄ¥ ¹üÀ§
	D3DXVECTOR3		m_vSelectRangePos;

public:
	cTerrainTest2();
	virtual ~cTerrainTest2();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

