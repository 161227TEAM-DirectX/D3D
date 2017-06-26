#include "stdafx.h"
#include "cMinimapTest.h"


cMinimapTest::cMinimapTest()
{
}


cMinimapTest::~cMinimapTest()
{
}

HRESULT cMinimapTest::init()
{
	//로딩될 메쉬의 정보 내맘대로 보정하기
	D3DXMATRIXA16	matScale, matRotate, matCorrection;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	matCorrection = matScale * matRotate;

	//플레이어 오브젝트 초기화
	_player.setMesh(RM_XMESH->getResource("ResourceUI/test/GunShip/gunship.x", &matCorrection));
	_player.setActive(true);
	_player._transform->SetWorldPosition(D3DXVECTOR3(0, 2, 0));

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





	//기본 광원 생성
	_baseLight = new lightDirection;
	//기본 값
	_baseLight->_color = D3DXCOLOR(1, 1, 1, 1);
	_baseLight->_intensity = 1.0f;

	//카메라 월드 위치 설정
	_mainCamera.SetWorldPosition(0.0f, 0.0f, 0.0f);

	//지형 생성
	_terrain = new terrain;
	_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("height_base"));
	_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("minimap3"));
	_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("tileTest1"));
	_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("tileTest2"));
	_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("tileTest3"));
	_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("splat_red_base"));
	_terrain->setTileNum(1);
	//_terrain->setHeightscale(100.0f);
	//_terrain->setBrushmap(FILEPATH_MANAGER->GetFilepath("브러쉬_brush01"));
	//_terrain->setBrushScale(1.0f);
	_terrain->setting();

	_hitPos = D3DXVECTOR3(0, 0, 0);


	DXIMG_MANAGER->GetDxImg("minimap3")->SetPosition(D3DXVECTOR3(WINSIZEX - 400, 0, 0));
	//DXIMG_MANAGER->GetDxImg("minimap3")->SetCenterDraw(true);

	miniWidth = 400;
	miniHeight = 400;
	miniX = (DXIMG_MANAGER->GetDxImg("minimap3")->GetSize().fWidth / 2) - miniWidth / 2;
	miniY = (DXIMG_MANAGER->GetDxImg("minimap3")->GetSize().fHeight / 2) - miniHeight / 2;


	DXIMG_MANAGER->GetDxImg("miniPlayer")->SetPosition(D3DXVECTOR3(DXIMG_MANAGER->GetDxImg("minimap3")->GetPosition().x + miniWidth / 2 + miniMoveX,
																   DXIMG_MANAGER->GetDxImg("minimap3")->GetPosition().y + miniHeight / 2 + miniMoveY, 0));
	DXIMG_MANAGER->GetDxImg("miniPlayer")->SetCenterDraw(true);

	DXIMG_MANAGER->GetDxImg("radar")->SetPosition(D3DXVECTOR3(DXIMG_MANAGER->GetDxImg("miniPlayer")->GetPosition().x,
															  DXIMG_MANAGER->GetDxImg("miniPlayer")->GetPosition().y,
															  DXIMG_MANAGER->GetDxImg("miniPlayer")->GetPosition().z));
	DXIMG_MANAGER->GetDxImg("radar")->SetCenterDraw(true);
	DXIMG_MANAGER->GetDxImg("radar")->SetImgAlpha(64);

	_mainCamera.SetWorldPosition(0, 200, 0);
	_mainCamera.SetRotateWorld(D3DXToRadian(90), 0, 0);

	return S_OK;
}

void cMinimapTest::release()
{
}

void cMinimapTest::update()
{
	_mainCamera.updateBase();

	_player._transform->DefaultMyControl(_timeDelta);


	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		angle -= 90 * _timeDelta;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		angle += 90 * _timeDelta;
	}

	//	//각도 값만큼 회전행렬
	//	D3DXMATRIXA16 matRot;
	//	D3DXMatrixRotationY(&matRot, angle);
	//
	//	//회전을 먹이기전 사물의 진행방향
	//	D3DXVECTOR3 moveDir(0, 0, 1);
	//	//진행방향에 회전행렬을 주기
	//	D3DXVec3TransformNormal(&moveDir, &moveDir, &matRot);
	//
	//
	//	
	//
	//
	//
	//	//이동벡터 이동량 * 진행방향
	//	D3DXVECTOR3 moveVector = moveDir * moveValue;
	//
	//
	//
	//	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON) == FALSE)
	//	{
	//		if (KEYMANAGER->isStayKeyDown('A'))
	//		{
	//			angle -= 90 * _timeDelta;
	//
	//			////미니맵의 절반에 도달하지 못했으면(왼쪽으로)
	//			//if (moveX < miniWidth * 3 / 2)
	//			//{
	//			//	//미니맵에서 오른쪽에 위치하고 있을 경우
	//			//	//왼쪽진행시 미니맵내부의 플레이어 위치가 미니맵 절반에 도달하지 못했다면 
	//			//	if (miniMoveX >= 0)
	//			//	{
	//			//		//미니맵 내부의 플레이어가 왼쪽으로 움직인다.
	//			//		miniMoveX -= moveValue;
	//			//	}
	//			//	//미니맵내부 플레이어가 미니맵 중심부에 위치한다면
	//			//	else
	//			//	{
	//			//		//미니맵이 오른쪽으로 밀려난다.
	//			//		moveX += moveValue;
	//			//	}
	//			//}
	//			////미니맵이 왼쪽절반에 도달햇으면 미니맵 내부의 플레이어가 왼쪽으로 움직인다.
	//			//else
	//			//{
	//			//	miniMoveX -= moveValue;
	//			//}
	//		}
	//		if (KEYMANAGER->isStayKeyDown('D'))
	//		{
	//			angle += 90 * _timeDelta;
	//
	//			////미니맵의 절반에 도달하지 못했으면(오른쪽으로)
	//			//if (moveX > -miniWidth * 3 / 2)
	//			//{
	//			//	//미니맵에서 왼쪽에 위치하고 있을경우
	//			//	//오른쪽진행시 미니맵내부의 플레이어 위치가 미니맵 절반에 도달하지 못했다면
	//			//	if (miniMoveX <= 0)
	//			//	{
	//			//		//미니맵 내부의 플레이어가 오른쪽으로 움직인다.
	//			//		miniMoveX += moveValue;
	//			//	}
	//			//	//미니맵내부 플레이어가 미니맵 중심부에 위치한다면
	//			//	else
	//			//	{
	//			//		//미니맵을 왼쪽으로 밀어낸다.
	//			//		moveX -= moveValue;
	//			//	}
	//			//}
	//			////미니맵이 오른쪽절반에 도달햇으면 미니맵 내부의 플레이어가 오른쪽으로 움직인다.
	//			//else
	//			//{
	//			//	miniMoveX += moveValue;
	//			//}
	//			
	//		}
	//
	//
	//		//각도 값만큼 회전행렬
	//		D3DXMATRIXA16 matRot;
	//		D3DXMatrixRotationY(&matRot, angle);
	//
	//		//회전을 먹이기전 사물의 진행방향
	//		D3DXVECTOR3 moveDir(0, 0, 1);
	//		//진행방향에 회전행렬을 주기
	//		D3DXVec3TransformNormal(&moveDir, &moveDir, &matRot);
	//
	//		//이동벡터 이동량 * 진행방향
	//		D3DXVECTOR3 moveVector = moveDir * moveValue;
	//
	//		if(KEYMANAGER->isStayKeyDown('W'))
	//		{
	//		/*	DXIMG_MANAGER->GetDxImg("minimap3")->SetPosition(D3DXVECTOR3(DXIMG_MANAGER->GetDxImg("minimap3")->GetPosition().x + moveValue * cosf(D3DXToRadian(angle-90)),
	//																		   DXIMG_MANAGER->GetDxImg("minimap3")->GetPosition().y + moveValue * sinf(D3DXToRadian(angle-90)), 0));*/
	//			moveY += moveValue;
	//
	//			////미니맵의 절반에 도달하지 못했으면(위쪽으로)
	//			//if (moveY < miniHeight * 3 / 2)
	//			//{
	//			//	//미니맵내부의 플레이어 위치가 미니맵 절반에 도달하지 못했다면 
	//			//	if (miniMoveY >= 0)
	//			//	{
	//			//		//미니맵 내부의 플레이어가 아래로 움직인다.
	//			//		miniMoveY -= moveValue;
	//			//	}
	//			//	else
	//			//	{
	//			//	//미니맵이 위로 움직인다.
	//			//		moveY += moveValue;
	//			//	}
	//			//}
	//			////미니맵이 위쪽절반에 도달햇으면 미니맵 내부의 플레이어가 움직인다.
	//			//else
	//			//{
	//			//	miniMoveY-= moveValue;
	//			//}
	//		}
	//		if (KEYMANAGER->isStayKeyDown('S'))
	//		{
	//			////미니맵의 절반에 도달하지 못했으면(아래쪽으로)
	//			//if (moveY > -miniHeight * 3 / 2)
	//			//{
	//			//	//미니맵내부의 플레이어 위치가 미니맵 절반에 도달하지 못했다면 
	//			//	if (miniMoveY <= 0)
	//			//	{
	//			//		//미니맵 내부의 플레이어가 아래로 움직인다.
	//			//		miniMoveY += moveValue;
	//			//	}
	//			//	else
	//			//	{
	//			//	//미니맵이 아래로 움직인다.
	//			//		moveY -= moveValue;
	//			//	}
	//			//}
	//			////미니맵이 아래쪽절반에 도달햇으면 미니맵 내부의 플레이어가 움직인다.
	//			//else
	//			//{
	//			//	miniMoveY += moveValue;
	//			//}
	//		}
	//	}
	//
	//	/*if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	//	{
	//		Ray ray;
	//		POINT ptMousePos = GetMousePos();
	//		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
	//		_mainCamera.computeRay(&ray, &screenPos);
	//
	//		_terrain->isIntersectRay(&_hitPos, &ray);
	//	}*/
	//
	//	/*DXIMG_MANAGER->GetDxImg("miniPlayer")->SetPosition(D3DXVECTOR3(DXIMG_MANAGER->GetDxImg("minimap3")->GetPosition().x + miniWidth / 2 + miniMoveX,
	//																   DXIMG_MANAGER->GetDxImg("minimap3")->GetPosition().y + miniHeight / 2 + miniMoveY, 0));
	//*/
	//
	//
	//	//DXIMG_MANAGER->GetDxImg("radar")->SetPosition(D3DXVECTOR3(DXIMG_MANAGER->GetDxImg("miniPlayer")->GetPosition().x,
	//	//														  DXIMG_MANAGER->GetDxImg("miniPlayer")->GetPosition().y,
	//	//														  DXIMG_MANAGER->GetDxImg("miniPlayer")->GetPosition().z));
	//
	//	//moveValue = 0;

	moveValue = DXIMG_MANAGER->GetDxImg("minimap3")->GetSize().fWidth * _player._transform->GetMove() * _timeDelta / _terrain->GetTerrainSizeX();
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		moveX += moveValue * -cosf(D3DXToRadian(angle - 90));
		moveY += moveValue * -sinf(D3DXToRadian(angle - 90));
	}
}

void cMinimapTest::render()
{
	//플레이어 렌더
	_player.render();

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




	_terrain->render(&_mainCamera, _baseLight);

	GIZMOMANAGER->LineAxis();

	DXIMG_MANAGER->render("minimap3", miniX, miniY, miniWidth, miniHeight,
						  moveX,
						  moveY);

	//DXIMG_MANAGER->render("radar");
	DXIMG_MANAGER->GetDxImg("radar")->render(0, 0, angle);


	DXIMG_MANAGER->render("miniPlayer");



	//Hit 위치에 구만들기
	//GIZMOMANAGER->WireSphere(_hitPos, 0.5f, RED);


	char str[STR_LEN];
	sprintf(str, "플레이어 좌표: [ %f %f ]", _player._transform->GetWorldPosition().x, _player._transform->GetWorldPosition().z);
	FONTMANAGER->fontOut(str, 0, 0, GREEN);

	FONTMANAGER->fontOut("미니맵가로: " + to_string(DXIMG_MANAGER->GetDxImg("minimap3")->GetSize().fWidth), 100, 20, GREEN);
	FONTMANAGER->fontOut("미니맵세로" + to_string(DXIMG_MANAGER->GetDxImg("minimap3")->GetSize().fHeight), 100, 40, GREEN);

	FONTMANAGER->fontOut("카메라 위치x: " + to_string(_mainCamera.GetWorldPosition().x), 100, 60, GREEN);
	FONTMANAGER->fontOut("카메라 위치y: " + to_string(_mainCamera.GetWorldPosition().y), 100, 80, GREEN);
	FONTMANAGER->fontOut("카메라 위치z: " + to_string(_mainCamera.GetWorldPosition().z), 100, 100, GREEN);

	FONTMANAGER->fontOut("카메라 회전x: " + to_string(_mainCamera.GetAngleX()), 100, 160, GREEN);
	FONTMANAGER->fontOut("카메라 회전y: " + to_string(_mainCamera.GetAngleY()), 100, 180, GREEN);

	FONTMANAGER->fontOut("미니맵무브Y: " + to_string(moveY), 100, 200, GREEN);
	FONTMANAGER->fontOut("미니맵미니무브Y: " + to_string(miniMoveY), 100, 220, GREEN);

	FONTMANAGER->fontOut("3차원게임맵길이: " + to_string(_terrain->GetTerrainSizeX()), 100, 240, GREEN);
	FONTMANAGER->fontOut("미니맵게임길이: " + to_string(DXIMG_MANAGER->GetDxImg("minimap3")->GetSize().fWidth), 100, 260, GREEN);

	FONTMANAGER->fontOut("각도: " + to_string(angle), 100, 280, GREEN);

}
