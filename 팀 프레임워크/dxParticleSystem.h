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
	bool _isActive;			//Ȱ��ȭ
	dx::transform* _trans;

	//�ð���
	float _limitTime;
	float _currentTime;
	//D3DXMATRIX _matWorld;

	//float _
	//float _currentTime;
	//bool _timeOn;

	//ī���Ϳ�
	int _EmitterCountNum;

	bool _AllRealTimeTrackingOn;

	//������
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
	//Ȱ��ȭ ����
	void SetActive(bool inActive) { _isActive = inActive; };
	bool GetActive() { return _isActive; }
	//�ð�
	void SetLimitTime(float inTime) { _limitTime = inTime; };
	float GetLimitTime(void) { return _limitTime; }

	void SetTime(float inTime) { _currentTime = inTime; };
	float GetTime(void) { return _currentTime; }

	//Ʈ������
	dx::transform* Transform() { return _trans; }
	//���� ����
	vector<dxEmitter*> &GetPaticles() { return _vEmitter; }

	//�ڵ� �ð� ����
	bool autoTimeReset(bool ResetFunOn = true);

	void setAllRealTimeTrackingOn(bool realTimeTrackingOn) { _AllRealTimeTrackingOn = realTimeTrackingOn; };

	//���� ������ -> �����غ��� �̷��� ���� ������ �ǹ̰� ����......��� �Ⱦ�
	//void autoRenderThread(void)
	//{
	//	//�ʱ�ȭ
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

		//���� ������
		//_randerThreadOneSettingOn = false;
	}
	~dxParticleSystem() {}
};

