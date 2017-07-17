#include "stdafx.h"
#include "leftViewHead.h"
#include "terrain.h"
#include "terrainSc.h"
#include "Environment.h"
#include "mapObject.h"
#include "WaterTerrain.h"
#include "rightView.h"		//상호참조 클래스
#include "monster.h"

//1.로드를 불러서 오브젝트를 찍으면 처음지형값에 적용된다.하지만 지형을 내리거나 올리면 적용이되버린다.
//2.두번쨰 버그는 raw3번을 눌렸다 그렇게 하고 지형을 누르면 지형이 0을로 돌아가는 버그
//3.나중에 수정할것.
//4.로드릃 하고 다시 세이브를 하고 로드를해서 삭제를 시키면 벡터순서떄문에 떙겨짐 . list가 필요함

leftViewHead::leftViewHead()
	: m_eHeightType(eHeightType::E_NONE), sour(-1), dest(-1)
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
	//카메라
	_mainCamera = new camera;
	_mainCamera->SetWorldPosition(0.0f, 0.0f, 0.0f);

	//환경맵
	_environment = new Environment;
	_environment->init();
	_environment->linkCamera(*_mainCamera);

	//오브젝트
	_mapObject = new mapObject;
	_mapObject->objectinit();

	_waterTerrain = new WaterTerrain;
	_waterTerrain->linkCamera(*_mainCamera);
	_waterTerrain->init(3.0f, 256);

	//지형
	_terrain = new terrain;
	_terrain->setHeightmap("높이맵_5");
	_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("타일맵_4"), false);
	_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("타일맵_10"), false);
	_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("타일맵_13"), false);
	_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("타일맵_23"), false);
	_terrain->setSplat(FILEPATH_MANAGER->GetFilepath("스플랫_1"), false);
	_terrain->setHeightscale(10.0f);
	_terrain->setBrushmap("브러쉬_brush01");
	_terrain->setBrushScale(1.0f);
	_terrain->setting();

	//색칠하는 init함수
	this->textureColorInit();

	tile1 = "타일맵_4";
	tile2 = "타일맵_10";
	tile3 = "타일맵_13";
	tile4 = "타일맵_23";
	splat = "스플랫_1";
	raw = "높이맵_1";

	//충돌지역, 카메라
	_hitPos = D3DXVECTOR3(0, 0, 0);
	_SaveButton.FT = false;
	first = false;

	mapRotation = D3DXToRadian(180);

	DXIMG_MANAGER->GetDxImg("tileTest0")->SetPosition(D3DXVECTOR3(leftViewPort.X / 2, leftViewPort.Y, 0));

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
	_sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);
	//레프트 메인카메라 움직이기
	_mainCamera->DefaultControl(_timeDelta, 1);
	_mainCamera->updateMatrix();
	_mainCamera->updateCamToDevice();

	//마우스 포인트 가져오기
	_ptMousePos = GetMousePos();

	//업데이트 부분
	this->save();				//데이터 로드
	this->PickUdate();
	this->terrainUpdate();
	this->textureColorUpdate();

	//몬스터 업데이트 부분
	for (int i = 0; i < _monster.size(); i++)
	{
		_monster[i]->update();
	}

	_environment->update();
}

void leftViewHead::PickUdate()
{
	//왼쪽사이즈뷰만큼일떄만 업데이트가 된다.
	if (_ptMousePos.x < leftViewPort.X + leftViewPort.Width && _ptMousePos.x >= 0)
	{
		D3DXVECTOR2 _screenPos(_ptMousePos.x, _ptMousePos.y);
		_mainCamera->computeRay(&ray, &_screenPos, 1);

		switch (_rightView->GetGSnumberMonster())
		{
		case 1:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("골렘", 1);
			break;
		case 2:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("개", 2);
			break;
		case 3:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("멧돼지", 3);
			break;
		case 4:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("나무짐승", 4);
			break;
		case 5:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("브루탈루스", 5);
			break;
		case 6:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("히드라", 6);
			break;
		case 7:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("새", 7);
			break;
		case 8:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("악어", 8);
			break;
		case 9:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("곰", 9);
			break;
		case 10:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("둠가드", 10);
			break;
		case 11:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("하피", 11);
			break;
		case 12:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("랩터", 12);
			break;
		case 13:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("전갈", 13);
			break;
		case 14:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("도마뱀", 14);
			break;
		}

		if (_rightView->getnumberObject() != 0)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				float scale;
				baseObject* temp = new baseObject;
				D3DXMATRIX mapRotate;

				_terrain->isIntersectRay(&_hitPos, &ray);

				scale = 1.5f;

				//넘버값 , 로테이트값 저장
				temp->SetObjectNumber(_rightView->getnumberObject());
				temp->SetObjectRotation(mapRotation);

				if ((temp->getObjectNumber() == 189 || temp->getObjectNumber() == 190 || temp->getObjectNumber() == 191 || temp->getObjectNumber() == 192))
				{
					scale = 1.5f;
				}
				else
				{
					scale = 0.6f;
				}

				//오브젝트를 함수로 뻇음.
				_mapObject->objectSet(temp->getObjectNumber(), temp, mapRotate, _hitPos.x, _hitPos.y, _hitPos.z, scale, temp->getObjectRotation());

				m_vecObject.push_back(temp);
				//지정해놓았던것을 push로 넣는다
				//스케일을 곱해줘야 제대로 y값에 든다 
				temp->_transform->SetWorldPosition(_hitPos.x, _hitPos.y + (-temp->getBoundBox()._localMinPos.y * scale), _hitPos.z);

				//오브젝트 세이브 하기전에 값 넣기
				ObjecTemp.infoName = "넘버" + to_string(m_vecObject.size());
				ObjecTemp.objectNumber = temp->getObjectNumber();
				ObjecTemp.objectRotate = temp->getObjectRotation();
				ObjecTemp.objectScale = scale;
				ObjecTemp.objectX = temp->_transform->GetWorldPosition().x;
				ObjecTemp.objectY = temp->_transform->GetWorldPosition().y;
				ObjecTemp.objectZ = temp->_transform->GetWorldPosition().z;

				InfoObjectTemp.push_back(ObjecTemp);
			}
		}

		//노드지정
		switch (_rightView->GetGSnumberNodeInstal())
		{
		case 1:
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_terrain->isIntersectRay(&_hitPos, &ray);
				if (_hitPos.y > 0.1f)
				{
					_hitPos.y = 0;
				}
				_terrain->getDijkstra().addNode(_hitPos);
			}
		}
		break;
		}

		//노드 연결
		switch (_rightView->GetGSnumberNodelink())
		{
		case 1:
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				const vector<Node*>& temp = _terrain->getDijkstra().getVecNode();

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

		//오브젝트 삭제
		if (KEYMANAGER->isOnceKeyDown('H'))
		{
			for (int i = 0; i < m_vecObject.size(); i++)
			{
				if (PHYSICSMANAGER->isRayHitStaticMeshObject(&ray, m_vecObject[i], &_hitPos, NULL))
				{
					switch (m_vecObject[i]->getObjectNumber())
					{
					case 189:
					case 190:
					case 191:
					case 192:
						_mapObject->potralErase(m_vecObject[i]->getObjectNumber(), m_vecObject[i]->getportalNumber());
						break;
					}
					//오브젝트 삭제
					m_vecObject.erase(m_vecObject.begin() + i);
					//오브젝트 세이브 삭제
					InfoObjectTemp.erase(InfoObjectTemp.begin() + i);
				}
			}
		}

		_mapObject->portal(m_vecObject);
	}

	//각도 조절하는 키입력
	if (KEYMANAGER->isStayKeyDown('C'))
	{
		for (int i = 0; i < m_vecObject.size(); i++)
		{
			if (PHYSICSMANAGER->isRayHitStaticMeshObject(&ray, m_vecObject[i], &_hitPos, NULL))
			{
				tagSaveObject ObjecTemp;

				if (mapRotation >= D3DXToRadian(360))
				{
					mapRotation = D3DXToRadian(0);
					m_vecObject[i]->_transform->SetRotateWorld(mapRotation, mapRotation, mapRotation);

					InfoObjectTemp[i].objectRotate = mapRotation;
				}
				else
				{
					mapRotation += D3DXToRadian(5);
					m_vecObject[i]->_transform->SetRotateWorld(0, mapRotation, 0);

					InfoObjectTemp[i].objectRotate = mapRotation;
				}
			}
		}
	}

	if (KEYMANAGER->isStayKeyDown('V'))
	{
		for (int i = 0; i < m_vecObject.size(); i++)
		{
			if (PHYSICSMANAGER->isRayHitStaticMeshObject(&ray, m_vecObject[i], &_hitPos, NULL))
			{
				if (mapRotation <= D3DXToRadian(0))
				{
					mapRotation = D3DXToRadian(360);
					m_vecObject[i]->_transform->SetRotateWorld(mapRotation, mapRotation, mapRotation);

					InfoObjectTemp[i].objectRotate = mapRotation;
				}
				else
				{
					mapRotation -= D3DXToRadian(5);
					m_vecObject[i]->_transform->SetRotateWorld(0, mapRotation, 0);

					InfoObjectTemp[i].objectRotate = mapRotation;
				}
			}
		}
	}
}

void leftViewHead::terrainUpdate()
{
	this->terrainTextureUpate();

	if (_ptMousePos.x < leftViewPort.X + leftViewPort.Width && _ptMousePos.x >= 0)
	{
		//지형맵 높이 업데이트
		if (_rightView->getNumberHeight() == 1)
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				_terrain->SetHtChangeSign(1);

				_terrain->isIntersectRay(&_hitPos, &ray);

				//Terrain에서 피킹한 곳의 인덱스를 가져온다.
				m_vSelectIdx = _terrain->getIdx(_hitPos.x, _hitPos.z);

				//Terrain에서 피킹한 인덱스 부분을 올린다.
				//현재 상태는 쿼드트리 할당 트루상태이므로 한번 세팅할 때는 쿼드가 적용된다.
				_terrain->changeHeight(m_vSelectIdx.x, m_vSelectIdx.y);

				//키를 누르고 있을 때는 쿼드트리 할당을 하지 않는다.
				_terrain->SetIsQuad(false);
			}
		}
		if (_rightView->getNumberHeight() == 2)
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				_terrain->SetHtChangeSign(-1);

				_terrain->isIntersectRay(&_hitPos, &ray);

				//Terrain에서 피킹한 곳의 인덱스를 가져온다.
				m_vSelectIdx = _terrain->getIdx(_hitPos.x, _hitPos.z);

				//Terrain에서 피킹한 인덱스 부분을 올린다.
				//현재 상태는 쿼드트리 할당 트루상태이므로 한번 세팅할 때는 쿼드가 적용된다.
				_terrain->changeHeight(m_vSelectIdx.x, m_vSelectIdx.y);

				//키를 누르고 있을 때는 쿼드트리 할당을 하지 않는다.
				_terrain->SetIsQuad(false);
			}
		}
	}

	if (_rightView->getnumberwater() != 0)
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
		tile1 = "타일맵_1";
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath(tile1), false);
		break;
	case 2:
		tile1 = "타일맵_2";
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath(tile1), false);
		break;
	case 3:
		tile1 = "타일맵_3";
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath(tile1), false);
		break;
	case 4:
		tile1 = "타일맵_4";
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath(tile1), false);
		break;
	case 5:
		tile1 = "타일맵_5";
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath(tile1), false);
		break;
	case 6:
		tile1 = "타일맵_6";
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath(tile1), false);
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
		tile2 = "타일맵_7";
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath(tile2), false);
		break;
	case 2:
		tile2 = "타일맵_8";
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath(tile2), false);
		break;
	case 3:
		tile2 = "타일맵_9";
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath(tile2), false);
		break;
	case 4:
		tile2 = "타일맵_10";
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath(tile2), false);
		break;
	case 5:
		tile2 = "타일맵_11";
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath(tile2), false);
		break;
	case 6:
		tile2 = "타일맵_12";
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath(tile2), false);
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
		tile3 = "타일맵_13";
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath(tile3), false);
		break;
	case 2:
		tile3 = "타일맵_14";
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath(tile3), false);
		break;
	case 3:
		tile3 = "타일맵_15";
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath(tile3), false);
		break;
	case 4:
		tile3 = "타일맵_16";
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath(tile3), false);
		break;
	case 5:
		tile3 = "타일맵_17";
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath(tile3), false);
		break;
	case 6:
		tile3 = "타일맵_18";
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath(tile3), false);
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
		tile4 = "타일맵_19";
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath(tile4), false);
		break;
	case 2:
		tile4 = "타일맵_20";
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath(tile4), false);
		break;
	case 3:
		tile4 = "타일맵_21";
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath(tile4), false);
		break;
	case 4:
		tile4 = "타일맵_22";
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath(tile4), false);
		break;
	case 5:
		tile4 = "타일맵_23";
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath(tile4), false);
		break;
	case 6:
		tile4 = "타일맵_24";
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath(tile4), false);
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
		splat = "스플랫_1";
		_terrain->setSplat(FILEPATH_MANAGER->GetFilepath(splat), false);
		break;
	case 2:
		splat = "스플랫_2";
		_terrain->setSplat(FILEPATH_MANAGER->GetFilepath(splat), false);
		break;
	case 3:
		splat = "스플랫_3";
		_terrain->setSplat(FILEPATH_MANAGER->GetFilepath(splat), false);
		break;
	case 4:
		splat = "스플랫_4";
		_terrain->setSplat(FILEPATH_MANAGER->GetFilepath(splat), false);
		break;
	case 5:
		splat = "스플랫_5";
		_terrain->setSplat(FILEPATH_MANAGER->GetFilepath(splat), false);
		break;
	case 6:
		splat = "스플랫_6";
		_terrain->setSplat(FILEPATH_MANAGER->GetFilepath(splat), false);
		break;
	}

	//RAW
	switch (_rightView->GetGSnumberRaw())
	{
	case 1:
		raw = "높이맵_1";
		{
			if (_rightView->GetGSboolHeight() == true)
			{
				for (int i = 0; i < _terrain->_vecPos.size(); i++)
				{
					_terrain->_vecPos[i].y = 0;
				}
			}
		}
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath(raw), false);
		break;
	case 2:
		raw = "높이맵_2";
		{
			if (_rightView->GetGSboolHeight() == true)
			{
				for (int i = 0; i < _terrain->_vecPos.size(); i++)
				{
					_terrain->_vecPos[i].y = 0;
				}
			}
		}
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath(raw), false);
		break;
	case 3:
		raw = "높이맵_3";
		{
			if (_rightView->GetGSboolHeight() == true)
			{
				for (int i = 0; i < _terrain->_vecPos.size(); i++)
				{
					_terrain->_vecPos[i].y = 0;
				}
			}
		}
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath(raw), false);
		break;
	case 4:
		raw = "높이맵_4";
		{
			if (_rightView->GetGSboolHeight() == true)
			{
				for (int i = 0; i < _terrain->_vecPos.size(); i++)
				{
					_terrain->_vecPos[i].y = 0;
				}
			}
		}
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath(raw), false);
		break;
	case 5:
		raw = "높이맵_5";
		{
			if (_rightView->GetGSboolHeight() == true)
			{
				for (int i = 0; i < _terrain->_vecPos.size(); i++)
				{
					_terrain->_vecPos[i].y = 0;
				}
			}
		}
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath(raw), false);
		break;
	case 6:
		raw = "높이맵_6";
		{
			if (_rightView->GetGSboolHeight() == true)
			{
				for (int i = 0; i < _terrain->_vecPos.size(); i++)
				{
					_terrain->_vecPos[i].y = 0;
				}
			}
		}
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath(raw), false);
		break;
	}

	if (_rightView->GetGSboolRaw())
	{
		_rightView->SetGSboolHeight(false);
		_rightView->SetGSboolRaw(false);
		_terrain->setting();
	}
}

void leftViewHead::monsterMaptul()
{
	

}

void leftViewHead::save()
{
	if (first == false)
	{
		if (KEYMANAGER->isOnceKeyDown('L'))
		{
			m_vecObject.clear();
			InfoObjectTemp.clear();
			_mapObject->deletePortal();

			IOSAVEOBJECTMANAGER->loadFile("ㅇㅇ");
			for (int i = 0; i < IOSAVEOBJECTMANAGER->getCount(); i++)
			{
				object = IOSAVEOBJECTMANAGER->findTag("넘버" + to_string(i + 1));
				baseObject* temp2 = new baseObject;
				D3DXMATRIX mapRotate;
				_mapObject->objectSet(object.objectNumber, temp2, mapRotate, object.objectX, object.objectY, object.objectZ, object.objectScale, object.objectRotate);
				InfoObjectTemp.push_back(object);
				temp2->SetObjectNumber(object.objectNumber);
				m_vecObject.push_back(temp2);
			}

			_terrain->setHeightmap(IOMAPMANAGER->loadMapInfo("ㅇㅇ").heightMap, false);
			_terrain->setTile0(IOMAPMANAGER->loadMapInfo("ㅇㅇ").tile0, false);
			_terrain->setTile1(IOMAPMANAGER->loadMapInfo("ㅇㅇ").tile1, false);
			_terrain->setTile2(IOMAPMANAGER->loadMapInfo("ㅇㅇ").tile2, false);
			_terrain->setTile3(IOMAPMANAGER->loadMapInfo("ㅇㅇ").tile3, false);
			_terrain->setSplat(IOMAPMANAGER->loadMapInfo("ㅇㅇ").splat, false);
			_terrain->setMapPosition(IOMAPMANAGER->loadMapInfo("ㅇㅇ").vecPos);
			_terrain->setting();
			_terrain->changeHeightTerrain();


			tagSaveMap _envTemp;
			tagSaveMap _waterTemp;

			IOSAVEMANAGER->loadFile("ㅇㅇ");

			_envTemp = IOSAVEMANAGER->findTag("환경맵");
			_waterTemp = IOSAVEMANAGER->findTag("물결맵");

			_rightView->setNumberEnv(_envTemp.number);
			_rightView->setnumberwater(_waterTemp.number);

			//loadMonster();
			//loadNode();
			first = true;
		}
	}
	if (PtInRect(&_SaveButton.rc2, GetMousePos()))
	{
		_SaveButton.FT = true;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
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

			IOSAVEMANAGER->saveFile("ㅇㅇ", InfoTemp);

			//지우고 나서 문제가 생겨서 이름을 다시 1번부터 저장시켜준다
			for (int i = 0; i < InfoObjectTemp.size(); i++)
			{
				InfoObjectTemp[i].infoName = "넘버" + to_string(i + 1);
			}

			IOSAVEOBJECTMANAGER->saveFile("ㅇㅇ", InfoObjectTemp);

			ST_MAP temp0;

			temp0.heightMap = FILEPATH_MANAGER->GetFilepath(raw);
			temp0.splat = FILEPATH_MANAGER->GetFilepath(splat);
			temp0.tile0 = FILEPATH_MANAGER->GetFilepath(tile1);
			temp0.tile1 = FILEPATH_MANAGER->GetFilepath(tile2);
			temp0.tile2 = FILEPATH_MANAGER->GetFilepath(tile3);
			temp0.tile3 = FILEPATH_MANAGER->GetFilepath(tile4);

			temp0.vecPos = _terrain->getMapPosition();

			IOMAPMANAGER->saveFile("ㅇㅇ", temp0);

			////몬스터 위치 ,값 저장/////////////////////////////////
			//vector<tagSaveMonster> monsterTemp;
			//tagSaveMonster Mtemp;

			//if (_monster.size() != 0)
			//{
			//	for (int i = 0; i < _monster.size(); i++)
			//	{
			//		Mtemp.infoName = "몬스터넘버" + to_string(i + 1);
			//		Mtemp.monsterNumber = _monster[i]->getObjectNumber();
			//		Mtemp.monsterX = _monster[i]->_transform->GetWorldPosition().x;
			//		Mtemp.monsterY = _monster[i]->_transform->GetWorldPosition().y;
			//		Mtemp.monsterZ = _monster[i]->_transform->GetWorldPosition().z;
			//		Mtemp.scale = 1.0f;

			//		monsterTemp.push_back(Mtemp);
			//	}

			//	IOSAVEMONSTERMANAGER->saveFile("몬스터", monsterTemp);
			//}

			//////노드지정 ,위치,값 저장////////////////////////////
			//vector<tagSaveNode> nodeTemp;
			//tagSaveNode nTemp;

			//for (int i = 0; i < _terrain->getDijkstra().getVecNode().size(); i++)
			//{
			//	nTemp.nodeFS.clear();
			//	nTemp.infoName = "노드" + to_string(i + 1);
			//	nTemp.Inumber = i;														// 벡터의 인덱스값 저장
			//	nTemp.nodeX = _terrain->getDijkstra().getVecNode()[i]->getPosition().x;	//위치값 저장
			//	nTemp.nodeY = _terrain->getDijkstra().getVecNode()[i]->getPosition().y;	//위치값 저장
			//	nTemp.nodeZ = _terrain->getDijkstra().getVecNode()[i]->getPosition().z;	//위치값 저장
			//	nTemp.nodeFSSize = _terrain->getDijkstra().getadjNode()[i].size();			//벡터 사이즈값 저장

			//	for (int j = 0; j < _terrain->getDijkstra().getadjNode()[i].size(); j++)
			//	{
			//		nTemp.nodeFS.push_back(make_pair(_terrain->getDijkstra().getadjNode()[i][j].first, _terrain->getDijkstra().getadjNode()[i][j].second)); 	//first는 벡터에서 몇번 노드인지를 알려준다.	
			//																																					//second는 현재 노드에서 j노드까지의 거리값을 가진다.
			//	}

			//	nodeTemp.push_back(nTemp);
			//}

			//IOSAVENODEMANAGER->saveFile("노드", nodeTemp);
		}

	}
	else
	{
		_SaveButton.FT = false;
	}
}

void leftViewHead::textureColorInit()
{
	ZeroMemory(&m_pCSplatBase, sizeof(m_pCSplatBase));

	m_pCSplatBase = TEXTURE_MANAGER->GetTexture("splat_base");
	m_pCSplatBase = TEXTURE_MANAGER->GetTexture("splat_test0");
	m_pCSplatBase = TEXTURE_MANAGER->GetTexture("splat_test1");
	m_pCSplatBase = TEXTURE_MANAGER->GetTexture("splat_test2");
	m_pCSplatBase = TEXTURE_MANAGER->GetTexture("splat_test3");
	_terrain->setSplat(m_pCSplatBase);

	//============================================================================================//
	_textureColorBack.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/믹스배경.png");

	for (int i = 0; i < 4; i++)
	{
		_textureColorMix[i].FT = false;
		_textureColorMixSize[i].FT = false;

		_textureColorMix[i].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/믹스1.png");
		_textureColorMixSize[i].tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/믹스2.png");
	}

	MoveX = -202;
	MoveY = 150;
	MAXX = 19;
	MAXY = 551;
	_textureColorBack.rc2 = { (LONG)leftViewPort.X + MoveX , (LONG)leftViewPort.Y + MoveY, (LONG)leftViewPort.X + MAXX, (LONG)leftViewPort.Y + MAXY };

	_textureColorMix[0].rc2 = { MoveX + 48 , MoveY + 74,MoveX + 152,MoveY + 96 };
	_textureColorMix[1].rc2 = { MoveX + 48 , MoveY + 101,MoveX + 152,MoveY + 123 };
	_textureColorMix[2].rc2 = { MoveX + 48 , MoveY + 128,MoveX + 152,MoveY + 150 };
	_textureColorMix[3].rc2 = { MoveX + 48 , MoveY + 155,MoveX + 152,MoveY + 177 };

	_textureColorMixSize[0].rc2 = { MoveX + 48 , MoveY + 229,MoveX + 152,MoveY + 251 };
	_textureColorMixSize[1].rc2 = { MoveX + 48 , MoveY + 256,MoveX + 152,MoveY + 278 };
	_textureColorMixSize[2].rc2 = { MoveX + 48 , MoveY + 283,MoveX + 152,MoveY + 305 };
	_textureColorMixSize[3].rc2 = { MoveX + 48 , MoveY + 310,MoveX + 152,MoveY + 332 };

	MoveBack = 0;

	_pick1.first = false;
	_pick1.second = { 0,0 };

	_pick2.first = false;
	_pick2.second = { 0,0 };
}

void leftViewHead::textureColorUpdate()
{
	//이부분은 이동이기떄문에 포함될필요없음(LEFT안에)
	switch (MoveBack)
	{
	case MOVETYPE::BackRight:
		if (leftViewPort.X + 19 >= MoveX)
		{
			MoveX = 19;
			MAXX = 221;
		}
		else
		{
			MoveX++;
			MAXX++;
		}
		break;

	case MOVETYPE::BackLeft:
		if (19 >= MAXX)
		{
			MoveX = -202;
			MAXX = 19;
		}
		else
		{
			MoveX--;
			MAXX--;
		}
		break;

	case MOVETYPE::RightSTOP:
		break;

	case MOVETYPE::LeftSTOP:
		break;
	}
	//==============================================================================/
	if (_ptMousePos.x < leftViewPort.X + leftViewPort.Width && _ptMousePos.x >= 0)
	{
		for (int i = 0; i < 4; i++)
		{
			if (PtInRect(&_textureColorMix[i].rc2, GetMousePos()))
			{
				_textureColorMix[i].FT = true;

				if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
				{
					_pick1.first = true;
					_pick1.second = { _textureColorMix[i].rc2.left,_textureColorMix[i].rc2.top };
					m_sCCurTex = "tileTest" + to_string(i) + "_mapTool";
				}
			}
			else
			{
				_textureColorMix[i].FT = false;
			}

			if (PtInRect(&_textureColorMixSize[i].rc2, GetMousePos()))
			{
				_textureColorMixSize[i].FT = true;

				if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
				{
					_pick2.first = true;
					_pick2.second = { _textureColorMixSize[i].rc2.left,_textureColorMixSize[i].rc2.top };
					m_nSplatRange = i;
				}
			}
			else
			{
				_textureColorMixSize[i].FT = false;
			}
		}

		if (_pick1.first == true && _pick2.first == true)
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				//Terrain 이랑 Ray체크
				_terrain->isIntersectRay(&_hitPos, &ray);

				//Terrain에서 피킹한 곳의 인덱스를 가져온다.
				m_vSelectIdx = _terrain->getIdx(_hitPos.x, _hitPos.z);

				//현재 정점x,y에서 스플랫 색상을 가져온다.
				m_vCSelectColor = _terrain->selectSplatColor("splat_base", m_vSelectIdx.x, m_vSelectIdx.y);

				D3DLOCKED_RECT lockRect;
				m_pCSplatBase->LockRect(0, &lockRect, 0, 0);

				for (int z = m_vSelectIdx.y - m_nSplatRange; z <= m_vSelectIdx.y + m_nSplatRange; z++)
				{
					for (int x = m_vSelectIdx.x - m_nSplatRange; x <= m_vSelectIdx.x + m_nSplatRange; x++)
					{
						//해당 픽셀의 컬러 값을 얻는다.
						DWORD* pStart = (DWORD*)lockRect.pBits;	//(DWORD 형으로 형변환된 lock 된 이미지지의 시작 주소
						DWORD dwColor = *(pStart + (z * (lockRect.Pitch / 4) + x));

						if (m_sCCurTex == "tileTest0_mapTool")
						{
							*(pStart + (z * (lockRect.Pitch / 4) + x)) = 255 << 16;		// R    
						}
						else if (m_sCCurTex == "tileTest1_mapTool")
						{
							*(pStart + (z * (lockRect.Pitch / 4) + x)) = 255 << 8;		// G  
						}
						else if (m_sCCurTex == "tileTest2_mapTool")
						{
							*(pStart + (z * (lockRect.Pitch / 4) + x)) = 255 << 4;		// B   
						}
						else if (m_sCCurTex == "tileTest3_mapTool")
						{
							*(pStart + (z * (lockRect.Pitch / 4) + x)) = 0;				// Bk  
						}

						//*(pStart + (z * (lockRect.Pitch / 4) + x)) = 255 << 16;		// R    
						//*(pStart + (z * (lockRect.Pitch / 4) + x)) = 255 << 8;		// G    
						//*(pStart + (z * (lockRect.Pitch / 4) + x)) = 255 << 4;		// B    
						//*(pStart + (z * (lockRect.Pitch / 4) + x)) = 0;				// Bk 
					}
				}
				m_pCSplatBase->UnlockRect(0);
			}
		}
	}
	else
	{
		_pick1.first = false;
		_pick2.first = false;
	}
}

void leftViewHead::textureColorRender()
{
	//이동뒤에 필요하기떄문에 추가 
	_textureColorBack.rc2 = { MoveX ,MoveY, MAXX,MAXY };

	_textureColorMix[0].rc2 = { MoveX + 48 , MoveY + 74,MoveX + 152,MoveY + 96 };
	_textureColorMix[1].rc2 = { MoveX + 48 , MoveY + 101,MoveX + 152,MoveY + 123 };
	_textureColorMix[2].rc2 = { MoveX + 48 , MoveY + 128,MoveX + 152,MoveY + 150 };
	_textureColorMix[3].rc2 = { MoveX + 48 , MoveY + 155,MoveX + 152,MoveY + 177 };

	_textureColorMixSize[0].rc2 = { MoveX + 48 , MoveY + 229,MoveX + 152,MoveY + 251 };
	_textureColorMixSize[1].rc2 = { MoveX + 48 , MoveY + 256,MoveX + 152,MoveY + 278 };
	_textureColorMixSize[2].rc2 = { MoveX + 48 , MoveY + 283,MoveX + 152,MoveY + 305 };
	_textureColorMixSize[3].rc2 = { MoveX + 48 , MoveY + 310,MoveX + 152,MoveY + 332 };

	SPRITEMANAGER->renderRectTexture(_textureColorBack.tex, &_textureColorBack.rc1, &_textureColorBack.rc2, 0, 0, 202, 361, MoveX, MoveY);

	//MIX
	if (_textureColorMix[0].FT == false) SPRITEMANAGER->renderRectTexture(_textureColorMix[0].tex, &_textureColorMix[0].rc1, &_textureColorMix[0].rc2, 0, 0, 104, 22, MoveX + 48, MoveY + 74);
	else SPRITEMANAGER->renderRectTexture(_textureColorMix[0].tex, &_textureColorMix[0].rc1, &_textureColorMix[0].rc2, 0, 22, 104, 44, MoveX + 48, MoveY + 74);

	if (_textureColorMix[1].FT == false) SPRITEMANAGER->renderRectTexture(_textureColorMix[1].tex, &_textureColorMix[1].rc1, &_textureColorMix[1].rc2, 0, 44, 104, 66, MoveX + 48, MoveY + 101);
	else SPRITEMANAGER->renderRectTexture(_textureColorMix[1].tex, &_textureColorMix[1].rc1, &_textureColorMix[1].rc2, 0, 66, 104, 88, MoveX + 48, MoveY + 101);

	if (_textureColorMix[2].FT == false) SPRITEMANAGER->renderRectTexture(_textureColorMix[2].tex, &_textureColorMix[2].rc1, &_textureColorMix[2].rc2, 0, 88, 104, 110, MoveX + 48, MoveY + 128);
	else SPRITEMANAGER->renderRectTexture(_textureColorMix[2].tex, &_textureColorMix[2].rc1, &_textureColorMix[2].rc2, 0, 110, 104, 132, MoveX + 48, MoveY + 128);

	if (_textureColorMix[3].FT == false) SPRITEMANAGER->renderRectTexture(_textureColorMix[3].tex, &_textureColorMix[3].rc1, &_textureColorMix[3].rc2, 0, 132, 104, 154, MoveX + 48, MoveY + 155);
	else SPRITEMANAGER->renderRectTexture(_textureColorMix[3].tex, &_textureColorMix[3].rc1, &_textureColorMix[3].rc2, 0, 154, 104, 176, MoveX + 48, MoveY + 155);

	//MIXSIZE
	if (_textureColorMixSize[0].FT == false)  SPRITEMANAGER->renderRectTexture(_textureColorMixSize[0].tex, &_textureColorMixSize[0].rc1, &_textureColorMixSize[0].rc2, 0, 0, 104, 22, MoveX + 48, MoveY + 229);
	else SPRITEMANAGER->renderRectTexture(_textureColorMixSize[0].tex, &_textureColorMixSize[0].rc1, &_textureColorMixSize[0].rc2, 0, 22, 104, 44, MoveX + 48, MoveY + 229);

	if (_textureColorMixSize[1].FT == false)  SPRITEMANAGER->renderRectTexture(_textureColorMixSize[1].tex, &_textureColorMixSize[1].rc1, &_textureColorMixSize[1].rc2, 0, 44, 104, 66, MoveX + 48, MoveY + 256);
	else SPRITEMANAGER->renderRectTexture(_textureColorMixSize[1].tex, &_textureColorMixSize[1].rc1, &_textureColorMixSize[1].rc2, 0, 66, 104, 88, MoveX + 48, MoveY + 256);

	if (_textureColorMixSize[2].FT == false)  SPRITEMANAGER->renderRectTexture(_textureColorMixSize[2].tex, &_textureColorMixSize[2].rc1, &_textureColorMixSize[2].rc2, 0, 88, 104, 110, MoveX + 48, MoveY + 283);
	else SPRITEMANAGER->renderRectTexture(_textureColorMixSize[2].tex, &_textureColorMixSize[2].rc1, &_textureColorMixSize[2].rc2, 0, 110, 104, 132, MoveX + 48, MoveY + 283);

	if (_textureColorMixSize[3].FT == false)  SPRITEMANAGER->renderRectTexture(_textureColorMixSize[3].tex, &_textureColorMixSize[3].rc1, &_textureColorMixSize[3].rc2, 0, 132, 104, 154, MoveX + 48, MoveY + 310);
	else SPRITEMANAGER->renderRectTexture(_textureColorMixSize[3].tex, &_textureColorMixSize[3].rc1, &_textureColorMixSize[3].rc2, 0, 154, 104, 176, MoveX + 48, MoveY + 310);

	if (_pick1.first == true)
	{
		LPDIRECT3DTEXTURE9 temp = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/믹스픽.png");
		for (int i = 0; i < 4; i++)
		{
			SPRITEMANAGER->renderRectTexture(temp, &_textureColorMix[i].rc1, &_textureColorMix[i].rc2, 0, 0, 128, 128, _pick1.second.x, _pick1.second.y);
		}
	}

	if (_pick2.first == true)
	{
		LPDIRECT3DTEXTURE9 temp = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/믹스픽1.png");
		for (int i = 0; i < 4; i++)
		{
			SPRITEMANAGER->renderRectTexture(temp, &_textureColorMixSize[i].rc1, &_textureColorMixSize[i].rc2, 0, 0, 128, 128, _pick2.second.x, _pick2.second.y);
		}
	}
}

void leftViewHead::render()
{
	//텍스쳐칼라렌더 
	this->textureColorRender();

	//////맵지형 맵바탕 UI
	_leftView.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/왼쪽맵툴.png");
	SPRITEMANAGER->renderRectTexture(_leftView.tex, &_leftView.rc1, &_leftView.rc2, 0, 0, 2048, 1024, leftViewPort.X, leftViewPort.Y);

	char str[128];
	sprintf_s(str, "%.0f", D3DXToDegree(mapRotation));
	FONTMANAGER->fontOut(str, leftViewPort.X + 1085, leftViewPort.Y + 22, D3DCOLOR_XRGB(255, 255, 255));

	//save버튼
	switch (_SaveButton.FT)
	{
	case true:
		_SaveButton.rc2 = { 1050,860,_SaveButton.rc2.left + 95,_SaveButton.rc2.top + 37 };
		_SaveButton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/SAVE.png");
		SPRITEMANAGER->renderRectTexture(_SaveButton.tex, &_SaveButton.rc1, &_SaveButton.rc2, 0, 0, 256, 37, leftViewPort.X + 1050, leftViewPort.Y + 860);
		break;

	case false:
		_SaveButton.rc2 = { 1050,860,_SaveButton.rc2.left + 95,_SaveButton.rc2.top + 37 };
		_SaveButton.tex = RM_TEXTURE->getResource("Resource/Maptool/maptoolui/SAVE.png");
		SPRITEMANAGER->renderRectTexture(_SaveButton.tex, &_SaveButton.rc1, &_SaveButton.rc2, 0, 37, 256, 74, leftViewPort.X + 1050, leftViewPort.Y + 860);
		break;
	}

	//지형 렌더
	_terrain->render(_mainCamera, _sceneBaseDirectionLight);

	//오브젝트 렌더
	if (!m_vecObject.empty()) _mapObject->objectRenderTool(m_vecObject, _mainCamera, _sceneBaseDirectionLight);

	xMeshSkinned::setCamera(_mainCamera);
	xMeshSkinned::setTechniqueName("Toon");
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resource/Testures/Ramp_1.png"));
	xMeshSkinned::setBaseLight(this->_sceneBaseDirectionLight);

	//몬스터 렌더
	for (int i = 0; i < _monster.size(); i++)
	{
		_monster[i]->render();
	}

	if (_rightView->getNumberEnv() != 0)
	{
		_environment->renderEnvironment(_rightView->getNumberEnv());
	}

	if (_rightView->getnumberwater() != 0)
	{
		_waterTerrain->render(_rightView->getnumberwater());
	}

	const vector<Node*>& temp = _terrain->getDijkstra().getVecNode();
	for (int i = 0; i < temp.size(); i++)
	{
		temp[i]->Render();
	}

	//다익스트라 노드 그리기
	_terrain->getDijkstra().render();

	DXIMG_MANAGER->GetDxImg("mouseCursor")->setPos(GetMousePos().x, GetMousePos().y);
	DXIMG_MANAGER->GetDxImg("mouseCursor")->render();
}

void leftViewHead::monsterSelect(string str, int monsterNumber)
{
	monster* temp = new monster(findMonsterName(monsterNumber));
	temp->_transform->SetScale(1.0f, 1.0f, 1.0f);

	_terrain->isIntersectRay(&_hitPos, &ray);

	temp->_transform->SetWorldPosition(_hitPos);
	temp->setRegenPosition(_hitPos);
	temp->setMesh(XMESH_MANAGER->GetXmeshSkinned(str));
	temp->setActive(true);
	temp->SetObjectNumber(monsterNumber);
	_monster.push_back(temp);
}

void leftViewHead::loadMonster(void)
{
	IOSAVEMONSTERMANAGER->loadFile("몬스터");
	vector<tagSaveMonster> temp;
	tagSaveMonster tagMTemp;

	for (int i = 0; i < IOSAVEMONSTERMANAGER->getCount(); i++)
	{
		tagMTemp = IOSAVEMONSTERMANAGER->findTag("몬스터넘버" + to_string(i + 1));

		temp.push_back(tagMTemp);
	}

	for (int i = 0; i < temp.size(); i++)
	{
		D3DXMATRIX matRotate;
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));

		monster* tempMonster = new monster(findMonsterName(temp[i].monsterNumber));
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
		return XMESH_MANAGER->GetXmeshSkinned("골렘");
	case 2:
		return XMESH_MANAGER->GetXmeshSkinned("개");
		break;
	case 3:
		return XMESH_MANAGER->GetXmeshSkinned("멧돼지");
		break;
	case 4:
		return XMESH_MANAGER->GetXmeshSkinned("나무짐승");
		break;
	case 5:
		return XMESH_MANAGER->GetXmeshSkinned("브루탈루스");
		break;
	case 6:
		return XMESH_MANAGER->GetXmeshSkinned("히드라");
		break;
	case 7:
		return XMESH_MANAGER->GetXmeshSkinned("새");
		break;
	case 8:
		return XMESH_MANAGER->GetXmeshSkinned("악어");
		break;
	case 9:
		return XMESH_MANAGER->GetXmeshSkinned("곰");
		break;
	case 10:
		return XMESH_MANAGER->GetXmeshSkinned("둠가드");
		break;
	case 11:
		return XMESH_MANAGER->GetXmeshSkinned("하피");
		break;
	case 12:
		return XMESH_MANAGER->GetXmeshSkinned("랩터");
		break;
	case 13:
		return XMESH_MANAGER->GetXmeshSkinned("전갈");
		break;
	case 14:
		return XMESH_MANAGER->GetXmeshSkinned("도마뱀");
		break;
	}
}

string leftViewHead::findMonsterName(int & index)
{
	string temp = "";
	switch (index)
	{
	case 1:
		temp = "아크레골렘";
		return temp;
	case 2:
		temp = "이현총";
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

void leftViewHead::loadNode(void)
{
	IOSAVENODEMANAGER->loadFile("노드");
	vector<tagSaveNode> temp;
	tagSaveNode tempNode;

	for (int i = 0; i < IOSAVENODEMANAGER->getCount(); i++)
	{
		tempNode = IOSAVENODEMANAGER->findTag("노드" + to_string(i + 1));

		temp.push_back(tempNode);
	}

	for (int i = 0; i < temp.size(); i++)
	{
		_terrain->getDijkstra().addNode(D3DXVECTOR3(temp[i].nodeX, temp[i].nodeY, temp[i].nodeZ));
	}

	for (int i = 0; i < temp.size(); i++)
	{
		for (int j = 0; j < temp[i].nodeFSSize; j++)
		{
			int tempSour = i;
			int tempDest = temp[i].nodeFS[j].first;
			_terrain->getDijkstra().connectNode(tempSour, tempDest);
		}
	}
}
