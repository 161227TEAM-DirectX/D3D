#pragma once
#include "dxSkill.h"
class skill00 :	public dxSkill
{
private:
	/*bool _skillStartOn;
	bool _skillActionOn;
	bool _skillFinshOn;*/

	//transform* _playerTrans;
	//transform* _targetTrans;

	/*boundSphere _playerSphereCollisoin;
	boundSphere _targetSphereCollisoin;*/


	/*float _testTime;
	float _testTime2;*/
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

	virtual void* castSkill(dxSkill* inSkill)
	{
		return NULL;
	}
public:
public:
	skill00() {};
	~skill00() {};
};

