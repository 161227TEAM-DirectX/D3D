#include "stdafx.h"
#include "EndingScene.h"

HRESULT EndingScene::init()
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

	return S_OK;
}

void EndingScene::release()
{

}

void EndingScene::update()
{
	//카메라 업데이트
	_camera->updateBase(true);

	npcVector[5]->_transform->DefaultControl(_timeDelta * 3.0f);

	//오브젝트 업데이트
	for (int i = 0; i < _renderObject.size(); i++) _renderObject[i]->update();

	//물부분 업데이트
	water.update(waterTemp.number);

	for (int i = 0; i < npcVector.size(); i++)
	{
		npcVector[i]->update();
	}

}

void EndingScene::render()
{
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

	FONTMANAGER->fontOut(to_string(npcVector[5]->_transform->GetWorldPosition().x),0, 120, YELLOW);
	FONTMANAGER->fontOut(to_string(npcVector[5]->_transform->GetWorldPosition().z), 0, 150, YELLOW);
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
}
