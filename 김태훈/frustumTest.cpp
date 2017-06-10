#include "stdafx.h"
#include "frustumTest.h"

HRESULT frustumTest::init(void)
{
	//원래있던 메쉬에서 다음과 같은 행렬로 보정시켜 모든 정보를 틀어버린다.
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.01f, 0.01f, 0.01f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
	D3DXMATRIXA16 matCorrention = matScale*matRotate;

	//원본 메쉬 로딩
	xMeshStatic* mesh = RM_XMESH->getResource("Resources/Meshes/Fighter/Fighter.x", &matCorrention);

	//라이트 입력
	lightDirection* pLight1 = new lightDirection;
	pLight1->_color = D3DXCOLOR(1, 1, 1, 1);
	pLight1->_intensity = 1.0f;
	//라이트 벡터에 담기
	_lights.push_back(pLight1);

	//오브젝트 생성
	for (int i = 0; i < OBJECTNUM; i++)
	{
		for (int j = 0; j < OBJECTNUM; j++)
		{
			baseObject* pNewObject = new baseObject;
			pNewObject->setMesh(mesh);
			pNewObject->setActive(true);

			//위치 세팅
			pNewObject->_transform->SetWorldPosition(i * 20, 0.0f, j * 20);

			//렌더 오브젝트 입력
			_renderObjects.push_back(pNewObject);
		}
	}

	return S_OK;
}

void frustumTest::release(void)
{
	//라이트 해제
	for (int i = 0; i < _lights.size(); i++)
	{
		SAFE_DELETE(_lights[i]);
	}
	//오브젝트 해제
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

		//프러스텀 안에 있니??
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
	//프러스텀을 그리자
	_mainCamera->_frustum.renderGizmo();
}
