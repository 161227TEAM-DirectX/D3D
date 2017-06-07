#pragma once
#include "gameNode.h"

class rotateTest_1 : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9		_vb;		//정점버퍼
	LPDIRECT3DINDEXBUFFER9		_ib;		//인덱스버퍼
	D3DXMATRIXA16				_matWorld;	//월드행렬

	//사물의 축 (모든 축은 방향에 따라 무조건 직교한다)
	//방향벡터
	D3DXVECTOR3	_forward;	//사물의 정면 벡터
	D3DXVECTOR3 _right;		//사물의 오른쪽 벡터
	D3DXVECTOR3 _up;		//사물의 상방벡터
	//위치벡터
	D3DXVECTOR3 _pos;		//사물의 위치
	//바라보는 위치
	D3DXVECTOR3 _targetPos;	//타겟 위치

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void CreateCube(void);

	rotateTest_1() {}
	~rotateTest_1() {}
};

