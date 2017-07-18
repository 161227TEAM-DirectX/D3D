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

	//�뷡���
	SOUNDMANAGER->play("�������1", 0.5f);

//	loadingScene();

	return S_OK;
}



void EndingScene::release()
{

}



void EndingScene::update()
{

	//ī�޶� ������Ʈ
	_camera->updateBase(true);
	//�ó׸� �ε� �κ�
	CINEMATICMANAGER->cinematicEndingLoad(_camera);
	//�ó׸� ���̺� �κ�
	//CINEMATICMANAGER->cinematicEndingSave(_camera);

	//������Ʈ ������Ʈ
	for (int i = 0; i < _renderObject.size(); i++) _renderObject[i]->update();

	//���κ� ������Ʈ
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

	//����
	if (CINEMATICMANAGER->GetGSnumber() == ENDINGNUMBER::SIX)
	{
		if (SOUNDMANAGER->isPlaySound("�������1"))
		{
			SOUNDMANAGER->stop("�������1");
			stop = true;
		}

		if (stop == true)
		{
			//�����뷡
			SOUNDMANAGER->play("�����������1", 0.5f);
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
		DXIMGANI_MANAGER->render("���½�");
		break;

	case ENDINGNUMBER::ETWO:
		DXIMGANI_MANAGER->render("������");
		break;

	case ENDINGNUMBER::ETHREE:
		DXIMGANI_MANAGER->render("�踸��");
		break;

	case ENDINGNUMBER::EFOUR:
		DXIMGANI_MANAGER->render("������");
		break;

	case ENDINGNUMBER::EFIVE:
		DXIMGANI_MANAGER->render("������");
		break;

	case ENDINGNUMBER::SIX:
		SPRITEMANAGER->renderRectTexture(directxBye.tex, &directxBye.rc1, &directxBye.rc2, 0, 0, 410, 120, WINSIZEX / 2 - 220, 770);
		SPRITEMANAGER->renderRectTexture(directxBye2.tex, &directxBye2.rc1, &directxBye2.rc2, 0, 0, 512, 2048, byeX, byeY);
		break;
	}
}



void EndingScene::meshInit()
{
	//�ּ� ó���� �ȳ����°͵�
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

	for (int i = 0; i < DXIMGANI_MANAGER->GetDxImgAni("���½�").size(); i++)
	{
		DXIMGANI_MANAGER->GetDxImgAni("���½�")[i]->SetPosition(D3DXVECTOR3(WINSIZEX / 2, 820, 0));
		DXIMGANI_MANAGER->GetDxImgAni("���½�")[i]->SetCenterDraw(true);
	}
	DXIMGANI_MANAGER->setDxAniIsOnce("���½�", true);

	for (int i = 0; i < DXIMGANI_MANAGER->GetDxImgAni("������").size(); i++)
	{
		DXIMGANI_MANAGER->GetDxImgAni("������")[i]->SetPosition(D3DXVECTOR3(WINSIZEX / 2, 820, 0));
		DXIMGANI_MANAGER->GetDxImgAni("������")[i]->SetCenterDraw(true);
	}
	DXIMGANI_MANAGER->setDxAniIsOnce("������", true);

	for (int i = 0; i < DXIMGANI_MANAGER->GetDxImgAni("�踸��").size(); i++)
	{
		DXIMGANI_MANAGER->GetDxImgAni("�踸��")[i]->SetPosition(D3DXVECTOR3(WINSIZEX / 2, 820, 0));
		DXIMGANI_MANAGER->GetDxImgAni("�踸��")[i]->SetCenterDraw(true);
	}
	DXIMGANI_MANAGER->setDxAniIsOnce("�踸��", true);

	for (int i = 0; i < DXIMGANI_MANAGER->GetDxImgAni("������").size(); i++)
	{
		DXIMGANI_MANAGER->GetDxImgAni("������")[i]->SetPosition(D3DXVECTOR3(WINSIZEX / 2, 820, 0));
		DXIMGANI_MANAGER->GetDxImgAni("������")[i]->SetCenterDraw(true);
	}
	DXIMGANI_MANAGER->setDxAniIsOnce("������", true);

	for (int i = 0; i < DXIMGANI_MANAGER->GetDxImgAni("������").size(); i++)
	{
		DXIMGANI_MANAGER->GetDxImgAni("������")[i]->SetPosition(D3DXVECTOR3(WINSIZEX / 2, 820, 0));
		DXIMGANI_MANAGER->GetDxImgAni("������")[i]->SetCenterDraw(true);
	}
	DXIMGANI_MANAGER->setDxAniIsOnce("������", true);
}



void EndingScene::loadingScene()
{
	//ī�޶� ���ʼ���
	_camera = new camera;
	_camera->SetLocalPosition(0, 0, 0);

	for (int i = 1; i <= 10; i++)
	{
		baseObject* NPC = new baseObject;
		NPC->setActive(true);
		npcVector.push_back(NPC);
	}

	//�޽� �ʱ�ȭ
	this->meshInit();

	sceneBaseDirectionLight._color = D3DXCOLOR(1, 1, 1, 1);
	sceneBaseDirectionLight._intensity = 1.0f;
	sceneBaseDirectionLight._transform->SetWorldPosition(0, 20, 0);
	sceneBaseDirectionLight._transform->RotateWorld(0, D3DXToRadian(90), 0);

	//�����ε�κ�
	_terrain = new terrain;
	_terrain->setHeightmap(IOMAPMANAGER->loadMapInfo("��������").heightMap, true);
	_terrain->setTile0(IOMAPMANAGER->loadMapInfo("��������").tile0, true);
	_terrain->setTile1(IOMAPMANAGER->loadMapInfo("��������").tile1, true);
	_terrain->setTile2(IOMAPMANAGER->loadMapInfo("��������").tile2, true);
	_terrain->setTile3(IOMAPMANAGER->loadMapInfo("��������").tile3, true);
	_terrain->setSplat(IOMAPMANAGER->loadMapInfo("��������").splat, true);
	_terrain->setMapPosition(IOMAPMANAGER->loadMapInfo("��������").vecPos);
	_terrain->setting();
	_terrain->changeHeightTerrain();

	//������Ʈ�ε�κ�
	IOSAVEOBJECTMANAGER->loadFile("����������Ʈ");
	for (int i = 0; i < IOSAVEOBJECTMANAGER->getCount(); i++)
	{
		tagSaveObject object;
		memset(&object, 0, sizeof(tagSaveObject));

		object = IOSAVEOBJECTMANAGER->findTag("�ѹ�" + to_string(i + 1));
		baseObject* temp = new baseObject;
		D3DXMATRIX matRotate;
		objectSet.objectSet(object.objectNumber, temp, matRotate, object.objectX, object.objectY, object.objectZ, object.objectScale, object.objectRotate);

		_renderObject.push_back(temp);
	}

	//���κ�,ȯ��ʺκ�
	IOSAVEMANAGER->loadFile("����ȯ��");

	envTemp = IOSAVEMANAGER->findTag("ȯ���");
	waterTemp = IOSAVEMANAGER->findTag("�����");

	water.linkCamera(*_camera);
	water.init(3.0f, 256);

	env.init();
	env.linkCamera(*_camera);

	//�ó׸�ƽ����
	CINEMATICMANAGER->init();
	//�ε�Ȱ� ���� �ֱ� 
	CINEMATICMANAGER->cinematicEndingInit();

	//�������λ�
	directxBye.tex = RM_TEXTURE->getResource("Resource/endingtexture/�λ�.png");
	directxBye2.tex = RM_TEXTURE->getResource("Resource/endingtexture/������.png");
	byeY = 900;
	byeX = WINSIZEX - 500;
	stop = false;
}

