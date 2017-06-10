#include "stdafx.h"
#include "defMeshMaterialScene.h"

HRESULT defMeshMaterialScene::init(void)
{
	//ī�޶� ��ġ ����
	_mainCamera.SetLocalPosition(0, 0, -10);

	//ť�����

	//ť��޽�
	D3DXCreateBox(_device, 1.0f, 1.0f, 1.0f, &_meshCube, NULL);
	//ť����ġ
	_transCube.SetWorldPosition(D3DXVECTOR3(-2.0f, 2.0f, 0.0f));
	//ť����͸���
	_cubeMeterial.Diffuse = D3DXCOLOR(0xffff0000);
	_cubeMeterial.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_cubeMeterial.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	_cubeMeterial.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_cubeMeterial.Power = 10.0f;

	//�� ����

	//���޽�
	D3DXCreateSphere(_device, 1.0f, 100, 100, &_meshSphere, NULL);
	//����ġ
	_transSphere.SetWorldPosition(D3DXVECTOR3(-2.0f, -2.0f, 0.0f));
	//ť����͸���
	_sphereMeterial.Diffuse = D3DXCOLOR(0xff00ff00);
	_sphereMeterial.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_sphereMeterial.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	_sphereMeterial.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_sphereMeterial.Power = 10.0f;

	//������ ����
	//�����ڸ޽�
	D3DXCreateTeapot(_device, &_meshTeapot, NULL);
	//��������ġ
	_transTeapot.SetWorldPosition(D3DXVECTOR3(2.0f, 2.0f, 0.0f));
	//�����ڸ��͸���
	_teapotMeterial.Diffuse = D3DXCOLOR(0xff0000ff);
	_teapotMeterial.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_teapotMeterial.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	_teapotMeterial.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_teapotMeterial.Power = 10.0f;

	//���� ����
	//���Ӹ޽�
	D3DXCreateTorus(_device, 0.5f, 1.0f, 25, 25, &_meshTorus, NULL);
	//������ġ
	_transTorus.SetWorldPosition(D3DXVECTOR3(2.0f, -2.0f, 0.0f));
	//���Ӹ��͸���
	_torusMeterial.Diffuse = D3DXCOLOR(0xffff00ff);
	_torusMeterial.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_torusMeterial.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	_torusMeterial.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_torusMeterial.Power = 10.0f;

	//����Ʈ
	ZeroMemory(&_light, sizeof(_light));
	_light.Type = D3DLIGHT_DIRECTIONAL;				//����Ÿ��
	_light.Direction = D3DXVECTOR3(-1.0f, 0, 0);	//�ٶ� ��ġ
	_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�����
	_light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//����Ʈ ����
	_device->SetRenderState(D3DRS_LIGHTING, TRUE);	//���� ����ϰڴ�
	_device->SetLight(0, &_light);					//0�� ���� ��������
	_device->LightEnable(0, TRUE);					//0�� ���� Ȱ��ȭ

													//Ambient ����
	_device->SetRenderState(D3DRS_AMBIENT, 0xff000000);
	//����ŧ�� ����
	_device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	return S_OK;
}

void defMeshMaterialScene::release(void)
{
	//�޽� ����
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

	//���̾� ����
	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	//����Ʈ ���� ���ΰ���
	_light.Direction = _lightTrans.GetForward();
	//���ŵ� ����Ʈ �ٽ� ����
	_device->SetLight(0, &_light);


	//ī�޶� ����Ʈ��Ʈ��
	_mainCamera.DefaultControl(_timeDelta);
	//ī�޶� ������Ʈ
	_mainCamera.updateCamToDevice();
}

void defMeshMaterialScene::render(void)
{
	//ť�귻��
	_device->SetMaterial(&_cubeMeterial);
	_transCube.SetDeviceWorld();
	_meshCube->DrawSubset(0);

	//�� ����
	_device->SetMaterial(&_sphereMeterial);
	_transSphere.SetDeviceWorld();
	_meshSphere->DrawSubset(0);

	//������ ����
	_device->SetMaterial(&_teapotMeterial);
	_transTeapot.SetDeviceWorld();
	_meshTeapot->DrawSubset(0);

	//���� ����
	_device->SetMaterial(&_torusMeterial);
	_transTorus.SetDeviceWorld();
	_meshTorus->DrawSubset(0);
}
