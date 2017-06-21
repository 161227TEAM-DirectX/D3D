#pragma once
#include "iGameNode.h"
#include "xPlayerStatus.h"
#include <list>

//#include "skill00_03.h"
//#include "SK_Boss00.h"

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
	//SK_Boss00* _lightSkill;
	//dx::transform* _skillTrans;

	

	bool _isJump;
	bool _isOnBattle;
	PL_STATE _state;
	PL_STATE _prevState;

	//PL_ARMOR Equipments;
	//int _Hp;
	//int _Att;
	//int _Def;

	float _moveSpeed;

	float _damagedTime;
	float _stunnedTime;
	float _castingTime;
	
	float _baseHeight;//�������۳���
	float _jumpHeight;//��������!
	float _jumpPower;//�����Ŀ�
	float _degree;//�ﰢ�Լ� ����
	float _jumpSpeed;

	float _playSpeed;

	float nowPeriod;

	DWORD vertexNum ;
	DWORD primitives;
	DWORD maxNum;

	D3DXVECTOR3 posHand;
	D3DXVECTOR3 posEdge;

	//D3DXVECTOR3 PVs1[4];
	//D3DXVECTOR3 PVs2[4];

	deque<MYLIGHTVERTEX> _vertexDeque;

	MYLIGHTVERTEX* pVertices;

	deque<D3DXVECTOR3> _vecPosHand;
	deque<D3DXVECTOR3> _vecPosEdge;



	bool _isBladePosInit;

	int sampleMax;

private:
	baseObject* _playerObject;
	baseObject* _weaponObject;
	baseObject* _shieldObject;

	dx::transform _attackTrans;
	boundBox _attackBound;

	dx::transform* _handTrans;
	dx::transform* _edgeTrans;

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

public:

	HRESULT init();
	void update();
	void render();
	void release(void);

	//�ʱ�ȭ �κп��� ȣ��Ǿ� ���� �����͸� �����´�.
	void LoadData();

	//�÷��̾��� �����Լ��� �ƴ� ������ ���� ���� �Լ��� ���� �ؾ��� �ʿ伺�� ���� �� ����. ������ �� ���� ������. (�׸��� ������� ����..?)
	vector<baseObject*>& getRenderObject() { return _renderObjects; }

	//�÷��̾� ���� ��Ʈ�� �ִϸ��̼� �� ���º�ȭ ������.
	void moveControl();

	void rotateControl();

	void attackControl();

	void jumpControl();

	//�׽�Ʈ�� ���� �ӽ����� ��ɼ���
	void testControl();

	//�÷��̾� �ൿ ���ռ�����Ʈ
	void actionControl();

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

	//�÷��̾� �ǰ� �ش� �Լ� ȣ���Ͽ� �ǰ� �� ���� ó��
	void playerDamaged(int damage, float damagedTime = 0.0f,float delayRate = 0.0f, float StunRate = 0.0f, float StunedTime = 0.0f);

	void setHeight();

	//�ÿ���å, �������� ����� ������Ʈ���ش�.
	void itemUpdate();

	void setPlaySpeed(float speed) { _playSpeed = speed; }

	void setlinkTerrain(terrain& rand) { this->linkTerrain = &rand; }

	void setTargetMonster(monster& monster) { this->targetMonster = &monster; }

	void setMonsterRegion(vector<monster*>* monsters) { this->_monsterPool = monsters; }

	void normalAttackDamageProcessing();

	void setBladeLight();

	void updateBladeLight();

	void drawBladeLight();

	void BladePosInit();

	xPlayer() {};
	~xPlayer() {};
};
