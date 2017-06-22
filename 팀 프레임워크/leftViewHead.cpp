#include "stdafx.h"
#include "leftViewHead.h"
//
#include "terrain.h"
#include "terrainSc.h"
#include "Environment.h"
#include "mapObject.h"
#include "WaterTerrain.h"
//
#include "rightView.h"		//��ȣ���� Ŭ����

#include "monster.h"

leftViewHead::leftViewHead()
	: m_eHeightType(eHeightType::E_NONE), sour(-1), dest(-1)
{
	//�⺻ ���� ����
	_sceneBaseDirectionLight = new lightDirection;
	//�⺻ ��
	_sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	_sceneBaseDirectionLight->_intensity = 1.0f;
}


leftViewHead::~leftViewHead()
{
	//���⼺ ������ ī�޶� ����
	SAFE_DELETE(this->_sceneBaseDirectionLight);
}

HRESULT leftViewHead::init()
{

	//ȯ���
	_environment = new Environment;
	_environment->init();
	_environment->linkCamera(_mainCamera);

	//������Ʈ
	_mapObject = new mapObject;
	_mapObject->objectinit();

	_waterTerrain = new WaterTerrain;
	_waterTerrain->init(3.0f, 100);

	//����
	_terrain = new terrain;
	_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("���̸�_3"));
	_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_4"));
	_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_10"));
	_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_13"));
	_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_23"));
	_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("���÷�_1"));
	_terrain->setHeightscale(10.0f);
	_terrain->setBrushmap(FILEPATH_MANAGER->GetFilepath("�귯��_brush01"));
	_terrain->setBrushScale(1.0f);
	_terrain->setting();

	tile1 = "Ÿ�ϸ�_4";
	tile2 = "Ÿ�ϸ�_10";
	tile3 = "Ÿ�ϸ�_13";
	tile4 = "Ÿ�ϸ�_23";
	splat = "���÷�_1";
	raw = "���̸�_3";

	//�浹����, ī�޶�
	_hitPos = D3DXVECTOR3(0, 0, 0);
	_mainCamera.SetWorldPosition(0.0f, 0.0f, 0.0f);
	_SaveButton.FT = false;

	mapRotation = D3DXToRadian(180);

	loadMonster();

	return S_OK;
}

void leftViewHead::release()
{
	SAFE_DELETE(_terrain);

	//���� ����
	//_terrainSc->release();
	//ȯ�������
	_environment->release();
	//���� ����
	_waterTerrain->release();
}

void leftViewHead::update()
{
	//����Ʈ ����ī�޶� �����̱�
	_mainCamera.DefaultControl(_timeDelta,1);
	_mainCamera.updateMatrix();
	_mainCamera.updateCamToDevice();

	//���콺 ����Ʈ ��������
	_ptMousePos = GetMousePos();

	//������Ʈ �κ�
	this->save();				//������ �ε�
	this->terrainUpdate();
	this->PickUdate();
	this->monsterMaptul();

	//���� ������Ʈ �κ�
	for (int i = 0; i < _monster.size(); i++)
	{
		_monster[i]->update();
	}

	_environment->update();
}

void leftViewHead::PickUdate()
{
	//���ʻ�����丸ŭ�ϋ��� ������Ʈ�� �ȴ�.
	if(_ptMousePos.x < leftViewPort.X + leftViewPort.Width && _ptMousePos.x >= 0)
	{
		if(_rightView->getnumberObject() != 0)
		{
			if(KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				float scale;
				baseObject* temp = new baseObject;
				D3DXMATRIX mapRotate;
				D3DXVECTOR2 _screenPos(_ptMousePos.x, _ptMousePos.y);

				scale = 0.3f;

				_mainCamera.computeRay(&ray, &_screenPos, 1);

				_terrain->isIntersectRay(&_hitPos, &ray);
				

				//�ѹ��� , ������Ʈ�� ����
				temp->SetObjectNumber(_rightView->getnumberObject());
				temp->SetObjectRotation(mapRotation);

				//������Ʈ�� �Լ��� �P��.
				_mapObject->objectSet(temp->getObjectNumber(), temp, mapRotate, _hitPos.x, _hitPos.y, _hitPos.z, scale, temp->getObjectRotation());

				//�����س��Ҵ����� push�� �ִ´�
				//�������� ������� ����� y���� ��� 
				temp->_transform->SetWorldPosition(_hitPos.x, _hitPos.y + (-temp->getBoundBox()._localMinPos.y * scale), _hitPos.z);
				m_vecObject.push_back(temp);

				//������Ʈ ���̺� �ϱ����� �� �ֱ�
				ObjecTemp.infoName = "�ѹ�" + to_string(m_vecObject.size());
				ObjecTemp.objectNumber = temp->getObjectNumber();
				ObjecTemp.objectRotate = temp->getObjectRotation();
				ObjecTemp.objectScale = 0.3f;
				ObjecTemp.objectX = temp->_transform->GetWorldPosition().x;
				ObjecTemp.objectY = temp->_transform->GetWorldPosition().y;
				ObjecTemp.objectZ = temp->_transform->GetWorldPosition().z;

				InfoObjectTemp.push_back(ObjecTemp);
			}
		}


		//������Ʈ ����
		if(KEYMANAGER->isOnceKeyDown('H'))
			{
			D3DXVECTOR2 _screenPos(_ptMousePos.x, _ptMousePos.y);
			_mainCamera.computeRay(&ray, &_screenPos, 1);

			for(int i = 0; i < m_vecObject.size(); i++)
			{
				if(PHYSICSMANAGER->isRayHitStaticMeshObject(&ray, m_vecObject[i], &_hitPos, NULL))
				{
					//������Ʈ ����
					m_vecObject.erase(m_vecObject.begin() + i);
					//������Ʈ ���̺� ����
					InfoObjectTemp.erase(InfoObjectTemp.begin() + i);
				}
			}
		}
	}

	//���� �����ϴ� Ű�Է�
	if(KEYMANAGER->isOnceKeyDown('C'))
	{
		if(mapRotation > D3DXToRadian(360))
		{
			mapRotation = D3DXToRadian(0);
		}
		else
		{
			mapRotation += D3DXToRadian(45);
		}
	}

	if(KEYMANAGER->isOnceKeyDown('V'))
	{
		if(mapRotation < D3DXToRadian(0))
		{
			mapRotation = D3DXToRadian(360);
		}
		else
		{
			mapRotation -= D3DXToRadian(45);
		}
	}
}

void leftViewHead::terrainUpdate()
{
	this->terrainTextureUpate();

	if(_ptMousePos.x < leftViewPort.X + leftViewPort.Width && _ptMousePos.x >= 0)
	{
		//���̰� �����ϴ� ���¸�...
		if (m_eHeightType != eHeightType::E_NONE)
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				_terrain->isIntersectRay(&_hitPos, &ray);
				_terrain->changeHeightTerrain(_hitPos.x, _hitPos.z);
			}
			if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
			{
				m_eHeightType = eHeightType::E_NONE;
				_terrain->_nHeightSign = 0;
			}
		}


		//������ ���� ������Ʈ
		if(_rightView->getNumberHeight() == 1)
		{
			if(KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				D3DXVECTOR2 _screenPos(_ptMousePos.x, _ptMousePos.y);
				_mainCamera.computeRay(&ray, &_screenPos, 1);
				
				m_eHeightType = eHeightType::E_UP;
				_terrain->_nHeightSign = 1;
			}
		}
		if(_rightView->getNumberHeight() == 2)
		{
			if(KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				D3DXVECTOR2 _screenPos(_ptMousePos.x, _ptMousePos.y);
				_mainCamera.computeRay(&ray, &_screenPos, 1);
				
				m_eHeightType = eHeightType::E_DOWN;
				_terrain->_nHeightSign = -1;
			}
		}
	}

	if(_rightView->getnumberwater() != 0)
	{
		_waterTerrain->update(_rightView->getnumberwater());
	}
}

void leftViewHead::terrainTextureUpate()
{
	//Ÿ�ϸ�1
	switch (_rightView->GetGSnumberTile1())
	{
	case 1:
		tile1 = "Ÿ�ϸ�_1";
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath(tile1));
		break;
	case 2:
		tile1 = "Ÿ�ϸ�_2";
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath(tile1));
		break;
	case 3:
		tile1 = "Ÿ�ϸ�_3";
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath(tile1));
		break;
	case 4:
		tile1 = "Ÿ�ϸ�_4";
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath(tile1));
		break;
	case 5:
		tile1 = "Ÿ�ϸ�_5";
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath(tile1));
		break;
	case 6:
		tile1 = "Ÿ�ϸ�_6";
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath(tile1));
		break;
	}

	if (_rightView->GetGSboolTile1())
	{
		_rightView->SetGSboolTile1(false);
		_terrain->setting();
	}

	//Ÿ�ϸ�2
	switch (_rightView->GetGSnumberTile2())
	{
	case 1:
		tile2 = "Ÿ�ϸ�_7";
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath(tile2));
		break;
	case 2:
		tile2 = "Ÿ�ϸ�_8";
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath(tile2));
		break;
	case 3:
		tile2 = "Ÿ�ϸ�_9";
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath(tile2));
		break;
	case 4:
		tile2 = "Ÿ�ϸ�_10";
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath(tile2));
		break;
	case 5:
		tile2 = "Ÿ�ϸ�_11";
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath(tile2));
		break;
	case 6:
		tile2 = "Ÿ�ϸ�_12";
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath(tile2));
		break;
	}

	if (_rightView->GetGSboolTile2())
	{
		_rightView->SetGSboolTile2(false);
		_terrain->setting();
	}

	//Ÿ�ϸ�3
	switch (_rightView->GetGSnumberTile3())
	{
	case 1:
		tile3 = "Ÿ�ϸ�_13";
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath(tile3));
		break;
	case 2:
		tile3 = "Ÿ�ϸ�_14";
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath(tile3));
		break;
	case 3:
		tile3 = "Ÿ�ϸ�_15";
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath(tile3));
		break;
	case 4:
		tile3 = "Ÿ�ϸ�_16";
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath(tile3));
		break;
	case 5:
		tile3 = "Ÿ�ϸ�_17";
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath(tile3));
		break;
	case 6:
		tile3 = "Ÿ�ϸ�_18";
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath(tile3));
		break;
	}

	if (_rightView->GetGSboolTile3())
	{
		_rightView->SetGSboolTile3(false);
		_terrain->setting();
	}

	//Ÿ�ϸ�4
	switch (_rightView->GetGSnumberTile4())
	{
	case 1:
		tile4 = "Ÿ�ϸ�_19";
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath(tile4));
		break;
	case 2:
		tile4 = "Ÿ�ϸ�_20";
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath(tile4));
		break;
	case 3:
		tile4 = "Ÿ�ϸ�_21";
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath(tile4));
		break;
	case 4:
		tile4 = "Ÿ�ϸ�_22";
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath(tile4));
		break;
	case 5:
		tile4 = "Ÿ�ϸ�_23";
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath(tile4));
		break;
	case 6:
		tile4 = "Ÿ�ϸ�_24";
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath(tile4));
		break;
	}

	if (_rightView->GetGSboolTile4())
	{
		_rightView->SetGSboolTile4(false);
		_terrain->setting();
	}

	//slpate��
	switch (_rightView->GetGSnumberSplate())
	{
	case 1:
		splat = "���÷�_1";
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath(splat));
		break;
	case 2:
		splat = "���÷�_2";
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath(splat));
		break;
	case 3:
		splat = "���÷�_3";
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath(splat));
		break;
	case 4:
		splat = "���÷�_4";
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath(splat));
		break;
	case 5:
		splat = "���÷�_5";
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath(splat));
		break;
	case 6:
		splat = "���÷�_6";
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath(splat));
		break;
	}

	//RAW
	switch (_rightView->GetGSnumberRaw())
	{
	case 1:
		raw = "���̸�_1";
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath(raw));
		break;
	case 2:
		raw = "���̸�_2";
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath(raw));
		break;
	case 3:
		raw = "���̸�_3";
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath(raw));
		break;
	case 4:
		raw = "���̸�_4";
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath(raw));
		break;
	case 5:
		raw = "���̸�_5";
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath(raw));
		break;
	case 6:
		raw = "���̸�_6";
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath(raw));
		break;
	}

	if (_rightView->GetGSboolRaw())
	{
		_rightView->SetGSboolRaw(false);
		_terrain->setting();
	}
}

void leftViewHead::monsterMaptul()
{
	if (_ptMousePos.x < leftViewPort.X + leftViewPort.Width && _ptMousePos.x >= 0)
	{
		//�������
		switch (_rightView->GetGSnumberNodeInstal())
		{
		case 1:
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				D3DXVECTOR2 _screenPos(_ptMousePos.x, _ptMousePos.y);
				_mainCamera.computeRay(&ray, &_screenPos, 1);

				_terrain->isIntersectRay(&_hitPos, &ray);
				_terrain->getDijkstra().addNode(_hitPos);
			}
		}
			break;
		}

		//��� ����
		switch (_rightView->GetGSnumberNodelink())
		{
		case 1:
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				const vector<Node*>& temp = _terrain->getDijkstra().getVecNode();

				D3DXVECTOR2 _screenPos(_ptMousePos.x, _ptMousePos.y);
				_mainCamera.computeRay(&ray, &_screenPos, 1);

				_terrain->isIntersectRay(&_hitPos, &ray);
				for (int i = 0; i < temp.size(); i++)
				{
					if (PHYSICSMANAGER->isRayHitSphere(&ray, &temp[i]->getPosition(), temp[i]->getRadius(), nullptr, nullptr))
					{
						if (sour == -1) sour = i;
						else if (dest == -1)
						{
							dest = i;
							_terrain->getDijkstra().connectNode(sour, dest);
						}
					}
				}
			}
		}
		break;

		}

		switch (_rightView->GetGSnumberMonster())
		{
		case 1:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("��",1);
			break;
		case 2:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("��",2);
			break;
		case 3:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("�����",3);
			break;
		case 4:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("��������",4);
			break;
		case 5:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("���Ż�罺",5);
			break;
		case 6:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("�����",6);
			break;
		case 7:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("��",7);
			break;
		case 8:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("�Ǿ�",8);
			break;													  
		case 9:														  
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("��",9);
			break;													  
		case 10:													  
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("�Ұ���",10);
			break;													  
		case 11:													  
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("����",11);
			break;													  
		case 12:													  
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("����",12);
			break;													  
		case 13:													  
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("����",13);
			break;													  
		case 14:													  
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("������",14);
			break;
		}


	}


}

void leftViewHead::save()
{
	if (PtInRect(&_SaveButton.rc2, GetMousePos()))
	{
		_SaveButton.FT = true;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			//�ʿ� ���� save
			//���ͷ� ���� temp����
			//vector<tagSaveMap> InfoTemp;
			//tagSaveMap temp;

			//temp.infoName = "ȯ���";
			//temp.number = _rightView->getNumberEnv();
			//temp.mapHeight = 0;
			//InfoTemp.push_back(temp);

			//temp.infoName = "�����";
			//temp.number = _rightView->getnumberwater();
			//temp.mapHeight = 0;
			//InfoTemp.push_back(temp);

			//IOSAVEMANAGER->saveFile("���̺��", InfoTemp);

			////����� ���� ������ ���ܼ� �̸��� �ٽ� 1������ ���ڽ����ش�
			//for (int i = 0; i < InfoObjectTemp.size(); i++)
			//{
			//	InfoObjectTemp[i].infoName = "�ѹ�" + to_string(i + 1);
			//}

			//IOSAVEOBJECTMANAGER->saveFile("������Ʈ", InfoObjectTemp);

			//ST_MAP temp0;

			//temp0.heightMap = FILEPATH_MANAGER->GetFilepath(raw);
			//temp0.splat = FILEPATH_MANAGER->GetFilepath(splat);
			//temp0.tile0 = FILEPATH_MANAGER->GetFilepath(tile1);
			//temp0.tile1 = FILEPATH_MANAGER->GetFilepath(tile2);
			//temp0.tile2 = FILEPATH_MANAGER->GetFilepath(tile3);
			//temp0.tile3 = FILEPATH_MANAGER->GetFilepath(tile4);

			//temp0.vecPos = _terrain->getMapPosition();

			//IOMAPMANAGER->saveFile("����0", temp0);

			//���� ��ġ ,�� ����/////////////////////////////////
			vector<tagSaveMonster> monsterTemp;
			tagSaveMonster Mtemp;

			if (_monster.size() != 0)
			{
				for (int i = 0; i < _monster.size(); i++)
				{
					Mtemp.infoName = "���ͳѹ�" + to_string(i + 1);
					Mtemp.monsterNumber = _monster[i]->getObjectNumber();
					Mtemp.monsterX = _monster[i]->_transform->GetWorldPosition().x;
					Mtemp.monsterY = _monster[i]->_transform->GetWorldPosition().y;
					Mtemp.monsterZ = _monster[i]->_transform->GetWorldPosition().z;
					Mtemp.scale = 1.0f;

					monsterTemp.push_back(Mtemp);
				}

				IOSAVEMONSTERMANAGER->saveFile("����", monsterTemp);
			}

			//������� ,��ġ,�� ����////////////////////////////
			vector<tagSaveNode> nodeTemp;
			tagSaveNode nTemp;

			for (int i = 0; i < _terrain->getDijkstra().getVecNode().size(); i++)
			{
				nTemp.infoName = "���" + to_string(i + 1);
				nTemp.Inumber = i; // ������ �ε����� ����
				nTemp.nodeX = _terrain->getDijkstra().getVecNode()[i]->getPosition().x;//��ġ�� ����
				nTemp.nodeY = _terrain->getDijkstra().getVecNode()[i]->getPosition().y;//��ġ�� ����
				nTemp.nodeZ = _terrain->getDijkstra().getVecNode()[i]->getPosition().z;//��ġ�� ����

				for (int j = 0; j < _terrain->getDijkstra().getadjNode()[i].size(); j++)
				{
					nTemp.nodeFS.push_back(make_pair(_terrain->getDijkstra().getadjNode()[i][j].first, _terrain->getDijkstra().getadjNode()[i][j].second)); 	//first�� ���Ϳ��� ��� ��������� �˷��ش�.	
																																								//second�� ���� ��忡�� j�������� �Ÿ����� ������.
				}

				nodeTemp.push_back(nTemp);
			}

			IOSAVENODEMANAGER->saveFile("���", nodeTemp);
		}

	}
	else
	{
		_SaveButton.FT = false;
	}
}

void leftViewHead::render()
{
	//������ �ʹ��� UI
	_leftView.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/���ʸ���.png");
	SPRITEMANAGER->renderRectTexture(_leftView.tex, &_leftView.rc1, &_leftView.rc2, 0, 0, 2048, 1024, leftViewPort.X, leftViewPort.Y);

	char str[128];
	sprintf_s(str, "%.0f", D3DXToDegree(mapRotation));
	FONTMANAGER->fontOut(str, leftViewPort.X + 1085, leftViewPort.Y + 22, D3DCOLOR_XRGB(255, 255, 255));

	//save��ư
	switch (_SaveButton.FT)
	{
	case true:
		_SaveButton.rc2 = { 1050,860,_SaveButton.rc2.left + 95,_SaveButton.rc2.top + 37 };
		_SaveButton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/SAVE.png");
		SPRITEMANAGER->renderRectTexture(_SaveButton.tex, &_SaveButton.rc1, &_SaveButton.rc2, 0, 0, 256, 37, leftViewPort.X + 1050, leftViewPort.Y + 860);
		break;

	case false:
		_SaveButton.rc2 = {1050,860,_SaveButton.rc2.left + 95,_SaveButton.rc2.top + 37 };
		_SaveButton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/SAVE.png");
		SPRITEMANAGER->renderRectTexture(_SaveButton.tex, &_SaveButton.rc1, &_SaveButton.rc2, 0, 37, 256,74, leftViewPort.X + 1050, leftViewPort.Y + 860);
		break;
	}

	//���� ����
	_terrain->render(&_mainCamera, _sceneBaseDirectionLight);

	//������Ʈ ����
	if (!m_vecObject.empty()) _mapObject->objectRenderTool(m_vecObject, &_mainCamera, _sceneBaseDirectionLight);

	xMeshSkinned::setCamera(&_mainCamera);
	xMeshSkinned::setTechniqueName("Toon");
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resource/Testures/Ramp_1.png"));
	xMeshSkinned::setBaseLight(this->_sceneBaseDirectionLight);

	//���� ����
	for (int i = 0; i < _monster.size(); i++)
	{
		_monster[i]->render();
	}

	if (_rightView->getnumberwater() != 0)
	{
		_waterTerrain->render(_rightView->getnumberwater());
	}

	if (_rightView->getNumberEnv() != 0)
	{
		_environment->renderEnvironment(_rightView->getNumberEnv());
	}

	const vector<Node*>& temp = _terrain->getDijkstra().getVecNode();
	for (int i = 0; i < temp.size(); i++)
	{
		temp[i]->Render();
	}

	//���ͽ�Ʈ�� ��� �׸���
	_terrain->getDijkstra().render();

	FONTMANAGER->fontOut(to_string(_rightView->getnumberObject()), 100, 100, D3DCOLOR_XRGB(255,255,255));

}

void leftViewHead::monsterSelect(string str ,int monsterNumber)
{
	//D3DXMATRIX matRotate;
	//D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));

	monster* temp = new monster(&_mainCamera);
	temp->_transform->SetScale(1.0f, 1.0f, 1.0f);

	D3DXVECTOR2 _screenPos(_ptMousePos.x, _ptMousePos.y);
	_mainCamera.computeRay(&ray, &_screenPos, 1);

	_terrain->isIntersectRay(&_hitPos, &ray);

	temp->_transform->SetWorldPosition(_hitPos);
	temp->setRegenPosition(_hitPos);
	temp->setMesh(XMESH_MANAGER->GetXmeshSkinned(str));
	temp->setActive(true);
	temp->SetObjectNumber(monsterNumber);
	_monster.push_back(temp);
}

void leftViewHead::loadMonsterAndNode(void)
{

}

void leftViewHead::loadMonster(void)
{
	IOSAVEMONSTERMANAGER->loadFile("����");
	vector<tagSaveMonster> temp;
	tagSaveMonster tagMTemp;

	for (int i = 0; i < IOSAVEMONSTERMANAGER->getCount(); i++)
	{
		tagMTemp = IOSAVEMONSTERMANAGER->findTag("���ͳѹ�" + to_string(i + 1));

		temp.push_back(tagMTemp);
	}
	
	for (int i = 0; i < temp.size(); i++)
	{
		D3DXMATRIX matRotate;
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));

		monster* tempMonster = new monster(&_mainCamera);
		tempMonster->_transform->SetScale(temp[i].scale, temp[i].scale, temp[i].scale);
		tempMonster->_transform->SetWorldPosition(temp[i].monsterX, temp[i].monsterY, temp[i].monsterZ);
		tempMonster->setRegenPosition(temp[i].monsterX, temp[i].monsterY, temp[i].monsterZ);
		tempMonster->setMesh(findMonster(temp[i].monsterNumber));
		tempMonster->setActive(true);
		tempMonster->SetObjectNumber(temp[i].monsterNumber);
		_monster.push_back(tempMonster);
	}
}

xMesh * leftViewHead::findMonster(int & index)
{
	switch (index)
	{
	case 1:
		return XMESH_MANAGER->GetXmeshSkinned("��");
	case 2:
		return XMESH_MANAGER->GetXmeshSkinned("��");
		break;
	case 3:
		return XMESH_MANAGER->GetXmeshSkinned("�����");
		break;
	case 4:
		return XMESH_MANAGER->GetXmeshSkinned("��������");
		break;
	case 5:
		return XMESH_MANAGER->GetXmeshSkinned("���Ż�罺");
		break;
	case 6:
		return XMESH_MANAGER->GetXmeshSkinned("�����");
		break;
	case 7:
		return XMESH_MANAGER->GetXmeshSkinned("��");
		break;
	case 8:
		return XMESH_MANAGER->GetXmeshSkinned("�Ǿ�");
		break;
	case 9:
		return XMESH_MANAGER->GetXmeshSkinned("��");
		break;
	case 10:
		return XMESH_MANAGER->GetXmeshSkinned("�Ұ���");
		break;
	case 11:
		return XMESH_MANAGER->GetXmeshSkinned("����");
		break;
	case 12:
		return XMESH_MANAGER->GetXmeshSkinned("����");
		break;
	case 13:
		return XMESH_MANAGER->GetXmeshSkinned("����");
		break;
	case 14:
		return XMESH_MANAGER->GetXmeshSkinned("������");
		break;
	}
}

void leftViewHead::loadNode(void)
{
}
