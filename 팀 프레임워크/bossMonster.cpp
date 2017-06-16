#include "stdafx.h"
#include "bossMonster.h"
#include "bossActionControl.h"


bossMonster::bossMonster() : monster(), Frequency(0)
{
}


bossMonster::~bossMonster()
{
}

void bossMonster::baseObjectEnable()
{
	D3DXVECTOR3 temp(_boundBox._localCenter);
	temp.z = _boundBox._localMaxPos.z;
	//���ڽ�
	range.setBound(&D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(_transform->GetScale().x * BOSSRANGE, _transform->GetScale().y * BOSSRANGE, _transform->GetScale().z * BOSSRANGE));

	//�浹�ڽ�
	hitBox.setBound(&temp, &D3DXVECTOR3(_transform->GetScale().x * 2.6f, temp.y*1.9f, _transform->GetScale().z * 2.9f));

	HP = myUtil::RandomIntRange(MINHM, MAXHM);
	mana = myUtil::RandomIntRange(MINHM, MAXHM);
	gold = myUtil::RandomIntRange(MINGS, MAXGS);
	soul = myUtil::RandomIntRange(MINGS, MAXGS);
	att = DEFAULTATT;
	def = DEFAULTDEF;

	//��Ʈ�ѿ� ���� �ʱ� �׼�
	CurrAction = ACMANAGER->getAction("�����ó׸�", *this);
	result = (LHS::ACTIONRESULT)CurrAction->Start();
}

void bossMonster::baseObjectDisable()
{
}

void bossMonster::baseObjectUpdate()
{
	switchState();

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
	}
}
