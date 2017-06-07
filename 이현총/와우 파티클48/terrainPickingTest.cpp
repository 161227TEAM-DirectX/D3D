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

		//Terrain 이랑 Ray체크
		_terrain->isIntersectRay(&_hitPos, &ray);
	}

	//거리를 구한다.
	D3DXVECTOR3 dirToTarget = _hitPos - _trans->GetWorldPosition();
	float dist = D3DXVec3Length(&dirToTarget);

	//1초당 3씩 이동
	float deltaMove = 3.0f * _timeDelta;
	float time = Clamp01(deltaMove / dist);
	//벡터 보간
	D3DXVECTOR3 pos = VecLerp(_trans->GetWorldPosition(), _hitPos, time);

	//높이 얻기
	pos.y = _terrain->getHeight(pos.x, pos.z);
	//얻은 높이위치로 이동
	_trans->SetWorldPosition(pos);

	//중력처리
	D3DXVECTOR3 sliding;
	_terrain->getSlant(&sliding, 0.81f, pos.x, pos.z);

	//얻은 sliding 만큼 강제 이동시킴
	_trans->MovePositionWorld(sliding * _timeDelta);

	_dirLight->_transform->DefaultMyControl(_timeDelta);
}

void terrainPickingTest::render(void)
{
	//포그세팅 0xff806A12
	_device->SetRenderState(D3DRS_FOGENABLE, TRUE);					//포그 사용여부
	_device->SetRenderState(D3DRS_FOGCOLOR, 0xff806A12);			//포그 색상
	_device->SetRenderState(D3DRS_FOGSTART, FloatToDWORD(10.0f));	//포그 시작 거리
	_device->SetRenderState(D3DRS_FOGEND, FloatToDWORD(100.0f));	//포그 종료 거리
	_device->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);		//포그선형 모드
	_terrain->render(_mainCamera, _dirLight);
	_device->SetRenderState(D3DRS_FOGENABLE, false);

	//Hit 위치에 구만들기
	GIZMOMANAGER->WireSphere(_hitPos, 0.5f, 0xffff0000);

	//Trans 위치에 구
	GIZMOMANAGER->WireSphere(_trans->GetWorldPosition(), 1.0f, 0xffffffff);
	_trans->RenderGimozo();
}
