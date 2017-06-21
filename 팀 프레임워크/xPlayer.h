#pragma once
#include "iGameNode.h"
#include "xPlayerStatus.h"
#include <list>

//#include "skill00_03.h"
//#include "SK_Boss00.h"

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

typedef struct tagLightVertex
{
	D3DXVECTOR3 pos;			//정점의 위치

	D3DXVECTOR2	uv;				//정점의 UV좌표 (0.0f ~ 1.0f)
								//D3DCOLOR uv;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
	//현재 정점의 정보를 나타내는 플래그 상수값
}MYLIGHTVERTEX, *LPMYLIGHTVERTEX;

struct tagIndex
{
	DWORD x;
	DWORD y;
	DWORD z;
	DWORD w;
};

//플레이어는 항상 존재하지만 싱글톤으로는 구현하지 않고,
//플레이어의 데이터만을 싱글톤으로 구현한다.
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
	
	float _baseHeight;//점프시작높이
	float _jumpHeight;//점프높이!
	float _jumpPower;//점프파워
	float _degree;//삼각함수 높이
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


	//정점의 위치를 저장하는 큐
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


	LPDIRECT3DVERTEXBUFFER9 _myVertexbuffer;	//정점 버퍼
	LPDIRECT3DINDEXBUFFER9 _myIndexBuffer;		//인덱스 버퍼
									//로딩될 텍스쳐(png, jpg, bmp, tga, dds) => 텍스쳐포맷(dds : 다이렉트 전용 텍스쳐 포맷)
	LPDIRECT3DTEXTURE9 _texture;	//로딩될 텍스쳐

	DWORD* idx;

public:

	HRESULT init();
	void update();
	void render();
	void release(void);

	//초기화 부분에서 호출되어 이전 데이터를 가져온다.
	void LoadData();

	//플레이어의 렌더함수가 아닌 씬에서 직접 렌더 함수를 관리 해야할 필요성이 있을 수 있음. 쉐도우 맵 등의 이유로. (그림자 연산등의 문제..?)
	vector<baseObject*>& getRenderObject() { return _renderObjects; }

	//플레이어 무브 컨트롤 애니메이션 및 상태변화 미포함.
	void moveControl();

	void rotateControl();

	void attackControl();

	void jumpControl();

	//테스트를 위한 임시적인 기능설정
	void testControl();

	//플레이어 행동 종합선물세트
	void actionControl();

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

	//플레이어 피격 해당 함수 호출하여 피격 및 스턴 처리
	void playerDamaged(int damage, float damagedTime = 0.0f,float delayRate = 0.0f, float StunRate = 0.0f, float StunedTime = 0.0f);

	void setHeight();

	//궁여지책, 아이템의 행렬을 업데이트해준다.
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
