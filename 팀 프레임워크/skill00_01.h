#pragma once
#include "dxSkill.h"
class skill00_01 :	public dxSkill
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

	float _testLimitTime[8];
	float _testLimitTime2[8];
	float _testTime[8];
	float _testTime2[8];
public:
	virtual HRESULT init();
	//HRESULT init(transform * playerTrans, transform * tagetTrans);
	virtual void release();
	//void void Update();
	//virtual void update(transform* playerTrans, transform* tagetTrans);
	//virtual void update(transform* playerTrans, transform* tagetTrans);
	//void update() {};
	//virtual void render();
public:
	//virtual void Start() { _skillStartOn = true; };
	virtual bool Prepare();
	virtual bool Action();
	virtual void Finsh();
	virtual void Reset();
	//virtual void test(,transform* ...) {}
public:
	
public:
	skill00_01() {};
	~skill00_01() {};
};

