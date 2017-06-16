#include "stdafx.h"
#include "bossActionMove.h"


bossActionMove::bossActionMove()
	:Action(), ch(false), resultValue(0), index(0.0f)
{
}


bossActionMove::~bossActionMove()
{
}

int bossActionMove::Start()
{
	if (!owner) return (int)LHS::ACTIONRESULT::ACTION_FAIL;

	//baseObject�� transform�� ȣ���Ͽ� world��ġ�� from���� ����
	owner->getSkinnedAnim().Play("Animation_56", 0.5f);
	
	//Ȯ���� ���� ���� �� �õ� �ʱ�ȭ
	int seed = 0;
	
	seed = 1;
	for (int i = 0; i < 8; i++)
	{
		list.push_back(seed);
	}
	seed = 2;
	list.push_back(seed);
	seed = 3;
	list.push_back(seed);

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionMove::Update()
{
	if (!owner) return (int)LHS::ACTIONRESULT::ACTION_FAIL;

	//�ѹ� ������ ���Ƽ� index�� �ʱ�ȭ�� �ʿ��ϴ�.
	index = myUtil::RandomFloatRange(0.1f, 1.0f);
	//index = 0.991f;

	PHYSICSMANAGER->isBlocking(owner, enemy);
	//������ ���� ��ġ�� �����Ѵ�.
	from = owner->_transform->GetWorldPosition();
	rotateTemp = *owner->_transform;
	//�÷��̾��� ��ġ�� y���� ������ �����Ѵ�.
	float tempY = rand->getHeight(enemy->_transform->GetWorldPosition().x, enemy->_transform->GetWorldPosition().z);
	//���� �÷��̾��� ��ġ�� to�� �����Ѵ�.
	to = D3DXVECTOR3(enemy->_transform->GetWorldPosition().x, tempY, enemy->_transform->GetWorldPosition().z);
	//���ʹ� �÷��̾ �ٶ󺸵��� �����Ѵ�.
	owner->_transform->LookPosition(to);

	owner->_transform->RotateSlerp(rotateTemp, *owner->_transform, _timeDelta);

	D3DXVECTOR3 look(0.0f, 0.0f, 0.01f);
	owner->_transform->MovePositionSelf(look);
	look = owner->_transform->GetWorldPosition();
	tempY = rand->getHeight(look.x, look.z);
	owner->_transform->SetWorldPosition(look.x, tempY, look.z);


	//���� �����ؾ� �� ������ ���۵Ǵ� �κ��̴�.
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	if (index >= 0.1f && index <= 0.98f)
	{
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), enemy->_transform, &enemy->_boundBox))
		{
			return LHS::ACTIONRESULT::ACTION_ATT;
		}
	}
	else if (index >= 0.98f && index <= 0.99f)
	{
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
		{
			return LHS::ACTIONRESULT::ACTION_SKILL_BATTLE_ROAR;
		}
	}
	else if(index >= 0.99f && index <= 1.0f)
	{
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
		{
			return LHS::ACTIONRESULT::ACTION_SKILL_FIRE;
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
