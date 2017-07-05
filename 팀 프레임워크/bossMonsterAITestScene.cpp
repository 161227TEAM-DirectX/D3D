#include "stdafx.h"
#include "bossMonsterAITestScene.h"
#include "bossMonster.h"
#include "xPlayer.h"


HRESULT bossMonsterAITestScene::clear(void)
{
	boss = nullptr;
	player = nullptr;
	_mainCamera = nullptr;
	_directionLightCamera = nullptr;
	sceneBaseDirectionLight = nullptr;

	_terrain = nullptr;

	return S_OK;
}

void bossMonsterAITestScene::destroy(void)
{
	SAFE_DELETE(boss);
	SAFE_DELETE(player);
	SAFE_DELETE(_mainCamera);
	SAFE_DELETE(_directionLightCamera);
	SAFE_DELETE(sceneBaseDirectionLight);
}

HRESULT bossMonsterAITestScene::init()
{
	boss = new bossMonster;
	player = new xPlayer;
	_mainCamera = new camera;
	_directionLightCamera = new camera;
	sceneBaseDirectionLight = new lightDirection;

	//지형 초기화
	_terrain = new terrain;
	_terrain->setHeightmap("높이맵_3");
	_terrain->setTile0(IOMAPMANAGER->loadMapInfo("보스지형").tile0, true);
	_terrain->setTile1(IOMAPMANAGER->loadMapInfo("보스지형").tile1, true);
	_terrain->setTile2(IOMAPMANAGER->loadMapInfo("보스지형").tile2, true);
	_terrain->setTile3(IOMAPMANAGER->loadMapInfo("보스지형").tile3, true);
	_terrain->setSplat(IOMAPMANAGER->loadMapInfo("보스지형").splat, true);
	_terrain->setMapPosition(IOMAPMANAGER->loadMapInfo("보스지형").vecPos);
	_terrain->setting();
	_terrain->changeHeightTerrain();

	float tempY = _terrain->getHeight(0.0f, 5.0f);

	//액션 매니저 초기화
	ACMANAGER->Init(*_terrain, *player);

	//보스몬스터 초기화
	boss->setMesh(XMESH_MANAGER->GetXmeshSkinned("데스윙"));
	boss->_transform->SetScale(2.0f, 2.0f, 2.0f);
	boss->_transform->SetWorldPosition(0.0f, 0.0f, 0.0f);
	boss->setActive(true);

	//플레이어 초기화
	player->out_setlinkTerrain(*_terrain);
	player->init();
	player->getPlayerObject()->_transform->SetWorldPosition(5.0f, tempY, 5.0f);
	player->getPlayerObject()->_transform->SetScale(1.0f, 1.0f, 1.0f);

	_mainCamera->out_SetLinkTrans(player->getPlayerObject()->_transform);
	_mainCamera->out_SetRelativeCamPos(D3DXVECTOR3(0, 5, 5));

	//배경씬 기본 빛 초기화
	sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	sceneBaseDirectionLight->_intensity = 1.0f;
	sceneBaseDirectionLight->_transform->SetWorldPosition(0, 20, 0);
	sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(89), 0, 0);

	return S_OK;
}

void bossMonsterAITestScene::release()
{
}

void bossMonsterAITestScene::update()
{
	_mainCamera->updateBase();
	//player->update();

//	player->out_setTargetByMouse(_mainCamera);
	boss->update();
}

void bossMonsterAITestScene::render()
{
	//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
	xMeshStatic::setCamera(_mainCamera);
	//xMeshStatic::setTechniqueName("ReciveShadow");
	xMeshStatic::setTechniqueName("Toon");
	xMeshStatic::_staticMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resource/Testures/Ramp_1.png"));
	xMeshStatic::setBaseLight(this->sceneBaseDirectionLight);

	xMeshSkinned::setCamera(_mainCamera);
	//xMeshSkinned::setTechniqueName("ReciveShadow");
	xMeshSkinned::setTechniqueName("Toon");
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resource/Testures/Ramp_1.png"));
	xMeshSkinned::setBaseLight(this->sceneBaseDirectionLight);

	_terrain->render(_mainCamera, sceneBaseDirectionLight);

	boss->render();
	player->render();
}
