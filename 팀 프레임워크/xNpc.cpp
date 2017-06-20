#include "stdafx.h"
#include "xNpc.h"

HRESULT xNpc::init(float posX, float posZ, string name)
{
	//터레인 링크 이미 끝내두자.

	_posX = posX;
	_posZ = posZ;
	_name = name;
	_playerTrace = false;
	xMeshSkinned* pSkinned = nullptr;
	D3DXMATRIXA16 matCorrection;
	D3DXMATRIXA16 matScale;
	D3DXMATRIXA16 matRotate;
	//pSkinned = RM_SKINNED->getResource("Resource/npc/thrall/thrall.X", &matCorrection);




	_NpcObject = new baseObject;
	if (_name == "상인쓰랄")
	{

		D3DXMatrixScaling(&matScale, 1, 1, 1);
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
		matCorrection = matRotate*matScale;
		pSkinned = RM_SKINNED->getResource("Resource/npc/thrall/thrall.X", &matCorrection);
		D3DXVECTOR3 pos = _NpcObject->_transform->GetWorldPosition();
		_NpcObject->_transform->SetScale(0.25f, 0.25f, 0.25f);
		_NpcObject->_boundBox.setBound(&D3DXVECTOR3(pos.x, pos.y + 2.0f, pos.z), &D3DXVECTOR3(1.3, 1.5, 1.3));
	}
	if (_name == "시바나스")
	{
		D3DXMatrixScaling(&matScale, 1, 1, 1);
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
		matCorrection = matRotate*matScale;
		pSkinned = RM_SKINNED->getResource("Resource/npc/sylvanas/sylvanas.X", &matCorrection);
		D3DXVECTOR3 pos = _NpcObject->_transform->GetWorldPosition();
		_NpcObject->_transform->SetScale(0.33f, 0.33f, 0.33f);
		_NpcObject->_boundBox.setBound(&D3DXVECTOR3(pos.x, pos.y + 2.0f, pos.z), &D3DXVECTOR3(1.3, 1.5, 1.3));
	}



	_NpcObject->setMesh(pSkinned);
	_NpcObject->setActive(true);



	//_renderObjects.push_back(_NpcObject);

	_NpcObject->_transform->SetWorldPosition(_posX, linkTerrain->getHeight(_posX, _posZ), _posZ);

	_NpcObject->_skinnedAnim->Play(0);

	return S_OK;
}

void xNpc::update()
{
	Ray ray;
	POINT ptMousePos = GetMousePos();
	D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
	D3DXVECTOR3 hitpos;
	gameNode::_mainCamera->computeRay(&ray, &screenPos);

	if (PHYSICSMANAGER->isRayHitBound(&ray, &_NpcObject->_boundBox, _NpcObject->_transform, &hitpos, nullptr))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			trans1 = *_NpcObject->_transform;
			trans2 = *_NpcObject->_transform;
			trans2.LookPosition(PLAYERMANAGER->GetPos());
			_Tlerp = 0;
			_playerTrace = true;
		}
	}

	if (_playerTrace == true)
	{
		_Tlerp += 2*_timeDelta;
		_NpcObject->_transform->RotateSlerp(trans1, trans2, _Tlerp);
		if (_Tlerp > 1.0f)
		{
			_playerTrace = false;
		}
	}
}

void xNpc::render()
{
	if (KEYMANAGER->isToggleKey(VK_F6))
	{
		FONTMANAGER->fontOut(_name + ".pos : " + to_string(_posX) + "," + to_string(_posX), 300, 0, 0xfffffffff);
		RM_SKINNED->getResource("Resource/npc/thrall/thrall.X")->ShowAnimationName(0, 0);
	}
}

void xNpc::release(void)
{
	for (int i = 0; i < _renderObjects.size(); i++)
	{
		SAFE_DELETE(_renderObjects[i]);
	}
}
