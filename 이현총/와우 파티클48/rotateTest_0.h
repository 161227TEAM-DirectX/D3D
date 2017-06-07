#pragma once
#include "gameNode.h"

class rotateTest_0 : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9		_vb;		//정점버퍼
	LPDIRECT3DINDEXBUFFER9		_ib;		//인덱스버퍼
	D3DXMATRIXA16				_matWorld;	//월드행렬

	float _xAngle;	//Pitch
	float _yAngle;	//Yaw
	float _zAngle;	//Roll

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void CreateCube(void);

	rotateTest_0() {}
	~rotateTest_0() {}
};

