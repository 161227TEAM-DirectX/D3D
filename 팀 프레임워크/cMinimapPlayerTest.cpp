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
	//���� ī�޶�
	_mainCamera = new camera;
	_mainCamera->SetWorldPosition(0.0f, 3.0f, 3.0f);
	_mainCamera->LookPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//���� ���� ����ϴ� ����
	_sceneBaseDirectionLight = new lightDirection;
	_sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	_sceneBaseDirectionLight->_intensity = 1.0f;
	_sceneBaseDirectionLight->_transform->RotateWorld(0, 0, 0);

	//���� ����
	_terrain = new terrain;
	_terrain->setHeightmap("height_base256");
	_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_1"), true);
	_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_2"), true);
	_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_3"), true);
	_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_4"), true);
	_terrain->setSplat(FILEPATH_MANAGER->GetFilepath("splat_test2"),true);
	_terrain->setting();

	//�÷��̾� ����
	_player = new xPlayer;
	_player->out_setlinkTerrain(*_terrain);
	_player->init();
	_player->getPlayerObject()->_transform->SetWorldPosition(0.0f, 0.0f, 0.0f);
	
	//�÷��̾�UI ����
	m_pUIPlayer = new cUIPlayer;
	m_pUIPlayer->linkMinimapPlayerAngle(_player->getPlayerObject()->_transform->GetAngleY());
	m_pUIPlayer->linkMinimapPlayerMove(_player->getPlayerObject()->_transform->GetWorldPosition().x + _terrain->GetTerrainSizeX() / 2,
									   _player->getPlayerObject()->_transform->GetWorldPosition().z + _terrain->GetTerrainSizeZ() / 2,
									   _terrain->GetTerrainSizeX());
	m_pUIPlayer->SetMinimap("worldmapTest");
	m_pUIPlayer->init();

	//UI�ó׸� �ʱ�ȭ
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
	//����ī�޶� ����
	_mainCamera->updateBase(true);
	
	//����ī�޶��� ��ġ
	D3DXVECTOR3 camPos = _player->getPlayerObject()->_transform->GetWorldPosition();																							//D3DXVECTOR3 camFront = _mainCamera->GetForward();									//����ī�޶��� ����

	//���⼺ ������ ����
	D3DXVECTOR3 lightDir = _sceneBaseDirectionLight->_transform->GetForward();

	//�÷��̾� ������Ʈ
	//if (KEYMANAGER->isToggleKey('0'))
	{
		_player->update();

		//_player->out_setTargetByMouse(_mainCamera);
	}
	_player->getPlayerObject()->update();
	
	//UI ������Ʈ
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

	//UI�ó׸� ������Ʈ
	m_pUICinema->update();
}

void cMinimapPlayerTest::render()
{
	xMeshSkinned::setCamera(_mainCamera);
	xMeshSkinned::setTechniqueName("Toon");
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resource/Testures/Ramp_1.png"));
	xMeshSkinned::setBaseLight(this->_sceneBaseDirectionLight);

	//�÷��̾� ����
	_player->getPlayerObject()->render();
	
	//���� ����
	_terrain->render(_mainCamera, _sceneBaseDirectionLight);

	//UI����
	m_pUIPlayer->render();

	//UI�ó׸� ����
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
