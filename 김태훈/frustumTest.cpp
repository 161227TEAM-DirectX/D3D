#include "stdafx.h"
#include "frustumTest.h"

HRESULT frustumTest::init(void)
{
	//�����ִ� �޽����� ������ ���� ��ķ� �������� ��� ������ Ʋ�������.
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.01f, 0.01f, 0.01f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	D3DXMATRIXA16 matCorrention = matScale*matRotate;

	//���� �޽� �ε�
	xMeshStatic* mesh = RM_XMESH->getResource("Resources/Meshes/Fighter/Fighter.x", &matCorrention);

	//����Ʈ �Է�
	lightDirection* pLight1 = new lightDirection;
	pLight1->_color = D3DXCOLOR(1, 1, 1, 1);
	pLight1->_intensity = 1.0f;
	//����Ʈ ���Ϳ� ���
	_lights.push_back(pLight1);

	//������Ʈ ����
	for (int i = 0; i < OBJECTNUM; i++)
	{
		for (int j = 0; j < OBJECTNUM; j++)
		{
			baseObject* pNewObject = new baseObject;
			pNewObject->setMesh(mesh);
			pNewObject->setActive(true);

			//��ġ ����
			pNewObject->_transform->SetWorldPosition(i * 20, 0.0f, j * 20);

			//���� ������Ʈ �Է�
			_renderObjects.push_back(pNewObject);
		}
	}

	return S_OK;
}

void frustumTest::release(void)
{
	//����Ʈ ����
	for (int i = 0; i < _lights.size(); i++)
	{
		SAFE_DELETE(_lights[i]);
	}
	//������Ʈ ����
	for (int i = 0; i < _renderObjects.size(); i++)
	{
		SAFE_DELETE(_renderObjects[i]);
	}
}

void frustumTest::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_mainCamera->updateFrustum();
	}

	_cullObjects.clear();

	for (int i = 0; i < _renderObjects.size(); i++)
	{
		_renderObjects[i]->update();

		//�������� �ȿ� �ִ�??
		if (_mainCamera->_frustum.isInFrustum(_renderObjects[i]))
		{
			_cullObjects.push_back(_renderObjects[i]);
		}
	}
}

void frustumTest::render(void)
{
	xMeshStatic::setCamera(_mainCamera);
	xMeshStatic::setLighting(&_lights);

	for (int i = 0; i < _cullObjects.size(); i++)
	{
		_cullObjects[i]->render();
	}
	//���������� �׸���
	_mainCamera->_frustum.renderGizmo();
}
