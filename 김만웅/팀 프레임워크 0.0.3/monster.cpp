#include "stdafx.h"
#include "monster.h"


monster::monster() : baseObject(), linkTerrain(nullptr), linkObject(nullptr), CurrAction(nullptr), NextAction(nullptr)
{
}


monster::~monster()
{
	SAFE_DELETE(CurrAction);
	SAFE_DELETE(NextAction);
}

void monster::baseObjectEnable()
{
	range.setBound(&D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(RANGE, RANGE, RANGE));
	D3DXVECTOR3 tempPosition = _transform->GetForward();

	tempPosition.z *= 0.1f;
	tempPosition.y = 0.07f;
	hitBox.setBound(&tempPosition, &D3DXVECTOR3(0.04f, 0.06f, 0.06f));

	HP = myUtil::RandomIntRange(MINHM, MAXHM);
	mana = myUtil::RandomIntRange(MINHM, MAXHM);
	gold = myUtil::RandomIntRange(MINGS, MAXGS);
	soul = myUtil::RandomIntRange(MINGS, MAXGS);
	att = DEFAULTATT;
	def = DEFAULTDEF;
	CurrAction = new ActionStanding;
	CurrAction->setOwner(this);
	CurrAction->setObject(linkObject);
	CurrAction->setRand(*linkTerrain);
	CurrAction->setEnemy(player);
	result = (LHS::ACTIONRESULT)CurrAction->Start();
}

void monster::baseObjectDisable()
{
}

void monster::baseObjectUpdate()
{
	stateSwitch();

	if (NextAction != nullptr)
	{
		delete CurrAction;
		CurrAction = NextAction;
		result = (LHS::ACTIONRESULT)CurrAction->Start();
		NextAction = nullptr;
	}

	if (CurrAction) result = (LHS::ACTIONRESULT)CurrAction->Update();
	_skinnedAnim->update();
}

void monster::baseObjectNoActiveUpdate()
{
}

void monster::baseObjectRender()
{
	if (_skinnedAnim != nullptr) _skinnedAnim->render(_transform);
	hitBox.renderGizmo(_transform);
	range.renderGizmo(_transform);

	_boundBox.renderGizmo(_transform);
}

void monster::stateSwitch(void)
{
	//������ HP�� �������� ���� ���·� ����
	// �� �׼��� update �Լ��� ���� �Ŀ� ���°��� �Ѱܿ´�.
	// �� ���°��� ���� ���Ͱ� �ؾ� �� �ൿ�� ���ϸ� �ȴ�.
	switch (result)
	{
		//���� ���� �׼��� ����Ǿ����� �˷��ö� -> standing���·� ���ư���.
	case LHS::ACTIONRESULT::ACTION_FINISH:
		NextAction = new ActionStanding;
		NextAction->setOwner(this);
		NextAction->setObject(linkObject);
		NextAction->setRand(*linkTerrain);
		NextAction->setEnemy(player);
		break;
		//�׼��� �Ҵ�, �پ��� ������ ������ ���
	case LHS::ACTIONRESULT::ACTION_FAIL:
		MessageBox(nullptr, "new �������� ������ ������ϴ�.", "!!!!", MB_OK);
		exit(1);
		break;
		//���� �׼��� �����ϴ� ���̸� ���� ������ �����ų� �ٸ� ��찡 ���� �����϶�.
		//Ư���� �� �� ���� ��� �׼��� ���ϸ� �ȴ�.
	case LHS::ACTIONRESULT::ACTION_PLAY:
		return;
		//�׼��� ����Ǿ��ٰų�, �ٽ� Ž�����·� ���ư��� �Ҷ�.
	case LHS::ACTIONRESULT::ACTION_STAND:
		NextAction = new ActionStanding;
		NextAction->setOwner(this);
		NextAction->setObject(linkObject);
		NextAction->setRand(*linkTerrain);
		NextAction->setEnemy(player);
		break;
		// �̵��� �ʿ��� ���
	case LHS::ACTIONRESULT::ACTION_MOVE:
		linkTerrain->getDijkstra().FindPath(_transform->GetWorldPosition(), player->_transform->GetWorldPosition());
		NextAction = linkTerrain->getDijkstra().OptimizedAction(*this, *player, linkTerrain, *linkObject, _transform->GetWorldPosition(), player->_transform->GetWorldPosition());
		break;
		//������ ���� ��ġ�� ���ư��� �ϴ� ���
	case LHS::ACTIONRESULT::ACTION_REMOVE:
		linkTerrain->getDijkstra().FindPath(_transform->GetWorldPosition(), regenPosition);
		NextAction = linkTerrain->getDijkstra().OptimizedAction(*this, linkTerrain, *linkObject, _transform->GetWorldPosition(), regenPosition);
		break;
		//������ �ؾ� �ϴ� ���
	case LHS::ACTIONRESULT::ACTION_ATT:
	{
		ActionAttack* temp = new ActionAttack;
		temp->setOwner(this);
		temp->setObject(linkObject);
		temp->setRand(*linkTerrain);
		temp->setActionTime(LHS::MOVETIME);
		temp->setEnemy(player);

		NextAction = temp;
	}
	break;
	//���� ������ �޾� ������ �Ǿ�� �ϴ� ���
	case LHS::ACTIONRESULT::ACTION_STUN:
		NextAction = new ActionStun;
		break;
		//�׾�����.
	case LHS::ACTIONRESULT::ACTION_DIE:
		NextAction = new ActionDie;
		break;
	case LHS::ACTIONRESULT::ACTION_NONE:
		break;
	}

	//���� �÷��̾ ���� ����� ���� ���Ͽ� �ɸ����� ����


	//���Ͱ� ������ �ް� �Ǹ� �ɸ����� ��ġ�� �̵�


	//������ ��ġ�� �̵� �Ŀ��� ���� ��� �۵�
	//for (int i = 0; i < linkObject->size(); i++)
	//{
	//	if (PHYSICSMANAGER->isOverlap(_skTransform, &_boundBox, (*linkObject)[i]->_transform, &(*linkObject)[i]->_boundBox))
	//	{
	//		
	//		return;
	//	}
	//}

	//������ ���� �ڽ��� �ɸ��Ͱ� ���� �ɸ����� ��ġ�� �̵�


	//���� �ƹ��͵� �ɸ��� �ʾҴٸ� standing����

}
