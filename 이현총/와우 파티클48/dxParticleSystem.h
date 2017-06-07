#pragma once
#include "dxEmitter.h"

class dxParticleSystem
{
public:

private:
	vector<dxEmitter*> _vEmitter;
	vector<dxEmitter*>::iterator _Iter;

private:
	bool _isActive;			//활성화
	transform* _trans;

	//시간용
	float _limitTime;
	float _currentTime;
	//D3DXMATRIX _matWorld;

	//float _
	//float _currentTime;
	//bool _timeOn;

	//카운터용
	int _EmitterCountNum;

public:
	HRESULT init();
	void addEmitter(dxEmitter* emitter);
	void reset();
	void update();
	void render();

public:
	//활성화 접근
	void SetActive(bool inActive) { _isActive = inActive; };
	bool GetActive() { return _isActive; }
	//시간
	void SetLimitTime(float inTime) { _limitTime = inTime; };
	float GetLimitTime(void) { return _limitTime; }

	void SetTime(float inTime) { _currentTime = inTime; };
	float GetTime(void) { return _currentTime; }
	
	//트랜스폼
	transform* Transform() { return _trans; }
	//벡터 접근
	vector<dxEmitter*> &GetPaticles() { return _vEmitter; }


	/*void init()
	{
		_transform = new transform;
		_transform->SetWorldPosition(0,0,0);
	}
	void setStartPoint(D3DXVECTOR3 pos)
	{
		_transform->SetWorldPosition(pos);
	}*/

public:
	dxParticleSystem()
	{
		_trans = new transform; bool isActive = true; 
		_limitTime = 0.0f;
		_currentTime = 0.0f;
		_EmitterCountNum = 0;
	}
	~dxParticleSystem() {}
};

