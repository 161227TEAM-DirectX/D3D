#pragma once
#include "dxSkillContainer.h"



class dxSkill : public dxSkillContainer
{
protected:
	//트렌스폼
	dx::transform* _playerTrans;	//임시용 지울예정
	dx::transform* _playerTransDir;//임시용 지울예정

	//스킬 위치 및 방향 트랜스폼
	dx::transform* _skillPosTrans;
	dx::transform* _skillDirTrans;

	//한 타겟 바향 및 트랜스폼
	dx::transform* _oneTargetTrans;
	dx::transform* _allTargetTrans;

	int _targetMaxNum;

	bool _OneActionSettingOn;

	bool _LimitTimeOn;

	float _limitTime;
	float _currentTime;

	//bool _endOn;

public:
	//업데이트 동작
	virtual bool Prepare() = 0;
	virtual bool Action() = 0;
	virtual void Finsh() = 0;
	virtual void Reset() = 0;

public:
	//스킬
	virtual void setSkillPosTrans(dx::transform* inPosTrans) { _skillPosTrans = inPosTrans; };
	virtual void setSkillDirTrans(dx::transform* inDirTrans) { _skillDirTrans = inDirTrans; };

	//타겟
	virtual void setOneTargetTrans(dx::transform* inTarget) { _oneTargetTrans = inTarget; };

	void SetManyTargetTrans(dx::transform*& allTarget, int targetMaxNum)
	{
		_allTargetTrans = allTarget;
		_targetMaxNum = targetMaxNum;

	};

	virtual void setPlayer(dx::transform* inPlayerTrans) { _playerTrans = inPlayerTrans; };
	virtual void setPlayerDir(dx::transform* inPlayerTrans) { _playerTransDir = inPlayerTrans; };
	virtual void setTarget(dx::transform* inTargetTrans) { _targetTrans = inTargetTrans; };
	//virtual void setAction(transform* inTargetTrans) { _actionTrans = inTargetTrans; };

public:
	virtual bool getCollision(void) { return true; };
	virtual D3DXVECTOR3 getActionShperePos() { return D3DXVECTOR3(0,0,0); };
	

//	this->ContainerInit();
public:
	void resetTimeOn(float inTime = 2.0f) { _limitTime = inTime; _LimitTimeOn = true; }


public:
	//생성자
	dxSkill()
	{
		this->ContainerInit();

		//__super::dxSkillContainer();

		//this->init();
		////동작들 초기화
		//_skillStartOn = false;
		//_skillActionOn = false;
		//_skillFinshOn = false;
		//_skillResetOn = false;
		////시간 초기화
		//_currentResetTime = 0.0f;
		//_resetTime = 0.0f;

		////파티클 초기화
		//_preparePS = NULL;
		//_actionPS = NULL;
		//_finishPS = NULL;

		//_SkillRenderType = SR_One;

	};
	~dxSkill() {};
};

