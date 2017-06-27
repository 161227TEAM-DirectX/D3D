#pragma once
#include "dxEmitter.h"


class dxPointEmitter : public dxEmitter
{
private:
	//dxModule* _module;

	D3DXMATRIX _matWorld;

	//tagDxParticle* ptcVtx;

	string _textureFileName;

	int _vbMaxStep;
	
	LPDIRECT3DTEXTURE9 _testTex;
	LPDIRECT3DTEXTURE9 _testTex2;

	int limitCycle;
	int currentCycle;
	bool cycleOn;
	 
	tagDxParticle* _ptcVtx;
	tagDxParticle* _drawVtx;


public:
	virtual HRESULT init(string textureFileName, int OneTimePaticleNum = 10, float spawnTime = 1.0f, int totalPaticleNum = 0);
	//vietual HRESULT init(string textureFileName, int OneTimePaticleNum = 10, float spawnTime = 1.0f, int allPaticleNum = 200);
	virtual void relese();
	virtual void update();
	virtual void render();

public:
	////리셋
	//void reset()
	//{
	//	_ptcList.clear();
	//	_ptcList.resize(_totalPtcNum);
	//	_currentDelayTime = 0.0f;
	//	//_spawnCurrentTime = _spawnTime;
	//	if (_startDelayTimeOn)
	//	{
	//		_spawnCurrentTime = 0.0f;	
	//	}
	//	else 
	//	{	
	//		_spawnCurrentTime = _spawnTime; 
	//	}
	//}
public:
	/*void CopyInit()
	{
		_ptcVtx = NULL;
		_ptcVtx = new tagDxParticle[(int)_vbSize];
		_drawVtx = NULL;
		_drawVtx = new tagDxParticle[(int)_vbSize];
	}*/

public:
	dxPointEmitter()
	{
		//이미터 초기화
		this->EmitterInit();
		//이미터 타입 설정
		_EmitterType = ET_POINT;
		
	};
	virtual ~dxPointEmitter() {};
	
};

