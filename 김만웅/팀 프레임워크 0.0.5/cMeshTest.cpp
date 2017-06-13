#include "stdafx.h"
#include "cMeshTest.h"


cMeshTest::cMeshTest()
{
}


cMeshTest::~cMeshTest()
{
}

HRESULT cMeshTest::init()
{
	//����ī�޶� �ʱ�ȭ
	_mainCamera = new camera;

	//�⺻ ���� ����
	_sceneBaseDirectionLight = new lightDirection;

	//���⼺ ������ ī�޶� �� �����Ѵ�.
	_directionLightCamera = new camera;

	//�⺻ ��
	_sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	_sceneBaseDirectionLight->_intensity = 1.0f;

	//�׸��� �Ÿ�
	_shadowDistance = 100.0f;

	//ī�޶��� ��������� �ٲ۴�...
	_directionLightCamera->_isOrtho = true;
	_directionLightCamera->_camNear = 0.1f;
	_directionLightCamera->_camFar = _shadowDistance * 2.0f;
	_directionLightCamera->_aspect = 1;
	_directionLightCamera->_orthoSize = _shadowDistance * 1.5f;	//����ũ��� �׸���ũ���

	//���⼺���� ī�޶��� RenderToTexture �غ�
	_directionLightCamera->readyShadowTexture(4096);


	//���� �ִ� �Ž����� ������ ���� ��ķ� �������� 
	//��� ������ Ʋ�������.
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.007f, 0.007f, 0.007f);
	D3DXMATRIXA16 matCorrection = matScale;

	//�⺻����Ʈ ����
	_sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(90), 0, 0);

	D3DXMATRIXA16 matCorrection2;
	D3DXMatrixScaling(&matCorrection2, 1.0f, 1.0f, 1.0f);
	xMeshSkinned* pSkinned =
		RM_SKINNED->getResource("Resources/Meshes/Witch/WitchApprentice.X",
								&(matCorrection2*0.1f));

	_pSkinned1 = new skinnedAnimation;
	_pSkinned1->init(pSkinned);
	_pSkinnedTrans1 = new dx::transform;
	_aniObjects.push_back(_pSkinned1);

	baseObject* pChar;
	pChar = new baseObject();
	pChar->setMesh(pSkinned);
	pChar->setActive(true);

	_renderObjects.push_back(pChar);


	return S_OK;
}

void cMeshTest::release()
{
	SAFE_DELETE(_pSkinnedTrans1);
	SAFE_DELETE(_pSkinned1);

	//������Ʈ ����
	for (int i = 0; i < _renderObjects.size(); i++)
	{
		SAFE_DELETE(_renderObjects[i]);
	}

	SAFE_DELETE(_sceneBaseDirectionLight);
	SAFE_DELETE(_directionLightCamera);
	SAFE_DELETE(_mainCamera);
}

void cMeshTest::update()
{
	_pSkinned1->update();

	_mainCamera->DefaultControl(_timeDelta);
	_mainCamera->updateCamToDevice();
	_mainCamera->updateFrustum();

	//���� ��ġ
	D3DXVECTOR3 camPos = _mainCamera->GetWorldPosition();		//����ī�޶��� ��ġ
	D3DXVECTOR3 camFront = _mainCamera->GetForward();			//����ī�޶��� ����
	D3DXVECTOR3 lightDir = _sceneBaseDirectionLight->_transform->GetForward();	//���⼺ ������ ����

	D3DXVECTOR3 lightPos = camPos +
		(camFront * (_shadowDistance * 0.5f)) +
		(-lightDir * _shadowDistance);

	_directionLightCamera->SetWorldPosition(lightPos.x, lightPos.y, lightPos.z);
	_directionLightCamera->LookDirection(lightDir);

	_sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);

	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		_renderObjects[i]->update();
	}

	for (int i=0; i < _aniObjects.size(); i++)
	{
		if (KEYMANAGER->isOnceKeyDown('1'))
		{
			_aniObjects[i]->Play("Idle", 0.3f);
		}
		if (KEYMANAGER->isOnceKeyDown('2'))
		{
			_aniObjects[i]->Play("Walk", 0.3f);
		}
		if (KEYMANAGER->isOnceKeyDown('3'))
		{
			_aniObjects[i]->Play("run", 0.3f);
		}
		if (KEYMANAGER->isOnceKeyDown('4'))
		{
			_aniObjects[i]->PlayOneShot("Atk01", 0.3, 0.3);
		}
		if (KEYMANAGER->isOnceKeyDown('5'))
		{
			_aniObjects[i]->PlayOneShotAfterHold("Death", 0.3);
		}

		static float speed = 1.0f;
		_pSkinned1->SetPlaySpeed(speed);
	}
}

void cMeshTest::render()
{
	//ī�޶� �ø��ȰŸ�....
	this->_cullObjects.clear();
	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		//�������� �ȿ� �ִ�?
		if (_mainCamera->_frustum.isInFrustum(_renderObjects[i]))
		{
			this->_cullObjects.push_back(_renderObjects[i]);
		}
	}

	xMeshStatic::setCamera(_mainCamera);
	if (KEYMANAGER->isStayKeyDown('1'))
	{
		//������� ���� �׸����� ReciveShadow �� Technique ����
		xMeshStatic::setTechniqueName("CreateShadow");
	}
	else
	{
		//������� ���� �׸����� ReciveShadow �� Technique ����
		xMeshStatic::setTechniqueName("ReciveShadow");
	}

	xMeshStatic::setBaseLight(this->_sceneBaseDirectionLight);

	xMeshSkinned::setCamera(_mainCamera);
	//xMeshSkinned::setTechniqueName("ReciveShadow");
	xMeshSkinned::setTechniqueName("Toon");
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resources/Testures/Ramp_1.png"));
	xMeshSkinned::setBaseLight(this->_sceneBaseDirectionLight);

	for (int i = 0; i < this->_cullObjects.size(); i++)
	{
		//this->_cullObjects[i]->render();
	}

	for (int i=0; i < _aniObjects.size(); i++)
	{
		_aniObjects[i]->render(_pSkinnedTrans1);
	}
	//_pSkinned1->render(_pSkinnedTrans1);
}

void cMeshTest::readyShadowMap(vector<baseObject*>* renderObjects, terrain * pTerrain)
{
	//���⼺������ ���� ī�޶��� Frustum ������Ʈ
	_directionLightCamera->updateMatrix();
	_directionLightCamera->updateFrustum();

	//���̷��Ƕ����� ī�޶� ������ �ֵ鸸 �׸���...
	static vector<baseObject*>	shadowCullObject;
	shadowCullObject.clear();

	for (int i = 0; i < renderObjects->size(); i++)
	{
		//�������� �ȿ� �ִ�?
		if (this->_directionLightCamera->_frustum.isInFrustum((*renderObjects)[i]))
		{
			shadowCullObject.push_back((*renderObjects)[i]);
		}
	}

	//������ �� �׸���.
	_directionLightCamera->renderTextureBegin(0xffffffff);

	//�����޽� ����
	xMeshStatic::setCamera(this->_directionLightCamera);
	xMeshStatic::setTechniqueName("CreateShadow");
	//��Ų��޽� ����
	xMeshSkinned::setCamera(this->_directionLightCamera);
	xMeshSkinned::setTechniqueName("CreateShadow");

	for (int i = 0; i < shadowCullObject.size(); i++)
	{
		if (shadowCullObject[i]->_ignoreCreateShadow == false)
		{
			shadowCullObject[i]->render();
		}
	}

	//���� Terrain �� ������ ���� �׷����Ѵٸ�...
	if (pTerrain != NULL)
	{
		pTerrain->renderShadow(_directionLightCamera);
	}

	_directionLightCamera->renderTextureEnd();


	//���� Terrain �� ������ ���� �����Ѵٸ�
	if (pTerrain != NULL)
	{
		pTerrain->_terrainEffect->SetTexture("Shadow_Tex", _directionLightCamera->getRenderTexture());
		pTerrain->_terrainEffect->SetMatrix("matLightViewProjection", &_directionLightCamera->getViewProjectionMatrix());
	}

	//������ �ؽ���
	xMeshStatic::_staticMeshEffect->SetTexture("Shadow_Tex", _directionLightCamera->getRenderTexture());
	//������ ���
	xMeshStatic::_staticMeshEffect->SetMatrix("matLightViewProjection", &_directionLightCamera->getViewProjectionMatrix());
	//������ �ؽ���
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Shadow_Tex", _directionLightCamera->getRenderTexture());
	//������ ���
	xMeshSkinned::_sSkinnedMeshEffect->SetMatrix("matLightViewProjection", &_directionLightCamera->getViewProjectionMatrix());

}
