#include "stdafx.h"
#include "enemyPlane.h"

void enemyPlane::baseObjectEnable()
{
	//��ġ����
	this->_transform->SetWorldPosition(RandomFloatRange(-15.0f, 15.0f), 0, 50);
	//�ӵ�����
	_speed = RandomFloatRange(1.0f, 5.0f);
	//�ڸ� ������ ���⼳��
	this->_transform->LookDirection(D3DXVECTOR3(0, 0, -1), D3DXVECTOR3(0, 1, 0));
}

void enemyPlane::baseObjectUpdate()
{
	//z�� 0�̸��϶�
	if (this->_transform->GetWorldPosition().z < 0.0f)
	{
		_nextGenTime = RandomFloatRange(5, 10);
		this->setActive(false);
	}
	else
	{
		//������ ������
		this->_transform->MovePositionSelf(0, 0, _speed * _timeDelta);
	}
}

void enemyPlane::baseObjectNoActiveUpdate()
{
	_nextGenTime -= _timeDelta;
	if (_nextGenTime <= 0.0f) this->setActive(true);
}
