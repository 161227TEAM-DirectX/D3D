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
	dx::transform* _oneTagerTrans;
	dx::transform* _AllTagerTrans;

	int _targetMaxNum;

	bool _OneActionSettingOn;

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
	virtual void setOneTargetTrans(dx::transform* inTarger) { _oneTagerTrans = inTarger; };

	void SetManyTargetTrans(dx::transform*& allTarget, int targetMaxNum)
	{
		_AllTagerTrans = allTarget;
		_targetMaxNum = targetMaxNum;

	};

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

