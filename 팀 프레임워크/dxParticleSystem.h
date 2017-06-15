#pragma once
#include "dxEmitter.h"

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


public:
	dxParticleSystem()
	{
		_trans = new dx::transform;
		bool isActive = true;
		_limitTime = 0.0f;
		_currentTime = 0.0f;
		_EmitterCountNum = 0;
	}
	~dxParticleSystem() {}
};

