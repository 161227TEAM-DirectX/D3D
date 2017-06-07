#include "stdafx.h"
#include "terrainPickingTest.h"

HRESULT terrainPickingTest::init(void)
{
	_terrain = new terrain;
	
	_terrain->init(
		"Resources/Textures/Height_map1024.jpg",
		//"Resources/Textures/MyHeight128.bmp",
		//"Resources/Textures/MyHeight512.bmp",
		//"Resources/Textures/Sheep_Height.bmp",
		"Resources/Textures/Sheep_terrain1.jpg",
		"Resources/Textures/Sheep_terrain2.jpg",
		"Resources/Textures/Sheep_terrain3.jpg",
		"Resources/Textures/Sheep_terrain4.jpg",
		"Resources/Textures/Sheep_Splat.bmp",
		1.0f,
		250.0f,
		10,
		50);
	

	_trans = new transform;
	_dirLight = new lightDirection;
	_hitPos = D3DXVECTOR3(0, 5, 0);

	return S_OK;
}

void terrainPickingTest::release(void)
{
	_terrain->release();
	SAFE_DELETE(_terrain);
	SAFE_DELETE(_trans);
	SAFE_DELETE(_dirLight);
}

void terrainPickingTest::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		Ray ray;
		POINT ptMousePos = GetMousePos();
		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		_mainCamera->computeRay(&ray, &screenPos);

		//Terrain �̶� Rayüũ
		_terrain->isIntersectRay(&_hitPos, &ray);
	}

	//�Ÿ��� ���Ѵ�.
	D3DXVECTOR3 dirToTarget = _hitPos - _trans->GetWorldPosition();
	float dist = D3DXVec3Length(&dirToTarget);

	//1�ʴ� 3�� �̵�
	float deltaMove = 3.0f * _timeDelta;
	float time = Clamp01(deltaMove / dist);
	//���� ����
	D3DXVECTOR3 pos = VecLerp(_trans->GetWorldPosition(), _hitPos, time);

	//���� ���
	pos.y = _terrain->getHeight(pos.x, pos.z);
	//���� ������ġ�� �̵�
	_trans->SetWorldPosition(pos);

	//�߷�ó��
	D3DXVECTOR3 sliding;
	_terrain->getSlant(&sliding, 0.81f, pos.x, pos.z);

	//���� sliding ��ŭ ���� �̵���Ŵ
	_trans->MovePositionWorld(sliding * _timeDelta);

	_dirLight->_transform->DefaultMyControl(_timeDelta);
}

void terrainPickingTest::render(void)
{
	//���׼��� 0xff806A12
	_device->SetRenderState(D3DRS_FOGENABLE, TRUE);					//���� ��뿩��
	_device->SetRenderState(D3DRS_FOGCOLOR, 0xff806A12);			//���� ����
	_device->SetRenderState(D3DRS_FOGSTART, FloatToDWORD(10.0f));	//���� ���� �Ÿ�
	_device->SetRenderState(D3DRS_FOGEND, FloatToDWORD(100.0f));	//���� ���� �Ÿ�
	_device->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);		//���׼��� ���
	_terrain->render(_mainCamera, _dirLight);
	_device->SetRenderState(D3DRS_FOGENABLE, false);

	//Hit ��ġ�� �������
	GIZMOMANAGER->WireSphere(_hitPos, 0.5f, 0xffff0000);

	//Trans ��ġ�� ��
	GIZMOMANAGER->WireSphere(_trans->GetWorldPosition(), 1.0f, 0xffffffff);
	_trans->RenderGimozo();
}
