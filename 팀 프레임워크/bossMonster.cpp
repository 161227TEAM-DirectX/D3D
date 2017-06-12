#include "stdafx.h"
#include "bossMonster.h"


bossMonster::bossMonster() : monster(), Frequency(0)
{
}


bossMonster::~bossMonster()
{
}

void bossMonster::baseObjectEnable()
{
	range.setBound(&D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(RANGE, RANGE, RANGE));
	D3DXVECTOR3 tempPosition = _transform->GetForward();

	tempPosition.z *= 0.1f;
	tempPosition.y = 0.07f;
	hitBox.setBound(&tempPosition, &D3DXVECTOR3(0.04f, 0.06f, 0.06f));

	HP = myUtil::RandomIntRange(MINHM, MAXHM);
	mana = myUtil::RandomIntRange(MINHM, MAXHM);
	gold = myUtil::RandomIntRange(MINGS, MAXGS);
	soul = myUtil::RandomIntRange(MINGS, MAXGS);
	att = DEFAULTATT;
	def = DEFAULTDEF;
	CurrAction = new bossActionMove;
	CurrAction->setOwner(this);
	CurrAction->setObject(&monster::getObject());
	CurrAction->setRand(monster::getTerrain());
	CurrAction->setEnemy(&monster::getPlayer());
	result = (LHS::ACTIONRESULT)CurrAction->Start();
}

void bossMonster::baseObjectDisable()
{
}

void bossMonster::baseObjectUpdate()
{
	switchState();

	if (NextAction != nullptr)
	{
		delete CurrAction;
		CurrAction = NextAction;
		result = (LHS::ACTIONRESULT)CurrAction->Start();
		NextAction = nullptr;
	}

	if (CurrAction) result = (LHS::ACTIONRESULT)CurrAction->Update();
	
	_skinnedAnim->update();
}

void bossMonster::baseObjectNoActiveUpdate()
{
}

void bossMonster::baseObjectRender()
{
	if (_skinnedAnim != nullptr) _skinnedAnim->render(_transform);
	hitBox.renderGizmo(_transform);
	range.renderGizmo(_transform);

	_boundBox.renderGizmo(_transform);
}

void bossMonster::switchState(void)
{
	switch (result)
	{
	case LHS::ACTION_ATT:
		break;
	case LHS::ACTION_DIE:
		break;
	case LHS::ACTION_FAIL:
		break;
	case LHS::ACTION_FINISH:
		break;
	case LHS::ACTION_MOVE:
		break;
	case LHS::ACTION_NONE:
		break;
	case LHS::ACTION_PLAY:
		return;
	case LHS::ACTION_REMOVE:
		break;
	}
}
