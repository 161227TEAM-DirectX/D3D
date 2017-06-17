#include "stdafx.h"
#include "leftViewHead.h"
//
#include "terrain.h"
#include "terrainSc.h"
#include "Environment.h"
#include "mapObject.h"
#include "WaterTerrain.h"
//
#include "rightView.h"		//상호참조 클래스

leftViewHead::leftViewHead()
	: m_eHeightType(eHeightType::E_NONE)
{
	//기본 광원 생성
	_sceneBaseDirectionLight = new lightDirection;
	//기본 값
	_sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	_sceneBaseDirectionLight->_intensity = 1.0f;
}


leftViewHead::~leftViewHead()
{
	//방향성 광원과 카메라 해제
	SAFE_DELETE(this->_sceneBaseDirectionLight);
}

HRESULT leftViewHead::init()
{
	co = 0;
	//환경맵
	_environment = new Environment;
	_environment->init();

	//오브젝트
	_mapObject = new mapObject;
	_mapObject->objectinit();

	_waterTerrain = new WaterTerrain;
	_waterTerrain->init(3.0f, 100);

	//지형
	_terrain = new terrain(FILEPATH_MANAGER->GetFilepath("FX_지형기본"));
	_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("높이맵_3"));
	_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("타일맵_1"));
	_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("타일맵_2"));
	_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("타일맵_3"));
	_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("타일맵_4"));
	_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("스플랫_1"));
	_terrain->setBrushmap(FILEPATH_MANAGER->GetFilepath("브러쉬_brush01"));
	_terrain->setting();


	//충돌지역, 카메라
	_hitPos = D3DXVECTOR3(0, 0, 0);
	_mainCamera.SetWorldPosition(0.0f, 0.0f, 0.0f);

	mapRotation = D3DXToRadian(180);

	return S_OK;
}

void leftViewHead::release()
{
	SAFE_DELETE(_terrain);

	//지형 해제
	//_terrainSc->release();
	//환경맵해제
	_environment->release();
	//물결 해제
	_waterTerrain->release();
}

void leftViewHead::update()
{
	//레프트 메인카메라 움직이기
	_mainCamera.DefaultControl(_timeDelta,1);
	_mainCamera.updateMatrix();
	_mainCamera.updateCamToDevice();

	//마우스 포인트 가져오기
	_ptMousePos = GetMousePos();

	//업데이트 부분
	this->Load();				//데이터 로드
	this->terrainUpdate();
	this->PickUdate();

	_environment->update();
}

void leftViewHead::PickUdate()
{
	//왼쪽사이즈뷰만큼일떄만 업데이트가 된다.
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
				

				//넘버값 , 로테이트값 저장
				temp->SetObjectNumber(_rightView->getnumberObject());
				temp->SetObjectRotation(mapRotation);

				//오브젝트를 함수로 뻇음.
				_mapObject->objectSet(temp->getObjectNumber(), temp, mapRotate, _hitPos.x, _hitPos.y, _hitPos.z, scale, temp->getObjectRotation());

				//지정해놓았던것을 push로 넣는다
				//스케일을 곱해줘야 제대로 y값에 든다 
				temp->_transform->SetWorldPosition(_hitPos.x, _hitPos.y + (-temp->getBoundBox()._localMinPos.y * scale), _hitPos.z);
				m_vecObject.push_back(temp);

				//오브젝트 세이브 하기전에 값 넣기
				ObjecTemp.infoName = "넘버" + to_string(m_vecObject.size());
				ObjecTemp.objectNumber = temp->getObjectNumber();
				ObjecTemp.objectRotate = temp->getObjectRotation();
				ObjecTemp.objectScale = 0.3f;
				ObjecTemp.objectX = temp->_transform->GetWorldPosition().x;
				ObjecTemp.objectY = temp->_transform->GetWorldPosition().y;
				ObjecTemp.objectZ = temp->_transform->GetWorldPosition().z;

				InfoObjectTemp.push_back(ObjecTemp);
			}
		}


		//오브젝트 삭제
		if(KEYMANAGER->isOnceKeyDown('H'))
			{
			D3DXVECTOR2 _screenPos(_ptMousePos.x, _ptMousePos.y);
			_mainCamera.computeRay(&ray, &_screenPos, 1);

			for(int i = 0; i < m_vecObject.size(); i++)
			{
				if(PHYSICSMANAGER->isRayHitStaticMeshObject(&ray, m_vecObject[i], &_hitPos, NULL))
				{
					co--;
					//오브젝트 삭제
					m_vecObject.erase(m_vecObject.begin() + i);
					//오브젝트 세이브 삭제
					InfoObjectTemp.erase(InfoObjectTemp.begin() + i);
				}
			}
		}
	}

	//각도 조절하는 키입력
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
		//높이값 변경하는 상태면...
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


		//지형맵 높이 업데이트
		if(_rightView->getNumberHeight() == 1)
		{
			if(KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				D3DXVECTOR2 _screenPos(_ptMousePos.x, _ptMousePos.y);
				_mainCamera.computeRay(&ray, &_screenPos, 1);
				
				m_eHeightType = eHeightType::E_UP;
				_terrain->_nHeightSign = 1;
				//지형이랑 광선이랑 충돌
				//_terrainSc->isIntersectRay(&_hitPos, &ray);
				//지형 높이기
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
				//지형이랑 광선이랑 충돌
				//_terrainSc->isIntersectRay(&_hitPos, &ray);
				//지형 내리기
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
	//타일맵1
	switch (_rightView->GetGSnumberTile1())
	{
	case 1:
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("타일맵_1"));
		break;
	case 2:
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("타일맵_2"));
		break;
	case 3:
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("타일맵_3"));
		break;
	case 4:
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("타일맵_4"));
		break;
	case 5:
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("타일맵_5"));
		break;
	case 6:
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("타일맵_6"));
		break;
	}

	if (_rightView->GetGSboolTile1())
	{
		_rightView->SetGSboolTile1(false);
		_terrain->setting();
	}

	//타일맵2
	switch (_rightView->GetGSnumberTile2())
	{
	case 1:
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("타일맵_7"));
		break;
	case 2:
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("타일맵_8"));
		break;
	case 3:
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("타일맵_9"));
		break;
	case 4:
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("타일맵_10"));
		break;
	case 5:
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("타일맵_11"));
		break;
	case 6:
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("타일맵_12"));
		break;
	}

	if (_rightView->GetGSboolTile2())
	{
		_rightView->SetGSboolTile2(false);
		_terrain->setting();
	}

	//타일맵3
	switch (_rightView->GetGSnumberTile3())
	{
	case 1:
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("타일맵_13"));
		break;
	case 2:
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("타일맵_14"));
		break;
	case 3:
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("타일맵_15"));
		break;
	case 4:
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("타일맵_16"));
		break;
	case 5:
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("타일맵_17"));
		break;
	case 6:
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("타일맵_18"));
		break;
	}

	if (_rightView->GetGSboolTile3())
	{
		_rightView->SetGSboolTile3(false);
		_terrain->setting();
	}

	//타일맵4
	switch (_rightView->GetGSnumberTile4())
	{
	case 1:
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("타일맵_19"));
		break;
	case 2:
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("타일맵_20"));
		break;
	case 3:
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("타일맵_21"));
		break;
	case 4:
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("타일맵_22"));
		break;
	case 5:
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("타일맵_23"));
		break;
	case 6:
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("타일맵_24"));
		break;
	}

	if (_rightView->GetGSboolTile4())
	{
		_rightView->SetGSboolTile4(false);
		_terrain->setting();
	}

	//slpate맵
	switch (_rightView->GetGSnumberSplate())
	{
	case 1:
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("스플랫_1"));
		break;
	case 2:
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("스플랫_2"));
		break;
	case 3:
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("스플랫_3"));
		break;
	case 4:
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("스플랫_4"));
		break;
	case 5:
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("스플랫_5"));
		break;
	case 6:
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("스플랫_6"));
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
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("높이맵_1"));
		break;
	case 2:
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("높이맵_2"));
		break;
	case 3:
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("높이맵_3"));
		break;
	case 4:
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("높이맵_4"));
		break;
	case 5:
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("높이맵_5"));
		break;
	case 6:
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("높이맵_6"));
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
		//맵에 관한 save
		//벡터로 담을 temp설정
		vector<tagSaveMap> InfoTemp;
		tagSaveMap temp;

		temp.infoName = "환경맵";
		temp.number = _rightView->getNumberEnv();
		temp.mapHeight = 0;
		InfoTemp.push_back(temp);

		temp.infoName = "물결맵";
		temp.number = _rightView->getnumberwater();
		temp.mapHeight = 0;
		InfoTemp.push_back(temp);

		temp.infoName = "RAW맵";
		temp.number = _rightView->GetGSnumberRaw();
		temp.mapHeight = 0;
		InfoTemp.push_back(temp);

		temp.infoName = "타일맵1";
		temp.number = _rightView->GetGSnumberTile1();
		temp.mapHeight = 0;
		InfoTemp.push_back(temp);

		temp.infoName = "타일맵2";
		temp.number = _rightView->GetGSnumberTile2();
		temp.mapHeight = 0;
		InfoTemp.push_back(temp);

		temp.infoName = "타일맵3";
		temp.number = _rightView->GetGSnumberTile3();
		temp.mapHeight = 0;
		InfoTemp.push_back(temp);

		temp.infoName = "타일맵4";
		temp.number = _rightView->GetGSnumberTile4();
		temp.mapHeight = 0;
		InfoTemp.push_back(temp);

		temp.infoName = "스플랫";
		temp.number = _rightView->GetGSnumberSplate();
		temp.mapHeight = 0;
		InfoTemp.push_back(temp);

		IOSAVEMANAGER->saveFile("세이브맵", InfoTemp);

		//지우고 나서 문제가 생겨서 이름을 다시 1번부터 저자시켜준다
		for (int i = 0; i < InfoObjectTemp.size(); i++)
		{
			InfoObjectTemp[i].infoName = "넘버" + to_string(i+1);
		}

		IOSAVEOBJECTMANAGER->saveFile("오브젝트", InfoObjectTemp);

	}
}

void leftViewHead::render()
{
	//맵지형 맵바탕 UI
	_leftView.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/왼쪽맵툴.png");
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

	//오브젝트 렌더
	if(!m_vecObject.empty()) _mapObject->objectRenderTool(m_vecObject, &_mainCamera);

	//지형 렌더
	_terrain->render(&_mainCamera, _sceneBaseDirectionLight);

	FONTMANAGER->fontOut(to_string(co), 100, 100, D3DCOLOR_XRGB(255, 255, 255));
	
	switch(m_eHeightType)
	{
	case eHeightType::E_NONE:
		FONTMANAGER->fontOut("논상태:", 0, 200, BLACK);
		break;
	case eHeightType::E_UP:
		FONTMANAGER->fontOut("올리자!:", 0, 200, BLACK);
		break;
	case eHeightType::E_DOWN:
		FONTMANAGER->fontOut("내리자!:", 0, 200, BLACK);
		break;
	}
}
