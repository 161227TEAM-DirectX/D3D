#pragma once
#include "gameNode.h"
#include "xPlayerStatus.h"

class monster;
class terrain;
/*
�÷��̾� Ű

CapsLock ī�޶�/�÷��̾� ��Ʈ�� ��ȯ
Tab	�������/�⺻��� ��ȯ
WASD �̵�
LBUTTON ����
V �ǰ� (HP -1)
SPACE ���� (HP -1)
*/


enum PL_STATE
{
	P_STAND = 0,
	P_RUN,
	P_MOVE,
	P_READYTOATTACK,
	P_ATTACK,
	P_ATTACK2,
	P_ATTACK3,
	P_ATTACK4,
	P_ATTACK5,
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

//�÷��̾�� �׻� ���������� �̱������δ� �������� �ʰ�,
//�÷��̾��� �����͸��� �̱������� �����Ѵ�.
class xPlayer :	public gameNode
{
private:
	bool _isOnBattle;
	PL_STATE _state;
	PL_STATE _prevState;
	PL_WEAPON Weapons;
	PL_SHIELD Shields;
	PL_ARMOR Equipments;
	int _Hp;
	int _Att;
	int _Def;

	float _damagedTime;
	float _stunnedTime;
	float _castingTime;
	
	float _baseHeight;//�������۳���
	float _jumpHeight;//��������!
	float _jumpPower;//�����Ŀ�
	float _degree;//�ﰢ�Լ� ����
	float _jumpSpeed;

	float _playSpeed;


private:
	baseObject* _playerObject;
	baseObject* _weaponObject;
	baseObject* _shieldObject;

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

	//�ʱ�ȭ �κп��� ȣ��Ǿ� ���� �����͸� �����´�.
	void LoadData();

	//�÷��̾��� �����Լ��� �ƴ� ������ ���� ���� �Լ��� ���� �ؾ��� �ʿ伺�� ���� �� ����. ������ �� ���� ������. (�׸��� ������� ����..?)
	vector<baseObject*>& getRenderObject() { return _renderObjects; }

	//void Attack();
	void setHeight(float height);

	//�ܺο� �������� ������Ʈ�� ���� �����Ѵ�.->�������� ������ ����... �ո������� ����.
	baseObject* getPlayerObject() { return _playerObject; }

	//�ܺ��� �Է¿� ���� �÷��̾��� �̵��� ���°�, �ִϸ��̼� ���� �����Ѵ�.
	void userPlayerControl();

	//�÷��̾��� ���¸� �����Ѵ�.
	//�� �κп��� �÷��̾��� �ִϸ��̼��� ��ȭ��Ű�� �ʾƾ� ��. -> ���� �׷���?
	//�ð��� ������ ���� Ȥ�� ��ġ���� ������ ���� �ڵ������� ��ȭ�ؾ� �ϴ� ��츦 �����Ѵ�.
	void playerStateManager();

	//���°��� ���� �÷��̾��� �ִϸ��̼��� �ٲ����Ҷ� �����Ѵ�.
	void playerAnimationManager();

	//�÷��̾� ���� ó�� (�ִϸ��̼� ����.)
	void playerAttack();

	//�÷��̾� ���� ��ų ó��(�ִϸ��̼� ����.)
	void playerSkillDirect(float castingTime);

	//�÷��̾� ���� ��ų ó��()
	void playerSkillOmni(float castingTime);

	//�÷��̾� ����
	void playerJump();

	//�÷��̾� �ǰ� �ش� �Լ� ȣ���Ͽ� �ǰ� �� ���� ó��
	void playerDamaged(int damage, float damagedTime = 0.0f,float delayRate = 0.0f, float StunRate = 0.0f, float StunedTime = 0.0f);

	void setPlaySpeed(float speed) { _playSpeed = speed; }

	void setlinkTerrain(terrain& rand) { this->linkTerrain = &rand; }

	void setTargetMonster(monster& monster) { this->targetMonster = &monster; }

	xPlayer() {};
	~xPlayer() {};
};