#include "stdafx.h"
#include "characterController.h"

HRESULT characterController::init(void)
{
	//월드행렬 초기화
	D3DXMatrixIdentity(&_matWorld);

	_vCubePos = D3DXVECTOR3(0, 0, 0);
	_vDir = D3DXVECTOR3(0, 0, 1);
	_angle = 0.0f;
	_speed = 0.1f;

	return S_OK;
}

void characterController::release(void)
{
}

void characterController::update(void)
{
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_vCubePos = _vCubePos + (_vDir * _speed);
	}

	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_vCubePos = _vCubePos - (_vDir * _speed);
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_angle -= 0.1f;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_angle += 0.1f;
	}

	D3DXMATRIXA16 matT, matR;
	D3DXMatrixTranslation(&matT, _vCubePos.x, _vCubePos.y, _vCubePos.z);
	D3DXMatrixRotationY(&matR, _angle);

	_vDir = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&_vDir, &_vDir, &matR);

	_matWorld = matR * matT;
}

void characterController::render(void)
{
}
