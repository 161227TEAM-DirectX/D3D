#include "stdafx.h"
#include "gameObject.h"

HRESULT gameObject::init(void)
{
	//월드행렬 초기화
	D3DXMatrixIdentity(&_matWorld);

	_vLocalTranslation = D3DXVECTOR3(0, 0, 0);
	_angle = 0.0f;
	_angleSpeed = 0.0f;

	return S_OK;
}

void gameObject::release(void)
{
}

void gameObject::update(D3DXMATRIXA16 * parent)
{
	_angle += _angleSpeed;

	if (_angle > D3DX_PI / 4.0f)
	{
		_angle = D3DX_PI / 4.0f;
		_angleSpeed *= -1;
	}

	if (_angle < -D3DX_PI / 4.0f)
	{
		_angle = -D3DX_PI / 4.0f;
		_angleSpeed *= -1;
	}

	D3DXMATRIXA16 matT, matR;

	D3DXMatrixRotationX(&matR, _angle);
	D3DXMatrixTranslation(&matT,
		_vLocalTranslation.x,
		_vLocalTranslation.y,
		_vLocalTranslation.z);

	_matWorld = matR * matT;

	if (parent) _matWorld *= *parent;

	if (_child)
	{
		((gameObject*)_child)->update(&_matWorld);
	}
	if (_sibling)
	{
		((gameObject*)_sibling)->update(parent);
	}
}

void gameObject::render(void)
{
	if (_child)
	{
		((gameObject*)_child)->render();
	}
	if (_sibling)
	{
		((gameObject*)_sibling)->render();
	}
}

