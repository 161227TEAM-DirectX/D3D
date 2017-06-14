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
	owner->getSkinnedAnim().Play("Animation_56");

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

	//������ ���� ��ġ�� �����Ѵ�.
	from = owner->_transform->GetWorldPosition();
	//�÷��̾��� ��ġ�� y���� ������ �����Ѵ�.
	float tempY = rand->getHeight(enemy->_transform->GetWorldPosition().x, enemy->_transform->GetWorldPosition().z);
	//���� �÷��̾��� ��ġ�� to�� �����Ѵ�.
	to = D3DXVECTOR3(enemy->_transform->GetWorldPosition().x, tempY, enemy->_transform->GetWorldPosition().z);
	//���ʹ� �÷��̾ �ٶ󺸵��� �����Ѵ�.
	owner->_transform->LookPosition(to);

	D3DXVECTOR3 look(0.0f, 0.0f, 0.05f);
	owner->_transform->MovePositionSelf(look);
	look = owner->_transform->GetWorldPosition();
	tempY = rand->getHeight(look.x, look.z);
	owner->_transform->SetWorldPosition(look.x, tempY, look.z);

	if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f)
	{
		//int index = myUtil::RandomIntRange(0, 9);
		//resultValue = list[index];
		index = myUtil::RandomFloatRange(0.1f, 1.0f);
	}


	//���� �����ؾ� �� ������ ���۵Ǵ� �κ��̴�.
	bossMonster* temp = dynamic_cast<bossMonster*>(owner);
	//D3DXVECTOR3 tempVec = enemy->_transform->GetWorldPosition() - temp->_transform->GetWorldPosition();
	//D3DXVec3Normalize(&tempVec, &tempVec);
	//float angle = D3DXVec3Dot(&temp->_transform->GetForward(), &tempVec);
//	float angle = D3DXVec3Length(&(enemy->_transform->GetWorldPosition() - temp->_transform->GetWorldPosition()));

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

	/*switch (resultValue)
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
				return LHS::ACTIONRESULT::ACTION_SKILL_FIRE;
		}
		break;
	}*/

	//�÷��̾ ã�Ƽ� �÷��̾��� �ٿ�� �ڽ��� ���� hit�ڽ��� �浹�ߴٸ� ���� �������� �Ѿ��


	//�÷��̾�(enemy)�� ���������� range�ڽ� �ȿ� ���Դٸ� ���Ͷ�
	//���⼭ ��Ʋ�ξ�, ��������, �Ұ��� Ȯ���� ���Ѵ�.

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
