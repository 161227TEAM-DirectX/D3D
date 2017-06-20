#include "stdafx.h"
#include "monster.h"


monster::monster() 
	: baseObject(), CurrAction(nullptr), NextAction(nullptr)
	, _mainCamera(nullptr)
{
}

monster::monster(string Name)
	: baseObject(), CurrAction(nullptr), NextAction(nullptr)
	, Name(Name), _mainCamera(nullptr)
{
}

monster::monster(camera* _mainCamera, string Name)
	: baseObject(), CurrAction(nullptr), NextAction(nullptr)
	, Name(Name), _mainCamera(_mainCamera)
{
}


monster::~monster()
{
	SAFE_DELETE(CurrAction);
	SAFE_DELETE(NextAction);
}

void monster::baseObjectEnable()
{
	D3DXVECTOR3 temp(_boundBox._localCenter);
	range.setBound(&temp, &D3DXVECTOR3(_transform->GetScale().x * RANGE, _transform->GetScale().y * RANGE, _transform->GetScale().z * RANGE));

	temp.z = _boundBox._localMaxPos.z;
	
	hitBox.setBound(&temp, &D3DXVECTOR3(_transform->GetScale().x * 0.6f, temp.y * 1.0f, _transform->GetScale().z * 0.3f));

	HP = myUtil::RandomIntRange(MINHM, MAXHM);
	mana = myUtil::RandomIntRange(MINHM, MAXHM);
	gold = myUtil::RandomIntRange(MINGS, MAXGS);
	soul = myUtil::RandomIntRange(MINGS, MAXGS);
	att = DEFAULTATT;
	def = DEFAULTDEF;
	CurrAction = ACMANAGER->getAction("일반대기", *this);

	result = (LHS::ACTIONRESULT)CurrAction->Start();
}

void monster::baseObjectDisable()
{
	SAFE_DELETE(CurrAction);
	SAFE_DELETE(NextAction);

	this->_transform->SetWorldPosition(regenPosition);
}

void monster::baseObjectUpdate()
{
	stateSwitch();

	if (NextAction != nullptr)
	{
		SAFE_DELETE(CurrAction);
		CurrAction = NextAction;
		result = (LHS::ACTIONRESULT)CurrAction->Start();
		NextAction = nullptr;
	}

	if (CurrAction) result = (LHS::ACTIONRESULT)CurrAction->Update();
	_skinnedAnim->update();
}

void monster::baseObjectNoActiveUpdate()
{
}

void monster::baseObjectRender()
{
	if (_skinnedAnim != nullptr) _skinnedAnim->render(_transform);

	if(_mainCamera!=nullptr) SPRITEMANAGER->RenderFont(_mainCamera, Name);

	hitBox.renderGizmo(_transform, D3DCOLOR_XRGB(255, 0, 0));
	range.renderGizmo(_transform, D3DCOLOR_XRGB(255, 255, 0));

	_boundBox.renderGizmo(_transform);
}

void monster::stateSwitch(void)
{
	//몬스터의 HP가 떨어지면 죽음 상태로 변경
	// 각 액션이 update 함수를 실행 후에 상태값을 넘겨온다.
	// 그 상태값에 따라 몬스터가 해야 할 행동을 취하면 된다.
	switch (result)
	{
		//리턴 값이 액션이 종료되었음을 알려올때 -> standing상태로 돌아간다.
	case LHS::ACTIONRESULT::ACTION_FINISH:
		NextAction = ACMANAGER->getAction("일반대기", *this);
		break;
		//액션을 할당, 다양한 문제가 생겼을 경우
	case LHS::ACTIONRESULT::ACTION_FAIL:
		MessageBox(nullptr, "new 과정에서 문제가 생겼습니다.", "!!!!", MB_OK);
		exit(1);
		break;
		//현재 액션을 실행하는 중이며 아직 실행이 끝나거나 다른 경우가 없는 상태일때.
		//특별히 할 것 없이 계속 액션을 취하면 된다.
	case LHS::ACTIONRESULT::ACTION_PLAY:
		return;
		//액션이 종료되었다거나, 다시 탐색상태로 돌아가야 할때.
	case LHS::ACTIONRESULT::ACTION_STAND:
		NextAction = ACMANAGER->getAction("일반대기", *this);
		break;
	// 이동이 필요한 경우
	case LHS::ACTIONRESULT::ACTION_MOVE:
		NextAction = ACMANAGER->getAction("일반시퀸스", *this);
		break;
	//원래의 리젠 위치로 돌아가야 하는 경우
	case LHS::ACTIONRESULT::ACTION_REMOVE:
		NextAction = ACMANAGER->getAction("일반재이동시퀸스", *this);
		break;
		//공격을 해야 하는 경우
	case LHS::ACTIONRESULT::ACTION_ATT:
		NextAction = ACMANAGER->getAction("일반공격", *this);
		break;
		//죽었을때.
	case LHS::ACTIONRESULT::ACTION_DIE:
		NextAction = ACMANAGER->getAction("일반죽음", *this);
		break;
	case LHS::ACTIONRESULT::ACTION_NONE:
		this->setActive(false);
		break;
	}
}
