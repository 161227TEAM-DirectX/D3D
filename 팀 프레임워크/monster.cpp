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
	CurrAction = ACMANAGER->getAction("�Ϲݴ��", *this);

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
	//������ HP�� �������� ���� ���·� ����
	//if (HP < 0 && result != LHS::ACTIONRESULT::ACTION_NONE) result = LHS::ACTIONRESULT::ACTION_DIE;
	// �� �׼��� update �Լ��� ���� �Ŀ� ���°��� �Ѱܿ´�.
	// �� ���°��� ���� ���Ͱ� �ؾ� �� �ൿ�� ���ϸ� �ȴ�.
	switch (result)
	{
		//���� ���� �׼��� ����Ǿ����� �˷��ö� -> standing���·� ���ư���.
	case LHS::ACTIONRESULT::ACTION_FINISH:
		NextAction = ACMANAGER->getAction("�Ϲݴ��", *this);
		break;
	case LHS::ACTIONRESULT::ACTION_REFINISH:
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

	//��
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
	//����
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
	//���
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

	//��� ���ڰ� ������ ��츦 �ֿ켱 ������ ó���Ѵ�.
	if (checkArray[0] == 1 && checkArray[1] == 1 && checkArray[2] == 1)
	{
		prefixName = "������ ";
		nameColor = NAMERED;
		return;
	}
	if (checkArray[0] == 2 && checkArray[1] == 2 && checkArray[2] == 2)
	{
		HP *= 2;
		att *= 2;
		def *= 2;
		prefixName = "����Ʈ ";
		nameColor = NAMEPURPLE;
		return;
	}
	if (checkArray[0] == -1 && checkArray[1] == -1 && checkArray[2] == -1)
	{
		prefixName = "�ִ��̵� ";
		nameColor = NAMEGRAY;
		return;
	}
	if (checkArray[0] == -2 && checkArray[1] == -2 && checkArray[2] == -2)
	{
		prefixName = "���Ͼ��� ";
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

	//���� 2�� ���� ������ ó���Ѵ�.
	if (checkArray[0] == 2 || checkArray[1] == 2 || checkArray[2] == 2)
	{
		int count = 0;
		int index[2];
		int j = 0;
		//2�� 2�� �� ���� �����ϰ� 1���� Ư������ Ư������ �ο�.
		for (int i = 0; i < 3; i++)
		{
			if (checkArray[i] == 2)
			{
				count++;
				index[j++] = i;
			}
		}
		//2���� ��� �����ϰ� 1���� 0���� ����� ������.
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
			prefixName = "������ ���� ���� ";
			nameColor = ORANGE;
			return;
		}
		else if (checkArray[1] == 2)
		{
			att *= 2;
			prefixName = "�ѹ濡 ���̴� ";
			nameColor = ORANGE;
			return;
		}
		else if (checkArray[2] == 2)
		{
			def *= 2;
			prefixName = "ö������ ";
			nameColor = ORANGE;
			return;
		}
	}
	//2�� ��� ����

//=============================================================================================
	//1�� ��� ����
	if (checkArray[0] == 1 || checkArray[1] == 1 || checkArray[2] == 1)
	{
		int count = 0;
		int index[2];
		int j = 0;
		//2�� 2�� �� ���� �����ϰ� 1���� Ư������ Ư������ �ο�.
		for (int i = 0; i < 3; i++)
		{
			if (checkArray[i] == 1)
			{
				count++;
				index[j++] = i;
			}
		}
		//2���� ��� �����ϰ� 1���� 0���� ����� ������.
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
			prefixName = "������ ���� ";
			nameColor = ORANGE;
			return;
		}
		else if (checkArray[1] == 1)
		{
			prefixName = "�ѹ��� ���� ";
			nameColor = ORANGE;
			return;
		}
		else if (checkArray[2] == 1)
		{
			prefixName = "ưư�� ";
			nameColor = ORANGE;
			return;
		}
	}

	//=============================================================================================
	//-2�� ��� ����
	if (checkArray[0] == -2 || checkArray[1] == -2 || checkArray[2] == -2)
	{
		int count = 0;
		int index[2];
		int j = 0;
		//2�� 2�� �� ���� �����ϰ� 1���� Ư������ Ư������ �ο�.
		for (int i = 0; i < 3; i++)
		{
			if (checkArray[i] == -2)
			{
				count++;
				index[j++] = i;
			}
		}
		//2���� ��� �����ϰ� 1���� 0���� ����� ������.
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
			prefixName = "���� ����� ";
			nameColor = NAMEWHITE;
			return;
		}
		else if (checkArray[1] == -2)
		{
			prefixName = "���а��� ";
			nameColor = NAMEWHITE;
			return;
		}
		else if (checkArray[2] == -2)
		{
			prefixName = "�����⸦ ���� ";
			nameColor = NAMEWHITE;
			return;
		}
	}

	//=============================================================================================
	//-1�� ��� ����
	if (checkArray[0] == -1 || checkArray[1] == -1 || checkArray[2] == -1)
	{
		int count = 0;
		int index[2];
		int j = 0;
		//2�� 2�� �� ���� �����ϰ� 1���� Ư������ Ư������ �ο�.
		for (int i = 0; i < 3; i++)
		{
			if (checkArray[i] == -1)
			{
				count++;
				index[j++] = i;
			}
		}
		//2���� ��� �����ϰ� 1���� 0���� ����� ������.
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
			prefixName = "����� ";
			nameColor = NAMEWHITE;
			return;
		}
		else if (checkArray[1] == -1)
		{
			prefixName = "���� ���� ";
			nameColor = NAMEWHITE;
			return;
		}
		else if (checkArray[2] == -1)
		{
			prefixName = "�㸧�� ";
			nameColor = NAMEWHITE;
			return;
		}
	}
}
