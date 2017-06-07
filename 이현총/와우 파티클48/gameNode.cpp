#include "stdafx.h"
#include "gameNode.h"

gameNode::gameNode() : _environmentTexture(NULL), _environmemtSphereMesh(NULL)
{
	//ȯ�汸 ����Ʈ �ʱ�ȭ
	_environmentEffect = RM_SHADERFX->getResource("Resources/Shaders/EnvironmentCube.fx");
	//����ī�޶� �ʱ�ȭ
	_mainCamera = new camera;
}

gameNode::~gameNode()
{
	//ȯ���ؽ���, �޽� ����
	SAFE_RELEASE(_environmentTexture);
	SAFE_RELEASE(_environmemtSphereMesh);
	//����ī�޶� ����
	SAFE_DELETE(_mainCamera);
}

HRESULT gameNode::init(void)
{
	SetRandomSeed();					//�����õ� �ʱ�ȭ
	CreateDevice();						//����̽� �ʱ�ȭ
	KEYMANAGER->init();					//Ű�Ŵ��� �ʱ�ȭ
	TIMEMANAGER->init();				//Ÿ�ӸŴ��� �ʱ�ȭ
	SCENEMANAGER->init();				//���Ŵ��� �ʱ�ȭ
	FONTMANAGER->init();				//��Ʈ�Ŵ��� �ʱ�ȭ
	GIZMOMANAGER->init();				//�����Ŵ��� �ʱ�ȭ
	RM_TEXTURE->init();					//RM�ؽ��� �ʱ�ȭ
	RM_SHADERFX->init();				//RM���̴�FX �ʱ�ȭ
	RM_XMESH->init();					//RM����ƽX�޽� �ʱ�ȭ
	RM_SKINNED->init();					//RM��Ų��X�޽� �ʱ�ȭ
	PHYSICSMANAGER->init();				//�������Ŵ��� �ʱ�ȭ
	SPRITEMANAGER->init();				//��������Ʈ�Ŵ��� �ʱ�ȭ

	PSM->ParticleSystemSetInit();

	return S_OK;
}

void gameNode::release(void)
{
	//Ű�Ŵ��� �̱��� ����
	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();
	//Ÿ�ӸŴ��� �̱��� ����
	TIMEMANAGER->release();
	TIMEMANAGER->releaseSingleton();
	//���Ŵ��� �̱��� ����
	SCENEMANAGER->release();
	SCENEMANAGER->releaseSingleton();
	//��Ʈ�Ŵ��� �̱��� ����
	FONTMANAGER->release();
	FONTMANAGER->releaseSingleton();
	//�����Ŵ��� �̱��� ����
	GIZMOMANAGER->release();
	GIZMOMANAGER->releaseSingleton();
	//���ҽ��Ŵ��� �̱��� ����
	RM_TEXTURE->clearResource();
	RM_TEXTURE->releaseSingleton();
	RM_SHADERFX->clearResource();
	RM_SHADERFX->releaseSingleton();
	RM_XMESH->clearResource();
	RM_XMESH->releaseSingleton();
	RM_SKINNED->clearResource();
	RM_SKINNED->releaseSingleton();
	//�������Ŵ��� �̱��� ����
	PHYSICSMANAGER->release();
	PHYSICSMANAGER->releaseSingleton();
	//��������Ʈ�Ŵ��� �̱��� ����
	SPRITEMANAGER->release();
	SPRITEMANAGER->releaseSingleton();

	PSM->ParticleSystemSetRelease();
	PSM->releaseSingleton();
	
	
	//����̽� ����
	ReleaseDevice();
}

void gameNode::update(void)
{
}

void gameNode::render(void)
{
}

//���Ŵ������� ó��
void gameNode::renderEnvironment(void)
{
	//ȯ�� �� �ε��Ȱ� ���ٸ� �����ض�
	if (_environmentTexture == NULL) return;

	//ȯ�� ����Ʈ ����
	_environmentEffect->SetTexture("MyCube_Tex", _environmentTexture);

	//WVP ��Ʈ����
	D3DXMATRIXA16 matWorld = _mainCamera->GetFinalMatrix();
	D3DXMATRIXA16 matViewProj = _mainCamera->getViewProjectionMatrix();
	D3DXMATRIXA16 matWVP = matWorld * matViewProj;

	//����Ʈ ����
	_environmentEffect->SetMatrix("matWVP", &matWVP);
	_environmentEffect->SetMatrix("matWorld", &matWorld);

	//���̴� �׷���
	UINT numPass;
	_environmentEffect->Begin(&numPass, 0);		//���̴��� �׸��ٴ� ���� �˸��� pass ���� ��´�.
	for (UINT i = 0; i < numPass; i++)			//���� ����� ����.
	{
		_environmentEffect->BeginPass(i);		//i��° ��������
		_environmemtSphereMesh->DrawSubset(0);	//�� �׷���
		_environmentEffect->EndPass();			//i��° ������
	}
	_environmentEffect->End();					//���̴��� �׸��� ��
}

void gameNode::setEnvironment(string cubeFilePath)
{
	//������ ȯ����� ���õǾ������� �𸣴� ���� ���������ְ� ��������
	SAFE_RELEASE(_environmentTexture);

	//ȯ��� �ε�
	D3DXCreateCubeTextureFromFile(_device, cubeFilePath.c_str(), &_environmentTexture);

	//ȯ�汸 �ε��Ǿ����� �ʴٸ�....
	if (_environmemtSphereMesh == NULL)
	{
		D3DXCreateSphere(_device, 3.0f, 20, 20, &_environmemtSphereMesh, NULL);
	}
}

void gameNode::updateCamera(void)
{
	//ī�޶� ������Ʈ
	_mainCamera->DefaultControl(_timeDelta);
	_mainCamera->updateCamToDevice();
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}


