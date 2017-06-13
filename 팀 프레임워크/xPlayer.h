#pragma once
#include "gameNode.h"
#include "xPlayerStatus.h"

class monster;
class terrain;
/*
플레이어 키

CapsLock 카메라/플레이어 컨트롤 전환
Tab	전투대기/기본대기 전환
WASD 이동
LBUTTON 공격
V 피격 (HP -1)
SPACE 스턴 (HP -1)
*/


enum PL_STATE
{
	P_STAND = 0,
	P_RUN,
	P_MOVE,
	P_READYTOATTACK,
	P_ATTACK,
	P_READYSPELL,
	P_CASTSPELL,
	P_READYOMNI,
	P_CASTOMNI,
	P_JUMPUP,
	P_JUMP,
	P_JUMPDOWN,
	P_STUN,
	P_DEATH,
	P_MOUNT,
	P_WALKBACK,
	P_DAMAGED,
	P_END
};

//플레이어는 항상 존재하지만 싱글톤으로는 구현하지 않고,
//플레이어의 데이터만을 싱글톤으로 구현한다.
class xPlayer :	public gameNode
{
private:
	bool _isOnBattle;
	PL_STATE _state;
	PL_STATE _prevState;
	PL_WEAPON Weapons;
	PL_ARMOR Equipments;
	int _Hp;
	int _Att;
	int _Def;

	float _damagedTime;
	float _stunnedTime;
	float _castingTime;
	
<<<<<<< HEAD
	float _baseHeight;//점프시작높이
	float _jumpHeight;//점프높이!
	float _jumpPower;//점프파워
	float _degree;//삼각함수 높이
	float _jumpSpeed;

	float _playSpeed;


=======
	float _jumpHeight; //점프높이!

	float _playSpeed;

>>>>>>> d6e334270052364b68749c2834fb5bad8b2deb60
private:
	baseObject* _playerObject;
	baseObject* _weaponObject;

	dx::transform _attackTrans;
	boundBox _attackBound;

	vector<baseObject*> _renderObjects;

	map<string, BONE*> _EquipSocket;

	terrain*			linkTerrain;
	monster*			targetMonster;

public:
	HRESULT init();
	void update();
	void render();
	void release(void);

	//초기화 부분에서 호출되어 이전 데이터를 가져온다.
	void LoadData();

	//플레이어의 렌더함수가 아닌 씬에서 직접 렌더 함수를 관리 해야할 필요성이 있을 수 있음. 쉐도우 맵 등의 이유로. (그림자 연산등의 문제..?)
	vector<baseObject*>& getRenderObject() { return _renderObjects; }

	//void Attack();
	void setHeight(float height);

	//외부에 렌더링할 오브젝트의 값을 전달한다.->구조상의 문제가 있음... 합리적이지 못함.
	baseObject* getPlayerObject() { return _playerObject; }

	//외부의 입력에 대해 플레이어의 이동과 상태값, 애니메이션 등을 제어한다.
	void userPlayerControl();

	//플레이어의 상태를 관리한다.
	//이 부분에서 플레이어의 애니메이션을 변화시키지 않아야 함. -> 과연 그럴까?
	//시간이 지남에 따라 혹은 수치값의 변동에 따라 자동적으로 변화해야 하는 경우를 지정한다.
	void playerStateManager();

	//상태값에 따라 플레이어의 애니메이션이 바뀌어야할때 지정한다.
	void playerAnimationManager();

	//플레이어 공격 처리 (애니메이션 포함.)
	void playerAttack();

	//플레이어 직선 스킬 처리(애니메이션 포함.)
	void playerSkillDirect(float castingTime);

	//플레이어 원형 스킬 처리()
	void playerSkillOmni(float castingTime);

	//플레이어 점프
	void playerJump();

	//플레이어 피격 해당 함수 호출하여 피격 및 스턴 처리
	void playerDamaged(int damage, float damagedTime = 0.0f,float delayRate = 0.0f, float StunRate = 0.0f, float StunedTime = 0.0f);

	void setPlaySpeed(float speed) { _playSpeed = speed; }

	void setlinkTerrain(terrain& rand) { this->linkTerrain = &rand; }

	void setTargetMonster(monster& monster) { this->targetMonster = &monster; }

	xPlayer() {};
	~xPlayer() {};
};