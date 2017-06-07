#pragma once
#include "treeNode.h"

class gameObject : public treeNode
{
protected:
	D3DXMATRIXA16	_matWorld;
	D3DXVECTOR3		_vLocalTranslation;
	float			_angle;
	float			_angleSpeed;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(D3DXMATRIXA16* parent = NULL);
	virtual void render(void);

	//╪бем
	virtual void setLocalTranslation(D3DXVECTOR3& vLocal) { _vLocalTranslation = vLocal; }
	virtual void setAngleSpeed(float angleSpeed) { _angleSpeed = angleSpeed; }

	gameObject() {}
	virtual ~gameObject() {}
};

