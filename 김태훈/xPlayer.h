#pragma once
#include "gameNode.h"




/*
�÷��̾� Ű

CapsLock ī�޶�/�÷��̾� ��Ʈ�� ��ȯ
Tab	�������/�⺻��� ��ȯ
WASD �̵�
LBUTTON ����
V �ǰ� (HP -1)
SPACE ���� (HP -1)
*/


enum PL_WEAPON
{
	W_NONE = 0,
	W_BLACK_WING,
	W_END
};

enum PL_ARMOR
{
	A_NONE = 0,
	A_LEATHER,
	A_ROBE,
	A_PLATE,
	A_END
};

enum PL_STATE
{
	P_STAND = 0,
	P_RUN,
	P_MOVE,
	P_READYTOATTACK,
	P_ATTACK,
	P_READYSPELL,
	P_CASTSPELL,
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
	PL_ARMOR Equipments;
	int _Hp;
	int _Att;
	int _Def;

	float _damagedTime;
	float _stunnedTime;
	
	float _jumpHeight; //��������!

private:
	baseObject* _playerObject;
	baseObject* _weaponObject;

	boundBox _attackBound;

	vector<baseObject*> _renderObjects;

	map<string, BONE*> _EquipSocket;

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

	//�÷��̾� ��ų ó�� (�ִϸ��̼� ����.)


	//�÷��̾� �ǰ� �ش� �Լ� ȣ���Ͽ� �ǰ� �� ���� ó��
	void playerDamaged(int damage, float damagedTime = 0.0f,float delayRate = 0.0f, float StunRate = 0.0f, float StunedTime = 0.0f);


	xPlayer() {};
	~xPlayer() {};
};