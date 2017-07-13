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
	if (!SOUNDMANAGER->isPlaySound("�ȱ�"))
	{
		SOUNDMANAGER->play("�ȱ�");
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionMove::Update()
{
	if (!owner) return (int)LHS::ACTIONRESULT::ACTION_FAIL;

	bossMonster* temp = dynamic_cast<bossMonster*>(owner);

	if (temp->getHP() <= 0) return LHS::ACTIONRESULT::ACTION_DIE;

	PHYSICSMANAGER->isBlocking(owner, playerObject);
	//������ ���� ��ġ�� �����Ѵ�.
	from = owner->_transform->GetWorldPosition();
	rotateTemp = *owner->_transform;
	//�÷��̾��� ��ġ�� y���� ������ �����Ѵ�.
	float tempY = rand->getHeight(playerObject->_transform->GetWorldPosition().x, playerObject->_transform->GetWorldPosition().z);
	//���� �÷��̾��� ��ġ�� to�� �����Ѵ�.
	to = D3DXVECTOR3(playerObject->_transform->GetWorldPosition().x, tempY, playerObject->_transform->GetWorldPosition().z);
	//���ʹ� �÷��̾ �ٶ󺸵��� �����Ѵ�.
	owner->_transform->LookPosition(to);

	owner->_transform->RotateSlerp(rotateTemp, *owner->_transform, _timeDelta);

	D3DXVECTOR3 look(0.0f, 0.0f, 0.1f);
	owner->_transform->MovePositionSelf(look);
	look = owner->_transform->GetWorldPosition();
	tempY = rand->getHeight(look.x, look.z);
	owner->_transform->SetWorldPosition(look.x, tempY, look.z);


	//���� �����ؾ� �� ������ ���۵Ǵ� �κ��̴�.
	//�ѹ� ������ ���Ƽ� index�� �ʱ�ȭ�� �ʿ��ϴ�.
	index = myUtil::RandomFloatRange(0.1f, 1.0f);

	//���� �ִϸ��̼��� ������.
	//if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
	//{
		//�ȴٰ� hit�ڽ��� �÷��̾ �ִٸ�.
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getHitBox(), playerObject->_transform, &playerObject->_boundBox))
		{
			SOUNDMANAGER->stop("�ȱ�");
			return LHS::ACTIONRESULT::ACTION_ATT;
		}
		//�ȴٰ� range�ڽ� �ȿ� �÷��̾ �ִٸ�.
		if (PHYSICSMANAGER->isOverlap(temp->_transform, &temp->getRange(), playerObject->_transform, &playerObject->_boundBox))
		{
			SOUNDMANAGER->stop("�ȱ�");
			if (index >= 0.98f && index <= 0.99f) return LHS::ACTIONRESULT::ACTION_SKILL_BATTLE_ROAR;
			else if (index >= 0.99f && index <= 1.0f) return LHS::ACTIONRESULT::ACTION_SKILL_FIRE;
			else if (index - Gap >= 0.97f && index - Gap <= 0.975) return LHS::ACTIONRESULT::ACTION_FLY;
		}

		//Ȯ�������� ������������ �̵�
		if (index - Gap >= 0.97f && index - Gap <= 0.975f)
		{
			return LHS::ACTIONRESULT::ACTION_FLY;
		}
	//}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
