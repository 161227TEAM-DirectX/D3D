#include "stdafx.h"
#include "SK00.h"

HRESULT SK00::init()
{
	_SkillRenderType = SR_Big;

	//_enemyTrans = new dx::transform[5];

	setMaxNumPreparePS(3);
	setPvPreparePS(0,"¸¶¹ýÁø",1);

	_pvPrepaerPS[0][0]->SetLimitTime(10.0f);

	return S_OK;
}

void SK00::release()
{

}

bool SK00::Prepare()
{
	_pvPrepaerPS[0][0]->update();
	if (_pvPrepaerPS[0][0]->autoTimeReset(false))
	{
		//_skillStartOn = false;
		//_skillActionOn = true;
	}





	
	return false;
}

bool SK00::Action()
{


	return false;
}

void SK00::Finsh()
{

}

void SK00::Reset()
{

}
