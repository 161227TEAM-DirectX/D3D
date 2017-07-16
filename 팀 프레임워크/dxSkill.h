#pragma once
#include "dxSkillContainer.h"



class dxSkill : public dxSkillContainer
{
protected:
	//Ʈ������
	dx::transform* _playerTrans;	//�ӽÿ� ���￹��
	dx::transform* _playerTransDir;//�ӽÿ� ���￹��

	//��ų ��ġ �� ���� Ʈ������
	dx::transform* _skillPosTrans;
	dx::transform* _skillDirTrans;

	//�� Ÿ�� ���� �� Ʈ������
	dx::transform* _oneTargetTrans;
	dx::transform* _allTargetTrans;

	int _targetMaxNum;

	bool _OneActionSettingOn;

	bool _LimitTimeOn;

	float _limitTime;
	float _currentTime;

	//bool _endOn;

public:
	//������Ʈ ����
	virtual bool Prepare() = 0;
	virtual bool Action() = 0;
	virtual void Finsh() = 0;
	virtual void Reset() = 0;

public:
	//��ų
	virtual void setSkillPosTrans(dx::transform* inPosTrans) { _skillPosTrans = inPosTrans; };
	virtual void setSkillDirTrans(dx::transform* inDirTrans) { _skillDirTrans = inDirTrans; };

	//Ÿ��
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
	//������
	dxSkill()
	{
		this->ContainerInit();

		//__super::dxSkillContainer();

		//this->init();
		////���۵� �ʱ�ȭ
		//_skillStartOn = false;
		//_skillActionOn = false;
		//_skillFinshOn = false;
		//_skillResetOn = false;
		////�ð� �ʱ�ȭ
		//_currentResetTime = 0.0f;
		//_resetTime = 0.0f;

		////��ƼŬ �ʱ�ȭ
		//_preparePS = NULL;
		//_actionPS = NULL;
		//_finishPS = NULL;

		//_SkillRenderType = SR_One;

	};
	~dxSkill() {};
};

