#pragma once
#include "dxEmitter.h"
#include "dxParticle.h"

class dxPlaneEmitter : public dxEmitter
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
	//virtual void reset();

private:
	void InitCreatePlane(tagDxParticleEX* ptcVertex, DWORD * ptcIndex, vector<tagDxAttribute>::iterator iter, DWORD drawParticleNum);

	void ActiveUpdatePlane(tagDxParticleEX * ptcVertex, DWORD * ptcIndex, vector<tagDxAttribute>::iterator iter, DWORD drawParticleNum);



public:
	dxPlaneEmitter()
	{
		//이미터 초기화
		this->EmitterInit();
		//이미터 타입 설정
		_EmitterType = ET_PLANE;

	};
	~dxPlaneEmitter() {};
};

