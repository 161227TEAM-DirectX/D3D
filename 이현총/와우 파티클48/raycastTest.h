#pragma once
#include "gameNode.h"

class raycastTest : public gameNode
{
private:
	baseObject		_object;	//������Ʈ
	vector<light*>	_lights;	//����
	bool			_isHit;		//�浹�߳�?
	Ray				_camRay;	//ī�޶� ����
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

