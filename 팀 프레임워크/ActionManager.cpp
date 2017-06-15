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
	actionMap.insert(make_pair("일반공격", new ActionAttack));
	actionMap.insert(make_pair("일반죽음", new ActionDie));
//	actionMap.insert(make_pair("일반이동", new ActionMove));
//	actionMap.insert(make_pair("일반재이동", new ActionReMove));
	actionMap.insert(make_pair("일반시퀸스", new ActionSeq));
	actionMap.insert(make_pair("일반재이동시퀸스", new ActionSeq));
	actionMap.insert(make_pair("일반대기", new ActionStanding));
	actionMap.insert(make_pair("보스공격", new bossActionAttack));
	actionMap.insert(make_pair("보스시네마", new bossActionCinema));
	actionMap.insert(make_pair("보스죽음", new bossActionDie));
	actionMap.insert(make_pair("보스이동", new bossActionMove));
	actionMap.insert(make_pair("배틀로어", new bossActionSkillBattleRoar));
	actionMap.insert(make_pair("보스브레스", new bossActionSkillFire));
	actionMap.insert(make_pair("꼬리공격", new bossActionSkillTailAtt));
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
		if (!actionMapIter->first.compare("일반시퀸스"))
		{
			land->getDijkstra().FindPath(singleMonster->_transform->GetWorldPosition(), player->_transform->GetWorldPosition());
			return land->getDijkstra().OptimizedAction(*singleMonster, land, objectVector, singleMonster->_transform->GetWorldPosition(), player->_transform->GetWorldPosition());
		}
		else if (!actionMapIter->first.compare("일반재이동시퀸스"))
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

	//전체삭제
	actionMap.clear();
}
