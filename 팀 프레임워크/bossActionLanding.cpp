#include "stdafx.h"
#include "bossActionLanding.h"


bossActionLanding::bossActionLanding()
	:Action(), isTrans(true)
{
	D3DXMatrixIdentity(&matPosition);
}


bossActionLanding::~bossActionLanding()
{
}

int bossActionLanding::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	owner->getSkinnedAnim().Play("Animation_39");
	//owner->_transform->SetWorldPosition(10.0f, 70.0f, 10.0f);

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionLanding::Update()
{
	string temp = owner->getSkinnedAnim().getAnimationSet()->GetName();
	if (!strcmp("Animation_39", temp.c_str()))
	{
		lerpTransform = *owner->_transform;
		D3DXVECTOR3 tempPos(0.0f, 13.0f, 0.0f);
		owner->_transform->LookPosition(tempPos);
		owner->_transform->RotateSlerp(lerpTransform, *owner->_transform, _timeDelta * 2);
		owner->_transform->MovePositionSelf(0.0f, 0.0f, 0.5f);
		if (D3DXVec3Length(&(owner->_transform->GetWorldPosition() - tempPos)) <= 0.7f)
		{
			owner->getSkinnedAnim().Play("Animation_43");
			return LHS::ACTIONRESULT::ACTION_PLAY;
		}
	}

	//�����ö��� �ִϸ��̼�
	if (!strcmp("Animation_43", temp.c_str()))
	{
		if (isTrans)
		{
			owner->_transform->SetWorldPosition(
				owner->_transform->GetWorldPosition().x,
				0.0f, owner->_transform->GetWorldPosition().z);
			isTrans = false;
		}
		//matPosition = owner->getSkinnedAnim().getSkinnedMesh()->GetFineBONE("Deathwing_Bone03")->CombinedTransformationMatrix;
		////������ ���̰�.
		//float tempY = rand->getHeight(owner->_transform->GetWorldPosition().x, owner->_transform->GetWorldPosition().z);

		//�������� �۴ٸ�
		//if (tempY >= owner->_transform->GetWorldPosition().y)
		//{
			//�ִϸ��̼��� ������ �ʾҴٸ�
			if (owner->getSkinnedAnim().getAnimationPlayFactor() >= 0.95f)
			{
				//D3DXVECTOR3 temp = owner->_transform->GetWorldPosition();
				//temp.y = tempY;
				//owner->_transform->SetWorldPosition(temp);

				return LHS::ACTIONRESULT::ACTION_MOVE;
			}
		//}
		//else
		//{
		//	owner->_transform->MovePositionSelf(0.0f, -0.3f, 0.0f);
		//}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
