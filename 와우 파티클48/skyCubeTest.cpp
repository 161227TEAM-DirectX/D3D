#include "stdafx.h"
#include "skyCubeTest.h"

HRESULT skyCubeTest::init(void)
{
	//ȯ�� ����Ʈ(FX) �ʱ�ȭ
	_environmentEffect = RM_SHADERFX->loadResource("RESOURCE/FX/EnvironmentCUBE.fx");
	//ȯ��� ����
	this->setEnvironment("RESOURCE/TEXTURECUBE/GanjiCube.dds");

	return S_OK;
}

void skyCubeTest::release(void)
{
	SAFE_RELEASE(_environmentTexture);
	SAFE_RELEASE(_environmentCubeMesh);
	SAFE_RELEASE(_environmentEffect);
}

void skyCubeTest::update(void)
{
	//ī�޶� ������Ʈ
	//this->updateForCamera();
}

void skyCubeTest::render(void)
{
	this->renderEnvironment();
}

void skyCubeTest::setEnvironment(string cubeFileName)
{
	//������ ȯ����� ���õǾ� ������ �𸣴� ����ϰ� ����� �����ϱ�
	SAFE_RELEASE(_environmentTexture);

	//ȯ��� �ε�
	D3DXCreateCubeTextureFromFile(_device, cubeFileName.c_str(), &_environmentTexture);

	//ȯ��� �ε��� �Ǿ����� ������ ����ó��
	if (_environmentCubeMesh == NULL)
	{
		D3DXCreateSphere(_device, 3.0f, 20, 20, &_environmentCubeMesh, NULL);
	}
}

void skyCubeTest::renderEnvironment(void)
{
	//ȯ��� �ε��Ȱ� ���ٸ� �ٷ� ���Ͻ�Ű��
	if (_environmentTexture == NULL) return;

	//ȯ��� ����Ʈ ����
	_environmentEffect->SetTexture("MyCube_Tex", _environmentTexture);

	//WVP ���
	D3DXMATRIXA16 matWorld = _mainCamera->GetFinalMatrix();
	D3DXMATRIXA16 matViewProj = _mainCamera->getViewProjectionMatrix();
	D3DXMATRIXA16 matWVP = matWorld * matViewProj;

	_environmentEffect->SetMatrix("matWVP", &matWVP);
	_environmentEffect->SetMatrix("matWorld", &matWorld);

	//���̴��� ����
	UINT iPassNum = 0;

	//����Ʈ�� ����������
	_environmentEffect->Begin(&iPassNum, 0);
	//�н� ����� for������ ������
	for (UINT i = 0; i < iPassNum; i++)
	{
		_environmentEffect->BeginPass(i);
		//����
		_environmentCubeMesh->DrawSubset(0);
		_environmentEffect->EndPass();
	}
	_environmentEffect->End();
}
