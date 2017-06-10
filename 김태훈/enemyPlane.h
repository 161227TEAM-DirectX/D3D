#pragma once
#include "baseObject.h"

class enemyPlane : public baseObject
{
private:
	float _nextGenTime;
	float _speed;

public:
	virtual void baseObjectEnable();			//BaseObject 가 활성화 될때 실행
	virtual void baseObjectUpdate();			//BaseObject 가 Update 때 실행
	virtual void baseObjectNoActiveUpdate();	//BaseObject 가 비활성화시 업데이트 실행

	enemyPlane() {}
	~enemyPlane() {}
};

