#pragma once
#include "dxEmitter.h"

class dxBeamEmitter : public dxEmitter
{
private:
	tagDxParticleEX*	 _ptcEx;
	
	tagDxParticleEX*	_ptcVertex;		//파티클 버텍스
	
	DWORD*				_ptcIndex;		//파티클 인덱스
	
	tagDxParticleEX*	_drawVertex;

	D3DXVECTOR3 _posCenter;

	dx::transform* _trans;


	int _onePtcNum;

public:
	virtual HRESULT init(string textureFileName, int OneTimePaticleNum = 10, float spawnTime = 0.1f, int totalPaticleNum = 1.0f);
	virtual void relese();
	virtual void update();
	virtual void render();
	//virtual void reset() {};

private:
	void ActiveUpdatePlane(tagDxParticleEX * ptcVertex, DWORD * ptcIndex, vector<tagDxAttribute>::iterator iter, DWORD drawParticleNum);




public:
	dxBeamEmitter()
	{
		//모듈 초기화
		_module = new dxModuleKit;
		_trans = new dx::transform;
		_module->init();
		//이미터 타입 설정
		_EmitterType = ET_BOARD;

		_posCenter = D3DXVECTOR3(0, 0, 0);
	};
	~dxBeamEmitter() {};
};

