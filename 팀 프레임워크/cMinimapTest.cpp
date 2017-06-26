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
	//�ε��� �޽��� ���� ������� �����ϱ�
	D3DXMATRIXA16	matScale, matRotate, matCorrection;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	matCorrection = matScale * matRotate;

	//�÷��̾� ������Ʈ �ʱ�ȭ
	_player.setMesh(RM_XMESH->getResource("ResourceUI/test/GunShip/gunship.x", &matCorrection));
	_player.setActive(true);
	_player._transform->SetWorldPosition(D3DXVECTOR3(0, 2, 0));

	//���� ����
	//���⼺ ����
	lightDirection* light1 = new lightDirection;
	light1->_color = D3DXCOLOR(1, 1, 1, 0);
	light1->_intensity = 1.0f;
	//����Ʈ ����
	lightPoint* light2 = new lightPoint;
	light2->_color = D3DXCOLOR(1, 0, 0, 0);
	light2->_minRange = 5.0f;
	light2->_maxRange = 10.0f;
	light2->_distancePow = 10.0f;
	//����Ʈ ����
	lightPoint* light3 = new lightPoint;
	light3->_color = D3DXCOLOR(0, 1, 0, 0);
	light3->_minRange = 5.0f;
	light3->_maxRange = 10.0f;
	light3->_distancePow = 10.0f;
	light3->_transform->SetWorldPosition(3, 3, 0);
	light3->_intensity = 0.5f;

	//���� ���Ϳ� ���
	_lights.push_back(light1);
	_lights.push_back(light2);
	_lights.push_back(light3);





	//�⺻ ���� ����
	_baseLight = new lightDirection;
	//�⺻ ��
	_baseLight->_color = D3DXCOLOR(1, 1, 1, 1);
	_baseLight->_intensity = 1.0f;

	//ī�޶� ���� ��ġ ����
	_mainCamera.SetWorldPosition(0.0f, 0.0f, 0.0f);

	//���� ����
	_terrain = new terrain;
	_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("height_base"));
	_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("minimap3"));
	_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("tileTest1"));
	_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("tileTest2"));
	_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("tileTest3"));
	_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("splat_red_base"));
	_terrain->setTileNum(1);
	//_terrain->setHeightscale(100.0f);
	//_terrain->setBrushmap(FILEPATH_MANAGER->GetFilepath("�귯��_brush01"));
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

	//	//���� ����ŭ ȸ�����
	//	D3DXMATRIXA16 matRot;
	//	D3DXMatrixRotationY(&matRot, angle);
	//
	//	//ȸ���� ���̱��� �繰�� �������
	//	D3DXVECTOR3 moveDir(0, 0, 1);
	//	//������⿡ ȸ������� �ֱ�
	//	D3DXVec3TransformNormal(&moveDir, &moveDir, &matRot);
	//
	//
	//	
	//
	//
	//
	//	//�̵����� �̵��� * �������
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
	//			////�̴ϸ��� ���ݿ� �������� ��������(��������)
	//			//if (moveX < miniWidth * 3 / 2)
	//			//{
	//			//	//�̴ϸʿ��� �����ʿ� ��ġ�ϰ� ���� ���
	//			//	//��������� �̴ϸʳ����� �÷��̾� ��ġ�� �̴ϸ� ���ݿ� �������� ���ߴٸ� 
	//			//	if (miniMoveX >= 0)
	//			//	{
	//			//		//�̴ϸ� ������ �÷��̾ �������� �����δ�.
	//			//		miniMoveX -= moveValue;
	//			//	}
	//			//	//�̴ϸʳ��� �÷��̾ �̴ϸ� �߽ɺο� ��ġ�Ѵٸ�
	//			//	else
	//			//	{
	//			//		//�̴ϸ��� ���������� �з�����.
	//			//		moveX += moveValue;
	//			//	}
	//			//}
	//			////�̴ϸ��� �������ݿ� ���������� �̴ϸ� ������ �÷��̾ �������� �����δ�.
	//			//else
	//			//{
	//			//	miniMoveX -= moveValue;
	//			//}
	//		}
	//		if (KEYMANAGER->isStayKeyDown('D'))
	//		{
	//			angle += 90 * _timeDelta;
	//
	//			////�̴ϸ��� ���ݿ� �������� ��������(����������)
	//			//if (moveX > -miniWidth * 3 / 2)
	//			//{
	//			//	//�̴ϸʿ��� ���ʿ� ��ġ�ϰ� �������
	//			//	//����������� �̴ϸʳ����� �÷��̾� ��ġ�� �̴ϸ� ���ݿ� �������� ���ߴٸ�
	//			//	if (miniMoveX <= 0)
	//			//	{
	//			//		//�̴ϸ� ������ �÷��̾ ���������� �����δ�.
	//			//		miniMoveX += moveValue;
	//			//	}
	//			//	//�̴ϸʳ��� �÷��̾ �̴ϸ� �߽ɺο� ��ġ�Ѵٸ�
	//			//	else
	//			//	{
	//			//		//�̴ϸ��� �������� �о��.
	//			//		moveX -= moveValue;
	//			//	}
	//			//}
	//			////�̴ϸ��� ���������ݿ� ���������� �̴ϸ� ������ �÷��̾ ���������� �����δ�.
	//			//else
	//			//{
	//			//	miniMoveX += moveValue;
	//			//}
	//			
	//		}
	//
	//
	//		//���� ����ŭ ȸ�����
	//		D3DXMATRIXA16 matRot;
	//		D3DXMatrixRotationY(&matRot, angle);
	//
	//		//ȸ���� ���̱��� �繰�� �������
	//		D3DXVECTOR3 moveDir(0, 0, 1);
	//		//������⿡ ȸ������� �ֱ�
	//		D3DXVec3TransformNormal(&moveDir, &moveDir, &matRot);
	//
	//		//�̵����� �̵��� * �������
	//		D3DXVECTOR3 moveVector = moveDir * moveValue;
	//
	//		if(KEYMANAGER->isStayKeyDown('W'))
	//		{
	//		/*	DXIMG_MANAGER->GetDxImg("minimap3")->SetPosition(D3DXVECTOR3(DXIMG_MANAGER->GetDxImg("minimap3")->GetPosition().x + moveValue * cosf(D3DXToRadian(angle-90)),
	//																		   DXIMG_MANAGER->GetDxImg("minimap3")->GetPosition().y + moveValue * sinf(D3DXToRadian(angle-90)), 0));*/
	//			moveY += moveValue;
	//
	//			////�̴ϸ��� ���ݿ� �������� ��������(��������)
	//			//if (moveY < miniHeight * 3 / 2)
	//			//{
	//			//	//�̴ϸʳ����� �÷��̾� ��ġ�� �̴ϸ� ���ݿ� �������� ���ߴٸ� 
	//			//	if (miniMoveY >= 0)
	//			//	{
	//			//		//�̴ϸ� ������ �÷��̾ �Ʒ��� �����δ�.
	//			//		miniMoveY -= moveValue;
	//			//	}
	//			//	else
	//			//	{
	//			//	//�̴ϸ��� ���� �����δ�.
	//			//		moveY += moveValue;
	//			//	}
	//			//}
	//			////�̴ϸ��� �������ݿ� ���������� �̴ϸ� ������ �÷��̾ �����δ�.
	//			//else
	//			//{
	//			//	miniMoveY-= moveValue;
	//			//}
	//		}
	//		if (KEYMANAGER->isStayKeyDown('S'))
	//		{
	//			////�̴ϸ��� ���ݿ� �������� ��������(�Ʒ�������)
	//			//if (moveY > -miniHeight * 3 / 2)
	//			//{
	//			//	//�̴ϸʳ����� �÷��̾� ��ġ�� �̴ϸ� ���ݿ� �������� ���ߴٸ� 
	//			//	if (miniMoveY <= 0)
	//			//	{
	//			//		//�̴ϸ� ������ �÷��̾ �Ʒ��� �����δ�.
	//			//		miniMoveY += moveValue;
	//			//	}
	//			//	else
	//			//	{
	//			//	//�̴ϸ��� �Ʒ��� �����δ�.
	//			//		moveY -= moveValue;
	//			//	}
	//			//}
	//			////�̴ϸ��� �Ʒ������ݿ� ���������� �̴ϸ� ������ �÷��̾ �����δ�.
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
	//�÷��̾� ����
	_player.render();

	//������ų ���� �ʱ�ȭ(������ ����Ʈ Ŭ�����ȿ� ������� ����)
	//�����ų lightMatrix
	D3DXMATRIXA16 matLights[10];
	for (int i = 0; i < _lights.size(); i++)
	{
		matLights[i] = _lights[i]->getLightMatrix();
	}
	//���̴��� ����Ʈ ����
	xMeshStatic::_staticMeshEffect->SetMatrixArray("matLights", matLights, 10);
	xMeshStatic::_staticMeshEffect->SetInt("LightNum", _lights.size());
	//xMeshStatic::setCamera => ���̴��ȿ� ���������ǰ�, ������ġ�� ��������� �Ѵ�
	xMeshStatic::setCamera(&_mainCamera);




	_terrain->render(&_mainCamera, _baseLight);

	GIZMOMANAGER->LineAxis();

	DXIMG_MANAGER->render("minimap3", miniX, miniY, miniWidth, miniHeight,
						  moveX,
						  moveY);

	//DXIMG_MANAGER->render("radar");
	DXIMG_MANAGER->GetDxImg("radar")->render(0, 0, angle);


	DXIMG_MANAGER->render("miniPlayer");



	//Hit ��ġ�� �������
	//GIZMOMANAGER->WireSphere(_hitPos, 0.5f, RED);


	char str[STR_LEN];
	sprintf(str, "�÷��̾� ��ǥ: [ %f %f ]", _player._transform->GetWorldPosition().x, _player._transform->GetWorldPosition().z);
	FONTMANAGER->fontOut(str, 0, 0, GREEN);

	FONTMANAGER->fontOut("�̴ϸʰ���: " + to_string(DXIMG_MANAGER->GetDxImg("minimap3")->GetSize().fWidth), 100, 20, GREEN);
	FONTMANAGER->fontOut("�̴ϸʼ���" + to_string(DXIMG_MANAGER->GetDxImg("minimap3")->GetSize().fHeight), 100, 40, GREEN);

	FONTMANAGER->fontOut("ī�޶� ��ġx: " + to_string(_mainCamera.GetWorldPosition().x), 100, 60, GREEN);
	FONTMANAGER->fontOut("ī�޶� ��ġy: " + to_string(_mainCamera.GetWorldPosition().y), 100, 80, GREEN);
	FONTMANAGER->fontOut("ī�޶� ��ġz: " + to_string(_mainCamera.GetWorldPosition().z), 100, 100, GREEN);

	FONTMANAGER->fontOut("ī�޶� ȸ��x: " + to_string(_mainCamera.GetAngleX()), 100, 160, GREEN);
	FONTMANAGER->fontOut("ī�޶� ȸ��y: " + to_string(_mainCamera.GetAngleY()), 100, 180, GREEN);

	FONTMANAGER->fontOut("�̴ϸʹ���Y: " + to_string(moveY), 100, 200, GREEN);
	FONTMANAGER->fontOut("�̴ϸʹ̴Ϲ���Y: " + to_string(miniMoveY), 100, 220, GREEN);

	FONTMANAGER->fontOut("3�������Ӹʱ���: " + to_string(_terrain->GetTerrainSizeX()), 100, 240, GREEN);
	FONTMANAGER->fontOut("�̴ϸʰ��ӱ���: " + to_string(DXIMG_MANAGER->GetDxImg("minimap3")->GetSize().fWidth), 100, 260, GREEN);

	FONTMANAGER->fontOut("����: " + to_string(angle), 100, 280, GREEN);

}
