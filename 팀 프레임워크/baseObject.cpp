#include "stdafx.h"
#include "baseObject.h"
#include "monster.h"

baseObject::baseObject() : _isActive(FALSE), _mesh(NULL), _skinnedAnim(NULL)
{
	_transform = new dx::transform;
	_ignoreCreateShadow = false;
}

baseObject::~baseObject()
{
	SAFE_DELETE(_transform);
	if (_skinnedAnim != NULL)
	{
		_skinnedAnim->release();
		SAFE_DELETE(_skinnedAnim);
	}
}

void baseObject::update()
{
	if (_isActive)
	{
		this->baseObjectUpdate();
		if (_skinnedAnim != NULL)
		{
			_skinnedAnim->update();
		}
	}
	else
	{
		baseObjectNoActiveUpdate();
	}
}

void baseObject::render()
{
	if (_isActive)
	{
		baseObjectRender();
	}
}

void baseObject::setMesh(xMesh * pMesh)
{
	_mesh = pMesh;
	xMeshSkinned* pSkin = dynamic_cast<xMeshSkinned*>(pMesh);

	this->computeBoundBox();

	//StaticMesh ���...
	if (pSkin == NULL)
	{
		if (_skinnedAnim != NULL)
		{
			_skinnedAnim->release();
			SAFE_DELETE(_skinnedAnim);
		}

		_skinnedAnim = NULL;
	}
	//SkinnedMesh ���...
	else
	{
		_skinnedAnim = new skinnedAnimation;
		_skinnedAnim->init(pSkin);
	}
}

void baseObject::setActive(bool isActive)
{
	//Ȱ��ȭ �Ǿ��ִ� ���¿��� ��Ȱ��ȭ ���ý� 
	if (isActive == false && _isActive)
	{
		_isActive = false;
		baseObjectDisable();
	}
	//��Ȱ��ȭ �Ǿ��ִ� ���¿��� Ȱ��ȭ ���ý�
	else if (isActive && _isActive == false)
	{
		_isActive = true;
		baseObjectEnable();
	}
}

void baseObject::computeBoundBox()
{
	if (_mesh != NULL)
	{
		/*
		dynamic_cast : ��Ӱ��� �ȿ��� �����ͳ� �������� Ÿ���� 
		�⺻Ŭ�������� �Ļ�Ŭ������ �ٿ� ĳ���ð� 
		���߻�ӿ��� �⺻ Ŭ�������� ������ Ÿ��ĳ���ÿ� ����Ѵ�.
		*/
		//���õ� �޽��� xMeshStatic ���
		xMeshStatic* staticMesh = dynamic_cast<xMeshStatic*>(_mesh);
		if (staticMesh != NULL)
		{
			_boundBox._localCenter = staticMesh->_boundCenter;
			_boundBox._halfSize = staticMesh->_boundHalfSize;
			_boundBox._localMinPos = staticMesh->_boundMin;
			_boundBox._localMaxPos = staticMesh->_boundMax;
			_boundBox._radius = staticMesh->_boundRadius;
			return;
		}
		else//���õ� �޽��� xMeshSkinned ��� �ӽ÷� �ٿ�� �ڽ������
		{
			D3DXMATRIX matScaling;
			D3DXMATRIX mat;
			D3DXMATRIX matRotate;
			D3DXMatrixScaling(&matScaling, _mesh->getScale()/2, _mesh->getScale()/2, _mesh->getScale()/2);
			D3DXMatrixRotationY(&matRotate, D3DXToRadian(180));
			mat = matScaling * matRotate;
			tagSaveMonsterBoundBox temp;
		//	xMesh* mesh = RM_XMESH->getResource(_mesh->getFilePath(), mat);
		//	xMeshStatic* staticMesh = dynamic_cast<xMeshStatic*>(mesh);
			monster* tempMonster = dynamic_cast<monster*>(this);
			if (tempMonster == nullptr) return;
			temp = IOSAVEMONSTERBOX->findTag(tempMonster->getLastName());
		//
			_boundBox._localCenter = temp.localCenter;
			_boundBox._localMinPos = temp.localMinPos;
			_boundBox._localMaxPos = temp.localMaxPos;
			_boundBox._halfSize = temp.halfSize;
			_boundBox._radius = temp.radius;
		//	_boundBox._localCenter = staticMesh->_boundCenter;
		//	_boundBox._halfSize = staticMesh->_boundHalfSize;
		//	_boundBox._localMinPos = staticMesh->_boundMin;
		//	_boundBox._localMaxPos = staticMesh->_boundMax;
		//	_boundBox._radius = staticMesh->_boundRadius;

		//	string temp = _mesh->getFilePath();
		//
		//	if (!strcmp("Resource/Meshes/BossMonster/deathwing_ok/x/deathWing.x", temp.c_str()))
		//	{
		//		//������ �ٿ�� �ڽ��� �缳��.
		//		_boundBox._localMaxPos = _boundBox._localMaxPos / 2;
		//		_boundBox._localCenter = (_boundBox._localMinPos + _boundBox._localMaxPos)*0.5f;
		//		_boundBox._halfSize = D3DXVECTOR3(
		//			_boundBox._localMaxPos.x - _boundBox._localMinPos.x,
		//			_boundBox._localMaxPos.y - _boundBox._localMinPos.y,
		//			_boundBox._localMaxPos.z - _boundBox._localMinPos.z)*0.5f;
		//
		//		_boundBox._radius = D3DXVec3Length(&(_boundBox._localCenter - _boundBox._localMinPos));
		//	}
		//
		//	//_boundBox.setBound(&D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(10.0f, 10.0f, 10.0f));
		//
		//	RM_XMESH->removeResource(mesh->getFilePath());
		}
	}
}


void baseObject::baseObjectRender()
{
	if (_mesh != NULL)
	{
		if (_skinnedAnim)
		{
			_skinnedAnim->render(_transform);
		}
		else
		{
			_mesh->render(_transform);
		}
	}
	//������Ʈ �ٿ��ڽ� �����ֱ�
	if (KEYMANAGER->isToggleKey(VK_F8))
	{
		_boundBox.renderGizmo(_transform);
	}
}
