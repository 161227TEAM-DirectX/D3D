#include "stdafx.h"
#include "stageThree.h"
#include "bossMonster.h"
#include "xPlayer.h"


stageThree::stageThree()
	:_shadowDistance(0.0f)
{
	_mainCamera = new camera;
	_directionLightCamera = new camera;
	sceneBaseDirectionLight = new lightDirection;
}


stageThree::~stageThree()
{
	for (int i = 0; i < _renderObject.size(); i++)
	{
		SAFE_DELETE(_renderObject[i]);
	}
	SAFE_DELETE(_mainCamera);
	SAFE_DELETE(_directionLightCamera);
	SAFE_DELETE(sceneBaseDirectionLight);
}

HRESULT stageThree::init()
{
	this->shadowInit();

	bossMonster* boss = new bossMonster;
	boss->setMesh(XMESH_MANAGER->GetXmeshSkinned("������"));
	boss->_transform->SetScale(5.0f, 5.0f, 5.0f);
	boss->_transform->SetWorldPosition(0.0f, 0.0f, 0.0f);
	boss->setActive(true);
	_renderObject.push_back(boss);


	return S_OK;
}

void stageThree::release()
{
}

void stageThree::update()
{
	// shadowUpdate();

	//������Ʈ ������Ʈ
	for (int i = 0; i < _renderObject.size(); i++) _renderObject[i]->update();
}

void stageThree::render()
{
	_directionLightCamera->_frustum.renderGizmo();

	//ī�޶� �ø��Ȱ͸�
	this->_cullObject.clear();
	for (int i = 0; i < this->_renderObject.size(); i++)
	{
		//�������� Ȯ��
		if (_mainCamera->_frustum.isInFrustum(_renderObject[i]))
		{
			this->_cullObject.push_back(_renderObject[i]);
		}
	}

	//������� ���� �׸����� ReciveShadow �� Technique ����
	xMeshStatic::setCamera(_mainCamera);
	//xMeshStatic::setTechniqueName("ReciveShadow");
	xMeshStatic::setTechniqueName("Toon");
	xMeshStatic::_staticMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resource/Testures/Ramp_1.png"));
	xMeshStatic::setBaseLight(this->sceneBaseDirectionLight);

	xMeshSkinned::setCamera(_mainCamera);
	//xMeshSkinned::setTechniqueName("ReciveShadow");
	xMeshSkinned::setTechniqueName("Toon");
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resource/Testures/Ramp_1.png"));
	xMeshSkinned::setBaseLight(this->sceneBaseDirectionLight);

	for (int i = 0; i < this->_cullObject.size(); i++)
	{
		this->_cullObject[i]->render();
	}
}

void stageThree::shadowInit(void)
{
	//���� �⺻ �� �ʱ�ȭ
	sceneBaseDirectionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	sceneBaseDirectionLight->_intensity = 1.0f;

	//�׸��ڸ� ���� ī�޶� �ڽ� ũ�� ������ ���� �ʱ�ȭ
	_shadowDistance = 100.0f;

	//�׸��� ī�޶��� ���� ��� ���� �� ���� / ���Ÿ� ũ�� ����
	_directionLightCamera->_isOrtho = true;	//��������
	_directionLightCamera->_camNear = 0.1f;	//�ٰŸ�
	_directionLightCamera->_camFar = _shadowDistance * 2.0f;
	_directionLightCamera->_aspect = 1;
	_directionLightCamera->_orthoSize = _shadowDistance * 1.5f;	//����ũ��

	//�ؽ�ó �غ�
	_directionLightCamera->readyShadowTexture(4096);

	_mainCamera->readyRenderToTexture(WINSIZEX, WINSIZEY);

	sceneBaseDirectionLight->_transform->SetWorldPosition(0, 20, 0);
	sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(90), 0, 0);
}

void stageThree::shadowUpdate(void)
{
	_mainCamera->updateBase();
	sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);

	//���� ��ġ
	D3DXVECTOR3 camPos = _mainCamera->GetWorldPosition();	//����ī�޶��� ��ġ
	D3DXVECTOR3 camFront = _mainCamera->GetForward();		//����ī�޸��� ����
	D3DXVECTOR3 lightDir = sceneBaseDirectionLight->_transform->GetForward();	//���⼺ ���� ����

	D3DXVECTOR3 lightPos = camPos +
		(camFront * (_shadowDistance * 0.5f)) +
		(-lightDir * _shadowDistance);

	_directionLightCamera->SetWorldPosition(lightPos.x, lightPos.y, lightPos.z);
	_directionLightCamera->LookDirection(lightDir);

	//������� �غ�
//	this->readyShadowMap(&this->_renderObject, /*��������*/)
}

void stageThree::shadowRender(void)
{

}

void stageThree::readyShadowMap(vector<baseObject*>* renderObjects, terrain * pTerrain)
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
		if (this->_mainCamera->_frustum.isInFrustum((*renderObjects)[i]))
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
		pTerrain->renderShadow(_mainCamera);
	}

	_directionLightCamera->renderTextureEnd();
}
