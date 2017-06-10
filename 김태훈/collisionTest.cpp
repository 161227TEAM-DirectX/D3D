#include "stdafx.h"
#include "collisionTest.h"

HRESULT collisionTest::init(void)
{
	//�ε��� �޽��� ������ ������� �����ϱ�
	D3DXMATRIXA16	matScale, matRotate, matCorrection;
	D3DXMatrixScaling(&matScale, 0.3f, 0.3f, 0.3f);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	matCorrection = matScale * matRotate;

	//�÷��̾� ������Ʈ
	_player.setMesh(RM_XMESH->getResource("Resources/Meshes/GunShip/Gunship.x", &matCorrection));
	_player.setActive(true);

	//���ʹ� ������Ʈ
	_enemy.setMesh(RM_XMESH->getResource("Resources/Meshes/GunShip/Gunship.x", &matCorrection));
	_enemy.setActive(true);
	//���ʹ� ������Ʈ ��ȯ��Ű��
	//_enemy._transform.SetWorldPosition(10, 5, -2); //�������
	//_enemy._transform.LookPosition(D3DXVECTOR3(0, 0, 0)); //�÷��̾ �ִ� ����

	//���ŷ(�����̵� �̲�������, �б�, ���ΰ��� �����̱�)
	//���ʹ̸� ���������� �����α�
	_enemy._transform->SetWorldPosition(20, 0, 0);
	_enemy._transform->SetScale(3, 3, 3);

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

void collisionTest::release(void)
{
	for (int i = 0; i < _lights.size(); i++)
	{
		SAFE_DELETE(_lights[i]);
	}
}

void collisionTest::update(void)
{
	//�÷��̾� �����̱�
	_player._transform->DefaultMyControl(_timeDelta);

	//�������Ŵ��� �̿��ؼ� �浹�����ϱ�
	//_isHit = PHYSICSMANAGER->isOverlap(&_player, &_enemy);
	
	//�������Ŵ��� �̿��ؼ� ���ŷ�ϱ�(���ο���ޱ�, ���ʸ� ����ޱ�)
	//_isHit = PHYSICSMANAGER->isBlocking(&_player, &_enemy, 1.0f);
	//_isHit = PHYSICSMANAGER->isBlocking(&_player, &_enemy, 0.5f);
	//_isHit = PHYSICSMANAGER->isBlocking(&_player, &_enemy, 0.0f);
}

void collisionTest::render(void)
{
	//�÷��̾�, ���ʹ� ����
	_player.render();
	_enemy.render();

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

	//�浹���� �����ֱ�
	if (_isHit)
	{
		FONTMANAGER->fontOut("���� �浹��~~~", 200, 100, 0xffff0000);
	}
	else
	{
		FONTMANAGER->fontOut("���浹��", 200, 100, 0xffffff00);
	}
}
