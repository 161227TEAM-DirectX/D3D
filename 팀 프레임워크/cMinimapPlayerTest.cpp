#include "stdafx.h"
#include "cMinimapPlayerTest.h"
//
#include "xPlayer.h"
#include "cUIPlayer.h"
#include "cUICinema.h"

cMinimapPlayerTest::cMinimapPlayerTest()
{
}


cMinimapPlayerTest::~cMinimapPlayerTest()
{
}

HRESULT cMinimapPlayerTest::init()
{
	//메인 카메라
	_mainCamera = new camera;
	_mainCamera->SetWorldPosition(0.0f, 3.0f, 3.0f);
	_mainCamera->LookPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//현재 씬을 담당하는 광원
	_sceneBaseDirectionLight = new lightDirection;
	_sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	_sceneBaseDirectionLight->_intensity = 1.0f;
	_sceneBaseDirectionLight->_transform->RotateWorld(0, 0, 0);

	//지형 생성
	_terrain = new terrain;
	_terrain->setHeightmap("height_base256");
	_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("타일맵_1"), true);
	_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("타일맵_2"), true);
	_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("타일맵_3"), true);
	_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("타일맵_4"), true);
	_terrain->setSplat(FILEPATH_MANAGER->GetFilepath("splat_test2"),true);
	_terrain->setting();

	//플레이어 생성
	_player = new xPlayer;
	_player->out_setlinkTerrain(*_terrain);
	_player->init();
	_player->getPlayerObject()->_transform->SetWorldPosition(0.0f, 0.0f, 0.0f);
	
	//플레이어UI 생성
	m_pUIPlayer = new cUIPlayer;
	m_pUIPlayer->linkMinimapPlayerAngle(_player->getPlayerObject()->_transform->GetAngleY());
	m_pUIPlayer->linkMinimapPlayerMove(_player->getPlayerObject()->_transform->GetWorldPosition().x + _terrain->GetTerrainSizeX() / 2,
									   _player->getPlayerObject()->_transform->GetWorldPosition().z + _terrain->GetTerrainSizeZ() / 2,
									   _terrain->GetTerrainSizeX());
	m_pUIPlayer->SetMinimap("worldmapTest");
	m_pUIPlayer->init();

	//UI시네마 초기화
	m_pUICinema = new cUICinema;
	m_pUICinema->init();

	return S_OK;
}

void cMinimapPlayerTest::release()
{
	SAFE_DELETE(m_pUICinema);
	SAFE_DELETE(m_pUIPlayer);
	SAFE_DELETE(_player);
	SAFE_DELETE(_terrain);
	SAFE_DELETE(_sceneBaseDirectionLight);
	SAFE_DELETE(_mainCamera);
}

void cMinimapPlayerTest::update()
{
	//메인카메라 조작
	_mainCamera->updateBase(true);
	
	//메인카메라의 위치
	D3DXVECTOR3 camPos = _player->getPlayerObject()->_transform->GetWorldPosition();																							//D3DXVECTOR3 camFront = _mainCamera->GetForward();									//메인카메라의 정면

	//방향성 광원의 방향
	D3DXVECTOR3 lightDir = _sceneBaseDirectionLight->_transform->GetForward();

	//플레이어 업데이트
	//if (KEYMANAGER->isToggleKey('0'))
	{
		_player->update();

		//_player->out_setTargetByMouse(_mainCamera);
	}
	_player->getPlayerObject()->update();
	
	//UI 업데이트
	m_pUIPlayer->update();
	m_pUIPlayer->linkMinimapPlayerAngle(_player->getPlayerObject()->_transform->GetAngleY());
	m_pUIPlayer->linkMinimapPlayerMove(_player->getPlayerObject()->_transform->GetWorldPosition().x + _terrain->GetTerrainSizeX() / 2,
									   _player->getPlayerObject()->_transform->GetWorldPosition().z + _terrain->GetTerrainSizeZ() / 2,
									   _terrain->GetTerrainSizeX());

	if(KEYMANAGER->isOnceKeyDown('9'))
	{
		_mainCamera->SetWorldPosition(0,300,0);
		_mainCamera->SetRotateWorld(D3DXToRadian(90.0f),0,0);
		_mainCamera->SetNowAngleV(90.0f);
	}

	//UI시네마 업데이트
	m_pUICinema->update();
}

void cMinimapPlayerTest::render()
{
	xMeshSkinned::setCamera(_mainCamera);
	xMeshSkinned::setTechniqueName("Toon");
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resource/Testures/Ramp_1.png"));
	xMeshSkinned::setBaseLight(this->_sceneBaseDirectionLight);

	//플레이어 렌더
	_player->getPlayerObject()->render();
	
	//지형 렌더
	_terrain->render(_mainCamera, _sceneBaseDirectionLight);

	//UI렌더
	m_pUIPlayer->render();

	//UI시네마 렌더
	m_pUICinema->render();

	//FONTMANAGER->fontOut("posX : %f", _player->getPlayerObject()->_transform->GetWorldPosition().x + _terrain->GetTerrainSizeX() / 2, 600, 100, WHITE);
	//FONTMANAGER->fontOut("posY : %f", _player->getPlayerObject()->_transform->GetWorldPosition().y, 600, 120, WHITE);
	//FONTMANAGER->fontOut("posZ : %f", _player->getPlayerObject()->_transform->GetWorldPosition().z + _terrain->GetTerrainSizeZ() / 2, 600, 140, WHITE);
	//FONTMANAGER->fontOut("GetMinimapMoveX : %f", m_pUIPlayer->GetMinimapMoveX(), 600, 160, WHITE);
	//FONTMANAGER->fontOut("GetMinimapMoveY : %f", m_pUIPlayer->GetMinimapMoveY(), 600, 180, WHITE);
	//FONTMANAGER->fontOut("GetTerrainSizeX : %f", _terrain->GetTerrainSizeX(), 600, 200, WHITE);

}

void cMinimapPlayerTest::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pUIPlayer->WndProc(hWnd,message,wParam,lParam);
}
