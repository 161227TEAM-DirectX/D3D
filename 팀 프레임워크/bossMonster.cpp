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
	CurrAction = new bossActionCinema;
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
	case LHS::BOSSAC_ATT:
		break;
	case LHS::BOSSAC_DIE:
		break;
	case LHS::BOSSAC_FAIL:
		break;
	case LHS::BOSSAC_FINISH:
		break;
	case LHS::BOSSAC_MOVE:
		break;
	case LHS::BOSSAC_NONE:
		break;
	case LHS::BOSSAC_PLAY:
		break;
	case LHS::BOSSAC_REMOVE:
		break;
	case LHS::BOSSAC_SKILL:
		break;
	case LHS::BOSSAC_STAND:
		break;
	}
}
