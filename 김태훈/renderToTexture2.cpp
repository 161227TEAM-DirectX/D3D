#include "stdafx.h"
#include "renderToTexture2.h"

HRESULT renderToTexture2::init(void)
{
	//���� �ִ� �޽����� ������ ���� ��ķ� ��������  ��� ������ Ʋ�������.
	D3DXMATRIXA16 matScale, matRotate, matCorrection;
	D3DXMatrixScaling(&matScale, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	matCorrection = matScale * matRotate;

	//���� �޽��ε�
	xMeshStatic* mesh = RM_XMESH->getResource("Resources/Meshes/Fighter/Fighter.x", &matCorrection);

	//����Ʈ �Է�
	lightDirection* pLight1 = new lightDirection;
	pLight1->_color = D3DXCOLOR(1, 1, 1, 1);
	pLight1->_intensity = 1.0f;
	//����Ʈ ���Ϳ� ���
	_lights.push_back(pLight1);

	//������Ʈ ����
	for (int i = 0; i < OBJECT_NUM; i++)
	{
		for (int j = 0; j < OBJECT_NUM; j++)
		{
			baseObject* pNewObject = new baseObject();
			pNewObject->setMesh(mesh);
			pNewObject->setActive(true);
			//��ġ ����
			pNewObject->_transform->SetWorldPosition(i * 10, 0, j * 20);
			//���� ������Ʈ �Է�
			this->_renderObjects.push_back(pNewObject);
		}
	}

////////////////////////////////////////////////////
	//������ �ؽ��� ����� ���� �����... 
	//ī�޶�Ŭ�����ȿ� readyRenderToTexture ����
	//�߰�ī�޶�..
	_extraCam = new camera;
	_extraCam->_camFar = 100.0f;
	int width = 512;
	int height = 512;

	//����Ʈ��Cam ��Ⱦ�� 
	_extraCam->_aspect = (float)width / (float)height;

	//����Ʈ�� ī�޶� RenderToTexture �غ�
	_extraCam->readyRenderToTexture(width, height);
////////////////////////////////////////////////////

	return S_OK;
}

void renderToTexture2::release(void)
{
	//����Ʈ ����
	for (int i = 0; i < this->_lights.size(); i++)
	{
		SAFE_DELETE(this->_lights[i]);
	}
	//������Ʈ ����
	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		SAFE_DELETE(this->_renderObjects[i]);
	}
	//�߰�ī�޶� ����
	SAFE_DELETE(this->_extraCam);
}

void renderToTexture2::update(void)
{
	//�߰� ī�޶� ��Ʈ��
	_extraCam->DefaultMyControl(_timeDelta);
	_extraCam->updateMatrix();

	for (int i = 0; i < _renderObjects.size(); i++) 
	{
		_renderObjects[i]->update();
	}
}

void renderToTexture2::render(void)
{
	//�߰� Ȯ�� ī�޶� ������
	_extraCam->updateFrustum();
	_cullObjects.clear();
	for (int i = 0; i < _renderObjects.size(); i++)
	{
		if (_extraCam->_frustum.isInFrustum(_renderObjects[i]))
		{
			_cullObjects.push_back(_renderObjects[i]);
		}
	}
	//�����(���� ���� ���� ������ ����)�� �� �� ����.
	//���� �� �ؽ��� ����
	_extraCam->renderTextureBegin(0xffff0000);

	xMeshStatic::setCamera(_extraCam);
	xMeshStatic::setLighting(&_lights);

	for (int i = 0; i < _cullObjects.size(); i++)
	{
		_cullObjects[i]->render();
	}

	//���� �� �ؽ��� ��
	_extraCam->renderTextureEnd();

	//����ī�޶� �������� �ø�
	_mainCamera->updateFrustum();
	_cullObjects.clear();

	for (int i = 0; i < _renderObjects.size(); i++)
	{
		if (_mainCamera->_frustum.isInFrustum(_renderObjects[i]))
		{
			_cullObjects.push_back(_renderObjects[i]);
		}
	}

	xMeshStatic::setCamera(_mainCamera);
	xMeshStatic::setLighting(&_lights);

	for (int i = 0; i < _cullObjects.size(); i++)
	{
		_cullObjects[i]->render();
	}

	//����� �׷�����
	_extraCam->_frustum.renderGizmo();
}

void renderToTexture2::renderSprite(void)
{
	RECT rcSour = { 0, 0, 512, 512 };
	RECT rcDest = { 0, 0, 512, 512 };
	SPRITEMANAGER->renderArea(_extraCam->getRenderTexture(), &rcSour, &rcDest);
}
