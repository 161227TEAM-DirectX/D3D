#include "stdafx.h"
#include "cMinimapTest2.h"


cMinimapTest2::cMinimapTest2()
{
}


cMinimapTest2::~cMinimapTest2()
{
}

HRESULT cMinimapTest2::init()
{
	//�ε��� �޽��� ���� ������� �����ϱ�
	D3DXMATRIXA16	matScale, matRotate, matCorrection;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	matCorrection = matScale * matRotate;

	//�÷��̾� ������Ʈ �ʱ�ȭ
	_player.setMesh(RM_XMESH->getResource("ResourceUI/test/GunShip/gunship.x", &matCorrection));
	_player.setActive(true);


	//���� ����
	//���⼺ ����
	lightDirection* light1 = new lightDirection;
	light1->_color = D3DXCOLOR(1, 1, 1, 0);
	light1->_intensity = 1.0f;
	//����Ʈ ����
	lightPoint* light2 = new lightPoint;
	light2->_color = D3DXCOLOR(1, 0, 0, 0);
	light2->_minRange = 5.0f;
	light2->_maxRange = 10.0f;
	light2->_distancePow = 10.0f;
	//����Ʈ ����
	lightPoint* light3 = new lightPoint;
	light3->_color = D3DXCOLOR(0, 1, 0, 0);
	light3->_minRange = 5.0f;
	light3->_maxRange = 10.0f;
	light3->_distancePow = 10.0f;
	light3->_transform->SetWorldPosition(3, 3, 0);
	light3->_intensity = 0.5f;

	//���� ���Ϳ� ���
	_lights.push_back(light1);
	_lights.push_back(light2);
	_lights.push_back(light3);

	//�浹���� �ʱ�ȭ
	_isHit = false;

	return S_OK;
}

void cMinimapTest2::release()
{
}

void cMinimapTest2::update()
{
	_mainCamera.updateBase();

	_player._transform->DefaultMyControl(_timeDelta);

	//�����Ŵ����� �̿��ؼ� �浹�����ϱ�
	//_isHit = PHYSICSMANAGER->isOverlap(&_player, &_enemy);

	//�����Ŵ����� �̿��ؼ� ���ŷ�ϱ�(���ο���ޱ�, ���ʸ� ����ޱ�)
	//2���� �ٿ�� ���Ǿ���� �⵿�ϰ� ��ġ�� �ʰ� �Ѵ�.
	//moveFactor 0.0f ~ 1.0f
	//moveFactor �� 0 �ϼ��� ��Ĩ�� ���� B �� �����δ�.
	//moveFactor �� 0.5 �̸� ��Ĩ�� ���� A �� B �� �Ȱ��������� �����δ�.
	//moveFactor �� 1 �ϼ��� ��Ĩ�� ���� A �� �����δ�.

	//_isHit = PHYSICSMANAGER->isBlocking(&_player, &_enemy, 0.0f);
	//_isHit = PHYSICSMANAGER->isBlocking(&_player, &_enemy, 0.5f);
	//_isHit = PHYSICSMANAGER->isBlocking(&_player, &_enemy, 1.0f);
}

void cMinimapTest2::render()
{
	//�÷��̾� ����
	_player.render();
	//���ʹ� ����
	//_enemy.render();

	//������ų ���� �ʱ�ȭ(������ ����Ʈ Ŭ�����ȿ� ������� ����)
	//�����ų lightMatrix
	D3DXMATRIXA16 matLights[10];
	for (int i = 0; i < _lights.size(); i++)
	{
		matLights[i] = _lights[i]->getLightMatrix();
	}
	//���̴��� ����Ʈ ����
	xMeshStatic::_staticMeshEffect->SetMatrixArray("matLights", matLights, 10);
	xMeshStatic::_staticMeshEffect->SetInt("LightNum", _lights.size());
	//xMeshStatic::setCamera => ���̴��ȿ� ���������ǰ�, ������ġ�� ��������� �Ѵ�
	xMeshStatic::setCamera(&_mainCamera);

	////�浹���� �����ֱ�
	//if (_isHit)
	//{
	//	FONTMANAGER->fontOut("���� �浹��", 100, 100, 0xffff0000);
	//}
	//else
	//{
	//	FONTMANAGER->fontOut("�浹����", 200, 100, 0xffffff00);
	//}
}
