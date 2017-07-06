#include "stdafx.h"
#include "xPlayer.h"
#include "monster.h"
#include "ActionManager.h"
#include "Action.h"
#include "ActionAttack.h"
#include "ActionDie.h"
#include "ActionMove.h"
#include "ActionReMove.h"
#include "ActionSeq.h"
#include "ActionStanding.h"
#include "bossActionAttack.h"
#include "bossActionCinema.h"
#include "bossActionDie.h"
#include "bossActionMove.h"
#include "bossActionSkillBattleRoar.h"
#include "bossActionSkillFire.h"
#include "bossActionSkillTailAtt.h"
#include "bossActionFly.h"
#include "bossActionFlyDie.h"
#include "bossActionFlyMove.h"
#include "bossActionLanding.h"

ActionManager::ActionManager()
{
	actionName.push_back("�Ϲݰ���");
	actionName.push_back("�Ϲ�����");
	actionName.push_back("�Ϲݽ�����");
	actionName.push_back("�Ϲ����̵�������");
	actionName.push_back("�Ϲݴ��");
	actionName.push_back("��������");
	actionName.push_back("�����ó׸�");
	actionName.push_back("��������");
	actionName.push_back("�����̵�");
	actionName.push_back("��Ʋ�ξ�");
	actionName.push_back("�����극��");
	actionName.push_back("��������");
	actionName.push_back("����");
	actionName.push_back("��������");
	actionName.push_back("�����̵�");
	actionName.push_back("����");
}


ActionManager::~ActionManager()
{
	clearAction();
}

Action * ActionManager::getAction(string Name, baseObject& who)
{
	Action* temp = nullptr;
	if (!actionName[0].compare(Name)) temp = new ActionAttack;
	else if (!actionName[1].compare(Name)) temp = new ActionDie;
	else if (!actionName[2].compare(Name))
	{
		land->getDijkstra().FindPath(who._transform->GetWorldPosition(), player->getPlayerObject()->_transform->GetWorldPosition());
		return land->getDijkstra().OptimizedAction(who, *player->getPlayerObject(), *land, *objectVector, who._transform->GetWorldPosition(), player->getPlayerObject()->_transform->GetWorldPosition());
	}
	else if (!actionName[3].compare(Name))
	{
		monster* temp = dynamic_cast<monster*>(&who);
		land->getDijkstra().FindPath(who._transform->GetWorldPosition(), temp->getRegenPosition());
		return land->getDijkstra().OptimizedAction(who, *land, *objectVector, who._transform->GetWorldPosition(), temp->getRegenPosition());
	}
	else if (!actionName[4].compare(Name)) temp = new ActionStanding;
	else if (!actionName[5].compare(Name)) temp = new bossActionAttack;
	else if (!actionName[6].compare(Name)) temp = new bossActionCinema;
	else if (!actionName[7].compare(Name)) temp = new bossActionDie;
	else if (!actionName[8].compare(Name)) temp = new bossActionMove;
	else if (!actionName[9].compare(Name)) temp = new bossActionSkillBattleRoar;
	else if (!actionName[10].compare(Name)) temp = new bossActionSkillFire;
	else if (!actionName[11].compare(Name)) temp = new bossActionSkillTailAtt;
	else if (!actionName[12].compare(Name)) temp = new bossActionFly;
	else if (!actionName[13].compare(Name)) temp = new bossActionFlyDie;
	else if (!actionName[14].compare(Name)) temp = new bossActionFlyMove;
	else if (!actionName[15].compare(Name))temp = new bossActionLanding;

	if (player != nullptr) temp->setEnemy(*player);
	if (player != nullptr) temp->setPlayerObject(*player->getPlayerObject());
	if(objectVector != nullptr) temp->setObject(*objectVector);
	else
	{
		objectVector = &tempObjectVector;
	}
	temp->setOwner(who);
	temp->setRand(*land);
	return temp;
}

void ActionManager::clearAction(void)
{
}
