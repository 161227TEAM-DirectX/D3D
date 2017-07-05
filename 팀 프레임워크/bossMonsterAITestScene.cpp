#include "stdafx.h"
#include "bossMonsterAITestScene.h"
#include "bossMonster.h"
#include "xPlayer.h"


bossMonsterAITestScene::bossMonsterAITestScene()
{
}


bossMonsterAITestScene::~bossMonsterAITestScene()
{
}

HRESULT bossMonsterAITestScene::clear(void)
{
	boss = nullptr;
	player = nullptr;
	_mainCamera = nullptr;

	return S_OK;
}

void bossMonsterAITestScene::destroy(void)
{
	SAFE_DELETE(boss);
	SAFE_DELETE(player);
	SAFE_DELETE(_mainCamera);
}

HRESULT bossMonsterAITestScene::init()
{
	boss = new bossMonster;
	player = new xPlayer;
	_mainCamera = new camera;

	//액션 매니저 초기화
	ACMANAGER->Init(*player);

	boss->setMesh(XMESH_MANAGER->GetXmeshSkinned("데스윙"));
	boss->_transform->SetScale(2.0f, 2.0f, 2.0f);
	boss->_transform->SetWorldPosition(0.0f, 0.0f, 0.0f);
	boss->setActive(true);

	return S_OK;
}

void bossMonsterAITestScene::release()
{
}

void bossMonsterAITestScene::update()
{
}

void bossMonsterAITestScene::render()
{
}
