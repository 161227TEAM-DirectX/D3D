#include "stdafx.h"
#include "bossMonster.h"


bossMonster::bossMonster() : monster()
{
}


bossMonster::~bossMonster()
{
	SAFE_DELETE(m_pBar);
}

void bossMonster::baseObjectEnable()
{
	D3DXVECTOR3 temp(_boundBox._localCenter);
	temp.z = _boundBox._localMaxPos.z;

	//경계박스
	range.setBound(&D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(_boundBox._localMaxPos.x * BOSSRANGE, _boundBox._localMaxPos.y * BOSSRANGE, _boundBox._localMaxPos.z * BOSSRANGE));

	//충돌박스
	hitBox.setBound(&temp, &D3DXVECTOR3(_transform->GetScale().x * 0.6f, temp.y*1.0f, _transform->GetScale().z * 0.5f));

	HP = 100000;
	mana = 10000;
	gold = 10000;
	soul = 100;
	att = 1000;
	def = 550;

	_skinnedAnim->AddBoneTransform("Deathwing_Bone130", &fieldTrans);
	fieldTrans.SetWorldPosition(0, 0.5f, 0);
	_skinnedAnim->AddBoneTransform("Deathwing_Bone92", &rightTrans);
	_skinnedAnim->AddBoneTransform("Deathwing_Bone89", &leftTrans);
	_skinnedAnim->AddBoneTransform("Deathwing_Bone01_Waist", &tailTrans);
	_skinnedAnim->AddBoneTransform("Deathwing_Bone129__Breath", &breathTrans);

	//보스몬스터 체력UI 초기화
	m_pBar = new cDxImgBar("bossbar_cover",
		"bossbar_back",
		"bossbar_move",
		D3DXVECTOR2(WINSIZEX / 2, 43),
		true);
	m_pBar->setMoveGauge(m_pBar->GetMove()->GetSize().fWidth);

	//컨트롤에 의한 초기 액션
	CurrAction = ACMANAGER->getAction("보스시네마", *this);
	result = (LHS::ACTIONRESULT)CurrAction->Start();
}

void bossMonster::baseObjectDisable()
{
	//SAFE_DELETE(m_pBar);
	_transform->SetWorldPosition(0.0f, 0.0f, 0.0f);
}

void bossMonster::baseObjectUpdate()
{
	switchState();
//	testKeyAI();

	//보스몬스터 체력바 연동
	//보스 현재 체력 / 보스 최대 체력 * 100
	m_pBar->moveBar((float)HP / (float)100000 * 100);

	if (NextAction != nullptr)
	{
		SAFE_DELETE(CurrAction);
		CurrAction = NextAction;
		//_skinnedAnim->Stop();
		result = (LHS::ACTIONRESULT)CurrAction->Start();
		NextAction = nullptr;
	}

	if (CurrAction) result = (LHS::ACTIONRESULT)CurrAction->Update();
}

void bossMonster::baseObjectNoActiveUpdate()
{
}

void bossMonster::baseObjectRender()
{
	m_pBar->render();

	if (_skinnedAnim != nullptr) _skinnedAnim->render(_transform);
	CurrAction->Render();

//	hitBox.renderGizmo(_transform, D3DCOLOR_XRGB(255,0,0));
//	range.renderGizmo(_transform, D3DCOLOR_XRGB(255,255,0));

//	_boundBox.renderGizmo(_transform);
}

void bossMonster::switchState(void)
{
	switch (result)
	{
	case LHS::ACTION_ATT:
		NextAction = ACMANAGER->getAction("보스공격", *this);
		break;
	case LHS::ACTION_DIE:
		NextAction = ACMANAGER->getAction("보스죽음", *this);
		break;
	case LHS::ACTION_FAIL:
		MessageBox(nullptr, "문제가 발생했어요 뿌우~", "ㅋㅋ", MB_OK);
		exit(0);
		break;
	case LHS::ACTION_FINISH:
		MessageBox(nullptr, "문제가 발생했어요 뿌우~", "ㅋㅋ", MB_OK);
		NextAction = ACMANAGER->getAction("보스이동", *this);
		break;
	case LHS::ACTION_MOVE:
		NextAction = ACMANAGER->getAction("보스이동", *this);
		break;
	case LHS::ACTION_NONE:
		setActive(false);
		break;
	case LHS::ACTION_PLAY:
		return;
	case LHS::ACTION_REMOVE:
		break;
	case LHS::ACTION_SKILL_TAIL:
		NextAction = ACMANAGER->getAction("꼬리공격", *this);
		break;
	case LHS::ACTION_SKILL_FIRE:
		NextAction = ACMANAGER->getAction("보스브레스", *this);
		break;
	case LHS::ACTION_SKILL_BATTLE_ROAR:
		NextAction = ACMANAGER->getAction("배틀로어", *this);
		break;
	case LHS::ACTIONRESULT::ACTION_FLY:
		NextAction = ACMANAGER->getAction("날기", *this);
		break;
	case LHS::ACTIONRESULT::ACTION_FLY_DIE:
		NextAction = ACMANAGER->getAction("날기죽음", *this);
		break;
	case LHS::ACTIONRESULT::ACTION_FLY_MOVE_ATT:
		NextAction = ACMANAGER->getAction("날기이동", *this);
		break;
	case LHS::ACTIONRESULT::ACTION_LANDING:
		NextAction = ACMANAGER->getAction("착지", *this);
		break;
	case LHS::ACTIONRESULT::ACTION_PA_OX:
		NextAction = ACMANAGER->getAction("OX패턴", *this);
		break;
	case LHS::ACTIONRESULT::ACTION_SAFE:
		return;
	}
}

void bossMonster::testKeyAI(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD0))
	{
		NextAction = ACMANAGER->getAction("보스공격", *this);
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1))
	{
		NextAction = ACMANAGER->getAction("보스죽음", *this);
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2))
	{
		NextAction = ACMANAGER->getAction("보스이동", *this);
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD3))
	{
		NextAction = ACMANAGER->getAction("꼬리공격", *this);
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
	{
		NextAction = ACMANAGER->getAction("보스브레스", *this);
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
	{
		NextAction = ACMANAGER->getAction("배틀로어", *this);
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD6))
	{
		NextAction = ACMANAGER->getAction("날기", *this);
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD7))
	{
		NextAction = ACMANAGER->getAction("날기죽음", *this);
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD8))
	{
		NextAction = ACMANAGER->getAction("날기이동", *this);
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD9))
	{
		NextAction = ACMANAGER->getAction("착지", *this);
	}
	else if (KEYMANAGER->isOnceKeyDown('L'))
	{
		NextAction = ACMANAGER->getAction("보스시네마", *this);
	}
	else if (KEYMANAGER->isOnceKeyDown('K'))
	{
		NextAction = ACMANAGER->getAction("OX패턴", *this);
	}
}
