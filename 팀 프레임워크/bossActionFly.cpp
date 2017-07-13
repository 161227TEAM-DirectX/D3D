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
	test = *owner->_transform;
	test.MovePositionSelf(0.0f, 1.0f, 0.0f);
	EFFECT->findEffect("����_����")->setLimitTime(5.0f);
	EFFECT->findEffect("����_����")->Start(&test);


	D3DXMatrixIdentity(&matTranslation);

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionFly::Update()
{
	string name = owner->getSkinnedAnim().getAnimationSet()->GetName();
	float a = owner->getSkinnedAnim().getAnimationPlayFactor();
	//���� �����ϴ� �κ�
	if (!strcmp("Animation_44", name.c_str()))
	{
		if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
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
		if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
		{
			if (owner->_transform->GetWorldPosition().y >= 50.0f) return LHS::ACTIONRESULT::ACTION_FLY_MOVE_ATT;			
		}

		//�ӽ������� ���̰��� �����Ѵ�.
		if (owner->_transform->GetWorldPosition().y < 50.0f)
		{
			//�ƴҰ��
			matTranslation = owner->getSkinnedAnim().getSkinnedMesh()->GetFineBONE("Deathwing_Bone03")->CombinedTransformationMatrix;
			owner->_transform->MovePositionSelf(0.0f, matTranslation._42 * 0.01f, 0.0f);
		}
	}

	//���ݿ� ���� ������ �ʿ�, ū ������ ����, �˹鰡��?

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
