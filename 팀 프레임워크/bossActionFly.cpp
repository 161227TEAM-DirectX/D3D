#include "stdafx.h"
#include "bossActionFly.h"


bossActionFly::bossActionFly()
{
}


bossActionFly::~bossActionFly()
{
}

int bossActionFly::Start()
{
	if (!owner)return LHS::ACTIONRESULT::ACTION_FINISH;

	owner->getSkinnedAnim().Play("Animation_44");

	D3DXMatrixIdentity(&matTranslation);

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionFly::Update()
{
	string name = owner->getSkinnedAnim().getAnimationSet()->GetName();

	//���� �����ϴ� �κ�
	if (!strcmp("Animation_44", name.c_str()))
	{
		if (owner->getSkinnedAnim().getAnimationPlayFactor() >= 0.95f)
		{
			//�������� �� ��� TRANSFORM�� Y���� 0.0���� ���������� �ִϸ��̼� �����δ� ���� �߰� �ִ� ��Ȳ�̴�.
			//�׷��⿡ ��Ű��޽��� ���� �����Ͽ� ���� �̸��� ���� BONE����ü�� ������ ���� ����� �����´�.
			//�̸� ���� ��Ŀ��� ���� ��ġ���� ������ �ִ� _41, _42, _43�� ���� ���� TRANSFORM�� ���� ��ȭ��Ų��.
			matTranslation = owner->getSkinnedAnim().getSkinnedMesh()->GetFineBONE("Deathwing_Bone03")->CombinedTransformationMatrix;
			owner->_transform->MovePositionSelf(0.0f, matTranslation._42, 0.0f);
			//owner->_transform->SetWorldMatrix(matTranslation);
			owner->getSkinnedAnim().Play("Animation_48");
			return LHS::ACTIONRESULT::ACTION_PLAY;
		}
	}

	//���� ������ �Ϸ�ǰ� ���߿��� �������ϰ� �ִ� ������ ���
	if (!strcmp("Animation_48", name.c_str()))
	{
		//�ִϸ��̼��� ���� �ȴٸ�.
		if (owner->getSkinnedAnim().getAnimationPlayFactor() >= 0.95f)
		{
			//�ٸ��ൿ�� ���ؾ� �� �κ�.
			if (owner->_transform->GetWorldPosition().y < 50.0f)
			{
				matTranslation = owner->getSkinnedAnim().getSkinnedMesh()->GetFineBONE("Deathwing_Bone03")->CombinedTransformationMatrix;
				owner->_transform->MovePositionSelf(0.0f, matTranslation._42, 0.0f);
			}
			//owner->_transform->SetWorldMatrix(matTranslation);
			//�ӽ÷� play�� ������.
			return LHS::ACTIONRESULT::ACTION_PLAY;
		}

		//�ӽ������� ���̰��� �����Ѵ�.
		if (owner->_transform->GetWorldPosition().y < 50.0f)
		{
			//�ƴҰ��
			matTranslation = owner->getSkinnedAnim().getSkinnedMesh()->GetFineBONE("Deathwing_Bone03")->CombinedTransformationMatrix;
			owner->_transform->MovePositionSelf(0.0f, matTranslation._42 * 0.01f, 0.0f);
		}
	}

	//if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.99f)
	//{
	//	owner->getSkinnedAnim().Play("Animation_48");
	//	//if (strcmp("Animation_44", owner->getSkinnedAnim().getAnimationSet()->GetName()))
	//	//{
	//	//	return LHS::ACTIONRESULT::ACTION_PLAY;
	//	//	if
	//	//}
	//	//else
	//	//{
	//	//	owner->getSkinnedAnim().Play("Animation_48");
	//	//}
	//}
	//else
	//{
	//	return LHS::ACTIONRESULT::ACTION_PLAY;
	//}

	//���ݿ� ���� ������ �ʿ�, ū ������ ����, �˹鰡��?

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
