#include "stdafx.h"
#include "bossMonster.h"
#include "bossActionControl.h"


bossMonster::bossMonster() : monster(), Frequency(0)
{
	control = new bossActionControl(this);
}


bossMonster::~bossMonster()
{
	SAFE_DELETE(control);
}

void bossMonster::baseObjectEnable()
{
	D3DXVECTOR3 temp(_boundBox._localCenter);
	temp.z = _boundBox._localMaxPos.z;
	//���ڽ� - �������� �ʿ������� �ǹ��̴�..... �ʿ� �ϰ���?
	range.setBound(&D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(RANGE, RANGE, RANGE));

	//�浹�ڽ�
	hitBox.setBound(&temp, &D3DXVECTOR3(_transform->GetScale().x * 2.6f, _transform->GetScale().y * 2.9f, _transform->GetScale().z * 2.9f));

	HP = myUtil::RandomIntRange(MINHM, MAXHM);
	mana = myUtil::RandomIntRange(MINHM, MAXHM);
	gold = myUtil::RandomIntRange(MINGS, MAXGS);
	soul = myUtil::RandomIntRange(MINGS, MAXGS);
	att = DEFAULTATT;
	def = DEFAULTDEF;

	//��Ʈ�ѿ� ���� �ʱ� �׼�
	control->Init(CurrAction, result);
}

void bossMonster::baseObjectDisable()
{
}

void bossMonster::baseObjectUpdate()
{
	control->switchState(result);

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

void bossMonster::baseObjectNoActiveUpdate()
{
}

void bossMonster::baseObjectRender()
{
	if (_skinnedAnim != nullptr) _skinnedAnim->render(_transform);
	hitBox.renderGizmo(_transform);
	//range.renderGizmo(_transform);

	_boundBox.renderGizmo(_transform);
}