#include "stdafx.h"
#include "baseObject.h"

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
		}
		else//���õ� �޽��� xMeshSkinned ��� �ӽ÷� �ٿ�� �ڽ������
		{
			D3DXMATRIX matScaling;
			//D3DXMatrixScaling(&matScaling, _mesh->getScale()/2, _mesh->getScale()/2, _mesh->getScale()/2);
			xMesh* mesh = RM_XMESH->getResource(_mesh->getFilePath(), matScaling);
			xMeshStatic* staticMesh = dynamic_cast<xMeshStatic*>(mesh);
			
			_boundBox._localCenter = staticMesh->_boundCenter;
			_boundBox._halfSize = staticMesh->_boundHalfSize/2;
			_boundBox._localMinPos = staticMesh->_boundMin/2;
			_boundBox._localMaxPos = staticMesh->_boundMax/2;
			_boundBox._radius = staticMesh->_boundRadius/2;

			//_boundBox.setBound(&D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(10.0f, 10.0f, 10.0f));
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
	_boundBox.renderGizmo(_transform);
}
