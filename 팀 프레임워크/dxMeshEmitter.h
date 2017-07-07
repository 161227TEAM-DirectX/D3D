#pragma once
#include "dxEmitter.h"
class dxMeshEmitter : public dxEmitter
{
private:
	tagDxParticleEX*	_ptcEx;

	tagDxParticleEX*	_ptcVertex;		//파티클 버텍스

	DWORD*				_ptcIndex;		//파티클 인덱스

	tagDxParticleEX*	_drawVertex;

	D3DXVECTOR3 _posCenter;

	dx::transform* _trans;

	

	camera _meshCamera;

	int _onePtcNum;

public:
	vector<LPD3DXMESH> _vMesh;
	//vector<LPD3DXMESH> _vMesh;
	
	LPD3DXMESH _mesh;

	DWORD _materialsNum;

	D3DMATERIAL9* _meshMaterial;

	LPDIRECT3DTEXTURE9* _meshTexture;

	D3DXVECTOR3 _vtxPosMin;
	D3DXVECTOR3 _vtxPosMax;

public:


public:
	virtual HRESULT init(string xFileName, int OneTimePaticleNum = 10, float spawnTime = 0.1f, int totalPaticleNum = 1.0f);
	virtual void relese();
	virtual void update();
	virtual void render();
	//virtual void reset() {};

private:
	//void ActiveUpdatePlane(tagDxParticleEX * ptcVertex, DWORD * ptcIndex, vector<tagDxAttribute>::iterator iter, DWORD drawParticleNum);




public:
	dxMeshEmitter()
	{
		//이미터 초기화
		this->EmitterInit();
		//이미터 타입 설정
		_EmitterType = ET_MESH;		

	};
	virtual ~dxMeshEmitter() {};
};
