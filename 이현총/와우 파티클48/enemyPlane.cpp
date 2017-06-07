#include "stdafx.h"
#include "enemyPlane.h"

void enemyPlane::baseObjectEnable()
{
	//위치랜덤
	this->_transform->SetWorldPosition(RandomFloatRange(-15.0f, 15.0f), 0, 50);
	//속도랜덤
	_speed = RandomFloatRange(1.0f, 5.0f);
	//뒤를 보도록 방향설정
	this->_transform->LookDirection(D3DXVECTOR3(0, 0, -1), D3DXVECTOR3(0, 1, 0));
}

void enemyPlane::baseObjectUpdate()
{
	//z축 0미만일때
	if (this->_transform->GetWorldPosition().z < 0.0f)
	{
		_nextGenTime = RandomFloatRange(5, 10);
		this->setActive(false);
	}
	else
	{
		//앞으로 앞으로
		this->_transform->MovePositionSelf(0, 0, _speed * _timeDelta);
	}
}

void enemyPlane::baseObjectNoActiveUpdate()
{
	_nextGenTime -= _timeDelta;
	if (_nextGenTime <= 0.0f) this->setActive(true);
}
