#include "stdafx.h"
#include "defMeshMaterialScene.h"

HRESULT defMeshMaterialScene::init(void)
{
	//카메라 위치 세팅
	_mainCamera.SetLocalPosition(0, 0, -10);

	//큐브생성

	//큐브메쉬
	D3DXCreateBox(_device, 1.0f, 1.0f, 1.0f, &_meshCube, NULL);
	//큐브위치
	_transCube.SetWorldPosition(D3DXVECTOR3(-2.0f, 2.0f, 0.0f));
	//큐브메터리얼
	_cubeMeterial.Diffuse = D3DXCOLOR(0xffff0000);
	_cubeMeterial.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_cubeMeterial.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	_cubeMeterial.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_cubeMeterial.Power = 10.0f;

	//구 생성

	//구메시
	D3DXCreateSphere(_device, 1.0f, 100, 100, &_meshSphere, NULL);
	//구위치
	_transSphere.SetWorldPosition(D3DXVECTOR3(-2.0f, -2.0f, 0.0f));
	//큐브메터리얼
	_sphereMeterial.Diffuse = D3DXCOLOR(0xff00ff00);
	_sphereMeterial.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_sphereMeterial.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	_sphereMeterial.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_sphereMeterial.Power = 10.0f;

	//주전자 생성
	//주전자메시
	D3DXCreateTeapot(_device, &_meshTeapot, NULL);
	//주전자위치
	_transTeapot.SetWorldPosition(D3DXVECTOR3(2.0f, 2.0f, 0.0f));
	//주전자메터리얼
	_teapotMeterial.Diffuse = D3DXCOLOR(0xff0000ff);
	_teapotMeterial.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_teapotMeterial.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	_teapotMeterial.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_teapotMeterial.Power = 10.0f;

	//도넛 생성
	//도넛메시
	D3DXCreateTorus(_device, 0.5f, 1.0f, 25, 25, &_meshTorus, NULL);
	//도넛위치
	_transTorus.SetWorldPosition(D3DXVECTOR3(2.0f, -2.0f, 0.0f));
	//도넛메터리얼
	_torusMeterial.Diffuse = D3DXCOLOR(0xffff00ff);
	_torusMeterial.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_torusMeterial.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	_torusMeterial.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_torusMeterial.Power = 10.0f;

	//라이트
	ZeroMemory(&_light, sizeof(_light));
	_light.Type = D3DLIGHT_DIRECTIONAL;				//광원타입
	_light.Direction = D3DXVECTOR3(-1.0f, 0, 0);	//바라볼 위치
	_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//백색광
	_light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//라이트 세팅
	_device->SetRenderState(D3DRS_LIGHTING, TRUE);	//광원 사용하겠다
	_device->SetLight(0, &_light);					//0번 광원 정보세팅
	_device->LightEnable(0, TRUE);					//0번 광원 활성화

													//Ambient 세팅
	_device->SetRenderState(D3DRS_AMBIENT, 0xff000000);
	//스펙큘러 세팅
	_device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	return S_OK;
}

void defMeshMaterialScene::release(void)
{
	//메쉬 해제
	SAFE_RELEASE(_meshCube);
	SAFE_RELEASE(_meshSphere);
	SAFE_RELEASE(_meshTeapot);
	SAFE_RELEASE(_meshTorus);
}

void defMeshMaterialScene::update(void)
{
	float deltaMove = 3.0f * _timeDelta;
	float deltaAngle = D3DXToRadian(90) * _timeDelta;

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON) == FALSE)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_lightTrans.MovePositionSelf(-deltaMove, 0.0f, 0.0f);
		}
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			_lightTrans.MovePositionSelf(deltaMove, 0.0f, 0.0f);
		}
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_lightTrans.MovePositionSelf(0.0f, 0.0f, deltaMove);
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			_lightTrans.MovePositionSelf(0.0f, 0.0f, -deltaMove);
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_lightTrans.RotateSelf(0.0f, -deltaAngle, 0.0f);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_lightTrans.RotateSelf(0.0f, deltaAngle, 0.0f);
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_lightTrans.RotateSelf(-deltaAngle, 0.0f, 0.0f);
		}
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_lightTrans.RotateSelf(deltaAngle, 0.0f, 0.0f);
		}
	}

	//와이어 보기
	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	//라이트 방향 새로갱신
	_light.Direction = _lightTrans.GetForward();
	//갱신된 라이트 다시 세팅
	_device->SetLight(0, &_light);


	//카메라 디폴트컨트롤
	_mainCamera.DefaultControl(_timeDelta);
	//카메라 업데이트
	_mainCamera.updateCamToDevice();
}

void defMeshMaterialScene::render(void)
{
	//큐브렌더
	_device->SetMaterial(&_cubeMeterial);
	_transCube.SetDeviceWorld();
	_meshCube->DrawSubset(0);

	//구 렌더
	_device->SetMaterial(&_sphereMeterial);
	_transSphere.SetDeviceWorld();
	_meshSphere->DrawSubset(0);

	//주전자 렌더
	_device->SetMaterial(&_teapotMeterial);
	_transTeapot.SetDeviceWorld();
	_meshTeapot->DrawSubset(0);

	//도넛 렌더
	_device->SetMaterial(&_torusMeterial);
	_transTorus.SetDeviceWorld();
	_meshTorus->DrawSubset(0);
}
