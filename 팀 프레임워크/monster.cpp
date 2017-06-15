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
	D3DXVECTOR3 temp(_boundBox._localCenter);
	range.setBound(&temp, &D3DXVECTOR3(_transform->GetScale().x * RANGE, _transform->GetScale().y * RANGE, _transform->GetScale().z * RANGE));

	temp.z = _boundBox._localMaxPos.z;
	
	hitBox.setBound(&temp, &D3DXVECTOR3(_transform->GetScale().x * 1.6f, _transform->GetScale().y * 2.9f, _transform->GetScale().z * 2.9f));

	HP = myUtil::RandomIntRange(MINHM, MAXHM);
	mana = myUtil::RandomIntRange(MINHM, MAXHM);
	gold = myUtil::RandomIntRange(MINGS, MAXGS);
	soul = myUtil::RandomIntRange(MINGS, MAXGS);
	att = DEFAULTATT;
	def = DEFAULTDEF;
	CurrAction = ACMANAGER->getAction("�Ϲݴ��");
	/*CurrAction = new ActionStanding;
	CurrAction->setOwner(*this);
	CurrAction->setObject(*linkObject);
	CurrAction->setRand(*linkTerrain);
	CurrAction->setEnemy(*player);*/
	result = (LHS::ACTIONRESULT)CurrAction->Start();
}

void monster::baseObjectDisable()
{
//	SAFE_DELETE(CurrAction);
//	SAFE_DELETE(NextAction);
	CurrAction = nullptr;
	NextAction = nullptr;
	this->_transform->SetWorldPosition(regenPosition);
}

void monster::baseObjectUpdate()
{
	stateSwitch();

	if (NextAction != nullptr)
	{
		CurrAction = nullptr;
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
	hitBox.renderGizmo(_transform, D3DCOLOR_XRGB(255, 0, 0));
	range.renderGizmo(_transform, D3DCOLOR_XRGB(255, 255, 0));

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
		NextAction = ACMANAGER->getAction("�Ϲݴ��");
		/*NextAction = new ActionStanding;
		NextAction->setOwner(*this);
		NextAction->setObject(*linkObject);
		NextAction->setRand(*linkTerrain);
		NextAction->setEnemy(*player);*/
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
		NextAction = ACMANAGER->getAction("�Ϲݴ��");
		/*NextAction = new ActionStanding;
		NextAction->setOwner(*this);
		NextAction->setObject(*linkObject);
		NextAction->setRand(*linkTerrain);
		NextAction->setEnemy(*player);*/
		break;
	// �̵��� �ʿ��� ���
	case LHS::ACTIONRESULT::ACTION_MOVE:
		NextAction = ACMANAGER->getAction("�Ϲݽ�����");
		/*linkTerrain->getDijkstra().FindPath(_transform->GetWorldPosition(), player->_transform->GetWorldPosition());
		NextAction = linkTerrain->getDijkstra().OptimizedAction(*this, *player, linkTerrain, *linkObject, _transform->GetWorldPosition(), player->_transform->GetWorldPosition());*/
		break;
	//������ ���� ��ġ�� ���ư��� �ϴ� ���
	case LHS::ACTIONRESULT::ACTION_REMOVE:
		NextAction = ACMANAGER->getAction("�Ϲ����̵�������");
//		linkTerrain->getDijkstra().FindPath(_transform->GetWorldPosition(), regenPosition);
//		NextAction = linkTerrain->getDijkstra().OptimizedAction(*this, linkTerrain, *linkObject, _transform->GetWorldPosition(), regenPosition);
		break;
		//������ �ؾ� �ϴ� ���
	case LHS::ACTIONRESULT::ACTION_ATT:
	{
		ActionAttack* temp = new ActionAttack;
		temp->setOwner(*this);
		temp->setObject(*linkObject);
		temp->setRand(*linkTerrain);
		temp->setEnemy(*player);
		NextAction = ACMANAGER->getAction("�Ϲݰ���");
	}
	break;
		//�׾�����.
	case LHS::ACTIONRESULT::ACTION_DIE:
		NextAction = ACMANAGER->getAction("�Ϲ�����");
		break;
	case LHS::ACTIONRESULT::ACTION_NONE:
		this->setActive(false);
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
