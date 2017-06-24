#pragma once
#include "dxEmitter.h"
#include <thread>

class dxParticleSystem
{
public:

private:
	vector<dxEmitter*> _vEmitter;
	vector<dxEmitter*>::iterator _Iter;

private:
	bool _isActive;			//활성화
	dx::transform* _trans;

	//시간용
	float _limitTime;
	float _currentTime;
	//D3DXMATRIX _matWorld;

	//float _
	//float _currentTime;
	//bool _timeOn;

	//카운터용
	int _EmitterCountNum;

	bool _AllRealTimeTrackingOn;

	//쓰레드
	//thread* _randerThread;

	//thread _testThread;
	//bool _randerThreadOneSettingOn;

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
	dx::transform* Transform() { return _trans; }
	//벡터 접근
	vector<dxEmitter*> &GetPaticles() { return _vEmitter; }

	//자동 시간 리셋
	bool autoTimeReset(bool ResetFunOn = true);

	void setAllRealTimeTrackingOn(bool realTimeTrackingOn) { _AllRealTimeTrackingOn = realTimeTrackingOn; };

	//렌더 쓰레드 -> 생각해보니 이렇게 쓰면 쓰레드 의미가 없다......고로 안씀
	//void autoRenderThread(void)
	//{
	//	//초기화
	//	if (_randerThreadOneSettingOn)
	//	{
	//		
	//		_randerThread = new thread[_vEmitter.size()];
	//		
	//		_randerThreadOneSettingOn = FALSE;
	//	}

	//	for (int i = 0; i < _vEmitter.size(); i++)
	//	{
	//		//
	//		_randerThread[i] = thread(&vEmitterRender, i);
	//		//_randerThread[i] = thread(&vEmitter->rander));

	//	}

	//	for (int i = 0; i < _vEmitter.size(); i++)
	//	{
	//		_randerThread[i].join();
	//	}

	//}
	//void vEmitterRender(int i)
	//{
	//	_vEmitter[i]->render();
	//}



public:
	dxParticleSystem()
	{
		_trans = new dx::transform;
		bool isActive = true;
		_limitTime = 0.0f;
		_currentTime = 0.0f;
		_EmitterCountNum = 0;

		_AllRealTimeTrackingOn = false;

		//렌더 쓰레드
		//_randerThreadOneSettingOn = false;
	}
	~dxParticleSystem() {}
};

