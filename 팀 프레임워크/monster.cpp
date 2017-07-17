#include "stdafx.h"
#include "monster.h"


//monster::monster() 
//	: baseObject(), CurrAction(nullptr), NextAction(nullptr)
//	, _mainCamera(nullptr)
//{
//	
//}

monster::monster(string Name)
	: baseObject(), CurrAction(nullptr), NextAction(nullptr), dieCount(60), isRender(false)
{
	name = new Text;
	prefixName = "";
	lastName = Name;
}


monster::~monster()
{
	SAFE_DELETE(CurrAction);
	SAFE_DELETE(NextAction);
	SAFE_DELETE(name);
}

void monster::baseObjectEnable()
{
	D3DXVECTOR3 temp(_boundBox._localCenter);
	range.setBound(&temp, &D3DXVECTOR3(_transform->GetScale().x * RANGE, _transform->GetScale().y * RANGE, _transform->GetScale().z * RANGE));

	temp.z = _boundBox._localMaxPos.z;
	
	hitBox.setBound(&temp, &D3DXVECTOR3(_transform->GetScale().x * 0.6f, temp.y * 1.0f, _transform->GetScale().z * 0.3f));

	name->setPos(D3DXVECTOR3(_transform->GetWorldPosition().x, _boundBox._localMaxPos.y, _transform->GetWorldPosition().z));

	HP = myUtil::RandomIntRange(MINHM, MAXHM);
	mana = myUtil::RandomIntRange(MINHM, MAXHM);
	gold = myUtil::RandomIntRange(MINGS, MAXGS);
	soul = myUtil::RandomIntRange(MINGS, MAXGS);
	att = myUtil::RandomIntRange(MINATT, MAXATT);
	def = myUtil::RandomIntRange(MINDEF, MAXDEF);
	CurrAction = ACMANAGER->getAction("일반대기", *this);

	authorizeName();
	MAXHP = HP;
	string tempName = prefixName + lastName;

	name->init(tempName, nameColor);

	m_pBar = new cDxImgBar("bossbar_cover",
		"bossbar_back",
		"bossbar_move",
		D3DXVECTOR2(WINSIZEX / 2, 43),
		true);
	m_pBar->setMoveGauge(m_pBar->GetMove()->GetSize().fWidth);

	result = (LHS::ACTIONRESULT)CurrAction->Start();
}

void monster::baseObjectDisable()
{
	SAFE_DELETE(CurrAction);
	SAFE_DELETE(NextAction);
	isRender = false;

	this->_transform->SetWorldPosition(regenPosition);
}

void monster::baseObjectUpdate()
{
	if (HP < 0) HP = 0;
	stateSwitch();
	name->update();

	if (isRender)
	{
		m_pBar->moveBar((float)HP / (float)MAXHP * 100);
	}

	if (NextAction != nullptr)
	{
		SAFE_DELETE(CurrAction);
		CurrAction = NextAction;
		result = (LHS::ACTIONRESULT)CurrAction->Start();
		NextAction = nullptr;
	}

	if (CurrAction != NULL) result = (LHS::ACTIONRESULT)CurrAction->Update();
	name->setPos(D3DXVECTOR3(_transform->GetWorldPosition().x, _boundBox._localMaxPos.y, _transform->GetWorldPosition().z));
}

void monster::baseObjectNoActiveUpdate()
{
	isRender = false;
	if (TIMEMANAGER->getWorldTime() - startTime > dieCount)
	{
		result = LHS::ACTIONRESULT::ACTION_STAND;
		setActive(true);
	}
}

void monster::baseObjectRender()
{
	if (_skinnedAnim != nullptr) _skinnedAnim->render(_transform);

	if (isRender)
	{
		m_pBar->render();
	}
	

	CurrAction->Render();

	D3DXVECTOR3 temp = { _transform->GetWorldPosition().x, _boundBox._localMaxPos.y, _transform->GetWorldPosition().z };
	name->render();

	//string temps = "hp:" + to_string(HP);

	//FONTMANAGER->fontOut(temps.c_str(), 100, 100, D3DCOLOR_XRGB(255, 255, 255));

//	hitBox.renderGizmo(_transform, D3DCOLOR_XRGB(255, 0, 0));
//	range.renderGizmo(_transform, D3DCOLOR_XRGB(255, 255, 0));

//	_boundBox.renderGizmo(_transform);
}

void monster::stateSwitch(void)
{
	//몬스터의 HP가 떨어지면 죽음 상태로 변경
	//if (HP < 0 && result != LHS::ACTIONRESULT::ACTION_NONE) result = LHS::ACTIONRESULT::ACTION_DIE;
	// 각 액션이 update 함수를 실행 후에 상태값을 넘겨온다.
	// 그 상태값에 따라 몬스터가 해야 할 행동을 취하면 된다.
	switch (result)
	{
		//리턴 값이 액션이 종료되었음을 알려올때 -> standing상태로 돌아간다.
	case LHS::ACTIONRESULT::ACTION_FINISH:
		NextAction = ACMANAGER->getAction("일반대기", *this);
		break;
	case LHS::ACTIONRESULT::ACTION_REFINISH:
		NextAction = ACMANAGER->getAction("일반대기", *this);
		break;
		//액션을 할당, 다양한 문제가 생겼을 경우
	case LHS::ACTIONRESULT::ACTION_FAIL:
		MessageBox(nullptr, "new 과정에서 문제가 생겼습니다.", "!!!!", MB_OK);
		exit(1);
		break;
		//현재 액션을 실행하는 중이며 아직 실행이 끝나거나 다른 경우가 없는 상태일때.
		//특별히 할 것 없이 계속 액션을 취하면 된다.
	case LHS::ACTIONRESULT::ACTION_PLAY:
		return;
		//액션이 종료되었다거나, 다시 탐색상태로 돌아가야 할때.
	case LHS::ACTIONRESULT::ACTION_STAND:
		NextAction = ACMANAGER->getAction("일반대기", *this);
		break;
	// 이동이 필요한 경우
	case LHS::ACTIONRESULT::ACTION_MOVE:
		NextAction = ACMANAGER->getAction("일반시퀸스", *this);
		break;
	//원래의 리젠 위치로 돌아가야 하는 경우
	case LHS::ACTIONRESULT::ACTION_REMOVE:
		NextAction = ACMANAGER->getAction("일반재이동시퀸스", *this);
		break;
		//공격을 해야 하는 경우
	case LHS::ACTIONRESULT::ACTION_ATT:
		NextAction = ACMANAGER->getAction("일반공격", *this);
		break;
		//죽었을때.
	case LHS::ACTIONRESULT::ACTION_DIE:
		NextAction = ACMANAGER->getAction("일반죽음", *this);
		break;
	case LHS::ACTIONRESULT::ACTION_NONE:
		this->setActive(false);
		startTime = TIMEMANAGER->getWorldTime();
		break;
	}
}

void monster::authorizeName(void)
{
	int checkArray[3] = { 0, 0, 0 };
	int normalGapHP = 3500;
	int eliteGapHP = 1500;
	int normalGapAtt = 35;
	int eliteGapAtt = 15;
	int normalGapDef = 35;
	int eliteGapDef = 15;

	//피
	if (HP >= MAXHM - normalGapHP)
	{
		if (HP >= MAXHM - eliteGapHP) checkArray[0] = 2;
		else checkArray[0] = 1;
	}
	else if (HP < MINHM + normalGapHP)
	{
		if (HP < MINHM + eliteGapHP) checkArray[0] = -2;
		else checkArray[0] = -1;
	}
	//공격
	if (att >= MAXATT - normalGapAtt)
	{
		if (att >= MAXATT - eliteGapAtt) checkArray[1] = 2;
		else checkArray[1] = 1;
	}
	else if (att < MINATT + normalGapAtt)
	{
		if (att < MINATT + eliteGapAtt) checkArray[1] = -2;
		else checkArray[1] = -1;
	}
	//방어
	if (def >= MAXDEF - normalGapDef)
	{
		if (def >= MAXDEF - eliteGapDef) checkArray[2] = 2;
		else checkArray[2] = 1;
	}
	else if (def < MINDEF + normalGapDef)
	{
		if (def < MINDEF + eliteGapDef) checkArray[2] = -2;
		else checkArray[2] = -1;
	}
//=============================================================================================================

	//모든 숫자가 동일한 경우를 최우선 적으로 처리한다.
	if (checkArray[0] == 1 && checkArray[1] == 1 && checkArray[2] == 1)
	{
		prefixName = "강인한 ";
		nameColor = NAMERED;
		return;
	}
	if (checkArray[0] == 2 && checkArray[1] == 2 && checkArray[2] == 2)
	{
		HP *= 2;
		att *= 2;
		def *= 2;
		prefixName = "엘리트 ";
		nameColor = NAMEPURPLE;
		return;
	}
	if (checkArray[0] == -1 && checkArray[1] == -1 && checkArray[2] == -1)
	{
		prefixName = "주눅이든 ";
		nameColor = NAMEGRAY;
		return;
	}
	if (checkArray[0] == -2 && checkArray[1] == -2 && checkArray[2] == -2)
	{
		prefixName = "제일약한 ";
		nameColor = NAMEGRAY;
		return;
	}
	
	if (checkArray[0] == 0 && checkArray[1] == 0 && checkArray[2] == 0)
	{
		prefixName = "";
		nameColor = GREEN;
		return;
	}
//==================================================================================================

	//먼저 2를 가진 경우부터 처리한다.
	if (checkArray[0] == 2 || checkArray[1] == 2 || checkArray[2] == 2)
	{
		int count = 0;
		int index[2];
		int j = 0;
		//2가 2개 일 경우는 랜덤하게 1개의 특성에만 특수성을 부여.
		for (int i = 0; i < 3; i++)
		{
			if (checkArray[i] == 2)
			{
				count++;
				index[j++] = i;
			}
		}
		//2개일 경우 랜덤하게 1개는 0으로 만들어 버린다.
		if (count == 2)
		{
			int random = myUtil::RandomIntRange(1, 2);
			switch (random)
			{
			case 1:
				checkArray[index[0]] = 0;
				break;
			case 2:
				checkArray[index[1]] = 0;
				break;
			}
		}

		if (checkArray[0] == 2)
		{
			HP *= 2;
			prefixName = "맷집이 아주 좋은 ";
			nameColor = ORANGE;
			return;
		}
		else if (checkArray[1] == 2)
		{
			att *= 2;
			prefixName = "한방에 죽이는 ";
			nameColor = ORANGE;
			return;
		}
		else if (checkArray[2] == 2)
		{
			def *= 2;
			prefixName = "철벽같은 ";
			nameColor = ORANGE;
			return;
		}
	}
	//2의 경우 종료

//=============================================================================================
	//1의 경우 시작
	if (checkArray[0] == 1 || checkArray[1] == 1 || checkArray[2] == 1)
	{
		int count = 0;
		int index[2];
		int j = 0;
		//2가 2개 일 경우는 랜덤하게 1개의 특성에만 특수성을 부여.
		for (int i = 0; i < 3; i++)
		{
			if (checkArray[i] == 1)
			{
				count++;
				index[j++] = i;
			}
		}
		//2개일 경우 랜덤하게 1개는 0으로 만들어 버린다.
		if (count == 2)
		{
			int random = myUtil::RandomIntRange(1, 2);
			switch (random)
			{
			case 1:
				checkArray[index[0]] = 0;
				break;
			case 2:
				checkArray[index[1]] = 0;
				break;
			}
		}

		if (checkArray[0] == 1)
		{
			prefixName = "맷집이 좋은 ";
			nameColor = ORANGE;
			return;
		}
		else if (checkArray[1] == 1)
		{
			prefixName = "한방이 아픈 ";
			nameColor = ORANGE;
			return;
		}
		else if (checkArray[2] == 1)
		{
			prefixName = "튼튼한 ";
			nameColor = ORANGE;
			return;
		}
	}

	//=============================================================================================
	//-2의 경우 시작
	if (checkArray[0] == -2 || checkArray[1] == -2 || checkArray[2] == -2)
	{
		int count = 0;
		int index[2];
		int j = 0;
		//2가 2개 일 경우는 랜덤하게 1개의 특성에만 특수성을 부여.
		for (int i = 0; i < 3; i++)
		{
			if (checkArray[i] == -2)
			{
				count++;
				index[j++] = i;
			}
		}
		//2개일 경우 랜덤하게 1개는 0으로 만들어 버린다.
		if (count == 2)
		{
			int random = myUtil::RandomIntRange(1, 2);
			switch (random)
			{
			case 1:
				checkArray[index[0]] = 0;
				break;
			case 2:
				checkArray[index[1]] = 0;
				break;
			}
		}

		if (checkArray[0] == -2)
		{
			prefixName = "아주 허약한 ";
			nameColor = NAMEWHITE;
			return;
		}
		else if (checkArray[1] == -2)
		{
			prefixName = "솜털같은 ";
			nameColor = NAMEWHITE;
			return;
		}
		else if (checkArray[2] == -2)
		{
			prefixName = "누더기를 입은 ";
			nameColor = NAMEWHITE;
			return;
		}
	}

	//=============================================================================================
	//-1의 경우 시작
	if (checkArray[0] == -1 || checkArray[1] == -1 || checkArray[2] == -1)
	{
		int count = 0;
		int index[2];
		int j = 0;
		//2가 2개 일 경우는 랜덤하게 1개의 특성에만 특수성을 부여.
		for (int i = 0; i < 3; i++)
		{
			if (checkArray[i] == -1)
			{
				count++;
				index[j++] = i;
			}
		}
		//2개일 경우 랜덤하게 1개는 0으로 만들어 버린다.
		if (count == 2)
		{
			int random = myUtil::RandomIntRange(1, 2);
			switch (random)
			{
			case 1:
				checkArray[index[0]] = 0;
				break;
			case 2:
				checkArray[index[1]] = 0;
				break;
			}
		}

		if (checkArray[0] == -1)
		{
			prefixName = "허약한 ";
			nameColor = NAMEWHITE;
			return;
		}
		else if (checkArray[1] == -1)
		{
			prefixName = "힘이 없는 ";
			nameColor = NAMEWHITE;
			return;
		}
		else if (checkArray[2] == -1)
		{
			prefixName = "허름한 ";
			nameColor = NAMEWHITE;
			return;
		}
	}
}
