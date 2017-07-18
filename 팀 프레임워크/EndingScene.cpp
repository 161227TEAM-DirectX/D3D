#include "stdafx.h"
#include "EndingScene.h"

EndingScene* ex_pEnding = new EndingScene;

EndingScene::EndingScene()
	: _terrain(nullptr)
	, _camera(nullptr)
{
	_renderObject.clear();

	memset(&envTemp, 0, sizeof(tagSaveMap));
	memset(&waterTemp, 0, sizeof(tagSaveMap));

	npcVector.clear();
}

EndingScene::~EndingScene()
{
}

HRESULT EndingScene::init()
{
	loadingScene();

	//노래배경
	SOUNDMANAGER->play("엔딩배경1", 0.5f);

//	loadingScene();

	return S_OK;
}



void EndingScene::release()
{

}



void EndingScene::update()
{

	//카메라 업데이트
	_camera->updateBase(true);
	//시네마 로드 부분
	CINEMATICMANAGER->cinematicEndingLoad(_camera);
	//시네마 세이브 부분
	//CINEMATICMANAGER->cinematicEndingSave(_camera);

	//오브젝트 업데이트
	for (int i = 0; i < _renderObject.size(); i++) _renderObject[i]->update();

	//물부분 업데이트
	water.update(waterTemp.number);

	for (int i = 0; i < npcVector.size(); i++)
	{
		npcVector[i]->update();
	}

	switch (CINEMATICMANAGER->GetGSnumber())
	{
	case  ENDINGNUMBER::SIX:
		byeY--;
		break;
	}

	//사운드
	if (CINEMATICMANAGER->GetGSnumber() == ENDINGNUMBER::SIX)
	{
		if (SOUNDMANAGER->isPlaySound("엔딩배경1"))
		{
			SOUNDMANAGER->stop("엔딩배경1");
			stop = true;
		}

		if (stop == true)
		{
			//엔딩노래
			SOUNDMANAGER->play("최종엔딩배경1", 0.5f);
			stop = false;
		}
	}

}



void EndingScene::render()
{
	CINEMATICMANAGER->cinematicEndingRender();

	objectSet.objectRenderTool2(_renderObject, _camera, &sceneBaseDirectionLight);

	_terrain->render(_camera, &sceneBaseDirectionLight);

	env.renderEnvironment(envTemp.number);

	water.render(waterTemp.number);

	xMeshSkinned::setCamera(_camera);
	xMeshSkinned::setTechniqueName("Toon");
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resource/Testures/Ramp_1.png"));
	xMeshSkinned::setBaseLight(&this->sceneBaseDirectionLight);

	for (int i = 0; i < npcVector.size(); i++)
	{
		npcVector[i]->render();
	}

	switch (CINEMATICMANAGER->GetGSnumber())
	{
	case ENDINGNUMBER::EONE:
		DXIMGANI_MANAGER->render("김태승");
		break;

	case ENDINGNUMBER::ETWO:
		DXIMGANI_MANAGER->render("이현총");
		break;

	case ENDINGNUMBER::ETHREE:
		DXIMGANI_MANAGER->render("김만웅");
		break;

	case ENDINGNUMBER::EFOUR:
		DXIMGANI_MANAGER->render("김태훈");
		break;

	case ENDINGNUMBER::EFIVE:
		DXIMGANI_MANAGER->render("이현수");
		break;

	case ENDINGNUMBER::SIX:
		SPRITEMANAGER->renderRectTexture(directxBye.tex, &directxBye.rc1, &directxBye.rc2, 0, 0, 410, 120, WINSIZEX / 2 - 220, 770);
		SPRITEMANAGER->renderRectTexture(directxBye2.tex, &directxBye2.rc1, &directxBye2.rc2, 0, 0, 512, 2048, byeX, byeY);
		break;
	}
}



void EndingScene::meshInit()
{
	//주석 처리는 안나오는것들
	npcVector[0]->_transform->SetWorldPosition(-19.0f, 0.0f, -48.0f);
	npcVector[0]->setMesh(XMESH_MANAGER->GetXmeshSkinned("npc6"));
	npcVector[0]->_transform->SetScale(2.5f, 2.5f, 2.5f);
	npcVector[0]->_transform->SetRotateWorld(0, D3DXToRadian(20), 0);

	npcVector[1]->_transform->SetWorldPosition(8.0f, 0.0f, -64.0f);
	npcVector[1]->setMesh(XMESH_MANAGER->GetXmeshSkinned("npc7"));
	npcVector[1]->_transform->SetScale(4.0f, 4.0f, 4.0f);
	npcVector[1]->_transform->SetRotateWorld(0, 0, 0);

	npcVector[2]->_transform->SetWorldPosition(42.0f, 0.0f, -51.0f);
	npcVector[2]->setMesh(XMESH_MANAGER->GetXmeshSkinned("npc8"));
	npcVector[2]->_transform->SetScale(2.5f, 2.5f, 2.5f);
	npcVector[2]->_transform->SetRotateWorld(0, D3DXToRadian(-30), 0);

	npcVector[3]->_transform->SetWorldPosition(56.0f, 0.0f, -27.0f);
	npcVector[3]->setMesh(XMESH_MANAGER->GetXmeshSkinned("npc10"));
	npcVector[3]->_transform->SetScale(3.0f, 3.0f, 3.0f);
	npcVector[3]->_transform->SetRotateWorld(0, D3DXToRadian(270), 0);

	npcVector[4]->_transform->SetWorldPosition(48.0f, -1.5f, 4.0f);
	npcVector[4]->setMesh(XMESH_MANAGER->GetXmeshSkinned("npc9"));
	npcVector[4]->_transform->SetScale(2.5f, 2.5f, 2.5f);
	npcVector[4]->_transform->SetRotateWorld(0, D3DXToRadian(270), 0);

	npcVector[5]->_transform->SetWorldPosition(-12.0f, 0.0f, -9.0f);
	npcVector[5]->setMesh(XMESH_MANAGER->GetXmeshSkinned("npc1"));
	npcVector[5]->_transform->SetScale(2.5f, 2.5f, 2.5f);
	npcVector[5]->_transform->SetRotateWorld(0, D3DXToRadian(130), 0);

	npcVector[6]->_transform->SetWorldPosition(-9.0f, 0.0f, -5.0f);
	npcVector[6]->setMesh(XMESH_MANAGER->GetXmeshSkinned("npc2"));
	npcVector[6]->_transform->SetScale(2.5f, 2.5f, 2.5f);
	npcVector[6]->_transform->SetRotateWorld(0, D3DXToRadian(130), 0);

	npcVector[7]->_transform->SetWorldPosition(-16.0f, 0.0f, -2.0f);
	npcVector[7]->setMesh(XMESH_MANAGER->GetXmeshSkinned("npc3"));
	npcVector[7]->_transform->SetScale(2.5f, 2.5f, 2.5f);
	npcVector[7]->_transform->SetRotateWorld(0, D3DXToRadian(130), 0);

	npcVector[8]->_transform->SetWorldPosition(-10.0f, 0.0f, 2.0f);
	npcVector[8]->setMesh(XMESH_MANAGER->GetXmeshSkinned("npc4"));
	npcVector[8]->_transform->SetScale(2.5f, 2.5f, 2.5f);
	npcVector[8]->_transform->SetRotateWorld(0, D3DXToRadian(130), 0);

	npcVector[9]->_transform->SetWorldPosition(-18.0f, 0.0f, -8.0f);
	npcVector[9]->setMesh(XMESH_MANAGER->GetXmeshSkinned("npc5"));
	npcVector[9]->_transform->SetScale(2.5f, 2.5f, 2.5f);
	npcVector[9]->_transform->SetRotateWorld(0, D3DXToRadian(130), 0);

	for (int i = 0; i < DXIMGANI_MANAGER->GetDxImgAni("김태승").size(); i++)
	{
		DXIMGANI_MANAGER->GetDxImgAni("김태승")[i]->SetPosition(D3DXVECTOR3(WINSIZEX / 2, 820, 0));
		DXIMGANI_MANAGER->GetDxImgAni("김태승")[i]->SetCenterDraw(true);
	}
	DXIMGANI_MANAGER->setDxAniIsOnce("김태승", true);

	for (int i = 0; i < DXIMGANI_MANAGER->GetDxImgAni("이현총").size(); i++)
	{
		DXIMGANI_MANAGER->GetDxImgAni("이현총")[i]->SetPosition(D3DXVECTOR3(WINSIZEX / 2, 820, 0));
		DXIMGANI_MANAGER->GetDxImgAni("이현총")[i]->SetCenterDraw(true);
	}
	DXIMGANI_MANAGER->setDxAniIsOnce("이현총", true);

	for (int i = 0; i < DXIMGANI_MANAGER->GetDxImgAni("김만웅").size(); i++)
	{
		DXIMGANI_MANAGER->GetDxImgAni("김만웅")[i]->SetPosition(D3DXVECTOR3(WINSIZEX / 2, 820, 0));
		DXIMGANI_MANAGER->GetDxImgAni("김만웅")[i]->SetCenterDraw(true);
	}
	DXIMGANI_MANAGER->setDxAniIsOnce("김만웅", true);

	for (int i = 0; i < DXIMGANI_MANAGER->GetDxImgAni("이현수").size(); i++)
	{
		DXIMGANI_MANAGER->GetDxImgAni("이현수")[i]->SetPosition(D3DXVECTOR3(WINSIZEX / 2, 820, 0));
		DXIMGANI_MANAGER->GetDxImgAni("이현수")[i]->SetCenterDraw(true);
	}
	DXIMGANI_MANAGER->setDxAniIsOnce("이현수", true);

	for (int i = 0; i < DXIMGANI_MANAGER->GetDxImgAni("김태훈").size(); i++)
	{
		DXIMGANI_MANAGER->GetDxImgAni("김태훈")[i]->SetPosition(D3DXVECTOR3(WINSIZEX / 2, 820, 0));
		DXIMGANI_MANAGER->GetDxImgAni("김태훈")[i]->SetCenterDraw(true);
	}
	DXIMGANI_MANAGER->setDxAniIsOnce("김태훈", true);
}



void EndingScene::loadingScene()
{
	//카메라 기초세팅
	_camera = new camera;
	_camera->SetLocalPosition(0, 0, 0);

	for (int i = 1; i <= 10; i++)
	{
		baseObject* NPC = new baseObject;
		NPC->setActive(true);
		npcVector.push_back(NPC);
	}

	//메쉬 초기화
	this->meshInit();

	sceneBaseDirectionLight._color = D3DXCOLOR(1, 1, 1, 1);
	sceneBaseDirectionLight._intensity = 1.0f;
	sceneBaseDirectionLight._transform->SetWorldPosition(0, 20, 0);
	sceneBaseDirectionLight._transform->RotateWorld(0, D3DXToRadian(90), 0);

	//지형로드부분
	_terrain = new terrain;
	_terrain->setHeightmap(IOMAPMANAGER->loadMapInfo("엔딩지형").heightMap, true);
	_terrain->setTile0(IOMAPMANAGER->loadMapInfo("엔딩지형").tile0, true);
	_terrain->setTile1(IOMAPMANAGER->loadMapInfo("엔딩지형").tile1, true);
	_terrain->setTile2(IOMAPMANAGER->loadMapInfo("엔딩지형").tile2, true);
	_terrain->setTile3(IOMAPMANAGER->loadMapInfo("엔딩지형").tile3, true);
	_terrain->setSplat(IOMAPMANAGER->loadMapInfo("엔딩지형").splat, true);
	_terrain->setMapPosition(IOMAPMANAGER->loadMapInfo("엔딩지형").vecPos);
	_terrain->setting();
	_terrain->changeHeightTerrain();

	//오브젝트로드부분
	IOSAVEOBJECTMANAGER->loadFile("엔딩오브젝트");
	for (int i = 0; i < IOSAVEOBJECTMANAGER->getCount(); i++)
	{
		tagSaveObject object;
		memset(&object, 0, sizeof(tagSaveObject));

		object = IOSAVEOBJECTMANAGER->findTag("넘버" + to_string(i + 1));
		baseObject* temp = new baseObject;
		D3DXMATRIX matRotate;
		objectSet.objectSet(object.objectNumber, temp, matRotate, object.objectX, object.objectY, object.objectZ, object.objectScale, object.objectRotate);

		_renderObject.push_back(temp);
	}

	//물부분,환경맵부분
	IOSAVEMANAGER->loadFile("엔딩환경");

	envTemp = IOSAVEMANAGER->findTag("환경맵");
	waterTemp = IOSAVEMANAGER->findTag("물결맵");

	water.linkCamera(*_camera);
	water.init(3.0f, 256);

	env.init();
	env.linkCamera(*_camera);

	//시네마틱설정
	CINEMATICMANAGER->init();
	//로드된값 집어 넣기 
	CINEMATICMANAGER->cinematicEndingInit();

	//마지막인사
	directxBye.tex = RM_TEXTURE->getResource("Resource/endingtexture/인사.png");
	directxBye2.tex = RM_TEXTURE->getResource("Resource/endingtexture/마지막.png");
	byeY = 900;
	byeX = WINSIZEX - 500;
	stop = false;
}

