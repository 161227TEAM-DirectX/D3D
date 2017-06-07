#include "stdafx.h"
#include "boundBoxTest.h"

HRESULT boundBoxTest::init(void)
{
	//원래 있던 매쉬에서 다음과 같은 행렬로 보정시켜 
	//모든 정보를 틀어버린다.
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.2f, 0.2f, 0.2f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	//비행기에 메시 세팅하기
	_plane.setMesh(RM_XMESH->getResource("Resources/Meshes/GunShip/gunship.x", &matCorrection));

	//plane 에 카메라 붙여라...
	_plane._transform->AddChild(_mainCamera);
	_mainCamera->SetLocalPosition(0, 5, -10);
	_plane.setActive(true);

	//적비행기 초기화
	for (int i = 0; i < 10; i++)
	{
		_enemyPlanes.push_back(new enemyPlane);
		_enemyPlanes[i]->setActive(true);
		_enemyPlanes[i]->setMesh(RM_XMESH->getResource("Resources/Meshes/GunShip/gunship.x"));
	}

	//라이트 푸쉬
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

	return S_OK;
}

void boundBoxTest::release(void)
{
	for (int i = 0; i < _lights.size(); i++)
	{
		SAFE_DELETE(_lights[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		SAFE_DELETE(_enemyPlanes[i]);
	}
}

void boundBoxTest::update(void)
{
	_plane.update();

	for (int i = 0; i < 10; i++)
	{
		_enemyPlanes[i]->update();
	}
}

void boundBoxTest::render(void)
{
	//적용되는 LightMatrix
	D3DXMATRIXA16 matLights[10];
	for (int i = 0; i < _lights.size(); i++)
	{
		matLights[i] = _lights[i]->getLightMatrix();
	}

	//셰이더에 라이팅 셋팅
	xMeshStatic::_staticMeshEffect->SetMatrixArray("matLights", matLights, 10);
	xMeshStatic::_staticMeshEffect->SetInt("LightNum", _lights.size());

	xMeshStatic::setCamera(_mainCamera);

	_plane.render();

	//빨간색 Player 비행기 정면으로 빨간색라인
	D3DXVECTOR3 pos = _plane._transform->GetWorldPosition();
	D3DXVECTOR3 forward = _plane._transform->GetForward();
	GIZMOMANAGER->Line(pos, pos + forward * 30, 0xffff0000);

	for (int i = 0; i < 10; i++)
	{
		_enemyPlanes[i]->render();
	}
}
