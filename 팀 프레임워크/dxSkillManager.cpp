#include "stdafx.h"
#include "dxSkillManager.h"
#include "dxSkill.h"


// ## [ 플레이어 스킬 ] ## ==================================================
#include "skPlayer_MagicShoot.h"
#include "skPlayer_Heal.h"

// ## [ 보스 스킬 ] ## ==================================================
#include "skBoss_Breath.h"
#include "skBoss_GrandMagic.h"
#include "skBoss_Shouting.h"

void dxSkillManager::skillSetting()
{
	//플레이어 스킬 등록
	this->addSK("매직슈터", new skPlayer_MagicShoot);
	this->addSK("힐", new skPlayer_Heal);

	//보스 스킬 등록
	this->addSK("브레스", new skBoss_Breath);
	this->addSK("대마법", new skBoss_GrandMagic);
	this->addSK("샤우팅", new skBoss_Shouting);

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

