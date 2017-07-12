#include "stdafx.h"
#include "ActionSeq.h"

ActionSeq::ActionSeq()
	:Action(), CurrIdx(0), isCheck(false)
{
}


ActionSeq::~ActionSeq()
{
	for (int i = 0; i < vecAction.size(); i++)
	{
		SAFE_DELETE(vecAction[i]);
	}
	vecAction.clear();
	vector<Action*>().swap(vecAction);
}

void ActionSeq::AddAction(Action * tAction)
{
	//�����ϰ��� �ϴ� action�� ����ٸ� ����
	if (tAction == nullptr) return;

	//���Ϳ� ������ �׼��� �Է�
	vecAction.push_back(tAction);
}

int ActionSeq::Start()
{
	//���Ͱ� ����ٸ� �������� ����
	if (vecAction.empty()) return LHS::ACTIONRESULT::ACTION_FINISH;

	//�����̹Ƿ� ��ó���� 0���� ����
	CurrIdx = 0;
	//0���� ������ Start()�Լ��� ȣ��
	vecAction[CurrIdx]->Start();

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionSeq::Update()
{
	int result = -555;
	//CurrIdx���� ������ ������� ũ�ų� ���ٸ� Update�� �������� ����
	if (CurrIdx >= (int)vecAction.size())
	{
		return LHS::ACTIONRESULT::ACTION_FINISH;;
	}
	
	//CurrIdx��° �׼��� Update()�Լ��� ȣ���ض�
	result = vecAction[CurrIdx]->Update();

	switch (result)
	{
	case LHS::ACTIONRESULT::ACTION_FAIL:
		MessageBox(nullptr, "�� ����, ��ġ�� ActionSeq", "good", MB_OK);
		PostQuitMessage(0);
	case LHS::ACTIONRESULT::ACTION_ATT:
		return LHS::ACTIONRESULT::ACTION_ATT;
	case LHS::ACTIONRESULT::ACTION_MOVE:
		return LHS::ACTIONRESULT::ACTION_MOVE;
	case LHS::ACTIONRESULT::ACTION_REMOVE:
		return LHS::ACTIONRESULT::ACTION_REMOVE;
	case LHS::ACTIONRESULT::ACTION_STAND:
		return LHS::ACTIONRESULT::ACTION_STAND;
	case LHS::ACTIONRESULT::ACTION_STUN:
		return LHS::ACTIONRESULT::ACTION_STUN;
	case LHS::ACTIONRESULT::ACTION_PLAY:
		return LHS::ACTIONRESULT::ACTION_PLAY;
	case LHS::ACTIONRESULT::ACTION_FINISH:
		CurrIdx++;
		return LHS::ACTIONRESULT::ACTION_PLAY;
	}
}

void ActionSeq::Render()
{
	if (CurrIdx < vecAction.size())
	{
		vecAction[CurrIdx]->Render();
		string temp = vecAction[CurrIdx]->getOwner()->getSkinnedAnim().getAnimationSet()->GetName();
		temp + to_string(CurrIdx);
		FONTMANAGER->fontOut(temp.c_str(), 150, 150, WHITE);
	}
}