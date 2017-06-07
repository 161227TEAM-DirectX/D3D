#pragma once
#include "gameNode.h"

class raycastTest : public gameNode
{
private:
	baseObject		_object;	//오브젝트
	vector<light*>	_lights;	//조명
	bool			_isHit;		//충돌했냐?
	Ray				_camRay;	//카메라 레이
	D3DXVECTOR3		_hitPos;
	D3DXVECTOR3		_hitDirection;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	raycastTest() {}
	~raycastTest() {}
};

