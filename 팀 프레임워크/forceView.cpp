#include "stdafx.h"
#include "forceView.h"

HRESULT forceView::init(void)
{
	_directionLight = new lightDirection;
	_directionLight->_transform->RotateWorld(D3DXToRadian(90), 0, 0);
	_directionLight->_color = D3DXCOLOR(1, 1, 1, 1);
	_directionLight->_intensity = 2.0f;

	_sword[0].setMesh(RM_XMESH->getResource("ResourceUI/inven/weaponMesh/weapon01/weapon01.x"));
	_sword[0]._transform->SetWorldPosition(0, 0, 0);
	_sword[0]._transform->SetRotateLocal(D3DXToRadian(90), D3DXToRadian(90), 0);
	_sword[0].setActive(true);

	_sword[1].setMesh(RM_XMESH->getResource("ResourceUI/inven/weaponMesh/weapon02/weapon02.x"));
	_sword[1]._transform->SetWorldPosition(0, 0, 0);
	_sword[1]._transform->SetRotateLocal(D3DXToRadian(90), D3DXToRadian(90), 0);
	_sword[1].setActive(true);

	_sword[2].setMesh(RM_XMESH->getResource("ResourceUI/inven/weaponMesh/weapon03/weapon03.x"));
	_sword[2]._transform->SetWorldPosition(0, 0, 0);
	_sword[2]._transform->SetRotateLocal(D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(90));
	_sword[2].setActive(true);

	_sword[3].setMesh(RM_XMESH->getResource("ResourceUI/inven/weaponMesh/weapon04/weapon04.x"));
	_sword[3]._transform->SetWorldPosition(0, 0, 0);
	_sword[3]._transform->SetRotateLocal(D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(90));
	_sword[3].setActive(true);

	_sword[4].setMesh(RM_XMESH->getResource("ResourceUI/inven/weaponMesh/weapon05/weapon05.x"));
	_sword[4]._transform->SetWorldPosition(0, 0, 0);
	_sword[4]._transform->SetRotateLocal(D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(90));
	_sword[4].setActive(true);
		
	_mainCamera.SetLocalPosition(0, 1.2f, -5.0f);

	speed = D3DXToRadian(5);
	
	return S_OK;
}

void forceView::release(void)
{
}

void forceView::update(void)
{
	if (forceViewNumber != 0)
	{
		_sword[forceViewNumber - 1]._transform->RotateWorld(0, speed, 0);
	}
}

void forceView::render(void)
{
	_mainCamera.updateCamToDevice();

	xMeshStatic::_staticMeshEffect->SetMatrixArray("matLights", &_directionLight->getLightMatrix(), 1);
	xMeshStatic::_staticMeshEffect->SetInt("LightNum", 1);
	xMeshStatic::setCamera(&_mainCamera);

	if (forceViewNumber == 1)
	{
		_mainCamera.SetLocalPosition(0, 1.2f, -5.0f);
		_sword[0].render();
	}
	if (forceViewNumber == 2)
	{
		_mainCamera.SetLocalPosition(0, 1.6f, -8.0f);
		_sword[1].render();
	}
	if (forceViewNumber == 3)
	{
		_mainCamera.SetLocalPosition(0, 1.2f, -5.0f);
		_sword[2].render();
	}
	if (forceViewNumber == 4)
	{
		_mainCamera.SetLocalPosition(0, 1.2f, -3.0f);
		_sword[3].render();
	}
	if (forceViewNumber == 5)
	{
		_mainCamera.SetLocalPosition(0, 1.2f, -3.0f);
		_sword[4].render();
	}
}
