#include "stdafx.h"
#include "monster.h"


monster::monster() 
	: baseObject(), CurrAction(nullptr), NextAction(nullptr)
	, _mainCamera(nullptr)
{
}

monster::monster(string Name)
	: baseObject(), CurrAction(nullptr), NextAction(nullptr)
	, Name(Name), _mainCamera(nullptr)
{
}

monster::monster(camera* _mainCamera, string Name)
	: baseObject(), CurrAction(nullptr), NextAction(nullptr)
	, Name(Name), _mainCamera(_mainCamera)
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
	
	hitBox.setBound(&temp, &D3DXVECTOR3(_transform->GetScale().x * 0.6f, temp.y * 1.0f, _transform->GetScale().z * 0.3f));

	HP = myUtil::RandomIntRange(MINHM, MAXHM);
	mana = myUtil::RandomIntRange(MINHM, MAXHM);
	gold = myUtil::RandomIntRange(MINGS, MAXGS);
	soul = myUtil::RandomIntRange(MINGS, MAXGS);
	att = DEFAULTATT;
	def = DEFAULTDEF;
	CurrAction = ACMANAGER->getAction("�Ϲݴ��", *this);

	result = (LHS::ACTIONRESULT)CurrAction->Start();
}

void monster::baseObjectDisable()
{
	SAFE_DELETE(CurrAction);
	SAFE_DELETE(NextAction);

	this->_transform->SetWorldPosition(regenPosition);
}

void monster::baseObjectUpdate()
{
	stateSwitch();

	if (NextAction != nullptr)
	{
		SAFE_DELETE(CurrAction);
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

	if(_mainCamera!=nullptr) SPRITEMANAGER->RenderFont(_mainCamera, Name);

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
		NextAction = ACMANAGER->getAction("�Ϲݴ��", *this);
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
		NextAction = ACMANAGER->getAction("�Ϲݴ��", *this);
		break;
	// �̵��� �ʿ��� ���
	case LHS::ACTIONRESULT::ACTION_MOVE:
		NextAction = ACMANAGER->getAction("�Ϲݽ�����", *this);
		break;
	//������ ���� ��ġ�� ���ư��� �ϴ� ���
	case LHS::ACTIONRESULT::ACTION_REMOVE:
		NextAction = ACMANAGER->getAction("�Ϲ����̵�������", *this);
		break;
		//������ �ؾ� �ϴ� ���
	case LHS::ACTIONRESULT::ACTION_ATT:
		NextAction = ACMANAGER->getAction("�Ϲݰ���", *this);
		break;
		//�׾�����.
	case LHS::ACTIONRESULT::ACTION_DIE:
		NextAction = ACMANAGER->getAction("�Ϲ�����", *this);
		break;
	case LHS::ACTIONRESULT::ACTION_NONE:
		this->setActive(false);
		break;
	}
}
