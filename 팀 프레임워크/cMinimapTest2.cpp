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
	//로딩될 메쉬의 정보 내맘대로 보정하기
	D3DXMATRIXA16	matScale, matRotate, matCorrection;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	matCorrection = matScale * matRotate;

	//플레이어 오브젝트 초기화
	_player.setMesh(RM_XMESH->getResource("ResourceUI/test/GunShip/gunship.x", &matCorrection));
	_player.setActive(true);


	//광원 세팅
	//방향성 광원
	lightDirection* light1 = new lightDirection;
	light1->_color = D3DXCOLOR(1, 1, 1, 0);
	light1->_intensity = 1.0f;
	//포인트 광원
	lightPoint* light2 = new lightPoint;
	light2->_color = D3DXCOLOR(1, 0, 0, 0);
	light2->_minRange = 5.0f;
	light2->_maxRange = 10.0f;
	light2->_distancePow = 10.0f;
	//포인트 광원
	lightPoint* light3 = new lightPoint;
	light3->_color = D3DXCOLOR(0, 1, 0, 0);
	light3->_minRange = 5.0f;
	light3->_maxRange = 10.0f;
	light3->_distancePow = 10.0f;
	light3->_transform->SetWorldPosition(3, 3, 0);
	light3->_intensity = 0.5f;

	//광원 벡터에 담기
	_lights.push_back(light1);
	_lights.push_back(light2);
	_lights.push_back(light3);

	//충돌여부 초기화
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

	//물리매니져를 이용해서 충돌판정하기
	//_isHit = PHYSICSMANAGER->isOverlap(&_player, &_enemy);

	//물리매니져를 이용해서 블로킹하기(서로영향받기, 한쪽만 영향받기)
	//2개의 바운드 스피어에대한 출동하고 겹치지 않게 한다.
	//moveFactor 0.0f ~ 1.0f
	//moveFactor 가 0 일수록 겹칩에 대해 B 가 움직인다.
	//moveFactor 가 0.5 이면 겹칩에 대해 A 와 B 가 똑같은량으로 움직인다.
	//moveFactor 가 1 일수록 겹칩에 대해 A 가 움직인다.

	//_isHit = PHYSICSMANAGER->isBlocking(&_player, &_enemy, 0.0f);
	//_isHit = PHYSICSMANAGER->isBlocking(&_player, &_enemy, 0.5f);
	//_isHit = PHYSICSMANAGER->isBlocking(&_player, &_enemy, 1.0f);
}

void cMinimapTest2::render()
{
	//플레이어 렌더
	_player.render();
	//에너미 렌더
	//_enemy.render();

	//렌더시킬 광원 초기화(각각의 라이트 클래스안에 만들어져 있음)
	//적용시킬 lightMatrix
	D3DXMATRIXA16 matLights[10];
	for (int i = 0; i < _lights.size(); i++)
	{
		matLights[i] = _lights[i]->getLightMatrix();
	}
	//셰이더에 라이트 세팅
	xMeshStatic::_staticMeshEffect->SetMatrixArray("matLights", matLights, 10);
	xMeshStatic::_staticMeshEffect->SetInt("LightNum", _lights.size());
	//xMeshStatic::setCamera => 셰이더안에 뷰프로젝션과, 눈의위치를 세팅해줘야 한다
	xMeshStatic::setCamera(&_mainCamera);

	////충돌여부 보여주기
	//if (_isHit)
	//{
	//	FONTMANAGER->fontOut("으악 충돌됨", 100, 100, 0xffff0000);
	//}
	//else
	//{
	//	FONTMANAGER->fontOut("충돌안함", 200, 100, 0xffffff00);
	//}
}
