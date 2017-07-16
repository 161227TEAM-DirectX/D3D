#pragma once
#include "iGameNode.h"
#include "xPlayerStatus.h"
#include "skPlayer_Heal.h"

#include <list>

//#include "skill00_03.h"
//#include "SK_Boss00.h"

class monster;
class terrain;
class damageText;
/*
�÷��̾� Ű

CapsLock ī�޶�/�÷��̾� ��Ʈ�� ��ȯ
Tab	�������/�⺻��� ��ȯ
WASD �̵�
LBUTTON ����
V �ǰ� (HP -1)
SPACE ���� (HP -1)
*/

enum SkillType
{
	SKILL_NONE = 0,
	SKILL_HEAL,
	SKILL_MAGICMISSILE,
	SKILL_LIGHTNING,
	SKILL_SKYSWD,
	SKILL_FIRE,
	SKILL_SHIELD,
	SKILL_METEOR,
	SKILL_ROAR,
	SKILL_WHIRLWIND,
	SKILL_SLAM,
	SKILL_END
};

typedef struct tagLightVertex
{
	D3DXVECTOR3 pos;			//������ ��ġ

	D3DXVECTOR2	uv;				//������ UV��ǥ (0.0f ~ 1.0f)
								//D3DCOLOR uv;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
	//���� ������ ������ ��Ÿ���� �÷��� �����
}MYLIGHTVERTEX, *LPMYLIGHTVERTEX;

struct tagIndex
{
	DWORD x;
	DWORD y;
	DWORD z;
	DWORD w;
};


//�÷��̾�� �׻� ���������� �̱������δ� �������� �ʰ�,
//�÷��̾��� �����͸��� �̱������� �����Ѵ�.
class xPlayer :	public iGameNode
{
private:
	bool _isJump;
	bool _isOnBattle;
	bool _isMount;
	//float _houlse
	float _sitHeight;

	PL_STATE _state;
	PL_STATE _prevState;
	SkillType _nowSelectedSkill;

	PL_WEAPON _weaponCurrent;
	PL_SHIELD _shieldCurrent;
	
	float _moveSpeed;
	float _damagedTime;
	float _stunnedTime;
	float _castingTime;
	
	float _baseHeight;//�������۳���
	float _jumpHeight;//��������!
	float _jumpPower;//�����Ŀ�
	float _degree;//2�������Ŀ� ���� ����
	float _jumpSpeed;

	float _playSpeed;

	float nowPeriod;

	float _BladeLength;

	DWORD vertexNum ;
	DWORD primitives;
	DWORD maxNum;

	D3DXVECTOR3 posHand;
	D3DXVECTOR3 posEdge;

	deque<MYLIGHTVERTEX> _vertexDeque;

	MYLIGHTVERTEX* pVertices;

	deque<D3DXVECTOR3> _vecPosHand;
	deque<D3DXVECTOR3> _vecPosEdge;

	bool _isBladePosInit;

	int sampleMax;

	bool _isInvincible;

private:
	baseObject* _playerObject;
	baseObject* _mountObject;
	baseObject* _weaponObject;
	baseObject* _shieldObject;
	baseObject* _shoulderR;
	baseObject* _shoulderL;

	

	dx::transform _attackTrans;
	boundBox _attackBound;

	dx::transform* _handTrans;
	dx::transform* _edgeTrans;

	dx::transform* _sitPos;//������ġ!

	vector<baseObject*> _renderObjects;
	vector<monster*>* _monsterPool;


	map<string, BONE*> _EquipSocket;

	terrain*			linkTerrain;
	monster*			targetMonster;


	//������ ��ġ�� �����ϴ� ť
	D3DXVECTOR3 _edgePos[21];
	D3DXVECTOR3 _handPos[21];

	D3DXVECTOR3 _HStart;
	D3DXVECTOR3 _HEnd;

	D3DXVECTOR3 _EStart;
	D3DXVECTOR3 _Eend;


	
	//skinnedAnimation* CloneSkinned;

	dx::transform* myTrans;

	D3DXTRACK_DESC ORIG_DESC;

	D3DXTRACK_DESC O_DESC;


	LPDIRECT3DVERTEXBUFFER9 _myVertexbuffer;	//���� ����
	LPDIRECT3DINDEXBUFFER9 _myIndexBuffer;		//�ε��� ����
									//�ε��� �ؽ���(png, jpg, bmp, tga, dds) => �ؽ�������(dds : ���̷�Ʈ ���� �ؽ��� ����)
	LPDIRECT3DTEXTURE9 _texture;	//�ε��� �ؽ���

	DWORD* idx;

	damageText* _dmText;

	//baseObject* _forwardGate;
	//baseObject* _backGate;

public:

	HRESULT init();
	void update();
	void render();//�÷��̾� ������ ������ ������Ʈ ���� �� ���� ȣ���������.
	void release(void);

	//void setFGate(baseObject* FG) { _forwardGate = FG; }
	//void setBGate(baseObject* BG) { _backGate = BG; }

	//�ʱ�ȭ �κп��� ȣ��Ǿ� ���� �����͸� �����´�.
	void LoadData();

	//�÷��̾��� �����Լ��� �ƴ� ������ ���� ���� �Լ��� ���� �ؾ��� �ʿ伺�� ���� �� ����. ������ �� ���� ������. (�׸��� ������� ����..?)
	vector<baseObject*>& getRenderObject() { return _renderObjects; }

	//�÷��̾� ���� ��Ʈ�� �ִϸ��̼� �� ���º�ȭ ������.
	void moveControl(dx::transform* trans);

	void rotateControl(dx::transform* trans);

	void attackControl();

	void jumpControl();

	void skillControl();

	void summonControl();

	//�÷��̾� �ൿ ���ռ�����Ʈ ��������
	void actionControl();

	//�ܺο� �������� ������Ʈ�� ���� �����Ѵ�.->�������� ������ ����... �ո������� ����.
	baseObject* getPlayerObject() { return _playerObject; }

	//�ܺ��� �Է¿� ���� �÷��̾��� �̵��� ���°�, �ִϸ��̼� ���� �����Ѵ�.
	void PlayerInputControl();

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

	//�÷��̾� �ǰ� �ش� �Լ� ȣ���Ͽ� �ǰ� �� ���� ó��
	void playerDamaged(int damage, float damagedTime = 0.0f,float delayRate = 0.0f, float StunRate = 0.0f, float StunedTime = 0.0f);

	void setHeight(dx::transform* trans);

	void setPlaySpeed(float speed) { _playSpeed = speed; }

	void setTargetMonster(monster& monster) { this->targetMonster = &monster; }

	void normalAttackDamageProcessing();

	void setBladeLight();

	void drawBladeLight();

	void BladePosInit();

	void skilltrigger();

	void useNowSkill();

	void skillProcesser();
	
	void updateEquipments();

	//=========================================================================================================//
	//											������ ȣ�����ִ� ģ����
	//=========================================================================================================//

	//�˱������ �����κп��� ������Ʈ �ؾ���.
	void out_updateBladeLight();

	//�������� ����� ������Ʈ���ش�.
	void out_ItemUpdate();

	//���콺�� �̿��� Ÿ�� ����
	void out_setTargetByMouse(camera* mainCamera);

	//���� ����
	void out_setlinkTerrain(terrain& land) { this->linkTerrain = &land; }

	//���� ���� ����
	void out_setMonsterRegion(vector<monster*>* monsters) { this->_monsterPool = monsters; }
	//-----------------------------------------����Ʈ ����--------------------------------------------------------//
	void initMount();

	void summonMount();

	void unSummonMount();

	xPlayer(): _monsterPool(nullptr), linkTerrain(nullptr) {};
	~xPlayer() {};
};