#pragma once
#include "dxEmitter.h"
class dxMeshEmitter : public dxEmitter
{
private:
	tagDxParticleEX*	 _ptcEx;

	tagDxParticleEX*	_ptcVertex;		//��ƼŬ ���ؽ�

	DWORD*				_ptcIndex;		//��ƼŬ �ε���

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
		//��� �ʱ�ȭ
		_module = new dxModuleKit;
		_trans = new dx::transform;
		_module->init();
		//�̹��� Ÿ�� ����
		_EmitterType = ET_MESH;

		_posCenter = D3DXVECTOR3(0, 0, 0);

		_activeTimeCheckOn = FALSE;
		_activeCurrentTime = 0.0f;
		_activeLimitTime = 0.0f;

	};
	~dxMeshEmitter() {};
};
