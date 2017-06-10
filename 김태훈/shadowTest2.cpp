#include "stdafx.h"
#include "shadowTest2.h"

HRESULT shadowTest2::init(void)
{
	//지형 클래스 생성후 초기화
	_terrain = new terrain;
	_terrain->init(
		"Resources/Textures/MyHeight512.bmp",
		"Resources/Textures/terrain1.png",
		"Resources/Textures/terrain2.png",
		"Resources/Textures/terrain3.png",
		"Resources/Textures/terrain4.png",
		"Resources/Textures/Splat.png",
		1.0f,
		200.0f,
		3,
		100);
	//지형그림자 클래스 생성후 초기화
	_terrainShadow = new terrain();
	_terrainShadow->init(
		"Resources/Textures/MyHeight128.bmp",
		"Resources/Textures/terrain1.png",
		"Resources/Textures/terrain2.png",
		"Resources/Textures/terrain3.png",
		"Resources/Textures/terrain4.png",
		"Resources/Textures/Splat.png",
		4.0f,
		200.0f,
		10,
		100);

	//원래 있던 매쉬에서 다음과 같은 행렬로 보정시켜 
	//모든 정보를 틀어버린다.
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.007f, 0.007f, 0.007f);
	D3DXMATRIXA16 matCorrection = matScale;

	//소나무 메쉬 로딩
	xMeshStatic* mesh = RM_XMESH->getResource("Resources/Meshes/Tree/PineTree_01.X", &matCorrection);
	//원판 메쉬 로딩
	xMeshStatic* Disc = RM_XMESH->getResource("Resources/Meshes/Disc/Disc.x");

	//오브젝트 생성
	for (int i = 0; i < OBJECT_NUM; i++)
	{
		for (int j = 0; j < OBJECT_NUM; j++)
		{
			baseObject* pNewObject = new baseObject;
			pNewObject->setMesh(mesh);
			pNewObject->setActive(true);

			//if( j % 2 == 0 )
			//pNewObject->IgnoreCreateShadow = true;	//그림자 안그림

			D3DXVECTOR3 pos(i * 10, 30.0f, j * 20);

			pos.y = this->_terrain->getHeight(pos.x, pos.z);

			//위치 셋팅
			pNewObject->_transform->SetWorldPosition(pos);

			//렌더 오브젝트
			//this->_renderObjects.push_back(pNewObject);
		}
	}

	//디스크 추가
	//baseObject* pNewObject2 = new baseObject;
	//pNewObject2->setMesh( Disc );
	//pNewObject2->setActive( true );
	//pNewObject2->_transform->SetWorldPosition( 0, -10.0f, 0.0f );
	//pNewObject2->ignoreCreateShadow = true;		//그림자 안그린다.
	//this->renderObjects.push_back( pNewObject2 );

	//기본라이트 방향
	_sceneBaseDirectionLight->_transform->RotateWorld(D3DXToRadian(90), 0, 0);
	this->setEnvironment("Resources/TextureCUBE/SuperKanjiCube.dds");

	D3DXMATRIXA16 matCorrection2;
	D3DXMatrixScaling(&matCorrection2, 0.1f, 0.1f, 0.1f);
	xMeshSkinned* pSkinned = RM_SKINNED->getResource("Resources/Meshes/Female/Femail.X", &matCorrection2);

	baseObject* pChar;
	pChar = new baseObject();
	pChar->setMesh(pSkinned);
	pChar->setActive(true);

	D3DXVECTOR3 pos2(0, 0, 0);
	//pos2.y = this->_terrain->getHeight(pos2.x, pos2.z);
	pChar->_transform->SetWorldPosition(pos2);

	this->_renderObjects.push_back(pChar);

	return S_OK;
}

void shadowTest2::release(void)
{
	//오브젝트 해제
	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		SAFE_DELETE(this->_renderObjects[i]);
	}
	//지형과 지형그림자 해제
	SAFE_DELETE(this->_terrain);
	SAFE_DELETE(this->_terrainShadow);
}

void shadowTest2::update(void)
{
	_sceneBaseDirectionLight->_transform->DefaultMyControl(_timeDelta);

	for (int i = 0; i < this->_renderObjects.size(); i++)
	{
		_renderObjects[i]->update();
	}
	//쉐도우맵 준비
	this->readyShadowMap(&this->_renderObjects, this->_terrainShadow);
}

void shadowTest2::render(void)
{
	//카메라에 컬링된거만....
	this->_cullObjects.clear();
	for (int i = 0; i < this->_renderObjects.size(); i++) 
	{
		//프러스텀 안에 있니?
		if (_mainCamera->_frustum.isInFrustum(_renderObjects[i]))
		{
			this->_cullObjects.push_back(_renderObjects[i]);
		}
	}

	xMeshStatic::setCamera(_mainCamera);
	if (KEYMANAGER->isStayKeyDown('1'))
	{
		//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
		xMeshStatic::setTechniqueName("CreateShadow");		
	}
	else
	{
		//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
		xMeshStatic::setTechniqueName("ReciveShadow");		
	}

	xMeshStatic::setBaseLight(this->_sceneBaseDirectionLight);

	xMeshSkinned::setCamera(_mainCamera);
	//xMeshSkinned::setTechniqueName("ReciveShadow");
	xMeshSkinned::setTechniqueName("Toon");
	xMeshSkinned::_sSkinnedMeshEffect->SetTexture("Ramp_Tex", RM_TEXTURE->getResource("Resources/Testures/Ramp_1.png"));
	xMeshSkinned::setBaseLight(this->_sceneBaseDirectionLight);

	for (int i = 0; i < this->_cullObjects.size(); i++)
	{
		this->_cullObjects[i]->render();
	}
	//_terrain->render(_mainCamera, _sceneBaseDirectionLight, _directionLightCamera);
}

void shadowTest2::renderSprite(void)
{

}
