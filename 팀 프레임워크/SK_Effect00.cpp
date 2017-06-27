#include "stdafx.h"
#include "SK_Effect00.h"

HRESULT SK_Effect00::init()
{
	_SkillRenderType = SR_Big;

	//_enemyTrans = new dx::transform[5];

	setMaxNumPreparePS(3);
	setPvPreparePS(0, "피격", 10);

	_pvPrepaerPS[0][0]->SetLimitTime(0.0f);


	return S_OK;

}

void SK_Effect00::release()
{
}

bool SK_Effect00::Prepare()
{
	//피격
	for (int i = 0; i < _pvPrepaerPS[0].size(); i++)
	{
		if (_pvPrepaerPS[0][i]->GetActive())
		{
			_pvPrepaerPS[0][i]->Transform()->SetWorldPosition(_allTargetTrans[i].GetWorldPosition());
			_pvPrepaerPS[0][i]->update();
			
		}
	}
	
	
	
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
