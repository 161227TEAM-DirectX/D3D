#pragma once
#include "baseObject.h"

class enemyPlane : public baseObject
{
private:
	float _nextGenTime;
	float _speed;

public:
	virtual void baseObjectEnable();			//BaseObject �� Ȱ��ȭ �ɶ� ����
	virtual void baseObjectUpdate();			//BaseObject �� Update �� ����
	virtual void baseObjectNoActiveUpdate();	//BaseObject �� ��Ȱ��ȭ�� ������Ʈ ����

	enemyPlane() {}
	~enemyPlane() {}
};

