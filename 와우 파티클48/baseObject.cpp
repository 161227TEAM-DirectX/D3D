#include "stdafx.h"
#include "baseObject.h"

baseObject::baseObject() : _isActive(FALSE), _mesh(NULL)
{
	_transform = new transform;
}

baseObject::~baseObject()
{
	SAFE_DELETE(_transform);
}

void baseObject::update()
{
	if (_isActive) baseObjectUpdate();
	else baseObjectNoActiveUpdate();
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
	this->computeBoundBox();
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
	}
}


void baseObject::baseObjectRender()
{
	if(_mesh != NULL) _mesh->render(_transform);
	_boundBox.renderGizmo(_transform);
}
