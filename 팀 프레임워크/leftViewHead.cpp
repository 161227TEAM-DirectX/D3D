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

leftViewHead::leftViewHead()
	: m_eHeightType(eHeightType::E_NONE)
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
	co = 0;
	//ȯ���
	_environment = new Environment;
	_environment->init();

	//������Ʈ
	_mapObject = new mapObject;
	_mapObject->objectinit();

	_waterTerrain = new WaterTerrain;
	_waterTerrain->init(3.0f, 100);

	//����
	_terrain = new terrain(FILEPATH_MANAGER->GetFilepath("FX_�����⺻"));
	_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("���̸�_3"));
	_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_1"));
	_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_2"));
	_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_3"));
	_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_4"));
	_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("���÷�_1"));
	_terrain->setBrushmap(FILEPATH_MANAGER->GetFilepath("�귯��_brush01"));
	_terrain->setting();


	//�浹����, ī�޶�
	_hitPos = D3DXVECTOR3(0, 0, 0);
	_mainCamera.SetWorldPosition(0.0f, 0.0f, 0.0f);

	mapRotation = D3DXToRadian(180);

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
	this->Load();				//������ �ε�
	this->terrainUpdate();
	this->PickUdate();

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
				co++;
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
					co--;
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
				//�����̶� �����̶� �浹
				//_terrainSc->isIntersectRay(&_hitPos, &ray);
				//���� ���̱�
				//_terrainSc->setHeight(_hitPos.x, _hitPos.z, 1.0f);
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
				//�����̶� �����̶� �浹
				//_terrainSc->isIntersectRay(&_hitPos, &ray);
				//���� ������
				//_terrainSc->setHeight(_hitPos.x, _hitPos.z, -1.0f);
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
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_1"));
		break;
	case 2:
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_2"));
		break;
	case 3:
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_3"));
		break;
	case 4:
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_4"));
		break;
	case 5:
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_5"));
		break;
	case 6:
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_6"));
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
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_7"));
		break;
	case 2:
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_8"));
		break;
	case 3:
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_9"));
		break;
	case 4:
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_10"));
		break;
	case 5:
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_11"));
		break;
	case 6:
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_12"));
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
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_13"));
		break;
	case 2:
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_14"));
		break;
	case 3:
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_15"));
		break;
	case 4:
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_16"));
		break;
	case 5:
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_17"));
		break;
	case 6:
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_18"));
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
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_19"));
		break;
	case 2:
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_20"));
		break;
	case 3:
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_21"));
		break;
	case 4:
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_22"));
		break;
	case 5:
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_23"));
		break;
	case 6:
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("Ÿ�ϸ�_24"));
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
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("���÷�_1"));
		break;
	case 2:
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("���÷�_2"));
		break;
	case 3:
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("���÷�_3"));
		break;
	case 4:
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("���÷�_4"));
		break;
	case 5:
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("���÷�_5"));
		break;
	case 6:
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("���÷�_6"));
		break;
	}

	if (_rightView->GetGSboolSplate())
	{
		//_rightView->SetGSnumberSplate(false);
		//_terrain->setting();
	}

	//RAW
	switch (_rightView->GetGSnumberRaw())
	{
	case 1:
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("���̸�_1"));
		break;
	case 2:
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("���̸�_2"));
		break;
	case 3:
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("���̸�_3"));
		break;
	case 4:
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("���̸�_4"));
		break;
	case 5:
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("���̸�_5"));
		break;
	case 6:
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("���̸�_6"));
		break;
	}

	if (_rightView->GetGSboolRaw())
	{
		_rightView->SetGSboolRaw(false);
		_terrain->setting();
	}
}

void leftViewHead::Load()
{
	if(KEYMANAGER->isOnceKeyDown('M'))
	{
		//�ʿ� ���� save
		//���ͷ� ���� temp����
		vector<tagSaveMap> InfoTemp;
		tagSaveMap temp;

		temp.infoName = "ȯ���";
		temp.number = _rightView->getNumberEnv();
		temp.mapHeight = 0;
		InfoTemp.push_back(temp);

		temp.infoName = "�����";
		temp.number = _rightView->getnumberwater();
		temp.mapHeight = 0;
		InfoTemp.push_back(temp);

		temp.infoName = "RAW��";
		temp.number = _rightView->GetGSnumberRaw();
		temp.mapHeight = 0;
		InfoTemp.push_back(temp);

		temp.infoName = "Ÿ�ϸ�1";
		temp.number = _rightView->GetGSnumberTile1();
		temp.mapHeight = 0;
		InfoTemp.push_back(temp);

		temp.infoName = "Ÿ�ϸ�2";
		temp.number = _rightView->GetGSnumberTile2();
		temp.mapHeight = 0;
		InfoTemp.push_back(temp);

		temp.infoName = "Ÿ�ϸ�3";
		temp.number = _rightView->GetGSnumberTile3();
		temp.mapHeight = 0;
		InfoTemp.push_back(temp);

		temp.infoName = "Ÿ�ϸ�4";
		temp.number = _rightView->GetGSnumberTile4();
		temp.mapHeight = 0;
		InfoTemp.push_back(temp);

		temp.infoName = "���÷�";
		temp.number = _rightView->GetGSnumberSplate();
		temp.mapHeight = 0;
		InfoTemp.push_back(temp);

		IOSAVEMANAGER->saveFile("���̺��", InfoTemp);

		//����� ���� ������ ���ܼ� �̸��� �ٽ� 1������ ���ڽ����ش�
		for (int i = 0; i < InfoObjectTemp.size(); i++)
		{
			InfoObjectTemp[i].infoName = "�ѹ�" + to_string(i+1);
		}

		IOSAVEOBJECTMANAGER->saveFile("������Ʈ", InfoObjectTemp);

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


	if(_rightView->getnumberwater() != 0)
	{
		_waterTerrain->render(_rightView->getnumberwater());
	}

	if(_rightView->getNumberEnv() != 0)
	{
		_environment->renderEnvironment(_rightView->getNumberEnv());
	}

	//������Ʈ ����
	if(!m_vecObject.empty()) _mapObject->objectRenderTool(m_vecObject, &_mainCamera);

	//���� ����
	_terrain->render(&_mainCamera, _sceneBaseDirectionLight);

	FONTMANAGER->fontOut(to_string(co), 100, 100, D3DCOLOR_XRGB(255, 255, 255));
	
	switch(m_eHeightType)
	{
	case eHeightType::E_NONE:
		FONTMANAGER->fontOut("�����:", 0, 200, BLACK);
		break;
	case eHeightType::E_UP:
		FONTMANAGER->fontOut("�ø���!:", 0, 200, BLACK);
		break;
	case eHeightType::E_DOWN:
		FONTMANAGER->fontOut("������!:", 0, 200, BLACK);
		break;
	}
}
