#pragma once
#include "gameNode.h"

class directionTestScene : public gameNode
{
private:
	LPDIRECT3DVERTEXBUFFER9 _planeVB;		//비행기 정점 버퍼
	
	float _yawAngle;							//회전각도
	float _yawSpeed;							//회전속도	
	float _moveSpeed;

	D3DXVECTOR3	_pos;						//비행기 위치
	D3DXMATRIXA16 _matPlane;				//비행기 월드행렬
	
	D3DXVECTOR3	_pos2;						//비행기 위치
	D3DXMATRIXA16 _matPlane2;				//비행기 월드행렬

	D3DXMATRIXA16 mat;	//매트릭스 확인용

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	directionTestScene() {}
	~directionTestScene() {}
};

