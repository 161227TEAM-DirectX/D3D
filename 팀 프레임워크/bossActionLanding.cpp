#include "stdafx.h"
#include "bossActionLanding.h"


bossActionLanding::bossActionLanding()
	:Action()
{
	D3DXMatrixIdentity(&matPosition);
}


bossActionLanding::~bossActionLanding()
{
}

int bossActionLanding::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	owner->getSkinnedAnim().Play("Animation_48");
	//owner->_transform->SetWorldPosition(10.0f, 70.0f, 10.0f);

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionLanding::Update()
{
	//���ڸ� ���� ��� �ϰ�� �������� ���� �Ÿ��� �����Ǹ� ����� �����ϴ� �ڵ�
	string temp = owner->getSkinnedAnim().getAnimationSet()->GetName();
	if (!strcmp("Animation_48", temp.c_str()))
	{
		owner->_transform->MovePositionSelf(0.0f, -0.3f, 0.0f);
		float tempY = rand->getHeight(owner->_transform->GetWorldPosition().x, owner->_transform->GetWorldPosition().z) + 13.3f;

		if (owner->_transform->GetWorldPosition().y <= tempY)
		{
			owner->getSkinnedAnim().Play("Animation_43");
			return LHS::ACTIONRESULT::ACTION_PLAY;
		}
	}

	//�����ö��� �ִϸ��̼�
	if (!strcmp("Animation_43", temp.c_str()))
	{
		matPosition = owner->getSkinnedAnim().getSkinnedMesh()->GetFineBONE("Deathwing_Bone03")->CombinedTransformationMatrix;
		//������ ���̰�.
		float tempY = rand->getHeight(owner->_transform->GetWorldPosition().x, owner->_transform->GetWorldPosition().z);

		//�������� �۴ٸ�
		if (tempY >= owner->_transform->GetWorldPosition().y)
		{
			//�ִϸ��̼��� ������ �ʾҴٸ�
			if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.95f)
			{
				D3DXVECTOR3 temp = owner->_transform->GetWorldPosition();
				temp.y = tempY;
				owner->_transform->SetWorldPosition(temp);

				owner->getSkinnedAnim().Play("Animation_13", 1.0f);
			}
		}
		else
		{
			owner->_transform->MovePositionSelf(0.0f, -0.3f, 0.0f);
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
