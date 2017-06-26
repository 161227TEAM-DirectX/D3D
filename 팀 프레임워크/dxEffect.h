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


	string _psName;

	vector<dxParticleSystem*> _vPS;

	//위치와 방향 받기
	vector<D3DXVECTOR3*> _vPos;
	vector<D3DXVECTOR3*> _vDir;
	vector<D3DXVECTOR3*>::iterator _posIter;
	vector<D3DXVECTOR3*>::iterator _dirIter;

	vector<dx::transform*> _vPosTrans;


public:
	HRESULT init();
	void update();
	void render();

public:
	//기본들
	void setPS(string psName) { _psName = psName; }
	void setPositon(D3DXVECTOR3* pos) { this->_vPos.push_back(pos); }
	void setDirection(D3DXVECTOR3* dir) { this->_vDir.push_back(dir); }

	void setPosTrans(dx::transform* posTrans) { this->_vPosTrans.push_back(posTrans); }

	void setLimitTime(float inTime) { _limitTime = inTime; };
	void Start() { _startOn = true; };
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

