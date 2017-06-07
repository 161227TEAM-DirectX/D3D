#pragma once
#include "gameNode.h"

class rotateTest_0 : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9		_vb;		//��������
	LPDIRECT3DINDEXBUFFER9		_ib;		//�ε�������
	D3DXMATRIXA16				_matWorld;	//�������

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

