#include "stdafx.h"
#include "ActionSeq.h"
#include "monster.h"

ActionSeq::ActionSeq()
	:Action(), CurrIdx(0), isCheck(false)
{
}


ActionSeq::~ActionSeq()
{
	for (int i = 0; i < vecAction.size(); i++)
	{
		delete vecAction[i];
	}
	vecAction.clear();
	vector<Action*>().swap(vecAction);
}

void ActionSeq::AddAction(Action * tAction)
{
	//저장하고자 하는 action이 비었다면 종료
	if (tAction == nullptr) return;

	//벡터에 생성된 액션을 입력
	vecAction.push_back(tAction);
}

int ActionSeq::Start()
{
	//벡터가 비었다면 실행하지 마라
	if (vecAction.empty()) return LHS::ACTIONRESULT::ACTION_FINISH;

	//시작이므로 맨처음인 0번을 실행
	CurrIdx = 0;
	//0번의 인자의 Start()함수를 호출
	vecAction[CurrIdx]->Start();

	return LHS::ACTIONRESULT::ACTION_PLAY;
}

int ActionSeq::Update()
{
	int result = -555;
	//CurrIdx값이 벡터의 사이즈보다 크거나 같다면 Update를 실행하지 마라
	if (CurrIdx >= (int)vecAction.size())
	{
		monster* temp = dynamic_cast<monster*>(vecAction[CurrIdx - 1]->getOwner());
		float tempDistance = 0;
		tempDistance = D3DXVec3Length(&(temp->getRegenPosition() - temp->_transform->GetWorldPosition()));
		
		if (tempDistance - Gap < PLAYERDISTANCE) return LHS::ACTIONRESULT::ACTION_MOVE;
		else return LHS::ACTIONRESULT::ACTION_FINISH;
	}
	
	//CurrIdx번째 액션의 Update()함수를 호출해라
	result = vecAction[CurrIdx]->Update();

	switch (result)
	{
	case LHS::ACTIONRESULT::ACTION_FAIL:
		MessageBox(nullptr, "앗 오류, 위치는 ActionSeq", "good", MB_OK);
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
	case LHS::ACTIONRESULT::ACTION_REFINISH:
		if (CurrIdx + 1 < vecAction.size())
		{
			CurrIdx++;
			return LHS::ACTIONRESULT::ACTION_PLAY;
		}
		else return LHS::ACTIONRESULT::ACTION_REFINISH;
		
	}
}

void ActionSeq::Render()
{
	//if (CurrIdx < vecAction.size())
	//{
	//	vecAction[CurrIdx]->Render();
	//	string temp = vecAction[CurrIdx]->getOwner()->getSkinnedAnim().getAnimationSet()->GetName();
	//	temp + to_string(CurrIdx);
	//	FONTMANAGER->fontOut(temp.c_str(), 150, 150, WHITE);
	//}
}