#include "stdafx.h"
#include "useXMeshClass.h"

HRESULT useXMeshClass::init(void)
{
	//���� �ִ� �Ž����� ������ ���� ��ķ� �������� 
	//��� ������ Ʋ�������.
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);

	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));

	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	//_mesh = RM_XMESH->getResource("Resources/Meshes/GunShip/gunship.x", &matCorrection);
	//_mesh = RM_XMESH->getResource("Resources/Meshes/Raynor/Raynor.x", &matCorrection);
	//_mesh = RM_XMESH->getResource("Resources/Meshes/Elementalist/Elementalist.x", &matCorrection);
	_mesh = RM_XMESH->getResource("Resources/Meshes/GunShip/GunShip.x", &matCorrection);


	//����Ʈ Ǫ��
	light1 = new lightDirection;
	light1->_color = D3DXCOLOR(1, 1, 1, 1);
	light1->_intensity = 1.0f;

	lightPoint* light2 = new lightPoint;
	light2->_color = D3DXCOLOR(1, 1, 1, 0);
	light2->_minRange = 5.0f;
	light2->_maxRange = 10.0f;
	light2->_distancePow = 10.0f;

	lightPoint* light3 = new lightPoint;
	light3->_color = D3DXCOLOR(1, 1, 1, 0);
	light3->_minRange = 5.0f;
	light3->_maxRange = 10.0f;
	light3->_distancePow = 10.0f;
	light3->_transform->SetWorldPosition(3, 3, 0);
	light3->_intensity = 0.5f;

	_lights.push_back(light1);
	_lights.push_back(light2);
	_lights.push_back(light3);


	_camera = new camera;

	return S_OK;
}

void useXMeshClass::release(void)
{
	for (int i = 0; i < _lights.size(); i++)
	{
		SAFE_DELETE(_lights[i]);
	}
}

void useXMeshClass::update(void)
{
	//this->_lights[0]->_transform.DefaultMyControl(_timeDelta);
	this->_lights[1]->_transform->DefaultMyControl(_timeDelta);

	//_camera->DefaultControl(_timeDelta);
	_camera->updateCamToDevice();
	
}

void useXMeshClass::render(void)
{
	//����Ǵ� LightMatrix
	D3DXMATRIXA16 matLights[10];
	for (int i = 0; i < _lights.size(); i++)
	{
		matLights[i] = _lights[i]->getLightMatrix();
	}

	//_device->SetRenderState(D3DRS_LIGHTING, false);

	//���̴��� ������ ����
	//xMeshStatic::_staticMeshEffect->SetMatrixArray("matLights", matLights, 10);
	//xMeshStatic::_staticMeshEffect->SetInt("LightNum", _lights.size());
	//xMeshStatic::setCamera(this->_mainCamera);
	
	//_mesh->setLighting(&_lights);
	_mesh->setBaseLight(light1);
	//_mesh->setCamera(this->_mainCamera);
	_mesh->setCamera(this->_camera);

	_mesh->render(&_trans);
	
	//_device->SetRenderState(D3DRS_LIGHTING, true);

	_lights[0]->renderGizmo();
	_lights[1]->renderGizmo();
}
