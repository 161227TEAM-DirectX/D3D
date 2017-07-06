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

	//날기 시작하는 부분
	if (!strcmp("Animation_44", name.c_str()))
	{
		if (owner->getSkinnedAnim().getAnimationPlayFactor() >= 0.95f)
		{
			//데스윙이 날 경우 TRANSFORM의 Y값은 0.0으로 고정이지만 애니메이션 상으로는 위로 뜨고 있는 상황이다.
			//그렇기에 스키드메쉬에 직접 접근하여 본의 이름을 통해 BONE구조체를 가져와 최종 행렬을 가져온다.
			//이를 통해 행렬에서 현재 위치값을 가지고 있는 _41, _42, _43의 값을 통해 TRANSFORM의 값을 변화시킨다.
			matTranslation = owner->getSkinnedAnim().getSkinnedMesh()->GetFineBONE("Deathwing_Bone03")->CombinedTransformationMatrix;
			owner->_transform->MovePositionSelf(0.0f, matTranslation._42, 0.0f);
			//owner->_transform->SetWorldMatrix(matTranslation);
			owner->getSkinnedAnim().Play("Animation_48");
			return LHS::ACTIONRESULT::ACTION_PLAY;
		}
	}

	//날기 시작이 완료되고 공중에서 날개짓하고 있는 상태의 경우
	if (!strcmp("Animation_48", name.c_str()))
	{
		//애니메이션이 종료 된다면.
		if (owner->getSkinnedAnim().getAnimationPlayFactor() >= 0.95f)
		{
			//다른행동을 취해야 할 부분.
			if (owner->_transform->GetWorldPosition().y < 50.0f)
			{
				matTranslation = owner->getSkinnedAnim().getSkinnedMesh()->GetFineBONE("Deathwing_Bone03")->CombinedTransformationMatrix;
				owner->_transform->MovePositionSelf(0.0f, matTranslation._42, 0.0f);
			}
			//owner->_transform->SetWorldMatrix(matTranslation);
			//임시로 play로 돌린다.
			return LHS::ACTIONRESULT::ACTION_PLAY;
		}

		//임시적으로 높이값을 제한한다.
		if (owner->_transform->GetWorldPosition().y < 50.0f)
		{
			//아닐경우
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

	//공격에 따른 범위가 필요, 큰 데미지 적용, 넉백가능?

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
