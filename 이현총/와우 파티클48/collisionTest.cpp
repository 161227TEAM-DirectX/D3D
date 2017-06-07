#include "stdafx.h"
#include "collisionTest.h"

HRESULT collisionTest::init(void)
{
	//로딩될 메쉬의 정보를 내맘대로 보정하기
	D3DXMATRIXA16	matScale, matRotate, matCorrection;
	D3DXMatrixScaling(&matScale, 0.3f, 0.3f, 0.3f);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	matCorrection = matScale * matRotate;

	//플레이어 오브젝트
	_player.setMesh(RM_XMESH->getResource("Resources/Meshes/GunShip/Gunship.x", &matCorrection));
	_player.setActive(true);

	//에너미 오브젝트
	_enemy.setMesh(RM_XMESH->getResource("Resources/Meshes/GunShip/Gunship.x", &matCorrection));
	_enemy.setActive(true);
	//에너미 오브젝트 변환시키기
	//_enemy._transform.SetWorldPosition(10, 5, -2); //우측상단
	//_enemy._transform.LookPosition(D3DXVECTOR3(0, 0, 0)); //플레이어가 있는 방향

	//블로킹(슬라이드 미끄러지기, 밀기, 서로같이 움직이기)
	//에너미를 벽개념으로 세워두기
	_enemy._transform->SetWorldPosition(20, 0, 0);
	_enemy._transform->SetScale(3, 3, 3);

	//라이트 세팅
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

	//충돌변수 초기화(있어도 없어도 그만)
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
	//플레이어 움직이기
	_player._transform->DefaultMyControl(_timeDelta);

	//피직스매니져 이용해서 충돌판정하기
	//_isHit = PHYSICSMANAGER->isOverlap(&_player, &_enemy);
	
	//피직스매니져 이용해서 블로킹하기(서로영향받기, 한쪽만 영향받기)
	//_isHit = PHYSICSMANAGER->isBlocking(&_player, &_enemy, 1.0f);
	//_isHit = PHYSICSMANAGER->isBlocking(&_player, &_enemy, 0.5f);
	//_isHit = PHYSICSMANAGER->isBlocking(&_player, &_enemy, 0.0f);
}

void collisionTest::render(void)
{
	//플레이어, 에너미 렌더
	_player.render();
	_enemy.render();

	//렌더시킬 조명행렬 초기화 (각각의 라이트 클래스안에 만들어져있음)
	D3DXMATRIXA16 matLights[10];
	for (int i = 0; i < _lights.size(); i++)
	{
		matLights[i] = _lights[i]->getLightMatrix();
	}

	//셰이더에 라이트 세팅
	xMeshStatic::_staticMeshEffect->SetMatrixArray("matLights", matLights, 10);
	xMeshStatic::_staticMeshEffect->SetInt("LightNum", _lights.size());
	//세이더에 카메라 세팅
	xMeshStatic::setCamera(_mainCamera);

	//충돌여부 보여주기
	if (_isHit)
	{
		FONTMANAGER->fontOut("으악 충돌됨~~~", 200, 100, 0xffff0000);
	}
	else
	{
		FONTMANAGER->fontOut("안충돌함", 200, 100, 0xffffff00);
	}
}
