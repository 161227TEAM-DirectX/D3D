#include "stdafx.h"
#include "dxSkillManager.h"
#include "dxSkill.h"

#include "skPlayer_MagicShoot.h"
#include "skBoss_Breath.h"
#include "skPlayer_Heal.h"

void dxSkillManager::skillSetting()
{
	

	//플레이어 스킬 등록
	this->addSK("매직슈터", new skPlayer_MagicShoot);
	this->addSK("힐", new skPlayer_Heal);

	//보스 스킬 등록
	this->addSK("브레스", new skBoss_Breath);


	//this->skillInit();
}

void dxSkillManager::skillRelease()
{
	//SAFE_DELETE(_playerMagicShoot);
	//SAFE_DELETE(_bossBreath);
	_iter = _mapSK.begin();
	for (_iter; _iter != _mapSK.end(); ++_iter)
	{
		SAFE_DELETE(_iter->second);
	}
	_mapSK.clear();
}

void dxSkillManager::update()
{
	_iter = _mapSK.begin();
	for (_iter; _iter != _mapSK.end(); ++_iter)
	{
		if (_iter->second->getActive())
		{
			_iter->second->update();
		}

	}

}

void dxSkillManager::render()
{
	_iter = _mapSK.begin();
	for (_iter; _iter != _mapSK.end(); ++_iter)
	{
		if (_iter->second->getActive())
		{
			_iter->second->render();
		}

	}
}



void dxSkillManager::addSK(string skName, dxSkill * inSK)
{
	//있는지 확인
	if (checkName(skName)) return;
	//_mapPS.insert(pair<string, dxParticleSystem*>(psName,inPS));
	//inSK->setClassName(typeid(inSK).name());
	//inPS = dynamic_cast<>
	inSK->init();
	_mapSK.insert(pair<string, dxSkill*>(skName, inSK));
}

//void dxSkillManager::skillInit()
//{
//	_iter = _mapSK.begin();
//	for (_iter; _iter != _mapSK.end(); ++_iter)
//	{
//		_iter->second->init();
//	}
//}

