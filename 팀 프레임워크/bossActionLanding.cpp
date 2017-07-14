#include "stdafx.h"
#include "bossActionLanding.h"
#include "bossMonster.h"
#include "dxSkill.h"


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

	return (int)LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionLanding::Update()
{
	bossMonster* tempOwner = dynamic_cast<bossMonster*>(owner);
	if (tempOwner->getHP() <= 0) return LHS::ACTIONRESULT::ACTION_FLY_DIE;

	tempOwner->gettailTrans().SetWorldPosition(tempOwner->gettailTrans().GetWorldPosition().x,
		rand->getHeight(tempOwner->gettailTrans().GetWorldPosition().x, tempOwner->gettailTrans().GetWorldPosition().z),
		tempOwner->gettailTrans().GetWorldPosition().z);

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

		SKM->findSK("불꽃길")->setSkillPosTrans(&tempOwner->gettailTrans());
		SKM->findSK("불꽃길")->setSkillDirTrans(&tempOwner->gettailTrans());

		SKM->findSK("불꽃길")->Start();
	}

	//내려올때의 애니메이션
	if (!strcmp("Animation_43", temp.c_str()))
	{
		if (isTrans)
		{
			owner->_transform->SetWorldPosition(
				owner->_transform->GetWorldPosition().x,
				0.0f, owner->_transform->GetWorldPosition().z);
			isTrans = false;
		}

		//애니메이션이 끝나면
		if (owner->getSkinnedAnim().getAnimationPlayFactor() >= ANIMATIONENDTIME)
		{
			return LHS::ACTIONRESULT::ACTION_MOVE;
		}
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
