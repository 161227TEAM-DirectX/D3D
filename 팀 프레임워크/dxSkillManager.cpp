#include "stdafx.h"
#include "dxSkillManager.h"
#include "dxSkill.h"


// ## [ 플레이어 스킬 ] ## ==================================================
#include "skPlayer_MagicShoot.h"
#include "skPlayer_Heal.h"
#include "skPlayer_Shield.h"
#include "skPlayer_FireMagic.h"
#include "skPlayer_Lightning.h"
#include "skPlayer_ShootingStar.h"
#include "skPlayer_SkySword.h"
#include "skPlayer_Whirlwind.h"

// ## [ 보스 스킬 ] ## ==================================================
#include "skBoss_Breath.h"
#include "skBoss_GrandMagic.h"
#include "skBoss_Shouting.h"
#include "skBoss_EnergyBullet.h"
#include "skBoss_FireField.h"
#include "skBoss_Scratch.h"
#include "skBoss_FirePath.h"

#include "skBoss_PatternOX.h"


void dxSkillManager::skillSetting()
{
	//플레이어 스킬 등록
	this->addSK("매직슈터", new skPlayer_MagicShoot);
	this->addSK("힐", new skPlayer_Heal);
	this->addSK("매직쉴드", new skPlayer_Shield);
	this->addSK("파이어매직", new skPlayer_FireMagic);
	this->addSK("라이트닝", new skPlayer_Lightning);
	this->addSK("샛별_떨구기", new skPlayer_ShootingStar);
	this->addSK("하늘의_대검", new skPlayer_SkySword);
	this->addSK("빙글빙글", new skPlayer_Whirlwind);

	//보스 스킬 등록
	this->addSK("브레스", new skBoss_Breath);
	this->addSK("대마법", new skBoss_GrandMagic);
	this->addSK("샤우팅", new skBoss_Shouting);//터짐 하지마~
	this->addSK("에너지탄", new skBoss_EnergyBullet);
	this->addSK("화염장판", new skBoss_FireField);
	this->addSK("화염장판2", new skBoss_FireField);

	this->addSK("할퀴기_왼발", new skBoss_Scratch);
	this->addSK("할퀴기_오른발", new skBoss_Scratch);
	this->addSK("불꽃길", new skBoss_FirePath);

	this->addSK("패턴", new skBoss_PatternOX);



}

void dxSkillManager::skillRelease()
{
	//SAFE_DELETE(_playerMagicShoot);
	//SAFE_DELETE(_bossBreath);
	_iter = _mapSK.begin();
	for (_iter; _iter != _mapSK.end(); ++_iter)
	{
		//_iter->second->ReleaseSkillPS();
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

