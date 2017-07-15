#include "stdafx.h"
#include "dxSkillManager.h"
#include "dxSkill.h"


// ## [ �÷��̾� ��ų ] ## ==================================================
#include "skPlayer_MagicShoot.h"
#include "skPlayer_Heal.h"
#include "skPlayer_Shield.h"
#include "skPlayer_FireMagic.h"
#include "skPlayer_Lightning.h"
#include "skPlayer_ShootingStar.h"
#include "skPlayer_SkySword.h"
#include "skPlayer_Whirlwind.h"

// ## [ ���� ��ų ] ## ==================================================
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
	//�÷��̾� ��ų ���
	this->addSK("��������", new skPlayer_MagicShoot);
	this->addSK("��", new skPlayer_Heal);
	this->addSK("��������", new skPlayer_Shield);
	this->addSK("���̾����", new skPlayer_FireMagic);
	this->addSK("����Ʈ��", new skPlayer_Lightning);
	this->addSK("����_������", new skPlayer_ShootingStar);
	this->addSK("�ϴ���_���", new skPlayer_SkySword);
	this->addSK("���ۺ���", new skPlayer_Whirlwind);

	//���� ��ų ���
	this->addSK("�극��", new skBoss_Breath);
	this->addSK("�븶��", new skBoss_GrandMagic);
	this->addSK("������", new skBoss_Shouting);//���� ������~
	this->addSK("������ź", new skBoss_EnergyBullet);
	this->addSK("ȭ������", new skBoss_FireField);
	this->addSK("ȭ������2", new skBoss_FireField);

	this->addSK("������_�޹�", new skBoss_Scratch);
	this->addSK("������_������", new skBoss_Scratch);
	this->addSK("�Ҳɱ�", new skBoss_FirePath);

	this->addSK("����", new skBoss_PatternOX);



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
	//�ִ��� Ȯ��
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

