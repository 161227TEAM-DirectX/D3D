#pragma once
#include "dxParticleSystem.h"


class dxEffect
{
private:

	//dxParticleSystem* _ps;

	bool _startOn;

	bool _oneSettingOn;

	float _limitTime;
	float _currentTime;

	int _effectMax;

	string _psName;

	vector<dxParticleSystem*> _vPS;

	//위치와 방향 받기
	vector<D3DXVECTOR3*> _vPos;
	vector<D3DXVECTOR3*> _vDir;
	vector<D3DXVECTOR3*>::iterator _posIter;
	vector<D3DXVECTOR3*>::iterator _dirIter;

	vector<dx::transform*> _vPosTrans;
	vector<dx::transform*> _vDirTrans;


public:
	HRESULT init();
	void release();
	void update();
	void render();

public:
	//기본들
	void setPS(string psName) { _psName = psName; }
	//void setPositoin(D3DXVECTOR3* pos);
	//void setDirection(D3DXVECTOR3* dir) { this->_vDir.push_back(dir); }

	//void setPosTrans(dx::transform* posTrans);

	//void setLimitTime(float inTime) { _limitTime = inTime; };

	void setLimitTime(float inTime)
	{
		for (int i = 0; i < 12; i++)
		{
			_vPS[i]->SetLimitTime(inTime);
		}
		
		//_limitTime = inTime;
	}
	//void Start() { _startOn = true; };
	//void Start(D3DXVECTOR3* pos, D3DXVECTOR3* dir);//실패(주소는)

	void Start(dx::transform* posTrans, dx::transform* dirTrans = NULL);

	

public:
	dxEffect()
	{
		_startOn = false;
		_oneSettingOn = true;
		_currentTime = 0;
		_limitTime = 0;
	};
	~dxEffect() {};
};

