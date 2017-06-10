#include "stdafx.h"
#include "directionTestScene.h"

HRESULT directionTestScene::init(void)
{
	//비행기 정점버퍼 생성
	_device->CreateVertexBuffer(
		sizeof(MYVERTEX) * 3,
		D3DUSAGE_WRITEONLY,
		MYVERTEX::FVF,
		D3DPOOL_DEFAULT,
		&_planeVB,
		NULL);

	LPMYVERTEX pVertices;
	_planeVB->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].pos = D3DXVECTOR3(0, 0, 1);
	pVertices[0].color = 0xffff0000;
	pVertices[1].pos = D3DXVECTOR3(1, 0, -1);
	pVertices[1].color = 0xff00ff00;
	pVertices[2].pos = D3DXVECTOR3(-1, 0, -1);
	pVertices[2].color = 0xff0000ff;

	_planeVB->Unlock();

	//비행기 월드행렬 초기화
	D3DXMatrixIdentity(&_matPlane);	//단위행렬(항등행렬)
	//위치(0, 0, 0)
	//스케일(1, 1, 1)
	//회전 없다

	//회전 초기화
	_yawAngle = 0.0f;
	_yawSpeed = D3DXToRadian(90);

	//위치 초기화
	_pos.x = 0.0f;
	_pos.y = 0.0f;
	_pos.z = 0.0f;

	//위치1 초기화
	_pos2.x = 3.0f;
	_pos2.y = 0.0f;
	_pos2.z = 0.0f;
	D3DXMatrixIdentity(&_matPlane2);

	//이동 속도
	_moveSpeed = 3.0f;


	//뷰, 투영행렬 준비
//====================================================================
//			## 뷰 스페이스 ##
//====================================================================
	//뷰행렬 및 뷰벡터 준비
	D3DXMATRIXA16 matView;
	D3DXVECTOR3	lookAtPos(0, 0, 0);			//0,0,0위치를 바라본다
	D3DXVECTOR3 eyePos(0, 20, 0);			//카메라 눈의 위치
	D3DXVECTOR3 up(0, 0, 1);				//상방벡터 그냥 0,1,0

	//D3DXMatrixLookAtLH(뷰행렬, 눈위치, 바라볼위치, 업벡터)
	D3DXMatrixLookAtLH(&matView, &eyePos, &lookAtPos, &up);

	//뷰행렬 세팅
	_device->SetTransform(D3DTS_VIEW, &matView);

//====================================================================
//			## 투영 ##
//====================================================================
	//투영행렬 준비
	D3DXMATRIXA16 matProjection;

	D3DXMatrixPerspectiveFovLH(
		&matProjection,		//투영행렬
		D3DXToRadian(60),	//화각 60도
		(float)(WINSIZEX) / static_cast<float>(WINSIZEY), //화면 종횡비
		0.01f,				//근거리 평면 거리(0일때 뎁스가 꼬인다)
		100.0f);			//원거리 평면 거리

	//투영행렬 세팅
	_device->SetTransform(D3DTS_PROJECTION, &matProjection);
//============================================================================

	//라이트기능은 잠시 꺼두자
	_device->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

void directionTestScene::release(void)
{
	SAFE_RELEASE(_planeVB);
}

void directionTestScene::update(void)
{
	//회전 컨트롤
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_yawAngle -= _yawSpeed * _timeDelta;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_yawAngle += _yawSpeed * _timeDelta;
	}
	//각도 값만큼 회전행렬
	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationY(&matRot, _yawAngle);

	//컨트롤 회전 방향대로 전진시키기
	//초당 이동량
	float moveDelta = _moveSpeed * _timeDelta; 

	//회전을 먹이기전 사물의 진행방향
	D3DXVECTOR3 moveDir(0, 0, 1);
	//진행방향에 회전행렬을 주기
	D3DXVec3TransformNormal(&moveDir, &moveDir, &matRot);

	//이동벡터 이동량 * 진행방향
	D3DXVECTOR3 moveVector = moveDir * moveDelta;

	//위치값에 이동량을 더한다
	_pos += moveVector;

	//위치행렬
	D3DXMATRIXA16 matPostion;
	D3DXMatrixTranslation(&matPostion,
		_pos.x,
		_pos.y,
		_pos.z);
	_matPlane = matRot * matPostion;

	//두번째 비행기에 대한 행렬
	D3DXMATRIXA16 matPostion2;
	D3DXMatrixTranslation(&matPostion2,
		_pos2.x,
		_pos2.y,
		_pos2.z);
	_matPlane = matRot * matPostion;

	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		//_matPlane2 = matPostion2 *  _matPlane;
		_matPlane2 = _matPlane *  matPostion2;
		//mat = _matPlane2;
	}
	else
	{
		_matPlane2 = matPostion2;
		mat = _matPlane2;
	}


	/*
	//회전행렬
	D3DXMATRIXA16 matRot2;

	//바라봐야 할 방향 벡터
	D3DXVECTOR3 dirToTarget = _pos - _pos2;

	//정규화 시켜주기
	D3DXVec3Normalize(&dirToTarget, &dirToTarget);

	//비행기2가 바라보는 곳, 회전은 하지 않는다
	D3DXVECTOR3 dir2(0, 0, 1);
	
	//각도차
	float yawAngle = acosf(D3DXVec3Dot(&dir2, &dirToTarget));

	//정면과 타겟 방향 외적
	D3DXVECTOR3 cross;
	D3DXVec3Cross(&cross, &dir2, &dirToTarget);

	//외적 결과는 정규화 되지 않았다
	//정규화 시켜주기
	D3DXVec3Normalize(&cross, &cross);

	//그외 외적의 결과를 축으로 한 회전행렬
	D3DXMatrixRotationAxis(&matRot2, &cross, yawAngle);

	_matPlane2 = matRot2 * matPostion2;
	*/
}

void directionTestScene::render(void)
{
	//비행기 월드행렬 세팅
	_device->SetTransform(D3DTS_WORLD, &_matPlane);

	//비행기 그리기
	_device->SetStreamSource(0, _planeVB, 0, sizeof(MYVERTEX));
	_device->SetFVF(MYVERTEX::FVF);
	_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	//비행기2 월드행렬 세팅
	_device->SetTransform(D3DTS_WORLD, &_matPlane2);

	//비행기2 그리기
	_device->SetStreamSource(0, _planeVB, 0, sizeof(MYVERTEX));
	_device->SetFVF(MYVERTEX::FVF);
	_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	/*
	//다음과 같은 멤버 변수로 행렬 요소값에 접근가능
	mat._11, mat._12, mat._13, mat._14
	mat._21, mat._22, mat._23, mat._24
	mat._31, mat._32, mat._33, mat._34
	mat._41, mat._42, mat._43, mat._44
	
	mat.m[0][0], mat.m[0][1], mat.m[0][2], mat.m[0][3]
	mat.m[1][0], mat.m[1][1], mat.m[1][2], mat.m[1][3]
	mat.m[2][0], mat.m[2][1], mat.m[2][2], mat.m[2][3]
	mat.m[3][0], mat.m[3][1], mat.m[3][2], mat.m[3][3]
	*/

	//D3DXMatrixIdentity(&mat);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			char str[128];
			sprintf(str, "[%2.2f]", mat.m[i][j]);
			FONTMANAGER->fontOut(str, 300 + j * 80, i * 30, 0xffffffff);
		}
	}


}
