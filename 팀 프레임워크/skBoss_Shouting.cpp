#include "stdafx.h"
#include "skBoss_Shouting.h"

HRESULT skBoss_Shouting::init()
{
	_SkillRenderType = SR_Array;

	setArrayPreparePS("Å×½ºÆ®",7);


	return S_OK;
}

void skBoss_Shouting::release()
{
}

bool skBoss_Shouting::Prepare()
{

	_vPrepaerPS[0]->update();

	return false;
}

bool skBoss_Shouting::Action()
{
	return false;
}

void skBoss_Shouting::Finsh()
{
}

void skBoss_Shouting::Reset()
{
}
