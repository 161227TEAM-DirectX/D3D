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
	//활성화 되어있는 상태에서 비활성화 셋팅시 
	if (isActive == false && _isActive)
	{
		_isActive = false;
		baseObjectDisable();
	}
	//비활성화 되어있는 상태에서 활성화 셋팅시
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
		dynamic_cast : 상속관계 안에서 포인터나 참조자의 타입을 
		기본클래스에서 파생클래스로 다운 캐스팅과 
		다중상속에서 기본 클래스간의 안전한 타입캐스팅에 사용한다.
		*/
		//세팅된 메쉬가 xMeshStatic 라면
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
