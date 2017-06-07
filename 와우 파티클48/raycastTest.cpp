#include "stdafx.h"
#include "raycastTest.h"

HRESULT raycastTest::init(void)
{
	//�ε��� �޽��� ������ ������� �����ϱ�
	D3DXMATRIXA16	matScale, matRotate, matCorrection;
	D3DXMatrixScaling(&matScale, 0.3f, 0.3f, 0.3f);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	matCorrection = matScale * matRotate;

	//������Ʈ
	_object.setMesh(RM_XMESH->getResource("Resources/Meshes/GunShip/Gunship.x", &matCorrection));
	_object.setActive(true);

	//����Ʈ ����
	lightDirection* light1 = new lightDirection;
	light1->_color = D3DXCOLOR(1, 1, 1, 1);
	light1->_intensity = 1.0f;

	lightPoint* light2 = new lightPoint;
	light2->_color = D3DXCOLOR(1, 0, 0, 0);
	light2->_minRange = 5.0f;
	light2->_maxRange = 10.0f;
	light2->_distancePow = 10.0f;

	lightPoint* light3 = new lightPoint;
	light3->_color = D3DXCOLOR(0, 1, 0, 0);
	light3->_minRange = 5.0f;
	light3->_maxRange = 10.0f;
	light3->_distancePow = 10.0f;
	light3->_transform->SetWorldPosition(3, 3, 0);
	light3->_intensity = 0.5f;

	_lights.push_back(light1);
	_lights.push_back(light2);
	_lights.push_back(light3);

	//�浹���� �ʱ�ȭ(�־ ��� �׸�)
	_isHit = false;

	return S_OK;
}

void raycastTest::release(void)
{
	for (int i = 0; i < _lights.size(); i++)
	{
		SAFE_DELETE(_lights[i]);
	}
}

void raycastTest::update(void)
{
	//���� �߻�
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		POINT ptMouse = GetMousePos();
		D3DXVECTOR2 screenPos(ptMouse.x, ptMouse.y);
		this->_mainCamera->computeRay(&_camRay, &screenPos);

		_isHit = PHYSICSMANAGER->isRayHitStaticMeshObject(
			&_camRay,
			&_object,
			&_hitPos,
			&_hitDirection);
	}
}

void raycastTest::render(void)
{
	//������Ʈ ����
	_object.render();

	//������ų ������� �ʱ�ȭ (������ ����Ʈ Ŭ�����ȿ� �����������)
	D3DXMATRIXA16 matLights[10];
	for (int i = 0; i < _lights.size(); i++)
	{
		matLights[i] = _lights[i]->getLightMatrix();
	}

	//���̴��� ����Ʈ ����
	xMeshStatic::_staticMeshEffect->SetMatrixArray("matLights", matLights, 10);
	xMeshStatic::_staticMeshEffect->SetInt("LightNum", _lights.size());
	//���̴��� ī�޶� ����
	xMeshStatic::setCamera(_mainCamera);

	if (_isHit)
	{
		FONTMANAGER->fontOut("���� �浹��~~~", 200, 100, 0xffff0000);
		GIZMOMANAGER->WireSphere(_hitPos, 0.5f, 0xffff0000);
	}
	else
	{
		FONTMANAGER->fontOut("���浹��", 200, 100, 0xffffff00);
	}

	//ī�޶� ����
	GIZMOMANAGER->Line(_camRay.origin, _camRay.origin + _camRay.direction * 100, 0xffffff00);
}
