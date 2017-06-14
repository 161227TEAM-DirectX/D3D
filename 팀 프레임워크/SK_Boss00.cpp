#include "stdafx.h"
#include "SK_Boss00.h"

HRESULT SK_Boss00::init()
{
	_SkillRenderType = SR_Big;

	//_enemyTrans = new dx::transform[5];

	setMaxNumPreparePS(3);
	setPvPreparePS(0, "ºê·¹½º", 1);

	_pvPrepaerPS[0][0]->SetLimitTime(5.0f);

	return S_OK;

}

void SK_Boss00::release()
{
}

bool SK_Boss00::Prepare()
{

	//_pvPrepaerPS[0][0]->Transform()->SetWorldMatrix(_playerTrans->GetFinalMatrix());
	_pvPrepaerPS[0][0]->Transform()->SetWorldPosition(_playerTrans->GetWorldPosition());
	_pvPrepaerPS[0][0]->Transform()->LookDirection(_playerTransDir->GetForward());
	_pvPrepaerPS[0][0]->update();
	//_pvPrepaerPS[0][0]->Transform()->RotateWorld(0.0f,0.0f,0.01f);
	if (_pvPrepaerPS[0][0]->autoTimeReset(false))
	{
		_skillStartOn = false;
		_skillActionOn = true;
		_skillResetOn = true;
	}



	return false;
}

bool SK_Boss00::Action()
{
	return false;
}

void SK_Boss00::Finsh()
{
}

void SK_Boss00::Reset()
{
}
