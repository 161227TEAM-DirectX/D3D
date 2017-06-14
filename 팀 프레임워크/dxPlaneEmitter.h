#pragma once
#include "dxEmitter.h"
#include "dxParticle.h"

class dxPlaneEmitter : public dxEmitter
{
private:
	tagDxParticleEX*	 _ptcEx;
	
	tagDxParticleEX*	_ptcVertex;		//��ƼŬ ���ؽ�
	
	DWORD*				_ptcIndex;		//��ƼŬ �ε���
	
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
		//��� �ʱ�ȭ
		_module = new dxModuleKit;
		_trans = new dx::transform;
		_module->init();
		//�̹��� Ÿ�� ����
		_EmitterType = ET_PLANE;

		_posCenter = D3DXVECTOR3(0,0,0);
		_activeTimeCheckOn = FALSE;
		_activeCurrentTime = 0.0f;
		_activeLimitTime = 0.0f;


	};
	~dxPlaneEmitter() {};
};

