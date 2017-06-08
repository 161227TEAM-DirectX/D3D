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

	//StaticMesh 라면...
	if (pSkin == NULL)
	{
		if (_skinnedAnim != NULL)
		{
			_skinnedAnim->release();
			SAFE_DELETE(_skinnedAnim);
		}

		_skinnedAnim = NULL;
	}
	//SkinnedMesh 라면...
	else
	{
		_skinnedAnim = new skinnedAnimation;
		_skinnedAnim->init(pSkin);
	}
}

void baseObject::setActive(bool isActive)
{
	//활성화 되어있는 상태에서 비활성화 세팅시 
	if (isActive == false && _isActive)
	{
		_isActive = false;
		baseObjectDisable();
	}
	//비활성화 되어있는 상태에서 활성화 세팅시
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
		else//세팅된 메쉬가 xMeshSkinned 라면 임시로 바운드 박스만들기
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
	//오브젝트 바운드박스 보여주기
	_boundBox.renderGizmo(_transform);
}
