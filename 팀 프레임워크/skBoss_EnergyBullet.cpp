#include "stdafx.h"
#include "skBoss_EnergyBullet.h"

HRESULT skBoss_EnergyBullet::init()
{
	_SkillRenderType = SR_Big;

	setMaxNumPreparePS(1);
	setMaxNumActionPS(1);
	setMaxNumFinishPS(1);

	setPvPreparePS(0, "�����غ�1", 1);
	setPvPreparePS(1, "�����غ�2", 1);
	setPvPreparePS(2, "����������", 1);

	setPvActionPS(0, "������ź", 40);
	setPvFinishPS(0, "������ź_����", 40);

	//setArrayPreparePS("�׽�Ʈ",7);


	return S_OK;
}

void skBoss_EnergyBullet::release()
{
}

bool skBoss_EnergyBullet::Prepare()
{
	
		_skillActionOn = true;
	//_vPrepaerPS[0]->update();


	return false;
}

bool skBoss_EnergyBullet::Action()
{
	_skillFinshOn = true;

	return false;
}

void skBoss_EnergyBullet::Finsh()
{

}

void skBoss_EnergyBullet::Reset()
{
}
