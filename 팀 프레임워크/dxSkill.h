#pragma once
#include "dxParticleSystem.h"
#include "dxSkillContainer.h"



class dxSkill : public dxSkillContainer
{
protected:
	//Ʈ������
	dx::transform* _playerTrans;
	dx::transform* _playerTransDir;


public:
	//������Ʈ ����
	virtual bool Prepare() = 0;
	virtual bool Action() = 0;
	virtual void Finsh() = 0;
	virtual void Reset() = 0;

public:
	virtual void setPlayer(dx::transform* inPlayerTrans) { _playerTrans = inPlayerTrans; };
	virtual void setPlayerDir(dx::transform* inPlayerTrans) { _playerTransDir = inPlayerTrans; };
	virtual void setTarget(dx::transform* inTargetTrans) { _targetTrans = inTargetTrans; };
	//virtual void setAction(transform* inTargetTrans) { _actionTrans = inTargetTrans; };

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

