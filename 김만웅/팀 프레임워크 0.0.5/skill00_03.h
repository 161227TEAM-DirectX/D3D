#pragma once
#include "dxSkill.h"
class skill00_03 :	public dxSkill
{
private:
	/*bool _skillStartOn;
	bool _skillActionOn;
	bool _skillFinshOn;*/

	//transform* _playerTrans;
	//transform* _targetTrans;

	/*boundSphere _playerSphereCollisoin;
	boundSphere _targetSphereCollisoin;*/

	bool _oneSettingOn;

	float _currentTime;
	float _isActiveTime;
	int _activeNum;

	int _endCount;

	D3DXVECTOR3* _firstPlayerPos;
	D3DXVECTOR3* _SelfPos;

	float _testLimitTime[8];
	float _testLimitTime2[8];
	float _testTime[8];
	float _testTime2[8];

	D3DXVECTOR3 circlePositionY;

	tagBezierPoint* _BP;
	//float* _bpTime;
	float _bpTime[8];

public:
	virtual HRESULT init();
	//HRESULT init(transform * playerTrans, transform * tagetTrans);
	virtual void release();
	
public:
	//virtual void Start() { _skillStartOn = true; };
	virtual bool Prepare();
	virtual bool Action();
	virtual void Finsh();
	virtual void Reset();
	//virtual void test(,transform* ...) {}
public:
	
public:
	skill00_03() {};
	~skill00_03() {};
};

