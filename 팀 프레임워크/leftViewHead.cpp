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

#include "monster.h"

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

	//환경맵
	_environment = new Environment;
	_environment->init();
	_environment->linkCamera(_mainCamera);

	//오브젝트
	_mapObject = new mapObject;
	_mapObject->objectinit();

	_waterTerrain = new WaterTerrain;
	_waterTerrain->init(3.0f, 100);

	//지형
	_terrain = new terrain;
	_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath("높이맵_3"));
	_terrain->setTile0(FILEPATH_MANAGER->GetFilepath("타일맵_4"));
	_terrain->setTile1(FILEPATH_MANAGER->GetFilepath("타일맵_10"));
	_terrain->setTile2(FILEPATH_MANAGER->GetFilepath("타일맵_13"));
	_terrain->setTile3(FILEPATH_MANAGER->GetFilepath("타일맵_23"));
	_terrain->setSlat(FILEPATH_MANAGER->GetFilepath("스플랫_1"));
	_terrain->setHeightscale(10.0f);
	_terrain->setBrushmap(FILEPATH_MANAGER->GetFilepath("브러쉬_brush01"));
	_terrain->setBrushScale(1.0f);
	_terrain->setting();

	tile1 = "타일맵_4";
	tile2 = "타일맵_10";
	tile3 = "타일맵_13";
	tile4 = "타일맵_23";
	splat = "스플랫_1";
	raw = "높이맵_3";

	//충돌지역, 카메라
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
	this->save();				//데이터 로드
	this->terrainUpdate();
	this->PickUdate();
	this->monsterMaptul();

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
	//타일맵1
	switch (_rightView->GetGSnumberTile1())
	{
	case 1:
		tile1 = "타일맵_1";
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath(tile1));
		break;
	case 2:
		tile1 = "타일맵_2";
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath(tile1));
		break;
	case 3:
		tile1 = "타일맵_3";
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath(tile1));
		break;
	case 4:
		tile1 = "타일맵_4";
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath(tile1));
		break;
	case 5:
		tile1 = "타일맵_5";
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath(tile1));
		break;
	case 6:
		tile1 = "타일맵_6";
		_terrain->setTile0(FILEPATH_MANAGER->GetFilepath(tile1));
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
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath(tile2));
		break;
	case 2:
		tile2 = "타일맵_8";
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath(tile2));
		break;
	case 3:
		tile2 = "타일맵_9";
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath(tile2));
		break;
	case 4:
		tile2 = "타일맵_10";
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath(tile2));
		break;
	case 5:
		tile2 = "타일맵_11";
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath(tile2));
		break;
	case 6:
		tile2 = "타일맵_12";
		_terrain->setTile1(FILEPATH_MANAGER->GetFilepath(tile2));
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
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath(tile3));
		break;
	case 2:
		tile3 = "타일맵_14";
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath(tile3));
		break;
	case 3:
		tile3 = "타일맵_15";
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath(tile3));
		break;
	case 4:
		tile3 = "타일맵_16";
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath(tile3));
		break;
	case 5:
		tile3 = "타일맵_17";
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath(tile3));
		break;
	case 6:
		tile3 = "타일맵_18";
		_terrain->setTile2(FILEPATH_MANAGER->GetFilepath(tile3));
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
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath(tile4));
		break;
	case 2:
		tile4 = "타일맵_20";
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath(tile4));
		break;
	case 3:
		tile4 = "타일맵_21";
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath(tile4));
		break;
	case 4:
		tile4 = "타일맵_22";
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath(tile4));
		break;
	case 5:
		tile4 = "타일맵_23";
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath(tile4));
		break;
	case 6:
		tile4 = "타일맵_24";
		_terrain->setTile3(FILEPATH_MANAGER->GetFilepath(tile4));
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
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath(splat));
		break;
	case 2:
		splat = "스플랫_2";
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath(splat));
		break;
	case 3:
		splat = "스플랫_3";
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath(splat));
		break;
	case 4:
		splat = "스플랫_4";
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath(splat));
		break;
	case 5:
		splat = "스플랫_5";
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath(splat));
		break;
	case 6:
		splat = "스플랫_6";
		_terrain->setSlat(FILEPATH_MANAGER->GetFilepath(splat));
		break;
	}

	//RAW
	switch (_rightView->GetGSnumberRaw())
	{
	case 1:
		raw = "높이맵_1";
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath(raw));
		break;
	case 2:
		raw = "높이맵_2";
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath(raw));
		break;
	case 3:
		raw = "높이맵_3";
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath(raw));
		break;
	case 4:
		raw = "높이맵_4";
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath(raw));
		break;
	case 5:
		raw = "높이맵_5";
		_terrain->setHeightmap(FILEPATH_MANAGER->GetFilepath(raw));
		break;
	case 6:
		raw = "높이맵_6";
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
		//노드지정
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

		//노드 연결
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
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("골렘",1);
			break;
		case 2:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("개",2);
			break;
		case 3:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("멧돼지",3);
			break;
		case 4:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("나무짐승",4);
			break;
		case 5:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("브루탈루스",5);
			break;
		case 6:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("히드라",6);
			break;
		case 7:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("새",7);
			break;
		case 8:
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("악어",8);
			break;													  
		case 9:														  
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("곰",9);
			break;													  
		case 10:													  
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("둠가드",10);
			break;													  
		case 11:													  
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("하피",11);
			break;													  
		case 12:													  
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("랩터",12);
			break;													  
		case 13:													  
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("전갈",13);
			break;													  
		case 14:													  
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) monsterSelect("도마뱀",14);
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
			//맵에 관한 save
			//벡터로 담을 temp설정
			//vector<tagSaveMap> InfoTemp;
			//tagSaveMap temp;

			//temp.infoName = "환경맵";
			//temp.number = _rightView->getNumberEnv();
			//temp.mapHeight = 0;
			//InfoTemp.push_back(temp);

			//temp.infoName = "물결맵";
			//temp.number = _rightView->getnumberwater();
			//temp.mapHeight = 0;
			//InfoTemp.push_back(temp);

			//IOSAVEMANAGER->saveFile("세이브맵", InfoTemp);

			////지우고 나서 문제가 생겨서 이름을 다시 1번부터 저자시켜준다
			//for (int i = 0; i < InfoObjectTemp.size(); i++)
			//{
			//	InfoObjectTemp[i].infoName = "넘버" + to_string(i + 1);
			//}

			//IOSAVEOBJECTMANAGER->saveFile("오브젝트", InfoObjectTemp);

			//ST_MAP temp0;

			//temp0.heightMap = FILEPATH_MANAGER->GetFilepath(raw);
			//temp0.splat = FILEPATH_MANAGER->GetFilepath(splat);
			//temp0.tile0 = FILEPATH_MANAGER->GetFilepath(tile1);
			//temp0.tile1 = FILEPATH_MANAGER->GetFilepath(tile2);
			//temp0.tile2 = FILEPATH_MANAGER->GetFilepath(tile3);
			//temp0.tile3 = FILEPATH_MANAGER->GetFilepath(tile4);

			//temp0.vecPos = _terrain->getMapPosition();

			//IOMAPMANAGER->saveFile("지형0", temp0);

			//몬스터 위치 ,값 저장/////////////////////////////////
			vector<tagSaveMonster> monsterTemp;
			tagSaveMonster Mtemp;

			if (_monster.size() != 0)
			{
				for (int i = 0; i < _monster.size(); i++)
				{
					Mtemp.infoName = "몬스터넘버" + to_string(i + 1);
					Mtemp.monsterNumber = _monster[i]->getObjectNumber();
					Mtemp.monsterX = _monster[i]->_transform->GetWorldPosition().x;
					Mtemp.monsterY = _monster[i]->_transform->GetWorldPosition().y;
					Mtemp.monsterZ = _monster[i]->_transform->GetWorldPosition().z;
					Mtemp.scale = 1.0f;

					monsterTemp.push_back(Mtemp);
				}

				IOSAVEMONSTERMANAGER->saveFile("몬스터", monsterTemp);
			}

			//노드지정 ,위치,값 저장////////////////////////////
			vector<tagSaveNode> nodeTemp;
			tagSaveNode nTemp;

			for (int i = 0; i < _terrain->getDijkstra().getVecNode().size(); i++)
			{
				nTemp.infoName = "노드" + to_string(i + 1);
				nTemp.Inumber = i; // 벡터의 인덱스값 저장
				nTemp.nodeX = _terrain->getDijkstra().getVecNode()[i]->getPosition().x;//위치값 저장
				nTemp.nodeY = _terrain->getDijkstra().getVecNode()[i]->getPosition().y;//위치값 저장
				nTemp.nodeZ = _terrain->getDijkstra().getVecNode()[i]->getPosition().z;//위치값 저장

				for (int j = 0; j < _terrain->getDijkstra().getadjNode()[i].size(); j++)
				{
					nTemp.nodeFS.push_back(make_pair(_terrain->getDijkstra().getadjNode()[i][j].first, _terrain->getDijkstra().getadjNode()[i][j].second)); 	//first는 벡터에서 몇번 노드인지를 알려준다.	
																																								//second는 현재 노드에서 j노드까지의 거리값을 가진다.
				}

				nodeTemp.push_back(nTemp);
			}

			IOSAVENODEMANAGER->saveFile("노드", nodeTemp);
		}

	}
	else
	{
		_SaveButton.FT = false;
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

	//save버튼
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

	//지형 렌더
	_terrain->render(&_mainCamera, _sceneBaseDirectionLight);

	//오브젝트 렌더
	if (!m_vecObject.empty()) _mapObject->objectRenderTool(m_vecObject, &_mainCamera, _sceneBaseDirectionLight);

	xMeshSkinned::setCamera(&_mainCamera);
	xMeshSkinned::setTechniqueName("Toon");
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resource/Testures/Ramp_1.png"));
	xMeshSkinned::setBaseLight(this->_sceneBaseDirectionLight);

	//몬스터 렌더
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

	//다익스트라 노드 그리기
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

void leftViewHead::loadNode(void)
{
}
