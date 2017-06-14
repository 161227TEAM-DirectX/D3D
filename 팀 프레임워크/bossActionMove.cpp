#include "stdafx.h"
#include "bossActionMove.h"


bossActionMove::bossActionMove()
	:Action(), ch(false), resultValue(0)
{
}


bossActionMove::~bossActionMove()
{
}

int bossActionMove::Start()
{
	if (!owner) return (int)LHS::ACTIONRESULT::ACTION_FAIL;

	//baseObject�� transform�� ȣ���Ͽ� world��ġ�� from���� ����
	owner->getSkinnedAnim().Play("Animation_56");


	//������ ���� ��ġ�� �����Ѵ�.
	from = owner->_transform->GetWorldPosition();
	//�÷��̾��� ��ġ�� y���� ������ �����Ѵ�.
	float tempY = rand->getHeight(enemy->_transform->GetWorldPosition().x, enemy->_transform->GetWorldPosition().z);
	//���� �÷��̾��� ��ġ�� to�� �����Ѵ�.
	to = D3DXVECTOR3(enemy->_transform->GetWorldPosition().x, tempY, enemy->_transform->GetWorldPosition().z);
	//�� �ɸ��� ���� ���͸� ���Ѵ�.
	D3DXVECTOR3	range = to - from;
	//���ʹ� �÷��̾ �ٶ󺸵��� �����Ѵ�.
	owner->_transform->LookPosition(range);

	//Ȯ���� ���� ���� �� �õ� �ʱ�ȭ
	int seed = 0;
	
	seed = 1;
	for (int i = 0; i < 5; i++)
	{
		list.push_back(seed);
	}
	seed = 2;
	list.push_back(seed);
	seed = 3;
	list.push_back(seed);
	list.push_back(seed);
	seed = 4;
	list.push_back(seed);
	list.push_back(seed);

	/*switch (resultValue)
	{
	case 1:
		return LHS::ACTIONRESULT::ACTION_ATT;
	case 2:
		return LHS::ACTIONRESULT::ACTION_SKILL_BATTLE_ROAR;
	case 3:
		return LHS::ACTIONRESULT::ACTION_SKILL_FIRE;
	case 4:
		return LHS::ACTIONRESULT::ACTION_SKILL_TAIL;
	}*/

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionMove::Update()
{
	if (!owner) return (int)LHS::ACTIONRESULT::ACTION_FAIL;

	D3DXVECTOR3 look(0.0f, 0.0f, 0.1f);
	owner->_transform->MovePositionSelf(look);
	look = owner->_transform->GetWorldPosition();
	float tempY = rand->getHeight(look.x, look.z);
	owner->_transform->SetWorldPosition(look.x, tempY, look.z);

	int index = myUtil::RandomIntRange(0, 9);
	resultValue = 3;

	//���� �����ؾ� �� ������ ���۵Ǵ� �κ��̴�.
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);
	float angle = fabsf(D3DXVec3Dot(&temp->_transform->GetWorldPosition(), &enemy->_transform->GetWorldPosition()));
	switch (resultValue)
	{
	case 1:
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), enemy->_transform, &enemy->_boundBox))
		{
			return LHS::ACTIONRESULT::ACTION_ATT;
		}
		break;
	case 2:
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
		{
			return LHS::ACTIONRESULT::ACTION_SKILL_BATTLE_ROAR;
		}
		break;
	case 3:
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
		{
			if (angle <= 0)
			{
				return LHS::ACTIONRESULT::ACTION_SKILL_FIRE;
			}
		}
		break;
	case 4:
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox))
		{
			if (angle > 0)
			{
				return LHS::ACTIONRESULT::ACTION_SKILL_TAIL;
			}
		}
		break;
	}

	//�÷��̾ ã�Ƽ� �÷��̾��� �ٿ�� �ڽ��� ���� hit�ڽ��� �浹�ߴٸ� ���� �������� �Ѿ��


	//�÷��̾�(enemy)�� ���������� range�ڽ� �ȿ� ���Դٸ� ���Ͷ�
	//���⼭ ��Ʋ�ξ�, ��������, �Ұ��� Ȯ���� ���Ѵ�.
	if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), enemy->_transform, &enemy->_boundBox) && !ch)
	{
		//��Ʋ�ξ� ������ ����
		
		//��Ʋ�ξ� ��---------

		

		//�����̴�. �� ��� fire��ų�� �������.
		
		//���� ������ �Ѵ�.
		
	}

	//10���� seed�� ���� �迭�� ������ �����ϰ� �ε����� ���� �� ����� ���� ���� ��ų�� �����Ѵ�.
	//���Ϳ� ���� �ִٸ�


	////�׽�Ʈ
	//if (owner->_transform->GetWorldPosition() >= to)
	//{
	//	owner->_transform->SetWorldPosition(to);
	//	if (deleGate)deleGate->OnActionFinish(this, true);
	//	return LHS::ACTIONRESULT::ACTION_ATT;
	//}

	//if (speed >= 1.0f)
	//{
	//	owner->_transform->SetWorldPosition(to);
	//	return LHS::ACTIONRESULT::ACTION_ATT;
	//}


	//speed += 0.001f;
	return LHS::ACTIONRESULT::ACTION_PLAY;
}
