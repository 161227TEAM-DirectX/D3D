#pragma once

class Action;
class baseObject;
class terrain;
class xPlayer;

class iActionDelegate
{
public:
	//액션이 종료 될때 호출되는 함수 - 상속받는 클래스가 무조건 정의해야 한다.
	virtual void OnActionFinish(Action* pSender) = 0;
	virtual void OnActionFinish(Action* pSender, bool isCollision) = 0;
};

class Action
{
protected:
	baseObject*				owner;				// 액션의 주체(baseObject)
	iActionDelegate*		deleGate;			// 액션 종료시 호출될 함수를 위한 클래스변수
	terrain*				rand;				// 액션 및 이동 중 높이값을 가져오기 위한 변수
	vector<baseObject*>*	object;				// 오브젝트 정보, 장애물
	xPlayer*				enemy;				// 플레이어 정보
	baseObject*				playerObject;		// 플레이어 오브젝트 정보

	float _oldTimeDelta;
	const float Gap;
	const float LENGTHGAP;
	const float PLAYERDISTANCE;
public:
	Action();
	virtual ~Action();
	//움직일 개체 겟터
	inline baseObject* getOwner(void) { return owner; }
	//움직일 개체 셋터
	inline void setOwner(baseObject& tempOwner) { owner = &tempOwner; }

	//델리게이트?? 설정
	inline iActionDelegate* getDelegate(void) { return deleGate; }
	inline void setDelegate(iActionDelegate* tempDele) { deleGate = tempDele; }

	inline void setObject(vector<baseObject*>& temp) { this->object = &temp; }

	inline void setRand(terrain& temp) { this->rand = &temp; }

	inline void setEnemy(xPlayer& temp) 
	{ 
		this->enemy = &temp;
	}

	inline void setPlayerObject(baseObject& temp) { this->playerObject = &temp; }

	//액션의 시작을 정의하는 함수 - 순수가상함수
	virtual int Start() = 0;
	//액션을 실행하는 함수 - 순수가상함수
	virtual int Update() = 0;
	//액션중에 랜더가 필요하면 실행하는 함수.
	virtual void Render() {}
};

