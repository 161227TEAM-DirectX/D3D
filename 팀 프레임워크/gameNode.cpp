#include "stdafx.h"
#include "gameNode.h"

gameNode::gameNode() : _environmentTexture(NULL), _environmemtSphereMesh(NULL)
{
	//ȯ�汸 ����Ʈ �ʱ�ȭ
	_environmentEffect = RM_SHADERFX->getResource("Resources/Shaders/EnvironmentCube.fx");
	
	//����ī�޶� �ʱ�ȭ
	_mainCamera = new camera;
	
	//�⺻ ���� ����
	_sceneBaseDirectionLight = new lightDirection;

	//���⼺ ������ ī�޶� �� �����Ѵ�.
	_directionLightCamera = new camera;

	//���⼺���� �ڽĿ� ���δ�.
	//_directionLightCamera->AttachTo(_sceneBaseDirectionLight->_transform );

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
}

gameNode::~gameNode()
{
	//ȯ���ؽ���, �޽� ����
	SAFE_RELEASE(_environmentTexture);
	SAFE_RELEASE(_environmemtSphereMesh);
	//����ī�޶� ����
	SAFE_DELETE(_mainCamera);
	//���⼺ ������ ī�޶� ����
	SAFE_DELETE(this->_sceneBaseDirectionLight);
	SAFE_DELETE(this->_directionLightCamera);
}

HRESULT gameNode::initGameNode(void)
{
	/*�����Լ� �ʱ�ȭ*/
	//�ʱ�ȭ�� ����� �ȵǾ��ٸ� �׳� ������Ѷ�
	if (FAILED(this->init())) return E_FAIL;

	//����ī�޶� RenderToTexture �غ�
	_mainCamera->readyRenderToTexture(WINSIZEX, WINSIZEY);
	//0----1
	//|  / |
	//| /  |
	//3----2
	_scenePlaneVertex[0].pos = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	_scenePlaneVertex[1].pos = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	_scenePlaneVertex[2].pos = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	_scenePlaneVertex[3].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	_scenePlaneVertex[0].uv = D3DXVECTOR2(0.0f, 0.0f);
	_scenePlaneVertex[1].uv = D3DXVECTOR2(1.0f, 0.0f);
	_scenePlaneVertex[2].uv = D3DXVECTOR2(1.0f, 1.0f);
	_scenePlaneVertex[3].uv = D3DXVECTOR2(0.0f, 1.0f);
	_scenePlaneIndex[0] = 0;
	_scenePlaneIndex[1] = 1;
	_scenePlaneIndex[2] = 3;
	_scenePlaneIndex[3] = 3;
	_scenePlaneIndex[4] = 1;
	_scenePlaneIndex[5] = 2;

	//����Ʈ ����Ʈ �ε�
	_postEffect = RM_SHADERFX->getResource("Resources/Shaders/PostEffect.fx");

	return S_OK;
}

void gameNode::releaseGameNode(void)
{
	/*�����Լ� ����*/
	this->release();
}

void gameNode::updateGameNode(void)
{

	if (KEYMANAGER->isToggleKey(VK_CAPITAL))
	{
		_mainCamera->DefaultControl(_timeDelta);
	}
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

	/*�����Լ� ������Ʈ*/
	this->update();
}

void gameNode::renderGameNode(void)
{
	_directionLightCamera->SetWorldPosition(1, 1, 1);
	_directionLightCamera->RenderGimozo();
	//����ī�޶� RTT�غ�
	_mainCamera->renderTextureBegin(0x00101010);
	
	//ȯ�� ����
	this->renderEnvironment();
	
	/*�����Լ� ����*/
	this->render();

	//����ī�޶� RTT����
	_mainCamera->renderTextureEnd();

	//����Ʈ ����Ʈ ����
	_postEffect->SetTechnique("Base");
	_postEffect->SetTexture("screenTex", _mainCamera->getRenderTexture());
	float pixelU = 1.0f / WINSIZEX;
	float pixelV = 1.0f / WINSIZEY;
	_postEffect->SetFloat("pixelSizeU", pixelU);
	_postEffect->SetFloat("pixelSizeV", pixelV);
	_postEffect->SetFloat("pixelHalfSizeU", pixelU * 0.5f);
	_postEffect->SetFloat("pixelHalfSizeV", pixelV * 0.5f);

	//����Ʈ ����Ʈ ����
	UINT iPass;
	_postEffect->Begin(&iPass, 0);
	for (UINT i = 0; i < iPass; i++) 
	{
		_postEffect->BeginPass(i);
		_device->SetFVF(SCENE_VERTEX::FVF);
		_device->DrawIndexedPrimitiveUP(
			D3DPT_TRIANGLELIST,
			0,
			4,
			2,
			_scenePlaneIndex,
			D3DFMT_INDEX16,
			_scenePlaneVertex,
			sizeof(SCENE_VERTEX));
		_postEffect->EndPass();
	}
	_postEffect->End();
	
	//��������Ʈ ����
	SPRITEMANAGER->beginSpriteRender();
	this->renderSprite(); //������������Ʈ (�����Լ�)
	SPRITEMANAGER->endSpriteRender();
}

//ȯ��� ����
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

//ȯ��� ����
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

//�ε���� �غ�
void gameNode::readyShadowMap(vector<baseObject*>* renderObjects, terrain * pTerrain)
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

//ī�޶� ������Ʈ
void gameNode::updateCamera(void)
{
	_mainCamera->DefaultControl(_timeDelta);
	_mainCamera->updateCamToDevice();
}



