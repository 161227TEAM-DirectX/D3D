#include "stdafx.h"
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

ActionManager::ActionManager()
{
	actionMap.insert(make_pair("�Ϲݰ���", new ActionAttack));
	actionMap.insert(make_pair("�Ϲ�����", new ActionDie));
//	actionMap.insert(make_pair("�Ϲ��̵�", new ActionMove));
//	actionMap.insert(make_pair("�Ϲ����̵�", new ActionReMove));
	actionMap.insert(make_pair("�Ϲݽ�����", new ActionSeq));
	actionMap.insert(make_pair("�Ϲ����̵�������", new ActionSeq));
	actionMap.insert(make_pair("�Ϲݴ��", new ActionStanding));
	actionMap.insert(make_pair("��������", new bossActionAttack));
	actionMap.insert(make_pair("�����ó׸�", new bossActionCinema));
	actionMap.insert(make_pair("��������", new bossActionDie));
	actionMap.insert(make_pair("�����̵�", new bossActionMove));
	actionMap.insert(make_pair("��Ʋ�ξ�", new bossActionSkillBattleRoar));
	actionMap.insert(make_pair("�����극��", new bossActionSkillFire));
	actionMap.insert(make_pair("��������", new bossActionSkillTailAtt));
}


ActionManager::~ActionManager()
{
	clearAction();
}

Action * ActionManager::getAction(string Name)
{
	actionMapIter = actionMap.find(Name);

	if (actionMapIter == actionMap.end())
	{
		return nullptr;
	}
	else
	{
		if (!actionMapIter->first.compare("�Ϲݽ�����"))
		{
			land->getDijkstra().FindPath(singleMonster->_transform->GetWorldPosition(), player->_transform->GetWorldPosition());
			return land->getDijkstra().OptimizedAction(*singleMonster, land, objectVector, singleMonster->_transform->GetWorldPosition(), player->_transform->GetWorldPosition());
		}
		else if (!actionMapIter->first.compare("�Ϲ����̵�������"))
		{
			monster* temp = dynamic_cast<monster*>(singleMonster);
			land->getDijkstra().FindPath(singleMonster->_transform->GetWorldPosition(), temp->getRegenPosition());
			return land->getDijkstra().OptimizedAction(*singleMonster, land, objectVector, singleMonster->_transform->GetWorldPosition(), temp->getRegenPosition());
		}
		actionMapIter->second->setEnemy(*player);
		actionMapIter->second->setObject(objectVector);
		actionMapIter->second->setOwner(*singleMonster);
		actionMapIter->second->setRand(*land);
		return actionMapIter->second;
	}
}

void ActionManager::clearAction(void)
{
	for (actionMapIter = actionMap.begin(); actionMapIter != actionMap.end(); ++actionMapIter)
	{
		SAFE_DELETE(actionMapIter->second);
	}

	//��ü����
	actionMap.clear();
}
