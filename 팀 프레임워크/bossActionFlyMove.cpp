#include "stdafx.h"
#include "bossActionFlyMove.h"


bossActionFlyMove::bossActionFlyMove()
	:Action(), angle(0.0f)
{
}


bossActionFlyMove::~bossActionFlyMove()
{
}

int bossActionFlyMove::Start()
{
	if (!owner) LHS::ACTIONRESULT::ACTION_FINISH;

	owner->getSkinnedAnim().Play("Animation_48", 1.0f);

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int bossActionFlyMove::Update()
{
	string temp = owner->getSkinnedAnim().getAnimationSet()->GetName();

	if (!strcmp("Animation_48", temp.c_str()))
	{
		if (owner->getSkinnedAnim().getAnimationPlayFactor() > 0.9f) owner->getSkinnedAnim().Play("Animation_39", 1.0f);
	}

	//애니메이션이 날며 이동하는 애니메이션으로 변경 되었을 경우.
	if (!strcmp("Animation_39", temp.c_str()))
	{
		angle += D3DXToRadian(30)*_timeDelta;
		D3DXMatrixRotationY(&matRotateX, angle);
		//D3DXMatrixTranslation(&matTranslation, 50.0f, 0.0f, 50.0f);
		//D3DXMatrixRotationZ(&matRotateZ, angle);
		matWorld = matRotateX /** matTranslation*/;
		D3DXVec3TransformCoord(&pos, &playerObject->_transform->GetWorldPosition(), &matWorld);
		D3DXVECTOR3 tempPos(pos.x*30.0f, owner->_transform->GetWorldPosition().y, pos.z*30.0f);
		owner->_transform->LookDirection(tempPos, D3DXVECTOR3(playerObject->_transform->GetWorldPosition() - owner->_transform->GetWorldPosition()));
		owner->_transform->SetWorldPosition(tempPos);
		
	}

	return LHS::ACTIONRESULT::ACTION_PLAY;
}
