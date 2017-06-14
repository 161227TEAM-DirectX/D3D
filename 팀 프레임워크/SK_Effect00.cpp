#include "stdafx.h"
#include "SK_Effect00.h"

HRESULT SK_Effect00::init()
{
	_SkillRenderType = SR_Big;

	//_enemyTrans = new dx::transform[5];

	setMaxNumPreparePS(3);
	setPvPreparePS(0, "ÇÇ°Ý", 1);

	_pvPrepaerPS[0][0]->SetLimitTime(10.0f);

	return S_OK;

}

void SK_Effect00::release()
{
}

bool SK_Effect00::Prepare()
{
	_pvPrepaerPS[0][0]->update();
	//_pvPrepaerPS[0][0]->Transform()->RotateWorld(0.0f,0.0f,0.01f);
	//if (_pvPrepaerPS[0][0]->autoTimeReset(false))
	//{
	//	_skillStartOn = false;
	//	_skillActionOn = true;
	//}



	return false;
}

bool SK_Effect00::Action()
{
	return false;
}

void SK_Effect00::Finsh()
{
}

void SK_Effect00::Reset()
{
}
