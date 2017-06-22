#include "stdafx.h"
#include "bossMonster.h"


bossMonster::bossMonster() : monster(), Frequency(0)
{
}


bossMonster::~bossMonster()
{
	SAFE_DELETE(CurrAction);
	SAFE_DELETE(NextAction);
}

void bossMonster::baseObjectEnable()
{
	D3DXVECTOR3 temp(_boundBox._localCenter);
	temp.z = _boundBox._localMaxPos.z;
	//���ڽ�
	range.setBound(&D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(_transform->GetScale().x * BOSSRANGE, _transform->GetScale().y * BOSSRANGE, _transform->GetScale().z * BOSSRANGE));

	//�浹�ڽ�
	hitBox.setBound(&temp, &D3DXVECTOR3(_transform->GetScale().x * 0.6f, temp.y*1.0f, _transform->GetScale().z * 0.5f));

	HP = 100000;
	mana = 10000;
	gold = 10000;
	soul = 100;
	att = 1000;
	def = 550;

	//��Ʈ�ѿ� ���� �ʱ� �׼�
	CurrAction = ACMANAGER->getAction("�����ó׸�", *this);
	result = (LHS::ACTIONRESULT)CurrAction->Start();
}

void bossMonster::baseObjectDisable()
{
	SAFE_DELETE(CurrAction);
	SAFE_DELETE(NextAction);
	_transform->SetWorldPosition(0.0f, 0.0f, 0.0f);
}

void bossMonster::baseObjectUpdate()
{
	switchState();

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

void bossMonster::baseObjectNoActiveUpdate()
{
}

void bossMonster::baseObjectRender()
{
	if (_skinnedAnim != nullptr) _skinnedAnim->render(_transform);
	hitBox.renderGizmo(_transform, D3DCOLOR_XRGB(255,0,0));
	range.renderGizmo(_transform, D3DCOLOR_XRGB(255,255,0));

	_boundBox.renderGizmo(_transform);
}

void bossMonster::switchState(void)
{
	switch (result)
	{
	case LHS::ACTION_ATT:
		NextAction = ACMANAGER->getAction("��������", *this);
		break;
	case LHS::ACTION_DIE:
		NextAction = ACMANAGER->getAction("��������", *this);
		break;
	case LHS::ACTION_FAIL:
		MessageBox(nullptr, "������ �߻��߾�� �ѿ�~", "����", MB_OK);
		exit(0);
		break;
	case LHS::ACTION_FINISH:
		MessageBox(nullptr, "������ �߻��߾�� �ѿ�~", "����", MB_OK);
		NextAction = ACMANAGER->getAction("�����̵�", *this);
		break;
	case LHS::ACTION_MOVE:
		NextAction = ACMANAGER->getAction("�����̵�", *this);
		break;
	case LHS::ACTION_NONE:
		setActive(false);
		break;
	case LHS::ACTION_PLAY:
		return;
	case LHS::ACTION_REMOVE:
		break;
	case LHS::ACTION_SKILL_TAIL:
		NextAction = ACMANAGER->getAction("��������", *this);
		break;
	case LHS::ACTION_SKILL_FIRE:
		NextAction = ACMANAGER->getAction("�����극��", *this);
		break;
	case LHS::ACTION_SKILL_BATTLE_ROAR:
		NextAction = ACMANAGER->getAction("��Ʋ�ξ�", *this);
		break;
	case LHS::ACTIONRESULT::ACTION_FLY:
		NextAction = ACMANAGER->getAction("����", *this);
		break;
	}
}
