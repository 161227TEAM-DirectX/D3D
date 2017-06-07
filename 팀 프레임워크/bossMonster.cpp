#include "stdafx.h"
#include "bossMonster.h"


bossMonster::bossMonster() : monster()
{
}


bossMonster::~bossMonster()
{
}

void bossMonster::baseObjectEnable()
{
}

void bossMonster::baseObjectDisable()
{
}

void bossMonster::baseObjectUpdate()
{
	switchState();

	stateSwitch();

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
}

void bossMonster::switchState(void)
{
}
