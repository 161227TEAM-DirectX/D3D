#pragma once
#include "dxEmitter.h"

class dxBoardEmitter : public dxEmitter
{
private:
	tagDxParticleEX*	 _ptcEx;
	
	tagDxParticleEX*	_ptcVertex;		//��ƼŬ ���ؽ�
	
	DWORD*				_ptcIndex;		//��ƼŬ �ε���
	
	tagDxParticleEX*	_drawVertex;

	//D3DXVECTOR3* _posCenter;

	dx::transform* _trans;



	int _onePtcNum;

public:
	virtual HRESULT init(string textureFileName, int OneTimePaticleNum = 10, float spawnTime = 0.1f, int totalPaticleNum = 1.0f);
	virtual void release();
	virtual void update();
	virtual void render();
	//virtual void reset() {};

private:
	void ActiveUpdatePlane(tagDxParticleEX * ptcVertex, DWORD * ptcIndex, vector<tagDxAttribute>::iterator iter, DWORD drawParticleNum);


public:
	dxBoardEmitter()
	{
		//�̹��� �ʱ�ȭ
		this->EmitterInit();

		//�̹��� Ÿ�� ����
		_EmitterType = ET_BOARD;


	};
	virtual ~dxBoardEmitter() {};
};

