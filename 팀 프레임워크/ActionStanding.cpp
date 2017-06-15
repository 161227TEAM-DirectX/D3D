#include "stdafx.h"
#include "ActionStanding.h"


ActionStanding::ActionStanding()
	:Action(), PassedTime(0.0f)
{
}


ActionStanding::~ActionStanding()
{
}

int ActionStanding::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;
	owner->getSkinnedAnim().Play("Stand01");
	PassedTime = 0.0f;
	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionStanding::Update()
{
	if (!owner) return LHS::ACTIONRESULT::ACTION_FINISH;

	//owner�� baseobjectŬ�����̰� monsterŬ������ �ʿ��ϱ⿡ Ÿ�� ĳ����.
	monster* temp = dynamic_cast<monster*>(owner);
	
	//������ ���� �ڽ��� �ɸ��Ͱ� ���� �ɸ����� ��ġ�� �̵� - enemy������ �ʿ���.
	if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
	{
		if (deleGate) deleGate->OnActionFinish(this, true);
		return LHS::ACTIONRESULT::ACTION_MOVE;
	}

	//���� ������ �޾ҳ�?
	/*if(�浹ó�� Ȯ�� ����)
	{
		return LHS::ACTIONRESULT::ACTION_MOVE;
	}*/

	//���� ���� ������ �޾ҳ�?
	/*
	if(���ϰ��� Ȯ�� ����)
	{
		return LHS::ACTIONRESULT::ACTION_STUN;
	}
	*/

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
