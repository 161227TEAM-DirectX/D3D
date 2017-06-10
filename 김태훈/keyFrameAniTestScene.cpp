#include "stdafx.h"
#include "keyFrameAniTestScene.h"

HRESULT keyFrameAniTestScene::init(void)
{
	//큐브생성
	this->CreateCube();

	//메인카메라 시작위치
	_mainCamera.SetLocalPosition(-2, 5, -15);

	/*뼈대 조립*/

	//루트
	_boneMap.insert(make_pair("Pivot", new transform));
	_boneMap.insert(make_pair("Root", new transform));
	//궁뎅이
	_boneMap.insert(make_pair("LeftHip", new transform));
	_boneMap.insert(make_pair("RightHip", new transform));
	//허벅지
	_boneMap.insert(make_pair("LeftUpLeg", new transform));
	_boneMap.insert(make_pair("RightUpLeg", new transform));
	//종아리
	_boneMap.insert(make_pair("LeftDownLeg", new transform));
	_boneMap.insert(make_pair("RightDownLeg", new transform));
	//발
	_boneMap.insert(make_pair("LeftFoot", new transform));
	_boneMap.insert(make_pair("RightFoot", new transform));

	/*조립*/
	_boneMap["Root"]->AttachTo(_boneMap["Pivot"]);
	_boneMap["LeftHip"]->AttachTo(_boneMap["Root"]);
	_boneMap["RightHip"]->AttachTo(_boneMap["Root"]);
	_boneMap["LeftHip"]->SetLocalPosition(-1.0f, 0.0f, 0.0f);
	_boneMap["RightHip"]->SetLocalPosition(1.0f, 0.0f, 0.0f);

	_boneMap["LeftUpLeg"]->AttachTo(_boneMap["LeftHip"]);
	_boneMap["RightUpLeg"]->AttachTo(_boneMap["RightHip"]);
	_boneMap["LeftUpLeg"]->SetLocalPosition(0.0f, -0.5f, 0.0f);
	_boneMap["RightUpLeg"]->SetLocalPosition(0.0f, -0.5f, 0.0f);

	_boneMap["LeftDownLeg"]->AttachTo(_boneMap["LeftUpLeg"]);
	_boneMap["RightDownLeg"]->AttachTo(_boneMap["RightUpLeg"]);
	_boneMap["LeftDownLeg"]->SetLocalPosition(0.0f, -2.0f, 0.0f);
	_boneMap["RightDownLeg"]->SetLocalPosition(0.0f, -2.0f, 0.0f);

	_boneMap["LeftFoot"]->AttachTo(_boneMap["LeftDownLeg"]);
	_boneMap["RightFoot"]->AttachTo(_boneMap["RightUpLeg"]);
	_boneMap["LeftFoot"]->SetLocalPosition(0.0f, -2.0f, 0.0f);
	_boneMap["RightFoot"]->SetLocalPosition(0.0f, -2.0f, 0.0f);

	/*뼈에 붙는 메쉬*/
	
	//루트메쉬
	_meshMap.insert(make_pair("Root", new transform));
	_meshMap["Root"]->AttachTo(_boneMap["Root"]);

	_meshMap.insert(make_pair("LeftHip", new transform));
	_meshMap["LeftHip"]->AttachTo(_boneMap["LeftHip"]);
	_meshMap["LeftHip"]->Reset();

	_meshMap.insert(make_pair("RightHip", new transform));
	_meshMap["RightHip"]->AttachTo(_boneMap["RightHip"]);
	_meshMap["RightHip"]->Reset();

	_meshMap.insert(make_pair("LeftUpLeg", new transform));
	_meshMap["LeftUpLeg"]->AttachTo(_boneMap["LeftUpLeg"]);
	_meshMap["LeftUpLeg"]->Reset();
	_meshMap["LeftUpLeg"]->SetScale(1, 2, 1);
	_meshMap["LeftUpLeg"]->SetLocalPosition(0, -1, 0);

	_meshMap.insert(make_pair("RightUpLeg", new transform));
	_meshMap["RightUpLeg"]->AttachTo(_boneMap["RightUpLeg"]);
	_meshMap["RightUpLeg"]->Reset();
	_meshMap["RightUpLeg"]->SetScale(1, 2, 1);
	_meshMap["RightUpLeg"]->SetLocalPosition(0, -1, 0);

	_meshMap.insert(make_pair("LeftDownLeg", new transform));
	_meshMap["LeftDownLeg"]->AttachTo(_boneMap["LeftDownLeg"]);
	_meshMap["LeftDownLeg"]->Reset();
	_meshMap["LeftDownLeg"]->SetScale(1, 2, 1);
	_meshMap["LeftDownLeg"]->SetLocalPosition(0, -1, 0);

	_meshMap.insert(make_pair("RightDownLeg", new transform));
	_meshMap["RightDownLeg"]->AttachTo(_boneMap["RightDownLeg"]);
	_meshMap["RightDownLeg"]->Reset();
	_meshMap["RightDownLeg"]->SetScale(1, 2, 1);
	_meshMap["RightDownLeg"]->SetLocalPosition(0, -1, 0);

	_meshMap.insert(make_pair("LeftFoot", new transform));
	_meshMap["LeftFoot"]->AttachTo(_boneMap["LeftFoot"]);
	_meshMap["LeftFoot"]->Reset();
	_meshMap["LeftFoot"]->SetScale(1, 0.5f, 1.5f);
	_meshMap["LeftFoot"]->SetLocalPosition(0, -0.25f, 0.25f);

	_meshMap.insert(make_pair("RightFoot", new transform));
	_meshMap["RightFoot"]->AttachTo(_boneMap["RightFoot"]);
	_meshMap["RightFoot"]->Reset();
	_meshMap["RightFoot"]->SetScale(1, 0.5f, 1.5f);
	_meshMap["RightFoot"]->SetLocalPosition(0, -0.25f, 0.25f);

	//키프레임 생성 (초당 10프레임씩 증가 된다고 가정하기)

	//루트 추가
	KEY_FRAMES rootHipKey;
	_boneMap["Root"]->SetRotateLocal(0, 0, 0);
	rootHipKey.push_back(new KEY_FRAME(0, *_boneMap["Root"])); //0번프레임

	_boneMap["Root"]->SetRotateLocal(0, D3DXToRadian(30), 0);
	rootHipKey.push_back(new KEY_FRAME(15, *_boneMap["Root"])); //15번프레임

	_boneMap["Root"]->SetRotateLocal(0, 0, 0);
	rootHipKey.push_back(new KEY_FRAME(30, *_boneMap["Root"])); //30번프레임

	//맵에 추가
	_animationFrames.insert(make_pair("Root", rootHipKey));

	//오른쪽 엉덩이 추가
	KEY_FRAMES rightHipKey;
	_boneMap["RightHip"]->SetRotateLocal(0, 0, 0);
	rightHipKey.push_back(new KEY_FRAME(0, *_boneMap["RightHip"])); //0번프레임

	_boneMap["RightHip"]->SetRotateLocal(D3DXToRadian(-120), 0, 0);
	rightHipKey.push_back(new KEY_FRAME(10, *_boneMap["RightHip"])); //10번프레임

	_boneMap["RightHip"]->SetRotateLocal(D3DXToRadian(-120), 0, D3DXToRadian(90));
	rightHipKey.push_back(new KEY_FRAME(20, *_boneMap["RightHip"])); //20번프레임

	_boneMap["RightHip"]->SetRotateLocal(0, 0, 0);
	rightHipKey.push_back(new KEY_FRAME(30, *_boneMap["RightHip"])); //30번프레임

	//맵에 추가
	_animationFrames.insert(make_pair("RightHip", rightHipKey));

	//오른쪽 다리추가
	KEY_FRAMES rightDownLegKey;
	_boneMap["RightDownLeg"]->SetRotateLocal(0, 0, 0);
	rightDownLegKey.push_back(new KEY_FRAME(0, *_boneMap["RightDownLeg"])); //0번프레임

	_boneMap["RightDownLeg"]->SetRotateLocal(0, 0, 0);
	rightDownLegKey.push_back(new KEY_FRAME(5, *_boneMap["RightDownLeg"])); //5번프레임

	_boneMap["RightDownLeg"]->SetRotateLocal(D3DXToRadian(60), 0, 0);
	rightDownLegKey.push_back(new KEY_FRAME(10, *_boneMap["RightDownLeg"])); //10번프레임

	_boneMap["RightDownLeg"]->SetRotateLocal(0, D3DXToRadian(180), 0);
	rightDownLegKey.push_back(new KEY_FRAME(20, *_boneMap["RightDownLeg"])); //20번프레임

	_boneMap["RightDownLeg"]->SetRotateLocal(0, 0, 0);
	rightDownLegKey.push_back(new KEY_FRAME(30, *_boneMap["RightDownLeg"])); //30번프레임
	
	//맵에 추가
	_animationFrames.insert(make_pair("RightDownLeg", rightDownLegKey));

	//본 자동 업데이트 되는것 막기
	for each(auto iter in _boneMap)
	{
		iter.second->SetAutoUpdate(false);
	}
	_trans.SetAutoUpdate(false);

	_nowFrame = 0.0f;

	_trans.AddChild(_boneMap["Pivot"]);
	_boneMap["Pivot"]->SetLocalPosition(0, 5, 0);

	_device->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

void keyFrameAniTestScene::release(void)
{
	for each(auto iter in _boneMap)
	{
		SAFE_DELETE(iter.second);
	}
	/*
	for (MAP_TRANS_ITER iter = _boneMap.begin(); iter != _boneMap.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	*/

	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_ib);
}

void keyFrameAniTestScene::update(void)
{
	float deltaMove = 3.0f * _timeDelta;
	float deltaAngle = D3DXToRadian(90) * _timeDelta;



	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON) == FALSE)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_trans.MovePositionSelf(-deltaMove, 0.0f, 0.0f);
		}
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			_trans.MovePositionSelf(deltaMove, 0.0f, 0.0f);
		}
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_trans.MovePositionSelf(0.0f, 0.0f, deltaMove);
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			_trans.MovePositionSelf(0.0f, 0.0f, -deltaMove);
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_trans.RotateSelf(0.0f, -deltaAngle, 0.0f);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_trans.RotateSelf(0.0f, deltaAngle, 0.0f);
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_trans.RotateSelf(-deltaAngle, 0.0f, 0.0f);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_trans.RotateSelf(deltaAngle, 0.0f, 0.0f);
		}
	}

	
	static float angle = 0.0f;
	angle += D3DXToRadian(360) * _timeDelta;
	_boneMap["Pivot"]->SetLocalPosition(0, 5 + sin(angle) * 0.5f, 0);

	//프레임 증가
	_nowFrame += 10 * _timeDelta;
	if (_nowFrame > 30.0f) _nowFrame -= 30.0f;

	//애니메이션 처리
	for (MAP_BONE_KEYFRAMES::iterator iter = _animationFrames.begin(); iter != _animationFrames.end(); ++iter)
	{
		KEY_FRAMES keyFrames = iter->second;
		
		int frontIndex = 0;
		int backIndex = keyFrames.size() - 1;
		int centerIndex = (backIndex - frontIndex) / 2 + frontIndex;

		while (frontIndex < backIndex)
		{
			//센터인덱스의 프레임 값이 현재 프레임보다 크냐?
			if (keyFrames[centerIndex]->frame >= _nowFrame)
			{
				backIndex = centerIndex;
				//센터 갱신
				centerIndex = (backIndex - frontIndex) / 2 + frontIndex;
			}
			else//센터인덱스의 프레임 값이 현재 프레임보다 작냐?
			{
				frontIndex = centerIndex;
				//센터 갱신
				centerIndex = (backIndex - frontIndex) / 2 + frontIndex;
			}

			if (backIndex == frontIndex + 1) break;
		}

		//보간해야 할 앞인덱스와 뒤쪽 인덱스를 찾았다
		//현재 프레임이 프론트인덱스와 백인덱스 사이에서 얼만큼 진행되었는가를 0 ~ 1로 얻는다
		//보간역함수로 값을 얻는다
		float t = InverseLerp(keyFrames[frontIndex]->frame,
			keyFrames[backIndex]->frame, _nowFrame);

		//보간시킨다
		_boneMap[iter->first]->Interpolate(
			keyFrames[frontIndex]->trans,
			keyFrames[backIndex]->trans,
			t);

	}

	_trans.UpdateTransform();

	//카메라 디폴트컨트롤
	_mainCamera.DefaultControl(_timeDelta);
	//카메라 업데이트
	_mainCamera.updateCamToDevice();
}

void keyFrameAniTestScene::render(void)
{
	for (MAP_TRANS_ITER iter = _boneMap.begin(); iter != _boneMap.end(); ++iter)
	{
		iter->second->RenderGimozo();
	}

	for (MAP_TRANS_ITER iter = _meshMap.begin(); iter != _meshMap.end(); ++iter)
	{
		iter->second->SetDeviceWorld();
		RenderCube();
	}

	_trans.RenderGimozo();
}

void keyFrameAniTestScene::CreateCube()
{
	//정점 버퍼 만들기
	_device->CreateVertexBuffer(
		sizeof(MYVERTEX) * 24,		//만들어질 정점버퍼의 크기(삼각형은 정점 3개 필요)
		D3DUSAGE_WRITEONLY,			//만들어지는 정점버퍼의 속성(일단 writeonly가 접근이 빠르다, 후에 정점버퍼에 접근이 자주 일어난다면 다이내믹으로 변경하자)
		MYVERTEX::FVF,				//FVF정보
		D3DPOOL_DEFAULT,			//메모리풀 보관방식
		&_vb,						//생성된 버텍버퍼
		NULL);						//그냥 묻지도 따지지도 말고 NULL

									//쿼드 플랜 정점
	MYVERTEX quad[4];
	quad[0].pos = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
	quad[1].pos = D3DXVECTOR3(-0.5f, 0.5f, -0.5f);
	quad[2].pos = D3DXVECTOR3(0.5f, 0.5f, -0.5f);
	quad[3].pos = D3DXVECTOR3(0.5f, -0.5f, -0.5f);

	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationY(&matRot, D3DXToRadian(-90));

	//정점 배열 준비
	MYVERTEX vertices[24];

	//앞면
	memcpy(vertices, quad, sizeof(MYVERTEX) * 4);
	vertices[0].color = 0xffff0000;
	vertices[1].color = 0xffff0000;
	vertices[2].color = 0xffff0000;
	vertices[3].color = 0xffff0000;

	//4개 정점 돌려기
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//우측면 복사
	memcpy(vertices + 4, quad, sizeof(MYVERTEX) * 4);
	vertices[4].color = 0xff00ff00;
	vertices[5].color = 0xff00ff00;
	vertices[6].color = 0xff00ff00;
	vertices[7].color = 0xff00ff00;

	//4개 정점 돌려기
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//뒷면 복사
	memcpy(vertices + 8, quad, sizeof(MYVERTEX) * 4);
	vertices[8].color = 0xffff0000;
	vertices[9].color = 0xffff0000;
	vertices[10].color = 0xffff0000;
	vertices[11].color = 0xffff0000;

	//4개 정점 돌려기
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//좌측면 복사
	memcpy(vertices + 12, quad, sizeof(MYVERTEX) * 4);
	vertices[12].color = 0xff00ff00;
	vertices[13].color = 0xff00ff00;
	vertices[14].color = 0xff00ff00;
	vertices[15].color = 0xff00ff00;

	D3DXMatrixRotationZ(&matRot, D3DXToRadian(-90));

	//4개 정점 돌려기
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//윗면 복사
	memcpy(vertices + 16, quad, sizeof(MYVERTEX) * 4);
	vertices[16].color = 0xff0000ff;
	vertices[17].color = 0xff0000ff;
	vertices[18].color = 0xff0000ff;
	vertices[19].color = 0xff0000ff;

	D3DXMatrixRotationZ(&matRot, D3DXToRadian(-180));

	//4개 정점 돌려기
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&quad[i].pos, &quad[i].pos, &matRot);
	}

	//아래면 복사
	memcpy(vertices + 20, quad, sizeof(MYVERTEX) * 4);
	vertices[20].color = 0xff0000ff;
	vertices[21].color = 0xff0000ff;
	vertices[22].color = 0xff0000ff;
	vertices[23].color = 0xff0000ff;

	//정점 락
	void* pVertices = NULL;
	_vb->Lock(0, 0, &pVertices, 0);
	//메모리 복사
	memcpy(pVertices, vertices, sizeof(MYVERTEX) * 24);
	_vb->Unlock();

	//인덱스 버퍼 생성
	_device->CreateIndexBuffer(
		sizeof(WORD) * 36,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_DEFAULT,
		&_ib,
		NULL);

	//		5--------6
	//     /|       /|
	//    4--------7 |
	//    | |      | | 
	//    | 1------| 2
	//    |/       |/
	//    0--------3

	WORD indices[36];
	for (int i = 0; i < 6; i++)
	{
		//정점 스타트 인덱스
		WORD vertexIndex = i * 4;
		//인덱스 배열 스타트 인덱스
		WORD indicesIndex = i * 6;

		indices[indicesIndex + 0] = vertexIndex + 0;
		indices[indicesIndex + 1] = vertexIndex + 1;
		indices[indicesIndex + 2] = vertexIndex + 2;
		indices[indicesIndex + 3] = vertexIndex + 0;
		indices[indicesIndex + 4] = vertexIndex + 2;
		indices[indicesIndex + 5] = vertexIndex + 3;
	}

	//인덱스 락
	void* pIndices = NULL;
	_ib->Lock(0, 0, &pIndices, 0);
	memcpy(pIndices, indices, sizeof(WORD) * 36);
	_ib->Unlock();
}

void keyFrameAniTestScene::RenderCube()
{
	//SetStreamSource => 쉽게 이야기 하면 버텍스 버퍼 세팅
	_device->SetStreamSource(0, _vb, 0, sizeof(MYVERTEX));

	//인덱스버퍼 세팅
	_device->SetIndices(_ib);

	//지금 그리는 정점에 대한 정점 정보 플래그 세팅
	_device->SetFVF(MYVERTEX::FVF);

	_device->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,	 //라인그리기			
		0,				//시작 버텍스배열 인덱스				
		0,
		24,				//정점 갯수			
		0,				//시작 인덱스배열 인덱스		
		12				//그리는 개체수 라인이 12개
	);
}
