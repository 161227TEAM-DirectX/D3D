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
//	ofstream fout("Resource/��������/test.map");
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
		temp = "��ũ����";
		return temp;
	case 2:
		temp = "�Ǹ���";
		return temp;
	case 3:
		temp = "�����";
		return temp;
	case 4:
		temp = "��������";
		return temp;
	case 5:
		temp = "���Ż�罺";
		return temp;
	case 6:
		temp = "�����";
		return temp;
	case 7:
		temp = "���ڻ�";
		return temp;
	case 8:
		temp = "ũ��Ŀ����";
		return temp;
	case 9:
		temp = "Ǯ����";
		return temp;
	case 10:
		temp = "�Ұ���";
		return temp;
	case 11:
		temp = "����";
		return temp;
	case 12:
		temp = "����";
		return temp;
	case 13:
		temp = "����";
		return temp;
	case 14:
		temp = "���⵵����";
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
		return XMESH_MANAGER->GetXmeshSkinned("��");
	case 2:
		return XMESH_MANAGER->GetXmeshSkinned("��");
	case 3:
		return XMESH_MANAGER->GetXmeshSkinned("�����");
	case 4:
		return XMESH_MANAGER->GetXmeshSkinned("��������");
	case 5:
		return XMESH_MANAGER->GetXmeshSkinned("���Ż�罺");
	case 6:
		return XMESH_MANAGER->GetXmeshSkinned("�����");
	case 7:
		return XMESH_MANAGER->GetXmeshSkinned("��");
	case 8:
		return XMESH_MANAGER->GetXmeshSkinned("�Ǿ�");
	case 9:
		return XMESH_MANAGER->GetXmeshSkinned("��");
	case 10:
		return XMESH_MANAGER->GetXmeshSkinned("�Ұ���");
	case 11:
		return XMESH_MANAGER->GetXmeshSkinned("����");
	case 12:
		return XMESH_MANAGER->GetXmeshSkinned("����");
	case 13:
		return XMESH_MANAGER->GetXmeshSkinned("����");
	case 14:
		return XMESH_MANAGER->GetXmeshSkinned("������");
	}
}

HRESULT bossMonsterAITestScene::init()
{
	boss = new bossMonster;
	player = new xPlayer;
	_mainCamera = new camera;
	_directionLightCamera = new camera;
	sceneBaseDirectionLight = new lightDirection;

	//���� �ʱ�ȭ
	_terrain = new terrain;
	_terrain->setHeightmap("���̸�_3");
	_terrain->setTile0(IOMAPMANAGER->loadMapInfo("��������").tile0, true);
	_terrain->setTile1(IOMAPMANAGER->loadMapInfo("��������").tile1, true);
	_terrain->setTile2(IOMAPMANAGER->loadMapInfo("��������").tile2, true);
	_terrain->setTile3(IOMAPMANAGER->loadMapInfo("��������").tile3, true);
	_terrain->setSplat(IOMAPMANAGER->loadMapInfo("��������").splat, true);
	_terrain->setMapPosition(IOMAPMANAGER->loadMapInfo("��������").vecPos);
	_terrain->setting();
	_terrain->changeHeightTerrain();

	float tempY = _terrain->getHeight(0.0f, 5.0f);

	IOSAVEMONSTERBOX->loadFile("test");

	//�÷��̾� �ʱ�ȭ
	player->out_setlinkTerrain(*_terrain);
	player->init();
	player->getPlayerObject()->_transform->SetWorldPosition(10.0f, 0.0f, 10.0f);
	player->getPlayerObject()->_transform->SetScale(1.0f, 1.0f, 1.0f);

	_mainCamera->out_SetLinkTrans(player->getPlayerObject()->_transform);
	_mainCamera->out_SetRelativeCamPos(D3DXVECTOR3(0, 5, 5));

	//���� �⺻ �� �ʱ�ȭ
	sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	sceneBaseDirectionLight->_intensity = 1.0f;
	sceneBaseDirectionLight->_transform->SetWorldPosition(0, 20, 0);
	sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(89), 0, 0);

	//�׼� �Ŵ��� �ʱ�ȭ
	ACMANAGER->Init(*_terrain, *player, *_mainCamera);

	//�������� �ʱ�ȭ
	boss->setMesh(XMESH_MANAGER->GetXmeshSkinned("������"));
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
	//������� ���� �׸����� ReciveShadow �� Technique ����
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
