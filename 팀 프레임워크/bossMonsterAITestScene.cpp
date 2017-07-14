#include "stdafx.h"
#include "bossMonsterAITestScene.h"
#include "bossMonster.h"
#include "monster.h"
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

void bossMonsterAITestScene::InitMonster(void)
{
//	ofstream fout("Resource/몬스터정보/test.map");
	for (int i = 1; i < 15; i++)
	{
		monster* temp = new monster(findMonsterName(i));
		temp->_transform->SetScale(1.0f, 1.0f, 1.0f);
		temp->_transform->SetWorldPosition(myUtil::RandomFloatRange(-30.0f, 30.0f), 0.0f, myUtil::RandomFloatRange(-30.0f, 30.0f));
		temp->setRegenPosition(temp->_transform->GetWorldPosition());
		temp->setMesh(findMonster(i));
		temp->setActive(true);
		mon.push_back(temp);

		//fout << temp->getLastName() << "/"
		//	<< temp->_boundBox.getLocalCenter().x << "/"
		//	<< temp->_boundBox.getLocalCenter().y << "/"
		//	<< temp->_boundBox.getLocalCenter().z << "/"

		//	<< temp->_boundBox.getLocalMinPos().x << "/"
		//	<< temp->_boundBox.getLocalMinPos().y << "/"
		//	<< temp->_boundBox.getLocalMinPos().z << "/"

		//	<< temp->_boundBox.getLocalMaxPos().x << "/"
		//	<< temp->_boundBox.getLocalMaxPos().y << "/"
		//	<< temp->_boundBox.getLocalMaxPos().z << "/"

		//	<< temp->_boundBox.getHalfSize().x << "/"
		//	<< temp->_boundBox.getHalfSize().y << "/"
		//	<< temp->_boundBox.getHalfSize().z << "/"
		//	<< temp->_boundBox.getRadius() << endl;
	}

	//fout << boss->getLastName() << "/"
	//	<< boss->_boundBox.getLocalCenter().x << "/"
	//	<< boss->_boundBox.getLocalCenter().y << "/"
	//	<< boss->_boundBox.getLocalCenter().z << "/"

	//	<< boss->_boundBox.getLocalMinPos().x << "/"
	//	<< boss->_boundBox.getLocalMinPos().y << "/"
	//	<< boss->_boundBox.getLocalMinPos().z << "/"

	//	<< boss->_boundBox.getLocalMaxPos().x << "/"
	//	<< boss->_boundBox.getLocalMaxPos().y << "/"
	//	<< boss->_boundBox.getLocalMaxPos().z << "/"

	//	<< boss->_boundBox.getHalfSize().x << "/"
	//	<< boss->_boundBox.getHalfSize().y << "/"
	//	<< boss->_boundBox.getHalfSize().z << "/"
	//	<< boss->_boundBox.getRadius() << endl;
}

string bossMonsterAITestScene::findMonsterName(int & Name)
{
	string temp = "";
	switch (Name)
	{
	case 1:
		temp = "아크레골렘";
		return temp;
	case 2:
		temp = "악마개";
		return temp;
	case 3:
		temp = "멧돼지";
		return temp;
	case 4:
		temp = "나무짐승";
		return temp;
	case 5:
		temp = "브루탈루스";
		return temp;
	case 6:
		temp = "히드라";
		return temp;
	case 7:
		temp = "코코새";
		return temp;
	case 8:
		temp = "크로커다일";
		return temp;
	case 9:
		temp = "풀보그";
		return temp;
	case 10:
		temp = "둠가드";
		return temp;
	case 11:
		temp = "하피";
		return temp;
	case 12:
		temp = "랩터";
		return temp;
	case 13:
		temp = "전갈";
		return temp;
	case 14:
		temp = "전기도마뱀";
		return temp;
	}
}

xMesh * bossMonsterAITestScene::findMonster(int & index)
{
	D3DXMATRIX mat;
	D3DXMatrixRotationY(&mat, D3DXToRadian(180));
	switch (index)
	{
	case 1:
		return XMESH_MANAGER->GetXmeshSkinned("골렘");
	case 2:
		return XMESH_MANAGER->GetXmeshSkinned("개");
	case 3:
		return XMESH_MANAGER->GetXmeshSkinned("멧돼지");
	case 4:
		return XMESH_MANAGER->GetXmeshSkinned("나무짐승");
	case 5:
		return XMESH_MANAGER->GetXmeshSkinned("브루탈루스");
	case 6:
		return XMESH_MANAGER->GetXmeshSkinned("히드라");
	case 7:
		return XMESH_MANAGER->GetXmeshSkinned("새");
	case 8:
		return XMESH_MANAGER->GetXmeshSkinned("악어");
	case 9:
		return XMESH_MANAGER->GetXmeshSkinned("곰");
	case 10:
		return XMESH_MANAGER->GetXmeshSkinned("둠가드");
	case 11:
		return XMESH_MANAGER->GetXmeshSkinned("하피");
	case 12:
		return XMESH_MANAGER->GetXmeshSkinned("랩터");
	case 13:
		return XMESH_MANAGER->GetXmeshSkinned("전갈");
	case 14:
		return XMESH_MANAGER->GetXmeshSkinned("도마뱀");
	}
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

	IOSAVEMONSTERBOX->loadFile("test");

	//플레이어 초기화
	player->out_setlinkTerrain(*_terrain);
	player->init();
	player->getPlayerObject()->_transform->SetWorldPosition(10.0f, 0.0f, 10.0f);
	player->getPlayerObject()->_transform->SetScale(1.0f, 1.0f, 1.0f);

	_mainCamera->out_SetLinkTrans(player->getPlayerObject()->_transform);
	_mainCamera->out_SetRelativeCamPos(D3DXVECTOR3(0, 5, 5));

	//배경씬 기본 빛 초기화
	sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	sceneBaseDirectionLight->_intensity = 1.0f;
	sceneBaseDirectionLight->_transform->SetWorldPosition(0, 20, 0);
	sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(89), 0, 0);

	//액션 매니저 초기화
	ACMANAGER->Init(*_terrain, *player, *_mainCamera);

	//보스몬스터 초기화
	boss->setMesh(XMESH_MANAGER->GetXmeshSkinned("데스윙"));
	boss->_transform->SetScale(2.0f, 2.0f, 2.0f);
	boss->_transform->SetWorldPosition(0.0f, 0.0f, 0.0f);
	boss->setActive(true);

//	InitMonster();

	return S_OK;
}

void bossMonsterAITestScene::release()
{
}

void bossMonsterAITestScene::update()
{
	_mainCamera->DefaultControl(_timeDelta, 0.0f);
	_mainCamera->updateCamToDevice();
	//player->update();

//	player->out_setTargetByMouse(_mainCamera);
	boss->update();
//	for (int i = 0; i < mon.size(); i++) mon[i]->update();
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
//	for (int i = 0; i < mon.size(); i++)mon[i]->render();

	//char temp[128];
	//sprintf_s(temp, "%.2f     %.2f     %.2f", _mainCamera->GetWorldPosition().x, _mainCamera->GetWorldPosition().y, _mainCamera->GetWorldPosition().z);
	//FONTMANAGER->fontOut(temp, 300, 600, WHITE);

	//sprintf_s(temp, "%.2f     %.2f     %.2f", _mainCamera->GetForward().x, _mainCamera->GetForward().y, _mainCamera->GetWorldPosition().z);
	//FONTMANAGER->fontOut(temp, 300, 650, WHITE);
}
