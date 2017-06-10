#include "stdafx.h"
#include "phongShaderTest.h"

HRESULT phongShaderTest::init(void)
{
	//ī�޶� ��ġ����
	_mainCamera.SetLocalPosition(0, 0, -10);

	//������
	if (FAILED(D3DXCreateSphere(_device, 3.0f, 50, 50, &_mesh, NULL))) return E_FAIL;

	//���̴� �ε��� ������ ������ ���� ������ ������ �޾ƿ� Error����
	LPD3DXBUFFER	error = NULL;
	DWORD			shaderFlag = 0;

	//fx���Ϸ� ���� ����Ʈ ��ü�� �ε��Ѵ�
	D3DXCreateEffectFromFile(
		_device,				//����̽�
		"BlinnPhong.fx",		//�����̸�
		NULL,					//���̴��� �������Ҷ� �߰��� ����� #define����
		NULL,					//���̴��� �������Ҷ� #include���ù� ó���Ҷ� ����� �������̽� �÷���
		shaderFlag,				//���̴� ������ �÷���
		NULL,					//���̴� �Ű������� ������ �޸� Ǯ
		&_effect,				//�ε��� ���̴� ����Ʈ ������
		&error);				//���̴� �ε��ϰ� ������ �Ҷ� �����Ͽ� ������ ����� ������ۿ� �����޼����� ����

								//������ �ִٸ�
	if (error != NULL)
	{
		//�������� ������
		SAFE_RELEASE(error);
		return E_FAIL;
	}

	return S_OK;
}

void phongShaderTest::release(void)
{
	SAFE_RELEASE(_effect);
	SAFE_RELEASE(_mesh);
}

void phongShaderTest::update(void)
{
	//����Ʈ����
	_lightTrans.DefaultMyControl(_timeDelta);
	//ī�޶�
	_mainCamera.DefaultControl(_timeDelta);
	_mainCamera.updateCamToDevice();
}

void phongShaderTest::render(void)
{
	//����Ʈ�� �������� ���� �����ϱ�
	D3DXMATRIXA16 matWorld = _meshTrans.GetFinalMatrix();
	//������ļ���
	_effect->SetMatrix("matWorld", &matWorld);
	
	//����̽��κ��� ���õ� ����İ� ��������� ���
	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProjection;
	_device->GetTransform(D3DTS_VIEW, &matView);
	_device->GetTransform(D3DTS_PROJECTION, &matProjection);

	//����� ����
	_effect->SetMatrix("matView", &matView);
	//������� ����
	_effect->SetMatrix("matProjection", &matProjection);
	//�÷����� ����
	D3DXVECTOR4 vMaterialDiffuseColor(1, 0, 0, 1);
	_effect->SetVector("vMaterialDiffuseColor", &vMaterialDiffuseColor);
	D3DXVECTOR4 vMaterialSpecularColor(1, 1, 1, 1);
	_effect->SetVector("vMaterialSpecularColor", &vMaterialSpecularColor);
	//�Ŀ�
	_effect->SetFloat("fPower", 30.0f);


	//������ ����
	D3DXVECTOR4 lightDir(_lightTrans.GetForward(), 1);
	_effect->SetVector("vLightDir", &lightDir);
	D3DXVECTOR4 eyePos(_mainCamera.GetWorldPosition(), 1);
	_effect->SetVector("vEyePos", &eyePos);




	//��ũ�м���
	_effect->SetTechnique("MyShader");

	//���̴��� ť�귻��
	UINT iPassNum = 0;

	//����Ʈ�� ����������
	_effect->Begin(&iPassNum, 0);

	//�н� ����� for������ ������
	for (UINT i = 0; i < iPassNum; i++)
	{
		_effect->BeginPass(i);

		//����
		_mesh->DrawSubset(0);

		_effect->EndPass();
	}

	_effect->End();

	_lightTrans.RenderGimozo();
}
